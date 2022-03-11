import matplotlib.pyplot as plt
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
import numpy as np
import time 


rate, wav_data = wavfile.read(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\basic.wav")
#plot(wav_data)
#plot(np.abs(np.fft.fft(wav_data)))
#new_fft = np.fft.fft(wav_data)))
duration = len(wav_data)/rate
time = np.arange(0,duration,1/rate) #time vector
print(len(time))
print(len(wav_data))
plt.plot(time,wav_data)
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.title('Basic_Instrumental')
plt.show()
arr = []
old_time = 0
#need to detect beat amplitude throughout the song 



for i in range(len(wav_data)): 
    val = abs(wav_data[i])
    if ((time[i]-old_time) > .5 and max(val) > 32500):
        arr.append(time[i])
        old_time = time[i]
print(arr)
