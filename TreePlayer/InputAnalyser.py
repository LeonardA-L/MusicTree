# -*- coding: utf-8 -*-
__author__ = "Emilien Bai"
__email__ = "emilien.bai@insa-lyon.fr"

import TreeSoundBox as TSB

# Constants
sensorNumber = 6

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



arduinoValue = input("entrez votre entier\n")

while (arduinoValue != 666):
    fillTable(arduinoValue)
    callSound(sensorValues)
    arduinoValue = input()





