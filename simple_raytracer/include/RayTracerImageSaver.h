// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// RaytracerImageSaver.h                                                     //
// ========================================================================= //

#pragma once

struct RaytracerImage;

class RaytracerImageSaver
{
public:
	enum class FORMAT
	{
		PNG,
		PPM
	};
	static bool save( const RaytracerImage& image, const char* filename, const FORMAT& format = FORMAT::PNG );
};
