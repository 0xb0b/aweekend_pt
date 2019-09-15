# compiled from:
# 1. A Super-Simple Makefile for Medium-Sized C/C++ Projects
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
# 2. Auto-Dependency Generation
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

# features:
# * out of source builds (build artifacts go to a folder separate from the
# source);
# * atomatic list of source files;
# * automatic dependencies;
# should build the project with the following structure:
# <project>/src/  // folder with source files and internal headers
# <project>/include/  // folder with headers of external interface
# build artifacts go to build folder which may be separate from the project
# location;

BUILD_DIR := .build
SRC_DIR := tests
OUT := $(BUILD_DIR)/runtests

SRC_FILES := $(shell find $(SRC_DIR) -name \*.cpp)
OBJ_FILES := $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)
DEP_FILES := $(OBJ_FILES:.o=.d)

CXX = clang
CXXFLAGS = -O2 -std=c++11
LDFLAGS = -lstdc++ -lm

# flags for automatic dependencies generation
# write dependencies to temporary *.tmpd files first and rename to *.d files
# after successful compilation (to avoid corrupted dependency files in case
# of compilation failure)
DEPFLAGS = -MMD -MP -MF $(BUILD_DIR)/$*.tmpd

# comment this out if there is no include directories
INC_DIRS := include
# make include flags if there are include directories
ifdef INC_DIRS
CPPFLAGS := $(addprefix -I,$(INC_DIRS))
endif

$(OUT): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@ $(LDFLAGS)

# make build directory and subdirectories if they do not exist
# the subdirectory structure of build directory is the same as src/
#
# @ is at the start of the shell command to supress echo of the command to the
# output
#
# after the successful compilation rename the temporary dependency file to the
# final *.d
#
# touch object file to avoid it being older than dependency file which causes
# unnecessary rebuilds
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
	mv -f $(BUILD_DIR)/$*.tmpd $(BUILD_DIR)/$*.d && touch $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(DEP_FILES)
