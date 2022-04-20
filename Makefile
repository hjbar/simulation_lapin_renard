NAME := Lapin

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := _build

CXX ?= c++
CPPFLAGS ?= -std=c++20 -W -Wall -Wextra -Wdouble-promotion -Wformat -Winit-self  -Wmissing-include-dirs -Wswitch-default  -Wswitch-enum -Wunused -Wunused-parameter -Wuninitialized -Wunknown-pragmas -fstrict-overflow -Wstrict-overflow=2 -Wmissing-format-attribute -Wstrict-aliasing -Wfloat-equal -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wmissing-declarations -Wredundant-decls -Wpacked -Wpadded -Winline -Wvla -Wdisabled-optimization -Wstack-protector -Winvalid-pch -Wshadow -pedantic-errors --pedantic -g -Werror -O3 -pipe -funsigned-char -fsigned-bitfields -fPIC -fdiagnostics-color=auto

INCLUDE := -I$(INCLUDE_DIR)

LDFLAGS := -lfmt -fPIE

TARGET := $(NAME).exe
HPP_FILES := $(wildcard $(INCLUDE_DIR)/*.hpp)
CPP_FILES := $(HPP_FILES:$(INCLUDE_DIR)/%.hpp=$(SRC_DIR)/%.cpp)
O_FILES := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: clean mrproper

default: build

all: build clean

build: $(TARGET)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(INCLUDE)

$(TARGET): $(BUILD_DIR) $(O_FILES)
	$(CXX) -o $@ $(O_FILES) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

mrproper: clean
	rm -f $(TARGET)

fmt:
	find src/ -iname \*.cpp | xargs clang-format -style=file -i
	find include/ -iname \*.hpp | xargs clang-format -style=file -i
