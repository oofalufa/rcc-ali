
import numpy as np

import matplotlib.pyplot as plt

import math




scale = 0.01

lower = -(np.pi)

upper = np.pi

t = np.arange(lower, upper, scale)




def func(tau):

    return(6*tau + 5)




def integral(start, end, delta):

    num = delta

    output = 0

    delta_num = (end - start)/delta

    if end >= 0:

        while (num < end):

            output += func(num)*delta

            num += delta

    else:

        while (num > end):

            output -= func(num)*delta

            num -= delta

    return output


def integral_func(start, end, delta):

    output = []

    i = start

    while(i < end):

        output.append(integral((i - delta), i, delta))

        i += delta

    return output







fig, ax = plt.subplots()

print(integral(0, 3, 0.001))

ax.plot(t, func(t), 'b', label = 'example function 1')