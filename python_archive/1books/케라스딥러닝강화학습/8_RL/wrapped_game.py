#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 케라스딥러닝강화학습 p349, 강화학습을 하기 위해 벽돌게임을 만들어본 코드

                키보드가 아닌 네트워크와 통신으로 제어할 수 있도록 Wrapping된 클래스이다
'''
from __future__ import division, print_function
import collections
import numpy as np
import pygame
import random
import os


class MyWrappedGame(object):
    def __init__(self):
        # Headless 모드 (GUI창이 없는 모드)로 실행할 경우 아래 코드를 주석해제한다
        os.environ["SDL_VIDEODRIVER"] = "dummy"

        pygame.init()
        pygame.key.set_repeat(10, 100)

                # set constants
        self.COLOR_WHITE = (255, 255, 255)
        self.COLOR_BLACK = (0, 0, 0)
        self.GAME_WIDTH = 400
        self.GAME_HEIGHT = 400
        self.BALL_WIDTH = 20
        self.BALL_HEIGHT = 20
        self.PADDLE_WIDTH = 50
        self.PADDLE_HEIGHT = 10
        self.GAME_FLOOR = 350
        self.GAME_CEILING = 10
        # based on experimentation, the ball tends to move 4 times
        # between each paddle movement. Since here we alternate ball
        # and paddle movement, we make ball move 4x faster.
        self.BALL_VELOCITY = 10
        self.PADDLE_VELOCITY = 20
        self.FONT_SIZE = 30
#        self.MAX_TRIES_PER_GAME = 100
        self.MAX_TRIES_PER_GAME = 1
        self.CUSTOM_EVENT = pygame.USEREVENT + 1
        self.font = pygame.font.SysFont("Comic Sans MS", self.FONT_SIZE)
        

    def reset(self):
        self.frames = collections.deque(maxlen=4)
        self.game_over = False

        self.paddle_x = self.GAME_WIDTH // 2
        self.game_score = 0
        self.reward = 0

        self.ball_x = random.randint(0, self.GAME_WIDTH)
        self.ball_y = self.GAME_CEILING
        self.num_tries = 0

        self.screen = pygame.display.set_mode((self.GAME_WIDTH, self.GAME_HEIGHT))
        self.clock = pygame.time.Clock()


    def step(self, action):
        pygame.event.pump()

        # 패들을 왼쪽으로 옮기는 경우
        if action == 0: 
            self.paddle_x -= self.PADDLE_VELOCITY
            if self.paddle_x < 0:
                self.paddle_x = self.PADDLE_VELOCITY

        # 패들을 오른쪽으로 옮기는 경우
        elif action == 2:
            self.paddle_x += self.PADDLE_VELOCITY
            if self.paddle_x > self.GAME_WIDTH - self.PADDLE_WIDTH:
                self.paddle_x = self.GAME_WIDTH - self.PADDLE_WIDTH - self.PADDLE_VELOCITY

        # 패들을 움직이지 않는다
        else:
            pass

        self.screen.fill(self.COLOR_BLACK)
        score_text = self.font.render("Score: {:d}/{:d}, Ball: {:d}"
            .format(self.game_score, self.MAX_TRIES_PER_GAME,
                    self.num_tries), True, self.COLOR_WHITE)
                

        # 공의 위치를 업데이트한다
        self.ball_y += self.BALL_VELOCITY
        ball = pygame.draw.rect(self.screen, self.COLOR_WHITE,
                                pygame.Rect(self.ball_x, self.ball_y,
                                            self.BALL_WIDTH,
                                            self.BALL_HEIGHT))

        # 패들의 위치를 업데이트한다
        paddle = pygame.draw.rect(self.screen, self.COLOR_WHITE,
                                  pygame.Rect(self.paddle_x, 
                                              self.GAME_FLOOR,
                                              self.PADDLE_WIDTH,
                                              self.PADDLE_HEIGHT))


        # 충돌여부를 확인하고 보상을 준다
        self.reward = 0
        if self.ball_y >= self.GAME_FLOOR - self.BALL_WIDTH // 2:
            if ball.colliderect(paddle):
                self.reward = 1
            else:
                self.reward = -1

            self.game_score == self.reward
            self.ball_x = random.randint(0, self.GAME_WIDTH)
            self.ball_y = self.GAME_CEILING
            self.num_tries += 1


        pygame.display.flip()

        # 마지막 4 프레임을 저장한다 
        self.frames.append(pygame.surfarray.array2d(self.screen))
        if self.num_tries >= self.MAX_TRIES_PER_GAME:
            self.game_over = True

        self.clock.tick(30)
        return self.get_frames(), self.reward, self.game_over


    def get_frames(self):
        return np.array(list(self.frames))


if __name__ == '__main__':
    game = MyWrappedGame()

    NUM_EPOCHS = 10

    for e in  range(NUM_EPOCHS):
        print("Epoch: {:d}".format(e))

        game.reset()
        input_t = game.get_frames()
        game_ove = False

        while not game.game_over:
            action = np.random.randint(0, 3, size=1)[0]
            input_tp1, reward, game_over = game.step(action)
            print(action, reward, game_over)

            
        

