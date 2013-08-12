all: m2legovoxels

OBJECTS=model.o vertex.o face.o voxelspace.o voxel.o

m2legovoxels: m2legovoxels.cpp $(OBJECTS)
	g++ -O3 m2legovoxels.cpp -o m2legovoxels $(OBJECTS)

%.o:%.cpp
	g++ -c -O3 $< $(INCLUDES)

clean:
	rm -rf m2legovoxels *.o *~ *.ldr
