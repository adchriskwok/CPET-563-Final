import cv2
import numpy as np
import time
import mmap
import struct
import sys, random
import ctypes
import droneCamera as dc

cam = dc.cam()

for x in range(0,10):
  frame = cam.getFrame(1)
  cv2.imshow("frame", frame)
  cv2.waitKey(1)