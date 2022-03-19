import librosa
from trial2 import beats, tempo
import json

y,sr = librosa.load(r"C:\\Users\\shrey\\Documents\\4thYear\\2nd Sem\\Capstone\\DriveBy.wav")


# 2. Load the audio as a waveform `y`
#    Store the sampling rate as `sr`

# 3. Run the default beat tracker
tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)

print('Estimated tempo: {:.2f} beats per minute'.format(tempo))

# 4. Convert the frame indices of beat events into timestamps
beat_times = librosa.frames_to_time(beat_frames, sr=sr)
print(beat_times)
print(len(beat_times))
#############################################################

#create the JSON files
data = {
"Beat_file_data": {
"time_stamps": beats,
 "BPM": tempo

},
 "Beats": {
  "time_stamps": beats,
  "lanes": [0]*len(beats)
 }
}


json_string = json.dumps(data)
with open('json_data.json', 'w') as outfile:
    outfile.write(json_string)