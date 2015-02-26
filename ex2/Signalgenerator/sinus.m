function sinus = sinus(f,A,T)

fs= 44100;
Ts = 1/fs;
t = 0:Ts:T;
x = A*sin(2*pi*f*t);

sinus = x;
end