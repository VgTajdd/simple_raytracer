// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Raytracer.h                                                               //
// ========================================================================= //

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "RaytracerImage.h"
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

class Raytracer
{
public:
	explicit Raytracer( const unsigned int w, unsigned int h )
		: m_width( w )
		, m_height( h )
	{}
	void setEyeLocation( const Vec3& eyeLocation )
	{
		m_eyeLocation = eyeLocation;
	}

	RaytracerImage raytrace( const Scene& scene, const int maxDepth );

private:
	Vec3 computeLight( const Vec3& direction, const Vec3& lightcolor, const Vec3& normal, const Vec3& halfvec,
					   const Material& material );

	IntersectionInfo intersect( const Scene& scene, const Ray& ray );

	Vec3 computeColor( const Scene& scene, const Ray& ray, const IntersectionInfo& intersection, const int maxDepth );

private:
	Vec3 m_eyeLocation;
	unsigned int m_width;
	unsigned int m_height;
};

#endif // !RAYTRACER_H_
