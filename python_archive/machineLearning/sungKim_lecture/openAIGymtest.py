#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> RL sung kim 강의, OpenAI의 gym을 사용해 FrozenLake 게임을 키보드 입력을 통해 해본 코드
                                 강화학습을 체험해본다
'''
import gym
from gym.envs.registration import register
import sys, tty, termios

# 방향키 입력을 받기위한 클래스와 arrow_keys 배열 코드
class _Getch:
    def __call__(self):
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(3)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings
			)
        return ch

inkey = _Getch()

LEFT = 0
DOWN = 1
RIGHT = 2
UP = 3

arrow_keys = {
    '\x1b[A' : UP,
    '\x1b[B' : DOWN,
    '\x1b[C' : RIGHT,
    '\x1b[D' : LEFT}


# Register FrozenLake with is_slipeery False
register(
	id = 'FrozenLake-v3',
	entry_point = 'gym.envs.toy_text:FrozenLakeEnv',
	kwargs = {'map_name' : '4x4', 'is_slippery' : False}
)

env = gym.make('FrozenLake-v3')
env.render()

while True:
	key = inkey()
	if key not in arrow_keys.keys():
		print("Game aborted!")
		break

	action = arrow_keys[key]
	state, reward, done, info = env.step(action)
	env.render()
	print("State: ", state, "Action: ", action, "Reward: ", reward, "Info: ", info)

	if done:
		print("Finished with reward", reward)
		break
