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

#include "voxel.h"

Voxel::Voxel( const int& x, const int& y, const int& z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

bool
Voxel::operator<( const Voxel& v ) const {
	return ( x < v.x ) || ( ( x == v.x ) && ( y < v.y ) ) || ( ( x == v.x ) && ( y == v.y ) && ( z < v.z ) );
}

bool
Voxel::operator==( const Voxel& v ) const {
	return ( x == v.x ) && ( y == v.y ) && ( z == v.z );
}

