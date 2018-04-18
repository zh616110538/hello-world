# -*- coding:utf-8 -*-

import urllib
import os
import requests
import re
from lxml import etree
import time
import datetime
import math
import sqlite3
from win32.win32crypt import CryptUnprotectData

def getcookiefromchrome(host='.oschina.net'):
    cookiepath=os.environ['LOCALAPPDATA']+r"\Google\Chrome\User Data\Default\Cookies"
    sql="select host_key,name,encrypted_value from cookies where host_key='%s'" % host
    with sqlite3.connect(cookiepath) as conn:
        cu=conn.cursor()
        cookies={name:CryptUnprotectData(encrypted_value)[1].decode() for host_key,name,encrypted_value in cu.execute(sql).fetchall()}
        #print(cookies)
        return cookies

def lefttime(dt):
    return dt - time.time()

def f1(x):
    if x<0:
        return 0.3
    elif x > 120:
        return 12
    else:
        return 0.095*x+0.5

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.146 Safari/537.36",
    'Upgrade-Insecure-Requests':'1'
}

cookies1=getcookiefromchrome(r'bilibili.com')
cookies2=getcookiefromchrome(r'.bilibili.com')
cookies3=getcookiefromchrome(r'www.bilibili.com')
#cookies4=getcookiefromchrome(r'bilibili.com')
cookies = dict(cookies1,**cookies2,**cookies3)
cookies.pop('CNZZDATA2724999')
cookies.pop('_dfcaptcha')


url = input("链接地址\n")
month = input("输入month\n")
date = input("输入date\n")
hour = input("输入hour\n")
minute = input("输入minute\n")
message = input("输入 评论内容\n")


dt = datetime.datetime(2018, int(month), int(date), int(hour), int(minute)).timestamp()

while lefttime(dt) > 1:
    time.sleep(1)

while True:
    request = requests.get(url,headers=headers)
    if request.status_code != 404:
        av = re.search(r'AV(\d+)', request.text)
        if av == None:
            continue
        break
    time.sleep(f1(lefttime(dt)))
#print(request.status_code)
# print(request.status_code)

data = {
    'oid':av.group(1),
    'type':'1',
    'message':message,
    'plat':'1',
    'jsonp':'jsonp',
    'csrf':cookies['bili_jct']
}
requests.post('https://api.bilibili.com/x/v2/reply/add',headers=headers,cookies=cookies,data=data)
# os.system('shutdown -s -t 10')