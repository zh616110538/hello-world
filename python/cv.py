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
cap = cv2.VideoCapture("rtsp://admin:zh619903769.@192.168.0.64:554//Streaming/Channels/1")
# cap = cv2.VideoCapture('nv.mp4')
while(cap.isOpened()):
    face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
    eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = frame[y:y + h, x:x + w]
        # eyes = eye_cascade.detectMultiScale(roi_gray)
        # for (ex, ey, ew, eh) in eyes:
        #     cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)

    # cv2.imshow('frame',frame)
    # if ret == False:
    #     break
    # else:
    #     frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # (h, w) = frame.shape[:2]
    # print(frame.shape)
    # center = (w / 2, h / 2)
    # 旋转45度，缩放0.75
    # M = cv2.getRotationMatrix2D(center, -90, 0.3)  # 旋转缩放矩阵：(旋转中心，旋转角度，缩放因子)
    # rotated = cv2.warpAffine(frame, M, (w, h))
    # cv2.waitKey(0)
    # 旋转-45度，缩放1.25

    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()