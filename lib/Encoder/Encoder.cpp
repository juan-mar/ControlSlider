#include "Arduino.h"
#include "Encoder.h"
#include "Encoder_config.h"


//Interrupcion en caso de giro del encoder
static void IRAM_ATTR PIN_AB(void);

//Interrupcion en caso de que se haya apretado el boton
static void IRAM_ATTR DRV_PISR(void);

static hw_timer_t *Timer0_Cfg = NULL;

/*******************************************************************************
 * VARIABLE WITH GLOBAL SCOPE
 ******************************************************************************/
//Si las vueltas fueron hacia la derecha es positivo, sino negativo
static int vueltas;

//Cantidad de veces que fue apretado el boton
static int bot;

//Variable que se utilizara para contar las rotaciones del encoder
static int val_prev;


/*******************************************************************************
 * INICIALIZACION
 ******************************************************************************/
void DRV_Enc_Init (void)
{
	/*
	gpioMode(PIN_A, INPUT);
	gpioMode(PIN_B, INPUT);
	gpioMode(BOTON, INPUT);
	gpioIRQ(PIN_A, GPIO_IRQ_MODE_BOTH_EDGES, PIN_AB);
	gpioIRQ(PIN_B, GPIO_IRQ_MODE_BOTH_EDGES, PIN_AB);
	gpioFILT(PIN_A,0b11111);
	gpioFILT(PIN_B,0b11111);
	*/

	pinMode(PIN_A, INPUT);
	pinMode(PIN_B, INPUT);
	pinMode(BOTON, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_A), PIN_AB, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_B), PIN_AB, CHANGE);

    Timer0_Cfg = timerBegin(0, 80, true);
	timerAttachInterrupt(Timer0_Cfg, &DRV_PISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000*10, true);
    timerAlarmEnable(Timer0_Cfg);


	//SysTick_Init();
	//SysTick_Add(DRV_PISR);
	
	vueltas = 0;
	bot = 0;
	val_prev = (digitalRead(PIN_A)<<1)+ digitalRead(PIN_B);


}


/*******************************************************************************
 * FUNCIONES A UTILIZAR POR APP
 ******************************************************************************/
//Devuelve la cantidad de rotaciones del encoder
int get_vueltas()
{
	int32_t giros = vueltas/ESTADOS_TICK;
	vueltas = 0;
	return giros;
}

//Si paso un tick devuelve la cantidad de vueltas, sino 0
int get_paso()
{
	if(vueltas >= 4 || vueltas <= -4)
		return get_vueltas();
	else
		return 0;
}

//Devuelve la cantidad de veces que fue apretado el boton
int get_boton()
{
	int push = bot;
	bot = 0;
	return push;
}



/*******************************************************************************
 * INTERRUPCIONES
 ******************************************************************************/
//Interrupcion dedicada para contar los giros del encoder
static void IRAM_ATTR PIN_AB(void)
{
	int val_new = (digitalRead(PIN_A)<<1)+ digitalRead(PIN_B);
	switch(val_new)
	{
		case ESTADO1:
			if(val_prev == ESTADO3)
				vueltas++;			//giro DER
			if(val_prev == ESTADO2)
				vueltas--;			//giro IZQ
			break;
		case ESTADO2:
			if(val_prev == ESTADO1)
				vueltas++;
			if(val_prev == ESTADO4)
				vueltas--;
			break;
		case ESTADO3:
			if(val_prev == ESTADO4)
				vueltas++;
			if(val_prev == ESTADO1)
				vueltas--;
			break;
		case ESTADO4:
			if(val_prev == ESTADO2)
				vueltas++;
			if(val_prev == ESTADO3)
				vueltas--;
			break;
	}
	val_prev = val_new;
}

//Interrupcion periodica que cuenta la cantidad de veces que se apreto el boton
static void IRAM_ATTR DRV_PISR(void)
{
	static int val_prev;
	int val_new = digitalRead(BOTON);

	if((val_new != val_prev) && val_new == BOT_ACTIVE)
	{
		bot++;
	}
	val_prev= val_new;

}
