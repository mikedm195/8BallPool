ALL: pool
.PHONY= clean

pool: pool.cpp
	g++ -std=c++11 *.cpp -o pool -lGL -lGLU -lglut -w

clean:
	\rm -f pool
