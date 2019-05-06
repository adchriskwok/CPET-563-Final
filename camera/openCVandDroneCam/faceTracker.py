import sys
from os import path
import cv2
import numpy as np
import PyQt4.QtGui as QtWidgets
from PyQt4 import QtCore
from PyQt4 import QtGui
from globals import globals
import time
import mmap
import struct
import random
import ctypes
import droneCamera as dc

class RecordVideo(QtCore.QObject):
    image_data = QtCore.pyqtSignal(np.ndarray)

    def __init__(self, camera_port=0, parent=None):
        super(RecordVideo, self).__init__()
        self.camera = dc.cam()
        self.timer = QtCore.QBasicTimer()

    def start_recording(self):
        self.timer.start(0, self)

    def timerEvent(self, event):
        frame = self.camera.getFrame(0)
        self.image_data.emit(frame)

class FaceTracker(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(FaceTracker, self).__init__()
        script_dir = path.dirname(path.realpath(__file__))
        cascade_filepath = path.join(script_dir,
                                  'data',
                                  'haar.xml')
        haar_cascade_filepath = path.abspath(cascade_filepath)
        self.classifier = cv2.CascadeClassifier(haar_cascade_filepath)
        self.image = QtGui.QImage()
        self._red = (0, 0, 255)
        self._width = 2
        self._min_size = (30, 30)
        self.dockWidth = self.width()
        self.dockHeight = self.height()
        
        
    def image_data_slot(self, image_data):
        self.image = self.get_qimage(image_data)
        self.update()

    def get_qimage(self, image):
        height, width, colors = image.shape
        bytesPerLine = 3 * width
        QImage = QtGui.QImage

        image = QImage(image.data,
                       width,
                       height,
                       bytesPerLine,
                       QImage.Format_RGB888)


        image = image.scaledToHeight(self.dockHeight)
        image = image.scaledToWidth(self.dockWidth)
        image = image.rgbSwapped()
        return image

    def paintEvent(self, event):
        painter = QtGui.QPainter(self)
        painter.drawImage(0, 0, self.image)
                
    def resizeEvent(self, event):
        self.dockWidth = self.width()
        self.dockHeight = self.height()

class FaceTrackerHolder(QtWidgets.QWidget):
    def __init__(self, haarcascade_filepath, parent=None):
        super(FaceTrackerHolder, self).__init__()
        fp = haarcascade_filepath
        self.face_detection_widget = FaceTracker(fp)

        self.record_video = RecordVideo()

        image_data_slot = self.face_detection_widget.image_data_slot
        self.record_video.image_data.connect(image_data_slot)

        layout = QtWidgets.QVBoxLayout()

        layout.addWidget(self.face_detection_widget)

        self.record_video.start_recording()
        self.setLayout(layout)