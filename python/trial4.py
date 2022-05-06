import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
import numpy as np
import scipy
import time
import librosa
import statistics
import sys
import subprocess

def add_sound(wav_data, sound): 
    for i in range(len(sound)): 
        wav_data[i] += sound[i]
    return wav_data 

def get_stats(wav_data, BPM, time):
    #transform BPM to beats per second
    BPM = BPM[0]
    BPS = BPM/60
    SPB = 1/BPS
    print(SPB)

    #determines the beginning of the actual song
    #eliminates false positives
    wav_data = wav_data[:, 0]

    return wav_data, time, SPB

def get_average_energy(wav_data, time, SPB):
    #relies on the assumption that the entire song has the same energy
    summation = 0
    for i in range(1024):
        summation += (wav_data[i])^2
    return summation/1024

def get_local_energy(wav_data, time, SPB):
    summation = 0
    for i in range(43):
        summation += (wav_data[i])^2
    wav_data[0] = summation/43
    return summation/43

def comparison(energy, local_energy,c, beats, time,SPB):
    try:
        if (abs(int(local_energy) > abs(int((energy)*c)))) and (abs(beats[-1]["time"] - time) > .2): #  :

            beats.append({"locations": 3, "time": time})
            beats2.append(time)
    except:
        print("HERE2")
        return beats

    return beats

#definition of basic usage vectorssdsa,dmsa
start_time = time.time()
rate, wav_data = wavfile.read(r"Pompeii-high.wav")
y,sr = librosa.load(r"Pompeii-high.wav")
#rate2, wav_data2 = wavfile.read(r"click_B_1.wav")

file = "Pompeii.wav"
onset_env = librosa.onset.onset_strength(y=y, sr=sr)
tempo = librosa.beat.tempo(onset_envelope= onset_env, sr=sr)
#gets the static BPM
#for the purposes of this test:





beats = [{"locations":3, "time":0}]
beats2 = [0]

duration = len(wav_data)/rate
#correlates amplitudes to times
time1 = np.arange(0,duration,1/rate) #time vector
wav_data, time1, SPB = get_stats(wav_data, tempo,time1)
energy = abs(get_average_energy(wav_data[len(wav_data)//2:], time1, SPB))
local_energy = abs(get_local_energy(wav_data[0:43], time1[0:43], SPB))
print(energy)
print("MAX", np.amax(wav_data))
#c = 4
c = 80



for i in range(43,len(wav_data)):

    local_energy = 43*local_energy
    local_energy = local_energy -(wav_data[i-43])*wav_data[i-43]##

    local_energy = local_energy + ((wav_data[i])*(wav_data[i]))
    local_energy = local_energy/43

    beats = comparison(energy, local_energy, c, beats, time1[i], SPB)

new_time = time.time()
print("My program took", new_time - start_time, "to run")



