#pragma once
#ifndef XML_HANDLER_H
#define XML_HANDLER_H
#include<string>
#include "tinyxml2.hpp"


namespace XML_Handler
	{
	void GetIntAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, int* num);
	void GetFloatAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, float* num);
	void GetDoubleAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, double* num);
	void GetAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, const char* str);
	void GetUnsignedAttribute(tinyxml2::XMLElement* element, const std::string & attributeName, const char* str);
	void CheckError(const tinyxml2::XMLError error);
	}
	
	
#endif //XML_HANDLER_H
