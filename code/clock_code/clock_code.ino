//for use on attiny85
//IMPORTANT - use 16MHz internal clock. Wouldn;t have thought this would make a difference but it absolutely does!


int dat=2;
int strobe=1;
int clk=0;

// this constant won't change:
const int  SQPin = A2;    // the pin that the pushbutton is attached to

int SRDelayMicros = 1000; //delay between shift register inputs

// Variables will change:
int pulseCounter = 0;   // counter for the number of button presses
int secs = 0;         // current time
int lastinputState = 0;     // previous state of the button
int inputState=0;


byte digit;
byte digitSelect;
unsigned long digitArray[11]; //array of segment states
unsigned long selectArray[8]; //array of digit onoff states

void setup() {

  //arrays to switch on vfd. We add the digit and digit select numbers to get final output
  //final output in form C2,C1,Af,C7,C4,C6,C9,Aa,Ab,C8,Ae,Ac,C5,Ad,C3,Adp,Ag,0,0,0
  //define arrays - binary 
  digitArray[0] = 0b00100001101101000000; //segments abcdef
  digitArray[1] = 0b00000000100100000000; //segments bc
  digitArray[2] = 0b00000001101001001000; //segments abged
  digitArray[3] = 0b00000001100101001000; //segments abgcd
  digitArray[4] = 0b00100000100100001000; //segments bcfg
  digitArray[5] = 0b00100001000101001000; //segments afgcd
  digitArray[6] = 0b00100001001101001000; //segments afgcde
  digitArray[7] = 0b00000001100100001000; //segments abcg
  digitArray[8] = 0b00100001101101001000; //segments abcdefg
  digitArray[9] = 0b00100001100101001000; //segments abcdfg
  digitArray[10] = 0b00000000000000000000; //blank all

  //digit selects. In the order 1-9 going right to left
  selectArray[0] = 0b00000000000000000000;//all off
  selectArray[1] = 0b01000000000000000000;//C1
  selectArray[2] = 0b10000000000000000000;//C2
  selectArray[3] = 0b00000000000000100000;//C3
  selectArray[4] = 0b00001000000000000000;//C4
  selectArray[5] = 0b00000000000010000000;//C5
  selectArray[6] = 0b00000100000000000000;//C6
  selectArray[7] = 0b00010000000000000000;//C7
  selectArray[8] = 0b00000000010000000000;//C8


  
  pinMode(dat, OUTPUT);
  pinMode(strobe, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(SQPin, INPUT); 

  digitalWrite (dat, 0);
  digitalWrite (strobe, 0);
  digitalWrite (clk, 0);

}


void loop() {

  
  //count number of pulses and get second value
  // read the CLOCK input pin:
  inputState = digitalRead(SQPin);

  // compare the buttonState to its previous state
  if (inputState != lastinputState) {
    // if the state has changed, increment the counter
    if (inputState == LOW) {
       //if the current state is HIGH then the clock went from off to on:
      pulseCounter++;

      int digit1 = (secs/100)%10;
      int digit2 = (secs/10) %10;
      int digit3 = secs %10;
  
      displayDigit(digit1,5);
      displayDigit(digit2,4);
      displayDigit(digit3,3);
      displayDigit(0,0);//blank all

    }
  }

 // increase second count every 440 pulses
  if (pulseCounter >=440) {
        pulseCounter = 0; //TODO - should this actually be 1
        secs++;
        if(secs >= 60){
          secs=0;
        }

  } 

  
  // save the current state as the last state, for next time through the loop
  lastinputState = inputState;



}







void displayDigit(int digit, int posn){


  unsigned long digitOut = digitArray[digit];
  unsigned long posnOut = selectArray[posn];
  
    //assignments in the order C2,C1,Af,C7,C4,C6,C9,Aa,Ab,C8,Ae,Ac,C5,Ad,C3,C8,Adp,Ag,0,0
  unsigned long selectOut = digitOut + posnOut;

  // write time to VFD

    //write position
     for (int i = 19; i >= 0; i--)
   {
    int datOut = bitRead(selectOut,i);
       digitalWrite(dat, datOut);
       digitalWrite(clk, HIGH);
       delayMicroseconds(4);
       digitalWrite(clk, LOW);
       delayMicroseconds(4);     
   }

     
   // Turn on the outputs
   digitalWrite(strobe, HIGH);
   delayMicroseconds(4);
   digitalWrite(strobe, LOW);  

}


  