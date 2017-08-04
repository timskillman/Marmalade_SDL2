#include "Iw2D.h"
#include "IwGx.h"

namespace SG2DVars {
	GLfloat nearz;
	GLfloat farz;
	CIwColour colour;
	GLfloat linewidth;
	bool drawingPerspective;

	//Used from rendering internal 2D elements
	GLfloat verts[IW_MAX_VERTS];
	GLint indices[IW_MAX_INDICES];
	GLshort lindexes[IW_MAX_LINDEX];
	GLfloat uvs[IW_MAX_UVS];
	GLfloat rectuv[8];
	GLfloat light[2][4];
}

void Iw2DInit()
{
	for (uint16_t i = 0; i < IW_MAX_LINDEX; i++) SG2DVars::lindexes[i] = i;
}

void Iw2Ddraw(GLenum mode, GLsizei size)
{
	//if (SG2DVars::drawingPerspective) {
	//	IwGx::SetOrtho();
	//	SG2DVars::drawingPerspective = false;
	//}
	changeColour();
	glLineWidth(SG2DVars::linewidth);
	glVertexPointer(3, GL_FLOAT, 0, &SG2DVars::verts);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDrawElements(mode, size, GL_UNSIGNED_SHORT, &SG2DVars::lindexes);
}

void Iw2DDrawLine(CIwFVec2 from, CIwFVec2 too)
{
	SG2DVars::verts[0] = from.x; SG2DVars::verts[1] = from.y; SG2DVars::verts[2] = IW_2D_DIST;
	SG2DVars::verts[3] = too.x; SG2DVars::verts[4] = too.y; SG2DVars::verts[5] = IW_2D_DIST;
	draw(GL_LINE_STRIP, 2);
}


void Iw2DDrawRect(CIwFVec2 pos, CIwFVec2 size)
{
	SG2DVars::verts[0] = pos.x; SG2DVars::verts[1] = pos.y; SG2DVars::verts[2] = IW_2D_DIST;
	SG2DVars::verts[3] = pos.x + size.x; SG2DVars::verts[4] = pos.y; SG2DVars::verts[5] = IW_2D_DIST;
	SG2DVars::verts[6] = pos.x + size.x; SG2DVars::verts[7] = pos.y + size.y; SG2DVars::verts[8] = IW_2D_DIST;
	SG2DVars::verts[9] = pos.x; SG2DVars::verts[10] = pos.y + size.y; SG2DVars::verts[11] = IW_2D_DIST;
	SG2DVars::verts[12] = pos.x; SG2DVars::verts[13] = pos.y; SG2DVars::verts[14] = IW_2D_DIST;
	draw(GL_LINE_STRIP, 5);
}

void Iw2DDrawPolygon(CIwFVec2* verts, int32_t numberVerts, bool closed)
{
	for (int32_t i = 0; i < numberVerts; i++) {
		SG2DVars::verts[i * 3] = verts[i].x;
		SG2DVars::verts[i * 3 + 1] = verts[i].y;
		SG2DVars::verts[i * 3 + 2] = IW_2D_DIST;
	}
	if (closed) {
		SG2DVars::verts[numberVerts * 3] = verts[0].x;
		SG2DVars::verts[numberVerts * 3 + 1] = verts[1].y;
		SG2DVars::verts[numberVerts * 3 + 2] = IW_2D_DIST;
		numberVerts++;
	}
	draw(GL_LINE_STRIP, numberVerts);
}

void Iw2DDrawImage(CIw2DImage * image, CIwFVec2 pos, CIwFVec2 size)
{
}

void Iw2DFillRect(CIwFVec2 pos, CIwFVec2 size)
{
	SG2DVars::verts[0] = pos.x; SG2DVars::verts[1] = pos.y; SG2DVars::verts[2] = IW_2D_DIST;
	SG2DVars::verts[3] = pos.x; SG2DVars::verts[4] = pos.y + size.y; SG2DVars::verts[5] = IW_2D_DIST;
	SG2DVars::verts[6] = pos.x + size.x; SG2DVars::verts[7] = pos.y + size.y; SG2DVars::verts[8] = IW_2D_DIST;
	SG2DVars::verts[9] = pos.x + size.x; SG2DVars::verts[10] = pos.y; SG2DVars::verts[11] = IW_2D_DIST;
	draw(GL_TRIANGLE_FAN, 4);
}

void Iw2DFillPolygon(CIwFVec2* verts, int32_t numberVerts)
{
	for (int32_t i = 0; i < numberVerts; i++) {
		SG2DVars::verts[i * 3] = verts[i].x;
		SG2DVars::verts[i * 3 + 1] = verts[i].y;
		SG2DVars::verts[i * 3 + 2] = IW_2D_DIST;
	}
	draw(GL_TRIANGLE_FAN, numberVerts);
}

void Iw2DFillArc(CIwFVec2 pos, CIwFVec2 size, float from, float too, uint16_t segs)
{
	float PI2 = 2.0f*PI;

	if (from < too)
	{
		uint32_t numVerts = (uint32_t)(floorf((too - from) / 0.1f) + 1.f);
		std::vector<CIwFVec2> verts;
		verts.resize(numVerts + 1);

		verts[0].x = pos.x;
		verts[0].y = pos.y;

		float increment = 0.0f;

		for (uint32_t i = 1; i < numVerts; i++)
		{
			verts[i].x = pos.x + (size.x * sinf(from + increment));
			verts[i].y = pos.y - (size.y * cosf(from + increment));
			increment += 0.1f;
		}

		verts[numVerts].x = pos.x + (size.x * sinf(too));
		verts[numVerts].y = pos.y - (size.y * cosf(too));

		FillPolygon(verts.data(), numVerts + 1);
	}
	else
	{
		uint32_t numVerts = (uint32_t)(floorf((too - from) / 0.1f) + 1.f);
		std::vector<CIwFVec2> verts;
		verts.resize(numVerts + 1);

		verts[0].x = pos.x;
		verts[0].y = pos.y;

		float increment = 0.0f;

		for (uint32_t i = 1; i < numVerts; i++)
		{
			verts[i].x = pos.x + (size.x * sinf(too + increment));
			verts[i].y = pos.y - (size.y * cosf(too + increment));
			increment += 0.1f;
		}

		verts[numVerts].x = pos.x + (size.x * sinf(from));
		verts[numVerts].y = pos.y - (size.y * cosf(from));

		FillPolygon(verts.data(), numVerts + 1);
	}
}

void DrawTexture(CIwTexture* tex, CIwFVec2 pos, CIwFVec2 size, float* uvopt)
{
	if (tex && tex->textureID>0) {
		int currentID = 0;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentID); //Get current texture ID

		if (currentID != tex->textureID) glBindTexture(GL_TEXTURE_2D, tex->textureID);
		glEnable(GL_TEXTURE_2D);

		SG2DVars::verts[0] = pos.x; SG2DVars::verts[1] = pos.y; SG2DVars::verts[2] = IW_2D_DIST;
		SG2DVars::verts[3] = pos.x; SG2DVars::verts[4] = pos.y + size.y; SG2DVars::verts[5] = IW_2D_DIST;
		SG2DVars::verts[6] = pos.x + size.x; SG2DVars::verts[7] = pos.y + size.y; SG2DVars::verts[8] = IW_2D_DIST;
		SG2DVars::verts[9] = pos.x + size.x; SG2DVars::verts[10] = pos.y; SG2DVars::verts[11] = IW_2D_DIST;

		if (uvopt) {
			glTexCoordPointer(2, GL_FLOAT, 0, uvopt);
		}
		else
		{
			glTexCoordPointer(2, GL_FLOAT, 0, SG2DVars::rectuv);
		}

		changeColour();

		//glColor3f(1.0f,1.0f,1.0f);
		//glLineWidth(SG2DVars::linewidth);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, &SG2DVars::verts);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &SG2DVars::lindexes);

		if (currentID != tex->textureID) glBindTexture(GL_TEXTURE_2D, currentID);  //Restore previous texture
		glDisable(GL_TEXTURE_2D);
	}
}

void Iw2DSetColour(uint8 r, uint8 g, uint8 b)
{
	SG2DVars::colour.r = r;
	SG2DVars::colour.g = g;
	SG2DVars::colour.b = b;
	SG2DVars::colour.a = 255;
}

void Iw2DSetColour(CIwColour colour)
{
	SG2DVars::colour = colour;
}

void Iw2DLineWidth(float width)
{
	SG2DVars::linewidth = width;
}

CIw2DImage * Iw2DCreateImage(const char * filename)
{
	return nullptr;
}

CIw2DImage * Iw2DCreateImage(CIwImage & image)
{
	return nullptr;
}

void Iw2DSetTransformMatrix(CIwFMat2D & mtx)
{
}

void Iw2DSurfaceShow()
{
}

void changeColour()
{
	glColor4ub(SG2DVars::colour.r, SG2DVars::colour.g, SG2DVars::colour.b, SG2DVars::colour.a);
}

void Iw2DDrawArc(CIwFVec2 pos, CIwFVec2 size, float from, float too, uint16_t segs)
{
	float PI2 = 2.0f*PI;

	//if (from > PI2)
	//{
	//	from -= floorf(from / PI2)*PI2;

	//	if (from < 0.00001f)
	//	{
	//		from = PI2;
	//	}
	//}
	//else if (from < 0.0f)
	//{
	//	from -= ceilf(from / PI2)*PI2;

	//	if (from > -0.00001f)
	//	{
	//		from = PI2;
	//	}
	//}

	//if (too > PI2)
	//{
	//	too -= floorf(too / PI2)*PI2;
	//	
	//	if (too < 0.00001f)
	//	{
	//		too = PI2;
	//	}
	//}
	//else if (too < 0.0f)
	//{
	//	too -= ceilf(too / PI2)*PI2;

	//	if (too > -0.00001f)
	//	{
	//		too = PI2;
	//	}
	//}

	if (from < too)
	{
		uint32_t numVerts = (uint32_t)(floorf((too - from) / 0.1f));
		std::vector<CIwFVec2> verts;
		verts.resize(numVerts+1);
			
		float increment = 0.1f;

		//size_t j = 0;
		//for (float i = from; i < too; i += increment) {
		//	pverts[j].x = pos.x + (size.x * sinf(i));
		//	pverts[j++].y = pos.y - (size.y * cosf(i));
		//}

		for (uint32_t i = 0; i < numVerts; i++)
		{
			verts[i].x = pos.x + (size.x * sinf(from + increment));
			verts[i].y = pos.y - (size.y * cosf(from + increment));
			increment += 0.1f;
		}

		verts[numVerts].x = pos.x + (size.x * sinf(too));
		verts[numVerts].y = pos.y - (size.y * cosf(too));

		DrawPolygon(verts.data(), numVerts + 1, false);
	}
	else
	{
		uint32_t numVerts = (uint32_t)(floorf((from - too) / 0.1f));
		std::vector<CIwFVec2> verts;
		verts.resize(numVerts + 1);

		float increment = 0.0f;

		for (uint32_t i = 0; i < numVerts; i++)
		{
			verts[i].x = pos.x + (size.x * sinf(too + increment));
			verts[i].y = pos.y - (size.y * cosf(too + increment));
			increment += 0.1f;
		}

		verts[numVerts].x = pos.x + (size.x * sinf(from));
		verts[numVerts].y = pos.y - (size.y * cosf(from));

		DrawPolygon(verts.data(), numVerts + 1, false);
	}
}


