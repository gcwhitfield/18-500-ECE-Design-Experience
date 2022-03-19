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


def get_stats(wav_data, BPM, time):
    #transform BPM to beats per second
    BPM = BPM[0]
    BPS = BPM/60
    SPB = 1/BPS
    print(SPB)
    i = 0
    #determines the beginning of the actual song
    #eliminates false positives
    while (wav_data[i].all() == 0):
        i+=1
    old_beat_ind = i
    wav_data = wav_data[i:]
    time = time[i:]
    return wav_data, time, SPB

def get_average_energy(wav_data, time, SPB):
    #relies on the assumption that the entire song has the same energy
    summation = 0
    for i in range(1024):
        summation += (np.amax(wav_data[i]))^2
    return summation/102400

def get_local_energy(wav_data, time, SPB):
    summation = 0
    for i in range(43):
        summation += (np.amax(wav_data[i]))^2
    wav_data[0] = summation//43
    return summation/43

def comparison(energy, local_energy,c, beats, time,SPB):
    try:
        if (int(energy) > int(abs(local_energy)*c)):
            if (len(beats) >= 1):
                if abs(beats[-1] - time) > SPB:
                    beats.append(time)

    except:
        return beats

    return beats

#definition of basic usage vectors
start_time = time.time()
y,sr = librosa.load(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\DriveBy.wav")
onset_env = librosa.onset.onset_strength(y=y, sr=sr)
tempo = librosa.beat.tempo(onset_envelope= onset_env, sr=sr)
#gets the static BPM
#for the purposes of this test:
c = 3.5
beats = []
rate, wav_data = wavfile.read(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\basic.wav")

duration = len(wav_data)/rate
#correlates amplitudes to times
time1 = np.arange(0,duration,1/rate) #time vector
wav_data, time1, SPB = get_stats(wav_data, tempo,time1)
energy = get_average_energy(wav_data[len(wav_data)//2:], time1, SPB)
local_energy = abs(get_local_energy(wav_data[0:43], time1[0:43], SPB))
print("EN", local_energy)
print("HERE")
for i in range(43, len(wav_data)):
    if (i == 43):
        beats.append(time1[i])
    local_energy = 43*local_energy
    local_energy = local_energy - (np.amax(wav_data[i-43])*np.amax(wav_data[i-43]))
    local_energy = local_energy + (np.amax(wav_data[i])*np.amax(wav_data[i]))
    local_energy = local_energy/43

    beats = comparison(energy, local_energy, c, beats, time1[i], SPB)

print(len(beats))
print(beats)
new_time = time.time()
print("My program took", new_time - start_time, "to run")
y = []
for i in range(len(beats)):
    y.append(i)
plt.plot(beats, y, 'ro')
plt.show()


