TARGET = optimizer
OBJECTS = obj/main.o obj/hooke-jeeves.o obj/utils.o obj/sn.o

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

CROSS_COMPILE = 
CC	= $(CROSS_COMPILE)g++
CPP	= $(CROSS_COMPILE)g++
LD	= $(CROSS_COMPILE)g++
AR	= $(CROSS_COMPILE)ar
AS	= $(CROSS_COMPILE)as
CP	= $(CROSS_COMPILE)objcopy
OD	= $(CROSS_COMPILE)objdump

INCDIR = 
CFLAGS = -O2 -Wall -g -c -lstdc++ -lm -DVERSION=\"$(GIT_VERSION)\" -DCACHE
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -lm
CPPFLAGS = -O2 -Wall -g -c -lm -DVERSION=\"$(GIT_VERSION)\" -DCACHE
ASFLAGS = $(CFLAGS)

LIBS= -lm
LIBDIR =
LDFLAGS = -lm -ldl -lc 

all: optimizer
	@echo "All done"

debug: CPPFLAGS = -O2 -Wall -g -c -lm -DVERSION=\"$(GIT_VERSION)\" -DCACHE -DDEBUG
debug: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o optimizer
	@echo "Make debug done"

clean:
	-rm -rf $(OBJECTS) $(TESTOBJECTS)
	@echo "Clean done"
	
optimizer: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) $(LIBS) -o optimizer
	@echo "Make optimizer done"
		
unittest: $(TESTOBJECTS)
	$(LD) $(LDFLAGS) $(TESTOBJECTS) $(LIBS) -o unittests

obj:
	mkdir -p obj

obj/%.o: src/%.c | obj
	$(CC) $(CPPFLAGS) $< -o $@
	
obj/%.o: src/%.cpp | obj
	$(CPP) $(CPPFLAGS) $< -o $@

obj/%.o: src/%.S
	$(CC) $(CFLAGS) $< -o $@
