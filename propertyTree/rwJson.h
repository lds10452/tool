#pragma once
#include "public.h"
#include "boost/property_tree/json_parser.hpp"
class rwJson
{
public:
	bool LoadOrSaveFile(const tstring& path, tptree& tp, bool isSave);
	void ReadJson(const tstring& path);
	void WriteJson(const tstring& path);
};

