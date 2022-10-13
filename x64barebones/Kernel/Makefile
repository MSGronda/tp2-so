include Makefile.inc

KERNEL=kernel.bin

SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_EXCEPTIONS=$(wildcard exceptions/*.c)
SOURCES_IRQ=$(wildcard irq/*.c)
SOURCES_LIBS=$(wildcard libs/*.c)
SOURCES_SYSCALLS=$(wildcard syscalls/*.c)
SOURCES_MM=$(wildcard memoryManager/*.c)
SOURCES_DRIVERS=$(wildcard drivers/*.c)
SOURCES_PM=$(wildcard processManager/*.c)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_EXCEPTIONS=$(SOURCES_EXCEPTIONS:.c=.o)
OBJECTS_IRQ=$(SOURCES_IRQ:.c=.o)
OBJECTS_LIBS=$(SOURCES_LIBS:.c=.o)
OBJECTS_SYSCALLS=$(SOURCES_SYSCALLS:.c=.o)
OBJECTS_DRIVERS=$(SOURCES_DRIVERS:.c=.o)
OBJECTS_MM=$(SOURCES_MM:.c=.o)
OBJECTS_PM=$(SOURCES_PM:.c=.o)

LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_EXCEPTIONS) $(OBJECTS_IRQ) $(OBJECTS_LIBS) $(OBJECTS_SYSCALLS) $(OBJECTS_DRIVERS) $(OBJECTS_MM) $(OBJECTS_PM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_EXCEPTIONS) $(OBJECTS_IRQ) $(OBJECTS_LIBS) $(OBJECTS_SYSCALLS) $(OBJECTS_DRIVERS) $(STATICLIBS) $(OBJECTS_MM) $(OBJECTS_PM)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_EXCEPTIONS) $(OBJECTS_IRQ) $(OBJECTS_LIBS) $(OBJECTS_SYSCALLS) $(OBJECTS_DRIVERS) $(OBJECTS_MM) $(OBJECTS_PM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o exceptions/*.o irq/*.o libs/*.o syscalls/*.o drivers/*.o *.o *.bin *.elf

.PHONY: all clean
