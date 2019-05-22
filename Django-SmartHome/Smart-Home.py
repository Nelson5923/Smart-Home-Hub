import requests
import smbus
import time
import json

ARDUINO_1_ADDRESS = 0x04
ARDUINO_2_ADDRESS = 0x05
ARDUINO_3_ADDRESS = 0x06
CONTROL_ARG_GET_ADDRESS = "https://api.thingspeak.com/channels/761569/feeds/last.json?api_key=I0VDWYIJ0MY4GZLX"
# https://api.thingspeak.com/update?api_key=Z9JHULF38U3Y8IVW&field2=1
CONTROL_ARG_POST_ADDRESS = "https://api.thingspeak.com/update?api_key=EW7G6EOHQELFAUTF"
# https://api.thingspeak.com/update?api_key=Z9JHULF38U3Y8IVW&field2=1
SENSOR_VAL_FLAG_GET_ADDRESS = "https://api.thingspeak.com/channels/754991/feeds/last.json?api_key=P1XW47ZYFSB9MRN0"
# https://api.thingspeak.com/channels/754991/feeds/last.json?api_key=P1XW47ZYFSB9MRN0
SENSOR_VAL_FLAG_POST_ADDRESS = "https://api.thingspeak.com/update?api_key=KZ27JRPTMTZR9OKX"
# https://api.thingspeak.com/update?api_key=KZ27JRPTMTZR9OKX&field1=1
bus = smbus.SMBus(1)

######################### Device Control #########################

def controlMotor(val):

    op = 1
    putArduino(ARDUINO_1_ADDRESS, op, [val , 0, 255])

    return 1

def controlDoorLock(val):

    op = 2
    putArduino(ARDUINO_2_ADDRESS, op, [val, 0, 255])

    return 1

def controlLED(val):

    op = 3
    putArduino(ARDUINO_2_ADDRESS, op, [val, 0, 255])

    return 1

def playMusic(val):

    op = 4
    putArduino(ARDUINO_3_ADDRESS, op, [val, 0, 255])

    return 1

def getSensorVal():

    sensorVal = []
    val = 0

    while int(val) != 255:
        val = getArduino(ARDUINO_1_ADDRESS)
        sensorVal.append(int(val))
        print(sensorVal)

    if sensorVal:

        putThingSpeak(str(SENSOR_VAL_FLAG_POST_ADDRESS \
        + "&" + "field" + "5" + "=" + str(sensorVal[0]) \
        + "&" + "field" + "6" + "=" + str(sensorVal[1]) \
        + "&" + "field" + "7" + "=" + str(sensorVal[2]) \
        + "&" + "field" + "8" + "=" + str(sensorVal[3])))

    return sensorVal

######################### Remote Control #########################

def getThingSpeak(address):

    r = requests.get(address)
    time.sleep(3)

    return r.json()

def putThingSpeak(address):

    r = requests.post(address)
    time.sleep(3)

    return r

def getArduino(address):

    val = bus.read_byte(address)
    time.sleep(.3)

    return val

def putArduino(address, op, val):

    bus.write_byte(address, int(op))
    time.sleep(.4)

    for i in val:
        bus.write_byte(address, int(i))
        time.sleep(.4)

    return 1

######################### Automatic Control #########################

def updateMotor(sensorVal): # When the temperature is high, the motor would spin faster.

    temp = sensorVal[2]

    if temp > 25:

        speed = 2000
        controlMotor(speed)

    else:

        controlMotor(0)

def updateLED(sensorVal): # When the motion is detected, the LED would blink.

    motion = sensorVal[0]
    op = 5

    if motion:
        putArduino(ARDUINO_2_ADDRESS, op, [1, 0, 255])
    else:
        putArduino(ARDUINO_2_ADDRESS, op, [0, 0, 255])

def autoPlay(sensorVal): # When the light is low, the music would be played.

    light = sensorVal[1]

    if light < 40:
        playMusic(1)
    else:
        playMusic(0)

def main():

    # Get the Last Update Operation

    time.sleep(5)

    while True:

        ControlFlag = getThingSpeak(CONTROL_ARG_GET_ADDRESS)
        sensorVal = getSensorVal()
        AUTO_CONTROL_FLAG = int(ControlFlag['field5'])

        if AUTO_CONTROL_FLAG is 0:

            print("Mode: User-Control")

            print("Motor: " + ControlFlag['field1'])
            ret = controlMotor(ControlFlag['field1'])

            print("DoorLock: " + ControlFlag['field2'])
            ret = controlDoorLock(ControlFlag['field2'])

            time.sleep(5)

            print("LED: " + ControlFlag['field3'])
            ret = controlLED(ControlFlag['field3'])

            print("Buzzer: " + ControlFlag['field4'])
            ret = playMusic(ControlFlag['field4'])

        elif AUTO_CONTROL_FLAG is 1:

            print("Mode: Auto-Control")
            updateMotor(sensorVal)
            updateLED(sensorVal)
            # updateLock(sensorVal)
            autoPlay(sensorVal)

main()
