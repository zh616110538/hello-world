# -*- coding:utf-8 -*-

import urllib
import requests
from lxml import etree
from time import sleep

url = "https://www.qiushibaike.com/"
headers = {
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36"
}

request = requests.get(url,headers=headers)
#print(request.status_code)
html = etree.HTML(request.text)
img_list = html.xpath("//img")
for img in img_list:
    src = img.attrib.get("src")
    src = "http:"+ str(src)
    print(src)
