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

#include "face.h"

Face::Face() {
}

Vertex
Face::intersectRay( const Vertex& origin, const Vertex& direction ) const {
	// assume the ray hits the triangle
	double distance = intersectRayDistance( origin, direction );
	return origin + direction * distance;
}

double
Face::intersectRayDistance( const Vertex& origin, const Vertex& direction ) const {
	// assume the ray hits the triangle
	Vertex planeNormal = Vertex::crossProduct( (*this)[ 1 ] - (*this)[ 0 ], (*this)[ 2 ] - (*this)[ 0 ] );
	return - Vertex::dotProduct( origin - (*this)[ 0 ], planeNormal ) / Vertex::dotProduct( direction, planeNormal );
}

void
Face::updateStatistics() {
	minx = (*this)[ 0 ].x;
	maxx = (*this)[ 0 ].x;
	miny = (*this)[ 0 ].y;
	maxy = (*this)[ 0 ].y;
	minz = (*this)[ 0 ].z;
	maxz = (*this)[ 0 ].z;
	for( iterator i = begin()++; i != end(); i++ ) {
		if( minx > i->x )
			minx = i->x;
		if( maxx < i->x )
			maxx = i->x;
		if( miny > i->y )
			miny = i->y;
		if( maxy < i->y )
			maxy = i->y;
		if( minz > i->z )
			minz = i->z;
		if( maxz < i->z )
			maxz = i->z;
	}
}
