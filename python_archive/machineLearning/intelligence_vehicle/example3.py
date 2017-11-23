import tensorflow as tf

var = tf.Variable(tf.zeros([2, 3]))

sess = tf.Session()
init = tf.global_variables_initializer()
sess.run(init)

print(var)
print(sess.run(var))