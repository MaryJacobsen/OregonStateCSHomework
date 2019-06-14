all: compiler

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

compiler: ast.cpp parser.cpp scanner.cpp
	g++ -std=c++11 ast.cpp parser.cpp scanner.cpp `llvm-config-7.0-64 --cppflags --ldflags --libs --system-libs all` -o compiler

output.o: compiler
	./compiler < testing_code/p1.py

optimize: compiler
	./compiler -O < testing_code/p1.py

test: test.cpp output.o
	g++ test.cpp output.o -o test

clean:
	rm -f parse compiler scanner.cpp parser.cpp parser.hpp output.o
