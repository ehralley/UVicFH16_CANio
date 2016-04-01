/*
NEW PIN Breakdown
D2 - PD2 - Starter FET 
D3 - PD3 - N/C INTERUPT
D4 - PD4 - Clutch Fill FET
D5 - PD5 - Shift UP FET
D6 - PD6 - Shift DOWN FET
D7 - PD7 - Spare FET 1
D8 - PB0 - MS_FET
D9 - PB1 - Engine Fan FET - PWM
A0 (D14) - PC0 - RTD FET
A1 (D15) - PC1 - Brake Light FET
A3 (D17) - PC3 - Spare Relay 1 Relay
A4 (D18) - PC4 - Spare Relay 2 Relay
A5 (D19) - PC5 - FP FET 
*/

#include <SPI.h>
#include "mcp_can.h"
#include "Pin_Defines.h"
#include <TimerOne.h>

const int SPI_CS_PIN = 10;
const int fan_pin = 9;


MCP_CAN CAN(SPI_CS_PIN);

void setup()
{
  Serial.begin(115200);
  Timer1.initialize(40);  // 40 us = 25 kHz


  DDRB |= 0b00000001; //PB0 is output (PB1 is PWM set up seperately) 
  DDRC |= 0b00111011; //PC0 PC1 PC3 PC4 & PC5 are outputs 
  DDRD |= 0b11110100; //PD2 PD4 PD5 PD6 & PD7 are outputs
  
START_INIT:

  if(CAN_OK == CAN.begin(CAN_500KBPS)){
    Serial.println("CAN BUS INIT GOOD");
  }else{
    Serial.println("CAN BUS INIT FAIL, RETRY");
    delay(100);
    goto START_INIT;
  }
}

void loop()
{
  unsigned char len = 0;
  unsigned char buf[8];
    if(CAN_MSGAVAIL == CAN.checkReceive()){
      CAN.readMsgBuf(&len, buf);
      unsigned long canID = CAN.getCanId();  
      if(canID == 0x50){
        
        //Deal with IO (In order of CAN message location)  
        PORTC ^= (-((buf[0]>>CAN_0)&BIT_1_MASK)^PORTC)&(1U<<PC1); //Brake Light
        PORTC ^= (-((buf[0]>>CAN_1)&BIT_1_MASK)^PORTC)&(1U<<PC5); //FP
        
        //PORTB ^= (-((buf[0]>>CAN_2)&BIT_1_MASK)^PORTB)&(1U<<PB0); //MS
        //TEMPORARY DEBUG - Hardwire MS ON
        PORTB |= 1U<<PB0;
        
        PORTC ^= (-((buf[0]>>CAN_3)&BIT_1_MASK)^PORTC)&(1U<<PC0); //RTD
        PORTD ^= (-((buf[0]>>CAN_4)&BIT_1_MASK)^PORTD)&(1U<<PD7); //Spare 1
        PORTD ^= (-((buf[0]>>CAN_5)&BIT_1_MASK)^PORTD)&(1U<<PD2); //Starter
        PORTD ^= (-((buf[0]>>CAN_6)&BIT_1_MASK)^PORTD)&(1U<<PD5); //Shift UP
        PORTD ^= (-((buf[0]>>CAN_7)&BIT_1_MASK)^PORTD)&(1U<<PD6); //Shift DOWN        
        PORTD ^= (-((buf[1]>>CAN_0)&BIT_1_MASK)^PORTD)&(1U<<PD3); //Clutch Fill
        PORTC ^= (-((buf[1]>>CAN_1)&BIT_1_MASK)^PORTC)&(1U<<PC3); //CBRB
        PORTC ^= (-((buf[1]>>CAN_2)&BIT_1_MASK)^PORTC)&(1U<<PC4); //RBRB

        //Engine Fan - PWM 
        Timer1.pwm(fan_pin, buf[2]<<2); 
      }
    }
}
