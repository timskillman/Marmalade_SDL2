#pragma once

#include "s3e.h"
#include <cmath>

class CIwFVec2 {
public:
	CIwFVec2() { x = 0.f; y = 0.f; }
	CIwFVec2(float _x, float _y) { x = _x; y = _y; }
	//CIwFVec2(GLfloat _x, GLfloat _y) { x = _x; y = _y; }

	void Normalise()
	{
		float v = sqrtf(x*x + y*y);
		x = x / v;
		y = y / v;
	}

	CIwFVec2 operator - () const
	{
		return CIwFVec2(-x, -y);
	}

	CIwFVec2 operator - (CIwFVec2 rhs)
	{
		return CIwFVec2(x - rhs.x, y - rhs.y);
	}

	CIwFVec2 operator + (CIwFVec2 rhs)
	{
		return CIwFVec2(x + rhs.x, y + rhs.y);
	}

	bool operator == (CIwFVec2 rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}

	bool operator!=(CIwFVec2 rhs)
	{
		return (x != rhs.x || y != rhs.y);
	}

	CIwFVec2 operator*(float scale)
	{
		return CIwFVec2(x * scale, y * scale);
	}

	CIwFVec2 operator/(float div)
	{
		return CIwFVec2(x / div, y / div);
	}

	CIwFVec2 & operator += (CIwFVec2 const & v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	CIwFVec2 & operator -= (CIwFVec2 const & v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	CIwFVec2 & operator *= (float v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	float GetLength() const
	{
		return std::sqrtf(x*x + y*y);
	}


	static CIwFVec2 g_Zero;

	float x;
	float y;
};

class CIwFVec3 {
public:
	CIwFVec3() : x(0.f), y(0.f), z(0.f) {
	}

	CIwFVec3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

	CIwFVec3 operator - ()
	{
		return CIwFVec3(-x, -y, -z);
	}

	CIwFVec3 operator - (CIwFVec3 rhs)
	{
		return CIwFVec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	CIwFVec3 operator + (CIwFVec3 rhs)
	{
		return CIwFVec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	CIwFVec3 & operator += (CIwFVec3 const & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	bool operator==(CIwFVec3 rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	CIwFVec3 operator*(float scale)
	{
		return CIwFVec3(x * scale, y * scale, z * scale);
	}

	CIwFVec3 operator/(float div)
	{
		return CIwFVec3(x / div, y / div, z / div);
	}

	bool IsZero() const
	{
		return ((x == 0.f) && (y == 0.f) && (z == 0.f));
	}

	static CIwFVec3 g_Zero;

	float x;
	float y;
	float z;
};

class CIwFMat {
public:

	// VARS

	static CIwFMat g_Identity;
	float m[3][3];
	CIwFVec3 t;

	// FUNCTIONS

	CIwFMat() {
		m[0][0] = 1;
		m[1][0] = 0;
		m[2][0] = 0;
		m[0][1] = 0;
		m[1][1] = 1;
		m[2][1] = 0;
		m[0][2] = 0;
		m[1][2] = 0;
		m[2][2] = 1;
		t.x = 0;
		t.y = 0;
		t.z = 0;
	};

	CIwFVec3 TransformVec(CIwFVec3 const &v) const {
		return CIwFVec3(
			((m[0][0] * v.x) + (m[1][0] * v.y) + (m[2][0] * v.z)) + t.x,
			((m[0][1] * v.x) + (m[1][1] * v.y) + (m[2][1] * v.z)) + t.y,
			((m[0][2] * v.x) + (m[1][2] * v.y) + (m[2][2] * v.z)) + t.z
		);
	}

	CIwFVec3 TransposeRotateVec(CIwFVec3 const &v) const {
		return CIwFVec3(
			((m[0][0] * v.x) + (m[0][1] * v.y) + (m[0][2] * v.z)),
			((m[1][0] * v.x) + (m[1][1] * v.y) + (m[1][2] * v.z)),
			((m[2][0] * v.x) + (m[2][1] * v.y) + (m[2][2] * v.z))
		);
	}

	CIwFMat operator * (CIwFMat const & m2) const
	{
		CIwFMat nm;
		nm.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0];
		nm.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1];
		nm.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2];
		nm.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0];
		nm.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1];
		nm.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2];
		nm.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0];
		nm.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1];
		nm.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2];

		nm.t = m2.TransformVec(t);
		return nm;
	}

	void SetRotX(float ang = 0)
	{
		m[0][0] = 1.0f;
		m[1][1] = m[2][2] = (float)cos(ang);
		m[1][2] = -(m[2][1] = (float)sin(ang));
	}

	void SetRotY(float ang = 0)
	{
		m[1][1] = 1.0f;
		m[0][0] = m[2][2] = (float)cos(ang);
		m[2][0] = -(m[0][2] = (float)sin(ang));
	}

	void SetRotZ(float ang = 0)
	{
		m[2][2] = 1.0f;
		m[0][0] = m[1][1] = (float)cos(ang);
		m[0][1] = -(m[1][0] = (float)sin(ang));
	}

	CIwFVec3 TransposeTransformVec(CIwFVec3 const &V)
	{
		return CIwFVec3(
			((m[0][0] * (V.x - t.x)) + (m[0][1] * (V.y - t.y)) + (m[0][2] * (V.z - t.z))),
			((m[1][0] * (V.x - t.x)) + (m[1][1] * (V.y - t.y)) + (m[1][2] * (V.z - t.z))),
			((m[2][0] * (V.x - t.x)) + (m[2][1] * (V.y - t.y)) + (m[2][2] * (V.z - t.z)))
		);
	}

	CIwFMat & SetTrans(CIwFVec3 const & v)
	{
		t = v;
		return *this;
	}

	float TransformVecX(CIwFVec3 const &V) const { return (((m[0][0] * V.x) + (m[1][0] * V.y) + (m[2][0] * V.z))) + t.x; }
	float TransformVecY(CIwFVec3 const &V) const { return (((m[0][1] * V.x) + (m[1][1] * V.y) + (m[2][1] * V.z))) + t.y; }
	float TransformVecZ(CIwFVec3 const &V) const { return (((m[0][2] * V.x) + (m[1][2] * V.y) + (m[2][2] * V.z))) + t.z; }
	float TransformVecX(float x, float y, float z) const { return (((m[0][0] * x) + (m[1][0] * y) + (m[2][0] * z))) + t.x; }
	float TransformVecY(float x, float y, float z) const { return (((m[0][1] * x) + (m[1][1] * y) + (m[2][1] * z))) + t.y; }
	float TransformVecZ(float x, float y, float z) const { return (((m[0][2] * x) + (m[1][2] * y) + (m[2][2] * z))) + t.z; }

	CIwFVec3 RotateVec(CIwFVec3 const &V) const
	{
		return CIwFVec3(
			((m[0][0] * V.x) + (m[1][0] * V.y) + (m[2][0] * V.z)),
			((m[0][1] * V.x) + (m[1][1] * V.y) + (m[2][1] * V.z)),
			((m[0][2] * V.x) + (m[1][2] * V.y) + (m[2][2] * V.z))
		);
	}

	float RotateVecX(const CIwFVec3& V) const
	{
		return m[0][0] * V.x + m[1][0] * V.y + m[2][0] * V.z;
	}

	float RotateVecY(const CIwFVec3& V) const
	{
		return m[0][1] * V.x + m[1][1] * V.y + m[2][1] * V.z;
	}

	float RotateVecZ(const CIwFVec3& V) const
	{
		return m[0][2] * V.x + m[1][2] * V.y + m[2][2] * V.z;
	}

	bool IsRotZero() const
	{
		return m[0][0] == 0 &&
			m[0][1] == 0 &&
			m[0][2] == 0 &&
			m[1][0] == 0 &&
			m[1][1] == 0 &&
			m[1][2] == 0 &&
			m[2][0] == 0 &&
			m[2][1] == 0 &&
			m[2][2] == 0;
	}

	bool IsTransZero() const
	{
		return t.x == 0 &&
			t.y == 0 &&
			t.z == 0;
	}

	bool IsZero() const
	{
		return IsRotZero() && IsTransZero();
	}

	void SetIdentity() {
		*this = g_Identity;
	}


private:

};
