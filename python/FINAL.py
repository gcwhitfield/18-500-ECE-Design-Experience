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
    i = 0
    #determines the beginning of the actual song
    #eliminates false positives
    try: 
        wav_data = wav_data[:, 0]
    except:
        pass


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

def comparison_melody(energy, local_energy,c, beats, time,SPB, wav, location):
    try:
        if (abs(int(local_energy) > 4.2*c*abs(int((energy))))) and (abs(beats2[-1] - time) > 2*SPB) and location < 4: #  :

            beats.append({"locations": 0, "time": time})
            beats2.append(time)
            wav = 1000000
        elif (abs(int(local_energy) > 4.2*c*abs(int((energy))))) and (abs(beats2[-1] - time) > 2*SPB) and location < 8: #  :

            beats.append({"locations": 1, "time": time})
            beats2.append(time)
            wav = 1000000
    except:
        print("HERE2")
        return beats
    location +=1 
    location = location%8 

    return beats, wav, location 


def comparison_beats(energy, local_energy,c, beats, time,SPB, wav, location):
    try:
        if (abs(int(local_energy) > .1*c*abs(int((energy))))) and (abs(beats3[-1] - time) > SPB) and location < 4: #  :

            beats.append({"locations": 2, "time": time})
            beats3.append(time)
            wav = 1000000
        elif (abs(int(local_energy) > .1*c*abs(int((energy))))) and (abs(beats3[-1] - time) >SPB) and location < 8: #  :

            beats.append({"locations": 3, "time": time})
            beats3.append(time)
            wav = 1000000
    except:
        print("HERE2")
        return beats
    location +=1 
    location = location%8 

    return beats, wav, location 

beats2 = [0]
beats3 = [0]

def beatmap_maker(wav_data_beats,wav_data_melody, filename, c, create_wav):
    #definition of basic usage vectors
    start_time = time.time()
    rate, wav_beats = wavfile.read(filename)
    y,sr = librosa.load(filename)
    onset_env = librosa.onset.onset_strength(y=y, sr=sr)
    tempo = librosa.beat.tempo(onset_envelope= onset_env, sr=sr)
    beats = [{"locations":0, "time":0}]
    b = [{"locations": 2, "time": 0}]
    location_beats = 0 
    location_melody = 0 
    duration = len(wav_data_melody)/rate
    time1 = np.arange(0,duration,1/rate) #time vector
    wav_data_beats, time1, SPB = get_stats(wav_data_beats, tempo,time1)
    wav_data_melody, time1, SPB = get_stats(wav_data_melody, tempo, time1) 
    energy_beats = abs(get_average_energy(wav_data_beats[len(wav_data_beats)//2:], time1, SPB))
    energy_melody = abs(get_average_energy(wav_data_melody[len(wav_data_melody)//2:], time1, SPB))
    local_energy_beats = abs(get_local_energy(wav_data_beats[0:43], time1[0:43], SPB))
    local_energy_melody = abs(get_local_energy(wav_data_melody[0:43], time1[0:43], SPB))
    for i in range(43,len(wav_data_beats)):
        local_energy_beats = wav_data_beats[i]*wav_data_beats[i]
        local_energy_melody = wav_data_melody[i]*wav_data_melody[i]

        beats, wav_data_beats[i],location_beats = comparison_beats(energy_beats, local_energy_beats, c*3, beats, time1[i], SPB, wav_data_beats[i], location_beats)
        b, wav_data_melody[i],location_melody = comparison_melody(energy_melody, local_energy_melody, 20, b, time1[i], SPB, wav_data_melody[i], location_melody)

    new_time = time.time()
    if (create_wav == 1):
        new_name_beats = filename[:-4] + "_beats.wav"
        
        wavfile.write(new_name_beats, rate, wav_data_beats.astype(np.int16))
        new_name_melody = filename[:-4] + "_melody.wav"
        wavfile.write(new_name_melody, rate, wav_data_melody.astype(np.int16))
    return beats, b, tempo, new_time-start_time, duration 




