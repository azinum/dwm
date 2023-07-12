PREFIX ?= /usr/local
CC ?= gcc
LDFLAGS = -lX11
C_FLAGS =

HAS_BATTERY="$(shell cat /sys/class/power_supply/BAT0/capacity 2>/dev/null)"

ifneq ("", $(HAS_BATTERY))
	C_FLAGS+=-DHAS_BATTERY
endif

output: dwmblocks.c blocks.def.h blocks.h
	${CC} dwmblocks.c $(LDFLAGS) -o dwmblocks -O3 $(C_FLAGS)
blocks.h:
	cp blocks.def.h $@

clean:
	rm -f *.o *.gch dwmblocks
install: output
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 dwmblocks $(DESTDIR)$(PREFIX)/bin/dwmblocks
uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwmblocks
