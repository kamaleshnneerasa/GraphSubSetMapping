compile:
	@echo "Compiling run1..."
	@g++ -std=c++11 -O3 -I ./headers ./code/code.cpp -o a1
	@echo "Compilimg run2..."
	@g++ -std=c++11 -O3 ./code/mapping.cpp -o a2