.PHONY: clean dirs

SRC=src
OPENCV=`pkg-config --libs opencv4` `pkg-config --cflags opencv4`
CLANG=clang++ -Wall -std=c++11 -lstdc++ -Wunused-function

all: dirs transform

transform: $(SRC)/main.cpp
	$(CLANG) $^ -o $@ $(OPENCV)

clean:
	rm -rf $(BIN) $(OBJ)

dirs:
	mkdir -p $(SRC) $(BIN)

stat:
	wc src/*
