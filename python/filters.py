from numbers import Integral
from scipy.io.wavfile import read, write
from scipy.signal.filter_design import butter, buttord
from scipy.signal import lfilter
from numpy import asarray
import numpy as np 

def convert_hertz(freq):
    # convert frequency in hz to units of pi rad/sample
    # (our .WAV is sampled at 44.1KHz)
    return freq * 2.0 / 44100.0
rate, sound_samples = read('DriveBy.wav')
pass_freq = convert_hertz(440.0) # pass up to 'middle C'
stop_freq = convert_hertz(440.0*4) # max attenuation from 3 octaves
pass_gain = 3.0 # tolerable loss in passband (dB)
stop_gain = 60.0 # required attenuation in stopband (dB)
ord, wn = buttord(pass_freq, stop_freq, pass_gain, stop_gain)
b, a = butter(ord, wn, btype = 'low')
filtered = lfilter(b, a, sound_samples)
integerised_filtered = asarray(filtered, int)
write('drive-filtered_low.wav', rate, integerised_filtered)
print(integerised_filtered)
print(np.amax(integerised_filtered))
print(integerised_filtered.shape)

