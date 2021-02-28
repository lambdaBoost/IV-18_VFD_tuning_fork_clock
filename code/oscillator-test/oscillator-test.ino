/*
Arduino Test to check the oscillator is working by printing to serial every 440 pulses
connect output from 555 to pin 2 on arduino
*/

// this constant won't change:
const int  CLKPin = 2;    // the pin that the pushbutton is attached to


// Variables will change:
int pulseCounter = 0;   // counter for the number of button presses
int secs = 0;         // current time
int lastinputState = 0;     // previous state of the button
int inputState=0;

void setup() {
  // initialize the button pin as a input:
  pinMode(CLKPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the CLOCK input pin:
  inputState = digitalRead(CLKPin);

  // compare the buttonState to its previous state
  if (inputState != lastinputState) {
    // if the state has changed, increment the counter
    if (inputState == HIGH) {
      // if the current state is HIGH then the clock went from off to on:
      pulseCounter++;

      // increase second count every 440 pulses
      if (pulseCounter % 440 == 0) {
        pulseCounter = 0; //TODO - should this actually be 1
        secs++;
        if(secs >= 60){
          secs=0;
        }
        Serial.println(secs);
  } 
      
    }
  }

  // save the current state as the last state, for next time through the loop
  lastinputState = inputState;




}
