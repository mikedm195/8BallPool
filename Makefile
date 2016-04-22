ALL: pool
.PHONY= clean

pool: pool.cpp
	g++ -std=c++11 bola.cpp pool.cpp glm.cpp Texture.cpp -o pool -lGL -lGLU -lglut -w

clean:
	\rm -f pool
