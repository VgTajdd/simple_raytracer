// ========================================================================= //
// Copyright (c) 2021 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Ray.h                                                                     //
// ========================================================================= //

#ifndef RAY_H_
#define RAY_H_

#include "Vec3.h"

class Ray {
 public:
  Ray(const Vec3& origin, const Vec3& direction)
      : m_origin(origin), m_direction(direction.normalized()) {}

  const Vec3& origin() const { return m_origin; }
  const Vec3& direction() const { return m_direction; }  // Normalized
 private:
  Vec3 m_origin;
  Vec3 m_direction;
};

#endif  // !RAY_H_
