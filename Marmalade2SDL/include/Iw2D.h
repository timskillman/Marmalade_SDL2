#pragma once

#include "IwGx.h"
#include "IwMath.h"
#include "CIwImage.h"
#include <vector>

void Iw2DInit();
void Iw2DDrawLine(CIwFVec2 from, CIwFVec2 too);
void Iw2DDrawRect(CIwFVec2 pos, CIwFVec2 size);
void Iw2DDrawArc(CIwFVec2 pos, CIwFVec2 size, float from, float too, uint16_t segs = 32); //TODO
void Iw2DDrawPolygon(CIwFVec2* verts, int32_t numberVerts, bool closed);
void Iw2DDrawImage(CIw2DImage* image, CIwFVec2 pos, CIwFVec2 size); //TODO
void Iw2DFillRect(CIwFVec2 pos, CIwFVec2 size);
void Iw2DFillPolygon(CIwFVec2* verts, int32_t numberVerts);
void Iw2DFillArc(CIwFVec2 pos, CIwFVec2 size, float from, float too, uint16_t segs = 32); //TODO
void Iw2DSetColour(uint8 r, uint8 g, uint8 b);
void Iw2DSetColour(CIwColour colour);
void Iw2DLineWidth(float width);
CIw2DImage* Iw2DCreateImage(const char* filename);
CIw2DImage* Iw2DCreateImage(CIwImage &image);
void Iw2DSetTransformMatrix(CIwFMat2D &mtx);
void Iw2DSurfaceShow();

//New calls
void DrawTexture(CIwTexture* tex, CIwFVec2 pos, CIwFVec2 size, float* uvopt = NULL);
void changeColour();

