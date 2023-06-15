from math import cos, acos, pi
import numpy

freq = 50 #Hz
V = 12 #V
w = 2 * pi * freq
b = 10 * 10**(-3)

def integral(a):
    return V/w * (cos(w*a) - cos(w*b))


def calca(a):
    proc = a
    return numpy.arccos(proc * (1 - numpy.cos(w*b)) + numpy.cos(w*b)) / w

i=0
while i<=1:
    print(calca(i))
    i += 0.1