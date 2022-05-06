import matplotlib.pyplot as plt
import numpy as np
import wave
import sys
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
import glob
import json

new_dict_neg = dict()
new_dict_pos = dict()
new_dict_good = dict()
new_dict_total = dict()
all_wav = glob.glob('accuracy/*.wav')






y, sr = librosa.load("accuracy/basic.wav")
tempo, beats = librosa.beat.beat_track(y=y, sr=sr)
frames = librosa.frames_to_time(beats, sr=sr)
my_beats = open("acc_beats/" + "basic.json")
my_beats = json.load(my_beats)
beats = my_beats["beats"]
list_beats = []

for key in beats:
    list_beats.append(key["time"])

print(list_beats)
print(frames)
plt.plot(list_beats,[0]*len(list_beats), 'ro')
plt.plot(frames,[.1]*len(frames), 'bo')
plt.show()




''''
    rate, wav_beats = wavfile.read(fileoname)
    rate, basic = wavfile.read("acc_beats/" + filename[9:-4] + "_beats.wav")
    wav_beats = wav_beats*((np.amax(basic))/(np.amax(wav_beats)))
    total = 0
    false_positive = 0
    good_points = 0
    false_negative = 0
    for i in range(len(wav_beats)):
        if (wav_beats[i].all() == basic[i].all()):
            pass
        else:
            if (wav_beats[i].any() > basic[i].any()):
                false_positive +=1
            elif (wav_beats[i].any() < .8*basic[i].any()):
                good_points +=1
            else:
                false_negative +=1
            total +=1

    new_dict_neg[filename] = false_negative/total
    new_dict_pos[filename] = false_positive/total
    new_dict_good[filename] = good_points/total
    print(new_dict_neg)
    print(new_dict_pos)
    print(new_dict_good)

'''

#plt.figure(1)
#plt.title("Signal Wave...")
#plt.plot(wav_beats, 'ro')
#plt.plot(basic)
#plt.plot(wav_beats, 'ro')
#plt.show()