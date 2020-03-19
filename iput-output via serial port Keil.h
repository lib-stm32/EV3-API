#ifdef __cplusplus
extern "C" {
#endif
#ifndef ev3_constants_h
#define ev3_constants_h
#ifndef input-output via serial port Keil
#define input-output via serial port Keil
#define ev3_output_h
#define keil_in_h
#include <stdint.h>

#define TRUE 1
#define FALSE 0
//output ev3
#define OUT_A 0x01
#define OUT_B 0x02
#define OUT_C 0x04
#define OUT_D 0x08 // 8-bit OUTPUT
#define OUT_AB 0x03
#define OUT_AC 0x05
#define OUT_AD 0x09
#define OUT_BC   0x06 
#define OUT_BD   0x0a 
#define OUT_CD   0x0c
#define OUT_ABC  0x07 
#define OUT_BCD  0x0e 
#define OUT_ABCD 0x0f 
#define OUT_ALL  0x0f 
#define OUT_MASK 0x0f
//INPUT for stm32
#define INPUT_A 0x0
#define INPUT_B 0x1
#define INPUT_C 0x2
#define INPUT_D 0x3

bool Instm32(default)
bool INstm32(OUT_AC == 0xf; INPUT_AC == 0x0f)
// 
#endif

#ifdef __cplusplus
}
#endif