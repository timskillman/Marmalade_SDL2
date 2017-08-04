#pragma once

#include "s3e.h"

class CIwImage {
public:
	CIwImage();
	~CIwImage();
	CIwImage(const CIwImage& img);

	void operator=(CIwImage const &pImg);
	void Serialise();
	void SerialisePaletteOnly();

	typedef enum FormatDataFlags
	{
		// Is palettised?
		PALETTISED_4BIT_F = (1 << 0),
		PALETTISED_5BIT_F = (1 << 1),
		PALETTISED_6BIT_F = (1 << 2),
		PALETTISED_7BIT_F = (1 << 3),
		PALETTISED_8BIT_F = (1 << 4),
		PALETTISED_MASK = PALETTISED_4BIT_F | PALETTISED_5BIT_F | PALETTISED_6BIT_F | PALETTISED_7BIT_F | PALETTISED_8BIT_F,

		ALPHA_F = (1 << 5), // if set, has alpha (i.e. RGBA or ABGR).
		REVERSE_F = (1 << 6), // if set, is reverse order (i.e. BGR or ABGR).

		SIZE_8_F = (1 << 7), // Size of texel (for unpalettised) or palette entry (for palettised)
		SIZE_16_F = (2 << 7), // Size of texel (for unpalettised) or palette entry (for palettised)
		SIZE_24_F = (3 << 7), // Size of texel (for unpalettised) or palette entry (for palettised)
		SIZE_32_F = (4 << 7), // Size of texel (for unpalettised) or palette entry (for palettised)
		SIZE_MASK = (0x7 << 7),

		ALPHA_FLIP_F = (1 << 10),

		NON_PALETTE_ALPHA_F = (1 << 11), // if set, has alpha but stored in texels not in palette (for DS A5I3 and A3I5)

	} FormatDataFlags;

	// PRIVATE - DO NOT DOC
	struct FormatData
	{
		uint16  m_Flags;        // The flags set.
		uint8   m_NumBitsR;     // Number of bits describing R component.
		uint8   m_NumBitsG;     // Number of bits describing G component.
		uint8   m_NumBitsB;     // Number of bits describing B component.
		uint8   m_NumBitsA;     // Number of bits describing A component.

		int32 GetByteDepth() const { return (m_Flags & SIZE_MASK) >> 7; }
	};

	enum Format
	{
		FORMAT_UNDEFINED,       //!< Format is undefined.

		RGB_332,    //!< Unpalettised 8-bit.
		BGR_332,    //!< Unpalettised 8-bit.


		RGB_565,    //!< Unpalettised 16-bit, no alpha.
		BGR_565,    //!< Unpalettised 16-bit, no alpha.


		RGBA_4444,  //!< Unpalettised 16-bit, alpha.
		ABGR_4444,  //!< Unpalettised 16-bit, alpha.
		RGBA_5551,  //!< Unpalettised 16-bit, alpha.
		ABGR_1555,  //!< Unpalettised 16-bit, alpha.


		RGB_888,    //!< Unpalettised 24-bit, no alpha.
		BGR_888,    //!< Unpalettised 24-bit, no alpha.


		RGBA_6666,  //!< Unpalettised 24-bit, alpha.
		ABGR_6666,  //!< Unpalettised 24-bit, alpha.


		RGBA_8888,  //!< Unpalettised 32-bit, alpha.
		ABGR_8888,  //!< Unpalettised 32-bit, alpha.
		RGBA_AAA2,  //!< Unpalettised 32-bit, alpha.
		ABGR_2AAA,  //!< Unpalettised 32-bit, alpha.


		PALETTE4_RGB_888,   //!< 16-colour palettised.
		PALETTE4_RGBA_8888, //!< 16-colour palettised.
		PALETTE4_RGB_565,   //!< 16-colour palettised.
		PALETTE4_RGBA_4444, //!< 16-colour palettised.
		PALETTE4_RGBA_5551, //!< 16-colour palettised.
		PALETTE4_ABGR_1555,

		PALETTE8_RGB_888,   //!< 256-colour palettised.
		PALETTE8_RGBA_8888, //!< 256-colour palettised.
		PALETTE8_RGB_565,   //!< 256-colour palettised.
		PALETTE8_RGBA_4444, //!< 256-colour palettised.
		PALETTE8_RGBA_5551, //!< 256-colour palettised.
		PALETTE8_ABGR_1555,

		PALETTE7_ABGR_1555, //!< 32-colour palettised.
		PALETTE6_ABGR_1555, //!< 64-colour palettised.
		PALETTE5_ABGR_1555, //!< 128-colour palettised.

		// PVRTC formats
		PVRTC_2,            //!< PowerVR compressed format.
		PVRTC_4,            //!< PowerVR compressed format.
		ATITC,              //!< ATI compressed format.
		COMPRESSED,         //!< gfx specific compressed format

		PALETTE4_ABGR_4444, //!< 16-colour palettised.
		PALETTE8_ABGR_4444, //!< 256-colour palettised.

		A_8,                //!< Unpalettised 8-bit alpha.

		ETC,                //!< Ericsson compressed format
		ARGB_8888,          //!< Unpalettised 32-bit, alpha.

		PALETTE4_ARGB_8888, //!< 16-colour palettised.
		PALETTE8_ARGB_8888, //!< 256-colour palettised.

		DXT3,               //!< DXT3 compressed format

		PALETTE4_BGR555,        //!< 16-colour palettised.
		PALETTE8_BGR555,        //!< 16-colour palettised.
		A5_PALETTE3_BGR_555,    //!< 8BPP, of which 5 are alpha and 3 are palette index
		A3_PALETTE5_BGR_555,    //!< 8BPP, of which 3 are alpha and 5 are palette index

		PALETTE4_BGR_565,   //!< 16-colour palettised.
		PALETTE4_ABGR_8888, //!< 16-colour palettised.
		PALETTE8_BGR_565,   //!< 256-colour palettised.
		PALETTE8_ABGR_8888, //!< 256-colour palettised.

		DXT1,               //!< DXT1 compressed format
		DXT5,               //!< DXT5 compressed format

		ETC2,               //!< GLES 3.0 mandated formats
		ETC2_A1,            //!< 1bit alpha version
		EAC_R11,            //!< 1 channel version
		EAC_RG11,           //!< 2 channel version

		ASTC,               //!< ASTC compressed format

		DEPTH_16,           //!< 16 bit depth texture (may not be supported)
		DEPTH_32,           //!< 32 bit depth texture (may not be supported)

		FORMAT_MAX,         // (Terminator)
	};

	enum ImageFlags
	{
		OWNS_TEXELS_F = (1 << 0),  // m_Texels allocation owned by this object.
		OWNS_PALETTE_F = (1 << 1),  // m_Palette allocation owned by this object.
		SERIALISE_NO_TEXELS_F = (1 << 2),  // Do not serialise texels.
		CUBE_MAP_F = (1 << 3),  // This image contains a cube map. The pre-upload texture is a column of cube map faces in the order +ve/-ve x, +ve/-ve y, +ve/-ve z.
		USE_FIXED_BUFFER_F = (1 << 11), // Use fixed buffer for memory allocations
		HAS_ALPHA_FROM_SOURCE_F = (1 << 12), // Alpha channel comes from a full alpha channel in the original image file not from a chromakey
		NO_CONVERT_MAGENTA_F = (1 << 13), // Suppress automatic converion of of magenta to black
		PAL_ZERO_IS_ALPHA_ZERO_F = (1 << 14), // Treat palette entry zero as alpha zero
		NO_CHROMA_KEY_F = (1 << 15), // If set, Chroma key is not applied (255,0,255 does not signify alpha)

									 //these flags are not serialised
									 NON_PERSISTENT_FLAGS_MASK = OWNS_TEXELS_F | OWNS_PALETTE_F | USE_FIXED_BUFFER_F

	} ImageFlags;

	uint32_t GetBitDepth() const { return GetBitDepth(m_Format); }
	static uint32_t GetBitDepth(const Format &format);

	uint32_t GetByteDepth() const { return GetByteDepth(m_Format); }
	static uint32_t GetByteDepth(const Format &format) { return GetBitDepth(format) >> 3; }

	uint32_t GetTexelBitDepth() const { return GetTexelBitDepth(m_Format); }
	static uint32_t GetTexelBitDepth(const Format &format);

	uint32_t GetPaletteSize() const { return GetPaletteSize(m_Format); }
	static uint32_t GetPaletteSize(const Format &format);

	inline uint32 GetTexelsMemSize() const
	{
		if (!IsCompressedFormat(GetFormat()))
		{
			return m_Pitch * m_Height;
		}

		return m_CompressedImageSize;
	}

	uint32 GetPaletteMemSize() const { return GetPaletteMemSize(m_Format); }
	static uint32 GetPaletteMemSize(const Format &format);

	void    SetFormat(Format format);
	inline Format GetFormat() const { return m_Format; }

	inline FormatData GetFormatData() const { return s_FormatData[m_Format]; };
	inline uint16 GetFlags() const { return m_Flags; }

	void SetWidth(uint32 width);
	inline uint32 GetWidth() const { return m_Width; }

	inline uint32 GetByteWidth() const
	{
		uint32 texBitDepth = GetTexelBitDepth();
		uint32 byteWidth = (m_Width * texBitDepth + 7) / 8;

		//IwAssert(UTIL, byteWidth * 8 / texBitDepth >= m_Width &&
		//	(byteWidth - 1) * 8 / texBitDepth < m_Width);
		return byteWidth;
	}

	void SetHeight(uint32 height);
	inline uint32 GetHeight() const { return m_Height; }

	void    SetPitch(uint32 pitch);
	inline uint32 GetPitch() const { return m_Pitch; }

	inline uint8* GetTexels() const { return m_Texels; }

	inline uint8* GetPalette() const { return m_Palette; }

	uint32 FormatColour(uint8 red, uint8 green, uint8 blue, uint8 alpha = 0xff);

	void ColourForFormat(uint32 value, uint16* red, uint16* green, uint16* blue, uint16* alpha);

	void    SetOwnedBuffers(uint8* pTexels, uint8* pPalette);

	inline uint8 HasAlpha() const { return (s_FormatData[m_Format].m_Flags & ALPHA_F) != 0; }

	bool    UsesAlpha(uint8 threshold = 0xff) const;

	bool    UsesChromakey() const;

	bool    TestForChromakey() const;

	//void    ReadFile(s3eFile* pFile);
	//void    ReadFile(s3eFile* pFile, uint8* pTexels, uint32 texelsSize, uint8* pPalette, uint32 palSize);
	void    LoadFromFile(const char* imageFile);

	void    ConvertToImage(CIwImage* pImage, bool chooseDepth = false);

	void    ConvertToImage(CIwImage* pImage, uint8* pTexels, uint32 texelsSize, uint8* pPalette, uint32 palSize, bool chooseDepth);

	void    ReplacePalette(uint8* pPalette);

	uint32  ReplaceColour(uint8 srcR, uint8 srcG, uint8 srcB, uint8 srcA, uint8 dstR, uint8 dstG, uint8 dstB, uint8 dstA);

	uint32  ReplaceAlpha(uint8 threshold, uint8 chromaR, uint8 chromaG, uint8 chromaB);

	uint32      ReplaceAlphaColourWithSurrounding(uint8 threshold = 0x80, uint8 numSurrounding = 0x2);

	uint32      MakeAlphaPalZero(uint8 threshold, uint8 keyR, uint8 keyG, uint8 keyB);

	//void        SetCompressed(CIwGxCompressedTextureBlock* pBlock);

	static void FixedBufferSetSize(uint32 size);

	static void FixedBufferFree();

	static void FixedBufferCheckOverflow();

	inline static bool FixedBufferAvailable()
	{
		//return s_FixedBucket != NULL;
		return false;
	}

	inline void UseFixedBuffer(bool use)
	{
		if (use == true)
			m_Flags |= USE_FIXED_BUFFER_F;
		else
			m_Flags &= ~USE_FIXED_BUFFER_F;
	}

	inline void UseChromaKey(bool use)
	{
		if (!use)
			m_Flags |= NO_CHROMA_KEY_F;
		else
			m_Flags &= ~NO_CHROMA_KEY_F;
	}

	static bool IsCompressedFormat(Format format)
	{
		return (((format >= PVRTC_2) && (format <= COMPRESSED)) || ((format >= DXT1) && (format <= ASTC))
			|| (format == ETC) || (format == DXT3));
	}

	void    SetBuffers(uint8* pTexels = NULL, uint32 texelLen = 0, uint8* pPalette = NULL, uint32 palSize = 0);
	void    ReadPalette(uint8* pPaletteSrc);
	void    ReadTexels(uint8* pTexelsSrc);
	int     CountColours();

	void    SaveBmp(const char* filename);
	void    SaveTga(const char* filename);
	void    SavePng(const char* filename);
	void    SaveJpg(const char* filename, uint32 quality = 100);

	void    MakeOwner(uint32 flags);

	// Sets this image to be equivalent to pImg. Ownership of any buffer owned by pImg will pass to this image.
	void    SetOwn(CIwImage* pImg);

	// Sets this image to be equivalent to pImg. Ownership of any buffers remains with pImg.
	void    SetNoOwn(CIwImage* pImg);

private:
	// Reads data from source with pitch (for palette: pitch == sizeof(pPalette))
	void    ReadData(uint32 pitch, uint8* pTexelsSrc, uint8* pPalette);

	// Updates this images info attributes. Assume for now that it will not be holding any data.
	void    UpdateInfo(CIwImage* pImg);

	// Sets the image flags.
	inline void SetFlags(uint16 flags) { m_Flags = flags; }

	// Frees the allocated data
	void    FreeData();

	// Internal functions for converting between different texel/palette types
	void    ConvertToPalettisedImage(CIwImage* pImage, bool useExistingPalette = false);
	void    do_neuquant(CIwImage* destImage);
	bool    ConvertToPalettisedImageSimple(CIwImage* pImage);
	void    ConvertDataToFormat(uint8* pSrcBuffer, uint8* pDstBuffer, CIwImage* pImage, uint32 height, uint32 width);
	void    ConvertIndexedDataToFormat(uint8* pPalette, uint8* pIndexData, uint8* pDstBuffer, CIwImage* pImage);
	void    ConvertPixelToFormat(uint8* pSrc, uint8* pDst, const FormatData* pSrcFormat, const FormatData* pDstFormat);
	void    DecodePixelRGBAFromFormat(uint8* pSrc, uint16* r, uint16* g, uint16* b, uint16* a, const FormatData* srcFormat) const;
	void    EncodePixelRGBAToFormat(uint8* pDst, uint16 r, uint16 g, uint16 b, uint16 a, const FormatData* srcFormat, const FormatData* dstFormat) const;
	int     ColourLookup(uint32 colour, uint8* pPalette, CIwImage* pImage, int32 paletteSize = -1) const;
	int     ColourLookupNearest(uint8* colour, uint8* pPalette, CIwImage* pImage);

	void    SetDefaultPitch();

	// Decode file formats to raw texels and palette
	void    DecodeGIF(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodeTGA(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodePNG(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodeRAW(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodeRP4(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodeJPG(void* pSrc, uint32 srcLen, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);

	//! Decode PVR compressed format
	void    DecodePVR(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);

	//! Decode PVR file container version 3
	void    DecodePVR3(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);
	void    DecodePVR3Compressed(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize); // internal function

																												 //! Decode ATI compressed format
	void    DecodeATI(void* pSrc, uint8* pTexels, uint32 texelsLen, uint8* pPalette, uint32 palSize);

	//! Create a power of 2 image from this
	uint8* IwImageMakePow2(uint32 *outWidth, uint32 *outHeight,
		uint32 minWidth = 1, uint32 minHeight = 1,
		uint32 maxWidth = (uint32)-1, uint32 maxHeight = (uint32)-1);

	//! Create a square power of 2 image from this
	uint8* IwImageMakePow2Square(uint32 *outWidth, uint32 *outHeight, uint32 minWidth = 1, uint32 minHeight = 1);

	inline uint32 MapColourToResolution(uint32 bitDepthIn, uint32 bitDepthOut, uint16 col) const
	{
		uint32 resIn = (1 << bitDepthIn) - 1;
		uint32 resOut = (1 << bitDepthOut) - 1;
		uint32 oldVal = (uint32)col;

		if (resIn == 0)
			return oldVal;

		return (resOut - (resOut*((resIn)-oldVal) / (resIn)));
	}

	inline uint32 ReformatColourComponent(uint32 bitDepthIn, uint32 bitDepthOut, uint16 col) const
	{
		uint32 mid = ((1 << bitDepthOut) - 1) >> 1;

		if (bitDepthOut<bitDepthIn)
		{
			// Round up when shifting down
			uint16 rounded_col = col | (0x1 << (bitDepthIn - bitDepthOut - 1));

			return rounded_col >> (bitDepthIn - bitDepthOut);
		}

		uint32 outCol = col << (bitDepthOut - bitDepthIn);

		// Only do lsb if the incoming value came from the source. If bitDepthIn is 0, something
		// else must have explicitly set this value (since the source didn't have any information here).
		if (bitDepthIn && outCol >= mid)
		{
			outCol |= (1 << (bitDepthOut - bitDepthIn)) - 1;
		}
		return outCol;
	}

	// Map an RGB888 colour value to either an RGB888 (reverse=false) or BGR888 (reverse=true) colour value
	inline void AssignRGB(uint8* pDst, uint8* pSrc, uint8 reverse)
	{
		pDst[0] = pSrc[reverse ? 2 : 0];
		pDst[1] = pSrc[1];
		pDst[2] = pSrc[reverse ? 0 : 2];
	}

	// Map an RGBA8888 colour value to either an RGBA8888 (reverse=false) or ABGR8888 (reverse=true) colour value
	inline void AssignRGBA(uint8* pDst, uint8* pSrc, uint8 reverse)
	{
		pDst[0] = pSrc[reverse ? 3 : 0];
		pDst[1] = pSrc[reverse ? 2 : 1];
		pDst[2] = pSrc[reverse ? 1 : 2];
		pDst[3] = pSrc[reverse ? 0 : 3];
	}

	// Map an ARGB8888 colour value to either an ABGR8888 (reverse=false) or RGBA8888 (reverse=true) colour value
	inline void AssignARGB(uint8* pDst, uint8* pSrc, uint8 reverse)
	{
		pDst[0] = pSrc[reverse ? 2 : 3];
		pDst[1] = pSrc[reverse ? 1 : 0];
		pDst[2] = pSrc[reverse ? 0 : 1];
		pDst[3] = pSrc[reverse ? 3 : 2];
	}

	uint32  ByteRead32(uint8* pSrc, int32 length) const;
	void ByteWrite32(uint32 val, uint8* pDst, int32 length) const;

	/* Replicate image across width;
	outXXX is for output image data;
	assumes outImage has enough space;
	Assumes source image is this image
	*/
	void    IwImageReplicateColumns(uint32 outWidth, uint8 *outImage);

	/* Replicate image rows;
	outXXX is for output image;
	assumes outImage has enough space;
	Assumes source image is already in outImage
	*/
	void    IwImageReplicateRows(uint32 outWidth, uint32 outHeight, uint8 *outImage);

	/*  Creates a new reduced palette and remaps into pImage
	NB: pImage is assumed to be setup with buffers already!
	NB NB: pImage must have 8bit texels!
	*/
	void    ReduceImagePalette8(CIwImage* pImage, bool chooseDepth);

	/*  Creates a new resized in pImage
	pImage must have a desired height and width specified
	Used as a helper to ConverToImage
	*/
	void    ResizeToImage(CIwImage* pImage);

	/*  Mip-mapping functions
	*/
	bool    CanMipMapImage() const;
	uint32  CalculateMipMapLevels() const;
	uint32  CalculateMipMapBufferSize(uint32 level) const;
	void    CalculateMipMapDimensions(uint32* width, uint32* height, uint32 level) const;
	bool    CreateMipMip(CIwImage* pImage, uint32 level, uint8* pTexels, uint32 texelLen, bool doChromaKeyTransparency) const;
	void	ReadAndAccumulateSample(uint16* pR, uint16* pG, uint16* pB, uint16* pA,
		uint8* pSrc, uint32 stepX, uint32 stepY, uint32 numX, uint32 numY,
		bool doChromaKeyTransparency) const;

protected:
	// Converts between existing buffers of different formats
	// Asserts if conversion is not available
	static void ConvertTexelsBetweenFormats(void* pSrcTexels, void* pDstTexels, Format srcFormat, Format dstFormat, uint32 width, uint32 height);
	static void ConvertPaletteBetweenFormats(void* pSrcPalette, void* pDstPalette, Format srcFormat, Format dstFormat);

private:
	uint16      m_Flags;        // flags
	Format      m_Format;       // texel/palette format type
	uint8       pad0;
	uint16      pad1;
	uint16      m_Width;        // width in texels
	uint16      m_Height;       // height in texels
	uint16      m_Pitch;        // pitch IN BYTES
	uint8*      m_Texels;       // ptr to texels
	uint8*      m_Palette;      // ptr to palette (or NULL for unpalettised formats)
	uint32      m_CompressedImageSize;      // size of the image when containing compressed data

	static const FormatData s_FormatData[];
	//static CIwMemBucket* s_FixedBucket;
	static uint8*       s_FixedBucketControlled;
	static uint32       s_FixedBufferSize;
	friend class CIwTexture;

	uint8* Alloc(uint32 size);

};
