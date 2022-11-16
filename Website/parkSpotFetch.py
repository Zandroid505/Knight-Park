import serial
import sys
from time import sleep


# must match port, baudrate, and delay() on Arduino file
esp32 = serial.Serial(baudrate=115200, timeout=2.5)

while 1:
    data = esp32.readline().decode('UTF-8')
    print(data)
# print("HELLO THERE")
    sys.stdout.flush()
    sleep(5)


# def parse_parking_info(spot):
#     info = spot.split('_')

#     return info[0], info[1], info[2], info[3]


# def function():
#     print(esp32.readline().decode('UTF-8'))
#     # parkingSpot = esp32.readline().decode('UTF-8')
#     # print(list(parse_parking_info(parkingSpot)))