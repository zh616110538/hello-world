# -*- coding:utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0,50,0.5)
y_old = 0.06*x/(1+0.06*x)
y_new = 0.05*x/(1+0.05*x)

plt.plot(x,y_old,label="old version")
plt.plot(x,y_new,label="new version")
plt.xlabel('hujia')
plt.ylabel('jianshang')
plt.legend()
plt.show()


# import numpy as np
# import matplotlib.pyplot as plt
# fig = plt.figure(dpi=80)
# x = np.linspace(0,10,100)
# plt.plot(x,np.sin(x),label="sin(x)")    #先设置一个label用于显示图例
# plt.xlabel("X axe")     #设置X轴的文字
# plt.ylabel("Y axe")     #设置Y轴的文字
# plt.title("sin(x) function")    #设置图的标题
# plt.legend()                        #显示图例。
# plt.show()