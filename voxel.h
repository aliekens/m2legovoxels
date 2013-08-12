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

#ifndef VOXEL__H
#define VOXEL__H

class Voxel {
public:
	int x, y, z;
	Voxel( const int&, const int&, const int& );
	bool operator<( const Voxel& ) const;
	bool operator==( const Voxel& ) const;
};

#endif
