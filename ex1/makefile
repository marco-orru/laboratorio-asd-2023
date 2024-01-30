C_COMPILER = gcc

C_COMPILER_FLAGS = -std=c11 -pedantic -Wall -O3
C_COMPILER_FLAGS_PROFILER = $(C_COMPILER_FLAGS) -DENABLE_PROFILER=1

MAIN_OUTPUT_DIR = bin
UT_OUTPUT_DIR = $(MAIN_OUTPUT_DIR)/ut

MAIN_NAME = main_ex1
PROFILER_NAME = profiler_ex1
UT_NAME = ut_ex1

SRC_DIR = src
LIB_DIR = $(SRC_DIR)/library
UT_DIR = $(SRC_DIR)/ut
UT_SUITE_DIR = $(UT_DIR)/suite

MAIN_SOURCES = $(SRC_DIR)/main.c 						\
               $(LIB_DIR)/merge-binary-insertion-sort.c \
               $(LIB_DIR)/records-sorter.c

UT_SOURCES = $(UT_DIR)/ut_main.c						\
		     $(LIB_DIR)/merge-binary-insertion-sort.c	\
		     $(UT_SUITE_DIR)/unity.c

MAIN_INC = -I$(LIB_DIR)
UT_INC = -I$(LIB_DIR) -I$(UT_SUITE_DIR)

all: $(MAIN_NAME) $(PROFILER_NAME) $(UT_NAME)

$(MAIN_NAME): $(MAIN_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(MAIN_INC) $^ -o $(MAIN_OUTPUT_DIR)/$@

$(PROFILER_NAME): $(MAIN_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS_PROFILER) $(MAIN_INC) $^ -o $(MAIN_OUTPUT_DIR)/$@

$(UT_NAME): $(UT_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(UT_INC) $^ -o $(UT_OUTPUT_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)