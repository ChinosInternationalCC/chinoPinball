/*
  Serial Call and Response with push button for ChinoPinBall  
  
  Created 26 March 2014 by Chinos International
  
 The circuit:
 * LED attached from pin 13 to ground
 * 3 pushbutton attached to pin 2 from +5V
 * 3 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 */

unsigned long timeMillis;
bool firstTimeEvent = true;
 
//For testing tru, false
bool bTesterArduino = false;

//LED
const int ledPin =  13;      // the number of the LED pin


//Rele
int rele1 = 5; 
int rele2 = 6; 

//Serial
int inByte = 0;         // incoming serial byte
String inputString = "";         // a string to hold incoming data

//Button
const int buttonPinL = 2;     // the number of the pushbutton LEFT LEVER
const int buttonPinR = 3;     // the number of the pushbutton RIGHT LEVER
const int buttonPinH = 4;     // the number of the pushbutton HAMMER

int typeButton = 0; //0 (LEFT) / 1 (RIGHT) / 2 (HAMMER)

int buttonStateL = 0;         // variable for reading the pushbutton status
int last_buttonStateL = 0;
int buttonStateR = 0;         // variable for reading the pushbutton status
int last_buttonStateR = 0;

int buttonStateH = 0;         // variable for reading the pushbutton status
int last_buttonStateH = 0;



//----------------------------------------

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  //Reles
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  
  //Buttons
  pinMode(buttonPinL, INPUT);   
  pinMode(buttonPinR, INPUT);   
  pinMode(buttonPinH, INPUT);   

  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output:
  
  //Leds
  setupLeds();
}

//----------------------------------------

void loop(){

  //Button Status
    // read the state of the pushbutton value:
    buttonStateL = digitalRead(buttonPinL);
    buttonStateR = digitalRead(buttonPinR);
    buttonStateH = digitalRead(buttonPinH);  
    
   if(bTesterArduino) Serial.print('buttonStateL=');
   if(bTesterArduino) Serial.println(buttonStateL);
    
 
     //LEVER
      if(last_buttonStateL != buttonStateL) {
         typeButton = 0;//0 (LEFT)
         
        //LEFT UP
        if(buttonStateL == HIGH) {
          digitalWrite(ledPin, HIGH);// turn LED on
          sendData(typeButton, buttonStateL);
        }
        //LEFT DOWN
        else {
          digitalWrite(ledPin, LOW);// turn LED off:
          sendData(typeButton, buttonStateL);   
        } 
        
        last_buttonStateL = buttonStateL;
      }
        
      //LEVER
      if(last_buttonStateR != buttonStateR) {
        
        typeButton = 1;//1 (RIGHT)
        
        //RIGHT UP
        if(buttonStateR == HIGH) {
          digitalWrite(ledPin, HIGH);// turn LED on
          sendData(typeButton, buttonStateR);
        }
        //RIGHT DOWN
        else {
          digitalWrite(ledPin, LOW);// turn LED off:
          sendData(typeButton, buttonStateR);    
        } 
        
         last_buttonStateR = buttonStateR;
      }
      
      //HAMER 
      if(last_buttonStateH != buttonStateH) {
        
        typeButton = 2;//2 (HAMMER)
        
        //HAMER UP
        if(buttonStateH == HIGH) {
          digitalWrite(ledPin, HIGH);// turn LED on
          sendData(typeButton, buttonStateH);
        }
        //HAMER DOWN
        else {
          digitalWrite(ledPin, LOW);// turn LED off:
          sendData(typeButton, buttonStateH);    
        } 
        
         last_buttonStateH = buttonStateH;
      }
    
    //LEDS
    //loopLeds();
}

//----------------------------------------
void sendData(int typeButton, int bPressed) {

  if(typeButton == 0 && bPressed == 1){
    Serial.print('L');   // send a capital A and wait for replay
    delay(5);
  }
  else if(typeButton == 0 && bPressed == 0){
    Serial.print('l');   // send a capital A and wait for replay
    delay(5);  
  }
  else if(typeButton == 1 && bPressed == 1){
    Serial.print('R');   // send a capital A and wait for replay
    delay(5); 
  }
  else if(typeButton == 1 && bPressed == 0){
    Serial.print('r');   // send a capital A and wait for replay
    delay(5); 
  }
   else if(typeButton == 2 && bPressed == 1){
    Serial.print('H');   // send a capital A and wait for replay
    delay(5); 
  }
  else if(typeButton == 2 && bPressed == 0){
    Serial.print('h');   // send a capital A and wait for replay
    delay(5); 
  }
  

}


//----------------------------------------
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  

 if(firstTimeEvent){ 
   timeMillis = millis();
   firstTimeEvent = false;
 }else {
  
    while (Serial.available()) {
      
      if (Serial.available() > 0)
      {
        int data = Serial.read();
        
        if(data == '0'){
          if(timeMillis < 200){
            digitalWrite(rele1, HIGH);   // turn the LED on (HIGH is the voltage level)
            //delay(200);               // wait for a second
          }
          else{
              digitalWrite(rele1, LOW);    // turn the LED off by making the voltage LOW
              firstTimeEvent = true;
          }
        }
        else if(data == '1'){
          if(timeMillis < 200){
            digitalWrite(rele2, HIGH);   // turn the LED on (HIGH is the voltage level)
            firstTimeEvent = true;
            //delay(200);    
          }          // wait for a second
          else {
            digitalWrite(rele2, LOW);    // turn the LED off by making the voltage LOW
            firstTimeEvent = false;
          }
        }else if(data == '2'){
          //loopLeds();   //led sequence
        }
  
      }
    }
 }//Else
}


