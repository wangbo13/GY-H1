# import time

# import matplotlib.pyplot as plt
# import numpy as np
# import math

# import DataProcess as DP
# from   scipy  import   signal

# x = np.arange(0,2*np.pi,0.01)
# y = np.sin(x)

# def Gnoisegen(x, snr):
#     Nx = len(x)  # 求出信号的长度
#     noise = np.random.randn(Nx)# 用randn产生正态分布随机数 
#     signal_power = np.sum(x*x)/Nx# 求信号的平均能量
#     noise_power = np.sum(noise*noise)/Nx# 求信号的平均能量
#     noise_variance = signal_power/(math.pow(10., (snr/10)))#计算噪声设定的方差值
#     noise = math.sqrt(noise_variance/noise_power)*noise# 按照噪声能量构成相应的白噪声

#     return x+noise


# y_noise = Gnoisegen(x=y,snr=2)

# for i in range(20):
#     n = np.random.randint(0,2*np.pi*100)
#     y_noise[n] *= np.random.randint(-100,100)

# plt.figure(1)
# plt.plot(x,y)
# plt.plot(x,y_noise)

# plt.figure(2)
# y2 = DP.Dataculling(y_noise.tolist(),'place')
# plt.plot(x,y)
# plt.plot(x,y2)

# plt.figure(3)
# b,a = signal.butter(1,0.01,'lowpass')
# y3 = signal.filtfilt(b,a,y2)
# plt.plot(x,y)
# plt.plot(x,y3)

# plt.show()


a = 1123
b = a.to_bytes(2,byteorder='big',signed=True)
c = a.to_bytes(2,byteorder='little',signed=True)
b = bytes.hex(b)
c = bytes.hex(c)
print(b[0:2],' ',b[2:4])