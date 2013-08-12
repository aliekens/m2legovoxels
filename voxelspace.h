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

#ifndef VOXELSPACE__H
#define VOXELSPACE__H

#include "voxel.h"

#include <map>

class VoxelSpace : public std::map< Voxel, double > {
public:
	int minx, maxx, miny, maxy, minz, maxz;
	void applyThreshold( double threshold );
	void removeLayer( int z );
	void makeHollow2();
	void makeHollow3();
	void computeStatistics();
	void printProfiles();
	void printLayers();
	void printLDraw( std::ostream& os );
};

#endif