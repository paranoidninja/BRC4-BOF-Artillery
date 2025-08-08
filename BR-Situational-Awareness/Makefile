CC=x86_64-w64-mingw32-gcc
CFLAGS=-m64 -Os -s -pedantic -nostdlib -fno-jump-tables -fdiagnostics-color=always -fno-ident -Wshadow -Wconversion -Wall -c
INCLUDES=includes/
SRC=src

.PHONY: all clean

all:
	$(MAKE) TARGET=dir bof
	$(MAKE) TARGET=driversigs bof
	$(MAKE) TARGET=enum_filter_driver bof
	$(MAKE) TARGET=findLoadedModule bof
	$(MAKE) TARGET=aadjoininfo bof
	$(MAKE) TARGET=locale bof
	$(MAKE) TARGET=resources bof

bof:
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $(TARGET).o $(SRC)/$(TARGET).c
	@mkdir -p bofs/
	@mv *.o ./bofs/

dir:
	$(MAKE) TARGET=dir bof

driversigs:
	$(MAKE) TARGET=driversigs bof

enum_filter_driver:
	$(MAKE) TARGET=enum_filter_driver bof

findLoadedModule:
	$(MAKE) TARGET=findLoadedModule bof

aadjoininfo:
	$(MAKE) TARGET=aadjoininfo bof

localte:
	$(MAKE) TARGET=locale bof

resources:
	$(MAKE) TARGET=resources bof

clean:
	@rm -rf ../bofs
