# Introduction #

> There is a sorry state of affairs for using a free fortran compiler available for 64-bit windows and generating a 64-bit binary. I generated the 64-bit binary (a very roundabout way) by using a crosscompiler on linux from the mingw64 project. This shows how to use, say, Intel Fortran compiler for use with the package and probably use other compilers in the same fashion on win64.

# Details #

Part of the code is in fortran and the function calls are exported to C. Usually different compilers have different ways to export them. Some append `_` to the function call like buildtree becomes `_`buildtree or buildtree`_` or `_`buildtree`_` and similarly C function calls are exported by specific name in fortran. In order to generate valid 64-bit obj code for 64-bit windows, as there is no native fortran compiler, a cross-compiler in linux was used to generate the obj file(the precompiled lib), but that caused many function to be exported in `_`x`_` form rather than `_`x form.

If using win64 and a fortran compiler, one might get errors like `_`unresolved external symbol RRAND referenced in function BUILDTREE`_` meaning that RRAND function was not found for function BUILDTREE. RRAND is a C function that is used in the fortran code. Thus, the fortran code when linked is not able to find the C function in the C-compiled code. Note the exact name of the function required, i.e as `_`RAND or  RAND`_` or something else, this exact name is how C should ideally export that function, and thus next we will see how to do this.

Thus for http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classRF.cpp#83 , there is a conditional compile to check that if it's win64 then export as `_`buildtree`_` rather than buildtree`_`.

The code in C calls a bunch of fortran commands and vice versa. The build problems happen when some other fortran compiler is used to compile, as fortran is not able to read c code well. I.e. the code is exported as `_`x`_` from C but read as x in fortran.

Thus, change http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classRF.cpp#104 from
`void _rrand_(double *r) ;`

to

`void rrand(double *r) ; `

(meaning that the export "C" says to export it as rrand() and then change http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classRF.cpp#133 from

`void _rrand_(double *r) { *r = unif_rand(); }`

to

`void rrand(double *r) { *r = unif_rand(); }`

meaning that this is the definition for rrand().

If this works, that is the error for RAND disappears, then change it for catmax and catmaxb which you find here http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classTree.cpp#49

That is within the export "C" and then for the definition of rrand() and now we have to change the function name.

To do that line http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classRF.cpp#60 , change this from `void F77_NAME(_catmaxb)` to just `void catmaxb`

Note: F77`_`NAME() is a macro that appends `_` to the name

and http://code.google.com/p/randomforest-matlab/source/browse/trunk/RF_Class_C/src/classTree.cpp#79 , change this from `void F77_NAME(_catmax)` to `void catmax`

and those errors should disappear.


Regarding, Intel visual fortran: it generates exports in uppercase. So the function name in cpp file has to be changed to uppercase and also the link process is case sensitive. The default in windows system for Intel visual fortran is to generate output symbol in uppercase, but it can be enforced to output the lowercase symbol by using  /names: lowercase.

There are conditional compiles like -DMATLAB and -DWIN64 and others, which just conditionally use mexprintf instead of printf and control the use of how to export functions clearly so that fortran and C can link.

Thanks to Enliang Zheng for pointing out changes required.