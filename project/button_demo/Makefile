#makefile configuration
COMMON_OBJECTS  =
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compile (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: button.elf

#additional rules for files
button.elf: ${COMMON_OBJECTS} p2_interrupt_handler.o led.o switches.o state_machine.o wdInterruptHandler.o buzzer.o main_program.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: button.elf
	msp430loader.sh button.elf

clean:
	rm -f *.o *.elf
