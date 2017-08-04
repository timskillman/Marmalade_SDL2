#include "IwGx.h"

CIwFVec2 CIwFVec2::g_Zero;
CIwFVec3 CIwFVec3::g_Zero;
CIwFMat CIwFMat::g_Identity;


namespace SGVars {
	//Static vars
	SDLwindow* Gxwindow = 0;

	SDL_GLContext Gxcontext;
	GLfloat nearz;
	GLfloat farz;
	CIwColour colour;
	GLfloat linewidth;
	bool drawingPerspective;

	//Used from rendering internal 2D elements
	//GLfloat verts[IW_MAX_VERTS];
	//GLint indices[IW_MAX_INDICES];
	GLshort lindexes[IW_MAX_LINDEX];
	//GLfloat uvs[IW_MAX_UVS];
	GLfloat rectuv[8];
	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat gmatrix[4][4];
};



void InitVars()
{
	SGVars::nearz = IW_NEARZ;
	SGVars::farz = IW_FARZ;
	//SR2D::SetColour(255, 255, 255);
	SGVars::linewidth = 0.f;
	SGVars::drawingPerspective = true;
	SGVars::Gxwindow->mousewheel = 0;

	for (uint16_t i = 0; i < IW_MAX_LINDEX; i++) SGVars::lindexes[i] = i;

	//These UVs will be used continuously for textured rectangles
	SGVars::rectuv[0] = 0.0f; SGVars::rectuv[1] = 0.0f;
	SGVars::rectuv[2] = 0.0f; SGVars::rectuv[3] = 1.0f;
	SGVars::rectuv[4] = 1.0f; SGVars::rectuv[5] = 1.0f;
	SGVars::rectuv[6] = 1.0f; SGVars::rectuv[7] = 0.0f;

	SGVars::light_ambient[0] = 0.f; SGVars::light_ambient[1] = 0.f; SGVars::light_ambient[2] = 0.f; SGVars::light_ambient[3] = 1.f;
	SGVars::light_diffuse[0] = 0.5f; SGVars::light_diffuse[1] = 0.5f; SGVars::light_diffuse[2] = 0.5f; SGVars::light_diffuse[3] = 1.f;

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);
	SDL_GL_MakeCurrent(SGVars::Gxwindow->handle(), SGVars::Gxcontext);

	glLoadIdentity();
	//glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//glDisable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
}

bool IwGxInit(SDLwindow* window)
{
	SGVars::Gxwindow = window;
	SGVars::Gxcontext = SDL_GL_CreateContext(SGVars::Gxwindow->handle());
		
	InitVars();
	return true;
}

bool IwGxInit(const char * title, int width, int height, Uint32 flags)
{
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); //Turn on anti-aliasing (before creating the SDL window)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

	SGVars::Gxwindow = new SDLwindow;
	if (!SGVars::Gxwindow->init(title, width, height, flags)) return false;
	SGVars::Gxcontext = SDL_GL_CreateContext(SGVars::Gxwindow->handle());

	InitVars();
	return true;
}

void IwGxTerminate()
{
	SGVars::Gxwindow->destroy();
	SDL_GL_DeleteContext(SGVars::Gxcontext);
}

void IwGxSetPerspMul(float perspmul)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	GLfloat aspect = (float)vp[2] / (float)vp[3];

	//Following 3 lines of code make a FOV compatible with gluPerspective from a perspective multiplier...
	//----------------------------------------------------------------------------------------------------
	//float irad1 = 360.f / PI;
	//float fov = (std::atanf(((float)vp[3]*0.5f) /perspmul))*irad1;  //angle = atan((height/2) / perspmul)
	//gluPerspective(perspmul, aspect, SGVars::nearz, SGVars::farz);
	// /* Perspective(fov, aspect, SGVars::nearz, SGVars::farz); */		//internal routine

	//BUT! ... we can trash the ATAN/TAN and radian conversions to just ...
	float fov = ((float)vp[3] / 2.f) / perspmul;

	GLfloat ymax = SGVars::nearz * (GLfloat)fov;
	GLfloat ymin = -ymax;
	GLfloat xmin = ymin * aspect;
	GLfloat xmax = -xmin;
	glFrustum((GLdouble)xmin, (GLdouble)xmax, (GLdouble)ymin, (GLdouble)ymax, (GLdouble)SGVars::nearz, (GLdouble)SGVars::farz);

	glEnable(GL_DEPTH_TEST);
}

void IwGxSetOrtho(float left, float right, float top, float bottom, float nearz, float farz) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, top, bottom, (GLdouble)nearz, (GLdouble)farz);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IwGxSetOrtho()
{
	//Set whole GL display as 1:1 2D canvas (top-left origin)
	SetOrtho(0, (float)SGVars::Gxwindow->getWidth(), (float)SGVars::Gxwindow->getHeight(), 0.f, -1.0f, 1.f);
}

void IwGxSetFarZNearZ(float _farz, float _nearz) {
	SGVars::nearz = _nearz;
	SGVars::farz = _farz;
}

void IwGxSetZDepthFixed(float z)
{
}

void IwGxSetViewMatrix(CIwFMat* viewmat) {

}

void IwGxconvCIwFMat_glMtx(GLfloat *mtx, CIwFMat* modelmat)
{
	mtx[0] = modelmat->m[0][0];
	mtx[1] = modelmat->m[0][1];
	mtx[2] = modelmat->m[0][2];
	mtx[3] = 0.0f;
	mtx[4] = modelmat->m[1][0];
	mtx[5] = modelmat->m[1][1];
	mtx[6] = modelmat->m[1][2];
	mtx[7] = 0.0f;
	mtx[8] = modelmat->m[2][0];
	mtx[9] = modelmat->m[2][1];
	mtx[10] = modelmat->m[2][2];
	mtx[11] = 0.0f;
	mtx[12] = modelmat->t.x;
	mtx[13] = modelmat->t.y;
	mtx[14] = modelmat->t.z;
	mtx[15] = 1.0f;
}

void IwGxSetModelMatrix(CIwFMat* modelmat) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//GLfloat mtx[4][4];
	convCIwFMat_glMtx(*SGVars::gmatrix, modelmat);
	glLoadMatrixf(*SGVars::gmatrix);
	//glTranslatef(0, 0, pos.z);
	//glRotatef(rot.x, 1, 0, 0);
	//glRotatef(rot.y, 0, 1, 0);
	//glRotatef(0, 0, 0, 1);
}

CIwFMat IwGxGetModelViewClipMatrix() {
	CIwFMat mat;
	return mat;
}

void IwGxSetLightType(uint32_t LightNo, uint32_t LightType) {
	//TODO: Lighting colour can change after setting the light type!
	switch (LightType) {
	case IW_GX_LIGHT_AMBIENT:
		glLightfv(GL_LIGHT0 | LightNo, GL_AMBIENT, SGVars::light_ambient);
		break;
	case IW_GX_LIGHT_DIFFUSE:
		glLightfv(GL_LIGHT0 | LightNo, GL_DIFFUSE, SGVars::light_diffuse);
		break;
	}
}

void IwGxSetLightDirn(uint32_t LightNo, CIwFVec3* light_position) {
	//uint32 lno = GL_LIGHT0 | LightNo;
	glLightfv(GL_LIGHT0 | LightNo, GL_DIFFUSE, SGVars::light_diffuse);
	glLightfv(GL_LIGHT0 | LightNo, GL_AMBIENT, SGVars::light_ambient);
	GLfloat lp[4];
	lp[0] = light_position->x; lp[1] = light_position->y; lp[2] = light_position->z; lp[3] = 0.0f;
	glLightfv(GL_LIGHT0 | LightNo, GL_POSITION, lp);
}

void IwGxSetLightPos(uint32_t LightNo, CIwFVec3* light_position) {
	//uint32 lno = 0x4000 | LightNo;
	glLightfv(GL_LIGHT0 | LightNo, GL_DIFFUSE, SGVars::light_diffuse);
	glLightfv(GL_LIGHT0 | LightNo, GL_AMBIENT, SGVars::light_ambient);
	GLfloat lp[4];
	lp[0] = light_position->x; lp[1] = light_position->y; lp[2] = light_position->z; lp[3] = 0.0f;
	glLightfv(GL_LIGHT0 | LightNo, GL_POSITION, lp);
}

void IwGxSetLightCol(uint32_t LightNo, CIwColour * colour)
{
	switch (LightNo) {
	case 0:
		SGVars::light_ambient[0] = (float)colour->r / 255.f;
		SGVars::light_ambient[1] = (float)colour->g / 255.f;
		SGVars::light_ambient[2] = (float)colour->b / 255.f;
		SGVars::light_ambient[3] = (float)colour->a / 255.f;
		break;
	case 1:
		SGVars::light_diffuse[0] = (float)colour->r / 255.f;
		SGVars::light_diffuse[1] = (float)colour->g / 255.f;
		SGVars::light_diffuse[2] = (float)colour->b / 255.f;
		SGVars::light_diffuse[3] = (float)colour->a / 255.f;
		break;
	}
}

void IwGxSetLightCol(uint32_t LightNo, GLuint* colour) {

}

void IwGxSetFogCol(GLuint* colour) {

}

void IwGxSetFogFarZNearZ(float far, float near) {

}

void IwGxFogOn() {

}

void IwGxSetColClear(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	glClearColor((float)r / 255.f, (float)g / 255.f, (float)b / 255.f, (float)a / 255.f);
}

void IwGxClear(GLenum flags) {
	glClear(flags);
}

void IwGxLightingOn() {
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void IwGxLightingOff() {
	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
}

void IwGxSetMaterial(CIwMaterial* material) {
	if (material)
		material->makeCurrent();
	else {
		glDisable(GL_TEXTURE_2D);
		//glDisable(GL_COLOR_MATERIAL);
	}

}

void IwGxFlush() {
	glFlush();
}

void IwGxSwapBuffers() {
	SDL_GL_SwapWindow(SGVars::Gxwindow->handle());
}

uint16_t IwGxClipVec(CIwFVec3 vec) {
	uint16_t clip = 0;
	return clip;
}

void IwGxSetColStream(GLvoid* cols, int count)
{
	if (cols != NULL) {
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, cols);
		glEnableClientState(GL_COLOR_ARRAY);
		//glEnable(GL_COLOR_MATERIAL);
	}
	else {
		glDisableClientState(GL_COLOR_ARRAY);
		//glDisable(GL_COLOR_MATERIAL);
	}
}

void IwGxSetUVStream(GLvoid* uv)
{
	if (uv != NULL) {
		glTexCoordPointer(2, GL_FLOAT, 0, uv);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void IwGxSetNormStream(const GLvoid* normals, int count)
{
	if (normals != NULL) {
		glNormalPointer(GL_FLOAT, 0, normals);
		glEnableClientState(GL_NORMAL_ARRAY);
	}
	else {
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

void IwGxSetNormStream(uint32_t p)
{
}

void IwGxSetVertStream(const GLvoid* verts, int count)
{
	if (verts != NULL) {
		glVertexPointer(3, GL_FLOAT, 0, verts);
		glEnableClientState(GL_VERTEX_ARRAY);
	}
	else {
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void IwGxSetVertStreamModelSpace(const GLvoid* verts, int count)
{
	if (verts != NULL) {
		glVertexPointer(3, GL_FLOAT, 0, verts);
		glEnableClientState(GL_VERTEX_ARRAY);
	}
	else {
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void IwGxSetVertStreamScreenSpace(const GLvoid * verts, int count)
{
}

void IwGxDrawPrims(uint16_t mode, GLvoid* indices, int indexNo)
{
	if (indices==nullptr) glDrawElements(mode, indexNo, GL_UNSIGNED_SHORT, &SGVars::lindexes); else
		glDrawElements(mode, indexNo, GL_UNSIGNED_SHORT, indices);
}

void DrawPolygon3D(CIwFVec3* verts, int32_t numberVerts, bool closed)
{
	srgx::SetColour();
	glLineWidth(SGVars::linewidth);
	glDisableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &verts);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_LINE_STRIP, numberVerts, GL_UNSIGNED_SHORT, &SGVars::lindexes);
}

void Perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
	//equivalent to gluPerspective ...
	GLfloat xmin, xmax, ymin, ymax;
	float rad1 = PI / 360.f;
	//float irad1 = 360.f / PI;

	//float pm = (std::atanf((float)GetScreenWidth() / 800.f) / 2.0f); // *irad1;
	float zf = tanf(fovy * rad1);
	ymax = zNear * (GLfloat)zf;
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum((GLdouble)xmin, (GLdouble)xmax, (GLdouble)ymin, (GLdouble)ymax, (GLdouble)zNear, (GLdouble)zFar);
}

void _IwGxSetViewRect(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
}

void IwGxLightingSpecular(bool s) {}; //TODO

uint32_t IwGxGetScreenWidth()
{
	return SGVars::Gxwindow->getWidth();
}

uint32_t IwGxGetScreenHeight()
{
	return SGVars::Gxwindow->getHeight();
};


//void SetColour()
//{
//	glColor4ub(SGVars::colour.r, SGVars::colour.g, SGVars::colour.b, SGVars::colour.a);
//}
