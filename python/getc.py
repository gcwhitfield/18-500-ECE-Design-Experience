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

def get_c(wav_melody):
    mean = np.mean(wav_melody) 
    high = np.amax(wav_melody) 
    #print(mean) 
    #print(high) 
    #print(high/mean) 
    return abs(high/(mean*10000)) 

