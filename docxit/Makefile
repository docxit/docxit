CC=gcc
CFLAGS=-Wall
BUILD_DIR=./build/
SRC_DIR=./src/
C_DIR=c/
SHELL_DIR=shell/
BASH_COMP_DIR=/etc/bash_completion.d/

all: docxit

docxit: $(SRC_DIR)$(C_DIR)docxit.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 



.PHONY: clean install uninstall

clean:
	rm -rf $(BUILD_DIR)

install:
	mkdir -p $(BASH_COMP_DIR)
	cp $(SRC_DIR)$(SHELL_DIR)docxit_completion $(BASH_COMP_DIR)
	echo "source $(BASH_COMP_DIR)docxit_completion  # docxit auto complete" >> ~/.bashrc
	bash $(BASH_COMP_DIR)docxit_completion
	cp $(BUILD_DIR)docxit /usr/local/bin/

uninstall:
	rm -f $(BASH_COMP_DIR)docxit_completion
	sed -i '/# docxit auto complete/d' ~/.bashrc
	rm -f /usr/local/bin/docxit
