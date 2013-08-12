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

#include <fstream>

Model::Model( std::string filename ) {
	std::cerr << "Loading model from " << filename;
	std::ifstream ifs( filename.c_str() );
	while( !ifs.eof() ) {
		std::string faceorvertex;
		ifs >> faceorvertex;
		if( faceorvertex == "Vertex" ) {
			int n;
			double x, y, z;
			ifs >> n;
			ifs >> x;
			ifs >> y;
			ifs >> z;
			vertices.push_back( Vertex( x, y, z ) );
			if( vertices.size() % 10000 == 0 )
				std::cerr << vertices.size() << std::endl;
		}
		if( faceorvertex == "Face" ) {
			int n, v1, v2, v3;
			ifs >> n;
			ifs >> v1;
			ifs >> v2;
			ifs >> v3;
			Face face;
			face.push_back( vertices[ v1 ] );
			face.push_back( vertices[ v2 ] );
			face.push_back( vertices[ v3 ] );
			face.updateStatistics();
			faces.push_back( face );
		}
	}
	std::cerr << " (" << vertices.size() << " vertices, " << faces.size() << " faces)." << std::endl;
}

void
Model::computeStatistics() {
	
	for( std::vector< Face >::iterator f = faces.begin(); f != faces.end(); f++ )
	for( std::vector< Vertex >::iterator i = f->begin(); i != f->end(); i++ ) {
		if( i->x < minx )
			minx = i->x;
		if( i->x > maxx )
			maxx = i->x;
		if( i->y < miny )
			miny = i->y;
		if( i->y > maxy )
			maxy = i->y;
		if( i->z < minz )
			minz = i->z;
		if( i->z > maxz )
			maxz = i->z;
	}

}
