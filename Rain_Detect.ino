 #include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 7, 9);
#include <TimerOne.h>
int inPin = 2;
int pcount = 0;
int timer = 0;
bool state = 0;
byte tcount = 0;
int darray[5];
byte i = 0;
byte j = 0;
int total = 0;
int average = 0;
int arraySize = 5;
byte rainLevel = 0;
void setup(){
lcd.begin(16, 2);
attachInterrupt(digitalPinToInterrupt (inPin), countFallingPluse, FALLING);
pinMode(13,OUTPUT);
TCCR0A =(1<<WGM01); //Set the CTC mode
OCR0A=0xF9; //Value for ORC0A for 1ms
TIMSK0|=(1<<OCIE0A); //Set the interrupt request
sei(); //Enable interrupt
TCCR0B|=(1<<CS01); //Set the prescale 1/64 clock
TCCR0B|=(1<<CS00);
lcd.setCursor(0, 0);
lcd.print("Counting. . .");
}
void countFallingPluse()
{
pcount = pcount + 1;
}
 

void loop(){
//in this way you can count 1 second because the interrupt request is each 1ms
digitalWrite(13,state);
if (i >= 4){
i = 0;
total = 0;
for (j = 0; j < 5; j++){
total = total + darray[j];
}
average = total / 5;
if (average == 0)
rainLevel = 0;
else if (average > 0 && average <= 5)
rainLevel = 1;
else if (average > 5 && average <= 10)
rainLevel = 2;
else if (average > 10 && average <= 20)
rainLevel = 3;
else
rainLevel = 4;
lcddata();
for (j = 0; j < 5; j++){
darray[j] = 0;
}
}
}
ISR(TIMER0_COMPA_vect){ //This is the interrupt request
timer++;
if(timer >= 1000){
state =! state;
timer = 0;
tcount = tcount + 1;
 

}
if (tcount >= 5) {
tcount = 0;
darray[i] = pcount;
pcount = 0;
i++; }}
void lcddata(){
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(darray[0]);
lcd.print(':');
lcd.print(darray[1]);
lcd.print(':');
lcd.print(darray[2]);
lcd.print(':');
lcd.print(darray[3]);
lcd.print(':');
lcd.print(darray[4]);
lcd.setCursor(1, 1);
lcd.print(total);
lcd.setCursor(5, 1);
lcd.print(average);
lcd.setCursor(8, 1);
switch(rainLevel){
case 0:
lcd.print("No Rain");
break;
case 1:
lcd.print("Low Rain");
break;
case 2:
lcd.print("Med Rain");
break;
case 3:
 
