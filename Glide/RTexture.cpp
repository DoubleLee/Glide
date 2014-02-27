#include "RTexture.hpp"

#include "GlideException.hpp"

using namespace std;

namespace gl
{

void ErrorCallbackPNG(png_structp png_ptr, png_const_charp error_msg)
	{
	std::string error = error_msg;
	throw GlideException("Libpng threw the error below:\n" + error);
	}

void ReadDataCallbackPNG(png_structp pngReadPtr, png_bytep data, png_size_t length)
	{
	png_voidp a = png_get_io_ptr(pngReadPtr);
	((std::istream*)a)->read((char*) data, length);
	}


RTexture::RTexture(const Resource::Configuration & config)
	:
	Resource(config)
	{
	// open file stream
	std::ifstream ifs;
	ifs.open(mFile.c_str(), std::ios_base::in | std::ios_base::binary);

	// check it was found an able to be opened
	if(!ifs.is_open())
		{
		throw GlideException("Failed to find Texture file, " + mFile);
		}

	// setup png signature check, first 8 bytes
	// should be same for every png
	static const int pngSigSize = 8;
	png_byte pngSigByteArray[pngSigSize];
	int is_png = 0;

	// read in the bytes
	ifs.read((char*) pngSigByteArray, pngSigSize);

	// make sure it read correctly
	if(!ifs.good())
		throw GlideException("Unable to read signature, may not be a png file, " + mFile);

	// let libpng check the sig for us
	is_png = png_sig_cmp(pngSigByteArray, 0, pngSigSize);
	if(is_png != 0)
		{
		throw GlideException("Signature check failed, this is not a png file, " + mFile);
		}

	// create read pointer
	png_structp pPngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, ErrorCallbackPNG, NULL);

	if(!pPngReadStruct)
		{
		throw GlideException("libpng couldn't make a read struct, libpng error.");
		}

	std::unique_ptr< png_struct, void(*)(png_struct*) > cleanReadStruct
		(
		pPngReadStruct,
		[](png_struct * pReadStruct) { png_destroy_read_struct(&pReadStruct, nullptr, nullptr); }
	);

	// create info pointer ( this is pointer to the information about the png file
	png_infop pPngInfoStruct = png_create_info_struct(pPngReadStruct);

	std::unique_ptr< std::pair<png_struct*, png_info*>, void(*)(std::pair<png_struct*, png_info*>*) > cleanInfoStruct
		(
		new std::pair<png_struct*, png_info*>(pPngReadStruct, pPngInfoStruct),
		[](std::pair<png_struct*, png_info*> * pPair) { png_destroy_info_struct(pPair->first, &pPair->second); delete pPair; }
	);

	if(!pPngInfoStruct)
		{
		throw GlideException("libpng couldn't make a info struct, libpng error.");
		}

	// setup the read function callback
	png_set_read_fn(pPngReadStruct, (png_voidp) &ifs, ReadDataCallbackPNG);

	// tell libpng we already read in the signature
	png_set_sig_bytes(pPngReadStruct, pngSigSize);

	png_read_info(pPngReadStruct, pPngInfoStruct);

	// get width and height from png file
	png_uint_32 imageWidth = png_get_image_width(pPngReadStruct, pPngInfoStruct);
	png_uint_32 imageHeight = png_get_image_height(pPngReadStruct, pPngInfoStruct);

	// bits per channel, not bits per pixel
	png_uint_32 bitDepth = png_get_bit_depth(pPngReadStruct, pPngInfoStruct);
	// number of channels
	png_uint_32 channels = png_get_channels(pPngReadStruct, pPngInfoStruct);

	// color type. ( RGB, RGBA, Luminance, luminance alpha... palette.. ect
	png_uint_32 color_type = png_get_color_type(pPngReadStruct, pPngInfoStruct);

	switch( color_type )
		{
		case PNG_COLOR_TYPE_RGB:
			{
			mColorType = GL_RGB;
			break;
			}
		case PNG_COLOR_TYPE_RGBA:
			{
			mColorType = GL_RGBA;
			break;
			}
		default:
			{
			throw GlideException("Png color format is not supported, " + mFile);
			}
		}

	/*if the image has a transperancy set.. convert it to a full Alpha channel..*/
	if(png_get_valid(pPngReadStruct, pPngInfoStruct, PNG_INFO_tRNS))
		{
		png_set_tRNS_to_alpha(pPngReadStruct);
		channels += 1;
		color_type = png_get_color_type(pPngReadStruct, pPngInfoStruct);
		}

	

	// check to make sure bitDepth isn't 16, if it is, will ask png to
	// change it back to 8
	if(bitDepth == 16)
		{
		png_set_strip_16(pPngReadStruct);
		bitDepth = png_get_bit_depth(pPngReadStruct, pPngInfoStruct);
		}

	// rows of pointers
	std::unique_ptr<png_bytep[]> rowPtrs(new png_bytep[imageHeight]);

	// all the data goes here
	std::unique_ptr<char[]> data(new char[imageWidth * imageHeight * bitDepth * channels / 8]);

	// length of bytes in one row
	const unsigned int stride = imageWidth * bitDepth * channels / 8;

	for(png_uint_32 i = 0; i < imageHeight; ++i)
		{
		// reverse allows to load from bottom to top like opengl needs
		png_uint_32 reverse = (imageHeight - i - 1) * stride;
		rowPtrs.get()[i] = (png_bytep) data.get() + reverse;
		}

	// this function reads the data
	// it will use our custom read function
	png_read_image(pPngReadStruct, rowPtrs.get());

	// IF WE GOT HERE LIBPNG LOADING WAS SUCCESSFULL
	// Now we load into openGL

	// TODO: link in openGL texture loading functions
	// WARNING: possible leak here when GLCHECKERROR throws below the bind
	// since the dtor isn't called if the ctor throws, the id will not be freed
	GLCHECKERROR(glGenTextures(1, &mTextureID))
	GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, mTextureID))

	GLCHECKERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, mColorType, GL_UNSIGNED_BYTE, data.get()))

	// anisotripic filtering
	//GLfloat maxFilter = 0.0f;
	//GLCHECKERROR( glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxFilter) )
	//GLCHECKERROR( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxFilter) )

	// Linear filtering
	GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
	GLCHECKERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))

	GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, 0))
	}

RTexture::RTexture(RTexture && other)
	:
	Resource(std::move(other)),
	mTextureID(other.mTextureID),
	mColorType(other.mColorType)
	{
	other.mTextureID = 0;
	other.mColorType = 0;
	}


RTexture::~RTexture()
	{
	GLCHECKERRORWARNING(glBindTexture(GL_TEXTURE_2D, 0))
	if(mTextureID)
		{
		GLCHECKERRORWARNING(glDeleteTextures(1, &mTextureID))
		mTextureID = 0;
		}
	}

GLuint RTexture::GetTextureID() const
	{
	return mTextureID;
	}

Void RTexture::Bind() const
	{
	GLCHECKERROR(glBindTexture(GL_TEXTURE_2D, mTextureID))
	}

Void RTexture::BindNull()
	{
	GLCHECKERRORWARNING(glBindTexture(GL_TEXTURE_2D, 0))
	}
}