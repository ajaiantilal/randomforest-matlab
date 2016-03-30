# Introduction #

Download the code in the Download section. There are two folders each with Howtos that will get you started with the RF code.

Folder RF\_Reg\_C contains code for regression Random Forest

Folder RF\_Class\_C contains code for classification Random Forest

Easiest way to start is to look for tutorial`_``*`.m file within these folders and read the README.txt

There are compile_**.m file,** = windows, linux {macs should also use the linux file}, What i do is call a Makefile (for linux) and that compiles the source. For windows i use some precompiled files (for fortran) and merge with the src files using mex._

# Linux #

Compiling: With g++ and gfortran installed for Linux, everything should be set; except do remove -ansi flag from mexopts.sh in ~/.matlab/Rversion/mexopts.sh [will be dependent on the matlab version installed](Rversion.md). That ansi flag will not allow // type comments in the source files. Other instructions in README.txt

# Windows #

You have two options, either download the precompiled binaries or compile them on your own.

**Using just the binary**

The binary for windows are already included, and should work out of the box. But to run, they need some additional libraries from Visual C++, which microsoft calls as redistributables.

Matlab usually installs these redistributable on Installation, but ...

Open the control panel and check for the following package:
> Microsoft visual C++ 2005 redistributable (x64 if your machine is 64-bit or x86 for 32-bit OS)

If either is not there this package will not work, you only need the 32-bit if you plan to use it on a 32-bit machine and same goes for 64-bit.

32-bit redistributable:
http://www.microsoft.com/downloads/details.aspx?familyid=32bc1bee-a3f9-4c13-9c99-220b62a191ee&displaylang=en

64-bit redistributable:
http://www.microsoft.com/downloads/details.aspx?familyid=90548130-4468-4BBC-9673-D6ACABD5D13B&displaylang=en

and you might require the later version of the redistributable, i.e. Microsoft visual C++ 2008

32-bit: http://www.microsoft.com/downloads/details.aspx?familyid=9B2DA534-3E03-4391-8A4D-074B9F2BC1BF&displaylang=en

64-bit: http://www.microsoft.com/downloads/details.aspx?displaylang=en&FamilyID=bd2a6171-e2d6-4230-b809-9a8d7548c1b6

Why do you need this?
Well, the package was compiled with Matlab and Visual C++ express edition. I reckon the latter might not be installed
on your machine. This is where the redistributable help. They contain the necessary libraries, dll to make the mex run.
Matlab should install these redistributables when its installed but you never know...


**Compiling them on your own**

The randomforest package needs a compiler to compile into mex (matlab executables). Matlab can use its own compiler lcc to compile it or use another compiler like visual studio C++.  lcc compiler that comes with matlab cannot compile C++ files etc, in short you have to install a compiler like visual studio's C++.

Even you dont need everything in visual studio, just visual studio C++ and microsoft has a free express version that you can download from here. http://www.microsoft.com/express/vc/

Once  Visual C++ is installed, you have to instruct matlab to use it as a compiler. You can do by issuing mex -setup at matlab terminal (http://www.mathworks.com/support/tech-notes/1600/1605.html#setup), then it will search your drives and give you visual c++ as an option. Select it and then rerun the compile\_windows file.

only for RF\_Classification and compiling your own .o from fortran, follow the following:
Compiling rfsub.o (from the fortran source in rfsub.f) for win64 was via a cross-compiler on linux, whereas rfsub.o for win32 was via cygwin. Cygwin in current form generates only 32 bit binaries thereby requiring a cross compiler. To avoid installing Cygwin and such, a precompiled rfsub.o is supplied for Windows.

For windows compiling of the mex files, precompiled rfsub.o are present and used instead of depending on a fortran compiler [if you want to recompile everything from scratch, use the makefile and modify the compile\_windows.m file](thus.md). If using the precompiled version of rfsub.o, the only requirement is some form of Visual C++ is installed either via express or full version of Visual Studio and appropriate setup of matlab to use Visual studio is done.


For both windows and linux, compilers can be set via **mex -setup** on matlab's command window.

# Mac #

Thanks to David L. Jones there are precompiled Mex files for Mac OS in the download section with compiler settings on how to setup on a Mac. Download the mex files and also download/unzip the RF\_MexStandalone.zip (source) files. Put the mex files in the folders created and you should be all set.

Also take a look into http://code.google.com/p/randomforest-matlab/issues/detail?id=8

_Alternate way to compile for Mac OS_

For the mac, you have good support for gcc and gfortran. These two programs will be needed to compile the code.
Before installing anything check for compatibility http://www.mathworks.com/support/compilers/previous_releases.html

The below are probable tools that might help you installing gcc/gfortran. Once the tools are installed, the compile\_linux.m file should work for your mac system.

http://r.research.att.com/tools/

Apple also has developer tools (Xcode tools) that has gcc http://developer.apple.com/documentation/Porting/Conceptual/PortingUNIX/preparing/preparing.html

Another tool that also has gcc/gfortran is fink http://www.finkproject.org/

Once you get the compiler installed. http://www.mathworks.com/support/tech-notes/1600/1605.html#setup to setup the compiler to be used with matlab, with the mex -setup command

Note the mex options file name that matlab copies to. [Rare: Sometimes that mex option file has -ansi flag included that makes compilers cringe if C code contains // for comments. Remove -ansi flag from the file if it does.]

An slight edit of the makefile might be required. Seems that mac's rm command doesnot like -rf option after a filename, that might require a makefile edit.