#include <Wire.h>

// Define I2C slave address and register array
#define I2C_SLAVE_ADDR 0x22  // Example address
#define NUM_REGISTERS 10

uint8_t registers[NUM_REGISTERS] = {0};  // Predefined registers
uint8_t currentRegister = 0;            // Pointer to the current register

void setup() {
  Wire.begin(I2C_SLAVE_ADDR);  // Initialize as I2C slave
  Wire.onReceive(onReceiveHandler);  // Set up receive handler
  Wire.onRequest(onRequestHandler);  // Set up request handler
  Serial.begin(115200);
  Serial.println("ESP32 I2C Slave Init");
}

// Handle data received from the master
void onReceiveHandler(int numBytes) {
  Serial.println("Handle data received from the master");
  if (numBytes < 1) return;

  uint8_t opcode = Wire.read();  // First byte is the opcode
  if (opcode == 0x00) {          // Write operation
    if (numBytes > 1) {
      currentRegister = Wire.read();  // Second byte is the register address
      if (currentRegister < NUM_REGISTERS && numBytes > 2) {
        registers[currentRegister] = Wire.read();  // Write the value
        Serial.printf("Register[%d] written with value: %d\n", currentRegister, registers[currentRegister]);
        
      }
    }
  }
}

// Handle data requested by the master
void onRequestHandler() {
  Serial.println("Handle data requested by the master");
  if (currentRegister < NUM_REGISTERS) {
    uint8_t value = registers[currentRegister];  // Read the value from the current register
    Wire.write(value);                           // Send the value back to the master
    Serial.printf("Register[%d] read with value: %d\n", currentRegister, value);
  }
}

void loop() {
  delay(1000);
  
  // Optionally, add debugging or processing here
}
