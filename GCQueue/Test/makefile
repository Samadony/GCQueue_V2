#Unit Test code directory
TARGET = GCQueue.exe
TST_SRCS_DIR = ./
TST_INCS_DIR = ./
TST_OBJS_DIR = ./
TST_BIN_DIR	 = ./

#Unit under test directory
TGT_SRCS_DIR = ../
TGT_INCS_DIR = ../


#Google test libraries and headers
TEST_HARNESS_DIR 	= ../../GTest/
GTEST_HDRS		= $(TEST_HARNESS_DIR)/Export/include/
GMOCK_HDRS		= $(TEST_HARNESS_DIR)/Export/include/
GTEST_LIB_DIR	= $(TEST_HARNESS_DIR)Export/
GMOCK_LIB_DIR	= $(TEST_HARNESS_DIR)Export/

#Unit test source code, objs and exe
TST_SRCS = $(wildcard $(TST_SRCS_DIR)*.c) 
TST_OBJS = $(patsubst $(TST_SRCS_DIR)%.c,$(TST_OBJS_DIR)%.o,$(TST_SRCS))
TST_BIN  = $(TGT_BIN_DIR)$(TARGET)

#Unit under test sourcecode
TGT_SRCS = $(wildcard $(TGT_SRCS_DIR)*.c) 
TGT_OBJS = $(patsubst $(TGT_SRCS_DIR)%.c,$(TST_OBJS_DIR)%.o,$(TGT_SRCS))
OBJS = $(TGT_OBJS) $(TST_OBJS)

#Preprocessor Flags
CPP_FLAGS = -I$(GTEST_HDRS) -I$(GMOCK_HDRS) -I$(TGT_INCS_DIR) -DUnitTestActive
#Compiler`s Flags
CXX_FLAGS = -Wall -Wextra -pthread
#Linker`s Flags
#gmock has symbols needed by gtest apparently, so the gmock (unknown symbols) 
#shall be linked before gtest
LD_FLAGS = -L$(GTEST_LIB_DIR) -L$(GMOCK_LIB_DIR) -lgmock -lgmock_main -lgtest -lgtest_main

#Compiler`s utilities
CXX = g++ 

.PHONY: retest test clean 

retest: clean test
 
test: build
	./$(TARGET)
	
build: $(TST_BIN)

$(TST_BIN): $(OBJS)
	$(CXX) $(LD_FLAGS) $^ -o $@ 
	rm -f *.o

$(TGT_OBJS): $(TGT_SRCS)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c $^ 
	
$(TST_OBJS): $(TST_SRCS)
	$(CXX) $(CPP_FLAGS) $(CXX_FLAGS) -c $^ 
	

clean:
	rm -f $(wildcard $(OBJS_DIR)*.o)
	rm -f $(wildcard $(BIN_DIR)*.exe)
	