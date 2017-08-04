#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "s3e.h"
#include "IwImage.h"
#include "SRGXTypes.h"
#include "CIwVector.h"

#ifdef __IPHONEOS__
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif /* __IPHONEOS__ */

#ifdef __ANDROID__
#include <SDL_opengles.h>
#endif /* __ANDROID__ */

#ifdef __WINDOWS__
#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#endif /* __WINDOWS__ */

#ifdef __APPLE__
#include <TargetConditionals.h>
#ifdef TARGET_OS_MAC
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#endif
#endif

class CIwTexture
{
public:

	enum Flags
	{
		// Old CIwTexture flags
		UPLOADED_F = (1 << 0),     //!< This texture has been uploaded.
		NEEDS_SW_TRANSPARENCY_F = (1 << 1),     //!< This texture has (and uses chromakey).
		UPLOAD_ON_LOAD_F = (1 << 2),     //!< Upload this texture as soon as it's been loaded.
		USES_TRANSPARENCY_F = (1 << 3),     //!< Texture uses colour-keying.
		NO_TRANSPARENCY_F = (1 << 4),     //!< Texture doesn't use colour-keying.
		NO_CHROMA_KEY_F = (1 << 5),     //!< Does not convert chroma key values (255, 0 255) to alpha.
		NO_FILTER_F = (1 << 6),     //!< Disable filtering.

		OWNS_TEXELS_F = (1 << 8),     //!< m_Texels (texel data) points to an owned allocation.
		OWNS_PALETTE_F = (1 << 9),     //!< m_Palette (palette data) points to an owned allocation.
		OWNS_PALETTE_CACHE_RGBS_F = (1 << 10),  //!< m_PaletteCacheRGBs points to an owned allocation
		NATIVE_16BIT_F = (1 << 11),    //!< Convert 16bit texture to native when uploading to VRAM
		SHARES_TEXELS_F = (1 << 12),    //!< Uses another texture's texels

		DO_SW_F = (1 << 13),    //!< Perform SW-related functions on this texture
		DO_HW_F = (1 << 14),    //!< Perform HW-related functions on this texture

		KEEP_DATA_AFTER_UPLOAD_F = (1 << 15), //!< Don't delete the texels and palette after upload. Use this for palette animation. Uses no extra memory if software rendering is enabled.
		ANIMATE_UV_F = (1 << 16),    // Animate UVs. USED BY LEGACY CODE ONLY.

		NEVER_SW_F = (1 << 17),    //!< Never upload this texture for SW
		NO_MIPMAPPING_F = (1 << 18),    //!< Disable mipmapping.
		CLAMP_UV_F = (1 << 19),    //!< Clamp (rather than wrap) in U and V

		SKIPPED_MIPMAP_GENERATION = (1 << 20), //!< Record if mip maps should have been generated, but weren't

		CREATE_FOR_3D_API_F = (1 << 21),    //!< For targets which support separate 2D and 3D APIs (e.g. J2ME + JSR-184), create the 3D API image (e.g. JSR-184's Image2D and Texture2D)
		CREATE_FOR_2D_API_F = (1 << 22),    //!< For targets which support separate 2D and 3D APIs (e.g. J2ME + JSR-184), create the 2D API image (e.g. MIDP's Image)

		SHARED_SOURCE_F = (1 << 23),    //!< Other textures share this texture's texels

		CLAMP_UV_SET_F = (1 << 24),    //!< Has HW target been set to clamp?

		DONT_SERIALISE_IMAGE_F = (1 << 25),    //!< Do not save any image data for this texture

		ATTACHED_TO_SURFACE_F = (1 << 26),    //!< It is an error to use a texture that's bound to the active surface
		BOUND_TO_ACTIVE_SURFACE_F = (1 << 27),    //!< It is an error to use a texture that's bound to the active surface
		OWNS_HW_TEXELS_F = (1 << 28),    //!< Does this texture own its HW storage?

		CUBE_MAP_F = (1 << 29),    //!< This texture contains a cube map. The pre-upload texture is a column of cube map faces in the order +ve/-ve x, +ve/-ve y, +ve/-ve z.

		IGNORE_MIPMAP_OFFSET_F = (1 << 30),    //!< This texture will not be affected by the mipmap offset

		ALLOW_LOW_QUALITY_F = (1u << 31),    //!< Indicate low quality compression can be used for this texture
	};

	CIwTexture();
	~CIwTexture();

	virtual void Serialise();
	virtual void Resolve();
	void    LoadFromFile(const char* imageFile);
	void    CopyFromBuffer(uint16_t w, uint16_t h, CIwImage::Format format, uint16_t pitch, uint8_t* pImageData, uint16_t* pPalette);
	void    CopyFromImage(CIwImage* pImg);
	void    SetImage(CIwImage* pImg);
	inline uint8 HasAlpha() const { return m_Image.HasAlpha(); }
	inline bool UsesAlpha(uint8 threshold = 0xff) const { return m_Image.UsesAlpha(threshold); }
	inline bool UsesChromakey() const { return m_Image.UsesChromakey(); }
	virtual void    Upload();
	CIwTexture* ExtractSubTexture(uint16 x, uint16 y, uint16 w, uint16 h, const char* name);
	void    ChangePalette(uint16* pPalette, CIwImage::Format format);
	void    ChangeTexels(uint8* pTexels, CIwImage::Format format);
	void    RemakeMipmaps();
	inline int32 GetPaletteMemSize() const
	{
		return m_Image.GetPaletteMemSize();
	}
	inline int32 GetPaletteNumEntries() const
	{
		return m_Image.GetPaletteSize();
	}
	inline int32 GetTexelsMemSize() const
	{
		return m_Image.GetTexelsMemSize();
	}
	inline uint32 GetWidth() const { return m_Image.GetWidth(); }
	inline uint32 GetHeight() const { return m_Image.GetHeight(); }
	inline uint16 GetDepth() const { return (uint16)m_Image.GetTexelBitDepth(); }
	inline CIwImage::Format GetFormatSW() const { return (CIwImage::Format)m_FormatSW; }
	inline CIwImage::Format GetFormatHW() const { return (CIwImage::Format)m_FormatHW; }
	inline CIwImage::Format GetFormat() const { return m_Image.GetFormat(); }
	inline void SetFormatSW(CIwImage::Format formatSW) { m_FormatSW = formatSW; }
	inline void SetFormatHW(CIwImage::Format formatHW) { m_FormatHW = formatHW; }
	inline uint32 GetFlags() const { return m_Flags; }
	uint8* GetTexels() const;
	//{
	//	//IwAssertMsgN(793, GX, m_Image.GetTexels(),
	//	//	("Texture data is discarded on upload unless the texture has been marked "
	//	//		"as modifiable using SetModifiable or the 'keepAfterUpload' image template parameter."));
	//	return m_Image.GetTexels();
	//}
	void GetTexels(uint8* pTexels, CIwImage::Format format) const;
	inline const uint8* GetPalette() const
	{
		//IwAssertMsgN(794, GX, !(m_Flags & UPLOADED_F) || (m_Flags & KEEP_DATA_AFTER_UPLOAD_F),
		//	("Texture data is discarded on upload unless the texture has been marked "
		//		"as modifiable using SetModifiable or the 'keepAfterUpload' image template parameter."));
		return m_Image.GetPalette();
	}
	void GetPalette(uint16* pPalette, CIwImage::Format format) const;
	uint32  GetPitch() const
	{
		//IwAssertMsgN(795, GX, !(m_Flags & UPLOADED_F), ("Illegal to call this because texture has been uploaded."));
		return m_Image.GetPitch();
	}
	void SetFiltering(bool bOn);
	inline bool GetFiltering() const { return (m_Flags & NO_FILTER_F) == 0; }
	void SetMipMapping(bool bOn);
	inline bool GetMipMapping() const { return (m_Flags & NO_MIPMAPPING_F) == 0; }
	void SetClamping(bool bOn);
	inline bool GetClamping() const
	{
		return (m_Flags & CLAMP_UV_F) != 0;
	}
	void SetModifiable(bool modifiable);
	inline CIwImage& GetImage() { return m_Image; }
	bool GetModifiable() const
	{
		return (0 != (m_Flags & KEEP_DATA_AFTER_UPLOAD_F));
	}
	void UseAsHandle(CIwTexture* pTex);
	CIwTexture* CloneWithNewPalette(const char* name, uint16* pPalette);
	CIwTexture* UploadSubRegion(int u0, int v0, int u1, int v1);
	void    PreparePalette(CIwImage* pImg);
	bool    UsesTransparency(CIwImage* pImg = NULL, int32 threshhold = 30);
	void    ReplaceTexture(CIwTexture* pTex);
	void    ChangePalette(uint16* pPalette);
	void    ChangeTexels(uint8* pTexels);
	void MakeModifiable(bool modifiable)
	{
		//IwAssertMsgN(940, GX, 0, ("MakeModifiable is now deprecated. Call SetModifiable instead."));
		SetModifiable(modifiable);
	}
	//----------------------------------------------------------------------------
	// Private API
	//----------------------------------------------------------------------------
	inline void _SetUploaded() { m_Flags |= UPLOADED_F; }
	inline void _SetUploadOnLoad() { m_Flags |= UPLOAD_ON_LOAD_F; }
	inline void _SetFlags(uint32 flags) { m_Flags |= flags; }
	inline void _ClearFlags(uint32 flags) { m_Flags &= ~flags; }
	inline CIwImage& _GetImage() { return m_Image; }
	void    _FreeTexelData();
	void    _FreePaletteData();
	void    _SetTransparencyFlags(CIwImage* pImg, int threshhold = 30);
	void    _SetTransparencyFlags(int threshhold = 30);
	void    _Refresh();
	void SW_BindToSurface(s3eSurfaceInfo* pSurfaceInfo);
	void SW_ReleaseFromSurface();
	void MakeTransPalIdxZero() { PreparePalette(&m_Image); }
	CIwImage::Format _DetermineFormatSW() const;
	void _SetFormatFromImageTemplate();
	void    _UpdateTexParamsGL(bool always = false);

	//Legacy
	uint16* _GetPaletteFromVRAM();
	uint8*  _GetTexelsFromVRAM();
	uint16* _GetPaletteCopy();
	uint8*  _GetTexelsCopy();
	uint32  _GetTexelVRAMAddress();
	uint32  _GetPaletteVRAMAddress() const;

	// TO DOC - real depth
	int     GetActualColourDepth();

	// Converts the texture to native format.
	//void  Convert();

	// Colour reduction to improve performance.
	void    ColourReduce();

	// Checks to see if a texture is named as source texels for other textures to share eg: image#.bmp
	bool    IsSharedSource();

	// Checks to see if a texture is named specially to share texels with another texture. eg. image#red.bmp
	bool    GetSharedForename(char* sharename, uint32 buffSize);

	// Fill in our texels with original texel data
	void    CopySharedTexels();

	//Get the contents of the texture in a safe, but very slow fashion...
	void    GL_GetContents();

private:
	uint32  _UploadIndividualImageGL(uint32 target, CIwImage& img);
	void    FreeCustomMipMaps();
	void    FindSharedTexels();     // sets g_SharedTexels if any
	//CIwGxCompressedTextureBlock* _Compress();


protected:

	CIwImage        m_Image;
	uint32          m_Flags;        //!< e.g. USES_TRANSPARENCY_F

	CIwImage**      m_CustomMipMaps;
	int32           m_NumCustomMipMaps;

	// (Keep both of these regardless of SW/HW support to pad out previous uint16)
	uint8           m_FormatSW;  //!< Preferred format for software rendering
	uint8           m_FormatHW;  //!< Preferred format for hardware rendering

public:
	//CIwTPageInfo    m_VRAMInfo;         //!< IwRenderer VRAM info for image and palette
	CIwColour*      m_PaletteCacheRGBs; //!< if non-NULL, use these (32?) values as colour multipliers when generating the palettes
	CIwTexture*     m_NonTransparentTex;
	uint32          m_SharedTexelHash;

	// HW-only stuff
	uint32          m_HWID;         //!< OpenGLES texture ID ("texture name")
	uint8           m_UShiftFactor; //!< factor for converting application u to GL fixed pt u; (left shift u by this factor);
	uint8           m_VShiftFactor; //!< factor for converting application v to GL fixed pt v; (left shift v by this factor);
	CIwFVec2        m_UVScale;

	static CIwTexture*  g_Context;
	static uint32       g_Stage;    // if loading from material, which texture stage are we loading to?

	static void SetContext(CIwTexture* tex) { g_Context = tex; };
	static CIwTexture* GetContext() { return g_Context; };

	typedef CIwTexture* GetSharedTexelsFn(CIwTexture* pTexture);
	//static void _SetCallback_GetSharedTexels(GetSharedTexelsFn* pCallback) { g_GetSharedTexelsCallback = pCallback; };

	uint32_t textureID;
private:
	uint8_t* pixels;
	int bpp;
	int format;
	int width;
	int height;
	size_t size;

};