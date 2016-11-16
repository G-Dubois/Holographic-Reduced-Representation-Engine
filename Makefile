all:
	g++ -std=c++11 main.cpp hrrengine.cpp -lgsl -lblas -o hrr.exe
clean:
	rm hrr.exe

