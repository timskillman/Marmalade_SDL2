#include "IwImage.h"

CIwImage::CIwImage()
{
}

CIwImage::~CIwImage()
{
}

CIwImage::CIwImage(const CIwImage & img)
{
}

void CIwImage::operator=(CIwImage const & pImg)
{
}

void CIwImage::Serialise()
{
}

void CIwImage::SerialisePaletteOnly()
{
}

uint32_t CIwImage::GetBitDepth(const Format & format)
{
	return uint32_t();
}

uint32_t CIwImage::GetTexelBitDepth(const Format & format)
{
	return uint32_t();
}

uint32_t CIwImage::GetPaletteSize(const Format & format)
{
	return uint32_t();
}

uint32 CIwImage::GetPaletteMemSize(const Format & format)
{
	return uint32();
}

void CIwImage::SetFormat(Format format)
{
}

void CIwImage::SetWidth(uint32 width)
{
}

void CIwImage::SetHeight(uint32 height)
{
}

void CIwImage::SetPitch(uint32 pitch)
{
}

uint32 CIwImage::FormatColour(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	return uint32();
}

void CIwImage::ColourForFormat(uint32 value, uint16 * red, uint16 * green, uint16 * blue, uint16 * alpha)
{
}

void CIwImage::SetOwnedBuffers(uint8 * pTexels, uint8 * pPalette)
{
}

bool CIwImage::UsesAlpha(uint8 threshold) const
{
	return false;
}

bool CIwImage::UsesChromakey() const
{
	return false;
}

bool CIwImage::TestForChromakey() const
{
	return false;
}

void CIwImage::LoadFromFile(const char * imageFile)
{
}

void CIwImage::ConvertToImage(CIwImage * pImage, bool chooseDepth)
{
}

void CIwImage::ConvertToImage(CIwImage * pImage, uint8 * pTexels, uint32 texelsSize, uint8 * pPalette, uint32 palSize, bool chooseDepth)
{
}

void CIwImage::ReplacePalette(uint8 * pPalette)
{
}

uint32 CIwImage::ReplaceColour(uint8 srcR, uint8 srcG, uint8 srcB, uint8 srcA, uint8 dstR, uint8 dstG, uint8 dstB, uint8 dstA)
{
	return uint32();
}

uint32 CIwImage::ReplaceAlpha(uint8 threshold, uint8 chromaR, uint8 chromaG, uint8 chromaB)
{
	return uint32();
}

uint32 CIwImage::ReplaceAlphaColourWithSurrounding(uint8 threshold, uint8 numSurrounding)
{
	return uint32();
}

uint32 CIwImage::MakeAlphaPalZero(uint8 threshold, uint8 keyR, uint8 keyG, uint8 keyB)
{
	return uint32();
}

void CIwImage::FixedBufferSetSize(uint32 size)
{
}

void CIwImage::FixedBufferFree()
{
}

void CIwImage::FixedBufferCheckOverflow()
{
}

void CIwImage::SetBuffers(uint8 * pTexels, uint32 texelLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::ReadPalette(uint8 * pPaletteSrc)
{
}

void CIwImage::ReadTexels(uint8 * pTexelsSrc)
{
}

int CIwImage::CountColours()
{
	return 0;
}

void CIwImage::SaveBmp(const char * filename)
{
}

void CIwImage::SaveTga(const char * filename)
{
}

void CIwImage::SavePng(const char * filename)
{
}

void CIwImage::SaveJpg(const char * filename, uint32 quality)
{
}

void CIwImage::MakeOwner(uint32 flags)
{
}

void CIwImage::SetOwn(CIwImage * pImg)
{
}

void CIwImage::SetNoOwn(CIwImage * pImg)
{
}

void CIwImage::ReadData(uint32 pitch, uint8 * pTexelsSrc, uint8 * pPalette)
{
}

void CIwImage::UpdateInfo(CIwImage * pImg)
{
}

void CIwImage::FreeData()
{
}

void CIwImage::ConvertToPalettisedImage(CIwImage * pImage, bool useExistingPalette)
{
}

void CIwImage::do_neuquant(CIwImage * destImage)
{
}

bool CIwImage::ConvertToPalettisedImageSimple(CIwImage * pImage)
{
	return false;
}

void CIwImage::ConvertDataToFormat(uint8 * pSrcBuffer, uint8 * pDstBuffer, CIwImage * pImage, uint32 height, uint32 width)
{
}

void CIwImage::ConvertIndexedDataToFormat(uint8 * pPalette, uint8 * pIndexData, uint8 * pDstBuffer, CIwImage * pImage)
{
}

void CIwImage::ConvertPixelToFormat(uint8 * pSrc, uint8 * pDst, const FormatData * pSrcFormat, const FormatData * pDstFormat)
{
}

void CIwImage::DecodePixelRGBAFromFormat(uint8 * pSrc, uint16 * r, uint16 * g, uint16 * b, uint16 * a, const FormatData * srcFormat) const
{
}

void CIwImage::EncodePixelRGBAToFormat(uint8 * pDst, uint16 r, uint16 g, uint16 b, uint16 a, const FormatData * srcFormat, const FormatData * dstFormat) const
{
}

int CIwImage::ColourLookup(uint32 colour, uint8 * pPalette, CIwImage * pImage, int32 paletteSize) const
{
	return 0;
}

int CIwImage::ColourLookupNearest(uint8 * colour, uint8 * pPalette, CIwImage * pImage)
{
	return 0;
}

void CIwImage::SetDefaultPitch()
{
}

void CIwImage::DecodeGIF(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodeTGA(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodePNG(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodeRAW(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodeRP4(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodeJPG(void * pSrc, uint32 srcLen, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodePVR(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodePVR3(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodePVR3Compressed(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

void CIwImage::DecodeATI(void * pSrc, uint8 * pTexels, uint32 texelsLen, uint8 * pPalette, uint32 palSize)
{
}

uint8 * CIwImage::IwImageMakePow2(uint32 * outWidth, uint32 * outHeight, uint32 minWidth, uint32 minHeight, uint32 maxWidth, uint32 maxHeight)
{
	return nullptr;
}

uint8 * CIwImage::IwImageMakePow2Square(uint32 * outWidth, uint32 * outHeight, uint32 minWidth, uint32 minHeight)
{
	return nullptr;
}

uint32 CIwImage::ByteRead32(uint8 * pSrc, int32 length) const
{
	return uint32();
}

void CIwImage::ByteWrite32(uint32 val, uint8 * pDst, int32 length) const
{
}

void CIwImage::IwImageReplicateColumns(uint32 outWidth, uint8 * outImage)
{
}

void CIwImage::IwImageReplicateRows(uint32 outWidth, uint32 outHeight, uint8 * outImage)
{
}

void CIwImage::ReduceImagePalette8(CIwImage * pImage, bool chooseDepth)
{
}

void CIwImage::ResizeToImage(CIwImage * pImage)
{
}

bool CIwImage::CanMipMapImage() const
{
	return false;
}

uint32 CIwImage::CalculateMipMapLevels() const
{
	return uint32();
}

uint32 CIwImage::CalculateMipMapBufferSize(uint32 level) const
{
	return uint32();
}

void CIwImage::CalculateMipMapDimensions(uint32 * width, uint32 * height, uint32 level) const
{
}

bool CIwImage::CreateMipMip(CIwImage * pImage, uint32 level, uint8 * pTexels, uint32 texelLen, bool doChromaKeyTransparency) const
{
	return false;
}

void CIwImage::ReadAndAccumulateSample(uint16 * pR, uint16 * pG, uint16 * pB, uint16 * pA, uint8 * pSrc, uint32 stepX, uint32 stepY, uint32 numX, uint32 numY, bool doChromaKeyTransparency) const
{
}

void CIwImage::ConvertTexelsBetweenFormats(void * pSrcTexels, void * pDstTexels, Format srcFormat, Format dstFormat, uint32 width, uint32 height)
{
}

void CIwImage::ConvertPaletteBetweenFormats(void * pSrcPalette, void * pDstPalette, Format srcFormat, Format dstFormat)
{
}

uint8 * CIwImage::Alloc(uint32 size)
{
	return nullptr;
}
