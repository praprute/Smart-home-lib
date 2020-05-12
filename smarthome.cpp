#include "smarthome.h"
#include "Arduino.h"
#include "LedControl.h"
#include "DHT.h"
#include "MCP23017.h"
#include "LiquidCrystal_I2C.h"
#include <inttypes.h>
#include <SPI.h>
#include <RFID.h>

#define led_pin1 8
#define led_pin2 9
#define led_pin3 10

#define btn_pin1 11
#define btn_pin2 12
#define btn_pin3 13
#define btn_pin4 14

#define MQ2 33
#define BUZZER 27
#define SOLENOID 12
#define DOORSENSOR 13
#define LDR 35
#define PIR 14

#define RELAY1 25
#define RELAY2 26

#define WATER_LEAK 34

#define SDA_PIN 21
#define RST_PIN 22



DHT dht;
MCP23017 mcp;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
LedControl lc=LedControl(23,18,5,1);
RFID rfid(SDA_PIN, RST_PIN); 
//23 MOSI 18CLK 5CS

int led_pin[3] = {led_pin1,led_pin2,led_pin3};
int btn_pin[4] = {btn_pin1, btn_pin2, btn_pin3, btn_pin4};
int relay[2]   = {RELAY1, RELAY2};

void smarthome::init()
{
    Serial.begin(9600);
    pinMode(RELAY1, OUTPUT); 
    pinMode(RELAY2, OUTPUT);
    dht.setup(32);
    mcp.begin();
    lcd.begin();
    lcd.backlight();
    SPI.begin(); 
    rfid.init();
}

void smarthome::rfidHalt()
{
    rfid.halt();
}

unsigned char smarthome::serNum(int position)
{
    return rfid.serNum[position];
}

bool smarthome::isCard()
{
    return rfid.isCard();
}

bool smarthome::readCardSerial()
{
    return rfid.readCardSerial();
}

// getter
bool getON(char state[])
{
    if (state == "ON")
    {
        return true;
    }
      return false;
}

void smarthome::setRelay(int pin, char state[])
{
    digitalWrite(relay[pin-1],getON(state));
}

float smarthome::getWater()
{
    float water = analogRead(WATER_LEAK);
    return water;
}

bool smarthome::getMovement()
{
    int pir = digitalRead(PIR);
    if (pir == HIGH)
    {
        return true;
    }else
    {
        return false;
    }
}


float smarthome::getLight()
{
    float light = analogRead(LDR);
    return light;
}

bool smarthome::setDoorSeneor()
{
    int state;
    state = digitalRead(DOORSENSOR);
    if (state == HIGH)
    {
        return true;
    }else
    {
        return false;
    }
}

void smarthome::setLCD(int x, int y, const char c[])
{
    lcd.setCursor(x, y);
    lcd.print(c);
}

void smarthome::ClearText()
{
    lcd.clear();
}

float smarthome::getSmoke()
{
    float mq = analogRead(MQ2);
    return mq;
}

float smarthome::getTemp()
{
    return dht.getTemperature();
}

float smarthome::getHumit()
{
    return dht.getHumidity();
}

bool smarthome::getSwitch(int pin)
{
    mcp.pinMode(btn_pin[pin-1], INPUT);
if (mcp.digitalRead(btn_pin[pin-1]) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void smarthome::setLED(int pin, char state[])
{
    // mcp.pinMode(pin, OUTPUT);
    // Serial.println(getON(state));
    mcp.digitalWrite(led_pin[pin - 1], getON(state));
}

void smarthome::setBuzzer(char state[])
{
    digitalWrite(BUZZER ,getON(state));
}

void smarthome::setSolenoid(char state[])
{
    digitalWrite(SOLENOID ,getON(state));
}







// bool smarthome::mcpDigitalRead(int pin){
//     mcp.pinMode(pin, INPUT);
//     if(mcp.digitalRead(pin) == 0){
//         return true;
//     }else
//     {
//         return false;
//     }
//     Serial.println(mcp.digitalRead(pin));
// }

// void smarthome::mcpDigitalWrite(){
//     if(mcp.digitalRead(8) == 1){
//         mcp.digitalWrite(15, 0);
//     }else if(mcp.digitalRead(8) == 0)
//     {
//         mcp.digitalWrite(15, 1);
//     }
// }

// bool smarthome::BtnDigitalRead(int pin)
// {
//     mcp.pinMode(pin, INPUT);
//     if (mcp.digitalRead(pin) == 0)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
//}