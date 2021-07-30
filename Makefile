OPTFLAG = -O3
INCLUDES = -I./lib -I. -I./lib/htslib -I./lib/Rmath -I./lib/pcre2
CXXFLAGS = -pipe -std=c++0x $(OPTFLAG) $(INCLUDES) -D__STDC_LIMIT_MACROS
CXX = g++

SOURCESONLY =

SOURCES = 
		
SOURCESONLY = main.cpp

TARGET = ft
TOOLSRC = $(SOURCES:=.cpp) $(SOURCESONLY)
TOOLOBJ = $(TOOLSRC:.cpp=.o)
LIBDEFLATE = lib/libdeflate/libdeflate.a
LIBHTS = lib/htslib/libhts.a
LIBRMATH = lib/Rmath/libRmath.a
LIBPCRE2 = lib/pcre2/libpcre2.a

all : $(TARGET)

${LIBDEFLATE} :
	cd lib/libdeflate; $(MAKE) || exit 1; 
	
${LIBHTS} : ${LIBDEFLATE}
	export LDFLAGS=-L${PWD}/lib/libdeflate;	export CPPFLAGS=-I${PWD}/lib/libdeflate; cd lib/htslib; autoheader; autoconf; ./configure; $(MAKE) libhts.a || exit 1; 

${LIBRMATH} :
	cd lib/Rmath; $(MAKE) libRmath.a || exit 1; 

${LIBPCRE2} :
	cd lib/pcre2; $(MAKE) libpcre2.a || exit 1; 

version :
	git rev-parse HEAD | cut -c 1-8 | awk '{print "#define VERSION \"0.5772-"$$0"\""}' > version.h;

$(TARGET) : ${LIBHTS} ${LIBRMATH} ${LIBPCRE2} $(TOOLOBJ) 
	$(CXX) $(CXXFLAGS) -o $@ $(TOOLOBJ) $(LIBHTS) $(LIBRMATH) ${LIBPCRE2} ${LIBDEFLATE} -lz -lpthread -lbz2 -llzma -lcurl -lcrypto

$(TOOLOBJ): $(HEADERSONLY)

.cpp.o :
	$(CXX) $(CXXFLAGS) -o $@ -c $*.cpp

.PHONY: clean cleanvt test version

clean :
	cd lib/libdeflate; $(MAKE) clean
	cd lib/htslib; $(MAKE) clean
	cd lib/Rmath; $(MAKE) clean
	cd lib/pcre2; $(MAKE) clean
	-rm -rf $(TARGET) $(TOOLOBJ)

cleanft :
	-rm -rf $(TARGET) $(TOOLOBJ)    

test : ft
	test/test.sh
	test/test_mnv.sh

debug : ft
	test/test.sh debug
