# 20250526 makefile for GCC

#EMSDK= C:\emsdk\upstream\emscripten
#CC= $(EMSDK)\em++ 
CC= gcc 
LINK= gcc
#AR= $(EMSDK)\emar
AR= ar
	
DEBUG= 1

PLATFORM= Win32

BUILD= Debug
OFLAGS += -O0 -g -D_DEBUG

#BUILD= Release
#OFLAGS += -O2 -s -DNDEBUG

OUTPATH= $(BUILD)_$(PLATFORM)

CFLAGS= -O3 -c -s $(OFLAGS) \
-I../EasyViewLib -I../sqlite3 -I../zlib

LFLAGS= -Wl,-b64 -maix64 -lstdc++ -lpthread -lm
AFLAGS= rs

SRCS= saiArray.cpp

OBJS= $(OUTPATH)/saiArray.o
	
all: $(OUTPATH)/libsai.a
	copy $(OUTPATH)\libsai.a ..\lib\Win32\$(BUILD)_$(PLATFORM)

testLinux: testLinux.cpp
	$(CC) $(CFLAGS) -o $(OUTPATH)/testLinux.o testLinux.cpp
	$(LINK) $(LFLAGS) -o $(OUTPATH)/testLinux $(OUTPATH)/testLinux.o \
	-lsqlite -lz -lEasyLib \
	-L$(OUTPATH) -L../sqlite3/$(OUTPATH) -L../zlib/$(OUTPATH)
	
$(OUTPATH)/libsai.a: $(OBJS)
	$(AR) $(AFLAGS) $(OUTPATH)/libEasyLib.a $(OBJS)
	
$(OUTPATH)/saiArray.o: saiArray.cpp
	$(CC) $(CFLAGS) -o $(OUTPATH)/saiArray.o saiArray.cpp