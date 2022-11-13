import serial

# must match port, baudrate, and delay() on Arduino file
esp32 = serial.Serial('COM5', baudrate=115200, timeout=2.5)

while True:
    parkingSpot = esp32.readline().decode('UTF-8')
    print(parkingSpot)
