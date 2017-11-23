import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from sklearn import datasets

iris = datasets.load_iris()
x_vals = np.array([x[0:3] for x in iris.data])
y_vals = np.array([x[3] for x in iris.data])
sess = tf.Session()

# to set a seed to make the results reproducible (i.e., to be the same)
seed = 3
tf.set_random_seed(seed)
np.random.seed(seed)


# Create a 80-20 train-test split and normalize the x features to be between 0 and 1
train_indices = np.random.choice(len(x_vals), round(len(x_vals)*0.8), replace=False)
test_indices = np.array(list(set(range(len(x_vals))) - set(train_indices)))
x_vals_train = x_vals[train_indices]
x_vals_test = x_vals[test_indices]
y_vals_train = y_vals[train_indices]
y_vals_test = y_vals[test_indices]


def normalize_cols(m):
    col_max = m.max(axis=0)
    col_min = m.min(axis=0)
    return (m-col_min) / (col_max - col_min)


x_vals_train = np.nan_to_num(normalize_cols(x_vals_train))
x_vals_test = np.nan_to_num(normalize_cols(x_vals_test))


# Declare the placeholder for the data and target
x_data = tf.placeholder(shape=[None, 3], dtype=tf.float32)
y_target = tf.placeholder(shape=[None, 1], dtype=tf.float32)


# Declare our neural network
hidden_layer_nodes = 10
W1 = tf.Variable(tf.random_normal(shape=[3, hidden_layer_nodes]))
b1 = tf.Variable(tf.random_normal(shape=[hidden_layer_nodes]))
W2 = tf.Variable(tf.random_normal(shape=[hidden_layer_nodes, 1]))
b2 = tf.Variable(tf.random_normal(shape=[1]))

# Declare outputs
hidden_output = tf.nn.relu(tf.add(tf.matmul(x_data, W1), b1))
final_output = tf.nn.relu(tf.add(tf.matmul(hidden_output, W2), b2))

# Loss function
loss = tf.reduce_mean(tf.square(y_target - final_output))

# Declare optimizing algorithm
opt = tf.train.GradientDescentOptimizer(learning_rate=0.005)
train_step = opt.minimize(loss)
init = tf.global_variables_initializer()
sess.run(init)

# Training iterations
batch_size = 50
iter_count = 500
train_loss = []
test_loss = []
for i in range(iter_count):
    # select a random set for the batch
    rand_index = np.random.choice(len(x_vals_train), size=batch_size)
    rand_x = x_vals_train[rand_index]
    rand_y = np.transpose([y_vals_train[rand_index]])

    # run the training step
    sess.run(train_step, feed_dict={x_data: rand_x, y_target: rand_y})
    temp_loss = sess.run(loss, feed_dict={x_data: rand_x, y_target: rand_y})
    train_loss.append(np.sqrt(temp_loss))

    test_temp_loss = sess.run(loss, feed_dict={x_data: x_vals_test, y_target: np.transpose([y_vals_test])})
    test_loss.append(np.sqrt(test_temp_loss))
    if (i+1) % 10 == 0:
        print("Generation: %d. Loss = %f" %(i+1, temp_loss))


plt.plot(train_loss, 'k-', label='Train Loss')
plt.plot(test_loss, 'r--', label='Test Loss')
plt.title('Loss (MSE) per Generation')
plt.xlabel('Generation')
plt.ylabel('Loss')
plt.legend(loc='upper right')
plt.show()


