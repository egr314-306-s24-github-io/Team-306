#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/eusart2.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/spi2.h"

#define TC74_I2C_SLAVE_ADDR 0x4C
#define ZERO 0x00

uint8_t fwd = 0b11101111;
uint8_t bckwd = 0b11101101;
uint8_t stop = 0b11101100;
uint8_t data;


uint8_t temp_value = 0;

/*
                         Main application
 */
void main(void)
{

        SYSTEM_Initialize();     
        EUSART1_Initialize();
        EUSART2_Initialize();
        I2C1_Initialize();
        SPI2_Initialize();

        SPI2_Open(SPI2_DEFAULT);
      
        

    INTERRUPT_GlobalInterruptEnable();

    INTERRUPT_PeripheralInterruptEnable();
    
   
    int i = 0 ; 

    float temp_run;
    
    while(1)
    {

       temp_value = I2C1_Read1ByteRegister(TC74_I2C_SLAVE_ADDR,ZERO );       
          // if the user value is higher or equal t temperature sensor value
          if (temp_value >= 28 ){
        IO_RB4_SetLow();
        //declare the data 
        data = SPI2_ExchangeByte(fwd);

        IO_RB4_SetHigh();
        IO_RA1_SetHigh();
        IO_RA0_SetHigh();  

        __delay_ms(1000);
         }
           else{
        IO_RB4_SetLow();
        //declare the data 
        data = SPI2_ExchangeByte(stop);

        IO_RB4_SetHigh();
        IO_RA1_SetLow();
        IO_RA0_SetLow();  
         }
       
       
       if (i < 100)
       {
          i++;
          temp_run = i/10;
 
          printf("The temperature now = %d \r",temp_value);
       }
       else
       {
           i =0;
       }
       }
        
}