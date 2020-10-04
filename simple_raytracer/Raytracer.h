// ========================================================================= //
// Copyright (c) 2020 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Raytracer.h                                                               //
// ========================================================================= //

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <vector>
#include "Vec3.h"

class Scene;
class Ray;
class SceneObject;
struct Material;

struct IntersectionInfo
{
	Vec3 normal;
	Vec3 pi;
	SceneObject* object = nullptr;
};

struct RaytracerImage
{
	RaytracerImage( const uint32_t w, const uint32_t h ):
		width( w ), height( h )
	{
		data.resize( h, std::vector<Vec3>() );
		for ( uint32_t i = 0; i < w; i++ )
		{
			data[i].resize( w );
		}
	}
	uint32_t width;
	uint32_t height;
	std::vector<std::vector<Vec3>> data;
};

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

class Raytracer
{
public:
	explicit Raytracer( const uint32_t w, uint32_t h ) : m_width( w ), m_height( h ) {}
	void setEyeLocation( const Vec3& eyeLocation )
	{
		m_eyeLocation = eyeLocation;
	}

	RaytracerImage raytrace( const Scene& scene, const int maxDepth );

private:
	Vec3 computeLight( const Vec3& direction,
					   const Vec3& lightcolor,
					   const Vec3& normal,
					   const Vec3& halfvec,
					   const Material& material );

	IntersectionInfo intersect( const Scene& scene,
								const Ray& ray );

	Vec3 computeColor( const Scene& scene,
					   const Ray& ray,
					   const IntersectionInfo& intersection,
					   const int maxDepth );

private:
	Vec3 m_eyeLocation;
	uint32_t m_width;
	uint32_t m_height;
};

#endif // !RAYTRACER_H_
