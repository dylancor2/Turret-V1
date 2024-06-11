import keyboard
import serial
import time

arduino = serial.Serial(port = 'COM3', baudrate=9600, timeout = 0.1)

x = 0
y = 0
def incrementY():
    arduino.write(b'1')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

def decrementY():
    arduino.write(b'2')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

def incrementX():
    arduino.write(b'3')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

def decrementx():
    arduino.write(b'4')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

def resetAll():
    arduino.write(b'5')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

def shoot():
    arduino.write(b'6')
    time.sleep(0.1)
    data = arduino.readline()
    print(data)

keyboard.add_hotkey('up', lambda: incrementY())
keyboard.add_hotkey('down', lambda: decrementY())

keyboard.add_hotkey('left', lambda: incrementX())
keyboard.add_hotkey('right', lambda: decrementx())
keyboard.add_hotkey('r', lambda: resetAll())
keyboard.add_hotkey('space', lambda: shoot())

keyboard.wait('esc')
print('Exiting...')
arduino.write(b'7')
