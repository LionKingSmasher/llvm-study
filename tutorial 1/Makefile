LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)
CXX=g++

OUTPUT=example
OBJ_FILE= \
	example1.cc

all: $(OUTPUT)

clear: 
	rm -rf $(OUTPUT)

%.o : %.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^

$(OUTPUT) : $(OBJ_FILE)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `$(LLVM_CONFIG) --libs bitreader core support`