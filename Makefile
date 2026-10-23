CC     = gcc
CFLAGS := -Wall $(shell pkg-config --cflags gtk4) -MMD -MP
LDLIBS := $(shell pkg-config --libs gtk4)

OBJS = $(addprefix objects/,main.o stopwatch.o resources.o)

.PHONY: all clean test
all: build/gtk-stopwatch

build/gtk-stopwatch: $(OBJS) | build
	$(CC) -o $@ $^ $(LDLIBS)

objects/%.o: %.c | objects
	$(CC) $(CFLAGS) -c -o $@ $<

build objects:
	mkdir -p $@

# builder.ui를 실행 파일 안에 넣는다: 어느 폴더에서 실행해도 UI를 찾는다
resources.c: gresource.xml builder.ui
	glib-compile-resources --target=$@ --generate-source $<

test: build/test-stopwatch
	./build/test-stopwatch

build/test-stopwatch: objects/test.o objects/stopwatch.o | build
	$(CC) -o $@ $^ $(LDLIBS)

clean:
	rm -rf build objects resources.c

-include $(wildcard objects/*.d)
