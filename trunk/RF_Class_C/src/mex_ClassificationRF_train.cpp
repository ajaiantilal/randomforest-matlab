#include <math.h>
#include "mex.h"

#define DEBUG_ON 0
void classRF(double *x, int *dimx, int *cl, int *ncl, int *cat, int *maxcat,
	     int *sampsize, int *strata, int *Options, int *ntree, int *nvar,
	     int *ipi, double *classwt, double *cut, int *nodesize,
	     int *outcl, int *counttr, double *prox,
	     double *imprt, double *impsd, double *impmat, int *nrnodes,
	     int *ndbigtree, int *nodestatus, int *bestvar, int *treemap,
	     int *nodeclass, double *xbestsplit, double *errtr,
	     int *testdat, double *xts, int *clts, int *nts, double *countts,
	     int *outclts, int labelts, double *proxts, double *errts,
             int *inbag);

void mexFunction( int nlhs, mxArray *plhs[], 
		  int nrhs, const mxArray*prhs[] )
     
{ 
	if(nrhs==3 | nrhs==4 | nrhs==5);
    else{
		printf("Too less parameters: You supplied %d",nrhs);
		return;
	}
    
        
    int i;
    int p_size = mxGetM(prhs[0]);
    int n_size = mxGetN(prhs[0]);int nsample=n_size;
    double *x = mxGetPr(prhs[0]);
    int *y = (int*)mxGetData(prhs[1]);
    int dimx[]={p_size, n_size};
    
    if (DEBUG_ON){
        //print few of the values
        //for(i=0;i<10;i++)
        //    mexPrintf("%d,",y[i]);
    }

    int nclass = (int)((double)mxGetScalar(prhs[2]));
	double nclass_d = ((double)mxGetScalar(prhs[2]));
    int* cat = (int*)calloc(p_size,sizeof(int));
    for(i=0;i<p_size;i++) cat[i]=1;
    
    
	if (DEBUG_ON){ mexPrintf("n_size %d, p_size %d, nclass %d (%f)",n_size,p_size,nclass,(double)mxGetScalar(prhs[2]));}
	fflush(stdout);
    int maxcat=1;
    int sampsize=n_size;
    int nsum = sampsize;
    int strata = 1;
    int addclass = 0;
    int importance=0;
    int localImp=0;
    int proximity=0;
    int oob_prox=0;
    int do_trace;
    if (DEBUG_ON){ do_trace=1;} else {do_trace=0;}    
    int keep_forest=1;
    int replace=1;
    int stratify=0;
    int keep_inbag=0;
    int Options[]={addclass,importance,localImp,proximity,oob_prox
     ,do_trace,keep_forest,replace,stratify,keep_inbag};
    
     
    int ntree=-1;
    int mtry=-1;
    if (nrhs==4 || nrhs==5){
        ntree = (int)mxGetScalar(prhs[3]);
    }
    
    if (nrhs==5){
       mtry =  (int)mxGetScalar(prhs[4]);
    }
    
    if (ntree<0)
        ntree=500;
            
    if (mtry<0)
        mtry = (int)floor((float)sqrt((float)p_size));
    
    mexPrintf("\nntree %d, mtry=%d\n",ntree,mtry);
    
    int nt=ntree;
    int ipi=0; // ipi:      0=use class proportion as prob.; 1=use supplied priors
    plhs[10] = mxCreateDoubleScalar(mtry);
    //double* classwt=(double*)calloc(nclass,sizeof(double));
    plhs[3] = mxCreateNumericMatrix(nclass, 1, mxDOUBLE_CLASS, 0);
    double *classwt = (double*) mxGetData(plhs[3]);
    
    //double* cutoff=(double*)calloc(nclass,sizeof(double));
    plhs[4] = mxCreateNumericMatrix(nclass, 1, mxDOUBLE_CLASS, 0);
    double *cutoff = (double*) mxGetData(plhs[4]);

    
    for(i=0;i<nclass;i++){
        classwt[i]=1;
        cutoff[i]=1/((double)nclass);
		if (DEBUG_ON){printf("%f,",cutoff[i]);}
    }
    int nodesize=1;
    int* outcl=(int*) calloc(nsample,sizeof(int));
    int* counttr=(int*) calloc(nclass*nsample,sizeof(int));
    double prox=1;
    double* impout=(double*)calloc(p_size,sizeof(double));
    double impSD=1;
    double impmat=1; 
    int nrnodes = 2 * (int)(nsum / nodesize) + 1;
    
    if (DEBUG_ON) { mexPrintf("\nnrnodes=%d, nsum=%d, nodesize=%d, mtry=%d\n",nrnodes,nsum,nodesize,mtry);}
    
    //int* ndbigtree = (int*) calloc(ntree,sizeof(int)); 
    plhs[9] = mxCreateNumericMatrix(nrnodes, nt, mxINT32_CLASS, 0);
    int *ndbigtree = (int*) mxGetData(plhs[9]);
    
    
    //int* nodestatus = (int*) calloc(nt*nrnodes,sizeof(int));
    plhs[6] = mxCreateNumericMatrix(nrnodes, nt, mxINT32_CLASS, 0);
    int *nodestatus = (int*) mxGetData(plhs[6]);
    
    //int* bestvar = (int*) calloc(nt*nrnodes,sizeof(int));
    plhs[8] = mxCreateNumericMatrix(nrnodes, nt, mxINT32_CLASS, 0);
    int *bestvar = (int*) mxGetData(plhs[8]);
    
    //int* treemap = (int*) calloc(nt * 2 * nrnodes,sizeof(int));
    plhs[5] = mxCreateNumericMatrix(nrnodes, 2*nt, mxINT32_CLASS, 0);
    int *treemap = (int*) mxGetData(plhs[5]);
    
    
    //int* nodepred = (int*) calloc(nt * nrnodes,sizeof(int));
    plhs[7] = mxCreateNumericMatrix(nrnodes, nt, mxINT32_CLASS, 0);
    int *nodepred = (int*) mxGetData(plhs[7]);
    
    
    //double* xbestsplit = (double*) calloc(nt * nrnodes,sizeof(double));
    plhs[2] = mxCreateNumericMatrix(nrnodes, nt, mxDOUBLE_CLASS, 0);
    double *xbestsplit = (double*) mxGetData(plhs[2]);
    
    double* errtr = (double*) calloc((nclass+1) * ntree,sizeof(double));
    int testdat=0;
    double xts=1;
    int clts = 1; 
    int nts=1;
    double* countts = (double*) calloc(nclass * nts,sizeof(double));
    int outclts = 1;
    int labelts=0;
    double proxts=1;
    double errts=1;
    int* inbag = (int*) calloc(n_size,sizeof(int));
    
    if (DEBUG_ON){
        //printf few of the values
        for(i=0;i<10;i++)
            mexPrintf("%f,",x[i]);
    }
    plhs[0] = mxCreateDoubleScalar(nrnodes);
    plhs[1] = mxCreateDoubleScalar(ntree);

    classRF(x, dimx, y, &nclass, cat, &maxcat,
	     &sampsize, &strata, Options, &ntree, &mtry,&ipi, 
         classwt, cutoff, &nodesize,outcl, counttr, &prox,
	     impout, &impSD, &impmat, &nrnodes,ndbigtree, nodestatus, 
         bestvar, treemap,nodepred, xbestsplit, errtr,&testdat, 
         &xts, &clts, &nts, countts,&outclts, labelts, 
         &proxts, &errts,inbag);
    
            
    
    
    free(cat);
    free(outcl);
    free(counttr);
    
    // Below are allocated via matlab and will be needed for prediction
    //free(classwt);
    //free(cutoff);
    //free(ndbigtree);
    //free(nodestatus);
    //free(bestvar);
    //free(treemap);
    //free(nodepred);
    //free(xbestsplit);
    
    free(errtr);
    free(countts);
    free(inbag);
    free(impout);
}