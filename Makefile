clean:
	rm main.o testcase_generator.o simulator.o

rmsimu:
	rm Simulation*

rmprog:
	rm cashier

.PHONY: clean rmprog rmsimu

main.o: main.cpp main.h testcase_generator.h
	g++ -c $<

testcase_generator.o: testcase_generator.cpp testcase_generator.h
	g++ -c $<

simulator.o: simulator.cpp simulator.h testcase_generator.h testcase_generator.o
	g++ -c $<

cashier: main.o testcase_generator.o simulator.o
	g++ $^ -o $@
	make clean
