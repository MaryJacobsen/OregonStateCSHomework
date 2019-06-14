all: parser

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

parser: main.cpp scanner.cpp parser.cpp parser.hpp
	g++ -std=c++11 main.cpp scanner.cpp parser.cpp -o parser

# make test -i hides errors
test: clean parser
	mkdir output/
	./parser < testing_code/p1.py > output/p1_result.cpp
	diff output/p1_result.cpp example_output/p1.cpp ; if [ $$? -eq 0 ] ; then echo "P1 PASSED" ; fi

	./parser < testing_code/p2.py > output/p2_result.cpp
	diff output/p2_result.cpp example_output/p2.cpp ; if [ $$? -eq 0 ] ; then echo "P2 PASSED" ; fi

	./parser < testing_code/p3.py > output/p3_result.cpp
	diff output/p3_result.cpp example_output/p3.cpp ; if [ $$? -eq 0 ] ; then echo "P3 PASSED" ; fi

	./parser < testing_code/error1.py
	./parser < testing_code/error2.py
	./parser < testing_code/error3.py

clean:
	rm -f scan scanner.cpp parser parser.cpp parser.hpp parser.output
	rm -rf output/
