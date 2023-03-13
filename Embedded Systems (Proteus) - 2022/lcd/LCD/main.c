#include <REGX52.H>

extern void LcdInit();
extern void LcdWelcome();
extern void Lcd_Cursor (char row, char column);
extern void Lcd_DisplayCharacter (char a_char);
extern void Lcd_DisplayString (char row, char column, char *string);
extern void Lcd_WriteControl (unsigned char LcdCommand);

unsigned char data Var1, Var2, Var3;
volatile unsigned char data Bufor[] = {" Received:      "};

void ISR_Serial(void) interrupt 4
  {
    if(RI ==1)
     {
       Lcd_Cursor (3,12);
       Lcd_DisplayCharacter (SBUF);
       Lcd_WriteControl(0x0C);
       RI = 0;
     }
  }

void Init(void)
  {
    SCON = 0x50;
    TH2 = RCAP2H = 0xFF;
    TL2 = RCAP2L = 0xDC;
    T2CON = 0x30;
    TR2 = 1;
    P3_4 = 0;
   
    EX0 = 1;
    IT0 = 1;
    ES  = 1;
    EA  = 1;
  }

void main(void){
  Init();
  LcdInit();
  LcdWelcome();
  Lcd_DisplayString (3,1,Bufor);
  while(1) {;}
}