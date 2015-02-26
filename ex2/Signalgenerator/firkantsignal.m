function firkant = firkantsignal(frekvens, amplitude, varighet)
    
    n = 501;
    fs = 44100;
    Ts = 1/fs;

    t = 0:Ts:varighet;
    y=0;

    for i=1:2:n
      
        %bn*sin(2*pi*fn*t);
        bn = ((4*amplitude)/(pi*i));
        y = y + bn*sin(2*pi*i*frekvens*t);
    end
    
  firkant = y;
  
end