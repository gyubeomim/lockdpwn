#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 자동차융합실험1, 5 진동신호의 측정 및 주파수 분석 리포트에 사용한 분석용 코드 
'''
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import scipy.io as sio

#==============================================================
# .mat data loading
input_1a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\InputData\\InputData_1_A_1.mat')['Inputdata'][0][0][1].reshape(16384,1)
input_1b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\InputData\\InputData_1_B_1.mat')['Inputdata'][0][0][1].reshape(16384,1)
input_2a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\InputData\\InputData_2_A_1.mat')['Inputdata'][0][0][1].reshape(16384,1)
input_2b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\InputData\\InputData_2_B_1.mat')['Inputdata'][0][0][1].reshape(16384,1)

output_1a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\OutputData\\OutputData_1_A_1.mat')['Outputdata'][0][0][1].reshape(16384,1)
output_1b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\OutputData\\OutputData_1_B_1.mat')['Outputdata'][0][0][1].reshape(16384,1)
output_2a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\OutputData\\OutputData_2_A_1.mat')['Outputdata'][0][0][1].reshape(16384,1)
output_2b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\OutputData\\OutputData_2_B_1.mat')['Outputdata'][0][0][1].reshape(16384,1)

frf_1a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\FRFmagnitude\\FRFmagnitude_1_A_1.mat')['FRF'][0][0][2].reshape(8192,1)
frf_1b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\FRFmagnitude\\FRFmagnitude_1_B_1.mat')['FRF'][0][0][2].reshape(8192,1)
frf_2a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\FRFmagnitude\\FRFmagnitude_2_A_1.mat')['FRF'][0][0][2].reshape(8192,1)
frf_2b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\FRFmagnitude\\FRFmagnitude_2_B_1.mat')['FRF'][0][0][2].reshape(8192,1)

coherence_1a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\Coherence\\Coherence_1_A_1.mat')['coherence'][0][0][2].reshape(4097,1)
coherence_1b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\Coherence\\Coherence_1_B_1.mat')['coherence'][0][0][2].reshape(4097,1)
coherence_2a1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\Coherence\\Coherence_2_A_1.mat')['coherence'][0][0][2].reshape(4097,1)
coherence_2b1 = sio.loadmat('D:\\Documents\\CloudStation\\KMU_sync\\자동차융합실험1\\5진동신호의측정및주파수분석\\data\\Coherence\\Coherence_2_B_1.mat')['coherence'][0][0][2].reshape(4097,1)


input_1a1_pd = pd.DataFrame(input_1a1)
input_1b1_pd = pd.DataFrame(input_1b1)
input_2a1_pd = pd.DataFrame(input_2a1)
input_2b1_pd = pd.DataFrame(input_2b1)

output_1a1_pd = pd.DataFrame(output_1a1)
output_1b1_pd = pd.DataFrame(output_1b1)
output_2a1_pd = pd.DataFrame(output_2a1)
output_2b1_pd = pd.DataFrame(output_2b1)

frf_1a1_pd = pd.DataFrame(frf_1a1)
frf_1b1_pd = pd.DataFrame(frf_1b1)
frf_2a1_pd = pd.DataFrame(frf_2a1)
frf_2b1_pd = pd.DataFrame(frf_2b1)

coherence_1a1_pd = pd.DataFrame(coherence_1a1)
coherence_1b1_pd = pd.DataFrame(coherence_1b1)
coherence_2a1_pd = pd.DataFrame(coherence_2a1)
coherence_2b1_pd = pd.DataFrame(coherence_2b1)


#==============================================================
# 곱법칙 확인

print("\n\n[*] 1A1 & 2A1 Input 곱법칙 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2A1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(input_1a1_pd.mean()[0].round(4), \
        input_1a1_pd.std()[0].round(2), \
        input_1a1_pd.min()[0].round(2), \
        input_1a1_pd.max()[0].round(2), \
        input_2a1_pd.mean()[0].round(4), \
        input_2a1_pd.std()[0].round(2), \
        input_2a1_pd.min()[0].round(2), \
        input_2a1_pd.max()[0].round(2)))

print("[*] 1B1 & 2B1 Input 곱법칙 확인 \n[+] 1B1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(input_1b1_pd.mean()[0].round(4), \
        input_1b1_pd.std()[0].round(2), \
        input_1b1_pd.min()[0].round(2), \
        input_1b1_pd.max()[0].round(2), \
        input_2b1_pd.mean()[0].round(4), \
        input_2b1_pd.std()[0].round(2), \
        input_2b1_pd.min()[0].round(2), \
        input_2b1_pd.max()[0].round(2)))


print("\n\n[*] 1A1 & 2A1 Output 곱법칙 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2A1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(output_1a1_pd.mean()[0].round(4), \
        output_1a1_pd.std()[0].round(2), \
        output_1a1_pd.min()[0].round(2), \
        output_1a1_pd.max()[0].round(2), \
        output_2a1_pd.mean()[0].round(4), \
        output_2a1_pd.std()[0].round(2), \
        output_2a1_pd.min()[0].round(2), \
        output_2a1_pd.max()[0].round(2)))

print("[*] 1B1 & 2B1 Output 곱법칙 확인 \n[+] 1B1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(output_1b1_pd.mean()[0].round(4), \
        output_1b1_pd.std()[0].round(2), \
        output_1b1_pd.min()[0].round(2), \
        output_1b1_pd.max()[0].round(2), \
        output_2b1_pd.mean()[0].round(4), \
        output_2b1_pd.std()[0].round(2), \
        output_2b1_pd.min()[0].round(2), \
        output_2b1_pd.max()[0].round(2)))


print("\n\n[*] 1A1 & 2A1 FRF 곱법칙 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2A1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(frf_1a1_pd.mean()[0].round(4), \
        frf_1a1_pd.std()[0].round(2), \
        frf_1a1_pd.min()[0].round(2), \
        frf_1a1_pd.max()[0].round(2), \
        frf_2a1_pd.mean()[0].round(4), \
        frf_2a1_pd.std()[0].round(2), \
        frf_2a1_pd.min()[0].round(2), \
        frf_2a1_pd.max()[0].round(2)))

print("[*] 1B1 & 2B1 FRF 곱법칙 확인 \n[+] 1B1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(frf_1b1_pd.mean()[0].round(4), \
        frf_1b1_pd.std()[0].round(2), \
        frf_1b1_pd.min()[0].round(2), \
        frf_1b1_pd.max()[0].round(2), \
        frf_2b1_pd.mean()[0].round(4), \
        frf_2b1_pd.std()[0].round(2), \
        frf_2b1_pd.min()[0].round(2), \
        frf_2b1_pd.max()[0].round(2)))

#==============================================================
# 상호성 확인

print("\n\n[*] 1A1 & 1B1 Input 상호성 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 1B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(input_1a1_pd.mean()[0].round(4), \
        input_1a1_pd.std()[0].round(2), \
        input_1a1_pd.min()[0].round(2), \
        input_1a1_pd.max()[0].round(2), \
        input_1b1_pd.mean()[0].round(4), \
        input_1b1_pd.std()[0].round(2), \
        input_1b1_pd.min()[0].round(2), \
        input_1b1_pd.max()[0].round(2)))


print("[*] 2A1 & 2B1 Input 상호성 확인 \n[+] 2A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(input_1a1_pd.mean()[0].round(4), \
        input_2a1_pd.std()[0].round(2), \
        input_2a1_pd.min()[0].round(2), \
        input_2a1_pd.max()[0].round(2), \
        input_2b1_pd.mean()[0].round(4), \
        input_2b1_pd.std()[0].round(2), \
        input_2b1_pd.min()[0].round(2), \
        input_2b1_pd.max()[0].round(2)))


print("\n\n[*] 1A1 & 1B1 Output 상호성 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 1B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(output_1a1_pd.mean()[0].round(4), \
        output_1a1_pd.std()[0].round(2), \
        output_1a1_pd.min()[0].round(2), \
        output_1a1_pd.max()[0].round(2), \
        output_1b1_pd.mean()[0].round(4), \
        output_1b1_pd.std()[0].round(2), \
        output_1b1_pd.min()[0].round(2), \
        output_1b1_pd.max()[0].round(2)))


print("[*] 2A1 & 2B1 Output 상호성 확인 \n[+] 2A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(output_1a1_pd.mean()[0].round(4), \
        output_2a1_pd.std()[0].round(2), \
        output_2a1_pd.min()[0].round(2), \
        output_2a1_pd.max()[0].round(2), \
        output_2b1_pd.mean()[0].round(4), \
        output_2b1_pd.std()[0].round(2), \
        output_2b1_pd.min()[0].round(2), \
        output_2b1_pd.max()[0].round(2)))



print("\n\n[*] 1A1 & 1B1 FRF 상호성 확인 \n[+] 1A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 1B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(frf_1a1_pd.mean()[0].round(4), \
        frf_1a1_pd.std()[0].round(2), \
        frf_1a1_pd.min()[0].round(2), \
        frf_1a1_pd.max()[0].round(2), \
        frf_1b1_pd.mean()[0].round(4), \
        frf_1b1_pd.std()[0].round(2), \
        frf_1b1_pd.min()[0].round(2), \
        frf_1b1_pd.max()[0].round(2)))


print("[*] 2A1 & 2B1 FRF 상호성 확인 \n[+] 2A1 mean:{:6}   std:{:5}   min:{:5}   max:{:6}\n[+] 2B1 mean:{:5}   std:{:5}   min:{:5}   max:{:5}\n"\
        .format(frf_2a1_pd.mean()[0].round(4), \
        frf_2a1_pd.std()[0].round(2), \
        frf_2a1_pd.min()[0].round(2), \
        frf_2a1_pd.max()[0].round(2), \
        frf_2b1_pd.mean()[0].round(4), \
        frf_2b1_pd.std()[0].round(2), \
        frf_2b1_pd.min()[0].round(2), \
        frf_2b1_pd.max()[0].round(2)))







