%**************************************************************
%* mex interface to Andy Liaw et al.'s C code (used in R package randomForest)
%* Added by Abhishek Jaiantilal ( abhishek.jaiantilal@colorado.edu )
%* License: GPLv2
%* Version: 0.1 
%
% Calls Classification Random Forest
% A wrapper matlab file that calls the mex file
% This does prediction given the data and the model file
%**************************************************************
%function Y_hat = classRF_predict(X,model)
%requires 2 arguments
%X: data matrix
%model: generated via classRF_train function
	
function Y_new = classRF_predict(X,model)
    
    if nargin~=2
		error('need atleast 2 parameters,X matrix and model');
	end
	[Y_hat,jts,countts] = mexClassRF_predict(X',model.nrnodes,model.ntree,model.xbestsplit,model.classwt,model.cutoff,model.treemap,model.nodestatus,model.nodeclass,model.bestvar,model.ndbigtree,model.nclass);
	%keyboard
    clear mexClassRF_predict
    
    Y_new = double(Y_hat);
    new_labels = model.new_labels;
    orig_labels = model.orig_labels;
    
    for i=1:length(orig_labels)
        Y_new(find(Y_hat==new_labels(i)))=Inf;
        Y_new(isinf(Y_new))=orig_labels(i);
    end
    1;
    