mode=release
nocheck=false
CC=gcc
CXX=g++
BUILD_DIR=./build/
SRC_DIR=./src/
C_DIR=c/
SHELL_DIR=shell/
JAVA_DIR=java/
BASH_COMP_DIR=/etc/bash_completion.d/
EXE_DIR=/usr/local/lib/docxit/
LIB_DIR=lib/
MY_PATH=/usr/local/bin/
EXT_HTTP=https://www.docx4java.org/docx4j/docx4j-6_0_1/dependencies/
DOCX4J_HTTP=https://www.docx4java.org/docx4j/docx4j-6_0_1/docx4j-6.0.1.jar
AD_EXT_HTTP=https://github.com/docxit/docxit-dependencies/raw/master/

ifeq ($(mode), debug)
all: all_release all_debug 
CFLAGS=-Wall -g -DDEBUG
else
all: all_release 
CFLAGS=-Wall -O3
endif


all_release: build externalbuild docxit init deinit addIndex removeIndex commit diff.jar merge.jar

all_debug: printIndex

build:
	mkdir -p $(BUILD_DIR)

externalbuild: antlr-2.7.7.jar antlr-runtime-3.5.2.jar avalon-framework-api-4.3.1.jar avalon-framework-impl-4.3.1.jar commons-codec-1.11.jar commons-compress-1.12.jar commons-io-2.5.jar commons-lang3-3.5.jar docx4j-6.0.1.jar guava-20.0.jar httpclient-4.5.6.jar httpcore-4.4.10.jar jackson-annotations-2.7.0.jar jackson-core-2.7.9.jar jackson-databind-2.7.9.4.jar jaxb-svg11-1.0.2.jar jcl-over-slf4j-1.7.25.jar log4j-1.2.17.jar lorem-2.1.jar mbassador-1.2.4.2.jar serializer-2.7.2.jar slf4j-api-1.7.25.jar slf4j-log4j12-1.7.25.jar stringtemplate-3.2.1.jar wmf2svg-0.9.8.jar xalan-2.7.2.jar xmlgraphics-commons-2.3.jar

ifeq ($(nocheck), true)
antlr-2.7.7.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

antlr-runtime-3.5.2.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

avalon-framework-api-4.3.1.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

avalon-framework-impl-4.3.1.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-codec-1.11.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-compress-1.12.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-io-2.5.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-lang3-3.5.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

docx4j-6.0.1.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(DOCX4J_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

guava-20.0.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

httpclient-4.5.6.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

httpcore-4.4.10.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-annotations-2.7.0.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-core-2.7.9.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-databind-2.7.9.4.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jaxb-svg11-1.0.2.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jcl-over-slf4j-1.7.25.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

log4j-1.2.17.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

lorem-2.1.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

mbassador-1.2.4.2.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

serializer-2.7.2.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

slf4j-api-1.7.25.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

slf4j-log4j12-1.7.25.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

stringtemplate-3.2.1.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

wmf2svg-0.9.8.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

xalan-2.7.2.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

xmlgraphics-commons-2.3.jar:
	[ -f $(LIB_DIR)$@ ] || wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

else
antlr-2.7.7.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

antlr-runtime-3.5.2.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

avalon-framework-api-4.3.1.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

avalon-framework-impl-4.3.1.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-codec-1.11.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-compress-1.12.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-io-2.5.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

commons-lang3-3.5.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

docx4j-6.0.1.jar:
	wget -P $(LIB_DIR) -c $(DOCX4J_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

guava-20.0.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

httpclient-4.5.6.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

httpcore-4.4.10.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-annotations-2.7.0.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-core-2.7.9.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jackson-databind-2.7.9.4.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jaxb-svg11-1.0.2.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

jcl-over-slf4j-1.7.25.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

log4j-1.2.17.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

lorem-2.1.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

mbassador-1.2.4.2.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

serializer-2.7.2.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

slf4j-api-1.7.25.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

slf4j-log4j12-1.7.25.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

stringtemplate-3.2.1.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

wmf2svg-0.9.8.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

xalan-2.7.2.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@

xmlgraphics-commons-2.3.jar:
	wget -P $(LIB_DIR) -c $(EXT_HTTP)$@ || wget -P $(LIB_DIR) -c $(AD_EXT_HTTP)$@
endif

docxit: $(SRC_DIR)$(C_DIR)docxit.cpp $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

init: $(SRC_DIR)$(C_DIR)init.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 
	
deinit: $(SRC_DIR)$(C_DIR)deinit.c
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ 

addIndex: $(SRC_DIR)$(C_DIR)addIndex.cpp $(BUILD_DIR)sha1.o $(BUILD_DIR)blobCreate.o $(BUILD_DIR)indexOp.o $(BUILD_DIR)shellCommand.o $(BUILD_DIR)docxitPath.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@ -lpthread 

commit: $(SRC_DIR)$(C_DIR)commit.cpp $(BUILD_DIR)sha1.o $(BUILD_DIR)blobCreate.o $(BUILD_DIR)indexOp.o $(BUILD_DIR)commitTree.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@

removeIndex: $(SRC_DIR)$(C_DIR)removeIndex.c $(BUILD_DIR)indexOp.o
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)$@ -lpthread

printIndex: $(SRC_DIR)$(C_DIR)printIndex.cpp $(BUILD_DIR)indexOp.o $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $(BUILD_DIR)$@

diff.jar: $(BUILD_DIR)diffdir
	jar cvfm $(BUILD_DIR)diff.jar $^/META-INF/MANIFEST.MF -C $^ .

merge.jar: $(BUILD_DIR)mergedir
	jar cvfm $(BUILD_DIR)merge.jar $^/META-INF/MANIFEST.MF -C $^ .

$(BUILD_DIR)diffdir: compilediff
	mkdir -p $(BUILD_DIR)diffdir/META-INF
	cp $(SRC_DIR)$(JAVA_DIR)docx4j.properties $(BUILD_DIR)diffdir
	cp $(SRC_DIR)$(JAVA_DIR)log4j.properties $(BUILD_DIR)diffdir
	cp $(SRC_DIR)$(JAVA_DIR)MANIFEST.MF $(BUILD_DIR)diffdir/META-INF/MANIFEST.MF
	
$(BUILD_DIR)mergedir: compilemerge
	mkdir -p $(BUILD_DIR)mergedir/META-INF
	cp $(SRC_DIR)$(JAVA_DIR)docx4j.properties $(BUILD_DIR)mergedir
	cp $(SRC_DIR)$(JAVA_DIR)log4j.properties $(BUILD_DIR)mergedir
	cp $(SRC_DIR)$(JAVA_DIR)MANIFEST.MF $(BUILD_DIR)mergedir/META-INF/MANIFEST.MF
	
compilediff: $(SRC_DIR)$(JAVA_DIR)diff_match_patch.java $(SRC_DIR)$(JAVA_DIR)Vo.java $(SRC_DIR)$(JAVA_DIR)WordCompareUtil.java
	mkdir -p $(BUILD_DIR)diffdir/docxit
	javac -Djava.ext.dirs=$(LIB_DIR) $^ -d $(BUILD_DIR)diffdir/

compilemerge: $(SRC_DIR)$(JAVA_DIR)WordMergeUtil.java
	mkdir -p $(BUILD_DIR)mergedir/docxit
	javac -Djava.ext.dirs=$(LIB_DIR) $^ -d $(BUILD_DIR)mergedir/

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

$(BUILD_DIR)commitTree.o: $(SRC_DIR)$(C_DIR)commitTree.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: clean rebuild install install_debug install_release uninstall

rebuild: clean all

clean:
	rm -rf $(BUILD_DIR)

ifeq ($(mode), debug)
install: install_release install_debug
else
install: install_release
endif

install_release:
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
	cp $(BUILD_DIR)commit $(EXE_DIR)commit
	cp $(BUILD_DIR)diff.jar $(EXE_DIR)diff.jar
	cp $(BUILD_DIR)merge.jar $(EXE_DIR)merge.jar
	cp -r $(LIB_DIR) $(EXE_DIR)externallib 


install_debug:
	cp $(BUILD_DIR)printIndex $(MY_PATH)

uninstall:
	-rm -f $(BASH_COMP_DIR)docxit_completion
	sed -i '/# docxit auto complete/d' ~/.bashrc
	-rm -f $(MY_PATH)docxit $(MY_PATH)printIndex
	-rm -rf $(EXE_DIR)
