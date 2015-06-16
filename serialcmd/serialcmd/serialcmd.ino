
#include <EEPROM.h>

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

void error() {
  Serial.println("error!");
}

void process_read(char** tokens) {
  byte where = atoi(tokens[1]);
  EEPROM.read(where);
  Serial.print("Value at ");
  Serial.print(where);
  Serial.print(" is ");
  Serial.println(EEPROM.read(where));
}

void process_write(char** tokens) {
  byte where = atoi(tokens[1]);
  byte what = atoi(tokens[2]);
  EEPROM.write(where, what);
  Serial.print("Successful write of ");
  Serial.print(what);
  Serial.print(" at ");
  Serial.println(where);
}

void parse_command(char** tokens, int num_tokens) {
  if( num_tokens > 0 ) {
    if( strcmp(tokens[0], "read") == 0 ) {
      if( num_tokens == 2 ) {
        process_read(tokens);
      } else {
        error();
      }
    } else if( strcmp(tokens[0], "write") == 0 ) {
      if( num_tokens == 3 ) {
        process_write(tokens);
      } else {
        error();
      }
    }
  }
}

#define INPUT_SIZE 30
char input[INPUT_SIZE+1];

// the loop function runs over and over again forever
void loop() {
  led_off();
  if( Serial.available() > 0 ) {
    byte size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = 0;

    // get first token
    char* command = strtok(input, " ");
    char* tokens[10];
    int i = 0;
    while( command != 0 && i < 10 ) {
      tokens[i] = command;
      command = strtok(0, " ");
      i++;
    }
    
    parse_command(tokens, i);
    led_on();
  }
}
