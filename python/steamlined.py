from jinja2 import pass_environment
from bandpass import filter 
from FINAL import beatmap_maker 
import json
from scipy.io import wavfile # get the api
from getc import get_c 
import librosa
import glob
import os 
from os.path import exists


new_dict = dict() 

for root, dirs, files in os.walk("songs/", topdown=False):
    for name in dirs:
        dir = os.path.join(root, name)
        if exists(os.path.join(dir, "beatmap.json")) == False:
            new_dict = dict() 
            filename = os.path.join(dir, "song.wav")
            create_wav = 1
            rate, wav_melody = wavfile.read(filename)
            c = 50 #get_c(wav_melody) 
            wav_beats = filter(filename, 0) 
            beats,b,tempo, output_time, duration  = beatmap_maker(wav_beats, wav_melody, filename, c, create_wav)
            print(len(beats), len(b)) 
            data = {
            "name": filename,
            "BPM": tempo[0],
            "beats": sorted(beats + b, key = lambda i: i['time'])
            }

            json_name = os.path.join(dir,"beatmap.json")

            json_string = json.dumps(data, indent=4, sort_keys=True, default=str)
            with open(json_name, 'w') as outfile:
                outfile.write(json_string)
            new_dict[duration] = output_time 

    