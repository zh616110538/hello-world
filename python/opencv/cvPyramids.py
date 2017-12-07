#-*- coding:utf-8 -*-

import cv2
import numpy as np

img = cv2.imread('messi.jpg')
lower_reso = cv2.pyrDown(img)
lower_reso = cv2.pyrDown(lower_reso)
lower_reso = cv2.pyrDown(lower_reso)
lower_reso1 = cv2.pyrUp(lower_reso)
lower_reso1 = cv2.pyrUp(lower_reso1)
lower_reso1 = cv2.pyrUp(lower_reso1)
cv2.imshow('img2',lower_reso1)
cv2.waitKeyEx(0)