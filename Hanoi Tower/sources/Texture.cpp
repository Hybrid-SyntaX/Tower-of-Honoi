#include "Texture.h"


_Texture::_Texture(void)
{
}


_Texture::~_Texture(void)
{
}

GLbyte * _Texture::LoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
    FILE *pFile=NULL;			// File pointer
    TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte	*pBits = NULL;          // Pointer to bits
    
    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;
    
    // Attempt to open the fil
	fopen_s(&pFile,szFileName,"rb");
    if(pFile == NULL)
        return NULL;
	
    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
    
    // Do byte swap for big vs little endian
#ifdef __APPLE__
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif
	
	
    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;
    
    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;
	
    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    
    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;
    
    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        delete pBits;
        return NULL;
		}
    
    // Set OpenGL format expected
    switch(sDepth)
		{
        case 3:     // Most likely case
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB;
            break;
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA8;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE8;
            break;
		};
	
    
    // Done with File
    fclose(pFile);
	
    // Return pointer to image data
    return pBits;
}
void _Texture::BindTexture(const char * fileName)
{
			GLbyte *pBytes;
			GLint iWidth, iHeight, iComponents;
			GLenum eFormat;
			pBytes = LoadTGA(fileName, &iWidth, &iHeight, &iComponents, &eFormat);


			glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
			free(pBytes);
   
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glEnable(GL_TEXTURE_2D);
	
}