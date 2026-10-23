CC     = gcc
CFLAGS = -Wall $(shell pkg-config --cflags gtk4) -MMD -MP
LDLIBS = $(shell pkg-config --libs gtk4)

OBJS = main.o stopwatch.o resources.o

.PHONY: all clean test
all: gtk-stopwatch

gtk-stopwatch: $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

# builder.ui를 실행 파일 안에 넣는다: 어느 폴더에서 실행해도 UI를 찾는다
resources.c: gresource.xml builder.ui
	glib-compile-resources --target=$@ --generate-source $<

test: test-stopwatch
	./test-stopwatch

test-stopwatch: test.o stopwatch.o
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	rm -f gtk-stopwatch test-stopwatch resources.c *.o *.d

-include $(wildcard *.d)
