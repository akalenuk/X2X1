all:
	clang++ -std=c++14 main.cpp -o main -lstdc++fs 
clean:
	rm main
