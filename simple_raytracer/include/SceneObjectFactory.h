// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// SceneObjectFactory.h                                                      //
// ========================================================================= //

#pragma once

class SceneObject;
class Vec3;

class SceneObjectFactory
{
	static unsigned int nextObjectId;

public:
	static SceneObject* createSphere( const Vec3& center, const float radious );
	static SceneObject* createTriangle( const Vec3& v1, const Vec3& v2, const Vec3& v3 );
};
