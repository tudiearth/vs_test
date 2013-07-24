#include "mytoolkit.h"
#include <string>
using std::string;

class CUniqIDCreator
{
private:
	static const unsigned int SUBID_MAX_LEN = 9;
	static const unsigned int SUBID_DEFAULT_LEN = 6;

public:
	CUniqIDCreator(int iSubIDLength=SUBID_DEFAULT_LEN);
	~CUniqIDCreator();

	string GenerateExecID();

private:
	CUniqIDCreator(const CUniqIDCreator &oUniqIDCreator);
	CUniqIDCreator operator =(const CUniqIDCreator &oUniqIDCreator);

	static unsigned int NormalizeSubIDLength(int uiSubIDLength);
	static string GenerateSubIDFormatStr(int uiSubIDLength);

	CMyThread_Mutex m_mutexSubID;
	unsigned int m_uiSubID;
	string m_ssSubIDFormat;
	unsigned int m_uiSubIDUpBound;
};
