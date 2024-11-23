# ESP32_Project_Bundle
This Repo contains Project for ESP32.</br>
The board that I have been using : ESP32_WROOM_DA </br>
See the link for the board pin-out : https://lastminuteengineers.com/esp32-wroom-32-pinout-reference/

## I2C_Slave
This Project turns ESP32 into I2C Slave device with slave address of 0x22, you could change the address </br>
```
#define I2C_SLAVE_ADDR 0x22
```
settings parameters that are read/written to in this project is defined on to of the file.
```
/*
 * Setting Param can be pre-defaulted to any desired value
 * 
 */
uint8_t Settings_Param[MAX_NO_OF_SETTINGS] = { 0, 10 , 20 , 30, 40, 50, 60, 70, 80, 90};
```
using the following two opcodes/commands/register-address
<ol>
<li>0x00 : Write Data to Setting Parameters </li>
<li>0x01 : Read Data to Setting Parameters </li>
</ol>
Example of packet that has to be sent to ESP I2C Slave 
<ul>
<li> Write Data: [slaveAddr :0x22] [CMD : 0x00] [setting/param addr : 0 - 9][value Byte[n] : any value]
<li>Read Data: [slaveAddr :0x22] [CMD : 0x01] [setting/param addr : 0 - 9]
</ul>

### PythonScript I2C Master
I have attached a python script, where it configures I2C 1 on Rasperry PI as I2C Master, and as the script is run the user can follow the instruction to send data across to I2C Slave - this is just for the verification/test on ESP32 I2C Slave functionalities.

