import requests
from bs4 import BeautifulSoup
import os
import traceback
import re
def download(url, filename):
    if os.path.exists(filename):
        print('file exists!')
        return
    try:
        r = requests.get(url, stream=True, timeout=60)
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


if os.path.exists('imgs') is False:
    os.makedirs('imgs')

start = 1
end = 27
for i in range(start, end + 1):
    url = 'http://www.noen.com.cn/page/%d' % i
    html = requests.get(url).text
    # print(html)
    soup = BeautifulSoup(html, 'html.parser')
    for target in soup.find_all('a', class_="thumbnail"):
        # print(target)
        target_url = target['href']
        target_html = requests.get(target_url).text
        soup = BeautifulSoup(target_html, 'html.parser')
        for img in soup.find_all("img",class_=re.compile('aligncenter size-full.+')):
            # print(img)
            target_url = img['src']
            print(target_url)
            # print(target_url)
            filename = os.path.join('imgs', target_url.split('/')[-1])
            print(filename)
            download(target_url, filename)
    print('%d / %d' % (i, end))