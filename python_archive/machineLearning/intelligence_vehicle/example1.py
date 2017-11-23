import tensorflow as tf

row_dim = 3
col_dim = 4

# declare tensors
ts1 = tf.zeros([row_dim, col_dim], name='zero_tensor')
ts2 = tf.ones([64, 64, 1])
ts3 = tf.fill([row_dim, col_dim], 42)
ts4 = tf.constant([1., 2., 3.])

ts5 = tf.zeros_like(ts4)
ts6 = tf.ones_like(ts4)

ts7 = tf.random_uniform([row_dim, col_dim], minval=0, maxval=1)

print(ts1)
print(ts7)


# declare variables
w = tf.Variable(tf.constant(4.))
W1 = tf.Variable(tf.random_normal(shape=[3, 5]))

print(w)
print(W1)

# declare placeholders
x = tf.placeholder(tf.float32, shape=[2, 2])
a = tf.placeholder(tf.float32)

print(x)
print(a)

