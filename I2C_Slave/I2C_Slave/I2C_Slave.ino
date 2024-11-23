#include <Wire.h>

// Define I2C slave address and register array
#define I2C_SLAVE_ADDR 0x22  // Example address

#define MAX_NO_OF_SETTINGS  10


/*
 * Setting Param can be pre-defaulted to any desired value
 * 
 */
uint8_t Settings_Param[MAX_NO_OF_SETTINGS] = { 0, 10 , 20 , 30, 40, 50, 60, 70, 80, 90};
static uint8_t Param_Addres = 0;

void setup() {
  Wire.begin(I2C_SLAVE_ADDR);  // Initialize as I2C slave
  Wire.onReceive(onReceiveHandler);  // Set up receive handler
  Wire.onRequest(onRequestHandler);  // Set up request handler
  Serial.begin(115200);
  Serial.println("ESP32 I2C Slave Init");
}


void UpdateSettings(int _numberofBytes,uint8_t _setting_addr)
{
  while(_numberofBytes && (_setting_addr <= MAX_NO_OF_SETTINGS) )
  {
    Serial.printf("Looping in Update settings setting_addr : %d --- numberOfBytes %d \n", _setting_addr, _numberofBytes);
    Settings_Param[_setting_addr] = Wire.read();
    Serial.printf("Settings_Param[%d] : %d \n",_setting_addr,Settings_Param[_setting_addr]);
    _numberofBytes--;
    _setting_addr++;    
  }
}

void Template_UpdateSettings_CMD(int _numberofBytes)
{
  uint8_t settingAddress;
  if (_numberofBytes)
  {
    settingAddress = Wire.read();
    _numberofBytes--;
    if (_numberofBytes && settingAddress < MAX_NO_OF_SETTINGS)
    {
      UpdateSettings(_numberofBytes,settingAddress);
    }
  }
  
}

// Handle data received from the master
void onReceiveHandler(int numBytes) 
{
  Serial.println("Handle data received from the master");
  if (numBytes < 1)
  {
    Serial.println(" Fatal Error panic");
    return;
  }
  uint8_t cmd = Wire.read();  // First byte is the opcode
  numBytes--;
  switch (cmd)
  {
    case 0x00:
      Serial.println(" Update Settings Upcode ");
      Template_UpdateSettings_CMD(numBytes);
    break;

    case 0x01:
      Param_Addres = Wire.read();
    
    break;

    default:
      Serial.println(" Unsupported cmd panic");
    break;
  }
  Serial.println("onReceiveHandler Completed \n");
}

// Handle data requested by the master
void onRequestHandler() 
{
  if (Param_Addres < MAX_NO_OF_SETTINGS) {
    Wire.write(Settings_Param[Param_Addres]); // Send the value at the last requested register
    Serial.printf("Sending data to Master: Register Address [%d]: %d\n", Param_Addres, Settings_Param[Param_Addres]);
  } else {
    Wire.write(0xFF); // Indicate an error or invalid address
    Serial.println("Invalid register address requested");
  }
}

void loop() {
  delay(1000);
  
  // Optionally, add debugging or processing here
}
