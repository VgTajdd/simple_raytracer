// ========================================================================= //
// Copyright (c) 2020 Agustin Jesus Durand Diaz.                             //
// This code is licensed under the Apache-2.0 License.                       //
// Vec3.h                                                                    //
// ========================================================================= //

#ifndef VEC_3_H_
#define VEC_3_H_

#include <math.h>

class Vec3
{
public:
	Vec3( const float x = 0.f, const float y = 0.f, const float z = 0.f ) :
		m_x( x ), m_y( y ), m_z( z ) {}

	const float x() const { return m_x; }
	const float y() const { return m_y; }
	const float z() const { return m_z; }
	const float length() const { return sqrtf( ( m_x * m_x ) + ( m_y * m_y ) + ( m_z * m_z ) ); }
	Vec3 normalized() const
	{
		const float l = length();
		if ( l > 0 )
			return Vec3( m_x / l, m_y / l, m_z / l );
		else
			return Vec3();
	}
	Vec3 operator - ( const Vec3& other ) const
	{
		return Vec3( m_x - other.x(), m_y - other.y(), m_z - other.z() );
	}
	Vec3 operator + ( const Vec3& other ) const
	{
		return Vec3( m_x + other.x(), m_y + other.y(), m_z + other.z() );
	}
	Vec3 operator * ( const float scale ) const
	{
		return Vec3( m_x * scale, m_y * scale, m_z * scale );
	}
	Vec3 operator * ( const Vec3& other ) const
	{
		return Vec3( m_x * other.m_x, m_y * other.m_y, m_z * other.m_z );
	}
	float dot( const Vec3& other ) const
	{
		float ans = ( m_x * other.x() ) + ( m_y * other.y() ) + ( m_z * other.z() );
		return ans;
	}
	void scale( const float scale )
	{
		m_x *= scale;
		m_y *= scale;
		m_z *= scale;
	}
	void clampValues( const float min, const float max )
	{
		m_x = std::max( std::min( max, m_x ), min );
		m_y = std::max( std::min( max, m_y ), min );
		m_z = std::max( std::min( max, m_z ), min );
	}
	Vec3 cross( const Vec3& other ) const
	{
		float x = m_y * other.z() - m_z * other.y();
		float y = m_z * other.x() - m_x * other.z();
		float z = m_x * other.y() - m_y * other.x();
		Vec3 ans( x, y, z );
		return ans;
	}
private:
	float m_x;
	float m_y;
	float m_z;
};

#endif // !VEC_3_H_
