CC=g++
exe=zoo

$(exe): animal.o oliphant.o tiger.o polar_bear.o penguin.o zoo.o driver.o
	$(CC) animal.o oliphant.o tiger.o polar_bear.o penguin.o zoo.o driver.o -o$(exe)
animal.o: animal.cpp
	$(CC) -c animal.cpp
oliphant.o: oliphant.cpp
	$(CC) -c oliphant.cpp
tiger.o: tiger.cpp
	$(CC) -c tiger.cpp
polar_bear.o: polar_bear.cpp
	$(CC) -c polar_bear.cpp
penguin.o: penguin.cpp
	$(CC) -c penguin.cpp 
zoo.o: zoo.cpp
	$(CC) -c zoo.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
