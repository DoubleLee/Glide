#pragma once
#ifndef XML_HANDLER_H
#define XML_HANDLER_H
#include<string>
#include "tinyxml2.hpp"


namespace XML_Handler
	{
	void getIntAttribute(tinyxml2::XMLElement* element, std::string attributeName, int* num);
	void getFloatAttribute(tinyxml2::XMLElement* element, std::string attributeName, float* num);
	void getDoubleAttribute(tinyxml2::XMLElement* element, std::string attributeName, double* num);
	void getAttribute(tinyxml2::XMLElement* element, std::string attributeName, const char* str);
	void getUnsignedAttribute(tinyxml2::XMLElement* element, std::string attributeName, const char* str);
	bool isNoError(tinyxml2::XMLError&& error);
	}
	
	
#endif //XML_HANDLER_H
