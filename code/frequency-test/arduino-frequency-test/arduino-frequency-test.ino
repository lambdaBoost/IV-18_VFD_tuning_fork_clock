//code to test frequency of tuning fork
//to be used on an external arduino
//connect clock sqout to A2 and gnd to gnd and view result on serial monitor (9600 baud)


int dat=2;
int strobe=1;
int clk=0;

int digit1;
int digit2;
int digit3;
int digit4;
int digit5;
int digit6;

float frequency;
unsigned long frequencyScaled;

// this constant won't change:
const int  SQPin = A2;    // 
const int  buttonPin = A3;    // the pin that the pushbuttons are attached to

int SRDelayMicros = 1000; //delay between shift register inputs

// Variables will change:
unsigned long pulseCounter = 0;   //
int secs = 0;         // current time
int lastinputState = 0;     // previous state of the button
int inputState=0;


byte digit;
byte digitSelect;
unsigned long digitArray[12]; //array of segment states
unsigned long selectArray[8]; //array of digit onoff states

void setup() {

  //arrays to switch on vfd. We add the digit and digit select numbers to get final output
  //final output in form C2,C1,Af,C7,C4,C6,C9,Aa,Ab,C8,Ae,Ac,C5,Ad,C3,Adp,Ag,0,0,0
  //define arrays - binary
  digitArray[0] = 0b00000000000000000000; //segments abcdef 
  digitArray[1] = 0b00100001101101000000; //segments abcdef
  digitArray[2] = 0b00000000100100000000; //segments bc
  digitArray[3] = 0b00000001101001001000; //segments abged
  digitArray[4] = 0b00000001100101001000; //segments abgcd
  digitArray[5] = 0b00100000100100001000; //segments bcfg
  digitArray[6] = 0b00100001000101001000; //segments afgcd
  digitArray[7] = 0b00100001001101001000; //segments afgcde
  digitArray[8] = 0b00000001100100001000; //segments abcg
  digitArray[9] = 0b00100001101101001000; //segments abcdefg
  digitArray[10] = 0b00100001100101001000; //segments abcdfg
  digitArray[11] = 0b00000000000000000000; //blank all

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

  Serial.begin(9600);


}

unsigned long startTime;
unsigned long pulseTime = 0;

void loop() {

  

     
  
  //count number of pulses and get second value
  // read the CLOCK input pin:
  inputState = digitalRead(SQPin);

  // compare the buttonState to its previous state
  if (inputState != lastinputState) {
    // if the state has changed, increment the counter
    if (inputState == LOW) {
       //if the current state is HIGH then the clock went from off to on:

       if(pulseCounter == 0){
      Serial.println("starting count");
      delay(10000); //let fork 'spin up'
      startTime = millis();
       }

       else if(pulseCounter < 100000){
       
       }

       else if (pulseCounter == 100000){
        pulseTime = millis() - startTime;
        Serial.println("count done");
        frequency = 1000.0 * (100000.0 / pulseTime);

        Serial.println(frequency, 4);

       
       }

       else{

          frequency = 1000.0 * (100000.0 / pulseTime);

          Serial.println(frequency, 4);
        
       }

      pulseCounter++;
     
    }

    
  }


   

  
  // save the current state as the last state, for next time through the loop
  lastinputState = inputState;




}







void displayDigit(int digit, int posn, bool DP){


  unsigned long digitOut = digitArray[digit + 1];
  unsigned long posnOut = selectArray[posn];
  

  unsigned long selectOut = digitOut + posnOut;

  //add DP if needed
  if(DP == true){
    selectOut = selectOut + 0b00000000000000010000;
  }

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


  
