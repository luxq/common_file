USR_DIR=/root/usr
CXX_FLAG= -I ${USR_DIR}/include
LD_FLAG=-L${USR_DIR}/lib -lpcrecpp -lpcre

all: pcrecpp

pcrecpp:
	g++ -g ./pcre_test.cpp ${CXX_FLAG}  -o $@ ${LD_FLAG} 
