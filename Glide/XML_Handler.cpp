#include "XML_Handler.hpp"
#include <iostream>
#include "GlideException.hpp"
#include <stdexcept>

void  XML_Handler::GetIntAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, int* num)
	{
	CheckError(element->QueryIntAttribute(attributeName.c_str(), num));
	}

void XML_Handler::GetFloatAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, float* num)
	{
	CheckError(element->QueryFloatAttribute(attributeName.c_str(), num));
	}

void XML_Handler::GetDoubleAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, double* num)
	{
	CheckError(element->QueryDoubleAttribute(attributeName.c_str(), num));
	}

void XML_Handler::GetAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, const char* str)
	{
	//TODO: awesome code here
	}
void XML_Handler::GetUnsignedAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, const char* str)
	{
	 //TODO: awesome code here
	}

void XML_Handler::CheckError(const tinyxml2::XMLError error)
	{
	switch (error)
		{
		case (tinyxml2::XMLError::XML_NO_ERROR) :
			{
			//success
			// do nothing
			return;
			}
		case (tinyxml2::XMLError::XML_ERROR_EMPTY_DOCUMENT) :
			{
			throw gl::GlideException("error empty document", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_ELEMENT_MISMATCH) :
			{
			throw gl::GlideException("error element missmatch", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED) :
			{
			throw gl::GlideException("Error file could not be opened", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND) :
			{
			throw gl::GlideException("Error file not found", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR) :
			{
			throw gl::GlideException("Error file read error", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_IDENTIFYING_TAG) :
			{
			throw gl::GlideException("error identifying tag", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_MISMATCHED_ELEMENT) :
			{	
			throw gl::GlideException("error mismatched element", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING) :
			{
			throw gl::GlideException("error parsing", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_ATTRIBUTE) :
			{
			throw gl::GlideException("error parsing attribute", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_CDATA) :
			{
			throw gl::GlideException("error parsing cData", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_COMMENT) :
			{
			throw gl::GlideException("error parsing comment", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_DECLARATION) :
			{
			throw gl::GlideException("error parsing decleration", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_ELEMENT) :
			{
			throw gl::GlideException("error parsing element", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_TEXT) :
			{
			throw gl::GlideException("error parsing text", error);
			break;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_UNKNOWN) :
			{
			throw gl::GlideException("error parsing unknown", error);
			break;
			}
		case (tinyxml2::XMLError::XML_NO_ATTRIBUTE) :
			{
			throw gl::GlideException("error no attribute", error);
			break;
			}
		case (tinyxml2::XMLError::XML_NO_TEXT_NODE) :
			{
			throw gl::GlideException("error no text node", error);
			break;
			}
		case (tinyxml2::XMLError::XML_WRONG_ATTRIBUTE_TYPE) :
			{
			throw gl::GlideException("error wrong attribute type", error);
			break;
			}
		default:
			{
			throw gl::GlideException("unknown error", error);
			break;
			}
		}
	}