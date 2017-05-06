CC=g++

COMPILE_FLAGS = -g -std=c++11 -Wall -c
LINKER_FLAGS = -g
LIBS = -l bcm2835 -l rt

OBJECTS = \
	test.o \
	PCA9685.o \
	Servos.o \
	AccurateTiming.o

all: pca.o servos.o timer.o main.o
	$(CC) $(LINKER_FLAGS) -o runner $(OBJECTS) $(LIBS)

main.o: test.cpp
	$(CC) $(COMPILE_FLAGS) test.cpp

pca.o: Libraries/PCA9685/PCA9685.cpp
	$(CC) $(COMPILE_FLAGS) Libraries/PCA9685/PCA9685.cpp
servos.o: Modules/Servos/Servos.cpp
	$(CC) $(COMPILE_FLAGS) Modules/Servos/Servos.cpp
timer.o: Libraries/Timer/AccurateTiming.cpp
	$(CC) $(COMPILE_FLAGS) Libraries/Timer/AccurateTiming.cpp

clean:
	$(RM) $(OBJECTS) runner
