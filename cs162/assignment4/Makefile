CC=g++  
exe=a.out

$(exe): game.o room.o escape_rope.o empty.o wumpus.o gold.o pit.o bats.o driver.o
	$(CC) game.o room.o escape_rope.o empty.o wumpus.o gold.o pit.o bats.o driver.o -o $(exe)
game.o: game.cpp
	$(CC) -c game.cpp
room.o: room.cpp
	$(CC) -c room.cpp
empty.o: empty.cpp
	$(CC) -c empty.cpp
escape_rope.o: escape_rope.cpp
	$(CC) -c escape_rope.cpp
wumpus.o: wumpus.cpp
	$(CC) -c wumpus.cpp
gold.o: gold.cpp
	$(CC) -c gold.cpp
pit.o: pit.cpp
	$(CC) -c pit.cpp
bats.o: bats.cpp
	$(CC) -c bats.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
