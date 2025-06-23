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
		tp1 = tp.get_child(_TEXT_T("xiaozhang"));//子节点包含属性、节点和注释3个含义
		tstring name = tp1.get<tstring>(_TEXT_T("<xmlattr>.name"), _TEXT_T(""));//获取根节点属性值
		int weight = tp1.get<int>(_TEXT_T("<xmlattr>.weight"), 0);
		tstring comment= tp1.get<tstring>(_TEXT_T("<xmlcomment>"), _TEXT_T(""));  //获取注释信息
		tcout << name << " " << weight << "" << comment << endl;
	}
	tptree::assoc_iterator iter = tp1.find(_TEXT_T("laoshi"));//查找是否包含该节点名的子节点
	if (iter != tp1.not_found())
	{
		tcout << iter->first << endl;// 获取子节点名
		tp2 = iter->second;//获取子节点
		unsigned int a = tp2.get<unsigned int>(_TEXT_T("<xmlattr>.age"), 0);//获取属性值方式一
		cout <<"age"<< a << endl;
		BOOST_FOREACH(const tptree::value_type & vt, tp2)
		{
			cout << "1111111111111" << endl;
			if (vt.first == _TEXT_T("<xmlcomment>"))//子节点的注释
			{
				tstring comment = tp1.get<tstring>(_TEXT_T("<xmlcomment>"), _TEXT_T(""));  
				tcout << comment << endl;
			}
			else if (vt.first == _TEXT_T("<xmlattr>"))//子节点的属性
			{
				a=vt.second.get<unsigned int>(_TEXT_T("age"), 0);//获取属性值方式二
				cout << a << endl;
				int b = vt.second.get<unsigned int>(_TEXT_T("xxx"), 0);
				cout << b << endl;
			}
			else if (vt.first == _TEXT_T("xuesheng"))//子节点的节点
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
	//方式一，一次添加一个子节点，如下添加三次
	tptree tp, tp1, tp2, tp3;
	auto& a1 = tp2.add_child(_TEXT_T("xuesheng"), tp3);//返回节点名为xuesheng的a1就是tp3，加子节点tp3到tp2下
	a1.put(_TEXT_T("<xmlattr>.height"), 14);//tp3加属性

	auto& a2 = tp1.add_child(_TEXT_T("laoshi"), tp2);
	a2.put(_TEXT_T("<xmlattr>.age"), 10);
	a2.put(_TEXT_T("<xmlattr>.xxx"), 11);

	auto& a3 = tp.add_child(_TEXT_T("xiaozhang"), tp1);//根节点tp加子节点tp1
	a3.put(_TEXT_T("<xmlattr>.name"), _TEXT_T("xxx"));
	a3.put(_TEXT_T("<xmlattr>.weight"), 40);
	tptree commentNode;
	commentNode.put_value(" This is a comment inside root ");
	a3.add_child(_TEXT_T("<xmlcomment>"), commentNode);

	//方式二，一次添加三个子节点，使用put_child会覆盖之前相同节点名的节点，add按顺序添加
	tptree tp4, tp5;
	tp4.add<tstring>(_TEXT_T("name"), _TEXT_T("lisan"));//创建tp4的子节点
	tp4.add<unsigned int>(_TEXT_T("age"), 20);
	tp4.put(_TEXT_T("<xmlattr>.weight"), 40);//添加tp4的属性
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xuesheng"), tp4);//加子节点tp4（节点名为xuesheng）到根节点tp，之前名为xuesheng的节点被覆盖
	//put_child添加不同节点名的节点，不会覆盖之前的
	tp5.add<tstring>(_TEXT_T("name"), _TEXT_T("lisi"));
	tp5.add<unsigned int>(_TEXT_T("age"), 10);
	tp5.put(_TEXT_T("<xmlattr>.weight"), 30);
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xxx"), tp5);

	LoadOrSaveFile(path, tp, true);
	//遍历子节点，注释、属性、子节点分别只遍历一次（一次性属性遍历完）
}