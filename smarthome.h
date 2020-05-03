class smarthome{
    public:
        
        void init();
        float getTemp();
        float getHumit();
        // bool mcpDigitalRead(int pin);
        //bool BtnDigitalRead(int pin);

        bool ReadSwitch(int pin);
        void LED(int pin, char[]);
        void ShowLCD(int x, int y, const char[]);
        void ClearText();
        float DetectedSmoke();
        void ActiveBuzzer(char state[]);
        void SolenoidON(char state[]);

};
//DHT
//MCP
//MQ
//LED*4
