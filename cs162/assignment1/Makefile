CC=g++
exe=state_facts

$(exe): state_facts.o run_facts.o
	$(CC) state_facts.o run_facts.o -o $(exe)
state_facts.o: state_facts.cpp
	$(CC) -c state_facts.cpp
run_facts.o: run_facts.cpp
	$(CC) -c run_facts.cpp
clean:
	rm -f a.out $(exe) *.o
