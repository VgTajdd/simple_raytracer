// ========================================================================= //
// Copyright (c) 2022 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Raytracer.cpp                                                             //
// ========================================================================= //

#include "Raytracer.h"
#include "Ray.h"
#include "RaytracerImage.h"
#include "Scene.h"
#include "SceneObject.h"

RaytracerImage Raytracer::raytrace( const Scene& scene, const int maxDepth )
{
	RaytracerImage image( m_width, m_height );
	for ( unsigned int r = 0; r < m_height; r++ )
	{
		for ( unsigned int c = 0; c < m_width; c++ )
		{
			Ray ray( m_eyeLocation,
					 Vec3( c + 0.5f - m_width / 2, ( m_height / 2 ) - ( r + 0.5f ), 0 ) - m_eyeLocation );
			IntersectionInfo intersection = intersect( scene, ray );
			image.data[r][c] = computeColor( scene, ray, intersection, maxDepth ) * 255;
		}
	}
	return image;
}

Vec3 Raytracer::computeLight( const Vec3& direction, const Vec3& lightcolor, const Vec3& normal, const Vec3& halfVec,
							  const Material& material )
{
	float nDotL = normal.dot( direction );
	nDotL = nDotL < 0 ? 0 : nDotL;
	Vec3 lambert = material.diffuse * lightcolor * nDotL;

	float nDotH = normal.dot( halfVec );
	nDotH = nDotH < 0 ? 0 : nDotH;
	Vec3 phong = material.specular * lightcolor * powf( nDotH, material.shininess );

	Vec3 retval = lambert + phong;
	return retval;
}

IntersectionInfo Raytracer::intersect( const Scene& scene, const Ray& ray )
{
	IntersectionInfo intersection_final;
	Vec3 pi, normal;
	float t = 0.f, t_min = 0.f;
	for ( const auto& [id, object] : scene.objects() )
	{
		if ( object->intersects( ray, pi, normal, t ) )
		{
			if ( t < 0 ) continue;

			if ( intersection_final.object == nullptr )
			{
				t_min = t;
				intersection_final.object = object;
				intersection_final.pi = pi;
				intersection_final.normal = normal;
			}
			else
			{
				if ( t_min > t )
				{
					t_min = t;
					intersection_final.object = object;
					intersection_final.pi = pi;
					intersection_final.normal = normal;
				}
			}
		}
	}
	return intersection_final;
}

Vec3 Raytracer::computeColor( const Scene& scene, const Ray& ray, const IntersectionInfo& intersection,
							  const int maxDepth )
{
	Vec3 pixelColor;
	if ( intersection.object != nullptr )
	{
		for ( const auto& light : scene.lights() )
		{
			// Shadows section.
			{
				Vec3 directionToLight = ( light.position - intersection.pi ).normalized();
				Ray rayToLight( intersection.pi + directionToLight * 0.01f, directionToLight );
				IntersectionInfo intersectionToLight = intersect( scene, rayToLight );
				if ( intersectionToLight.object != nullptr )
				{
					continue;
				}
			}

			Vec3 direction = light.position; // directional light by default.
			if ( light.isPoint )
			{
				direction = ( light.position - intersection.pi );
			}
			direction = direction.normalized();
			Vec3 halfVec = ( direction - ray.direction() ).normalized();
			Vec3 color =
				computeLight( direction, light.color, intersection.normal, halfVec, intersection.object->material() );
			pixelColor = pixelColor + color;
		}
		pixelColor = intersection.object->material().ambient + intersection.object->material().emissive + pixelColor;

		// Reflection section.
		if ( maxDepth > 0 )
		{
			auto a = intersection.normal * intersection.normal.dot( ray.direction() );
			auto reflectedDirection = ray.direction() - a * 2;
			Ray reflectedRay( intersection.pi + reflectedDirection * 0.01f, reflectedDirection );
			IntersectionInfo intersectionFromReflectedRay = intersect( scene, reflectedRay );
			if ( intersectionFromReflectedRay.object != nullptr )
			{
				Vec3 reflectedColor;
				reflectedColor = computeColor( scene, reflectedRay, intersectionFromReflectedRay, maxDepth - 1 ) *
								 intersection.object->material().reflectivity;
				pixelColor = pixelColor + reflectedColor;
			}
		}

		pixelColor.clampValues( 0, 1 );
	}
	return pixelColor;
}
