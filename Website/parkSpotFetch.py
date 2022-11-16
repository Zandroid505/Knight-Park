import serial
import sys


# must match port, baudrate, and delay() on Arduino file
esp32 = serial.Serial('COM4', baudrate=115200, timeout=2.5)
print(esp32.readline().decode('UTF-8'))
sys.stdout.flush()


# def parse_parking_info(spot):
#     info = spot.split('_')
    
#     return info[0], info[1], info[2], info[3]


# def function():
#     print(esp32.readline().decode('UTF-8'))
#     # parkingSpot = esp32.readline().decode('UTF-8')
#     # print(list(parse_parking_info(parkingSpot)))