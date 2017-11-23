import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf

# Load and prepare data by the following 2 lines of code (a piece of cake!)
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets("MNIST_data/", one_hot=True)

# Declare the placeholder for the data (i.e., images) and target (i.e., 10-length vector)
x_data = tf.placeholder(shape=[None, 784], dtype=tf.float32)
y_target = tf.placeholder(shape=[None, 10], dtype=tf.float32)

# Declare our neural network
hidden_layer_nodes = 10
W1 = tf.Variable(tf.random_normal(shape=[784, hidden_layer_nodes]))
b1 = tf.Variable(tf.random_normal(shape=[hidden_layer_nodes]))
W2 = tf.Variable(tf.random_normal(shape=[hidden_layer_nodes, 10]))
b2 = tf.Variable(tf.random_normal(shape=[10]))

hidden_output = tf.nn.relu(tf.add(tf.matmul(x_data, W1), b1))
final_output = tf.nn.relu(tf.add(tf.matmul(hidden_output, W2), b2))

# Loss function
loss = tf.reduce_mean(tf.square(y_target - final_output))


# Declare optimizing algorithm
opt = tf.train.GradientDescentOptimizer(learning_rate=0.005)
train_step = opt.minimize(loss)
init = tf.global_variables_initializer()

sess = tf.Session()
sess.run(init)

# Training iterations
batch_size = 50
iter_count = 1000
train_accuracies = []
test_accuracies = []
for i in range(iter_count):
    # run the training step
    rand_x, rand_y = mnist.train.next_batch(batch_size)
    sess.run(train_step, feed_dict={x_data: rand_x, y_target: rand_y})
    temp_loss = sess.run(loss, feed_dict={x_data: rand_x, y_target: rand_y})
    train_accuracies.append(np.sqrt(temp_loss))

    test_temp_loss = sess.run(loss, feed_dict={x_data: mnist.test.images, y_target: mnist.test.labels})
    test_accuracies.append(np.sqrt(test_temp_loss))
    if (i+1) % 10 == 0:
        print("Generation: %d. Loss = %f" %(i+1, temp_loss))


plt.plot(train_accuracies, 'k-', label='Train Loss')
plt.plot(test_accuracies, 'r--', label='Test Loss')
plt.title('Loss (MSE) per Generation')
plt.xlabel('Generation')
plt.ylabel('Loss')
plt.legend(loc='upper right')
plt.show()