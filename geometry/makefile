CC=g++
CFLAGS= -O3 -march=native -Wall -std=c++14


geometry : Mesh.h Triangle.h Point3.h main.cpp Mesh.h read_stl_bin.h
	$(CC) $(CFLAGS) main.cpp read_stl_bin.cpp -o geometry1

clean:
	\rm *.o
