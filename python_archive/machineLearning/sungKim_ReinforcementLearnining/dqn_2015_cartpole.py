#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> SungKim RL, DQN 2013 version을 작성 후 돌려본 코드
                           1. Go Deep
                           2. Capture & Replay
                                to solve Correlation between samples
                           3. Separate Network
                                Non-stationary targets

                            위 3가지 방법이 전부 구현된 코드
'''
import numpy as np
import tensorflow as tf
import random
import dqn
from collections import deque

import gym

env = gym.make('CartPole-v0')

# 새로운 gym 버전에서 step을 최대 200으로 막아놨으므로 아래 코드를 추가해야 정상작동한다
env._max_episode_steps = 10001

input_size = env.observation_space.shape[0]
output_size = env.action_space.n

dis = 0.9
REPLAY_MEMORY = 50000


# mainDQN ==> targetDQN 가중치를 복사하는 함수 (복잡해보이지만 그냥 복사하는것)
def get_copy_var_ops(*, dest_scope_name="target", src_scope_name="main"):
    # Copy variables src_scope to dest_scope
    op_holder = []
    
    # 모든 훈련가능한 Weight들을 scope에서 가져온다
    src_vars = tf.get_collection(
            tf.GraphKeys.TRAINABLE_VARIABLES, scope=src_scope_name)
    dest_vars = tf.get_collection(
            tf.GraphKeys.TRAINABLE_VARIABLES, scope=dest_scope_name)

    for src_var, dest_var in zip(src_vars, dest_vars):
        op_holder.append(dest_var.assign(src_var.value()))

    return op_holder


# 실제로 DQN을 학습하는 함수. targetDQN, mainDQN을 분리시켰다
def replay_train(mainDQN, targetDQN, train_batch):
    x_stack = np.empty(0).reshape(0, input_size)
    y_stack = np.empty(0).reshape(0, output_size)

    for state, action, reward, next_state, done in train_batch:
        Q = mainDQN.predict(state)

        # terminal?
        if done:
            Q[0, action] = reward
        else:
          #  Q[0, action] = reward + dis*np.max(targetDQN.predict(next_state))
            Q[0, action] = reward + dis*targetDQN.predict(next_state)[0, np.argmax(mainDQN.predict(next_state))]

        y_stack = np.vstack([y_stack, Q])
        x_stack = np.vstack([x_stack, state])

    return mainDQN.update(x_stack, y_stack)



# 학습이 끝나고 실제로 mainDQN Network로 CartPole을 돌려보는 함수
def bot_play(mainDQN):
    s = env.reset()
    reward_sum = 0

    while True:
        env.render()
        a = np.argmax(mainDQN.predict(s))
        s, reward, done, _ = env.step(a)
        reward_sum += reward

        if done:
            print("Total score: {}".format(reward_sum))
            break



def main():
    max_episodes = 2000
    replay_buffer = deque()

    with tf.Session() as sess:
        mainDQN = dqn.DQN(sess, input_size, output_size, name="main")
        targetDQN = dqn.DQN(sess, input_size, output_size, name="target")

        tf.global_variables_initializer().run()

        copy_ops = get_copy_var_ops(dest_scope_name="target", src_scope_name="main")
        sess.run(copy_ops)

        for episode in range(max_episodes):
            eps = 1. / ((episode / 10) + 1)
            done = False
            step_count = 0
            state = env.reset()

            while not done:
                if np.random.rand(1) < eps:
                    action = env.action_space.sample()
                else:
                    action = np.argmax(mainDQN.predict(state))

                next_state, reward, done, _ = env.step(action)

                if done:
                    reward = -100

                replay_buffer.append((state, action, reward, next_state, done))

                if len(replay_buffer) > REPLAY_MEMORY:
                    replay_buffer.popleft()

                state = next_state
                step_count += 1

                if step_count > 10000: # Good Enough
                    break

            print("Episode: {} steps: {}".format(episode, step_count))

            if step_count > 10000:
                pass 
                break

            if episode % 10 == 1:
                for _ in range(50):
                    minibatch = random.sample(replay_buffer, 10)
                    loss, _ = replay_train(mainDQN, targetDQN, minibatch)

                print("Loss : ", loss)

                # copy q_net ==> target_net
                sess.run(copy_ops)

        bot_play(mainDQN)


if __name__ == '__main__':
    main()





