#include "rwXml.h"
#include "rwJson.h"
int main()
{
	rwXml rw;
	tstring path =_TEXT_T("1.xml");
	rw.WriteXml(path);
	rw.ReadXml(path);

	/*rwJson rj;
	tstring p = _TEXT_T("2.xml");
	rj.WriteJson(p);
	rj.ReadJson(p);*/
	system("pause");
	return 0;
}