function Untitled

    clc 
clear all
close all

%Mass - DOCUMENTATION
%Call "mex -setup c++" to change compiler
%Will need Visual C++ 2015 Build tools: http://landinghub.visualstudio.com/visual-cpp-build-tools

%Helpful Link for input and output
%https://www.mathworks.com/help/matlab/matlab_external/data-flow-in-mex-files.html


%mex 'SignalGenCom\SigCommunicate.cpp'


 display(mfilename('fullpath'));
Name = 'SGCOM.mexw64';
path = 'G:\Capstone\Programming\SignalGenCom\Matlab';


% if exist(fullfile('G:\Capstone\Programming\SignalGenCom\Matlab',Name), 'file') == 0 %equals to 3 if exists
    mex('G:\Capstone\Programming\SignalGenCom\Matlab\SGInitialize.cpp', '-outdir', path);
    mex 'G:\Capstone\Programming\SignalGenCom\Matlab\SGCOM.cpp' -outdir 'G:\Capstone\Programming\SignalGenCom\Matlab'
    mex 'G:\Capstone\Programming\SignalGenCom\Matlab\SGTerminate.cpp' -outdir 'G:\Capstone\Programming\SignalGenCom\Matlab'
% end
Y = SGInitialize();
X = SGCOM();
display(Y);
display(X);

SGTerminate();
return



