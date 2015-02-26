function  trekant = trekantsignal1(frekvens,amplitude,varighet)
n = 501;
fs = 44100;
Ts = 1/fs;
t = 0:Ts:varighet;
y = 0;

for i = 1:2:n
    bn = (amplitude*8)/(pi^2);
    y = y+bn*((-1)^((i-1)/2))*(1/i^2)*sin(2*i*pi*frekvens*t);
end
trekant = y;
%sound(y,fs);
end
