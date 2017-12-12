import requests
from bs4 import BeautifulSoup
import os
import traceback
import re
import time
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


if os.path.exists('imgjd') is False:
    os.makedirs('imgjd')

start = 1
end = 348
for i in range(start, end + 1):
    url = 'http://www.jdlingyu.fun/page/%d/' % i
    html = requests.get(url).text
    # print(html)
    soup = BeautifulSoup(html, 'html.parser')
    for target in soup.find_all('a', class_="viewsButton"):
        # print(target)
        target_url = target['href']
        # print(target_url)
        target_html = requests.get(target_url).text
        # print(target_html)
        soup = BeautifulSoup(target_html, 'html.parser')
        for img in soup.find_all([re.compile('img')]):
            # print(str(img))
            target_url = re.search(r'data-original="([^\s]+)"',str(img))
            if(target_url):
                # print(target_url.group(1))
                target_url = target_url.group(1)
            # target_url = img[r"data-original"]
            # print(target_url)
            # print(target_url)
                name = re.search(r'/([^/]+)$', target_url).group(1)
                # print(name)
                filename = 'imgjd/' + name
                download(target_url, filename)
        # time.sleep(1)
    print('%d / %d' % (i, end))