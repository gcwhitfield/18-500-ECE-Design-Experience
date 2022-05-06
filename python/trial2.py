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
from bandpass import filter

def get_stats(wav_data, BPM, time):
    #transform BPM to beats per second
    BPM = BPM[0]
    BPS = BPM/60
    SPB = 1/BPS
    print(SPB)
    i = 0
    #determines the beginning of the actual song
    #eliminates false positives
    wav_data = .1*wav_data[:, 0]


    return wav_data, time, SPB

def get_average_energy(wav_data, time, SPB):
    #relies on the assumption that the entire song has the same energy
    summation = 0
    for i in range(1024):
        summation += wav_data[i]*wav_data[i]
    return summation/1024

def get_local_energy(wav_data, time, SPB):
    summation = 0
    for i in range(43):
        summation += wav_data[i]*wav_data[i]
    return wav_data[i]*wav_data[i]

def comparison(energy, local_energy,c, beats, time,SPB, wav, location):
    try:

        if (abs(int(local_energy) > c*abs(int((energy))))) and (abs(beats2[-1] - time) > .6) and location < 4: #  :

            beats.append({"locations": 2, "time": time})
            beats2.append(time)
            wav = 10000
        elif (abs(int(local_energy) > c*abs(int((energy))))) and (abs(beats2[-1] - time) > .6) and location < 8: #  :

            beats.append({"locations": 3, "time": time})
            beats2.append(time)
            wav = 10000

    except:
        print("HERE2")
        return beats

    location +=1
    location = location%8

    return beats, wav, location

#definition of basic usage vectors
start_time = time.time()
rate, wav_data = wavfile.read(r"This_Love.wav")
y,sr = librosa.load(r"This_Love.wav")

file = "Pompeii.wav"
onset_env = librosa.onset.onset_strength(y=y, sr=sr)
tempo = librosa.beat.tempo(onset_envelope= onset_env, sr=sr)
#gets the static BPM
#for the purposes of this test:





beats = [{"locations":0, "time":0}]
beats2 = [0]

location = 0
duration = len(wav_data)/rate
#correlates amplitudes to times
time1 = np.arange(0,duration,1/rate) #time vector

rate, wav_data = wavfile.read(r"Pompeii-LOW.wav")
y,sr = librosa.load(r"Pompeii-LOW.wav")


wav_data, time1, SPB = get_stats(.1*wav_data, tempo,time1)
energy = abs(get_average_energy(wav_data[len(wav_data)//2:], time1, SPB))
local_energy = abs(get_local_energy(wav_data[0:43], time1[0:43], SPB))
print(energy)
print("MAX", np.amax(wav_data))
#c = 3.5
c =5

for i in range(43,len(wav_data)):
    local_energy = wav_data[i]*wav_data[i]


    beats, wav_data[i],location = comparison(energy, local_energy, c, beats, time1[i], SPB, wav_data[i], location)
new_time = time.time()
print(len(beats))
print("My program took", new_time - start_time, "to run")

wavfile.write("This_Love-BEATS.wav", rate, 100*wav_data.astype(np.int16))
#
#    energy = 1024*energy
#    energy = energy -(wav_data[i-1024])*wav_data[i-1024]###

#    energy = energy + ((wav_data[i])*(wav_data[i]))
#    energy = energy/1024




