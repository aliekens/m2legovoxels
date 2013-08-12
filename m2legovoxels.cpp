/*

Copyright (C) 2009  Anthony Liekens <anthony@liekens.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "model.h"
#include "voxelspace.h"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#define COORDINATE2D std::pair< double, double >

COORDINATE2D
difference( COORDINATE2D a, COORDINATE2D b ) {
	return COORDINATE2D( a.first - b.first, a.second - b.second );
}

double
dotProduct( COORDINATE2D a, COORDINATE2D b ) {
	return a.first * b.first + a.second * b.second;
}

bool
pointInTriangle( COORDINATE2D p, COORDINATE2D a, COORDINATE2D b, COORDINATE2D c ) {
	
	// from http://www.blackpawn.com/texts/pointinpoly/default.html
	
	if( ( a.first == b.first ) && ( a.first == c.first ) )
		return false;
	if( ( a.second == b.second ) && ( a.second == c.second ) )
		return false;
	
	// compute vectors
	COORDINATE2D v0 = difference( c, a );
	COORDINATE2D v1 = difference( b, a );
	COORDINATE2D v2 = difference( p, a );
	
	// compute dot products
	double dot00 = dotProduct( v0, v0 );
	double dot01 = dotProduct( v0, v1 );
	double dot02 = dotProduct( v0, v2 );
	double dot11 = dotProduct( v1, v1 );
	double dot12 = dotProduct( v1, v2 );
	
	// compute barycentric coordinates
	double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u > 0) && (v > 0) && (u + v < 1);

}

int main( int argc, char** argv ) {
	
	double epsilon = 1e-5;
	
	std::cerr << "m2legovoxels  Copyright (C) 2009  Anthony Liekens <anthony@liekens.net>" << std::endl;
	std::cerr << "This program comes with ABSOLUTELY NO WARRANTY; for details see COPYING." << std::endl;
	std::cerr << "This is free software, and you are welcome to redistribute it" << std::endl;
	std::cerr << "under certain conditions; see COPYING for details." << std::endl;
	
	if( argc != 3 ){
		std::cerr << "Usage: " << argv[ 0 ] << " model.m nrlayers" << std::endl;
		exit(1);
	}
	std::string filename = argv[ 1 ];
	int layers = atoi( argv[ 2 ] );
	
	Model m( filename );
	m.computeStatistics();
	
	int samples = 4;
	float stepz = ( m.maxz - m.minz ) / layers;
	float stepxy = 0.8 * stepz / 0.96;
	stepz /= samples;
	stepxy /= samples;
	
	int layercounter = 0;
	int voxelcounter = 0;
	
	int counterx = 0;
	int countery = 0;
	int counterz = 0;

	VoxelSpace voxelspace;
	
	int percentdone = 0;
	
	for( float z = m.minz - stepz; z <= m.maxz + stepz; z += stepz ) {
		
		// progress
		while( ( z - m.minz ) / ( m.maxz - m.minz ) * 100 > percentdone ) {
			std::cerr << "Raytracing (" << percentdone << "% done)" << std::endl;
			percentdone += 5;
		}
		
		// select only those faces with z-values that we may actually hit, instead of going over all triangles for every ray
		std::vector< Face > faces;
		for( std::vector< Face >::iterator i = m.faces.begin(); i != m.faces.end(); i++ )
			if( ( i->minz <= z ) && ( i->maxz >= z ) )
				faces.push_back( *i );
		
		countery = 0;
		for( float y = m.miny - stepxy; y <= m.maxy + stepxy; y += stepxy ) {
			std::vector< double > intersectRayDistances;
			for( std::vector< Face >::iterator i = faces.begin(); i != faces.end(); i++ ) {
				if( pointInTriangle( COORDINATE2D( y, z ), COORDINATE2D( (*i)[ 0 ].y, (*i)[ 0 ].z ), COORDINATE2D( (*i)[ 1 ].y, (*i)[ 1 ].z ), COORDINATE2D( (*i)[ 2 ].y, (*i)[ 2 ].z ) ) ) {
					intersectRayDistances.push_back( i->intersectRayDistance( Vertex( m.minx, y, z ), Vertex( 1, 0, 0 ) ) );
				}
			}
			counterx = 0;
			for( float x = m.minx - stepxy; x <= m.maxx + stepxy; x += stepxy ) {
				int counter = 0;
				for( std::vector< double >::iterator i = intersectRayDistances.begin(); i != intersectRayDistances.end(); i++ )
					if( x > *i + m.minx )
						counter++;
				if( counter % 2 != 0 ) {
					if( intersectRayDistances.size() % 2 == 1 )
						voxelspace[ Voxel( counterx / samples, countery / samples, counterz / samples ) ] += 0.5; // uncertain, as there's an odd number of ray-triangle intersections for the current ray
					else
						voxelspace[ Voxel( counterx / samples, countery / samples, counterz / samples ) ] += 1;
				}
				counterx++;
			}
			countery++;
		}
		layercounter++;
		counterz++;
	}
	
	voxelspace.applyThreshold( samples * samples * samples / 2.5 );
	voxelspace.computeStatistics();
	
	voxelspace.makeHollow3();

	voxelspace.printLayers();
	voxelspace.printProfiles();
	
	std::cerr << voxelspace.size() << " voxels" << std::endl;
	voxelspace.computeStatistics();

	std::ofstream ofs( ( filename + ".ldr" ).c_str() );
	voxelspace.printLDraw( ofs );
	ofs.close();

}
