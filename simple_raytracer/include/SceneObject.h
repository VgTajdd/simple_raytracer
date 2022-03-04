// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// SceneObject.h                                                             //
// ========================================================================= //

#pragma once

#include "Vec3.h"

class Ray;

struct Material
{
	Vec3 diffuse = Vec3( 0.2f, 0.2f, 0.2f );
	Vec3 specular = Vec3( 1, 1, 1 );
	Vec3 ambient = Vec3( 0.1f, 0.1f, 0.1f );
	Vec3 emissive;
	float shininess = 200;
	float reflectivity = 0.8f;
};

/**
 * @brief The SceneObject class.
 * Abstract class for all objects in the scene.
 */
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
	explicit SceneObject( const unsigned int objectId, const OBJ_TYPE& type )
		: m_objectId( objectId )
		, m_type( type )
	{}
	virtual ~SceneObject() = default;
	const int objectId() const
	{
		return m_objectId;
	}
	virtual bool intersects( const Ray& ray, Vec3& pi, Vec3& normal, float& t ) = 0;
	const Material& material() const
	{
		return m_material;
	}
	Material& pvtMaterial()
	{
		return m_material;
	}

private:
	unsigned int m_objectId;
	OBJ_TYPE m_type;
	Material m_material;
};
