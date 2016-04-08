ALL: pool
.PHONY= clean

pool: pool.cpp
	g++ pool.cpp mesa.h -o pool -lGL -lGLU -lglut -w

clean:
	\rm -f pool
