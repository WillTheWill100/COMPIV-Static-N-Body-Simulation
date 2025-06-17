CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# Your .hpp files
DEPS = Universe.hpp CelestialBody.hpp
# Your compiled .o files
OBJECTS = Universe.o CelestialBody.o
# The name of your program
PROGRAM = NBody
LIBRARY = NBody.a

.PHONY: all clean lint

all: $(PROGRAM) test

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

test: test.o $(OBJECTS) $(LIBRARY)
	$(CC) $(CFLAGS) -o test $^ $(LIB)

$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(LIBRARY): Universe.o CelestialBody.o
	ar rcs $@ $^

clean:
	rm -f *.o $(PROGRAM) $(LIBRARY) test

lint:
	cpplint *.cpp *.hpp
