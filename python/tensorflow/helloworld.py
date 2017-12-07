# coding=utf-8

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

import os
import pickle
import numpy as np
import random
import tensorflow as tf
import cv2

# f = open('somedata.mydat', 'rb')
# l = pickle.load(f)
# f.close()
# f = open('testdata.mydat', 'rb')
# l_test = pickle.load(f)
# f.close()


# def next_batch(i,n):
#   return l[0][i*n%60000:i*n%60000+n],l[1][i*n%60000:i*n%60000+n]

x = tf.placeholder(tf.float32, shape=[None, 784])
y_ = tf.placeholder(tf.float32, shape=[None, 10])
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
W_conv1 = weight_variable([5, 5, 1, 32])
b_conv1 = bias_variable([32])
x_image = tf.reshape(x, [-1, 28, 28, 1])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
h_pool1 = max_pool_2x2(h_conv1)
W_conv2 = weight_variable([5, 5, 32, 64])
b_conv2 = bias_variable([64])

h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
h_pool2 = max_pool_2x2(h_conv2)

W_fc1 = weight_variable([7 * 7 * 64, 1024])
b_fc1 = bias_variable([1024])

h_pool2_flat = tf.reshape(h_pool2, [-1, 7*7*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
keep_prob = tf.placeholder(tf.float32)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)
W_fc2 = weight_variable([1024, 10])
b_fc2 = bias_variable([10])

y_conv = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

cross_entropy = tf.reduce_mean(
    tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=y_conv))
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
correct_prediction = tf.equal(tf.argmax(y_conv, 1), tf.argmax(y_, 1))
# print(correct_prediction)
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

answer = tf.argmax(y_conv, 1)[0]

tf.summary.scalar('loss',cross_entropy)
tf.summary.scalar('train accuracy',accuracy)
merge_summary_op = tf.summary.merge_all()

with tf.Session() as sess:
  sess.run(tf.global_variables_initializer())
  saver = tf.train.Saver()
  saver.restore(sess=sess, save_path='mnist/ckp')
  img = cv2.imread('4.png')
  img = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
  # img = np.asarray(img,dtype=np.uint8)
  # img = cv2.adaptiveThreshold(img,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,15,4)
  cv2.imshow('img', img)
  img = cv2.resize(img,(28,28))

  img = (255-np.asarray(img,dtype=np.float32))/255
  img = np.resize(img,(1,784))
  print(sess.run(answer,feed_dict={x:img,keep_prob:1.0}))
  cv2.waitKeyEx(0)
  # summary_writeer = tf.summary.FileWriter('mnist',graph=tf.get_default_graph())
  # for i in range(20000):
  #   batch = mnist.train.next_batch(50)
  #   # batch = next_batch(i,50)
  #   _,loss,summary = sess.run([train_step,cross_entropy,merge_summary_op],feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})
  #   summary_writeer.add_summary(summary,i)
  #   if i % 100 == 0:
  #     train_accuracy = accuracy.eval(feed_dict={
  #         x: batch[0], y_: batch[1], keep_prob: 1.0})
  #     print('step %d, training accuracy %g' % (i, train_accuracy))
  #
  # print('test accuracy %g' % accuracy.eval(feed_dict={
  #        x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))
  # # print('test accuracy %g' % accuracy.eval(feed_dict={
  # #        x: l_test[0], y_: l_test[1], keep_prob: 1.0}))
  # # 创建模型保存目录
  # model_dir = "mnist"
  # model_name = "ckp"
  # if not os.path.exists(model_dir):
  #     os.mkdir(model_dir)
  # # 保存模型
  # saver.save(sess, os.path.join(model_dir, model_name))