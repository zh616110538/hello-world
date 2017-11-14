import cv2
import numpy as np
import matplotlib.pyplot as plt

# def draw_circle(event,x,y,flags,param):
#     if event == cv2.EVENT_LBUTTONDBLCLK:
#         print(x,y)
#
# img = cv2.imread('test.jpg')
# img = cv2.resize(img,None,fx=0.25,fy=0.25,interpolation=cv2.INTER_CUBIC)
# # cv2.namedWindow('image')
# # cv2.setMouseCallback('image',draw_circle)
# cv2.imshow('image1',img)
# # cv2.waitKeyEx(0)
# rows,cols,ch = img.shape
# pts1 = np.float32([[202,209],[122,956],[685,220],[746,957]])
# pts2 = np.float32([[0,0],[0,700],[400,0],[400,700]])
# M = cv2.getPerspectiveTransform(pts1,pts2)
# dst = cv2.warpPerspective(img,M,(400,700))
# # plt.subplot(121),plt.imshow(img),plt.title('Input')
# # plt.subplot(122),plt.imshow(dst),plt.title('Output')
# # plt.show()
# cv2.imshow('image',dst)
# cv2.waitKeyEx(0)

# import cv2
# import numpy as np
# from matplotlib import pyplot as plt
# img = cv2.imread('test.jpg',0)
# ret,thresh1 = cv2.threshold(img,127,255,cv2.THRESH_BINARY)
# ret,thresh2 = cv2.threshold(img,127,255,cv2.THRESH_BINARY_INV)
# ret,thresh3 = cv2.threshold(img,127,255,cv2.THRESH_TRUNC)
# ret,thresh4 = cv2.threshold(img,127,255,cv2.THRESH_TOZERO)
# ret,thresh5 = cv2.threshold(img,127,255,cv2.THRESH_TOZERO_INV)
# titles = ['Original Image','BINARY','BINARY_INV','TRUNC','TOZERO','TOZERO_INV']
# images = [img, thresh1, thresh2, thresh3, thresh4, thresh5]
# for i in range(6):
#     plt.subplot(2,3,i+1),plt.imshow(images[i],'gray')
#     plt.title(titles[i])
#     plt.xticks([]),plt.yticks([])
# plt.show()

import cv2
import numpy as np
from matplotlib import pyplot as plt
# img = cv2.imread('test.jpg',0)
# img = cv2.medianBlur(img,5)
# ret,th1 = cv2.threshold(img,127,255,cv2.THRESH_BINARY)
# th2 = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
# th3 = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,11,2)
# titles = ['Original Image', 'Global Thresholding (v = 127)',
#             'Adaptive Mean Thresholding', 'Adaptive Gaussian Thresholding']
# images = [img, th1, th2, th3]
# for i in range(4):
#     plt.subplot(2,2,i+1),plt.imshow(images[i],'gray')
#     plt.title(titles[i])
#     plt.xticks([]),plt.yticks([])
# plt.show()

import cv2
import numpy as np
from matplotlib import pyplot as plt
img = cv2.imread('noise.png')
kernel = np.ones((5,5),np.float32)/25
# dst = cv2.filter2D(img,-1,kernel)
# dst = cv2.blur(img,(5,5))
# dst = cv2.GaussianBlur(img,(5,5),0)
dst = cv2.medianBlur(img,5)
# dst = cv2.bilateralFilter(img,9,100,100)
plt.subplot(121),plt.imshow(img),plt.title('Original')
plt.xticks([]), plt.yticks([])
plt.subplot(122),plt.imshow(dst),plt.title('Averaging')
plt.xticks([]), plt.yticks([])
plt.show()