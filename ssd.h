/* 
 * File:   ssd.h
 * Author: ahmed
 *
 * Created on May 16, 2022, 10:29 AM
 */

#ifndef SSD_H
#define	SSD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "gpio.h"
#include "timer_basic.h"
    
//General Configration
#define S_SEG_COMMON_CATHODE                0
#define S_SEG_COMMON_ANODE                  1
    
#define S_SEG_NR_OF_DIGITS                  4
#define S_SEG_TYPE                          S_SEG_COMMON_ANODE
    
    
#define S_SEG_PORT                          GPIOD

//All pins must be on the same port. 
#define SEGMENT_A_PIN						GPIO_PIN0
#define SEGMENT_B_PIN						GPIO_PIN1
#define SEGMENT_C_PIN						GPIO_PIN2
#define SEGMENT_D_PIN						GPIO_PIN3
#define SEGMENT_E_PIN						GPIO_PIN4
#define SEGMENT_F_PIN						GPIO_PIN5
#define SEGMENT_G_PIN						GPIO_PIN6

// The dot can be on a different port
#define SEGMENT_DOT_PORT					GPIOD
#define SEGMENT_DOT_PIN						GPIO_PIN7

// Common anode or common cathode pin for each digit
#define DISPLAY_DIGIT_1_PORT				GPIOB
#define DISPLAY_DIGIT_1_PIN					GPIO_PIN0

#define DISPLAY_DIGIT_2_PORT				GPIOB
#define DISPLAY_DIGIT_2_PIN					GPIO_PIN1

#define DISPLAY_DIGIT_3_PORT				GPIOB
#define DISPLAY_DIGIT_3_PIN					GPIO_PIN2

#define DISPLAY_DIGIT_4_PORT				GPIOB
#define DISPLAY_DIGIT_4_PIN					GPIO_PIN3


#define S_SEGMENT_DIGIT0    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_F_PIN)
#define S_SEGMENT_DIGIT1    (SEGMENT_E_PIN | SEGMENT_F_PIN)
#define S_SEGMENT_DIGIT2    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT3    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT4    (SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT5    (SEGMENT_A_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT6    (SEGMENT_A_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT7    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN)
#define S_SEGMENT_DIGIT8    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_E_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN)
#define S_SEGMENT_DIGIT9    (SEGMENT_A_PIN | SEGMENT_B_PIN | SEGMENT_C_PIN | SEGMENT_D_PIN | SEGMENT_F_PIN | SEGMENT_G_PIN)

void SSD_Init(void);
void SSD_Update(void);
void SSD_SetInt(int num, int8_t start_position, int8_t digits_number);
void SSD_Digits_TurnOFF(void);
void SSD_Clear(void);
void SSD_DotOn(uint8_t dot_number);
void SSD_DotOff(uint8_t dot_number);
void SSD_Dottoggle(uint8_t dot_number);

#ifdef	__cplusplus
}
#endif

#endif	/* SSD_H */

