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
	//��ȡ�ӽڵ�
	tp2 = tp1.get_child(_TEXT_T("xuexiao"));
	//��ֵ�Ի�ȡֵ
	tstring m = tp2.get<tstring>(_TEXT_T("mianji"), _TEXT_T(""));
	tcout << m << endl;
	tp3 = tp2.get_child(_TEXT_T("library"));
	//��������
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
	tp4.put(_TEXT_T("name"), _TEXT_T("english"));//������ֵ��
	tp4.put(_TEXT_T("price"), 10);
	tp3.push_back(make_pair(_TEXT_T(""), tp4));//���������������
	tp4.put(_TEXT_T("name"), _TEXT_T("chinese"));
	tp4.put(_TEXT_T("price"), 20);
	tp3.push_back(make_pair(_TEXT_T(""), tp4));
	tp2.add(_TEXT_T("mianji"),3000);
	tp2.add_child(_TEXT_T("library"), tp3);//���������ڵ�
	tp1.add_child(_TEXT_T("xuexiao"), tp2);
	tp.add_child(_TEXT_T("root"), tp1);
	LoadOrSaveFile(path, tp, true);
	// {}��ʾһ�����󣬿��԰��������ֵ��
	// []��ʾһ�����飬���԰����������
}