# Loading TensorFlow and creating a graph session
import tensorflow as tf
sess = tf.Session()


# Declare our model variable, input data, and placeholder
# We keep our input to be the value 5, so w should ideally be 10.
x_val = 5.0
target_val = 50.0
iter_count = 20
w = tf.Variable(tf.constant(4.0))
b = tf.Variable(tf.constant(5.0))
x_data = tf.placeholder(dtype=tf.float32)

# Add the multiplication operator and the addition operator to the graph
mult = tf.multiply(w, x_data)
a = tf.add(mult, b)

# Initialize variables
init = tf.global_variables_initializer()
sess.run(init)

# Declare the loss function
loss = tf.square(tf.subtract(a, target_val))


# Specify the optimizing algorithm
opt = tf.train.GradientDescentOptimizer(learning_rate=0.01)
train_step = opt.minimize(loss)


# Now, we are ready to optimize out model output towards the target value of 50
for i in range(iter_count):
    sess.run(train_step, feed_dict={x_data: x_val})
    w_val = sess.run(w)
    b_val = sess.run(b)
    a_val = sess.run(a, feed_dict={x_data:x_val})
    loss_val = sess.run(loss, feed_dict={x_data:x_val})
    print("%f * %f + %f = %f, loss=%f" %(w_val, x_val, b_val, a_val, loss_val))