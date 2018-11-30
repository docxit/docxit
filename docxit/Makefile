mode=release
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
DOCX4J_HTTP=https://www.docx4java.org/docx4j/docx4j-6.0.1.jar
AD_EXT_HTTP=https://github.com/docxit/docxit-dependencies/raw/master/

ifeq ($(mode), debug)
all: all_release all_debug 
CFLAGS=-Wall -g -DDEBUG
else
all: all_release 
CFLAGS=-Wall -O3
endif


all_release: build lib externalbuild $(BUILD_DIR)docxit $(BUILD_DIR)init $(BUILD_DIR)deinit $(BUILD_DIR)addIndex $(BUILD_DIR)removeIndex $(BUILD_DIR)commit $(BUILD_DIR)fileop.jar $(BUILD_DIR)config

all_debug: $(BUILD_DIR)printIndex $(BUILD_DIR)printConfig

build:
	mkdir -p $(BUILD_DIR)

lib:
	mkdir -p $(LIB_DIR)

externalbuild: $(LIB_DIR)antlr-2.7.7.jar $(LIB_DIR)antlr-runtime-3.5.2.jar $(LIB_DIR)avalon-framework-api-4.3.1.jar $(LIB_DIR)avalon-framework-impl-4.3.1.jar $(LIB_DIR)commons-codec-1.11.jar $(LIB_DIR)commons-compress-1.12.jar $(LIB_DIR)commons-io-2.5.jar $(LIB_DIR)commons-lang3-3.5.jar $(LIB_DIR)docx4j-6.0.1.jar $(LIB_DIR)guava-20.0.jar $(LIB_DIR)httpclient-4.5.6.jar $(LIB_DIR)httpcore-4.4.10.jar $(LIB_DIR)jackson-annotations-2.7.0.jar $(LIB_DIR)jackson-core-2.7.9.jar $(LIB_DIR)jackson-databind-2.7.9.4.jar $(LIB_DIR)jaxb-svg11-1.0.2.jar $(LIB_DIR)jcl-over-slf4j-1.7.25.jar $(LIB_DIR)log4j-1.2.17.jar $(LIB_DIR)lorem-2.1.jar $(LIB_DIR)mbassador-1.2.4.2.jar $(LIB_DIR)serializer-2.7.2.jar $(LIB_DIR)slf4j-api-1.7.25.jar $(LIB_DIR)slf4j-log4j12-1.7.25.jar $(LIB_DIR)stringtemplate-3.2.1.jar $(LIB_DIR)wmf2svg-0.9.8.jar $(LIB_DIR)xalan-2.7.2.jar $(LIB_DIR)xmlgraphics-commons-2.3.jar

$(LIB_DIR)antlr-2.7.7.jar:
	wget -O $@ -c $(EXT_HTTP)antlr-2.7.7.jar || wget -O $@ -c $(AD_EXT_HTTP)antlr-2.7.7.jar

$(LIB_DIR)antlr-runtime-3.5.2.jar:
	wget -O $@ -c $(EXT_HTTP)antlr-runtime-3.5.2.jar || wget -O $@ -c $(AD_EXT_HTTP)antlr-runtime-3.5.2.jar

$(LIB_DIR)avalon-framework-api-4.3.1.jar:
	wget -O $@ -c $(EXT_HTTP)avalon-framework-api-4.3.1.jar || wget -O $@ -c $(AD_EXT_HTTP)avalon-framework-api-4.3.1.jar

$(LIB_DIR)avalon-framework-impl-4.3.1.jar:
	wget -O $@ -c $(EXT_HTTP)avalon-framework-impl-4.3.1.jar || wget -O $@ -c $(AD_EXT_HTTP)avalon-framework-impl-4.3.1.jar

$(LIB_DIR)commons-codec-1.11.jar:
	wget -O $@ -c $(EXT_HTTP)commons-codec-1.11.jar || wget -O $@ -c $(AD_EXT_HTTP)commons-codec-1.11.jar

$(LIB_DIR)commons-compress-1.12.jar:
	wget -O $@ -c $(EXT_HTTP)commons-compress-1.12.jar || wget -O $@ -c $(AD_EXT_HTTP)commons-compress-1.12.jar

$(LIB_DIR)commons-io-2.5.jar:
	wget -O $@ -c $(EXT_HTTP)commons-io-2.5.jar || wget -O $@ -c $(AD_EXT_HTTP)commons-io-2.5.jar

$(LIB_DIR)commons-lang3-3.5.jar:
	wget -O $@ -c $(EXT_HTTP)commons-lang3-3.5.jar || wget -O $@ -c $(AD_EXT_HTTP)commons-lang3-3.5.jar

$(LIB_DIR)docx4j-6.0.1.jar:
	wget -O $@ -c $(DOCX4J_HTTP) || wget -O $@ -c $(AD_EXT_HTTP)docx4j-6.0.1.jar

$(LIB_DIR)guava-20.0.jar:
	wget -O $@ -c $(EXT_HTTP)guava-20.0.jar || wget -O $@ -c $(AD_EXT_HTTP)guava-20.0.jar

$(LIB_DIR)httpclient-4.5.6.jar:
	wget -O $@ -c $(EXT_HTTP)httpclient-4.5.6.jar || wget -O $@ -c $(AD_EXT_HTTP)httpclient-4.5.6.jar

$(LIB_DIR)httpcore-4.4.10.jar:
	wget -O $@ -c $(EXT_HTTP)httpcore-4.4.10.jar || wget -O $@ -c $(AD_EXT_HTTP)httpcore-4.4.10.jar

$(LIB_DIR)jackson-annotations-2.7.0.jar:
	wget -O $@ -c $(EXT_HTTP)jackson-annotations-2.7.0.jar || wget -O $@ -c $(AD_EXT_HTTP)jackson-annotations-2.7.0.jar

$(LIB_DIR)jackson-core-2.7.9.jar:
	wget -O $@ -c $(EXT_HTTP)jackson-core-2.7.9.jar || wget -O $@ -c $(AD_EXT_HTTP)jackson-core-2.7.9.jar

$(LIB_DIR)jackson-databind-2.7.9.4.jar:
	wget -O $@ -c $(EXT_HTTP)jackson-databind-2.7.9.4.jar || wget -O $@ -c $(AD_EXT_HTTP)jackson-databind-2.7.9.4.jar

$(LIB_DIR)jaxb-svg11-1.0.2.jar:
	wget -O $@ -c $(EXT_HTTP)jaxb-svg11-1.0.2.jar || wget -O $@ -c $(AD_EXT_HTTP)jaxb-svg11-1.0.2.jar

$(LIB_DIR)jcl-over-slf4j-1.7.25.jar:
	wget -O $@ -c $(EXT_HTTP)jcl-over-slf4j-1.7.25.jar || wget -O $@ -c $(AD_EXT_HTTP)jcl-over-slf4j-1.7.25.jar

$(LIB_DIR)log4j-1.2.17.jar:
	wget -O $@ -c $(EXT_HTTP)log4j-1.2.17.jar || wget -O $@ -c $(AD_EXT_HTTP)log4j-1.2.17.jar

$(LIB_DIR)lorem-2.1.jar:
	wget -O $@ -c $(EXT_HTTP)lorem-2.1.jar || wget -O $@ -c $(AD_EXT_HTTP)lorem-2.1.jar

$(LIB_DIR)mbassador-1.2.4.2.jar:
	wget -O $@ -c $(EXT_HTTP)mbassador-1.2.4.2.jar || wget -O $@ -c $(AD_EXT_HTTP)mbassador-1.2.4.2.jar

$(LIB_DIR)serializer-2.7.2.jar:
	wget -O $@ -c $(EXT_HTTP)serializer-2.7.2.jar || wget -O $@ -c $(AD_EXT_HTTP)serializer-2.7.2.jar

$(LIB_DIR)slf4j-api-1.7.25.jar:
	wget -O $@ -c $(EXT_HTTP)slf4j-api-1.7.25.jar || wget -O $@ -c $(AD_EXT_HTTP)slf4j-api-1.7.25.jar

$(LIB_DIR)slf4j-log4j12-1.7.25.jar:
	wget -O $@ -c $(EXT_HTTP)slf4j-log4j12-1.7.25.jar || wget -O $@ -c $(AD_EXT_HTTP)slf4j-log4j12-1.7.25.jar

$(LIB_DIR)stringtemplate-3.2.1.jar:
	wget -O $@ -c $(EXT_HTTP)stringtemplate-3.2.1.jar || wget -O $@ -c $(AD_EXT_HTTP)stringtemplate-3.2.1.jar

$(LIB_DIR)wmf2svg-0.9.8.jar:
	wget -O $@ -c $(EXT_HTTP)wmf2svg-0.9.8.jar || wget -O $@ -c $(AD_EXT_HTTP)wmf2svg-0.9.8.jar

$(LIB_DIR)xalan-2.7.2.jar:
	wget -O $@ -c $(EXT_HTTP)xalan-2.7.2.jar || wget -O $@ -c $(AD_EXT_HTTP)xalan-2.7.2.jar

$(LIB_DIR)xmlgraphics-commons-2.3.jar:
	wget -O $@ -c $(EXT_HTTP)xmlgraphics-commons-2.3.jar || wget -O $@ -c $(AD_EXT_HTTP)xmlgraphics-commons-2.3.jar

$(BUILD_DIR)docxit: $(SRC_DIR)$(C_DIR)docxit.cpp $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o $(BUILD_DIR)configOp.o 
	$(CXX) $(CFLAGS) $^ -o $@ 

$(BUILD_DIR)init: $(SRC_DIR)$(C_DIR)init.c
	$(CC) $(CFLAGS) $^ -o $@ 
	
$(BUILD_DIR)deinit: $(SRC_DIR)$(C_DIR)deinit.c
	$(CC) $(CFLAGS) $^ -o $@ 

$(BUILD_DIR)addIndex: $(SRC_DIR)$(C_DIR)addIndex.cpp $(BUILD_DIR)sha1.o $(BUILD_DIR)blobCreate.o $(BUILD_DIR)indexOp.o $(BUILD_DIR)shellCommand.o $(BUILD_DIR)docxitPath.o
	$(CXX) $(CFLAGS) $^ -o $@ -lpthread 

$(BUILD_DIR)commit: $(SRC_DIR)$(C_DIR)commit.cpp $(BUILD_DIR)sha1.o $(BUILD_DIR)blobCreate.o $(BUILD_DIR)indexOp.o $(BUILD_DIR)commitTree.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $@

$(BUILD_DIR)removeIndex: $(SRC_DIR)$(C_DIR)removeIndex.c $(BUILD_DIR)indexOp.o
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

$(BUILD_DIR)printIndex: $(SRC_DIR)$(C_DIR)printIndex.cpp $(BUILD_DIR)indexOp.o $(BUILD_DIR)docxitPath.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $@

$(BUILD_DIR)fileop.jar: $(BUILD_DIR)java
	jar cvfm $@ $^/META-INF/MANIFEST.MF -C $^ .
	
$(BUILD_DIR)java: $(SRC_DIR)$(JAVA_DIR)*.java
	mkdir -p $@/docxit
	javac -Djava.ext.dirs=$(LIB_DIR) $^ -d $@/
	mkdir -p $@/META-INF
	cp $(SRC_DIR)$(JAVA_DIR)docx4j.properties $@
	cp $(SRC_DIR)$(JAVA_DIR)log4j.properties $@
	cp $(SRC_DIR)$(JAVA_DIR)MANIFEST.MF $@/META-INF/MANIFEST.MF

$(BUILD_DIR)printConfig: $(SRC_DIR)$(C_DIR)printConfig.cpp $(BUILD_DIR)configOp.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $@

$(BUILD_DIR)config: $(SRC_DIR)$(C_DIR)config.cpp $(BUILD_DIR)configOp.o $(BUILD_DIR)shellCommand.o
	$(CXX) $(CFLAGS) $^ -o $@
	
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

$(BUILD_DIR)configOp.o: $(SRC_DIR)$(C_DIR)configOp.cpp
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
	cp $(SRC_DIR)$(SHELL_DIR)diff.sh $(EXE_DIR)diff
	echo "source $(BASH_COMP_DIR)docxit_completion  # docxit auto complete" >> ~/.bashrc
	cp $(BUILD_DIR)docxit $(MY_PATH)
	cp $(BUILD_DIR)init $(EXE_DIR)init
	cp $(BUILD_DIR)deinit $(EXE_DIR)deinit
	cp $(BUILD_DIR)addIndex $(EXE_DIR)addIndex
	cp $(BUILD_DIR)removeIndex $(EXE_DIR)removeIndex
	cp $(BUILD_DIR)commit $(EXE_DIR)commit
	cp $(BUILD_DIR)config $(EXE_DIR)config
	cp $(BUILD_DIR)fileop.jar $(EXE_DIR)fileop.jar
	cp -r $(LIB_DIR) $(EXE_DIR)externallib 

install_debug:
	cp $(BUILD_DIR)printIndex $(MY_PATH)
	cp $(BUILD_DIR)printConfig $(MY_PATH)

uninstall:
	-rm -f $(BASH_COMP_DIR)docxit_completion
	sed -i '/# docxit auto complete/d' ~/.bashrc
	-rm -f $(MY_PATH)docxit $(MY_PATH)printIndex $(MY_PATH)printConfig
	-rm -rf $(EXE_DIR)
