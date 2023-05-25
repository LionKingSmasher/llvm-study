LLVM_CONFIG?=llvm-config

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)
CLANGLIBS = \
	-Wl,--start-group \
	-lclang \
	-lclangFrontend \
	-lclangDriver \
	-lclangSerialization \
	-lclangParse \
	-lclangSema \
	-lclangAnalysis \
	-lclangEdit \
	-lclangAST \
	-lclangLex \
	-lclangBasic \
	-Wl,--end-group

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs)

OUTPUT=tutorial2
OBJ_FILE=tutorial2.o

CXX=g++

all: $(OUTPUT)

$(OUTPUT) : $(OBJ_FILE)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(CLANGLIBS) $(LLVMLIBS)

%.o : $(SRC_DIR)/%.cc
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $^

clear:
	rm $(OBJ_FILE)
	