# -*- coding:utf-8 -*-

import cv2
import numpy as np
import matplotlib.pyplot as plt
img = cv2.imread('daye.png')
# res = cv2.resize(img,None,fx=0.5, fy=0.5, interpolation = cv2.INTER_CUBIC)
# M = np.float32([[1,0,200],[0,1,200]])
# rows,cols = res.shape[:2]
# res = cv2.warpAffine(res,M,(cols,rows))
# cv2.imshow('1',res)
# M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
# res = cv2.warpAffine(res,M,(rows*2,cols))
# cv2.imshow('img',res)
# cv2.waitKeyEx(0)

###########################仿射变换
# rows,cols,ch = img.shape
# pts1 = np.float32([[50,50],[50,250],[250,50]])
# pts2 = np.float32([[30,70],[80,200],[200,20]])
# M = cv2.getAffineTransform(pts1,pts2)
# dst = cv2.warpAffine(img,M,(cols,rows))
# plt.subplot(121),plt.imshow(img),plt.title('Input')
# plt.subplot(122),plt.imshow(dst),plt.title('Output')
# plt.show()
###########################角度变化
rows,cols,ch = img.shape
pts1 = np.float32([[100,0],[100,1079],[500,0],[1500,1079]])
pts2 = np.float32([[0,0],[0,1079],[1400,0],[1400,1079]])
M = cv2.getPerspectiveTransform(pts1,pts2)
dst = cv2.warpPerspective(img,M,(1400,1080))
plt.subplot(121),plt.imshow(img),plt.title('Input')
plt.subplot(122),plt.imshow(dst),plt.title('Output')
plt.show()