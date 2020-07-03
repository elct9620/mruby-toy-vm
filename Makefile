.PHONY: clean run

BIN_DIR = bin
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: bin/mrb-ino

%.o: %.c src/app.c
	$(CC) -I include -c $< -o $@

src/app.c: app.rb
	mrbc -B app -o $@ $^

bin/mrb-ino: $(OBJECTS) src/app.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf src/app.c
	rm -rf src/*.o

run: clean bin/mrb-ino
	@bin/mrb-ino
