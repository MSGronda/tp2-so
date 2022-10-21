include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
ASMSOURCES= $(wildcard ./asm/*.asm)
ASMOBJECTS=$(ASMSOURCES:.asm=.o)
SOURCES=$(wildcard [^_]*.c)
COBJECTS=$(SOURCES:.c=.o)
COMANDOS_SOURCES=$(wildcard ./comandos/*.c)
COMANDOS_OBJECTS=$(COMANDOS_SOURCES:.c=.o)
TEST_SOURCES=$(wildcard ./comandos/tests/*.c)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
LIBS_SOURCES=$(wildcard ./libs/*.c)
LIBS_OBJECTS=$(LIBS_SOURCES:.c=.o)

all: $(MODULE)

$(MODULE): $(ASMOBJECTS) $(COBJECTS) $(COMANDOS_OBJECTS) $(TEST_OBJECTS) $(LIBS_OBJECTS)
	$(LD) -T sampleCodeModule.ld _loader.o $(COBJECTS) $(ASMOBJECTS) $(COMANDOS_OBJECTS) $(TESTS_OBJECTS) $(LIBS_OBJECTS) -o ../$(MODULE)
	$(LD) -T sampleCodeModule.ld _loader.o $(COBJECTS) $(ASMOBJECTS) $(COMANDOS_OBJECTS) $(TESTS_OBJECTS) --oformat=elf64-x86-64 -o ../0000-sampleCodeModule.elf

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c $(SOURCES) 
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o ./comandos/*.o ./libs/*.o

.PHONY: all clean print
