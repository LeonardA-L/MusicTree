# -*- coding: utf-8 -*-
from distlib.util import chdir

__author__ = "Emilien Bai"
__email__ = "emilien.bai@insa-lyon.fr"

import pygame
import pygame.mixer
from os import chdir
import thread
import gc

gc.disable()

def playSound(toPlay):
    toPlay.play()


class SoundBox :
    def __init__ (self) :
        pygame.init()
        chdir("../Sons/")
        self.sounds= []

        self.soundname0 = "clap.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname0))
        #self.sound0 = pygame.mixer.Sound(self.soundname0)

        self.soundname1 = "hithat.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname1))
        #self.sound1 = pygame.mixer.Sound(self.soundname1)

        self.soundname2 = "kick.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname2))
        #self.sound2 = pygame.mixer.Sound(self.soundname2)

        self.soundname3 = "midTom.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname3))
        #self.sound3 = pygame.mixer.Sound(self.soundname3)

        self.soundname4 = "snare.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname4))
        #self.sound4 = pygame.mixer.Sound(self.soundname4)

        self.soundname5 = "tambourin.wav"
        self.sounds.appen(pygame.mixer.Sound(self.soundname5))
        #self.sound5 = pygame.mixer.Sound(self.soundname5)


    def dispatch (self, args) :
        for i in range (0, len(args)):
            #print ("salut", i, args[i])
            if args[i]==1 :
                thread.start_new_thread(playSound, (self.sounds[i],))
            '''
            if args[i]==1 :
                if i == 0 :
                    thread.start_new_thread(playSound, (self.sound0,))
                elif i == 1 :
                    thread.start_new_thread(playSound, (self.sound1,))
                elif i == 2 :
                    thread.start_new_thread(playSound, (self.sound2,))
                elif i== 3 :
                    thread.start_new_thread(playSound, (self.sound3,))
                elif i == 4 :
                    thread.start_new_thread(playSound, (self.sound4,))
                elif i == 5 :
                    thread.start_new_thread(playSound, (self.sound5,))
            '''





