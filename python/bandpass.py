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
from scipy import signal

def filter(filename, high):
    rate, wav_data = wavfile.read(filename)
    N  = 6    # Filter order
    if (high == 0):
        fc = [.001, .7] # Cutoff frequency, normalized
    else:
        fc = [.6, .999]
    b, a = signal.butter(N, fc, btype="bandpass")
    filtered = signal.filtfilt(b,a, wav_data, padlen = 0)
    #firls
    wavfile.write("This_Love-low2.wav", rate, filtered.astype(np.int16))
    return filtered


