# -*- coding:utf-8 -*-

import cv2
import numpy as np

def draw_circle(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDBLCLK:
        # print('position ',x,y,'color',frame[y,x])
        tmp = np.uint8([[frame[y,x]]])
        print(cv2.cvtColor(tmp,cv2.COLOR_BGR2HSV))

cap = cv2.VideoCapture('nv.mp4')

while(1):
    # Take each frame
    ret, frame = cap.read()
    if ret == False:break
    cv2.namedWindow('frame')
    cv2.setMouseCallback('frame', draw_circle)
    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # define range of blue color in HSV
    lower_blue = np.array([0,15,60])
    upper_blue = np.array([20,90,200])
    # Threshold the HSV image to get only blue colors
    mask = cv2.inRange(hsv, lower_blue, upper_blue)
    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)
    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('res',res)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
cv2.destroyAllWindows()