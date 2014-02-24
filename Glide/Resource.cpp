#include "Resource.hpp"

using namespace std;
namespace gl
{
std::string StripPath(const std::string & fileNamePath)
	{
	char windowsStylePath = '\\';
	char linuxStylePath = '/';

	string::size_type winLastSlash = fileNamePath.find_last_of(windowsStylePath);
	string::size_type linLastSlash = fileNamePath.find_last_of(linuxStylePath);

	string::size_type indexLastSlash;

	if ( winLastSlash != string::npos )
		{
		indexLastSlash = winLastSlash;
		}
	else if ( linLastSlash != string::npos )
		{
		indexLastSlash = linLastSlash;
		}
	else
		{
		return fileNamePath;
		}

	
	++indexLastSlash; // move past '\'
	if(indexLastSlash < fileNamePath.size())
		{
		return fileNamePath.substr(indexLastSlash);
		}
	else
		{
		return fileNamePath.substr(--indexLastSlash);
		}

	}

}