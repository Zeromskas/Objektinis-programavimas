main: clean
	g++ -O3 -std=c++20 main.cpp mylib.cpp -o main && ./main
clean:
	rm -f studFail.txt studPass.txt

