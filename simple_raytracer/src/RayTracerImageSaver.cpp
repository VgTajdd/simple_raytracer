// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// RaytracerImageSaver.cpp                                                   //
// ========================================================================= //

#include "RayTracerImageSaver.h"
#include "RayTracerImage.h"
#include <fstream>
#include <iostream>

bool RaytracerImageSaver::save( const RaytracerImage& image, const char* filename, const FORMAT& format )
{
	if ( format == FORMAT::PPM )
	{
		std::ofstream out( filename );
		std::cout << "Saving screenshot (ppm): " << filename << "\n";
		out << "P3\n" << image.width << ' ' << image.height << ' ' << "255\n";
		for ( const auto& row : image.data )
		{
			for ( const Vec3& pixel : row )
			{
				out << (int)pixel.x() << ' ' << (int)pixel.y() << ' ' << (int)pixel.z() << '\n';
			}
		}
		return true;
	}
	else
	{
		return false;
	}

	return true;
}
