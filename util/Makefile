######################################################
# File: Makefile
# Desc: Makefile for the utilities (util) directory
#       Makes and tests the libutil.so library
#
######################################################

# $Revision: 1.6 $
# 09 Apr 02 - Mike: Created.
# 10 Apr 02 - Mike: interface -> include; added util.cpp (for str())
# 11 Apr 02 - Mike: target is now ../lib/libutil so can use -lutil
# 28 Apr 02 - Mike: Make library from .o not .cpp

top_srcdir = ..

LIB_OBJS = util.o
LIB=$(top_srcdir)/lib/libutil.so

CC = gcc -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
CXX = g++ -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
CFLAGS = -m32 -Wall
CXXFLAGS = -m32 -Wall
CPPFLAGS = -I$(top_srcdir)/include 
LDFLAGS = -m32

all: #$(LIB) testUtil 
	# Only "make test" is supported

# HOST_GNU_LD is true if the linker on this host machine is GNU
HOST_GNU_LD = yes

BOOMDIR="$(PWD)/.."
BOOMSET=-DBOOMDIR=\"$(BOOMDIR)\"
LIBDIR=$(BOOMDIR)/lib
ifeq ($(HOST_GNU_LD), yes)
RUNPATH=-Wl,-rpath -Wl,$(LIBDIR)
else # Assume Solaris
RUNPATH=-R$(LIBDIR)
endif

testUtil: testUtil.o UtilTest.o $(LIB)
	$(CC) -o $@ testUtil.o UtilTest.o -lutil -lcppunit $(RUNPATH) -L$(top_srcdir)/lib

$(LIB): $(LIB_OBJS)
	$(CC) -o $@ -shared $(LIB_OBJS) $(RUNPATH) -L$(top_srcdir)/lib

UtilTest.o: UtilTest.h
util.o: ../include/util.h

# Make these objects with -fPIC
$(LIB_OBJS): %.o : %.cpp
	$(CC) -c -fPIC -I$(top_srcdir)/include $(EXTRAS) -o $@ $<

# Others without -fPIC
.cpp.o:
	$(CC) -c -I$(top_srcdir)/include -o $@ $<

clean:
	rm -f testUtil *.o $(LIB)

test: $(LIB) testUtil
	./testUtil
