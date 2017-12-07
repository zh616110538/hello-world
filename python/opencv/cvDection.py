import cv2
import os

files = os.listdir("xiaoping")

face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
# eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')


for file in files:
    file = "xiaoping/" + file
    print(file)
    frame = cv2.imread(file)
    print(frame)
    frame = cv2.resize(frame,None,fx=0.2,fy=0.2,interpolation=cv2.INTER_CUBIC)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
        roi_gray = gray[y:y + h, x:x + w]
        roi_color = frame[y:y + h, x:x + w]
        # eyes = eye_cascade.detectMultiScale(roi_gray)
        # for (ex, ey, ew, eh) in eyes:
        #     cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)



    cv2.imshow('img',frame)
    cv2.waitKey(0)
    cv2.destroyAllWindows()