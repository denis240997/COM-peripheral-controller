# import subprocess
# from time import sleep
from contextlib import contextmanager

import serial


@contextmanager
def get_serial_port(port: str, baudrate: int = 9600) -> serial.Serial:
    try:
        ser = serial.Serial(port, baudrate)
        yield ser    
    except serial.SerialException as e:
        print(f"Serial port error: {e}")
        raise e
    finally:
        ser.close()


# def write_to_serial_port(data_to_send: bytes, serial_port: str) -> None:
#     with get_serial_port(serial_port) as ser:
#         ser.write(data_to_send)
#         print("Bytes sent successfully.")


# def read_from_serial_port(serial_port: str) -> bytes:
#     with get_serial_port(serial_port) as ser:
#         return ser.read(5)


if __name__ == "__main__":

    # subprocess.Popen("./serial_port_sniffer.sh", shell=True)
    # sleep(0.1)
    # print("Serial port sniffer started.")


    # data_to_send = "b".encode()
    # data_to_send = bytes([0x01, 0x02, 0x03, 0x04, 0x05])
    # data_to_send = bytes([71, 0, 0, 5, 123])
    # 71 0 0 5 123


    # SERIAL_PORT = "/dev/ttyUSB0"
    SERIAL_PORT = "/dev/ttyS0"
    

    with get_serial_port(SERIAL_PORT) as ser:
        while True:
            try:
                input_data = input("Enter bytes to send: ")
                input_bytes = bytes([int(x) if x.isdigit() else x for x in input_data.split()])

                # write_to_serial_port(input_bytes, SERIAL_PORT)
                # print(read_from_serial_port(SERIAL_PORT))

                ser.write(input_bytes)
                print(ser.read(5))

            except KeyboardInterrupt:
                print("\nExiting...")
                break
