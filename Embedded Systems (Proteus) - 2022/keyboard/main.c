#include <REGX52.H>

unsigned char code Tab[]={0x7F,0xBF,0xDF,0xEF};
unsigned char data ind;
unsigned char bdata Key;
bit Enable;
sbit Key_1 = Key^1;
sbit Key_2 = Key^2;
sbit Key_3 = Key^3;
int speed = 40;
int isOff = 1;
int default_speed = 40;
int number_pressed = 0;


void Send(unsigned char Value)
{
  P3_4 = 1;
    TI = 0;
    SBUF = Value;
    while(TI==0){;}
  P3_4 = 0;
}

void Setup(void)
{
  P3_4 = 0;
  Enable = 1;
  ind=0;
  SCON = 0x50;
  T2CON = 0x30;
  TH2 = RCAP2H = 0xFF;
  TL2 = RCAP2L = 0xDC;
  TR2 = 1;
}

void wait(void)
{
  unsigned char data x,y;
  for(x=0;x<=speed;x++)
    for(y=0;y<=speed;y++){;}
}


void MakeLights(int count){
  int i;
	for (i = 1; i <= count; ++i)
  {
    P0_0 = 0;
		wait();
		P0_0 = 1;
		wait();
  }
}

int OnOffLed(){
	if (isOff){
			isOff = 0;
		  return 0;
	}else{
		isOff = 1;
		return 1;
	}
}

void UpdateSpeed(){
	speed = number_pressed * 10;
}

void ResetSpeed(){
	speed = default_speed;
}





void main(void)
{
  unsigned char data Record[]={0x00,0x00,0x00};
  unsigned char index=0;
  
  Setup(); 
  while(1)
  {
    P2 = Tab[ind];
    Key = P2;
    if((Key_1 & Key_2 & Key_3)==0)
     {
       if(Enable==1)
       {
				switch(Key){
					case 0xE7:
						Send('1');
						MakeLights(1);
						number_pressed = 1;
						break;
					case 0xEB:
						Send('2');
						MakeLights(2);
						number_pressed = 2;
						break;
					case 0xED:
						Send('3');
						MakeLights(3);
						number_pressed = 3;
						break;
					case 0xD7:
						Send('4');
						MakeLights(4);
						number_pressed = 4;
						break;
					case 0xDB:
						Send('5');
						MakeLights(5);
						number_pressed = 5;
						break;
					case 0xDD:
						Send('6');
						MakeLights(6);
						number_pressed = 6;
						break;
					case 0xB7:
						Send('7');
						MakeLights(7);
						number_pressed = 7;
						break;
					case 0xBB:
						Send('8');
						MakeLights(8);
						number_pressed = 8;
						break;
					case 0xBD:
						Send('9');
						MakeLights(9);
						number_pressed = 9;
						break;
					case 0x77:
						Send('*');
						UpdateSpeed();
						break;
					case 0x7B:
						Send('0');
						P0_0 = OnOffLed();
						break;
					case 0x7D:
						Send('#');
						ResetSpeed();
						break;
				}
         Enable = 1; 
       }   
     }
    else
     {      
       if(ind<0x03) {ind++;} else{ind=0x00;}
       Enable = 1;
     }  
  }
}