# coding=utf-8

# from tensorflow.examples.tutorials.mnist import input_data
# mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

import os
import pickle
import numpy as np
import random
import cv2
import tensorflow as tf




def getPaddingSize(img):
    h, w, _ = img.shape
    top, bottom, left, right = (0,0,0,0)
    longest = max(h, w)

    if w < longest:
        tmp = longest - w
        # //表示整除符号
        left = tmp // 2
        right = tmp - left
    elif h < longest:
        tmp = longest - h
        top = tmp // 2
        bottom = tmp - top
    else:
        pass
    return top, bottom, left, right

def readData(path,filename , h=64, w=64):
    img = cv2.imread(path+'\\'+filename)

    top,bottom,left,right = getPaddingSize(img)
    # 将图片放大， 扩充图片边缘部分
    img = cv2.copyMakeBorder(img, top, bottom, left, right, cv2.BORDER_CONSTANT, value=[0,0,0])
    img = cv2.resize(img, (h, w))/255
    return img.tolist()

xiaoping = [1,0]
other = [0,1]
data = []
answer = []
for file in os.listdir('xiaoping'):
    data.append(readData('xiaoping',file))
    answer.append(xiaoping)
for file in os.listdir('other'):
    data.append(readData('other',file))
    answer.append(other)

x = tf.placeholder(tf.float32, shape=[None, 64 , 64 ,3])
y_ = tf.placeholder(tf.float32, shape=[None, 2])
def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)
def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')
W_conv1 = weight_variable([5, 5, 3, 32])
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)

W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

W_conv3 = weight_variable([5, 5, 64, 64])
b_conv3 = bias_variable([64])
h_conv3 = tf.nn.relu(conv2d(h_pool2, W_conv3) + b_conv3)
h_pool3 = max_pool_2x2(h_conv3)

W_fc1 = weight_variable([8 * 8 * 64, 1024])
b_fc1 = bias_variable([1024])
h_pool3_flat = tf.reshape(h_pool3, [-1, 8*8*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool3_flat, W_fc1) + b_fc1)
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

W_fc2 = weight_variable([1024, 2])
b_fc2 = bias_variable([2])

y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

cross_entropy = tf.reduce_mean(
    tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=y_conv))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

tf.summary.scalar('loss', cross_entropy)
tf.summary.scalar('accuracy', accuracy)
merged_summary_op = tf.summary.merge_all()


with tf.Session() as sess:
  sess.run(tf.global_variables_initializer())
  saver = tf.train.Saver()
  for i in range(101):
    # batch = mnist.train.next_batch(50)
    # batch = next_batch(i,50)
    if i % 100 == 0:
      train_accuracy = accuracy.eval(feed_dict={
          x: data, y_: answer, keep_prob: 1.0})
      print('step %d, training accuracy %g' % (i, train_accuracy))
    train_step.run(feed_dict={x: data, y_: answer, keep_prob: 0.5})
  # saver.restore(sess=sess,save_path='mnist/ckp')
  # print('test accuracy %g' % accuracy.eval(feed_dict={
  #        x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))
  # print('test accuracy %g' % accuracy.eval(feed_dict={
  #        x: l_test[0], y_: l_test[1], keep_prob: 1.0}))
  # 创建模型保存目录
  model_dir = "renlian"
  model_name = "ckp"
  if not os.path.exists(model_dir):
      os.mkdir(model_dir)
  # 保存模型
  saver.save(sess, os.path.join(model_dir, model_name))