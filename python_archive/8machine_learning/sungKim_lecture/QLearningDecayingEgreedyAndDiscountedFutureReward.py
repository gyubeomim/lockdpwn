#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> RL Sung Kim 강의, Q learing + e-greedy + add noise model과 Discounted Future Reward 알고리즘을 적용해 Q 학습을 좀더 잘하도록 수정한 코드
'''
import gym
from gym.envs.registration import register
import numpy as np
import matplotlib.pyplot as plt
import sys, tty, termios
import random as pr

register(
	id='FrozenLake-v3',
	entry_point = 'gym.envs.toy_text:FrozenLakeEnv',
	kwargs={'map_name' : '4x4', 'is_slippery' : False}
)

env = gym.make('FrozenLake-v3')

# Initialize table with zeros
Q = np.zeros([env.observation_space.n, env.action_space.n])

# set learning parameters
num_episodes = 2000

# discounted future reward 선언
dis = .99

# create lists to contain total rewards and steps per epdisode
rList = []

for i in range(num_episodes):
	# e-greedy 변수
	e = 1./((i // 100) + 1)
	state = env.reset()
	rAll = 0
	done = False

	while not done:
		# e-greedy 구현 코드
		if np.random.rand(1) < e:
			action = env.action_space.sample()
		else:
			action = np.argmax(Q[state, :])

		# add random noise 방법을 사용한 코드
#		action = np.argmax(Q[state, :] + np.random.randn(1, env.action_space.n) / (i+1))
		new_state, reward, done, _ = env.step(action)

		# Q값에 discounted future reward를 적용한 코드이다
		Q[state, action] = reward + dis* np.max(Q[new_state,:])
		rAll += reward
		state = new_state
	rList.append(rAll)


print("Success rate: " + str(sum(rList)/num_episodes))
print("Final Q-table values")
print("LEFT DOWN RIGHT UP")
print(Q)
plt.plot(range(len(rList)), rList, 'r+', color="blue")
plt.show()
