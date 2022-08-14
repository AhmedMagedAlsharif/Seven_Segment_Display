/*
 * File:   main.c
 * Author: ahmed
 *
 * Created on May 16, 2022, 10:27 AM
 */


#include "main.h"

int main(void)
{
    SSD_Init();
    sei();
    
    
    while(1)
    {
        for(int i = 0; i<100; i++)
        {
            SSD_SetInt(i, 3,2);
            SSD_Dottoggle(2);
            _delay_ms(500);
            
        }
        
    }
    return 0;
}
