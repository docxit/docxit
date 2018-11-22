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

all: build docxit init deinit addIndex removeIndex

build:
	mkdir -p $(BUILD_DIR)

docxit: $(SRC_DIR)$(C_DIR)docxit.cpp $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

init: $(SRC_DIR)$(C_DIR)init.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 
	
deinit: $(SRC_DIR)$(C_DIR)deinit.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

addIndex: $(SRC_DIR)$(C_DIR)addIndex.cpp $(BUILD_DIR)sha1.o $(BUILD_DIR)blobCreate.o $(BUILD_DIR)indexOp.o $(BUILD_DIR)shellCommand.o $(BUILD_DIR)docxitPath.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@ -lpthread 

removeIndex: $(SRC_DIR)$(C_DIR)removeIndex.c $(BUILD_DIR)indexOp.o
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ -lpthread

$(BUILD_DIR)docxitPath.o: $(SRC_DIR)$(C_DIR)docxitPath.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@ 

$(BUILD_DIR)shellCommand.o: $(SRC_DIR)$(C_DIR)shellCommand.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)indexOp.o: $(SRC_DIR)$(C_DIR)indexOp.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)blobCreate.o: $(SRC_DIR)$(C_DIR)blobCreate.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR)sha1.o: $(SRC_DIR)$(C_DIR)sha1.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@


.PHONY: clean rebuild install uninstall

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR)

install:
	mkdir -p $(BASH_COMP_DIR)
	mkdir -p $(EXE_DIR)
	cp $(SRC_DIR)$(SHELL_DIR)docxit_completion $(BASH_COMP_DIR)
	cp $(SRC_DIR)$(SHELL_DIR)updateDocxitPath.sh $(EXE_DIR)
	cp $(SRC_DIR)$(SHELL_DIR)listAllFiles.sh $(EXE_DIR)add
	echo "source $(BASH_COMP_DIR)docxit_completion  # docxit auto complete" >> ~/.bashrc
	cp $(BUILD_DIR)docxit $(MY_PATH)
	cp $(BUILD_DIR)init $(EXE_DIR)init
	cp $(BUILD_DIR)deinit $(EXE_DIR)deinit
	cp $(BUILD_DIR)addIndex $(EXE_DIR)addIndex
	cp $(BUILD_DIR)removeIndex $(EXE_DIR)removeIndex

uninstall:
	-rm -f $(BASH_COMP_DIR)docxit_completion
	sed -i '/# docxit auto complete/d' ~/.bashrc
	-rm -f $(MY_PATH)docxit
	-rm -rf $(EXE_DIR)
