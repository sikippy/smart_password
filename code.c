#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <stdlib.h>

#define redLed 27
#define greenLed 26

LiquidCrystal_I2C lcd(0x27,16,2);

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 2, 15 }; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 14, 12, 19, 18 }; // Pins connected to R1, R2, R3, R4

char passStr1[5];
String passStr;
int i =2;
int counter = 0;
int pass =0;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  i = 1;
  counter = 0;
  passStr="";
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(i,0);
  lcd.print("Input Password");
  pass = random(10000);
  Serial.println("Random pass :");
  Serial.println(pass);
}

void setOnOff(int pin,int onOff, int delayTime){
  digitalWrite(pin, onOff);
  delayMicroseconds(delayTime);
}
 
void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if(key=='#'){
      lcd.clear();
      setup();
    }
    else{
      setOnOff(greenLed,LOW,10);
      setOnOff(redLed,LOW,10);
      lcd.setCursor(i++,1);
      lcd.print('*');
      counter++;
      passStr +=key;
      if(counter==sprintf(passStr1, "%d", pass)){
        const char* string1 = passStr.c_str();
         atoi(string1)==atoi(passStr1)?setOnOff(greenLed,HIGH,10):setOnOff(redLed,HIGH,10);
      }    
      else{
        setOnOff(redLed,HIGH,10);
      }
    }
  }
}



