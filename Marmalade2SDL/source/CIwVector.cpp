#include "CIwVector.h"

CIwFMat2D CIwFMat2D::g_Identity;

void CIwFMat2D::InterpRot(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction)
{
}

void CIwFMat2D::InterpTrans(CIwFMat2D const & m0, CIwFMat2D const & m1, float fraction) //TODO
{
}

CIwFMat2D CIwFMat2D::GetInverse() const //TODO
{
	CIwFMat2D m;
	return m;
}

CIwVec2::CIwVec2(const CIwFVec2 & v)
{
	x = (int32)v.x;
	y = (int32)v.y;
}


CIwVec2 CIwVec2::operator=(const CIwFVec2 & v)
{
	return CIwVec2((int32)v.x, (int32)v.y);
}

int32 CIwVec2::GetLength() const
{
	return (int32)std::sqrtf((float)(x*x + y*y));
}

int32 CIwVec2::GetLengthSafe() const //TODO
{
	return (int32)std::sqrtf((float)(x*x + y*y));
}

int32 CIwVec2::GetLengthSquaredSafe() const //TODO
{
	return x*x+y*y;
}

int32 CIwVec2::GetLengthSquaredUnshifted() const //TODO
{
	return (x*x + y*y);
}

void CIwVec2::NormaliseSlow() //TODO
{
}

void CIwVec2::Normalise() //TODO
{
}

CIwVec2 CIwVec2::GetNormalised() const //TODO
{
	CIwVec2 v;
	return v;
}

void CIwVec2::NormaliseSafe() //TODO
{
}

CIwVec2 CIwVec2::GetNormalisedSafe() const //TODO
{
	CIwVec2 v;
	return v;
}

bool CIwVec2::IsNormalised() const //TODO
{
	return false;
}

void CIwVec2::Serialise(void) //TODO
{
}

bool CIwVec2::IsZero() const //TODO
{
	return false;
}

CIwVec2 & CIwVec2::operator=(CIwVec2 const & v)
{
	*this = v;
	return *this;
}

CIwVec2 CIwVec2::operator+(CIwVec2 const & v) const
{
	return CIwVec2(x+v.x,y+v.y);
}

CIwVec2 & CIwVec2::operator+=(CIwVec2 const & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

CIwVec2 CIwVec2::operator-(CIwVec2 const & v) const
{
	return CIwVec2(x - v.x, y - v.y);
}

CIwVec2 & CIwVec2::operator-=(CIwVec2 const & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

//Dot product ...
int32 CIwVec2::operator*(CIwVec2 const & v) const
{
	return v.x*x+y*v.y;
}

bool CIwVec2::operator==(CIwVec2 const & v) const
{
	return ((x==v.x) && (y==v.y));
}

bool CIwVec2::operator!=(CIwVec2 const & v) const
{
	return ((x != v.x) && (y != v.y));
}

CIwVec2 CIwVec2::operator-() const
{
	return CIwVec2(-x,-y);
}

CIwVec2 CIwVec2::operator*(iwfixed l) const
{
	return CIwVec2(x*l >> IW_GEOM_POINT,y*l >> IW_GEOM_POINT);
}

CIwVec2 & CIwVec2::operator*=(iwfixed l)
{
	// TODO: insert return statement here
	x = x*l >> IW_GEOM_POINT;
	y = y*l >> IW_GEOM_POINT;
	return *this;
}

CIwVec2 CIwVec2::operator/(const iwfixed s) const //TODO
{
	//Not correct!
	return CIwVec2(x/(s >> IW_GEOM_POINT), y/(s >> IW_GEOM_POINT));
}

CIwVec2 CIwVec2::operator >> (const int s) const
{
	return CIwVec2((int32)x>>s,(int32)y>>s);
}

CIwVec2 CIwVec2::operator>>=(const int s)
{
	return CIwVec2((int32)x >> s, (int32)y >> s);
}

CIwVec2 CIwVec2::operator<<(const int s) const
{
	return CIwVec2((int32)x << s, (int32)y << s);
}

CIwVec2 CIwVec2::operator<<=(const int s)
{
	return CIwVec2((int32)x << s, (int32)y << s);
}

int32 & CIwVec2::operator[](const int n)
{
	// TODO: insert return statement here
	int32 a = 0;
	return a;
}

int32 CIwVec2::operator[](const int n) const
{
	int32 a = 0;
	return a;
}

