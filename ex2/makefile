C_COMPILER = gcc

C_COMPILER_FLAGS = -std=c11 -pedantic -Wall -O3 -Wno-unknown-pragmas
C_COMPILER_FLAGS_PROFILER = $(C_COMPILER_FLAGS) -D__PROFILER

MAIN_OUTPUT_DIR = bin
PROFILER_OUTPUT_DIR = $(MAIN_OUTPUT_DIR)/profiler
UT_OUTPUT_DIR = $(MAIN_OUTPUT_DIR)/ut

MAIN_NAME = main_ex2
PROFILER_NAME = profiler_ex2
UT_NAME = ut_ex2

SRC_DIR = src
LIB_DIR = $(SRC_DIR)/library
PROFILER_DIR = $(SRC_DIR)/profiler
UT_DIR = $(SRC_DIR)/ut
UT_SUITE_DIR = $(UT_DIR)/suite

MAIN_SOURCES = $(SRC_DIR)/main.c 						\
               $(LIB_DIR)/skip-list.c					\
               $(LIB_DIR)/errors-finder.c				\
               $(LIB_DIR)/comparator.c

PROFILER_SOURCES = $(PROFILER_DIR)/profiler_main.c		\
               $(LIB_DIR)/skip-list.c					\
               $(LIB_DIR)/errors-finder.c				\
               $(LIB_DIR)/comparator.c

UT_SOURCES = $(UT_DIR)/ut_main.c						\
		     $(LIB_DIR)/skip-list.c						\
		     $(UT_SUITE_DIR)/unity.c					\
		     $(LIB_DIR)/comparator.c

MAIN_INC = -I$(LIB_DIR)
PROFILER_INC = -I$(LIB_DIR) -I$(PROFILER_DIR)
UT_INC = -I$(LIB_DIR) -I$(UT_SUITE_DIR)

all: $(MAIN_NAME) $(PROFILER_NAME) $(UT_NAME)

$(MAIN_NAME): $(MAIN_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(MAIN_INC) $^ -o $(MAIN_OUTPUT_DIR)/$@

$(PROFILER_NAME): $(PROFILER_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS_PROFILER) $(PROFILER_INC) $^ -o $(PROFILER_OUTPUT_DIR)/$@

$(UT_NAME): $(UT_SOURCES)
	$(C_COMPILER) $(C_COMPILER_FLAGS) $(UT_INC) $^ -o $(UT_OUTPUT_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)