import smbus

# Initialize I2C (bus 1 for Raspberry Pi)
bus = smbus.SMBus(1)
DEVICE_ADDRESS = 0x22  # Replace with your ESP32's I2C address

# Write to a register
try:
    bus.write_i2c_block_data(DEVICE_ADDRESS, 0x00, [2, 123])
    print("Data written to register 2")

    # Read from a register
    bus.write_byte(DEVICE_ADDRESS, 2)  # Point to register 2
    value = bus.read_byte(DEVICE_ADDRESS)
    print(f"Read value: {value}")
except Exception as e:
    print(f"Error communicating with I2C device: {e}")
