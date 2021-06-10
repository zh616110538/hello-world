import threading
from queue import Queue
import time

# 4.使用Queue队列来创建线程池
# 最常用的方法是put和get

class CustomThread(threading.Thread):
    # 初始化属性
    def __init__(self, queue,number):
        threading.Thread.__init__(self)
        self.__queue = queue
        self.number = number                # 线程编号

    # 要执行的话就需要去队列里面取了get
    def run(self):
        print('启动%d号线程' % self.number)
        while True:
            q_method = self.__queue.get()
            q_method()
            self.__queue.task_done()

# 创建线程池-Queue队列
def queue_pool():
    queue = Queue(10)                     # 创建一个长度为10的队列
    for i in range(queue.maxsize):       # 根据队列的长度创建了线程
        t = CustomThread(queue,i+1)      # 初始化
        t.setDaemon(True)               # 每个线程都设置为守护状态=即需要时马上执行
        t.start()                       # 启动线程
    for i in range(20):
        queue.put(job)               # put方法=把我们想做的事情往队列里面塞
    queue.join()

# 想做的事情
def job():
    print(" 开始搬砖 %s" % (time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))

if __name__ == '__main__':
    queue_pool()
