import tensorflow as tf

a = tf.placeholder(tf.float32)
b = tf.placeholder(tf.float32)
c = tf.add(a, b)
d = tf.subtract(b, 1)
e = tf.multiply(c, d)

sess = tf.Session()
a_data, b_data = 3.0, 6.0
feed_dict = {a: a_data, b:b_data}
output = sess.run(e, feed_dict={a: 3.0, b:6.0})
intermediate = sess.run(c, feed_dict={a: 3.0, b:6.0})
input = sess.run(a, feed_dict={a:3.0, b:6.0})
print(e)
print(c)
print(output)
print(intermediate)
print(input)