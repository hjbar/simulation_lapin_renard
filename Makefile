NAME := lapin
NAME_TEST := test

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := _build

CXX ?= c++
CPPFLAGS ?= -std=c++20 -W -Wall -Wextra -Wdouble-promotion -Wformat -Winit-self  -Wmissing-include-dirs -Wswitch-default  -Wswitch-enum -Wunused -Wunused-parameter -Wuninitialized -Wunknown-pragmas -fstrict-overflow -Wstrict-overflow=2 -Wmissing-format-attribute -Wstrict-aliasing -Wfloat-equal -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wmissing-declarations -Wredundant-decls -Wpacked -Wpadded -Winline -Wvla -Wdisabled-optimization -Wstack-protector -Winvalid-pch -Wshadow -pedantic-errors --pedantic -g -Werror -O3 -pipe -funsigned-char -fsigned-bitfields -fPIC -fdiagnostics-color=auto

INCLUDE := -I$(INCLUDE_DIR)

LDFLAGS := -fPIE

TARGET := $(NAME).exe
TARGET_TEST := $(NAME_TEST).exe

HPP_FILES := $(wildcard $(INCLUDE_DIR)/*.hpp)
CPP_FILES := $(HPP_FILES:$(INCLUDE_DIR)/%.hpp=$(SRC_DIR)/%.cpp)

O_FILES_ALL := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
O_FILES := $(filter-out $(BUILD_DIR)/test.o, $(O_FILES_ALL))
O_FILES_TEST := $(filter-out $(BUILD_DIR)/main.o, $(O_FILES_ALL))

.PHONY: clean mrproper

default: build

all: build test

build: $(TARGET)

check: $(TARGET_TEST)
	./$(TARGET_TEST) -s

test: $(TARGET_TEST)
	./$(TARGET_TEST)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(INCLUDE)

$(TARGET): $(BUILD_DIR) $(O_FILES)
	$(CXX) -o $@ $(O_FILES) $(LDFLAGS)

$(TARGET_TEST): $(BUILD_DIR) $(O_FILES_TEST)
	$(CXX) -o $@ $(O_FILES_TEST) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

mrproper: clean
	rm -f $(TARGET)
	rm -f $(TARGET_TEST)

fmt:
	find src/ -iname \*.cpp | xargs clang-format -style=file -i
	find include/ -iname \*.hpp | xargs clang-format -style=file -i
