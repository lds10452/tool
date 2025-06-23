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
		tp1 = tp.get_child(_TEXT_T("xiaozhang"));//�ӽڵ�������ԡ��ڵ��ע��3������
		tstring name = tp1.get<tstring>(_TEXT_T("<xmlattr>.name"), _TEXT_T(""));//��ȡ���ڵ�����ֵ
		int weight = tp1.get<int>(_TEXT_T("<xmlattr>.weight"), 0);
		tstring comment= tp1.get<tstring>(_TEXT_T("<xmlcomment>"), _TEXT_T(""));  //��ȡע����Ϣ
		tcout << name << " " << weight << "" << comment << endl;
	}
	tptree::assoc_iterator iter = tp1.find(_TEXT_T("laoshi"));//�����Ƿ�����ýڵ������ӽڵ�
	if (iter != tp1.not_found())
	{
		tcout << iter->first << endl;// ��ȡ�ӽڵ���
		tp2 = iter->second;//��ȡ�ӽڵ�
		unsigned int a = tp2.get<unsigned int>(_TEXT_T("<xmlattr>.age"), 0);//��ȡ����ֵ��ʽһ
		cout <<"age"<< a << endl;
		BOOST_FOREACH(const tptree::value_type & vt, tp2)
		{
			cout << "1111111111111" << endl;
			if (vt.first == _TEXT_T("<xmlcomment>"))//�ӽڵ��ע��
			{
				tstring comment = tp1.get<tstring>(_TEXT_T("<xmlcomment>"), _TEXT_T(""));  
				tcout << comment << endl;
			}
			else if (vt.first == _TEXT_T("<xmlattr>"))//�ӽڵ������
			{
				a=vt.second.get<unsigned int>(_TEXT_T("age"), 0);//��ȡ����ֵ��ʽ��
				cout << a << endl;
				int b = vt.second.get<unsigned int>(_TEXT_T("xxx"), 0);
				cout << b << endl;
			}
			else if (vt.first == _TEXT_T("xuesheng"))//�ӽڵ�Ľڵ�
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
	//��ʽһ��һ�����һ���ӽڵ㣬�����������
	tptree tp, tp1, tp2, tp3;
	auto& a1 = tp2.add_child(_TEXT_T("xuesheng"), tp3);//���ؽڵ���Ϊxuesheng��a1����tp3�����ӽڵ�tp3��tp2��
	a1.put(_TEXT_T("<xmlattr>.height"), 14);//tp3������

	auto& a2 = tp1.add_child(_TEXT_T("laoshi"), tp2);
	a2.put(_TEXT_T("<xmlattr>.age"), 10);
	a2.put(_TEXT_T("<xmlattr>.xxx"), 11);

	auto& a3 = tp.add_child(_TEXT_T("xiaozhang"), tp1);//���ڵ�tp���ӽڵ�tp1
	a3.put(_TEXT_T("<xmlattr>.name"), _TEXT_T("xxx"));
	a3.put(_TEXT_T("<xmlattr>.weight"), 40);
	tptree commentNode;
	commentNode.put_value(" This is a comment inside root ");
	a3.add_child(_TEXT_T("<xmlcomment>"), commentNode);

	//��ʽ����һ����������ӽڵ㣬ʹ��put_child�Ḳ��֮ǰ��ͬ�ڵ����Ľڵ㣬add��˳�����
	tptree tp4, tp5;
	tp4.add<tstring>(_TEXT_T("name"), _TEXT_T("lisan"));//����tp4���ӽڵ�
	tp4.add<unsigned int>(_TEXT_T("age"), 20);
	tp4.put(_TEXT_T("<xmlattr>.weight"), 40);//���tp4������
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xuesheng"), tp4);//���ӽڵ�tp4���ڵ���Ϊxuesheng�������ڵ�tp��֮ǰ��Ϊxuesheng�Ľڵ㱻����
	//put_child��Ӳ�ͬ�ڵ����Ľڵ㣬���Ḳ��֮ǰ��
	tp5.add<tstring>(_TEXT_T("name"), _TEXT_T("lisi"));
	tp5.add<unsigned int>(_TEXT_T("age"), 10);
	tp5.put(_TEXT_T("<xmlattr>.weight"), 30);
	tp.put_child(_TEXT_T("xiaozhang.laoshi.xxx"), tp5);

	LoadOrSaveFile(path, tp, true);
	//�����ӽڵ㣬ע�͡����ԡ��ӽڵ�ֱ�ֻ����һ�Σ�һ�������Ա����꣩
}