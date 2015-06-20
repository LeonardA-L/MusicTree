# -*- coding: utf-8 -*-
__author__ = "Emilien Bai"
__email__ = "emilien.bai@insa-lyon.fr"

import TreeSoundBox as TSB
import datetime
import serial

# Constants
sensorNumber = 6
s=serial.Serial('/dev/ttyACM1', 115200)


#Global
sensorValues = [0, 0, 0, 0, 0, 0]
a = TSB.SoundBox()

#Functions
def fillTable(int_value):
    for i in range(0, sensorNumber):
        temp = int_value >> i
        temp = temp & 0b1
        sensorValues[i] = int(temp)


def callSound(args):
    a.dispatch(args)


while True:
    try:
        arduinoValue = int (s.readline())
        break
    except ValueError:
        pass
        #print "Oops!  That was no valid number.  Try again..."

while (arduinoValue != 666):
    #print (datetime.datetime.now());
    fillTable(arduinoValue)
    #print (datetime.datetime.now());
    callSound(sensorValues)
    #print(datetime.datetime.now());
    try:
        arduinoValue = int (s.readline())
    except ValueError:
        print "Oops!  That was no valid number.  Try again..."


