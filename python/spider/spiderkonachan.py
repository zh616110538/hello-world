import requests
from bs4 import BeautifulSoup
import os
import traceback
import re
import time
proxies = {
    'http': 'http://127.0.0.1:1081',
    'https': 'https://127.0.0.1:1081'
}

def download(url, filename):
    if os.path.exists(filename):
        print('file exists!')
        return
    try:
        r = requests.get(url, stream=True, timeout=60,proxies=proxies)
        r.raise_for_status()
        with open(filename, 'wb') as f:
            for chunk in r.iter_content(chunk_size=1024):
                if chunk:  # filter out keep-alive new chunks
                    f.write(chunk)
                    f.flush()
        return filename
    except KeyboardInterrupt:
        if os.path.exists(filename):
            os.remove(filename)
        raise KeyboardInterrupt
    except Exception:
        traceback.print_exc()
        if os.path.exists(filename):
            os.remove(filename)

def getFileSize(filePath, size=0):
    for root, dirs, files in os.walk(filePath):
        for f in files:
            size += os.path.getsize(os.path.join(root, f))
    return size

if os.path.exists('imganime') is False:
    os.makedirs('imganime')

start = 474

if os.path.exists('record.dat'):
    with open('record.dat','r') as f:
        start = int(f.read())

#start = 238
end = 9620
for i in range(start, end + 1):
    url = 'http://konachan.net/post?page=%d&tags=' % i
    html = None
    try:
        html = requests.get(url,proxies=proxies).text
    except Exception:
        traceback.print_exc()
    if html == None:
        continue
    soup = BeautifulSoup(html, 'html.parser')
    for target in soup.find_all('a', class_="directlink smallimg"):
        target_url = 'http:'+ target['href']
        print(target_url)
        filename = os.path.join('imganime', target_url.split('/')[-1])
        download(target_url, filename)
    for target in soup.find_all('a', class_="directlink largeimg"):
        target_url = 'http:'+ target['href']
        print(target_url)
        filename = os.path.join('imganime', target_url.split('/')[-1])
        download(target_url, filename)
    # print(count)
    if getFileSize('imganime')/1024/1024/1024 > 100:
        os.system("shutdown -s -t 1")
        os.system("pause")
    print('%d / %d .time %s' % (i, end,time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
    with open('record.dat','w') as f:
        f.write(str(i))