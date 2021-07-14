// ========================================================================= //
// Copyright (c) 2021 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Scene.h                                                                   //
// ========================================================================= //

#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <vector>
#include "Vec3.h"
#include "Ray.h"

struct Light
{
	explicit Light( const Vec3& pos, const Vec3& col, const bool point ) : position( pos ), color( col ), isPoint( point ) {}
	Vec3 position;
	Vec3 color;
	bool isPoint;
};

struct Material
{
	Vec3 diffuse = Vec3( 0.2f, 0.2f, 0.2f );
	Vec3 specular = Vec3( 1, 1, 1 );
	Vec3 ambient = Vec3( 0.1f, 0.1f, 0.1f );
	Vec3 emissive;
	float shininess = 200;
	float reflectivity = 0.8f;
};

class SceneObject
{
public:
	enum class OBJ_TYPE
	{
		NO_TYPE,
		TRIANGLE,
		SPHERE,
	};
public:
	explicit SceneObject( const unsigned int objectId, const OBJ_TYPE& type ) : m_objectId( objectId ), m_type( type ) {}
	virtual ~SceneObject() = default;
	const int objectId() const { return m_objectId; }
	virtual bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t ) = 0;
	const Material& material() const { return m_material; }
	Material& pvtMaterial() { return m_material; }
private:
	unsigned int m_objectId;
	OBJ_TYPE m_type;
	Material m_material;
};

class Sphere : public SceneObject
{
public:
	explicit Sphere( const Vec3& center, const float radious, const unsigned int id ) :
		SceneObject( id, OBJ_TYPE::SPHERE ),
		m_center( center ), m_radious( radious ) {}

	const Vec3& center() const { return m_center; }
	const float radious() const { return m_radious; }
	bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t );
private:
	Vec3 m_center;
	float m_radious;
};

class Triangle : public SceneObject
{
public:
	explicit Triangle( const Vec3& v1, const Vec3& v2, const Vec3& v3, const unsigned int id ) :
		SceneObject( id, OBJ_TYPE::TRIANGLE ),
		m_v1( v1 ), m_v2( v2 ), m_v3( v3 )
	{
		m_normal = ( m_v2 - m_v1 ).cross( m_v3 - m_v2 ).normalized();
	}

	bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t );

	const Vec3& v1() const { return m_v1; }
	const Vec3& v2() const { return m_v2; }
	const Vec3& v3() const { return m_v3; }
private:
	Vec3 m_v1;
	Vec3 m_v2;
	Vec3 m_v3;
	Vec3 m_normal;
};

class ObjectsFactory
{
public:
	inline static Sphere* createSphere( const Vec3& center, const float radious )
	{
		Sphere* object = new Sphere( center, radious, nextObjectId++ );
		return object;
	}
	inline static Triangle* createTriangle( const Vec3& v1, const Vec3& v2, const Vec3& v3 )
	{
		Triangle* object = new Triangle( v1, v2, v3, nextObjectId++ );
		return object;
	}

	static unsigned int nextObjectId;
};

class Scene
{
public:
	bool addObject( SceneObject* object )
	{
		if ( m_objects.find( object->objectId() ) != m_objects.end() )
			return false;

		m_objects.emplace( object->objectId(), object );
		return true;
	}
	bool addLight( const Vec3& pos, const Vec3& col, const bool point )
	{
		m_lights.emplace_back( pos, col, point );
		return true;
	}
	const std::map<int, SceneObject*>& objects() const { return m_objects; }
	const std::vector<Light>& lights() const { return m_lights; }
private:
	std::map<int, SceneObject*> m_objects;
	std::vector<Light> m_lights;
};

#endif // !SCENE_H_
