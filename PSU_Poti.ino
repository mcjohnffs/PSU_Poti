/* @file EventSerialKeypad.pde
 || @version 1.0
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
 || #
 */
#include <Keypad.h>

#include <AD5272.h>

#include <Wire.h>

#define POT_ADDR 0x2F

// creates communication object with address 0x2E
AD5272 digital_pot(POT_ADDR);

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','A'},
    {'7','8','9','A'},
    {'*','0','#','A'}
};

byte rowPins[ROWS] = {12, 14, 27, 26}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {25, 33, 32, 35}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
byte ledPin = 13; 

boolean blink = false;
boolean ledPin_state;

char lesen;

#define I2C_SDA 21
#define I2C_SCL 22

void setup(){
  Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);              // Sets the digital pin as output.
    digitalWrite(ledPin, HIGH);           // Turn the LED on.
    ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop(){
    char key = keypad.getKey();
  if(digital_pot.init() != 0);
    Serial.println("Cannot send data to the IC.");
}

}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '#') {
  // set new value to RDAC (0~1024)
  uint16_t data = 512;
  ret = digital_pot.write_data(AD5272_RDAC_WRITE, data);
  if(ret != 0)  // check if data is sent successfully
    Serial.println("Error!");

 
        }
        break;

    case RELEASED:
        if (key == '*') {
            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
            blink = false;
        }
        break;

    case HOLD:
        if (key == '*') {
            blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
}
