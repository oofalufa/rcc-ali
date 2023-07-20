import numpy as np 
import matplotlib.pyplot as plt 

arr = np.array([1, 2, 3, 4, 5])

print(arr)
 
def different(t):
    v = ((t*t)* 3) + (5*t) + 7
    return v

if __name__ == "__main__":

    #print("what is your distance?")
    #x = int(input())

    print("what is your time")
    t = float(input())

    x1 = different(t)

    print("what is your delta time")
    deltat = float(input())

    x2 = different(deltat)

    print("your slope")
    print( (x2-x1) / (deltat-t))
