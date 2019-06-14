CC=g++
exe=blackjack

$(exe): dealer.o  deck.o  driver.o  game.o  hand.o  player.o
	$(CC) dealer.o  deck.o  driver.o  game.o  hand.o  player.o -o $(exe)
dealer.o: dealer.cpp
	$(CC) -c dealer.cpp
deck.o: deck.cpp
	$(CC) -c deck.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
game.o: game.cpp
	$(CC) -c game.cpp
hand.o: hand.cpp
	$(CC) -c hand.cpp
player.o: player.cpp
	$(CC) -c player.cpp







