# gets project name must not contain spaces
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
ProjectName := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

# compiler
CC = g++
CFLAG = -std=c++11

# path variables
BIN_DIR = build
INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib/wx

# source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRCS))

# library files
LIBS := $(patsubst $(LIB_DIR)/lib%.a,-l %, $(wildcard $(LIB_DIR)/*.a))

# rules
.PHONY: all run clean echo

all: $(BIN_DIR)/$(ProjectName)

echo:
	@echo $(LIBS)

# build in debug mode
$(BIN_DIR)/$(ProjectName): $(OBJS) # $< not working!
	@echo bulding project:
	$(CC) $(CFLAG) -g $(OBJS) -o $@ -I $(INC_DIR) -L $(LIB_DIR) $(LIBS)
	@echo done!

# static rule
# genetate .o files in obj_dir from source files
$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo creating object files:
	$(CC) $(CFLAG) -c $< -I $(INC_DIR) -o $@
	@echo done!

# runs output file in external console
# windows only
run: all
	cmd /c start cmd /k "cd $(BIN_DIR) & $(ProjectName).exe & exit"

# windows only
clean:
	del /f $(OBJ_DIR)\*.o $(BIN_DIR)\*.exe
	@echo Clean Complete!