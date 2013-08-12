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

#include "vertex.h"

Vertex::Vertex( double x, double y, double z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vertex 
Vertex::crossProduct( const Vertex& v1, const Vertex& v2 ) {
	return Vertex( v2.z * v1.y - v2.y * v1.z, v2.x * v1.z - v2.z * v1.x, v2.y * v1.x - v2.x * v1.y );
}

double
Vertex::dotProduct( const Vertex& v1, const Vertex& v2 ) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vertex
Vertex::operator-( const Vertex& v ) const {
	return Vertex( x - v.x, y - v.y, z - v.z );
}

Vertex
Vertex::operator+( const Vertex& v ) const {
	return Vertex( x + v.x, y + v.y, z + v.z );
}

Vertex
Vertex::operator*( const double& d ) const {
	return Vertex( d * x, d * y, d * z );
}

