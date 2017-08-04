#pragma once
#include "IwMaterial.h"

class CIw2DImage 
{
public:
	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;
	virtual CIwMaterial* GetMaterial() = 0;
	virtual ~CIw2DImage() {};
};