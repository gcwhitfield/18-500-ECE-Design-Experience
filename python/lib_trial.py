import librosa
from trial2 import beats2, tempo, file, beats
from trial import beats as b

import json
import librosa
import matplotlib.pyplot as plt

data = {
"name": file,
 "BPM": tempo[0],
 "beats": sorted(b + beats, key = lambda i: i['time'])
}
print(data)
print(len(beats))
print(len(b))
print(len(beats+b))
json_string = json.dumps(data, indent=4, sort_keys=True, default=str)
with open('Pompeii-FULL2.json', 'w') as outfile:
    outfile.write(json_string)
