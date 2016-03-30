This is a Matlab (and Standalone application) port for the excellent machine learning algorithm `Random Forests' - By Leo Breiman et al. from the R-source by Andy Liaw et al. http://cran.r-project.org/web/packages/randomForest/index.html ( Fortran original by Leo Breiman and Adele Cutler, R port by Andy Liaw and Matthew Wiener.) Current code version is based on 4.5-29 from source of randomForest package.

I especially am grateful for all the help i got from Andy Liaw. This project would not have been possible if not for the previous code by Andy Liaw, Matthew Wiener, Leo Brieman, Adele Cutler.

The wiki has short articles on using rfImpute to input in missing values and basic installation procedures.

**early 2012**
Bug: if you are **training a lot of trees and you tend to get an error**. try the svn source. that replaces allocation via callocs with mxcallocs http://code.google.com/p/randomforest-matlab/issues/detail?id=21

**1-march-2010**
Bug: Note the inputs to the package are in **double**. So make sure you are sending in doubles (the package just assumes that you are sending in doubles).

**6-feb-2010**
Added a separate **precompiled windows binary (mex files)** that will allow to run it on windows without compiling anything. Probably will require installation of a microsoft redistributable package. Edited the installation page here to reflect that http://code.google.com/p/randomforest-matlab/wiki/Introduction

**Known Bug**: right now it has a existing bug that is fixed in the R version 4.5-33. http://cran.r-project.org/web/packages/randomForest/NEWS . If both importance=TRUE and proximity=TRUE, the proximity matrix returned is incorrect. Those computed with importance=FALSE, or with proximity=TRUE are correct. Will fix it in sometime.

Version History:

**SVN source** (for now) contains unsupervised RF. Explanation in tutorial\_ClusterRF.m

**v0.02** (May-16-09) `[Major Update]` Supports **Classification** and **Regression** based RF's with allowing to change many parameters including mtry, ntree, nodesize, prox measure, importance etc. Roughly on par, with regards to functionality, with the R version. Not supported yet from the R-version are stratified sampling. Also Not tested are categorical variables (will do that once I get that type of data from somewhere). Added tutorial files to show how to get the different measures and examine the RF. Decrease in download file size as earlier version had a .svn folder present.

**v0.01-preview** (Deprecated)
Supports **Classification** and **Regression** based RF's with allowing to change mtry (variables) to split on and ntree (number of trees). Many secondary things not supported yet. Based on 4.5-29 of randomForest source.

Source and Readme inside the code package. Works on all 32, 64-bit Windows and Linux.


-Abhishek Jaiantilal

Questions? Comments,etc direct to abhishek.jaiantilal (at) colorado.edu or post in the issues section.