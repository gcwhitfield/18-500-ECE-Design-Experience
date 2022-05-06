import librosa
import matplotlib.pyplot as plt
import librosa.display
import sklearn
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
import numpy as np
import time
import librosa
#from trial2 import beats2, tempo, file, beats
import json
import vamp
import librosa
#import essentia.standard as es
import matplotlib.pyplot as plt

import json

#audio_path = "DriveBy.wav"
import os, sys, librosa
import pandas as pd
from scipy import signal
from scipy import linalg
import matplotlib
from matplotlib import pyplot as plt
from matplotlib.colors import ListedColormap
import IPython.display as ipd
from numba import jit
import libfmp 
import libfmp.b
start_time = time.time()

y, sr = librosa.load("DriveBy.wav")
spectrum = signal.stft(y, fs = sr)
print(spectrum) 
spectrum = np.abs(librosa.stft(y,n_fft = 16384, hop_length = 512, ))
print(np.amin(spectrum))
print(np.amax(spectrum))
times = librosa.frames_to_time(spectrum.shape[1], sr = sr,n_fft = 16384, hop_length = 512) 
time1 =  np.arange(0,times,times/len(spectrum)) #time vector 
print(time1)
new = []
print(len(spectrum))
print(len(time1))
print(spectrum) 
first_mean = np.mean(spectrum[:len(spectrum)//3])
second_mean = np.mean(spectrum[len(spectrum)//3:])
third_mean = np.mean(spectrum[2*len(spectrum)//3:])
for freq in range(len(spectrum)//3):
    bin_freq = np.amax(spectrum[freq])
    if (bin_freq > 5*first_mean):
        new.append({"locations": 1, "time": time1[freq]})
    elif (bin_freq > 500 and bin_freq < 850):
        pass
        #new.append({"locations": 2, "time": time1[freq]})
    else:
        pass
        #new.append({"locations": 3, "time": time1[freq]})

for freq in range(len(spectrum)//3):
    bin_freq = np.amax(spectrum[len(spectrum)//3 + freq])
    if (bin_freq > 5*second_mean):
        new.append({"locations": 2, "time": time1[freq + len(spectrum)//3]})
    elif (bin_freq > 500 and bin_freq < 850):
        pass
        #new.append({"locations": 2, "time": time1[freq]})
    else:
        pass
        #new.append({"locations": 3, "time": time1[freq]})
for freq in range(len(spectrum)//3):
    bin_freq = np.amax(spectrum[2*len(spectrum)//3 + freq])
    if (bin_freq > 5*third_mean):
        new.append({"locations": 3, "time": time1[freq + 2*len(spectrum)//3]})
    elif (bin_freq > 500 and bin_freq < 850):
        pass
        #new.append({"locations": 2, "time": time1[freq]})
    else:
        pass
        #new.append({"locations": 3, "time": time1[freq]})

    
#print(new) 
#print(len(new))


#print (len(frames))
#print(frames) 
#print(len(frames))
data = {
"name": "Whatever",
 "BPM": 122,
 "beats": new
}
print(new) 
print(len(new))
json_string = json.dumps(data, indent=4, sort_keys=True, default=str)
with open('db_mel5.json', 'w') as outfile:
    outfile.write(json_string)

new_time = time.time()
print("My program took", new_time - start_time, "to run")