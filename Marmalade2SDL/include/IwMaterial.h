#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "s3e.h"
//#include "IwImage.h"
#include "s3eTypes.h"
#include "IwTexture.h"



class CIwMaterial {
public:
	CIwMaterial();

	void SetTexture(CIwTexture* texture) { matTexture = texture; }
	void SetColAmbient(CIwColour &colour);
	void SetColAmbient(uint32 colour);
	void SetColAmbient(uint8 r, uint8 g, uint8 b, uint8 a);
	void SetColEmissive(uint32 colour);
	void SetColEmissive(CIwColour &colour);
	void SetColEmissive(uint8 r, uint8 g, uint8 b, uint8 a);
	void SetColDiffuse(CIwColour &colour);
	void SetColDiffuse(uint32 colour);
	void SetColDiffuse(uint8 r, uint8 g, uint8 b, uint8 a);
	void SetColSpecular(CIwColour &colour);
	void SetColSpecular(uint32 colour);
	void SetColSpecular(uint8 r, uint8 g, uint8 b, uint8 a);
	void SetSpecularPower(uint32_t s) { shininess = (float)s / 255.0f; }
	void SetAlphaMode(GLenum mode) { }
	void SetCullMode(int32_t cm) { cullmode = (cm==1); }
	void makeCurrent();

	enum {
		ALPHA_NONE = 0,
		ALPHA_HALF = 1,
		ALPHA_ADD = 2,
		ALPHA_SUB = 3,
		ALPHA_BLEND = 4,
		ALPHA_DEFAULT = 5
	};

	enum {
		CULL_FRONT,
		CULL_BACK,
		CULL_NONE
	};

	CIwTexture* matTexture;

private:
	GLfloat colAmbient[4];
	GLfloat colDiffuse[4];
	GLfloat colEmissive[4];
	GLfloat colSpecular[4];
	float shininess;
	bool cullmode;

};