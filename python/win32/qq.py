#-*- coding:utf-8 -*-
import win32api
import win32con
import win32gui
import win32ui
import time
import random
import os
import cv2
import numpy
from PIL import ImageGrab

def move_click(x, y, t = 0):  # 移动鼠标并点击左键
    win32api.SetCursorPos((x, y))  # 设置鼠标位置(x, y)
    if t==1:win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0)  # 点击鼠标左键
    if t==2:win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP, 0, 0, 0, 0)  # 点击鼠标左键
    if t==0:win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP | win32con.MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0)  # 点击鼠标左键

def keybd_click(l):
    for i in l:
        win32api.keybd_event(i, 0, 0, 0)
    for i in reversed(l):
        win32api.keybd_event(i, 0, win32con.KEYEVENTF_KEYUP, 0)
    time.sleep(0.1)


# keybd_click([17,18,ord('Z')])
# time.sleep(0.5)
# s = 'HAIZEI \rHAIZEI NIUBI \r'
# keybd_click([16,50])
# for i in s:
#     time.sleep(0.2)
#     keybd_click([ord(i)])

# for char in 'Hello, 世界':
#     win32gui.SendMessage(qq, win32con.WM_CHAR, ord(char), None)

qq = win32gui.FindWindow(None, "QQ")
y_shift = 128
x_shift = 85
left, top, right, bottom = win32gui.GetWindowRect(qq)

# win32gui.SetWindowPos(qq,win32con.HWND_TOPMOST,0,0,0,0,win32con.SWP_NOMOVE|win32con.SWP_NOSIZE|win32con.SWP_ACTIVATE)
win32gui.ShowWindow(qq,win32con.SW_SHOWNORMAL)
move_click(left+x_shift,top+y_shift)
time.sleep(0.5)

for char in '181447148':
    time.sleep(0.1)
    win32gui.SendMessage(qq, win32con.WM_CHAR, ord(char), None)

time.sleep(0.5)
keybd_click([13])
time.sleep(0.5)

win32gui.SetWindowPos(qq,win32con.HWND_TOPMOST,0,0,0,0,win32con.SWP_NOMOVE|win32con.SWP_NOSIZE|win32con.SWP_NOACTIVATE|win32con.SWP_HIDEWINDOW|win32con.SWP_NOOWNERZORDER)
tt = win32gui.FindWindow(None, "逐日者-天庭")
win32gui.ShowWindow(tt,win32con.SW_SHOWNORMAL)

#keybd_click([17,18,ord('Z')])
time.sleep(0.5)
s = '907427137'
keybd_click([16,50])
for char in s:
    time.sleep(0.1)
    win32gui.SendMessage(tt, win32con.WM_CHAR, ord(char), None)
keybd_click([13])
s = '海贼牛逼'
for char in s:
    time.sleep(0.1)
    win32gui.SendMessage(tt, win32con.WM_CHAR, ord(char), None)

# hwndChildList = []
# win32gui.EnumChildWindows(handle, lambda hwnd, param: param.append(hwnd),  hwndChildList)
# subHandle = hwndChildList[1]
# bufSize = win32api.SendMessage(subHandle, win32con.WM_GETTEXTLENGTH, 0, 0) +1
# # 利用api生成Buffer
# strBuf = win32gui.PyMakeBuffer(bufSize)
# print(strBuf)
# # 发送消息获取文本内容
# # 参数：窗口句柄； 消息类型；文本大小； 存储位置
# length = win32gui.SendMessage(subHandle, win32con.WM_GETTEXT, bufSize, strBuf)
# # 反向内容，转为字符串
# # text = str(strBuf[:-1])
#
# address, length = win32gui.PyGetBufferAddressAndLen(strBuf)
# text = win32gui.PyGetString(address, length)
# print(text)