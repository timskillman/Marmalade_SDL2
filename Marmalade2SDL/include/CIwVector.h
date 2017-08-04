#pragma once

#include "s3e.h"
#include <cmath>

#define RETURN_ADD(a, b) return ((a) + (b))

inline iwfixed IW_FIXED_MUL2(iwfixed a, iwfixed b, iwfixed d, iwfixed e)
{
	return ((a * d) + (b * e)) >> IW_GEOM_POINT;
}

inline iwfixed IW_FIXED_MUL(iwfixed a, iwfixed b)
{
	return (a * b) >> IW_GEOM_POINT;
}

inline iwfixed IW_FIXED_MUL2_SAFE(iwfixed a, iwfixed b, iwfixed d, iwfixed e)
{
	int64 res = ((((int64)a * d) + ((int64)b * e)) >> IW_GEOM_POINT);
	//IwAssertMsgN(354, GEOM, res >> 63 == res >> 31, ("Multiply overflow"));
	return (iwfixed)res;
}

inline int32_t IW_MUL_2_SHIFT(int32 a, int32 b, int32 d, int32 e, int32 shift)
{
	return ((a * d) + (b * e)) >> shift;
}

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

	//CIwFVec3 operator += (CIwFVec3 rhs)
	//{
	//	return CIwFVec3(x + rhs.x, y + rhs.y, z + rhs.z);
	//}

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

	void LookAt(const CIwFVec3& from, const CIwFVec3& to, const CIwFVec3& up)
	{
	//	// This is set up for a right-handed coordinate system
	//	CIwFVec3 vx, vy, vz;

	//	vz = (to - from).GetNormalised();  // Forward vector
	//	vx = (up ^ vz);                    // Right vector
	//	if (vx.IsZero())
	//		vx.x = 1.0f;
	//	else
	//		vx.Normalise();
	//	vy = (vz ^ vx);
	//	m[0][0] = vx.x; m[0][1] = vx.y; m[0][2] = vx.z;
	//	m[1][0] = vy.x; m[1][1] = vy.y; m[1][2] = vy.z;
	//	m[2][0] = vz.x; m[2][1] = vz.y; m[2][2] = vz.z;
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


	/**
	* Linear interpolation of rotation elements.
	* @param m0 Start rotation elements.
	* @param m1 End rotation elements.
	* @param fraction Relative amount of start and end elements to use.
	* fraction is constrained to [0, 1.0f].\n
	* fraction = 0 results in rotation being set to that of @a m0.\n
	* fraction = 1.0f results in rotationbeing set to that of @a m1.
	*/
	void InterpRot(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction);

	void InterpolateRot(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction)
	{
		InterpRot(m0, m1, fraction);
	}


	/**
	* Linear interpolation of translation elements.
	* @param m0 Start translation elements.
	* @param m1 End translation elements.
	* @param fraction Relative amount of start and end position to use.
	* fraction is constrained to [0, 1.0f]. \n
	* fraction = 0 results in position set to that of @a m0.\n
	* fraction = 1.0f results in position being set to that of @a m1.
	*/
	void InterpTrans(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction);

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


	CIwFMat2D GetInverse() const;


private:

	static float FindComponentFromBA(const CIwFMat2D& A, const CIwFMat2D& B, const int i, const int j)
	{
		return B.m[i][0] * A.m[0][j] + B.m[i][1] * A.m[1][j];

	}



};


class CIwSVec2
{
public:
	int16 x; //!< x-coordinate of the vector
	int16 y; //!< y-coordinate of the vector

			 /** Zero vector. */
	static    CIwSVec2    g_Zero;

	/** World X-axis. */
	static    CIwSVec2    g_AxisX;

	/** World Y-axis. */
	static    CIwSVec2    g_AxisY;
};

class CIwVec2
{
public:
	int32 x; //!< x-coordinate of the vector
	int32 y; //!< y-coordinate of the vector

			 /** Zero vector. */
	static    CIwVec2    g_Zero;

	/** World X-axis. */
	static    CIwVec2    g_AxisX;

	/** World Y-axis. */
	static    CIwVec2    g_AxisY;

	/**
	* Constructor: creates a new vector.
	*/
	CIwVec2() : x(0), y(0) {};

	/**
	* Constructor: creates a new vector.
	* @param _x X-component
	* @param _y Y-component
	*/
	CIwVec2(int32 _x, int32 _y) : x(_x), y(_y) {};

	explicit CIwVec2(const CIwFVec2& v);

	CIwVec2 operator = (const CIwFVec2& v);

	/**
	* @name Length
	* The following functions calculate the length of a vector. Variations
	* include optimisations for speed, security and fixed points.
	* @{
	*/

	/**
	* Supplies the length of the vector.
	* @return The length of the vector shifted (to fixed point representation).
	*/
	int32    GetLength() const;

	/**
	* Calculates the length of the vector.
	* @return The length of the vector shifted (to fixed point representation).
	*/
	inline int32    GetLengthSquared() const
	{

#ifdef IW_DEBUG
		int64 test;
		test = (int64)x*x + (int64)y*y; IwAssertMsg(GEOM, test >> 63 == test >> 31, ("CIwVec2 overflow"));
#endif
		return (x*x + y*y) >> IW_GEOM_POINT;
	}

	/**
	* Supplies the length of the vector with extra checking
	* done in order to prevent overflows.
	* @return The length of the vector shifted (to fixed point representation).
	*/
	int32    GetLengthSafe() const;

	/**
	* Calculates the length of the vector (multiplied in 64 Bit
	* in order to prevent overflows).
	* @return The length of the vector shifted (to fixed point representation).
	*/
	int32    GetLengthSquaredSafe() const;

	/**
	* Calculates the length of the vector.
	* @return The length of the vector unshifted.
	*/
	int32    GetLengthSquaredUnshifted() const;
	/**
	* @}
	*/

	/**
	* @name Normalise
	* The following functions normalise vectors, thus producing an output
	* vector that retains its orientation with a length equal to 1.
	* @{
	*/

	/**
	* Normalises a given vector to a vector having the same direction, but with
	* a length equal to 1 +/- approximately 4/2^12.
	*/
	void    NormaliseSlow();

	/**
	* Calculates 1 / sqrt(x) using a lookup table. This makes it approximately
	* five times faster than the Normalise() function.
	* The resulting vector's length will be normalised
	* within a margin of about +/- 12 / 2^12, whereas
	* the result of the Normalise() function will have
	* an inaccuracy of about +/- 4 / 2^12.
	*/
	void    Normalise();

	/**
	* Supplies a normalised vector - using Normalise().
	* @return A normalised version of the vector.
	*/
	CIwVec2        GetNormalised() const;

	/**
	* Normalises a given vector to a vector having the same direction,
	* but with a length equal to 1 +/- 4 / 2^12.
	* @remarks An additional checking mechanism is implemented in order to
	* prevent overflows.
	*/
	void    NormaliseSafe();

	/**
	* Supplies a normalised vector (using NormaliseSafe).
	* @return A normalised version of the vector.
	*/
	CIwVec2  GetNormalisedSafe() const;
	/**
	* Checks if a vector is normalised. The margin allowed is less than 0.36%
	* (chosen based on the accuracy of the Normalise() function), so the error
	* should be < 0.18%.
	* @return true if normalised, false otherwise.
	*/
	bool    IsNormalised() const;
	//@}

	/**
	* @name Miscellaneous
	* The following are helper functions that implement the most commonly
	* used operations.
	* @{
	*/

	/**
	* Functionality for writing/reading to a storage device.
	*/
	void    Serialise(void);

	/**
	* Checks if all vector components are zero.
	* @return true if zero, otherwise false.
	*/
	bool    IsZero() const;

	/**
	* Dot product.
	* @param Vector for dot product operation.
	* @return Resulting scalar value.
	*/
	inline int32 Dot(CIwVec2 const & v) const { return *this * v; }

	//--------------------------------------------------------------------------
	// Operator overloads - same type
	//--------------------------------------------------------------------------
	/**
	* @name Operator overloads.
	* Using vectors as operators.
	* @{
	*/

	/**
	* Simple assignment.
	* @param v Vector to assign from.
	* @return Resulting vector.
	*/
	CIwVec2& operator = (CIwVec2 const & v);

	/**
	* Addition.
	* @param v Vector to add.
	* @return Resulting vector.
	*/
	CIwVec2 operator + (CIwVec2 const & v) const;

	/**
	* Addition.
	* @param v Vector to add.
	* @return Resulting vector.
	*/
	CIwVec2 & operator += (CIwVec2 const & v);

	/**
	* Subtraction.
	* @param v Vector to subtract.
	* @return Resulting vector.
	*/
	CIwVec2 operator - (CIwVec2 const & v) const;

	/**
	* Subtraction.
	* @param v Vector to subtract.
	* @return Resulting vector.
	*/
	CIwVec2 & operator -= (CIwVec2 const & v);

	/**
	* Dot product.
	* @param Vector to dot product with.
	* @return Resulting scalar value .
	*/
	int32 operator * (CIwVec2 const & v) const;


	/**
	* Equalilty.
	* @param v Vector to compare with.
	* @return true if equal, false otherwise.
	*/
	bool operator == (CIwVec2 const & v) const;

	/**
	* Inequality.
	* @param v Vector to compare with.
	* @return true if unequal, false otherwise.
	*/
	bool operator != (CIwVec2 const & v) const;
	//@}

	/**
	* @name Operator overloads
	* Using scalar values.
	* @{
	*/

	/**
	* Unary negation : Component wise unary negation.
	* @return Resulting vector.
	*/
	CIwVec2 operator - () const;

	/**
	* Multiplication : Component wise multiplication with a scalar
	* @param l scalar value to be multiplied with
	* @return Resulting vector.
	*/
	CIwVec2 operator * (iwfixed l) const;

	/**
	* Multiplication assignment: Component wise multiplication with a scalar
	* with an assignment afterwards.
	* @param l Scalar value to be multiplied with and assigned aftwerwards.
	* @return Resulting vector.
	*/
	CIwVec2 & operator *= (iwfixed l);

	/**
	* Division : Component wise division by a scalar.
	* @param s Scalar value to divide by.
	* @return Resulting vector.
	*/
	CIwVec2 operator / (const iwfixed s) const;

	/**
	* Right shift : Component-wise right shift by a scalar value.
	* @param s Scalar value to shift by.
	* @return Resulting vector.
	*/
	CIwVec2 operator >> (const int s) const;

	/**
	* Right shift Assignment: Component-wise right shift by a scalar value
	* with an assignment afterwards.
	* @param s Scalar value to shift by.
	* @return Resulting vector.
	*/
	CIwVec2 operator >>= (const int s);

	/**
	* Left shift Assignment: Component-wise left shift by a scalar value.
	* @param s Scalar value to shift by.
	* @return Resulting vector.
	*/
	CIwVec2 operator << (const int s) const;

	/**
	* Left shift Assignment: Component-wise left shift by a scalar value
	* with an assignment afterwards.
	* @param s Scalar value to shift by.
	* @return Resulting vector.
	*/
	CIwVec2 operator <<= (const int s);

	/**
	* Member access by index
	* @param n Member to get
	* @return Reference to nth member
	*/
	int32 & operator [] (const int n);

	/**
	* Const member access by index
	* @param n Member to get
	* @return Reference to nth member
	*/
	int32 operator [] (const int n) const;
};

class CIwMat2D
{
public:
	/**
	* 2x2 rotation matrix.
	*/
	iwfixed m[2][2];
	/**
	* Trans vector.
	*/
	CIwVec2 t;

	/**
	* Identity matrix.
	*/
	static  CIwMat2D g_Identity;

	/**
	* Creates a new uninitialised matrix.
	*/
	CIwMat2D() {};

	/**
	* Creates a new matrix of scales by parameter @a f along each axis.
	* @param f Rotation set as identity scaled by @a f.
	*/
	explicit CIwMat2D(iwfixed f)
	{
		m[0][0] = m[1][1] = f;
		m[0][1] = m[1][0] = 0;
		t.x = t.y = 0;
	}

	/**
	* Creates a new matrix from the supplied matrix.
	* @param M Reference to matrix to copy.
	* @see CIwFMat2D
	*/
	explicit CIwMat2D(const CIwFMat2D & M);

	/**
	* Creates a CIwFMat2D matrix from this one.
	* @see CIwFMat2D
	*/
	inline CIwFMat2D ConvertToCIwFMat2D();


	/**
	* Creates a new matrix with given rotation and (vector) translation
	* @param R Reference to matrix from which to copy rotation.
	* @param T Reference to vector from which to copy translation.
	* @see CIwVec2
	*/
	CIwMat2D(CIwMat2D const & R, CIwVec2 const & T)
	{
		m[0][0] = R.m[0][0];
		m[1][0] = R.m[1][0];
		m[0][1] = R.m[0][1];
		m[1][1] = R.m[1][1];
		t = T;
	}

	/**
	* Creates a new matrix with given rotation and (short vector) translation.
	* @param R Reference to matrix from which to copy rotation.
	* @param T Reference to short vector from which to copy translation.
	* @see CIwSVec2
	*/
	//CIwMat2D(CIwMat2D const & R, CIwSVec2 const & T)
	//{
	//	m[0][0] = R.m[0][0];
	//	m[1][0] = R.m[1][0];
	//	m[0][1] = R.m[0][1];
	//	m[1][1] = R.m[1][1];
	//	t = T;
	//}


	/**
	* Reads/writes binary file using @a IwSerialise interface.
	* @see IwSerialise
	*/
	void Serialise();

	/**
	* Ensures the rotation part of matrix is orthogonal.
	* (TODO: This function could be faster using Gram-Schmidt orthogonalisation)
	*/
	void Normalise()
	{
		CIwVec2* pVecX = (CIwVec2*)&m[0][0];
		CIwVec2* pVecY = (CIwVec2*)&m[1][0];

		pVecX->Normalise();

		*pVecY = CIwVec2(-pVecX->y, pVecX->x);
	}

	/**
	* Transposes rotation part of matrix.
	*/
	void Transpose();

	/**
	* Gets the translation vector part of a matrix.
	* @return Reference to the translation vector part of supplied matrix.
	*/
	CIwVec2 const & GetTrans() const
	{
		return t;
	}

	/**
	* Sets the translation vector part of a matrix.
	* @param v Reference to vector to be set as translation part of a matrix.
	* @return Reference to matrix.
	*/
	CIwMat2D & SetTrans(CIwVec2 const & v)
	{
		t = v;
		return *this;
	}

	/**
	* Sets the translation vector part of the supplied matrix.
	* @param v Reference to vector to be set as translation part of a matrix.
	* @return Reference to matrix.
	*/
	//CIwMat2D & SetTrans(CIwSVec2 const & v)
	//{
	//	t = v;
	//	return *this;
	//}

	/**
	* Translates matrix.
	* @param V Vector to add onto translation part of a matrix.
	* @return Reference to matrix.
	*/
	CIwMat2D & operator += (CIwVec2 const & V)
	{
		t += V;
		return *this;
	}


	//CIwMat2D & operator += (CIwSVec2 const & V)
	//{
	//	t += V;
	//	return *this;
	//}

	/**
	* Gets a copy of this matrix translated by given vector.
	* @param V Vector by which to translate matrix copy.
	* @return Translated matrix.
	*/
	CIwMat2D operator + (CIwVec2 const & V) const
	{
		return CIwMat2D(*this, t + V);
	}

	/**
	* Gets a copy of this matrix translated by given vector.
	* @param V Vector by which to translate matrix copy.
	* @return Translated matrix
	*/
	//CIwMat2D operator + (CIwSVec2 const & V) const
	//{
	//	return CIwMat2D(*this, t + V);
	//}


	/**
	* Shifts elements of a matrix.
	* @param s Left shift to apply to elements of matrix.
	* @return Reference to matrix.
	*/
	CIwMat2D& operator <<= (int32 s)
	{
		m[0][0] <<= s; m[0][1] <<= s;
		m[1][0] <<= s; m[1][1] <<= s;
		t.x <<= s, t.y <<= s;
		return *this;
	}

	/**
	* Shifts elements of matrix.
	* @param s Right shift to apply to elements of matrix.
	* @return Reference to matrix.
	*/
	CIwMat2D& operator >>= (int32 s)
	{
		m[0][0] >>= s; m[0][1] >>= s;
		m[1][0] >>= s; m[1][1] >>= s;
		t.x >>= s, t.y >>= s;
		return *this;
	}

	/**
	* Vector representing the world (codomain) space X-axis in local (domain) space.
	* @return The same vector as calling TransposeRotateVec(CIwVec2::g_AxisX).
	*/
	CIwVec2 ColumnX() const
	{
		return CIwVec2(m[0][0], m[1][0]);
	}
	/**
	* Vector representing the world (codomain) space Y-axis in local (domain) space.
	* @return The same vector as calling TransposeRotateVec(CIwVec2::g_AxisY).
	*/
	CIwVec2 ColumnY() const
	{
		return CIwVec2(m[0][1], m[1][1]);
	}

#define VecX RowX
	/**
	* Vector representing the local (domain) space X-axis in world (codomain) space.
	* @return The same vector as calling RotateVec(CIwVec2::g_AxisX).
	* @note Function has alias VecX.
	*/
	CIwVec2 RowX() const
	{
		return CIwVec2(m[0][0], m[0][1]);
	}

#define VecY RowY
	/**
	* Vector representing the local (domain) space Y-axis in world (codomain) space.
	* @return The same vector as calling RotateVec(CIwVec2::g_AxisY).
	* @note Function has alias VecY.
	*/
	CIwVec2 RowY() const
	{
		return CIwVec2(m[1][0], m[1][1]);
	}

	/**
	* Transforms vector by rotation part of matrix.
	* @param V Vector to transform.
	* @return Vector rotated by rotation part of matrix.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 RotateVec(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2(m[0][0], m[1][0], V.x, V.y),
			IW_FIXED_MUL2(m[0][1], m[1][1], V.x, V.y)
		);
	}

	/**
	* Transforms vector by rotation part of matrix.
	* @param V vector to transform.
	* @return Vec rotated by rotation part of matrix.
	* @note Debug version provides overflow checking.
	*/
	//CIwSVec2 RotateVec(CIwSVec2 const &V) const
	//{
	//	return CIwSVec2(
	//		IW_SFIXED_FROM_FIXED(IW_FIXED_MUL2(m[0][0], m[1][0], V.x, V.y)),
	//		IW_SFIXED_FROM_FIXED(IW_FIXED_MUL2(m[0][1], m[1][1], V.x, V.y))
	//	);
	//}

	/**
	* Transforms vector by rotation part of matrix. Calculation is made using int64 numbers.
	* @param V Vector to transform.
	* @return Vector rotated by rotation part of matrix.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 RotateVecSafe(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2_SAFE(m[0][0], m[1][0], V.x, V.y),
			IW_FIXED_MUL2_SAFE(m[0][1], m[1][1], V.x, V.y)
		);
	}

	/**
	* Transforms vector by rotation and then translation parts of matrix.
	* @param V Vector to transform
	* @return Vector transformed by matrix.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransformVec(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2(m[0][0], m[1][0], V.x, V.y) + t.x,
			IW_FIXED_MUL2(m[0][1], m[1][1], V.x, V.y) + t.y
		);
	}

	/**
	* Transforms vector by rotation and then translation parts of matrix.
	* @param V Vector to transform.
	* @return Transformed vector.
	* @note This overload takes a short vector but it returns a vector, as the translation is a vector.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransformVec(CIwSVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2(m[0][0], m[1][0], V.x, V.y) + t.x,
			IW_FIXED_MUL2(m[0][1], m[1][1], V.x, V.y) + t.y
		);
	}

	/**
	* Transforms vector by rotation and then translation parts of matrix using a specifiable shift amount.
	* @param V Vector to transform.
	* @param shift amount to shift rotational component of matrix down by
	* @return Transformed vector compensated for shift down - so it will be in correct fixed point format.
	* @note This takes a short vector but it returns a vector, as the translation is a vector.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransformVecShift(CIwSVec2 const &V, int32 shift) const
	{
		int32 lDotShift = IW_GEOM_POINT - shift;
		return CIwVec2(
			IW_MUL_2_SHIFT(m[0][0] >> shift, m[1][0] >> shift, V.x, V.y, lDotShift) + t.x,
			IW_MUL_2_SHIFT(m[0][1] >> shift, m[1][1] >> shift, V.x, V.y, lDotShift) + t.y
		);
	}



	/**
	* Transforms vector by rotation and then translation parts of matrix. Calculation is made using int64 numbers.
	* @param V Vector to transform.
	* @return Transformed vector.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransformVecSafe(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2_SAFE(m[0][0], m[1][0], V.x, V.y) + t.x,
			IW_FIXED_MUL2_SAFE(m[0][1], m[1][1], V.x, V.y) + t.y
		);
	}
	/**
	* Transforms vector by rotation and then translation parts of matrix. Calculation is made using int64 numbers.
	* @param V Vector to transform.
	* @return Transformed vector.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransformVecSafe(CIwSVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2_SAFE(m[0][0], m[1][0], V.x, V.y) + t.x,
			IW_FIXED_MUL2_SAFE(m[0][1], m[1][1], V.x, V.y) + t.y
		);
	}

	/**
	* If matrix is orthogonal, transforms vector by inverse of rotation part of matrix.
	* @param V Vector to transform.
	* @return Transformed vector.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransposeRotateVec(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2(m[0][0], m[0][1], V.x, V.y),
			IW_FIXED_MUL2(m[1][0], m[1][1], V.x, V.y)
		);
	}

	/**
	* If matrix is orthogonal, transforms vector by inverse of rotation part of matrix.
	* @param V vector to transform
	* @return Transformed matrix.
	* @note Debug version provides overflow checking.
	*/
	//CIwSVec2 TransposeRotateVec(CIwSVec2 const &V) const
	//{
	//	return CIwSVec2(
	//		IW_SFIXED_FROM_FIXED(IW_FIXED_MUL2(m[0][0], m[0][1], V.x, V.y)),
	//		IW_SFIXED_FROM_FIXED(IW_FIXED_MUL2(m[1][0], m[1][1], V.x, V.y))
	//	);
	//}

	/**
	* If matrix is orthogonal, transforms vector by inverse of rotation part of matrix. Calculation is made using int64 numbers.
	* @param V vector to transform
	* @return Transformed matrix.
	* @note Debug version provides overflow checking
	*/
	CIwVec2 TransposeRotateVecSafe(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2_SAFE(m[0][0], m[0][1], V.x, V.y),
			IW_FIXED_MUL2_SAFE(m[1][0], m[1][1], V.x, V.y)
		);
	}

	/**
	* If matrix is orthogonal, performs the same operation as transforming vector by inverse
	* of the matrix.
	* @param V Vector to transform.
	* @return Vector, less translation vector, and then transformed by transpose of rotation part of matrix.
	* @note Debug version provides overflow checking.
	*/
	CIwVec2 TransposeTransformVec(CIwVec2 const &V) const
	{
		return CIwVec2(
			IW_FIXED_MUL2(m[0][0], m[0][1], V.x - t.x, V.y - t.y),
			IW_FIXED_MUL2(m[1][0], m[1][1], V.x - t.x, V.y - t.y)
		);
	}


#ifdef IW_DEBUG
#define RETURN_ADD(a, b) int64 test = (((int64)(a)) + ((int64)(b)));\
    IwAssertMsg(GEOM, test >> 63 == test >> 31,("Add overflow."));\
    return (iwfixed)test;
#else
#define RETURN_ADD(a, b) return ((a) + (b))
#endif
	iwfixed TransformVecX(CIwVec2 const &V) const { RETURN_ADD(IW_FIXED_MUL2(m[0][0], m[1][0], V.x, V.y), t.x); }
	iwfixed TransformVecY(CIwVec2 const &V) const { RETURN_ADD(IW_FIXED_MUL2(m[0][1], m[1][1], V.x, V.y), t.y); }
	iwfixed TransformVecX(iwsfixed x, iwsfixed y) const { RETURN_ADD(IW_FIXED_MUL2(m[0][0], m[1][0], x, y), t.x); }
	iwfixed TransformVecY(iwsfixed x, iwsfixed y) const { RETURN_ADD(IW_FIXED_MUL2(m[0][1], m[1][1], x, y), t.y); }
	iwfixed TransformVecX(iwfixed x, iwfixed y) const { RETURN_ADD(IW_FIXED_MUL2(m[0][0], m[1][0], x, y), t.x); }
	iwfixed TransformVecY(iwfixed x, iwfixed y) const { RETURN_ADD(IW_FIXED_MUL2(m[0][1], m[1][1], x, y), t.y); }


	/**
	* If matrix is orthogonal, finds X component of vector transformed by inverse of rotation part of matrix.
	* @param V vector to transform
	* @return X-component of vector transformed by transpose of rotation part of matrix
	*/
	inline   iwfixed RotateVecX(const CIwVec2& V)
	{
		return IW_FIXED_MUL(m[0][0], V.x) + IW_FIXED_MUL(m[1][0], V.y);
	}
	/**
	* If matrix is orthogonal, finds Y component of vector transformed by inverse of rotation part of matrix.
	* @param V Vector to transform.
	* @return Y-component of vector transformed by transpose of rotation part of matrix.
	*/
	inline   iwfixed RotateVecY(const CIwVec2& V)
	{
		return IW_FIXED_MUL(m[0][1], V.x) + IW_FIXED_MUL(m[1][1], V.y);
	}

	/**
	* If matrix is orthogonal, finds X component of vector transformed by inverse of rotation part of matrix.
	* @param V Vector to transform.
	* @return X-component of vector transformed by transpose of rotation part of matrix.
	*/
	inline   iwsfixed RotateVecX(const CIwSVec2& V)
	{
		return IW_SFIXED_FROM_FIXED(IW_FIXED_MUL(m[0][0], V.x) + IW_FIXED_MUL(m[1][0], V.y));
	}
	/**
	* If matrix is orthogonal, finds Y component of vector transformed by inverse of rotation part of matrix.
	* @param V Vector to transform
	* @return Y-component of vector transformed by transpose of rotation part of matrix
	*/
	inline   iwsfixed RotateVecY(const CIwSVec2& V)
	{
		return IW_SFIXED_FROM_FIXED(IW_FIXED_MUL(m[0][1], V.x) + IW_FIXED_MUL(m[1][1], V.y));
	}


	/**
	* @return Matrix with transpose of rotation part and zero translation.
	*/
	CIwMat2D GetTranspose() const
	{
		CIwMat2D N;
		N.m[0][0] = m[0][0];
		N.m[1][0] = m[0][1];
		N.m[0][1] = m[1][0];
		N.m[1][1] = m[1][1];

		// Note: this clears the translation vector
		N.t = CIwVec2(0, 0);
		return N;
	}

	/**
	* Sets matrix to be rotation around Z-axis by given angle.
	* @param r Angle of rotation.
	* @param resetTrans Whether the translation part of the matrix should be reset.
	* @param setZeros Whether the rotation should be zeroed (apart from the elements which determine the rotation).
	*/
	inline void  SetRot(iwangle r = 0, bool resetTrans = true)
	{
		if (resetTrans)     t.x = t.y = 0;
		m[0][0] = m[1][1] = IW_GEOM_COS((float)-r);
		m[0][1] = -(m[1][0] = IW_GEOM_SIN((float)-r));
	}

	/**
	* Sets matrix to be rotation around Z-axis at a point by given angle
	* @param r Angle of rotation
	* @param centre Centre of rotation
	*/
	inline void  SetRot(iwangle r, const CIwVec2& centre)
	{
		m[0][0] = m[1][1] = IW_GEOM_COS((float)-r);
		m[0][1] = -(m[1][0] = IW_GEOM_SIN((float)-r));
		t = centre - RotateVec(centre);
	}

	// TODO: Could optimise these functions
	inline void PreRotate(iwangle r)
	{
		CIwMat2D rz;
		rz.SetRot(r, true);
		PreRotate(rz);
	}
	inline void PostRotate(iwangle r)
	{
		CIwMat2D rz;
		rz.SetRot(r, true);
		PostRotate(rz);
	}


	/**
	* Composes two matrices together.
	* @param M Matrix by which to post multiply.
	* @return (this matrix) * M. Does not modify either input matrix.
	*/
	CIwMat2D operator * (CIwMat2D const & M) const
	{
		CIwMat2D N;
		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		N.t = M.TransformVec(t);

		//IwAssertMsg(GEOM, N.TransformVec(CIwVec2::g_Zero) ==
		//	M.TransformVec(TransformVec(CIwVec2::g_Zero)), ("CIwMat2D overflow: operator *"));

		return N;
	}


	/**
	* Composes two matrices together.
	* @param M matrix by which to pre multiply.
	* @return M * (this matrix). Overwrites this matrix.
	*/
	CIwMat2D & PreMult(CIwMat2D const & M)
	{
		return (*this = M * (*this));
	}

	/**
	* This method is deprecated in favour of CIwMat2D::PreMult(M).
	*/
	CIwMat2D & PreMultiply(CIwMat2D const & M)
	{
		//IwAssertMsg(GEOM, false, ("This method is deprecated in favour of CIwMat2D::PreMult(M)."));
		return PreMult(M);
	}


	/**
	* Composes two matrices together.
	* @param M matrix by which to post multiply.
	* @return (this matrix) * M. Overwrites this matrix.
	*/
	CIwMat2D & PostMult(CIwMat2D const & M)
	{
		return (*this = (*this) * M);
	}

	/**
	* This method is deprecated in favour of CIwMat2D::PostMult(M).
	*/
	CIwMat2D & PostMultiply(CIwMat2D const & M)
	{
		//IwAssertMsg(GEOM, false, ("This method is deprecated in favour of CIwMat2D::PostMult(M)."));
		return PostMult(M);
	}


	/**
	* Post multiplies matrix.
	* @param M Matrix by which to multiply.
	* @return Reference to matrix.
	*/
	CIwMat2D& operator *= (CIwMat2D const & M)
	{
		return PostMult(M);
	}


	/**
	* Transform the rotation part of the matrix by that of the supplied matrix.
	* @param M matrix from which to apply rotation.
	* @return Reference to matrix.
	*/
	CIwMat2D&  PostRotate(CIwMat2D const& M)
	{
		CIwMat2D N;

		N.m[0][0] = FindComponentFromBA(M, *this, 0, 0);
		N.m[0][1] = FindComponentFromBA(M, *this, 0, 1);

		N.m[1][0] = FindComponentFromBA(M, *this, 1, 0);
		N.m[1][1] = FindComponentFromBA(M, *this, 1, 1);

		CopyRot(N);

		return *this;
	}

	/**
	* Transforms the rotation part of the matrix by that of the supplied matrix.
	* @param M Matrix from which to apply rotation.
	* @return Reference to matrix.
	*/
	CIwMat2D PreRotate(CIwMat2D const& M)
	{
		CIwMat2D tmp = M;
		tmp.t = this->t;
		return (*this = tmp.PostRotate(*this));
	}


	/**
	* Scales rotation part of matrix.
	* @param v Scale to apply to rotation.
	* @return Reference to matrix.
	*/
	CIwMat2D& ScaleRot(iwfixed v)
	{
		for (int i = 0; i<2; i++)
			for (int j = 0; j<2; j++)
				m[i][j] = IW_FIXED_MUL(m[i][j], v);
		return *this;
	}

	/**
	* Scales translation part of matrix.
	* @param v Scale to apply to rotation.
	* @return Reference to matrix.
	*/
	CIwMat2D& ScaleTrans(iwfixed v)
	{
		t *= v;
		return *this;
	}

	/**
	* Scales rotation and translation parts of matrix.
	* @param v Scale to apply to matrix.
	*/
	CIwMat2D& Scale(iwfixed v)
	{
		ScaleRot(v);
		ScaleTrans(v);
		return *this;
	}

	/**
	* Scales matrix.
	* @param v Scale to apply to matrix
	* @return reference to matrix
	*/
	CIwMat2D& operator *= (const iwfixed v)
	{
		Scale(v);
		return *this;
	}


	/**
	* Linear interpolation of rotation elements.
	* @param m0 Start rotation elements.
	* @param m1 End rotation elements.
	* @param fraction Relative amount of start and end elements to use.
	* fraction is constrained to [0, IW_GEOM_ONE].\n
	* fraction = 0 results in rotation being set to that of @a m0.\n
	* fraction = IW_GEOM_ONE results in rotationbeing set to that of @a m1.
	*/
	void    InterpRot(CIwMat2D const & m0, CIwMat2D const & m1, iwfixed fraction);

	/** This method is deprecated in favour of CIwMat2D::InterpRot(m0, m1, fraction). */
	void InterpolateRot(CIwMat2D const & m0, CIwMat2D const & m1, iwfixed fraction)
	{
		//IwAssertMsg(GEOM, false, ("This method is deprecated in favour of CIwMat2D::InterpRot(m0, m1, fraction)."));
		InterpRot(m0, m1, fraction);
	}


	/**
	* Linear interpolation of translation elements.
	* @param m0 Start translation elements.
	* @param m1 End translation elements.
	* @param fraction Relative amount of start and end position to use.
	* fraction is constrained to [0, IW_GEOM_ONE]. \n
	* fraction = 0 results in position set to that of @a m0.\n
	* fraction = IW_GEOM_ONE results in position being set to that of @a m1.
	*/
	void    InterpTrans(CIwMat2D const & m0, CIwMat2D const & m1, iwfixed fraction);

	/** This method is deprecated in favour of CIwMat2D::InterpTrans(m0, m1, fraction). */
	void InterpolatePos(CIwMat2D const & m0, CIwMat2D const & m1, iwfixed fraction)
	{

		//IwAssertMsg(GEOM, false, ("This method is deprecated in favour of CIwMat2D::InterpTrans(m0, m1, fraction)."));
		InterpTrans(m0, m1, fraction);
	}


	/**
	* Copies rotation from another matrix.
	* @param m0 Source matrix.
	*/
	void    CopyRot(const CIwMat2D& m0)
	{
		m[0][0] = m0.m[0][0];
		m[0][1] = m0.m[0][1];
		m[1][0] = m0.m[1][0];
		m[1][1] = m0.m[1][1];
	}

	/**
	* Copies translation from another matrix.
	* @param m0 Source matrix.
	*/
	void    CopyTrans(const CIwMat2D& m0)
	{
		t = m0.t;
	}


	/**
	* Determines if rotation part equal to another matrix.
	* @param m0 Matrix for comparison with.
	* @return true if the matrices have equal rotation elements, otherwise false.
	*/
	bool IsRotSame(CIwMat2D const& m0) const
	{
		return  m[0][0] == m0.m[0][0] &&
			m[0][1] == m0.m[0][1] &&
			m[1][0] == m0.m[1][0] &&
			m[1][1] == m0.m[1][1];
	}

	/**
	* Determines if translation part of one matrix is equal to that of another matrix.
	* @param m0 Matrix for comparison.
	* @return true if the matrices have equal translation elements, otherwise false.
	*/
	bool IsTransSame(CIwMat2D const& m0) const
	{
		return (t == m0.t);
	}

	/**
	* Determines if matrix is equal to another matrix.
	* @param m0 Matrix for comparison.
	* @return true if the matrices are equal, otherwise false.
	*/
	bool operator == (CIwMat2D const & m0) const
	{
		return IsRotSame(m0) && IsTransSame(m0);
	}


	/**
	* Determines if matrix is not equal to another matrix.
	* @param m0 Matrix for comparison.
	* @return true if the matrices are not equal, otherwise false.
	*/
	bool operator != (CIwMat2D const & m0) const
	{
		return !IsRotSame(m0) || !IsTransSame(m0);
	}


	/** Determines if rotation part equal is equal to the identity rotation. */
	bool IsRotIdentity()
	{
		return IsRotSame(g_Identity);
	}

	/** Determines if translation part equal is equal to the zero vector. */
	bool IsTransIdentity()
	{
		return IsTransSame(g_Identity);
	}

	/** Determines if matrix is equal to the identity matrix. */
	bool IsIdentity()
	{
		return (*this) == g_Identity;
	}

	/** Sets matrix to the identity matrix. */
	void SetIdentity()
	{
		*this = g_Identity;
	}

	/** Determines if rotation part is equal to zero. */
	bool IsRotZero()
	{
		return m[0][0] == 0 &&
			m[0][1] == 0 &&
			m[1][0] == 0 &&
			m[1][1] == 0;
	}

	/** Determines if translation part is equal to zero. */
	bool IsTransZero()
	{
		return t.x == 0 &&
			t.y == 0;
	}

	/** Determines if matrix is equal to zero. */
	bool IsZero()
	{
		return IsRotZero() && IsTransZero();
	}

	/** Sets matrix to zero. */
	void SetZero();

	/** This method is deprecated in favour of CIwMat2D::SetZero(). */
	void Zero()
	{
		//IwAssertMsg(GEOM, false, ("This method is deprecated in favour of CIwMat2D::SetZero()."));
		SetZero();
	}

	iwfixed GetDeterminant() const
	{
		return IW_FIXED_MUL(m[0][0], m[1][1]) - IW_FIXED_MUL(m[0][1], m[1][0]);
	}

	/**
	* @ return Matrix that represents the inverse operation. Will return identity if inverse is not possible (i.e. determinant is zero)
	*/
	CIwMat2D GetInverse() const;



	// EXPERIMENTAL

	// Experimental fixed point functions go below.


	// end: experimental functions






private:

	// works out the component (i,j) of the composite matrix BA
	static inline iwfixed FindComponentFromBA(const CIwMat2D& A, const CIwMat2D& B, const int i, const int j)
	{

#ifdef IW_DEBUG
		int64 testA = (int64)(B.m[i][0]) * A.m[0][j];
		IwAssertMsg(GEOM, testA >> 63 == testA >> 31, ("Matrix multiplication overflow"));

		int64 testB = (int64)(B.m[i][1]) * A.m[1][j];
		IwAssertMsg(GEOM, testB >> 63 == testB >> 31, ("Matrix multiplication overflow"));

		int64 test = testA + testB;
		IwAssertMsg(GEOM, test >> 63 == test >> 31, ("Matrix multiplication overflow"));

#endif
		return (B.m[i][0] * A.m[0][j] + B.m[i][1] * A.m[1][j]) >> IW_GEOM_POINT;
	}



};

