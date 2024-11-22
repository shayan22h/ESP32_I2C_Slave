import smbus


# Function to Init the Bus
def init_i2c(bus_id):
    try:
        bus = smbus.SMBus(bus_id)
        print(f"I2C bus {bus_id} initialized successfully.")
        return bus
    except Exception as e:
        print(f"Error initializing I2C bus: {e}")
        exit(1)

# Function to Send I2C Data to the slave
def send_data(bus, slave_address, register_address, data):
    try:
        bus.write_i2c_block_data(slave_address, register_address, data)
        print(f"Data {data} sent to slave 0x{slave_address:02X} at opcode 0x{register_address:02X}.")
    except Exception as e:
        print(f"Error sending data: {e}")
def Write_Handler():
     # Input loop
    while True:
        try:
            slave_address = int(input("Enter the slave device address (hex, e.g., 0x08): "), 16)
            register_address = int(input("Enter register address (hex, e.g., 0x00): "), 16)

            # Prepare data to send
            data_input = input("Enter data to send as comma-separated bytes (e.g., 1,2,3): ")
            data = list(map(int, data_input.split(',')))

            # Call function to send data
            send_data(bus, slave_address, register_address, data)

            termination_input = input(" Press E to terminate")
            if (termination_input == 'E'):
                break
            # Confirm user inputs
            print(f"Slave Address: 0x{slave_address:02X} The Register Address: 0x{register_address:02X}")
        except ValueError:
            print("Invalid input. Please enter valid numbers.")
        except KeyboardInterrupt:
            print("\nExiting program.")
            break

# Main program
def main():
    BUS_ID = 1
    bus = init_i2c(BUS_ID)
    try:
        req_type = input("Enter Request Type : W for write R for read ")
        if (req_type == 'W'):
            Write_Handler()
        

    except ValueError:
        print("Invalid input. Please enter valid numbers.")




if __name__ == "__main__":
    main()