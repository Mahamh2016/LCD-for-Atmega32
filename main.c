#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

#define LCD PORTA
#define EN 7
#define RS 5
#define RW 6

void LcdCmd(unsigned char cmd){
PORTD &=~(1<<RS);   //RS =0 to accept a command mood
PORTD &=~(1<<RW);   //RW=0 to write on Lcd mood
LCD=cmd&0xF0;       //to send the upper nibble because this LCD is 4 bit mood

//the next 3 lines workes as a clock pulse of 1ms duration to enable the lcd
PORTD|=(1<<EN);
_delay_ms(1);
PORTD &=~(1<<EN);

LCD=cmd<<4;         //to send the lower nibble bec. we are on 4 bit mood at a time 

//the next 3 lines workes as a clock pulse of 1ms duration to enable the lcd
PORTD|=(1<<EN);
_delay_ms(1);
PORTD &=~(1<<EN);

}


void LcdData(unsigned char data){
PORTD |=(1<<RS);   //RS =1 to accept a data mood
PORTD &=~(1<<RW);   //RW=0 to write on Lcd mood
LCD= data & 0xF0;       //to send the upper nibble because this LCD is 4 bit mood

//the next 3 lines workes as a clock pulse of 1ms duration to enable the lcd
PORTD|=(1<<EN);
_delay_ms(1);
PORTD &=~(1<<EN);

LCD=data <<4;         //to send the lower nibble bec. we are on 4 bit mood at a time 

//the next 3 lines workes as a clock pulse of 1ms duration to enable the lcd
PORTD|=(1<<EN);
_delay_ms(1);
PORTD &=~(1<<EN);

}


void Lcd_init(){
  DDRA=0xff;
  DDRD=0xff;
  PORTD &=~(1<<EN);    //to make sure that the clock lines in the data function and cmd function will work right as it needs to be off at first

//the next 3 lines activate the 4 bit mood
  LcdCmd(0x33);
  LcdCmd(0x32);
  LcdCmd(0x28);

  LcdCmd(0x0E);        //to turn on display and cursor on
  LcdCmd(0x01);        // to clear lcd
  _delay_ms(2);
}



//function to deal with string
void lcd_print(char *str){
  unsigned char i=0;
  while(str[i]!=0)//if the string is not null (finished)
  {

    LcdData(str[i]);//display the data
    i++;// to display next char in the string
  }
}





void main(void){
  Lcd_init();
  lcd_print("Hello World");
  while(1);
  
}