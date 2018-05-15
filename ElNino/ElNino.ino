int led = 5;           // LED pinouts
int led2 = 6;
int led3 = 9;          
int led4 = 10;
int led5 = 11;
int butt = 7;          // button pin in
int pot = 2;           // potentiometer analog in 
int brightness = 100;  // how bright the LED is
int fadeAmount = 0;    // how many points to fade the LED by
int buttint = 0;       // button variable. Selects which lighting program to run in. 
int randnumb = 0;      // random number for the burst light program.
int potter = 0;        // analogRead(pot) / 50 . Scales the input for a reasonable range of random blinks. 
int invert = 0;        // Inversion variable for the fade program. Switches from "brightness + fadeAmount" to "brightness - fadeAmount"

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(butt, INPUT_PULLUP); //sets button input with an internal pullup resistor. Sets default state to HIGH, button press == LOW.
  randomSeed(analogRead(0));   // seed number for the random number generator. Uses the white noise from analog input pin 0. 
  
  Serial.begin(9600);
  while (! Serial);

}

void loop() {
  // the loop routine runs over and over again forever:
  if (buttint == 0 ) {
    analogWrite(led, 0); // turns off the LEDs
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
    analogWrite(led5, 0);
  }
  
  while (digitalRead(butt) == LOW ) {
    if (buttint < 2)
    {  
      buttint = buttint + 1;   // iterates buttint, to move to the next lighting program.    
    }
    delay(500); // prevents the button from registering more than one button press. 
  }

     //    BRIGHTNESS LOOP

    while (buttint == 1){
      analogWrite(led, brightness); // analogWrite sets the pins to use PWM to control LED brightness. Values can range from 0 - 255. 
      analogWrite(led2, brightness);
      analogWrite(led3, brightness);
      analogWrite(led4, brightness);
      analogWrite(led5, brightness);
      brightness = analogRead(pot) / 4;
      Serial.println("buttint = 1");
      while (digitalRead(butt) == LOW) {
        buttint = 2;
        delay(500);
      }
    }

   // FADE LOOP
  
   while (buttint == 2) {       
    // set the brightness of LEDs:
    analogWrite(led, brightness);
    analogWrite(led2, brightness);
    analogWrite(led3, brightness);
    analogWrite(led4, brightness);
    analogWrite(led5, brightness);
    fadeAmount = analogRead(pot) / 10;
    Serial.print("buttint = 2 : ");
    Serial.println(analogRead(pot) / 10);
      
      while (digitalRead(butt) == LOW) {
          buttint = 3;
          delay(500);
        }
      
      if (invert == 0){ // increases brightness
        brightness = brightness + fadeAmount;
        if (brightness >= 255){ 
          brightness = 255; // prevents brightness from being set to a value > 255
          invert = 1;
        }
      }
      if (invert == 1){ // decreases brightness
        brightness = brightness - fadeAmount;
        if (brightness <= 0){
          brightness = 0;
          invert = 0;
        }
      }
    
    // Sets the delay time between each individual fade 
    delay(30);
    }

    // RANDOM BURST LOOP

    while (buttint == 3){
      randnumb = random(0,10000);
      potter = analogRead(pot);
      digitalWrite(led, LOW) ;
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      
      if (digitalRead(butt) == LOW){
        buttint = 0;
        delay(500);  
      }

      if (0 < randnumb && randnumb < (1 + potter)){ // if randnumb falls between the two noted values, the LED will fire. 
        digitalWrite(led, HIGH);
        delay(50);
      }

      if (2000 < randnumb && randnumb < (2001 + potter)){
        digitalWrite(led2, HIGH);
        delay(50);
      }

      if (4000 < randnumb && randnumb < (4001 + potter)){
        digitalWrite(led3, HIGH);
        delay(50);
      }

      if (6000 < randnumb && randnumb < (6001 + potter)){
        digitalWrite(led4, HIGH);
        delay(50);
      }

      if (8000 < randnumb && randnumb < (8001 + potter)){
        digitalWrite(led5, HIGH);
        delay(50);
      } 

      Serial.print("buttint = 3 : ");
      Serial.println(analogRead(pot) / 20);
    }

}

