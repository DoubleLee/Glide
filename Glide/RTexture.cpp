#include "RTexture.hpp"


using namespace std;

namespace gl
{

void ErrorCallbackPNG(png_structp png_ptr, png_const_charp error_msg)
	{
	std::string error = error_msg;
	throw std::runtime_error("Libpng threw the error below:\n" + error);
	}

void ReadDataCallbackPNG(png_structp pngReadPtr, png_bytep data, png_size_t length)
	{
	png_voidp a = png_get_io_ptr(pngReadPtr);
	((std::istream*)a)->read((char*) data, length);
	}

}