#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> RL Sung Kim 강의, Dummy Q Learing을 구현해본 코드
'''

import gym
from gym.envs.registration import register
import numpy as np
import matplotlib.pyplot as plt
import sys, tty, termios
import random as pr

#
def rargmax(vector):
	# argmax that chooses randomly among eligible maximum idices
	m = np.amax(vector)
	indices = np.nonzero(vector == m)[0]
	return pr.choice(indices)

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

# create lists to contain total rewards and steps per epdisode
rList = []
for i in range(num_episodes):
	# reset environment and get first new observation
	state = env.reset()
	rAll = 0
	done = False;

	# the q-table learning algorithm
	while not done:
		action = rargmax(Q[state, :])
		# get new state and reward from environment
		new_state, reward, done, _ = env.step(action)

		# update q-table with new knowledge usig learning rate
		Q[state,action] = reward + np.max(Q[new_state,:])
		rAll += reward
		state = new_state
	rList.append(rAll)


print("Success rate: " + str(sum(rList)/num_episodes))
print("Final Q-table values")
print("LEFT DOWN RIGHT UP")
print(Q)
plt.plot(range(len(rList)), rList, 'r+', color="blue")
plt.show()
