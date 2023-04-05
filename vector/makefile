main: clean
	g++ -O3 -std=c++20 main.cpp mylib.cpp -o main && ./main

test: clean
	g++ -O3 -std=c++20 testing.cpp mylib.cpp -o testing && ./testing
test2: clean
	g++ -O3 -std=c++20 testing2.cpp mylib.cpp -o testing && ./testing
clean:
	rm -f studFail.txt studPass.txt