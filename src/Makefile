CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	PCA9685.o \
	Servos.o \

all: pca.o servos.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp

pca.o: libraries/robotois-PCA9685/PCA9685.cpp
	$(CC) $(COMPILE_FLAGS) libraries/robotois-PCA9685/PCA9685.cpp
servos.o: Servos.cpp
	$(CC) $(COMPILE_FLAGS) Servos.cpp

clean:
	$(RM) $(OBJECTS) runner
