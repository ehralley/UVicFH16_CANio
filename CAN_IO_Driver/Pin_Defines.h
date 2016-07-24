/*
NEW PIN Breakdown
D2 - PD2 - Starter FET 
D3 - PD3 - N/C INTERUPT !!!
D4 - PD4 - Clutch Fill FET !!!
D5 - PD5 - Shift UP FET !!!
D6 - PD6 - Shift DOWN FET !!!
D7 - PD7 - Spare FET 1
D8 - PB0 - MS_FET
D9 - PB1 - Engine Fan FET - PWM
A0 (D14) - PC0 - RTD FET
A1 (D15) - PC1 - Brake Light FET
A3 (D17) - PC3 - Spare Relay 1 Relay
A4 (D18) - PC4 - Spare Relay 2 Relay
A5 (D19) - PC5 - FP FET 
*/

#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PB0 0
#define PB1 1

#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5 

#define CAN_0 0
#define CAN_1 1
#define CAN_2 2
#define CAN_3 3
#define CAN_4 4
#define CAN_5 5
#define CAN_6 6
#define CAN_7 7

#define BIT_1_MASK 0x1
#define BIT_2_MASK 0x2
#define BIT_3_MASK 0x4
#define BIT_4_MASK 0x8
#define BIT_5_MASK 0x10
#define BIT_6_MASK 0x20
#define BIT_7_MASK 0x40
#define BIT_8_MASK 0x80
