%**************************************************************
%* mex interface to Andy Liaw et al.'s C code (used in R package randomForest)
%* Added by Abhishek Jaiantilal ( abhishek.jaiantilal@colorado.edu )
%* License: GPLv2
%* Version: 0.1 
%
% Calls Classification Random Forest
% A wrapper matlab file that calls the mex file
% This does training given the data and labels 
% number of trees is the third option (Optional) which is set to 500 if not
% supplied
%**************************************************************
%function model = classRF_train(X,Y,ntree,mtry)
%requires 2 arguments and the rest 2 are optional
%X: data matrix
%Y: target values
%ntree (optional): number of trees (default is 500)
%mtry (default is floor(sqrt(size(X,2))) D=number of features in X)

function model=classRF_train(X,Y,ntree,mtry)
    
    if ~exist('ntree','var') | ntree<0
		ntree=500;
    end
    if ~exist('mtry','var') | mtry<0 | mtry>size(X,2)
        mtry =floor(sqrt(size(X,2)));
    end
    
	%[ldau,rdau,nodestatus,nrnodes,upper,avnode,mbest,ndtree]=
    %keyboard
    orig_labels = unique(Y);
    Y_new = Y;
    new_labels = 1:length(orig_labels);
    
    for i=1:length(orig_labels)
        Y_new(find(Y==orig_labels(i)))=Inf;
        Y_new(isinf(Y_new))=new_labels(i);
    end
    
    [nrnodes,ntree,xbestsplit,classwt,cutoff,treemap,nodestatus,nodeclass,bestvar,ndbigtree,mtry]= mexClassRF_train(X',int32(Y_new),length(unique(Y)),ntree,mtry);
 	model.nrnodes=nrnodes;
 	model.ntree=ntree;
 	model.xbestsplit=xbestsplit;
 	model.classwt=classwt;
 	model.cutoff=cutoff;
 	model.treemap=treemap;
 	model.nodestatus=nodestatus;
 	model.nodeclass=nodeclass;
 	model.bestvar = bestvar;
 	model.ndbigtree = ndbigtree;
    model.mtry = mtry;
    model.orig_labels=orig_labels;
    model.new_labels=new_labels;
    model.nclass = length(unique(Y));
 	clear mexClassRF_train
    %keyboard
    1;

