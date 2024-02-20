NAME := lapin
NAME_TEST := test
NAME_VIDEO := video

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := _build

CXX ?= c++
CPPFLAGS ?= -std=c++20 -W -Wall -Wextra -Wdouble-promotion -Wformat -Winit-self  -Wmissing-include-dirs -Wswitch-default  -Wswitch-enum -Wunused -Wunused-parameter -Wuninitialized -Wunknown-pragmas -fstrict-overflow -Wstrict-overflow=2 -Wmissing-format-attribute -Wstrict-aliasing -Wfloat-equal -Wundef -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wmissing-declarations -Wredundant-decls -Wpacked -Wpadded -Winline -Wvla -Wdisabled-optimization -Wstack-protector -Winvalid-pch -Wshadow -pedantic-errors --pedantic -g -Werror -O3 -pipe -funsigned-char -fsigned-bitfields -fPIC -fdiagnostics-color=auto

INCLUDE := -I$(INCLUDE_DIR)

LDFLAGS := -fPIE

TARGET := $(NAME).exe
TARGET_TEST := $(NAME_TEST).exe
TARGET_VIDEO := $(NAME_VIDEO).exe

HPP_FILES := $(wildcard $(INCLUDE_DIR)/*.hpp)
CPP_FILES := $(HPP_FILES:$(INCLUDE_DIR)/%.hpp=$(SRC_DIR)/%.cpp)

O_FILES_ALL := $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
O_FILES := $(filter-out $(BUILD_DIR)/test.o $(BUILD_DIR)/video.o, $(O_FILES_ALL))
O_FILES_TEST := $(filter-out $(BUILD_DIR)/main.o $(BUILD_DIR)/video.o, $(O_FILES_ALL))
O_FILES_VIDEO := $(filter-out $(BUILD_DIR)/main.o $(BUILD_DIR)/test.o, $(O_FILES_ALL))

.PHONY: clean supprPhoto mrproper

default: build

all: build video test

build: $(TARGET)

check: $(TARGET_TEST)
	./$(TARGET_TEST) -s

test: $(TARGET_TEST)
	./$(TARGET_TEST)

video: $(TARGET_VIDEO)

exec: $(TARGET_VIDEO)
	./$(TARGET_VIDEO)
	convert -scale 300 -delay 10 img*.ppm movie.gif
	rm -f img*.ppm
	firefox movie.gif

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CXX) -o $@ -c $< $(CPPFLAGS) $(INCLUDE)

$(TARGET): $(BUILD_DIR) $(O_FILES)
	$(CXX) -o $@ $(O_FILES) $(LDFLAGS)

$(TARGET_TEST): $(BUILD_DIR) $(O_FILES_TEST)
	$(CXX) -o $@ $(O_FILES_TEST) $(LDFLAGS)

$(TARGET_VIDEO): $(BUILD_DIR) $(O_FILES_VIDEO)
	$(CXX) -o $@ $(O_FILES_VIDEO) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

supprPhoto:
	rm -f img*.ppm

mrproper: clean supprPhoto
	rm -f $(TARGET)
	rm -f $(TARGET_TEST)
	rm -f $(TARGET_VIDEO)
	rm -f movie.gif

fmt:
	find src/ -iname \*.cpp | xargs clang-format -style=file -i
	find include/ -iname \*.hpp | xargs clang-format -style=file -i
