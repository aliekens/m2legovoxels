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

#include "voxelspace.h"

#include <iostream>

void
VoxelSpace::applyThreshold( double threshold ) {
	// std::map does not have remove_if, so we have to copy to a new voxelspace, and copy back
	VoxelSpace newSpace;
	for( iterator i = begin(); i != end(); i++ )
		if( i->second >= threshold )
			newSpace[ i->first ] = i->second;
	clear();
	for( iterator i = newSpace.begin(); i != newSpace.end(); i++ )
		(*this)[ i->first ] = i->second;
}

void
VoxelSpace::removeLayer( int layer ) {
	// std::map does not have remove_if, so we have to copy to a new voxelspace, and copy back
	VoxelSpace newSpace;
	for( iterator i = begin(); i != end(); i++ )
		if( i->first.z != layer )
			newSpace[ i->first ] = i->second;
	clear();
	for( iterator i = newSpace.begin(); i != newSpace.end(); i++ )
		(*this)[ i->first ] = i->second;
}

void
VoxelSpace::makeHollow2() {
	VoxelSpace newSpace;
	
	for( iterator i = begin(); i != end(); i++ ) {
		int x = i->first.x;
		int y = i->first.y;
		int z = i->first.z;
		bool central = 
			( count( Voxel( x - 1 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 1, z + 1 ) ) == 1 ) &&
			
			( count( Voxel( x - 2 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 2, z + 0 ) ) == 1 ) &&

			( ( z < minz + 1 ) || (
				( count( Voxel( x - 1 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 1, z - 1 ) ) == 1 ) 
			)
				
		);

		if( !central )
			newSpace[ i->first ] = i->second;
			
	}
	clear();
	for( iterator i = newSpace.begin(); i != newSpace.end(); i++ )
		(*this)[ i->first ] = i->second;
}

void
VoxelSpace::makeHollow3() {
	VoxelSpace newSpace;
	
	for( iterator i = begin(); i != end(); i++ ) {
		int x = i->first.x;
		int y = i->first.y;
		int z = i->first.z;
		bool central = 
			( count( Voxel( x + 0 , y + 0, z + 3 ) ) == 1 ) &&
			
			( count( Voxel( x - 1 , y - 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 0, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 0, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 0, z + 2 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 1, z + 2 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 1, z + 2 ) ) == 1 ) &&
			
			( count( Voxel( x - 1 , y - 2, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 2, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 2, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 0, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 1, z + 1 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 2, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 2, z + 1 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 2, z + 1 ) ) == 1 ) &&
			
			( count( Voxel( x - 1 , y - 3, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 3, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 3, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 3 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 3 , y - 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 3 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 3 , y - 0, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 3 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 3 , y + 1, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 2 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 2 , y + 2, z + 0 ) ) == 1 ) &&
			( count( Voxel( x - 1 , y + 3, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 0 , y + 3, z + 0 ) ) == 1 ) &&
			( count( Voxel( x + 1 , y + 3, z + 0 ) ) == 1 ) &&

			( ( z < minz + 1 ) || (
				( count( Voxel( x - 1 , y - 2, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y - 2, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y - 2, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 2 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 2 , y - 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 2 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 2 , y + 0, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 2 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 2 , y + 1, z - 1 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 2, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 2, z - 1 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 2, z - 1 ) ) == 1 ) )
			) &&
			( ( z < minz + 2 ) || (
				( count( Voxel( x + 0 , y + 0, z - 2 ) ) == 1 ) &&
				( count( Voxel( x - 1 , y + 0, z - 2 ) ) == 1 ) &&
				( count( Voxel( x + 1 , y + 0, z - 2 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y - 1, z - 2 ) ) == 1 ) &&
				( count( Voxel( x + 0 , y + 1, z - 2 ) ) == 1 ) )
			) &&
				( ( z < minz + 3 ) || (
				( count( Voxel( x + 0 , y + 0, z - 3 ) ) == 1 ) )
			);

		if( !central )
			newSpace[ i->first ] = i->second;
	}
	clear();
	for( iterator i = newSpace.begin(); i != newSpace.end(); i++ )
		(*this)[ i->first ] = i->second;
}

void 
VoxelSpace::computeStatistics() {
	minx = 1000;
	miny = 1000;
	minz = 1000;
	maxx = -1000;
	maxy = -1000;
	maxz = -1000;
	for( iterator i = begin(); i != end(); i++ ) {
		int x = i->first.x;
		if( x > maxx )
			maxx = x;
		if( x < minx )
			minx = x;
		int y = i->first.y;
		if( y > maxy )
			maxy = y;
		if( y < miny )
			miny = y;
		int z = i->first.z;
		if( z > maxz )
			maxz = z;
		if( z < minz )
			minz = z;
	}
	std::cerr << "x = " << maxx - minx + 1 << "\ty = " << maxy - miny + 1 << "\tz = " << maxz - minz + 1 << std::endl;
}

void 
VoxelSpace::printProfiles() {
	for( int z = maxz; z >= minz; z-- ) {
		
		std::cerr << "#\t";
		
		for( int y = miny; y <= maxy; y++ ) {
			bool voxel = false;
			iterator i = begin();
			while( ( i != end() ) && !voxel ) {
				if( ( i->first.y == y ) && ( i->first.z == z ) )
					voxel = true;
				i++;
			}
			if( voxel )
				std::cerr << "[]";
			else
				std::cerr << "  ";
		}
		
		std::cerr << "\t";
		
		for( int x = minx; x <= maxx; x++ ) {
			bool voxel = false;
			iterator i = begin();
			while( ( i != end() ) && !voxel ) {
				if( ( i->first.x == x ) && ( i->first.z == z ) )
					voxel = true;
				i++;
			}
			if( voxel )
				std::cerr << "[]";
			else
				std::cerr << "  ";
		}

				
		std::cerr << std::endl;
	}
}

void
VoxelSpace::printLayers() {
	std::cerr << maxx - minx + 1 << " " << maxy - miny + 1 << " " << maxz - minz + 1 << std::endl;
	std::cerr << "# # denotes a brick on top of other brick in the layer below";
	std::cerr << "# O denotes a floating brick";
	std::cerr << "# : denotes no brick, but there's one below";
	std::cerr << "# . denotes no bricks";
	for( int z = maxz; z >= minz; z-- ) {
		std::cerr << "# Layer " << z << std::endl;
		for( int y = miny; y <= maxy; y++ ) {
//			std::cout << ( x - minx ) % 10 << " ";
			for( int x = minx; x <= maxx; x++ ) {
				if( count( Voxel( x, y, z ) ) > 0 )
					if( count( Voxel( x, y, z - 1 ) ) > 0 )
						std::cout << "#";
					else
						std::cout << "O";
				else
					if( count( Voxel( x, y, z - 1 ) ) > 0 )
						std::cout << ":";
					else
						std::cout << ".";
			}
			std::cout << std::endl;
		}
	}
}

void
VoxelSpace::printLDraw( std::ostream& os ) {
	int currentstep = 0;
	for( iterator i = begin(); i != end(); i++ ) {
		if( i->second > 0 ) {
//			if( currentstep != i->first.y ) {
//				os << "0 STEP" << std::endl;
//				currentstep = i->first.y;
//			}
			os << 
				"1 15 " << 
				( + i->first.x - maxx / 2 ) * 20 << " " << 
				( - i->first.z + maxz / 2 ) * 24 << " " << 
				( + i->first.y - maxy / 2 ) * 20 << 
				" 1 0 0 0 1 0 0 0 1 3005.dat" << std::endl;
		}
	}
}
