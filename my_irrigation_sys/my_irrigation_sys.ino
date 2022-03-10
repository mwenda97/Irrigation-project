#include <Wire.h>
#include <DS3231.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

DS3231 rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Time t;
int relay = 3;
char mode;
char prnt, M1, M2;
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
byte rowPins[ROWS] = {8, 7, 6, 5};
byte colPins[COLS] = {12, 11, 10, 9};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
byte thermometer_symbol[8] = {
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};

void setup()
{
  rtc.begin();
  Serial.begin(9600);
  mode = EEPROM.read(0);
  pinMode(relay, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(1, thermometer_symbol);
  lcd.setCursor(0, 0);
  lcd.print ("         ");
  lcd.setCursor(0, 1);
  lcd.print ("         ");
}

void loop() {
  keypressed();
  t = rtc.getTime();


  lcd.setCursor(0, 0);
  lcd.print(rtc.getDOWStr());
  // lcd.print(" ");
  lcd.print(t.dow);
  lcd.write(1);
  lcd.print(rtc.getTemp());
  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr());
  lcd.print(":");
  //lcd.print(t.dow);
  lcd.print(":");
  //lcd.print(prnt);
  if (mode == 0) {
    lcd.print("MODE1");
  }
  if (mode == 1) {
    lcd.print("MODE2");
  }
  if (mode == 2) {
    lcd.print("MODE3");
  }
  if (mode == 3) {
    lcd.print("MODE4");
  }
  if (mode == 4) {
    lcd.print("MODE5");
  }
  digitalWrite(relay, HIGH);
  if (t.dow == 5) {
    switmode();
  }

}
void switmode() {

  switch (mode) {
    case 0:
      if (t.sec == 20 ||  t.sec == 50 ) {

        digitalWrite(relay, LOW);
        delay(1000);
      }
      if (t.sec == 30) {
        digitalWrite(relay, LOW);
        delay(2000);
      }



      break;
    case 1:

      if (t.sec == 20 ||  t.sec == 50 ) {

        digitalWrite(relay, LOW);
        delay(1000);
      }
      if (t.sec == 30) {
        digitalWrite(relay, LOW);
        delay(2000);
      }
      break;
    case 2:
      if (t.sec == 20 ||  t.sec == 50 ) {

        //digitalWrite(relay, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("mode 3 is running");
        delay(2000);
        lcd.clear();
        delay(1000);
      }
      break;
    case 3:
      if (t.sec == 20 ||  t.sec == 50 ) {

        digitalWrite(relay, LOW);
        delay(1000);
      }
      break;

      break;
    case 4:
      digitalWrite(relay, HIGH);
  }

}

void keypressed() {
  char Key = customKeypad.getKey();

  if (Key) {
    Serial.println(Key);
  }
  if (Key == 'A') {
    mode = 0;
    EEPROM.update(0, mode);

  }
  if (Key == 'B') {
    mode = 1;
    EEPROM.update(0, mode);

  }
  if (Key == 'C') {
    mode = 2;
    EEPROM.update(0, mode);

  }

  if (Key == 'D') {
    mode = 3;
    EEPROM.update(0, mode);
  }
  if (Key == '#') {
    mode = 4;
    EEPROM.update(0, mode);
  }


}
