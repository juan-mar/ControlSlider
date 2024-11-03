#include <Arduino.h>
#include <unity.h>

void test_hello_world() {
    TEST_ASSERT_EQUAL_STRING("Hello, World!", "Hello, World!");
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_hello_world);
    UNITY_END();
}

void loop() {
}