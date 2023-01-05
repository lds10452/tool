#include "rwXml.h"
bool rwXml::LoadOrSaveFile(const tstring& path,tptree& tp, bool isSave)
{
#ifdef _UNICODE
	std::locale current_locale(locale(""), new boost::program_options::detail::utf8_codecvt_facet());
	wchar_t c = L'\t';
	boost::property_tree::xml_parser::xml_writer_settings<wstring> settings(c, 1);
#else
    std::locale current_locale;
    boost::property_tree::xml_parser::xml_writer_settings<string> settings('\t', 1, "utf-8");
#endif
	if (isSave)
	{
		std::basic_ofstream<tptree::key_type::value_type>
			stream(path);
		if (!stream)
			return false;
		stream.imbue(current_locale);
		write_xml(stream, tp, settings);
	}
	else
	{
		std::basic_ifstream<tptree::key_type::value_type>
			stream(path);
		if (!stream)
			return false;
		stream.imbue(current_locale);
		read_xml(stream, tp, 0);
	}
	return true;
}
void rwXml::ReadXml(const tstring& path)
{
	tptree tp, tp1, tp2, tp3;
	LoadOrSaveFile(path, tp, false);
	if (tp.get_child_optional(_TEXT_T("xiaozhang")))
	{
		tp1 = tp.get_child(_TEXT_T("xiaozhang"));
	}
	tptree::assoc_iterator iter = tp1.find(_TEXT_T("laoshi"));
	if (iter != tp1.not_found())
	{
		tp2 = iter->second;
		unsigned int a = tp2.get<unsigned int>(_TEXT_T("<xmlattr>.age"), 0);
		cout <<"age"<< a << endl;
		BOOST_FOREACH(const tptree::value_type & vt, tp2)
		{
			cout << "1111111111111" << endl;
			if (vt.first == _TEXT_T("<xmlcomment>"))
			{
				continue;
			}
			else if (vt.first == _TEXT_T("<xmlattr>"))
			{
				a=vt.second.get<unsigned int>(_TEXT_T("age"), 0);
				cout << a << endl;
				int b = vt.second.get<unsigned int>(_TEXT_T("xxx"), 0);
				cout << b << endl;
			}
			else if (vt.first == _TEXT_T("xuesheng"))
			{
				tstring name = vt.second.get<tstring>(_TEXT_T("name"), _TEXT_T(""));
				tcout << name << endl;
				unsigned int age = vt.second.get<unsigned int>(_TEXT_T("age"), 0);
				cout << age << endl;
				BOOST_FOREACH(const tptree::value_type & vt1, vt.second)
				{
					if (vt1.first == _TEXT_T("<xmlcomment>"))
					{
						continue;
					}
					else if (vt1.first == _TEXT_T("<xmlattr>"))
					{
						unsigned int w = vt1.second.get<unsigned int>(_TEXT_T("weight"), 0);
						cout << w << endl;
					}
				}
			}
		}
	}
}
void rwXml::WriteXml(const tstring& path)
{
	tptree tp, tp1, tp2, tp3;
	auto& a1 = tp2.add_child(_TEXT_T("xuesheng"), tp3);//加子节点
	a1.put(_TEXT_T("<xmlattr>.height"), 14);//加属性
	auto& a2 = tp1.add_child(_TEXT_T("laoshi"), tp2);
	a2.put(_TEXT_T("<xmlattr>.age"), 10);
	a2.put(_TEXT_T("<xmlattr>.xxx"), 11);
	auto& a3 = tp.add_child(_TEXT_T("xiaozhang"), tp1);
	a3.put(_TEXT_T("<xmlattr>.name"), _TEXT_T("xxx"));
	a3.put(_TEXT_T("<xmlattr>.weight"), 40);

	tptree tp4, tp5;
	tp4.add<tstring>(_TEXT_T("name"), _TEXT_T("lisan"));//加属性节点
	tp4.add<unsigned int>(_TEXT_T("age"), 20);
	tp4.put(_TEXT_T("<xmlattr>.weight"), 40);
	tp5.add<tstring>(_TEXT_T("name"), _TEXT_T("lisi"));
	tp5.add<unsigned int>(_TEXT_T("age"), 10);
	tp5.put(_TEXT_T("<xmlattr>.weight"), 30);
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xuesheng"), tp4);//加子节点
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xuesheng"), tp5);

	LoadOrSaveFile(path, tp, true);
	//put按路径添加，会覆盖原来的属性或者节点
	//add按顺序添加
	//遍历子节点，注释、属性、子节点分别只遍历一次（一次性属性遍历完）
}