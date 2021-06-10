// ========================================================================= //
// Copyright (c) 2020 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Scene.cpp                                                                 //
// ========================================================================= //

#include "Scene.h"

unsigned int ObjectsFactory::nextObjectId = 1;

bool Sphere::intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t )
{
	float a = ray.direction().dot( ray.direction() );
	Vec3 originMinusCenter = ray.origin() - m_center;
	float b = 2 * ray.direction().dot( originMinusCenter );
	float c = originMinusCenter.dot( originMinusCenter ) - m_radious * m_radious;

	float disc = b * b - 4 * a * c;
	if ( disc < 0 )
		return false;

	float t1 = ( -b - powf( disc, 0.5f ) ) / ( 2 * a );
	float t2 = ( -b + powf( disc, 0.5f ) ) / ( 2 * a );

	t = ( t2 > t1 ) ? t1 : t2;
	if ( t < 0 )
		return false;

	pi = ray.origin() + ray.direction() * t;
	normal = ( pi - m_center ).normalized();

	return true;
}

bool Triangle::intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t )
{
	// Ref: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

	// Avoid considering this triangle if its plane is parallel to ray or if ray origin is behind the triangle.
	if ( m_normal.dot( ray.direction() ) > -0.001f )
		return false;

	Vec3 v12 = m_v2 - m_v1;
	Vec3 v13 = m_v3 - m_v1;
	Vec3 v32 = m_v2 - m_v3;
	Vec3 v31 = m_v1 - m_v3;

	normal = m_normal;

	float D = normal.dot( m_v1 );

	t = -( normal.dot( ray.origin() ) - D ) / normal.dot( ray.direction() );
	if ( t <= 0 )
		return false;

	pi = ray.origin() + ray.direction() * t;

	// If ray is not parallel to triangle's plane and t > 0.
	Vec3 v1p = pi - m_v1;
	Vec3 v3p = pi - m_v3;

	if ( v12.cross( v13 ).dot( v12.cross( v1p ) ) > 0
		 && v32.cross( v31 ).dot( v32.cross( v3p ) ) > 0
		 && v12.cross( v13 ).dot( v1p.cross( v13 ) ) > 0 )
	{
		return true;
	}

	return false;
}