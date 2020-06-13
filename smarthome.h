#include <string>

class smarthome

{

public:

    void  sminit();
    float getTemp();
    float getHumit();
    float getSmoke();
    float getLight();
    float getWater();

    bool  getSwitch(int pin);
    bool  setDoorSeneor();
    bool  getMovement();

    void setLED(int pin, char[]);
    void setLCD(int x, int y, const char[]);
    void ClearText();
    void setBuzzer(char state[]);
    void setSolenoid(char state[]);
    void setRelay(int pin, char state[]);

    bool getCard();
    uint32_t readKeyCard();

};
