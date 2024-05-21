import numpy as np
import matplotlib.pyplot as plt

import matplotlib.animation as animation


import pandas as pd


df = pd.read_csv('csv/TestQ1_20x20.csv',index_col=False)
df = df.set_index('time')


fps = 100
nSeconds = 5

matrix_shape = (20,20)



# First set up the figure, the axis, and the plot element we want to animate
fig = plt.figure( figsize=matrix_shape )

im = plt.imshow(np.reshape(np.array(df.iloc[0]),matrix_shape), interpolation='none', aspect='auto', vmin=-90, vmax=30)
title = plt.title(f"Simulation T= {0} ms")

def animate_func(i):

    im.set_array(np.reshape(np.array(df.iloc[i]),matrix_shape))
    title.set_text(f"Simulation T= {i*5} ms")
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