// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Scene.cpp                                                                 //
// ========================================================================= //

#include "Scene.h"
#include "SceneObject.h"

bool Scene::addObject( SceneObject* object )
{
	if ( m_objects.find( object->objectId() ) != m_objects.end() ) return false;

	m_objects.emplace( object->objectId(), object );
	return true;
}
bool Scene::addLight( const Vec3& pos, const Vec3& col, const bool point )
{
	m_lights.emplace_back( pos, col, point );
	return true;
}
