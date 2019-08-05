#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> RL Sung Kim 강의, Frozen Lake에서 slippery 옵션을 켜놓으면 매우 어려워지는데 이 떄 Q값을 업데이트 할 떄 learning_rate를 도입해서 적절하게 AI가 알아서 판단하게 하는 코드
'''
import gym
import numpy as np
import matplotlib.pyplot as plt

env = gym.make('FrozenLake-v0')

# Initialize table with zeros
Q = np.zeros([env.observation_space.n, env.action_space.n])

learning_rate = .70
dis = .9
num_episodes = 2000

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
		Q[state, action] = (1-learning_rate)*Q[state,action] + learning_rate* (reward + dis* np.max(Q[new_state,:]))
		rAll += reward
		state = new_state
	rList.append(rAll)


print("Success rate: " + str(sum(rList)/num_episodes))
print("Final Q-table values")
print("LEFT DOWN RIGHT UP")
print(Q)
plt.bar(range(len(rList)), rList, color="blue")
plt.show()
