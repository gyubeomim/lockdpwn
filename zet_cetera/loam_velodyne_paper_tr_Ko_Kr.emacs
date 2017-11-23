# coding: utf-8

abstract

우리는 6-DOF 공간을 움직이는 2-axis LIDAR로부터 측정되는 거리 데이터를 사용해 실시간 odometry와 mapping을 하려고 한다.
이 문제는 상당히 어려운데 그 이유는 다른 시간대로부터 받은 거리정보를 측정하기 어렵고 잘못된 모션 예측이 잘못된 점군을 형성하도록 야기하기 때문이다.
현재 coherent 3D 맵들은 off-line batch method들을 사용해 만들어지고 종종 센서의 drift를 보정하기 위한 loop closure 방법을 사용한다

우리가 제안하는 방법은 높은 정확도와 IMU(관성측정)의 도움없이도 low-drift와 low-computational complexity를 가지는 장점이 있다.
이 정도의 성능을 뽑아내기 위한 핵심 아이디어는 동시에 많은 변수들을 최적화해야하는 복잡한 문제였던 simultaneous localization과 mapping을 둘로 분리하는 것이다.

첫번째는 


