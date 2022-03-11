import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
import time 
fs, data = wavfile.read(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\DriveBy.wav") # load the data
a = data.T[0] # this is a two channel soundtrack, I get the first track
b=[(ele/2**8.)*2-1 for ele in a] # this is 8-bit track, b is now normalized on [-1,1)
c = fft(b) # calculate fourier transform (complex numbers list)
d = len(c)/2  # you only need half of the fft list (real signal symmetry)
d = int(d)
print("HERE")
#plt.plot(abs(c[:(d-1)]),'r') 
print("NOW HERE")
plt.xlim(1,3)
#plt.show()

import matplotlib.pyplot as plt
import numpy as np


def plot(data):
    plt.plot(data, color='steelblue')
    plt.figure()
    plt.show()

rate, wav_data = wavfile.read(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\DriveBy.wav")
#plot(wav_data)
plot(np.abs(np.fft.fft(wav_data)))


rate, wav_data = wavfile.read(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\DriveBy.wav")


    #need to determine the correct amplitude 
    #for j in range(i, len(wav_data)-1):
    #    if (0 <= abs(time[j] - time[old_beat_ind]) <= 2*SPB):
    #        wav = np.amax(wav_data[j])
    #        count +=1
    #        amplitude.append(wav)
    #        old_beat_ind = i
    #print("COUNT", count)
    #print(amplitude)
    #return old_beat_ind