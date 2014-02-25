#include "XML_Handler.hpp"
#include <iostream>
#include "GlideException.hpp"
#include <stdexcept>

void  XML_Handler::getIntAttribute(tinyxml2::XMLElement* element, std::string attributeName, int* num)
	{
	isNoError(element->QueryIntAttribute(attributeName.c_str(), num));
	}

void XML_Handler::getFloatAttribute(tinyxml2::XMLElement* element, std::string attributeName, float* num)
	{
	isNoError(element->QueryFloatAttribute(attributeName.c_str(), num));
	}

void XML_Handler::getDoubleAttribute(tinyxml2::XMLElement* element, std::string attributeName, double* num)
	{
	isNoError(element->QueryDoubleAttribute(attributeName.c_str(), num));
	}

void XML_Handler::getAttribute(tinyxml2::XMLElement* element, std::string attributeName, const char* str)
	{
	//TODO: awesome code here
	}
void XML_Handler::getUnsignedAttribute(tinyxml2::XMLElement* element, std::string attributeName, const char* str)
	{
	 //TODO: awesome code here
	}

bool XML_Handler::isNoError(tinyxml2::XMLError&& error)
	{
	switch (error)
		{
		case (tinyxml2::XMLError::XML_NO_ERROR) :
			{
			//success
			return true;
			}
		case (tinyxml2::XMLError::XML_ERROR_EMPTY_DOCUMENT) :
			{
			throw gl::GlideException("error empty document");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_ELEMENT_MISMATCH) :
			{
			
			throw gl::GlideException("error element missmatch\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED) :
			{
			
			throw gl::GlideException("Error file could not be opened\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND) :
			{
			throw gl::GlideException("Error file not found\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR) :
			{
			throw gl::GlideException("Error file read error\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_IDENTIFYING_TAG) :
			{
			throw gl::GlideException("error identifying tag\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_MISMATCHED_ELEMENT) :
			{	
			throw gl::GlideException("error mismatched element\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING) :
			{
			throw gl::GlideException("error parsing\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_ATTRIBUTE) :
			{
			throw gl::GlideException("error parsing attribute\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_CDATA) :
			{
			throw gl::GlideException("error parsing cData\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_COMMENT) :
			{
			throw gl::GlideException("error parsing comment\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_DECLARATION) :
			{
			throw gl::GlideException("error parsing decleration\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_ELEMENT) :
			{
			throw gl::GlideException("error parsing element\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_TEXT) :
			{
			throw gl::GlideException("error parsing text\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_ERROR_PARSING_UNKNOWN) :
			{
			throw gl::GlideException("error parsing unknown\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_NO_ATTRIBUTE) :
			{
			throw gl::GlideException("error no attribute\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_NO_TEXT_NODE) :
			{
			throw gl::GlideException("error no text node\n");
			return false;
			}
		case (tinyxml2::XMLError::XML_WRONG_ATTRIBUTE_TYPE) :
			{
			throw gl::GlideException("error wrong attribute type\n");
			return false;
			}
		default:
			{
			throw gl::GlideException("unknown error\n");
			return false; 
			}
		}
	}