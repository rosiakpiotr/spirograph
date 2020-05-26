ifeq ($(mode),release)
   CPPFLAGS := -O3
else
   mode = debug
   CPPFLAGS := -g -Wall
endif

SRC_DIR := src
OBJ_DIR := build/$(mode)/obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -ltgui -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS += -Iinclude -std=c++14 -pedantic
FILENAME := spirograph

$(FILENAME): $(OBJ_FILES)
	g++ -o build/$(mode)/$@ $^ -g $(LDFLAGS)

clean:
	touch build/debug/$(FILENAME)
	touch build/release/$(FILENAME)

	rm -rf build/debug/obj/*
	rm build/debug/$(FILENAME)
	rm -rf build/release/obj/*
	rm build/release/$(FILENAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
