%% This matlab script reads a .wav file, resamples, puts the samples into a C array (string) and saves it in a .txt file

% Read
[y, Fs] = wavread('Beep1'); % Reads the file
y = 0.5 + 0.45.*y; % Scale and offset to get values within 0-1, file dependent

% Resample
Fsnew = 8192; % The sampling rate we used, can be changed
[P, Q] = rat(Fsnew/Fs); % Ratio between original sampling rate Fs and desired sampling rate
ynew = resample(y, P, Q); % resampling

% Scale
ysc = round(4096.*ynew); % Scale and round values for 12 bit DAC, 0-4096 = 0-FFF 

% Make the C array as a string
stra='const uint16_t variablename[]={'; % change variablename to fit the sound 
for i=1:length(ysc)-1
    disp(i)
    stra=strcat(stra, int2str(ysc(i)));
    stra=strcat(stra, ', ');
end
stra = strcat(stra,int2str(round(ysc(i)))); 
stra = strcat(stra, ' };');

% Write to file
fid = fopen('outputname.txt', 'w');
fprintf(fid, '%s\n', stra);
fclose(fid);