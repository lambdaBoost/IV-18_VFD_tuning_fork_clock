int dat=2;
int strobe=1;
int clk=0;

void setup() {
  pinMode(dat, OUTPUT);
  pinMode(strobe, OUTPUT);
  pinMode(clk, OUTPUT);

  digitalWrite (dat, 0);
  digitalWrite (strobe, 0);
  digitalWrite (clk, 0);

}

void loop() {
  // put your main code here, to run repeatedly:
     for (int i = 19; i >= 0; i--)
   {
       digitalWrite(dat, 1);
       digitalWrite(clk, HIGH);
       delay (1);
       digitalWrite(clk, LOW);
       delay (1);      
   }
   // Turn on the outputs
   digitalWrite(strobe, HIGH);
   delay (1);
   digitalWrite(strobe, LOW);  
}
