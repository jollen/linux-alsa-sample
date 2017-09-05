CC = arm-linux-gnueabi-gcc
LIBS = -lasound
all:
	$(CC) -o aplay aplay.c $(LIBS) -static
