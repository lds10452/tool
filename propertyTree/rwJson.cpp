#include "rwJson.h"

bool rwJson::LoadOrSaveFile(const tstring& path, tptree& tp, bool isSave)
{
#ifdef _UNICODE
	std::locale current_locale(locale(""), new boost::program_options::detail::utf8_codecvt_facet());
#else
	std::locale current_locale;
#endif
	if (isSave)
	{
		std::basic_ofstream<tptree::key_type::value_type>
			stream(path);
		if (!stream)
			return false;
		stream.imbue(current_locale);
		write_json(stream, tp);          
	}
	else
	{
		std::basic_ifstream<tptree::key_type::value_type>
			stream(path);
		if (!stream)
			return false;
		stream.imbue(current_locale);
		read_json(stream, tp);          
	}
	return true;
}
void rwJson::ReadJson(const tstring& path)
{
	tptree tp, tp1, tp2, tp3;
	LoadOrSaveFile(path, tp, false);
	tp1 = tp.get_child(_TEXT_T("root"));
	//获取子节点
	tp2 = tp1.get_child(_TEXT_T("xuexiao"));
	//键值对获取值
	tstring m = tp2.get<tstring>(_TEXT_T("mianji"), _TEXT_T(""));
	tcout << m << endl;
	tp3 = tp2.get_child(_TEXT_T("library"));
	//解析数组
	for(tptree::iterator iter=tp3.begin();iter!=tp3.end();iter++)
	{
		tstring name = iter->second.get<tstring>(_TEXT_T("name"), _TEXT_T(""));
		int price = iter->second.get<int>(_TEXT_T("price"), 0);
		tcout << name << " " << price << endl;
	}
}
void rwJson::WriteJson(const tstring& path)
{
	tptree tp, tp1, tp2, tp3, tp4;
	tp4.put(_TEXT_T("name"), _TEXT_T("english"));//创建键值对
	tp4.put(_TEXT_T("price"), 10);
	tp3.push_back(make_pair(_TEXT_T(""), tp4));//将对象放入数组中
	tp4.put(_TEXT_T("name"), _TEXT_T("chinese"));
	tp4.put(_TEXT_T("price"), 20);
	tp3.push_back(make_pair(_TEXT_T(""), tp4));
	tp2.add(_TEXT_T("mianji"),3000);
	tp2.add_child(_TEXT_T("library"), tp3);//将数组放入节点
	tp1.add_child(_TEXT_T("xuexiao"), tp2);
	tp.add_child(_TEXT_T("root"), tp1);
	LoadOrSaveFile(path, tp, true);
	// {}表示一个对象，可以包含多个键值对
	// []表示一个数组，可以包含多个对象
}