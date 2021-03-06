# coding=utf-8

import random
import cv2
import numpy as np
import pickle
from matplotlib import pyplot as plt
from PIL import Image, ImageDraw, ImageFont, ImageFilter

_letter_cases = "abcdefghjkmnpqrstuvwxy"  # 小写字母，去除可能干扰的i，l，o，z
_upper_cases = _letter_cases.upper()  # 大写字母
_numbers = ''.join(map(str, range(0, 10)))  # 数字
# init_chars = ''.join((_letter_cases, _upper_cases, _numbers))
init_chars = ''.join((_numbers))

def create_validate_code(size=(28, 28),
                         chars=init_chars,
                         img_type="GIF",
                         mode="RGB",
                         bg_color=(255, 255, 255),
                         fg_color=(0, 0, 255),
                         font_size=18,
                         font_type="arial.ttf",
                         length=1,
                         draw_lines=True,
                         n_line=(1, 2),
                         draw_points=True,
                         point_chance=2):
    '''
    @todo: 生成验证码图片
    @param size: 图片的大小，格式（宽，高），默认为(120, 30)
    @param chars: 允许的字符集合，格式字符串
    @param img_type: 图片保存的格式，默认为GIF，可选的为GIF，JPEG，TIFF，PNG
    @param mode: 图片模式，默认为RGB
    @param bg_color: 背景颜色，默认为白色
    @param fg_color: 前景色，验证码字符颜色，默认为蓝色#0000FF
    @param font_size: 验证码字体大小
    @param font_type: 验证码字体，默认为 ae_AlArabiya.ttf
    @param length: 验证码字符个数
    @param draw_lines: 是否划干扰线
    @param n_lines: 干扰线的条数范围，格式元组，默认为(1, 2)，只有draw_lines为True时有效
    @param draw_points: 是否画干扰点
    @param point_chance: 干扰点出现的概率，大小范围[0, 100]
    @return: [0]: PIL Image实例
    @return: [1]: 验证码图片中的字符串
    '''

    width, height = size  # 宽， 高
    img = Image.new(mode, size, bg_color)  # 创建图形
    draw = ImageDraw.Draw(img)  # 创建画笔

    def get_chars():
        '''生成给定长度的字符串，返回列表格式'''
        return random.sample(chars, length)

    def create_lines():
        '''绘制干扰线'''
        line_num = random.randint(*n_line)  # 干扰线条数

        for i in range(line_num):
            # 起始点
            begin = (random.randint(0, size[0]), random.randint(0, size[1]))
            # 结束点
            end = (random.randint(0, size[0]), random.randint(0, size[1]))
            draw.line([begin, end], fill=(0, 0, 0))

    def create_points():
        '''绘制干扰点'''
        chance = min(100, max(0, int(point_chance)))  # 大小限制在[0, 100]

        for w in range(width):
            for h in range(height):
                tmp = random.randint(0, 100)
                if tmp > 100 - chance:
                    draw.point((w, h), fill=(0, 0, 0))

    def create_strs():
        '''绘制验证码字符'''
        c_chars = get_chars()
        strs = ' %s ' % ' '.join(c_chars)  # 每个字符前后以空格隔开

        font = ImageFont.truetype(font_type, font_size)
        font_width, font_height = font.getsize(strs)

        draw.text(((width - font_width) / 3, (height - font_height) / 3),
                  strs, font=font, fill=fg_color)

        return ''.join(c_chars)

    if draw_lines:
        create_lines()
    if draw_points:
        create_points()
    strs = create_strs()

    # 图形扭曲参数
    params = [1 - float(random.randint(1, 2)) / 100,
              0,
              0,
              0,
              1 - float(random.randint(1, 10)) / 100,
              float(random.randint(1, 2)) / 500,
              0.001,
              float(random.randint(1, 2)) / 500
              ]
    img = img.transform(size, Image.PERSPECTIVE, params)  # 创建扭曲

    img = img.filter(ImageFilter.EDGE_ENHANCE_MORE)  # 滤镜，边界加强（阈值更大）

    return img, strs


if __name__ == "__main__":
    l1 = np.zeros([10000,784],dtype=np.float32)
    l2 = np.zeros([10000,10],dtype=np.float32)

    for i in range(10000):
        code_img = create_validate_code()
        code_img[0].save("zhuhao.jpg")
    #     img = np.asarray(code_img[0])
    #     # cv2.imshow('img', img1)
    #     # cv2.waitKeyEx(0)
    #     img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #     # img = cv2.medianBlur(img, 3)
    #     # img[img>0] = 1
    #     # cv2.imshow('img',img)
    #     # cv2.waitKeyEx(0)
    #     b = np.zeros([1,10])
    #     b[0,int(code_img[1])] = 1
    #     l1[i] = np.asarray(img,dtype=np.float32).reshape(1,784)/255
    #     l2[i] = b
    # # l1.tolist()
    # # l2.tolist()
    # l = [l1,l2]
    # f = open('testdata.mydat','wb')
    # pickle.dump(l,f)
    # f.close()
    # f = open('somedata.mydat', 'wb')
    # pickle.dump(l,f)
    # f.close()
        # cv2.imshow('img',img)
        # print(code_img[1])
        # cv2.waitKeyEx(1000)
        # im2, contours, hierarchy = cv2.findContours(img, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        # cv2.drawContours(img, contours, -1, (0, 255, 0), 1)
        # ret, img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)
        # plt.subplot(221),plt.imshow(img1,'gray')
        # plt.title('qian')
        # plt.subplot(222),plt.imshow(img,'gray')
        # plt.title('hou')
        # img_inv = 255 - img
        # img_inv = np.uint8(img_inv > 0)
        # y = np.sum(img_inv,0)
        # plt.subplot(224), plt.plot(y)
        # plt.title('zuo')
        # plt.show()
        # code_img[0].save("zhuhao.jpg", "JPG")
