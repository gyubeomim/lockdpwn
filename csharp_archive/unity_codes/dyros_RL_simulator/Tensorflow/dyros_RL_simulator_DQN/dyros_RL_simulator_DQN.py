import numpy as np
import tensorflow as tf
import random
from collections import deque
from dqn4 import dqn4 as dqn
from MySocket import MySocket
  
# ed: 입력값은 센서의 갯수만큼
input_size = 181

# ed: 출력값은 One hot vector로써 10개의 케이스로 나뉜다
output_size = 10

# 감가율
dis = 0.9
# 리플레이메모리 사이즈
REPLAY_MEMORY = 50000
# 최대 스텝개수
MAX_STEP = 5000

# ed: 데이터를 Socket으로부터 받아온다
dyrosRLdata = MySocket.MySocket()


# 실제로 DQN을 학습하는 함수. targetDQN, mainDQN을 분리시켰다
def ddqn_replay_train(mainDQN, targetDQN, train_batch):
    x_stack = np.empty(0).reshape(0, mainDQN.input_size)
    y_stack = np.empty(0).reshape(0, mainDQN.output_size)

    for state, action, reward, next_state, done in train_batch:
        Q = mainDQN.predict(state)

        # 게임이 끝난 경우
        if done:
            Q[0, action] = reward
        else:
            Q[0, action] = reward + dis * targetDQN.predict(next_state)[0, np.argmax(mainDQN.predict(next_state))]


        # 출력값 Q를 y_stack에 쌓는다
        y_stack = np.vstack([y_stack, Q])
        # 입력값 state를 x_stack에 쌓는다
        x_stack = np.vstack([x_stack, state])

    # 쌓인 학습데이터를 한번에 업데이트시킨다
    return mainDQN.update(x_stack, y_stack)


# mainDQN ==> targetDQN 가중치를 복사하는 함수 (복잡해보이지만 그냥 복사하는것)
def get_copy_var_ops(*, dest_scope_name="target", src_scope_name="main"):
    # Copy variables src_scope to dest_scope
    op_holder = []

    # 모든 훈련가능(TRAINABLE_VARIABLES)한 Weight들을 scope에서 가져온다
    src_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope=src_scope_name)
    dest_vars = tf.get_collection(tf.GraphKeys.TRAINABLE_VARIABLES, scope=dest_scope_name)


    # src_var.value(가중치) 값들을 dest_var에 assign한다
    # 쉽게 말하면 가중치를 dest_var에 복사한다
    for src_var, dest_var in zip(src_vars, dest_vars):
        op_holder.append(dest_var.assign(src_var.value()))

    return op_holder



def main():
    # 최대 에피소드 개수
    max_episodes = 5000

    replay_buffer = deque()
    last_100_game_reward = deque()


    with tf.Session() as sess:
        # mainDQN, targetDQN을 생성한다
        mainDQN = dqn.DQN(sess, input_size, output_size, name="main")
        targetDQN = dqn.DQN(sess, input_size, output_size, name="target")

        # tf 변수들을 초기화한다
        tf.global_variables_initializer().run()

        # q_net --> target_net 복사한다
        copy_ops = get_copy_var_ops(dest_scope_name="target", src_scope_name="main")
        sess.run(copy_ops)
        
        # mainDQN == targetDQN이 같은상태에서 학습을 시작한다 (mainDQN만 학습한다)
        for episode in range(max_episodes):
            e = 1. / ((episode / 10) + 1)
            done = False
            step_count = 0

            dyrosRLdata.sendingMsg(0)
            state, _reward, _done = dyrosRLdata.getStep()

            while not done:
                # epsilon greedy 입실론 탐욕알고리즘을 사용한다
                if np.random.rand(1) < e:
                    action = np.random.randint(10)
                else:
                    action = np.argmax(mainDQN.predict(state))

                # Unity로 action 값을 전송한다
                dyrosRLdata.sendingMsg(action)

                next_state, reward, done = dyrosRLdata.getStep()

                #print(next_state)
                #print("a : ",action, "s : ",next_state, "e : ", done)

                # ed: code added
                reward += step_count

                if done:
                    reward += -1000
                    if step_count > MAX_STEP:
                        reward += -500
                    elif step_count > MAX_STEP * 0.8:
                        reward += -600
                    elif step_count > MAX_STEP * 0.6:
                        reward += -700
                    elif step_count > MAX_STEP * 0.4:
                        reward += -800
                    elif step_count > MAX_STEP * 0.2:
                        reward += -900

                    print("--------- reward : ", reward)


                # replay_buffer에 SARS를 저장한다
                replay_buffer.append((state, action, reward, next_state, done))

                if len(replay_buffer) > REPLAY_MEMORY:
                      replay_buffer.popleft()

                state = next_state
                step_count += 1

            print("Episode: {} steps: {}".format(episode, step_count))
            
            
            # 에피소드가 4번될 때마다 1번씩 
            if episode % 4 == 1:
                # 100번정도 돌면서 replay_buffer에서 10개의 데이터를 가져와서 학습한다
                for _ in range(100):
                    minibatch = random.sample(replay_buffer, 10)
                    loss, _ = ddqn_replay_train(mainDQN, targetDQN, minibatch)

                print("Loss: ", loss)

                # 특정 주기로만 mainDQN --> targetDQN으로 가중치를 복사한다
                sess.run(copy_ops)
            
            last_100_game_reward.append(step_count)

            if len(last_100_game_reward) > 100:
                last_100_game_reward.popleft()

                avg_reward = np.mean(last_100_game_reward)

                if avg_reward > MAX_STEP * 0.97:
                    print("Game Cleared")
                    break


if __name__ == "__main__":
    main()
