import cv2
import numpy as np
import time
import mmap
import struct
import sys, random
import ctypes
import copy
import imutils
import math

class cam(object):
  def __init__(self):
    # only using global path because this is staring with a startup script 
    self.lib = ctypes.cdll.LoadLibrary('/snickerdoodle/mt9v034/mt9v034-driver.so')
    result = self.lib.init()
    self.frame = np.ones((480,752,4), dtype=np.uint8)
    self.f = open("/dev/mem", "r+b")
    self.memCam = mmap.mmap(self.f.fileno(), 100, offset=0xfffc1000)
    self.memADC = mmap.mmap(self.f.fileno(), 100, offset=0xfffc2000)
    self.memIMU = mmap.mmap(self.f.fileno(), 100, offset=0x43c20000)
    
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
    elif (type == 4):  # rgb compressed and tracked
      tempImage = self.frame[:,:,0:3]

      self.clone_img = copy.copy(tempImage)
      
      # open dev mem and see to base address
      f = open("/dev/mem", "r+b")
      read_mem = mmap.mmap(f.fileno(), 40, offset=0x43c10000)
      reg = 32
      read_mem.seek(reg)
      self.fromMem = int(struct.unpack('l', read_mem.read(4))[0])
      #print(self.fromMem)
      self.x = 0
      self.y = 0
      
      if self.fromMem == 1024:
        rMin = 80
        rMax = 255
        gMin = 135
        gMax = 190
        bMin = 0
        bMax = 15
        
        # generate threshold array
        lower = np.array([bMin,gMin,rMin])
        upper = np.array([bMax,gMax,rMax])
        
        #(Ideas derived from https://www.pyimagesearch.com/2015/09/14/ball-tracking-with-opencv/)
        #gaussian blur to reduce high frequency noise (especially applicable when video functionality is implemented)
        blurred = cv2.GaussianBlur(self.clone_img, (11, 11), 0) 
        #converted to hsv color space
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
        
        #mask colors based on thresholds
        mask = cv2.inRange(hsv, lower, upper)
        
        #remove small blobs
        mask = cv2.erode(mask, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)
        
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        center = None
        
        # only proceed if at least one contour was found
        if len(cnts) > 0:
          # find the largest contour in the mask, then use
          # it to compute the minimum enclosing circle and
          # centroid
          c = max(cnts, key=cv2.contourArea)
          ((self.x, self.y), radius) = cv2.minEnclosingCircle(c)
          M = cv2.moments(c)
          center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
        
          # only proceed if the radius meets a minimum size
          if radius > 10:
            # draw the circle and centroid on the frame,
            # then update the list of tracked points
            cv2.circle(self.clone_img, (int(self.x), int(self.y)), int(radius),(0, 255, 255), 2)
            cv2.circle(self.clone_img, center, 5, (0, 0, 255), -1)
            
            # Tell user coordinates:
            #print("self.x location: " + str(self.x))
            #print("self.y location: " + str(self.y))
        
        #cv2.imshow('Result',self.clone_img)
        
      elif self.fromMem == 1706:
        
        #(Ideas derived from https://realpython.com/face-recognition-with-python/) along with haarcascade_frontalface_default XML doc.
        
        cascPath = "haarcascade_frontalface_default.xml"
        
        # Create the haar cascade
        faceCascade = cv2.CascadeClassifier(cascPath)
        
        gray = cv2.cvtColor(self.clone_img, cv2.COLOR_BGR2HSV)
        
        # Detect faces in the image
        faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.1,
        minNeighbors=5,
        minSize=(30, 30),
        flags = cv2.CASCADE_SCALE_IMAGE
        )
        
        self.x = 0
        self.y = 0
        
        # Draw a rectangle around the faces
        for (x, y, w, h) in faces:
          cv2.rectangle(self.clone_img, (x, y), (x+w, y+h), (0, 255, 0), 2)
          if (math.sqrt(((abs(320 - (x+(w/2))))^2)+((abs(240 - (y+(h/2))))^2)) < math.sqrt(((abs(320 - (self.x+(w/2))))^2)+((abs(240 - self.y))^2))):
            self.x = x+(w/2)
            self.y = y+(h/2)
      
        cv2.line(self.clone_img,(int(self.x),0),(int(self.x),480),5)
        cv2.line(self.clone_img,(0,int(self.y)),(480,int(self.y)),5)
        #cv2.imshow('Result',self.clone_img)
          
      self.memCam.seek(0)  
      self.memCam.write(struct.pack('i', int(self.x))) 
      self.memCam.seek(4)  
      self.memCam.write(struct.pack('i', int(self.y))) 
  
      ret, jpeg = cv2.imencode('.jpg', self.clone_img)
      return jpeg.tobytes()
      
    elif (type == 5):  # rgb with on screen display of vitals
      tempImage = np.ascontiguousarray(self.frame[:,:,0:3], dtype=np.uint8)   # must make it contiguous for opencv processing to work
      
      self.memADC.seek(0)  
      busVoltage = 'Bus Voltage: ' + str(round((struct.unpack('f', self.memADC.read(4))[0]),2)) + ' V'
      
      self.memIMU.seek(0)  
      imuAccelX = 'X Accel: ' + str(round((struct.unpack('h', self.memIMU.read(2))[0] / 1670.70),2)) + ' m/sec^2'
      self.memIMU.seek(4)  
      imuAccelY = 'Y Accel: ' + str(round((struct.unpack('h', self.memIMU.read(2))[0] / -1670.70),2)) + ' m/sec^2'
      self.memIMU.seek(8)  
      imuAccelZ = 'Z Accel: ' + str(round((struct.unpack('h', self.memIMU.read(2))[0] / -1670.70),2)) + ' m/sec^2'
      
      font = cv2.FONT_HERSHEY_SIMPLEX
      cv2.putText(tempImage,imuAccelX,(544,410), font, .5,(255,255,255),1)
      cv2.putText(tempImage,imuAccelY,(544,430), font, .5,(255,255,255),1)
      cv2.putText(tempImage,imuAccelZ,(544,450), font, .5,(255,255,255),1)
      cv2.putText(tempImage,busVoltage,(544,470), font, .5,(255,255,255),1)
      cv2.rectangle(tempImage,(540,392),(750,478),(0,255,0),2)
      #return tempImage
      ret, jpeg = cv2.imencode('.jpg', tempImage)
      return jpeg.tobytes()
    else:
      print "invalid parameter"
   
  def __del__(self):
    result = self.lib.destroy
    self.memCam.close()
    self.memADC.close()
    self.memIMU.close()
    self.f.close()
