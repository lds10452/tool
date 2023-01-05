#pragma once
#include <iostream>
#include "boost/property_tree/ptree.hpp"
#include "boost/format.hpp"
#include "boost/program_options/detail/utf8_codecvt_facet.hpp"
#include "boost/foreach.hpp"
using namespace std;

#ifdef _UNICODE
typedef boost::property_tree::wptree tptree;
typedef std::wstring tstring;
typedef std::wstringstream tstringstream;
typedef boost::wformat tformat;
#define tstrcmp wcscmp
#define _TEXT_CHAR	wchar_t
#define _TEXT_T(x)	L ## x
#define tcout	wcout
#define tcin    wcin
#else  
typedef boost::property_tree::ptree tptree;
typedef std::string tstring;
typedef std::stringstream tstringstream;
typedef boost::format tformat;
#define tstrcmp strcmp
#define _TEXT_CHAR	char
#define _TEXT_T(x)	x
#define tcout	cout
#endif