#include "ssd.h"

static volatile uint8_t digit[] = {S_SEGMENT_DIGIT0, S_SEGMENT_DIGIT1, S_SEGMENT_DIGIT2, S_SEGMENT_DIGIT3, S_SEGMENT_DIGIT4,
                         S_SEGMENT_DIGIT5, S_SEGMENT_DIGIT6, S_SEGMENT_DIGIT7, S_SEGMENT_DIGIT8, S_SEGMENT_DIGIT9};
static int buffer[S_SEG_NR_OF_DIGITS] = {0};
static volatile uint8_t SSD_DOT_STATES = 0;

void SSD_Init(void)
{
    GPIO_Init(S_SEG_PORT, GPIO_PINS, GPIO_Mode_OUT);
    GPIO_Init(DISPLAY_DIGIT_1_PORT, DISPLAY_DIGIT_1_PIN, GPIO_Mode_OUT);
    GPIO_Init(DISPLAY_DIGIT_2_PORT, DISPLAY_DIGIT_2_PIN, GPIO_Mode_OUT);
    GPIO_Init(DISPLAY_DIGIT_3_PORT, DISPLAY_DIGIT_3_PIN, GPIO_Mode_OUT);
    GPIO_Init(DISPLAY_DIGIT_4_PORT, DISPLAY_DIGIT_4_PIN, GPIO_Mode_OUT);
    
    Timer0_init(Normal_Mode, TIMER_Prescaler_1024);
    Timer0_Set_Preload_Value(178);                                  //Tick every 5MS
    Timer0_Enable_Overflow_Interrupt();
    Timer0_OverFlow_INT_Callback(SSD_Update);
}
void SSD_Update(void)
{
    uint8_t num;
    static uint8_t idx = 0;
 
    Timer0_Set_Preload_Value(178);
    SSD_Digits_TurnOFF();
    
    num = buffer[idx];
    
    
#if S_SEG_TYPE == S_SEG_COMMON_CATHODE
    GPIO_Set_Port(S_SEG_PORT, digit[num]);
#elif S_SEG_TYPE == S_SEG_COMMON_ANODE
    GPIO_Set_Port(S_SEG_PORT, ~(digit[num]));
#endif
   
    // Turn on or off the dot for the active digit
    if(SSD_DOT_STATES & (1 << idx))
    {
        #if S_SEG_TYPE == S_SEG_COMMON_CATHODE
            GPIO_Set_Pins(SEGMENT_DOT_PORT, SEGMENT_DOT_PIN);
        #elif S_SEG_TYPE == S_SEG_COMMON_ANODE
            GPIO_Reset_Pins(SEGMENT_DOT_PORT, SEGMENT_DOT_PIN);
        #endif
    }
    
    switch (idx)
    {
        case 0:
            GPIO_Set_Pins(DISPLAY_DIGIT_1_PORT, DISPLAY_DIGIT_1_PIN);
            break;
        case 1:
            GPIO_Set_Pins(DISPLAY_DIGIT_2_PORT, DISPLAY_DIGIT_2_PIN);
            break;
        case 2:
            GPIO_Set_Pins(DISPLAY_DIGIT_3_PORT, DISPLAY_DIGIT_3_PIN);
            break;
        case 3:
            GPIO_Set_Pins(DISPLAY_DIGIT_4_PORT, DISPLAY_DIGIT_4_PIN);
            break;
    }
    
    idx++;
    if(idx > S_SEG_NR_OF_DIGITS-1)
    {
        idx = 0;
    }
}

void SSD_SetInt(int num, int8_t start_position, int8_t digits_number)
{
    uint8_t length = 0;
	uint8_t divide = 0;
	uint8_t idx = 0;
	int32_t temp_number = num;
	
	if(num == 0) length = 1;

	while(temp_number != 0)
    {
		length++;
		temp_number /= 10;
	}
	temp_number = num;
	
	digits_number -= length;
	if(digits_number < 0) digits_number = 0;
	
	if(num < 0)
    {
		temp_number = 0 - temp_number;
		idx++;
	}

	idx += length + start_position + digits_number - 2;
	divide = length + digits_number;
	
	while(divide)
    {
		if(idx < S_SEG_NR_OF_DIGITS)
        {
			buffer[idx] = temp_number % 10;
		}
		
		temp_number /= 10;
		idx--;
		divide--;
	}
}

void SSD_Digits_TurnOFF(void)
{
    GPIO_Reset_Pins(DISPLAY_DIGIT_1_PORT, DISPLAY_DIGIT_1_PIN);
    GPIO_Reset_Pins(DISPLAY_DIGIT_2_PORT, DISPLAY_DIGIT_2_PIN);
    GPIO_Reset_Pins(DISPLAY_DIGIT_3_PORT, DISPLAY_DIGIT_3_PIN);
    GPIO_Reset_Pins(DISPLAY_DIGIT_4_PORT, DISPLAY_DIGIT_4_PIN);
}

void SSD_Clear(void)
{
    for(int i=0; i<S_SEG_NR_OF_DIGITS; i++)
    {
        buffer[i] = 0;
    }
}

void SSD_DotOn(uint8_t dot_number)
{
	SSD_DOT_STATES |= 1 << (dot_number - 1);
}

void SSD_DotOff(uint8_t dot_number)
{
	SSD_DOT_STATES &= ~(1 << (dot_number - 1));
}

void SSD_Dottoggle(uint8_t dot_number)
{
    SSD_DOT_STATES ^= (1 << (dot_number - 1));
}
