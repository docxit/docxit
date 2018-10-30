CC=gcc
CXX=g++
CFLAGS=-Wall
BUILD_DIR=./build/
SRC_DIR=./src/
C_DIR=c/
SHELL_DIR=shell/
BASH_COMP_DIR=/etc/bash_completion.d/
EXE_DIR=/usr/local/lib/docxit/
MY_PATH=/usr/local/bin/

all: build docxit init

build:
	mkdir -p $(BUILD_DIR)

docxit: $(SRC_DIR)$(C_DIR)docxit.cpp $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

init: $(SRC_DIR)$(C_DIR)init.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

$(BUILD_DIR)docxitPath.o: $(SRC_DIR)$(C_DIR)docxitPath.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ 

$(BUILD_DIR)shellCommand.o: $(SRC_DIR)$(C_DIR)shellCommand.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: clean rebuild install uninstall

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR)

install:
	mkdir -p $(BASH_COMP_DIR)
	mkdir -p $(EXE_DIR)
	cp $(SRC_DIR)$(SHELL_DIR)docxit_completion $(BASH_COMP_DIR)
	echo "source $(BASH_COMP_DIR)docxit_completion  # docxit auto complete" >> ~/.bashrc
	cp $(BUILD_DIR)docxit $(MY_PATH)
	cp $(BUILD_DIR)init $(EXE_DIR)init

uninstall:
	-rm -f $(BASH_COMP_DIR)docxit_completion
	sed -i '/# docxit auto complete/d' ~/.bashrc
	-rm -f $(MY_PATH)docxit
	-rm -rf $(EXE_DIR)
