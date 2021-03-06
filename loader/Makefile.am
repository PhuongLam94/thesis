######################################################
# File: Makefile
#
# Desc: Makefile for the Loader library files.
#   This loader is lightly adapted from the loader in UQBT
#   Purpose is to load the input binary file into memory, with calls to iterate through sections,
#	find entry points, symbols, etc.
#   The main library is BinaryFile, which calls eactly one of ElfBinaryFile etc as needed.
#
# Prerequisite libraries: none
#
######################################################

# $Revision: 1.2 $
# Note: gnu make is probably required (for patsubst etc)
# This whole makefile is dependent on finding the pattern *BinaryFile.cpp; a lib%.so file is made for each of these
# You should be able to add a simple loader without any changes to this Makefile, as long as you follow the naming
# convention <type>BinaryFile.*

# 22 Aug 06 - Mike Frysinger: respect values set up by ./configure script
# 12 Jul 05 - Mike: All use SymTab.o now
# 20 Jul 04 - Mike: Removed BOOMDIR (paths relative now)
# 12 Apr 05 - Gerard: Structured
# 11 Apr 02 - Mike: Use lib%.so names and -l now; no "make install" any more

AUTOMAKE_OPTIONS = foreign

####################
# Compiler settings
#

FPIC = -fPIC

####################################
# Other variables detected by ./configure
#

# HOST_WINDOWS is "yes" if the host OS is Cygwin or MinGW
HOST_WINDOWS = @HOST_WINDOWS@

# HOST_CYGWIN is "yes" if the host environment is Cygwin
HOST_CYGWIN = @HOST_CYGWIN@

# HOST_OSX is true if the hostOS is OS X (*-apple-darwin*)
HOST_OSX = @HOST_OSX@

# HOST_OSX_10_2 is true if the hostOS is OS X version 10.2.x (*-apple-darwin6*)
HOST_OSX_10_2 = @HOST_OSX_10_2@

# HOST_GNU_LD is true if the linker on this host machine is GNU
HOST_GNU_LD = @HOST_GNU_LD@

MAKEDEPEND=@MAKEDEPEND@

####################################
# Detection of OS specific settings
#

# LDL is -ldl if needed (Windows does not)
# EXEEXT is .exe for Windows
# DLLEXT is .dll for Windows and .so otherwise 
ifeq ($(HOST_WINDOWS), yes)
 LDL=
 EXEEXT=.exe
 DLLEXT=.dll
 WININCLUDE=-Iwin32make/include
 # RUNPATH is not needed on Windows 
 RUNPATH=
 COPYDLL=$(top_srcdir)/libBinaryFile$(DLLEXT)
else # Non-Windows
 LDL=-ldl
 EXEEXT=
 DLLEXT=.so
 WININCLUDE=
 ifeq ($(HOST_GNU_LD), yes)
  RUNPATH=-Wl,-rpath -Wl,"lib"
 else
  ifeq ($(HOST_OSX), yes)
   RUNPATH=
  else		# Assume Solaris
   RUNPATH=-R"lib"
  endif
 endif
 COPYDLL=
endif

ifeq ($(HOST_OSX), yes)
 ifeq ($HOST_OSX_10_2), yes)
  SHARED=-dynamiclib		# Note: doesn't seem to work at present; fiddle manually
 else
  SHARED=-dynamic -dylib
 endif
 #-flat_namespace
 DLLEXT=.dylib
 RUNPATH=
else # Non-OS X
 SHARED=-shared
endif

######################
# Rules for compiling
#

LOADERS = \
	ElfBinaryFile.cpp \
	Win32BinaryFile.cpp \
	ExeBinaryFile.cpp \
	HpSomBinaryFile.cpp \
	PalmBinaryFile \
	DOS4GWBinaryFile.cpp \
	IntelCoffFile.cpp \
	$(NULL)

pkglib_LTLIBRARIES = 

ifeq ($(HOST_CYGWIN), no)
 # Until we can resolve the issue of compiling loader/MachOBinaryFile.cpp, don't attempt to make it so at least
 # the Cygwin hosted Boomerang can compile and use non-MachO loaders
 LOADERS+=MachOBinaryFile.cpp
endif
#LOADERDLLS=$(patsubst %,$(top_srcdir)/lib/lib%$(DLLEXT),$(LOADERS))
#BASEDLL=$(top_srcdir)/lib/libBinaryFile$(DLLEXT)
#ALLDLLS=$(LOADERDLLS) $(BASEDLL)
ALLLIBS=$(patsubst %,-l%,$(LOADERS)) -lBinaryFile
ALLOBJS = $(patsubst %, %.o, $(LOADERS))
ALLOBJS += BinaryFile.o SymTab.o

all:    $(ALLDLLS) $(COPYDLL) BinaryFileFactory.o BinaryFileStub.o

microX86dis.o: microX86dis.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $(FPIC) $<

# Extra object files, etc
# These are target specific variables.
$(top_srcdir)/lib/libWin32BinaryFile$(DLLEXT): EXTRAS = microX86dis.o
$(top_srcdir)/lib/libWin32BinaryFile$(DLLEXT): microX86dis.o
$(top_srcdir)/lib/libDOS4GWBinaryFile$(DLLEXT): EXTRAS = microX86dis.o
$(top_srcdir)/lib/libDOS4GWBinaryFile$(DLLEXT): microX86dis.o

$(top_srcdir)/libBinaryFile$(DLLEXT): $(top_srcdir)/lib/libBinaryFile$(DLLEXT)
	cp $< $@

BinaryFile.o:		CCEXTRAS = -DBUILDING_LIBBINARYFILE
MachOBinaryFile.o:	CCEXTRAS = -I.

$(BASEDLL) : BinaryFile.o SymTab.o
	$(CXX) $(CXXFLAGS) -o $@ $(SHARED) BinaryFile.o SymTab.o $(OUTIMPLIB) $(LDFLAGS)

# This pattern generates all the main dependencies
$(LOADERDLLS): $(top_srcdir)/lib/lib%$(DLLEXT) : %.o $(BASEDLL)
	$(CXX) $(CXXFLAGS) -o $@ $(SHARED) $< SymTab.o $(EXTRAS) -lBinaryFile $(RUNPATH) -L$(top_srcdir)/lib $(LDFLAGS)

# Compile all objects with -fPIC
$(ALLOBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $(FPIC) $(CCEXTRAS) -I$(top_srcdir)/include -o $@ $<

####################
# Conditional rules
#

# Automatic generation of dependencies
ifdef MAKEDEPEND
 # automatic is better!
 depend: $(MAKEDEPEND)
	$(MAKEDEPEND) -w120 -Y -I$(top_srcdir)/include -I. -I$(top_srcdir)/c -I$(top_srcdir)/codegen \
		-I$(top_srcdir)/frontend *.cpp *.c > /dev/null 2>&1

 depend.in: $(MAKEDEPEND)
	$(MAKEDEPEND) -fMakefile.in -w120 -Y -I$(top_srcdir)/include -I. -I$(top_srcdir)/c -I$(top_srcdir)/codegen \
		-I$(top_srcdir)/frontend *.cpp *.c > /dev/null 2>&1
	
else
 depend:
	# You need the (X11) makedepend tool to generate dependencies
 depend.in:
	# You need the (X11) makedepend tool to generate dependencies
endif # ifdef MAKEDEPEND

###############
# Unit testing
#

testLoader$(EXEEXT): testLoader.o LoaderTest.o microX86dis.o BinaryFileFactory.o SymTab.o
	$(CXX) $(CXXFLAGS) -o $@ $^  -lcppunit $(ALLLIBS) $(RUNPATH) $(LDL) -L$(top_srcdir)/lib $(LDFLAGS)

testLoader.o: testLoader.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -I$(top_srcdir)/include $<

LoaderTest.o: LoaderTest.cpp LoaderTest.h $(top_srcdir)/include/BinaryFile.h SymTab.o
	$(CXX) $(CXXFLAGS) -c -o $@ -I$(top_srcdir)/include $<

# Because of the relative paths, testLoader will only work from the parent
# directory...
test: all testLoader$(EXEEXT)
	cd $(top_srcdir) && loader/testLoader$(EXEEXT)

