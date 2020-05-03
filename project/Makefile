all: lcdproject.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

clean:
	rm -f *.o *.elf timerLib/*.o timerLib/*.a

lcdproject.elf: lcddemo.o stateMachines.o p1_interrupt_handler.o led.o switches.o buzzer.o lcddraw.o lcdutils.o font-11x16.o font-5x7.o font-8x12.o 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 

load: lcdproject.elf
	msp430loader.sh $^

install:
	(cd timerLib; make install)
