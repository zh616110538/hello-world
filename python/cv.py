# -*- coding:utf-8 -*-

# import numpy as np
# import cv2
# img = cv2.imread('daye.png',0)
# cv2.imshow('image',img)
# k = cv2.waitKey(0)
# if k == 27:         # wait for ESC key to exit
#     cv2.destroyAllWindows()
# elif k == ord('s'): # wait for 's' key to save and exit
#     cv2.imwrite('daye1.png',img)
#     cv2.destroyAllWindows()


# import numpy as np
# import cv2
# from matplotlib import pyplot as plt
# img = cv2.imread('daye.png')
# cv2.imshow('image',img)
# cv2.waitKeyEx()


import numpy as np
import cv2
cap = cv2.VideoCapture('nv.mp4')

while(cap.isOpened()):
    ret, frame = cap.read()

    # cv2.imshow('frame',frame)
    if ret == False:
        break
    else:
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    (h, w) = frame.shape[:2]
    # print(frame.shape)
    center = (w / 2, h / 2)
    # 旋转45度，缩放0.75
    M = cv2.getRotationMatrix2D(center, -90, 0.3)  # 旋转缩放矩阵：(旋转中心，旋转角度，缩放因子)
    rotated = cv2.warpAffine(frame, M, (w, h))
    # cv2.waitKey(0)
    # 旋转-45度，缩放1.25

    cv2.imshow('frame',rotated)
    if cv2.waitKey(17) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()