%**************************************************************
%* mex interface to Andy Liaw et al.'s C code (used in R package randomForest)
%* Added by Abhishek Jaiantilal ( abhishek.jaiantilal@colorado.edu )
%* License: GPLv2
%* Version: 0.1 
%
% Calls Regression Random Forest
% A wrapper matlab file that calls the mex file
% This does training given the data and labels 
% number of trees is the third option (Optional) which is set to 500 if not
% supplied
%**************************************************************

function model=regRF_train(X,Y,ntree,mtry)
	%function model = regRF_predict(X,Y,ntree,mtry)
    %requires 2 arguments and the rest 2 are optional
    %X: data matrix
    %Y: target values
    %ntree (optional): number of trees (default is 500)
    %mtry (default is max(floor(D/3),1) D=number of features in X)
    
    if ~exist('ntree','var') | ntree<0
		ntree=500;
    end
    if ~exist('mtry','var') | mtry<0 | mtry> size(X,2)
        mtry = max(floor(size(X,2)/3),1);
    end
    
    
	[ldau,rdau,nodestatus,nrnodes,upper,avnode,mbest,ndtree]=mexRF_train(X',Y,ntree,mtry);
	model.lDau=ldau;
	model.rDau=rdau;
	model.nodestatus=nodestatus;
	model.nrnodes=nrnodes;
	model.upper=upper;
	model.avnode=avnode;
	model.mbest=mbest;
	model.ndtree=ndtree;
	model.ntree = ntree;
	clear mexRF_train