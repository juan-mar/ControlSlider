/***************************************************************************//**
  @file     Encoder_config.h
  @brief    Encoder driver
  @author   Grupo 2
 ******************************************************************************/

#ifndef _ENCODER_CONFIG_H_
#define _ENCODER_CONFIG_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>
#include "board.h"

/*******************************************************************************
 * LOCAL CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define PIN_A     PIN_ENCODER_A // PTB2
#define PIN_B     PIN_ENCODER_B // PTB3
#define BOTON     PIN_ENCODER_SW // PTB10


#define ESTADO1	0b00
#define ESTADO2 0b01
#define ESTADO3 0b10
#define ESTADO4 0b11

#define BOT_ACTIVE 0

#define ESTADOS_TICK  4		//cantidad de estados por los que pasa el encoder en cada tick

/*******************************************************************************
 ******************************************************************************/

#endif // _ENCODER_CONFIG_H_
