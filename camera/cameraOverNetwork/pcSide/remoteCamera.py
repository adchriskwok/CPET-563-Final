# Dr. Kaputa

import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from os import path
import cv2
import numpy as np
import time
import mmap
import struct
import random
import ctypes
import imagezmq

class MainWindow(QMainWindow):
  def __init__(self):
    super(MainWindow, self).__init__()
    self.statusBar().showMessage("Imagine RIT")
    
    self.grid = Grid(self)
    self.cameraDock = QDockWidget(self)
    self.cameraDock.setWidget(self.grid)
    self.addDockWidget(Qt.DockWidgetArea(4),self.cameraDock)
    
    self.dummyDock = QDockWidget(self)
    self.button1 = QPushButton("button 1")
    self.dummyDock.setWidget(self.button1)
    self.addDockWidget(Qt.DockWidgetArea(4),self.dummyDock)
    
    DOCKOPTIONS = QMainWindow.AllowTabbedDocks
    DOCKOPTIONS = DOCKOPTIONS|QMainWindow.AllowNestedDocks
    DOCKOPTIONS = DOCKOPTIONS|QMainWindow.AnimatedDocks
    self.setDockOptions(DOCKOPTIONS)
    self.setTabPosition(Qt.AllDockWidgetAreas,QTabWidget.North)
    
    self.show()
  
###############################################################################
# camera stuff
###############################################################################
class Grid(QGraphicsView):   
  def __init__(self,parent):
    super(Grid, self).__init__()
    self.parent = parent
    self.scene = QGraphicsScene(self)
    self.setScene(self.scene)
    self.image_hub = imagezmq.ImageHub()
    rpi_name, jpg_buffer = self.image_hub.recv_jpg()
    self.frame = cv2.imdecode(np.fromstring(jpg_buffer, dtype='uint8'), -1)
    self.image_hub.send_reply(b'OK')
    
    self.height, self.width, self.colors = self.frame.shape
    self.bytesPerLine = 3 * self.width
    self.rawImage = QImage(self.frame.data,self.width,self.height,self.bytesPerLine,QImage.Format_RGB888)
    self.pixMap = QPixmap.fromImage(self.rawImage.rgbSwapped())
    self.pixPointer = self.scene.addPixmap(self.pixMap)
    
    self.timer = QBasicTimer()
    self.timer.start(0, self)
         
  def timerEvent(self, event):
    rpi_name, jpg_buffer = self.image_hub.recv_jpg()
    self.frame = cv2.imdecode(np.fromstring(jpg_buffer, dtype='uint8'), -1)
    self.image_hub.send_reply(b'OK')
    self.rawImage = QImage(self.frame.data,self.width,self.height,self.bytesPerLine,QImage.Format_RGB888)
    self.pixMap = QPixmap.fromImage(self.rawImage.rgbSwapped())
    self.pixPointer.setPixmap(self.pixMap)
         
  def resizeEvent(self, event):
    super(Grid, self).resizeEvent(event)
    self.fitInView(self.scene.sceneRect(), Qt.KeepAspectRatio) 
       
def main():
  app = QApplication(sys.argv) 
  mainWindow = MainWindow()
  sys.exit(app.exec_())

if __name__ == '__main__':
    main()