#include "SceneObject.h"
#include "Ray.h"
#include "Vec3.h"

/**
 * @brief Concrete class for a sphere.
 */
class Sphere : public SceneObject
{
public:
	explicit Sphere( const Vec3& center, const float radious, const unsigned int id )
		: SceneObject( id, OBJ_TYPE::SPHERE )
		, m_center( center )
		, m_radious( radious )
	{}

	const Vec3& center() const
	{
		return m_center;
	}
	const float radious() const
	{
		return m_radious;
	}
	bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t );

private:
	Vec3 m_center;
	float m_radious;
};

/**
 * @brief Concrete class for a triangle.
 */
class Triangle : public SceneObject
{
public:
	explicit Triangle( const Vec3& v1, const Vec3& v2, const Vec3& v3, const unsigned int id )
		: SceneObject( id, OBJ_TYPE::TRIANGLE )
		, m_v1( v1 )
		, m_v2( v2 )
		, m_v3( v3 )
	{
		m_normal = ( m_v2 - m_v1 ).cross( m_v3 - m_v2 ).normalized();
	}

	bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t );

	const Vec3& v1() const
	{
		return m_v1;
	}
	const Vec3& v2() const
	{
		return m_v2;
	}
	const Vec3& v3() const
	{
		return m_v3;
	}

private:
	Vec3 m_v1;
	Vec3 m_v2;
	Vec3 m_v3;
	Vec3 m_normal;
};

bool Sphere::intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t )
{
	float a = ray.direction().dot( ray.direction() );
	Vec3 originMinusCenter = ray.origin() - m_center;
	float b = 2 * ray.direction().dot( originMinusCenter );
	float c = originMinusCenter.dot( originMinusCenter ) - m_radious * m_radious;

	float disc = b * b - 4 * a * c;
	if ( disc < 0 ) return false;

	float t1 = ( -b - powf( disc, 0.5f ) ) / ( 2 * a );
	float t2 = ( -b + powf( disc, 0.5f ) ) / ( 2 * a );

	t = ( t2 > t1 ) ? t1 : t2;
	if ( t < 0 ) return false;

	pi = ray.origin() + ray.direction() * t;
	normal = ( pi - m_center ).normalized();

	return true;
}

bool Triangle::intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t )
{
	// Ref:
	// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	// Avoid considering this triangle if its plane is parallel to ray or if ray
	// origin is behind the triangle.
	if ( m_normal.dot( ray.direction() ) > -0.001f ) return false;

	Vec3 v12 = m_v2 - m_v1;
	Vec3 v13 = m_v3 - m_v1;
	Vec3 v32 = m_v2 - m_v3;
	Vec3 v31 = m_v1 - m_v3;

	normal = m_normal;

	float D = normal.dot( m_v1 );

	t = -( normal.dot( ray.origin() ) - D ) / normal.dot( ray.direction() );
	if ( t <= 0 ) return false;

	pi = ray.origin() + ray.direction() * t;

	// If ray is not parallel to triangle's plane and t > 0.
	Vec3 v1p = pi - m_v1;
	Vec3 v3p = pi - m_v3;

	if ( v12.cross( v13 ).dot( v12.cross( v1p ) ) > 0 && v32.cross( v31 ).dot( v32.cross( v3p ) ) > 0 &&
		 v12.cross( v13 ).dot( v1p.cross( v13 ) ) > 0 )
	{
		return true;
	}

	return false;
}

#include "SceneObjectFactory.h"

unsigned int SceneObjectFactory::nextObjectId = 1;

SceneObject* SceneObjectFactory::createSphere( const Vec3& center, const float radious )
{
	Sphere* object = new Sphere( center, radious, nextObjectId++ );
	return object;
}

SceneObject* SceneObjectFactory::createTriangle( const Vec3& v1, const Vec3& v2, const Vec3& v3 )
{
	Triangle* object = new Triangle( v1, v2, v3, nextObjectId++ );
	return object;
}
