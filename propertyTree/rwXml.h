#pragma once
#include "public.h"
#include "boost/property_tree/xml_parser.hpp"

class rwXml
{
public:
	bool LoadOrSaveFile(const tstring& path, tptree& tp, bool isSave);
	void ReadXml(const tstring& path);
	void WriteXml(const tstring& path);
};

