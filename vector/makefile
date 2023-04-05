CPPFLAGS = -O3 -std=c++20

main: clean
	g++ $(CPPFLAGS) main.cpp mylib.cpp -o main && ./main

test: clean
	g++ $(CPPFLAGS) testing.cpp mylib.cpp -o testing && ./testing

test2: clean
	g++ $(CPPFLAGS) testing2.cpp mylib.cpp -o testing2 && ./testing2
clean:
	rm -f studFail.txt studPass.txt