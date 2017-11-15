import os
import pickle
import numpy as np
import random
import tensorflow as tf

f = open('somedata', 'rb')
l = pickle.load(f)
f.close()
f = open('testdata', 'rb')
l_test = pickle.load(f)
f.close()


def next_batch(i,n):
  return l[0][i*n%60000:i*n%60000+n],l[1][i*n%60000:i*n%60000+n]

LAYER1 = 30

x = tf.placeholder(tf.float32,[None,784],'x-input')
y_ = tf.placeholder(tf.float32,[None,10],'y-input')

weights1 = tf.Variable(tf.truncated_normal([784,LAYER1],stddev=100))
biases1 = tf.Variable(tf.truncated_normal([LAYER1]))

weights2 = tf.Variable(tf.truncated_normal([LAYER1,10],stddev=100))
biases2 = tf.Variable(tf.truncated_normal([10]))

z1 = tf.matmul(x,weights1)+biases1
a1 = tf.nn.relu(z1)
z2 = tf.matmul(a1,weights2)+biases2
y = tf.nn.relu(z2)

cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=y))
train_step = tf.train.GradientDescentOptimizer(100).minimize(cross_entropy)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(30000):
        batch = next_batch(i,100)
        sess.run(train_step, feed_dict={x: batch[0], y_: batch[1]})
        if i%100 == 0:
            correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
            accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
            print(i," ",sess.run(accuracy, feed_dict={x: l_test[0], y_: l_test[1]}))