######################################################
# File: Makefile
# Desc: Makefile for the db (database) directory
#		NOTE: seems to be overridden by top level Makefile now!
#       Makes and tests all object files in this directory
#
# Prerequisite libraries: util, BinaryFile, cppunit
#
######################################################

# $Revision: 1.11 $
# 05 Apr 02 - Mike: Created. Added "test" target
# 10 Apr 02 - Mike: More dependencies; interface -> include
# 26 Apr 02 - Mike: Create the libdb.so library, from .o files
# 29 Apr 02 - Mike: Added sslparser etc
# 13 May 02 - Mike: Added RtlTest and ParserTest
# 04 Jul 02 - Mike: Added type.cpp, TypeType.cpp
# 01 Jul 05 - Mike: Big merge from boomerang.pole branch

top_srcdir = ..

# HOST_GNU_LD is true if the linker on this host machine is GNU
HOST_GNU_LD = yes

BISONPP=bison++
FLEXPP=flex++

DB_LIB=$(top_srcdir)/lib/libdb.so
TEST_OBJS = ExpTest.o ProcTest.o ProgTest.o RtlTest.o ParserTest.o TypeTest.o CfgTest.o
LIB_OBJS = exp.o prog.o proc.o rtl.o cfg.o basicblock.o register.o sslparser.o sslscanner.o insnameelem.o sslinst.o \
	table.o type.o dataflow.o worklist.o

BOOMDIR="$(PWD)/.."
LIBDIR=$(BOOMDIR)/lib
BOOMSET=-DBOOMDIR=\"$(BOOMDIR)\"

CC = gcc -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
CXX = g++ -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
CFLAGS = -m32 -Wall
CXXFLAGS = -m32 -Wall
CPPFLAGS = -I$(top_srcdir)/include 
LDFLAGS = -m32

GENFILES = sslparser.cpp sslparser.h sslscanner.cpp sslscanner.h

all: #$(DB_LIB) testDbase
	# Only "make test" is supported

test: testExp testStmt testRtl

testExp.o: testExp.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ -I$(top_srcdir)/include $<

testExp: testExp.o exp.o statement.o rtl.o testExpStubs.o ExpTest.o
	$(CC) -o $@ exp.o statement.o rtl.o testExpStubs.o ExpTest.o -lcppunit $<

testStmt.o: testStmt.cpp
	$(CC) -c -o $@ -I$(top_srcdir)/include $<

STMT_TEST_OBJS = testStmt.o statement.o exp.o testStmtStubs.o StatementTest.o proc.o signature.o
testStmt: $(STMT_TEST_OBJS)
	$(CC) -o $@ $(STMT_TEST_OBJS) -lcppunit

testRtl.o: testRtl.cpp
	$(CC) -c -o $@ -I$(top_srcdir)/include $<

# This one tests the whole front end!
RTL_TEST_OBJS=testRtl.o exp.o statement.o rtl.o proc.o prog.o testRtlStubs.o RtlTest.o ../loader/BinaryFile.o \
	../frontend/frontend.o ../frontend/njmcDecoder.o ../frontend/sparcfrontend.o ../frontend/pentiumfrontend.o \
	../frontend/sparcdecoder.o ../frontend/pentiumdecoder.o sslparser.o sslscanner.o register.o table.o ../util/util.o \
	cfg.o basicblock.o sslinst.o ../c/ansi-c-parser.o ../c/ansi-c-scanner.o insnameelem.o

testRtl: $(RTL_TEST_OBJS)
	$(CC) -o $@ $(RTL_TEST_OBJS) -lcppunit -ldl 

ifeq ($(HOST_GNU_LD), yes)
RUNPATH=-Wl,-rpath -Wl,$(LIBDIR)
else # Assume Solaris
RUNPATH=-R$(LIBDIR)
endif

$(DB_LIB): $(LIB_OBJS)
	$(CC) -shared -o $@ $(LIB_OBJS) -lBinaryFile -lcppunit -lutil \
		$(RUNPATH) -L$(top_srcdir)/lib

testDbase: testDbase.o $(DB_LIB) $(TEST_OBJS)
	$(CC) -o $@ testDbase.o $(TEST_OBJS) -ldb -lcppunit -lutil -lBinaryFile \
		$(RUNPATH) -L$(top_srcdir)/lib

TEST_HDRS = $(patsubst %.o,  %.h, $(TEST_OBJS))
testDbase: $(TEST_HDRS)

ExpTest.o: ExpTest.h ../include/exp.h ../include/operator.h
ProgTest.o: ProgTest.h ../include/prog.h

exp.o: ../include/exp.h ../include/operator.h
worklist.o: ../include/worklist.h ../include/exp.h
prog.o: ../include/prog.h
cfg.o: ../include/cfg.h
basicblock.o: ../include/cfg.h
rtl.o: ../include/rtl.h ../include/exp.h ../include/operator.h
register.o: ../include/register.h
sslparser.o: sslparser.cpp sslparser.h sslscanner.h
sslscanner.o: sslscanner.cpp sslscanner.h
insnameelem.o: insnameelem.h

testRtlStubs.o: typeStubs.cpp signatureStubs.cpp
testExpStubs.o: utilStubs.cpp typeStubs.cpp

prog.o:             EXTRAS = $(BOOMSET)
StatementTest.o:    EXTRAS = $(BOOMSET) -I$(top_srcdir)/frontend
exp.o:              EXTRAS = -I.
worklist.o:              EXTRAS = -I.
testStmtStubs.o:    EXTRAS = -I$(top_srcdir)/frontend
RtlTest.o:          EXTRAS = $(BOOMSET) -I$(top_srcdir)/frontend

# Make these objects with -fPIC
$(LIB_OBJS): %.o : %.cpp
	$(CC) -c -fPIC -I$(top_srcdir)/include $(EXTRAS) -o $@ $<

# Others without -fPIC
.cpp.o:
	$(CC) -c -I$(top_srcdir)/include $(EXTRAS) -o $@ $<

sslparser.cpp sslparser.h: sslparser.y sslscanner.l
	$(BISONPP) -d -v -osslparser.cpp -hsslparser.h $<

sslscanner.cpp sslscanner.h: sslscanner.l sslparser.y
	$(FLEXPP) -osslscanner.cpp -hsslscanner.h $<
	
clean:
	rm -f testDbase *.o $(DB_LIB)

# Clean up generated files
cleangen:
	rm -f $(GENFILES)

# Remote: for when making remotely from bison++/flex++ facilities, or just
# can't be bothered installing these.
remote:
	touch $(GENFILES)
