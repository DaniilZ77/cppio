CPPFLAGS = -I./include -std=c++20
DEBUG = -g
CC = g++
SRC = src
TARGET = lab-10_cppio
OBJ = obj

all: $(OBJ)/ $(TARGET)

$(TARGET): $(OBJ)/main.o $(OBJ)/bit_manip.o $(OBJ)/employees.o
	$(CC) $(CPPFLAGS) $(DEBUG) $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CC) $(CPPFLAGS) $(DEBUG) -c $< -o $@

$(OBJ)/bit_manip.o: $(SRC)/bit_manip.cpp
	$(CC) $(CPPFLAGS) $(DEBUG) -c $< -o $@

$(OBJ)/employees.o: $(SRC)/employees.cpp
	$(CC) $(CPPFLAGS) $(DEBUG) -c $< -o $@

$(OBJ)/:
	mkdir -p $(OBJ)

clean:
	rm -f $(OBJ)/*.o $(TARGET)
