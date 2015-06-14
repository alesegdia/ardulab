/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

#define LED_PIN 13

void setup_led() {
  pinMode(LED_PIN, OUTPUT);
}

void led_on() {
  digitalWrite(LED_PIN, HIGH);
}

void led_off() {
  digitalWrite(LED_PIN, LOW);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  setup_led();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Hello world!");  // prints hello with ending line break 
}

void parse_token(char* token) {
  Serial.print("token: ");
  Serial.println(token);
}

#define INPUT_SIZE 30

// the loop function runs over and over again forever
void loop() {
  led_off();
  if( Serial.available() > 0 ) {
    
    // init input buffer
    char input[INPUT_SIZE+1];
    byte size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = 0;

    // get first token
    char* command = strtok(input, " ");
    while( command != 0 ) {

      // process token
      parse_token(command);
      
      // get next token
      command = strtok(0, " ");
    }
    
    led_on();
  }
}
