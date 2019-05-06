import cv2
import numpy as np
import time
import mmap
import struct
import sys, random
import ctypes

class cam(object):
  def __init__(self):
    self.lib = ctypes.cdll.LoadLibrary('./mt9v034-driver.so')
    result = self.lib.init()
    self.frame = np.ones((480,752,4), dtype=np.uint8)

  def getFrame(self,type):
    result = self.lib.getFrame(ctypes.c_void_p(self.frame.ctypes.data))
    if (type == 0):  # rgb
      return self.frame[:,:,0:3]
    elif (type == 1): # gray
      return self.frame[:,:,3]
    elif (type == 2):  # rgb compressed
      ret, jpeg = cv2.imencode('.jpg', self.frame[:,:,0:3])
      return jpeg.tobytes()
    elif (type == 3):  # gray compressed
      ret, jpeg = cv2.imencode('.jpg', self.frame[:,:,3])
      return jpeg.tobytes()  
    else:
      print "invalid parameter"
   
  def __del__(self):
    result = self.lib.destroy