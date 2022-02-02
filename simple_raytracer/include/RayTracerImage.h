// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// RaytracerImage.h                                                          //
// ========================================================================= //

#include "Vec3.h"
#include <vector>

struct RaytracerImage
{
	RaytracerImage( const unsigned int w, const unsigned int h )
		: width( w )
		, height( h )
	{
		data.resize( h, std::vector<Vec3>() );
		for ( unsigned int i = 0; i < w; i++ )
		{
			data[i].resize( w );
		}
	}
	unsigned int width;
	unsigned int height;
	std::vector<std::vector<Vec3>> data;
};
