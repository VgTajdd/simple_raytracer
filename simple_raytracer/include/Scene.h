// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Scene.h                                                                   //
// ========================================================================= //

#ifndef SCENE_H_
#define SCENE_H_

#include <map>
#include <vector>

#include "Vec3.h"

class SceneObject;

struct Light
{
	explicit Light( const Vec3& pos, const Vec3& col, const bool point )
		: position( pos )
		, color( col )
		, isPoint( point )
	{}
	Vec3 position;
	Vec3 color;
	bool isPoint;
};

class Scene
{
public:
	bool addObject( SceneObject* object );
	bool addLight( const Vec3& pos, const Vec3& col, const bool point );
	const std::map<int, SceneObject*>& objects() const
	{
		return m_objects;
	}
	const std::vector<Light>& lights() const
	{
		return m_lights;
	}

private:
	std::map<int, SceneObject*> m_objects;
	std::vector<Light> m_lights;
};

#endif // !SCENE_H_
