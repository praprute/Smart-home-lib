#include "smarthome.h"
#include "Arduino.h"
#include "DHT.h"
#include "MCP23017.h"
#include "LiquidCrystal_I2C.h"
#include <inttypes.h>

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


DHT dht;
MCP23017 mcp;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int led_pin[3] = {led_pin1,led_pin2,led_pin3};
int btn_pin[4] = {btn_pin1, btn_pin2, btn_pin3, btn_pin4};

void smarthome::init()
{
    Serial.begin(9600);
    dht.setup(32);
    mcp.begin();
    lcd.begin();
    lcd.backlight();
    // mcp.pinMode(8, OUTPUT);
    // mcp.pinMode(15, INPUT);
    // mcp.pullUp(15, HIGH);
}


// getter
bool getON(char state[]){
    if (state == "ON")
    {
        return true;
    }
      return false;
}

void smarthome::ShowLCD(int x, int y, const char c[])
{
    lcd.setCursor(x, y);
    lcd.print(c);
}

void smarthome::ClearText(){
    lcd.clear();
}

float smarthome::DetectedSmoke(){
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

bool smarthome::ReadSwitch(int pin){
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

void smarthome::LED(int pin, char state[])
{
    // mcp.pinMode(pin, OUTPUT);
    // Serial.println(getON(state));
    mcp.digitalWrite(led_pin[pin - 1], getON(state));
}

void smarthome::ActiveBuzzer(char state[]){
    digitalWrite(BUZZER ,getON(state))
}
void smarthome::SolenoidON(char state[]){
    digitalWrite(BUZZER ,getON(state))
}

void





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