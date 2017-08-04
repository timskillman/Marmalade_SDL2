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

class CIwFMat2D
{
public:

	float m[2][2];
	CIwFVec2 t;

	static CIwFMat2D g_Identity;

	CIwFMat2D() {
		m[0][0] = m[1][1] = 1.f;
		m[0][1] = m[1][0] = 0;
		t.x = t.y = 0;
	};

	explicit CIwFMat2D(float f)
	{
		m[0][0] = m[1][1] = f;
		m[0][1] = m[1][0] = 0;
		t.x = t.y = 0;
	}

	CIwFMat2D(CIwFMat2D const & R, CIwFVec2 const & T)
	{
		m[0][0] = R.m[0][0];
		m[1][0] = R.m[1][0];
		m[0][1] = R.m[0][1];
		m[1][1] = R.m[1][1];
		t = T;
	}

	void Normalise()
	{
		CIwFVec2 * pVecX = (CIwFVec2*)&m[0][0];
		CIwFVec2 * pVecY = (CIwFVec2*)&m[1][0];

		pVecX->Normalise();
		pVecY->Normalise();

		*pVecY = CIwFVec2(-pVecX->y, pVecX->x);
	}

	void Transpose()
	{
		float temp = m[0][1];
		m[0][1] = m[1][0];
		m[1][0] = temp;
	}

	CIwFVec2 const & GetTrans() const
	{
		return t;
	}

	CIwFMat2D & SetTrans(CIwFVec2 const & v)
	{
		t = v;
		return *this;
	}

	CIwFMat2D & operator += (CIwFVec2 & V)
	{
		t += V;
		return *this;
	}

	CIwFMat2D operator + (CIwFVec2 & V)
	{
		return CIwFMat2D(*this, t + V);
	}

	CIwFVec2 ColumnX() const
	{
		return CIwFVec2(m[0][0], m[1][0]);
	}

	CIwFVec2 ColumnY() const
	{
		return CIwFVec2(m[0][1], m[1][1]);
	}

#define VecX RowX

	CIwFVec2 RowX() const
	{
		return CIwFVec2(m[0][0], m[0][1]);
	}

#define VecY RowY

	CIwFVec2 RowY() const
	{
		return CIwFVec2(m[1][0], m[1][1]);
	}

	CIwFVec2 RotateVec(CIwFVec2 const &V) const
	{
		return CIwFVec2(
			((m[0][0] * V.x) + (m[1][0] * V.y)),
			((m[0][1] * V.x) + (m[1][1] * V.y))
		);
	}

	CIwFVec2 TransformVec(CIwFVec2 const &V) const
	{
		return CIwFVec2(
			((m[0][0] * V.x) + (m[1][0] * V.y)) + t.x,
			((m[0][1] * V.x) + (m[1][1] * V.y)) + t.y
		);
	}

	CIwFVec2 TransposeRotateVec(CIwFVec2 const &V) const
	{
		return CIwFVec2(
			((m[0][0] * V.x) + (m[0][1] * V.y)),
			((m[1][0] * V.x) + (m[1][1] * V.y))
		);
	}

	CIwFVec2 TransposeTransformVec(CIwFVec2 const &V) const
	{
		return CIwFVec2(
			((m[0][0] * (V.x - t.x)) + (m[0][1] * (V.y - t.y))),
			((m[1][0] * (V.x - t.x)) + (m[1][1] * (V.y - t.y)))
		);
	}


	float TransformVecX(CIwFVec2 const &V) const { return (((m[0][0] * V.x) + (m[1][0] * V.y))) + t.x; }
	float TransformVecY(CIwFVec2 const &V) const { return (((m[0][1] * V.x) + (m[1][1] * V.y))) + t.y; }
	float TransformVecX(float x, float y) const { return (((m[0][0] * x) + (m[1][0] * y))) + t.x; }
	float TransformVecY(float x, float y) const { return (((m[0][1] * x) + (m[1][1] * y))) + t.y; }

	float RotateVecX(const CIwFVec2& V)
	{
		return m[0][0] * V.x + m[1][0] * V.y;
	}

	float RotateVecY(const CIwFVec2& V)
	{
		return m[0][1] * V.x + m[1][1] * V.y;
	}

	CIwFMat2D GetTranspose() const
	{
		CIwFMat2D N;
		N.m[0][0] = m[0][0];
		N.m[1][0] = m[0][1];
		N.m[0][1] = m[1][0];
		N.m[1][1] = m[1][1];

		N.t = CIwFVec2(0, 0);
		return N;
	}

	void SetRot(float r = 0, bool resetTrans = true)
	{
		if (resetTrans)     t.x = t.y = 0;
		m[0][0] = m[1][1] = (float)cos(-r);
		m[0][1] = -(m[1][0] = (float)sin(-r));
	}

	void SetRot(float r, CIwFVec2& centre)
	{
		m[0][0] = m[1][1] = (float)cos(-r);
		m[0][1] = -(m[1][0] = (float)sin(-r));
		t = centre - RotateVec(centre);
	}

	void PreRotate(float r)
	{
		CIwFMat2D rz;
		rz.SetRot(r, true);
		PreRotate(rz);
	}

	void PostRotate(float r)
	{
		CIwFMat2D rz;
		rz.SetRot(r, true);
		PostRotate(rz);
	}

	CIwFMat2D operator * (CIwFMat2D const & M) const
	{
		CIwFMat2D N;
		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		N.t = M.TransformVec(t);

		return N;
	}

	CIwFMat2D & PreMult(CIwFMat2D const & M)
	{
		return (*this = M * (*this));
	}

	CIwFMat2D & PreMultiply(CIwFMat2D const & M)
	{
		return PreMult(M);
	}

	CIwFMat2D & PostMult(CIwFMat2D const & M)
	{
		return (*this = (*this) * M);
	}

	CIwFMat2D & PostMultiply(CIwFMat2D const & M)
	{
		return PostMult(M);
	}

	CIwFMat2D& operator *= (CIwFMat2D const & M)
	{
		return PostMult(M);
	}

	CIwFMat2D&  PostRotate(CIwFMat2D const& M)
	{
		CIwFMat2D N;

		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		CopyRot(N);

		return *this;
	}

	CIwFMat2D PreRotate(CIwFMat2D const& M)
	{
		CIwFMat2D tmp = M;
		tmp.t = this->t;
		return (*this = tmp.PostRotate(*this));
	}

	CIwFMat2D& ScaleRot(float v)
	{
		for (int i = 0; i<2; i++)
			for (int j = 0; j<2; j++)
				m[i][j] = (m[i][j] * v);
		return *this;
	}

	CIwFMat2D& ScaleTrans(float v)
	{
		t *= v;
		return *this;
	}

	CIwFMat2D& Scale(float v)
	{
		ScaleRot(v);
		ScaleTrans(v);
		return *this;
	}

	CIwFMat2D& operator *= (const float v)
	{
		Scale(v);
		return *this;
	}

	void InterpolateRot(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction)
	{
		InterpRot(m0, m1, fraction);
	}

	void InterpolatePos(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction)
	{
		InterpTrans(m0, m1, fraction);
	}

	void    CopyRot(const CIwFMat2D& m0)
	{
		m[0][0] = m0.m[0][0];
		m[0][1] = m0.m[0][1];
		m[1][0] = m0.m[1][0];
		m[1][1] = m0.m[1][1];
	}

	void    CopyTrans(const CIwFMat2D& m0)
	{
		t = m0.t;
	}

	bool IsRotSame(CIwFMat2D const& m0) const
	{
		return  m[0][0] == m0.m[0][0] &&
			m[0][1] == m0.m[0][1] &&
			m[1][0] == m0.m[1][0] &&
			m[1][1] == m0.m[1][1];
	}

	bool IsTransSame(CIwFMat2D const& m0)
	{
		return (t == m0.t);
	}

	bool operator == (CIwFMat2D const & m0)
	{
		return IsRotSame(m0) && IsTransSame(m0);
	}

	bool operator != (CIwFMat2D const & m0)
	{
		return !IsRotSame(m0) || !IsTransSame(m0);
	}

	bool IsRotIdentity()
	{
		return IsRotSame(g_Identity);
	}

	bool IsTransIdentity()
	{
		return IsTransSame(g_Identity);
	}

	bool IsIdentity()
	{
		return (*this) == g_Identity;
	}

	void SetIdentity()
	{
		*this = g_Identity;
	}

	bool IsRotZero()
	{
		return m[0][0] == 0 &&
			m[0][1] == 0 &&
			m[1][0] == 0 &&
			m[1][1] == 0;
	}

	bool IsTransZero()
	{
		return t.x == 0 &&
			t.y == 0;
	}

	bool IsZero()
	{
		return IsRotZero() && IsTransZero();
	}

	void SetZero()
	{
		m[0][0] = m[0][1] = m[1][0] = m[1][1] = 0.0f;
	}


	void Zero()
	{
		SetZero();
	}

	float GetDeterminant() const
	{
		return m[0][0] * m[1][1] - m[0][1] * m[1][0];
	}
};