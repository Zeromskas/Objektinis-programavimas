main: clean
	g++ -O3 -std=c++20 main.cpp mylib.cpp -o main && ./main

test: clean
	g++ -O3 -std=c++20 testing.cpp mylib.cpp -o testing && ./testing
clean:
	rm -f studFail.txt studPass.txt



