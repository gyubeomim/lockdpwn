
#START============================================
# Heap, Queue를 사용해본 예제코드
# Heap
import heapq

L = [3,1,5,3,6,4,2,1]
heapq.heapify(L)       # L을 힙으로 만든다
heapq.heappush(L, 4)   # L에 4를 넣는다
x = heapq.heappop(L)   # L에서 가장 작은 원소를 빼서 x에 저장한다

# Queue
from collections import deque
Q = deque()
Q.append(3)
x = Q.popleft()
#END==============================================

#START============================================
# 순열 및 조합을 사용하는 예제코드
import itertools

for perm in itertools.permutations("ABCDE", 4):
	print(perm)

for comb in itertools.combinations("ABCDE", 3):
	print(comb)
#END==============================================
