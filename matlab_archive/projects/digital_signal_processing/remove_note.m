<<<<<<< HEAD
Fs=8192;
t=0:1/Fs:3;
a=[1 1 1];
f=[220;300;440];  
mask(1,:)=ones(1,length(t));
mask(2,:)=t>1;
mask(3,:)=t>2;
x=a*(mask.*sin(2*pi*f*t));
plot(t,x)
=======
Fs=8192;
t=0:1/Fs:3;
a=[1 1 1];
f=[220;300;440];  
mask(1,:)=ones(1,length(t));
mask(2,:)=t>1;
mask(3,:)=t>2;
x=a*(mask.*sin(2*pi*f*t));
plot(t,x)
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
sound(x,Fs);