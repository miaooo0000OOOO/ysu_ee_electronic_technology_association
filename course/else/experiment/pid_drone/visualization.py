import matplotlib.pyplot as plt
import numpy as np
import json

with open("data.json", "r") as f:
    data = json.load(f)

ts, Fs, hs, tars = [], [], [], []

for line in data:
    t, F, h, tar = line["t"], line["F"], line["h"], line["tar"]
    ts.append(t)
    Fs.append(F)
    hs.append(h)
    tars.append(tar)

# print(ts, Fs, hs)

plt.plot(ts, hs)
plt.plot(ts, Fs)
plt.plot(ts, tars)
plt.show()
