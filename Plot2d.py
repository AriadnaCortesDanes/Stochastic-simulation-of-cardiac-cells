import numpy as np
import matplotlib.pyplot as plt

import matplotlib.animation as animation


import pandas as pd


df = pd.read_csv('csv/Voltages_40x40.csv')
df = df.set_index('time_0_0')


fps = 100
nSeconds = 5
snapshots = [ np.random.rand(5,5) for _ in range( nSeconds * fps ) ]


# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure( figsize=(40,40) )

a = snapshots[0]
im = plt.imshow(np.reshape(np.array(df.iloc[0]),(40,40)), interpolation='none', aspect='auto', vmin=-90, vmax=30)

def animate_func(i):

    im.set_array(np.reshape(np.array(df.iloc[i]),(40,40)))
    return [im]

anim = animation.FuncAnimation(
                               fig, 
                               animate_func, 
                               frames = nSeconds * fps,
                               interval = 1000 / fps, # in ms
                               )

# anim.save('test_anim.mp4', fps=fps, extra_args=['-vcodec', 'libx264'])

print('Done!')

plt.show()  # Not required, it seems!