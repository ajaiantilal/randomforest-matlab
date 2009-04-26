% ********************************************************************
% * mex File compiling code for Random Forest (for linux)
% * mex interface to Andy Liaw et al.'s C code (used in R package randomForest)
% * Added by Abhishek Jaiantilal ( abhishek.jaiantilal@colorado.edu )
% * License: GPLv2
% * Version: 0.1 
% ********************************************************************/

function compile_windows
    system('del *.mexw32;del *.mexw64;');

    fprintf('I am going to use the precompiled fortran file\n');
    fprintf('If it doesnt work then use cygwin+g77 (or gfortran) to recompile rfsub.f\n');

    mex  -DMATLAB -output mexClassRF_train   src/classRF.cpp src/classTree.cpp src/cokus.cpp rfsub.o src/mex_ClassificationRF_train.cpp   src/rfutils.cpp 
    mex  -DMATLAB -output mexClassRF_predict src/classRF.cpp src/classTree.cpp src/cokus.cpp rfsub.o src/mex_ClassificationRF_predict.cpp src/rfutils.cpp 
    fprintf('Mex`s compiled correctly\n')