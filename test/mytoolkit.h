/**  
* Copyright (C), 2006-2008, ����֤ȯͨ�����޹�˾
* @filename    mytoolkit.h      
* @disp        ���ֿ�ƽ̨�������������д�ļ����̣߳�����ȣ�ͷ�ļ�      
* 
* @author      ������
* @version     1.0
* @date        
*/

#ifndef  __SSCC_MYTOOLKIT_H__
#define  __SSCC_MYTOOLKIT_H__


/* ��������:  �����⺯��
*  ����:  �� ������
*  ������ʷ: 
*      2006.3�� ������: ���� 
*      2007.8.7 ������: ����
*/


#ifdef _WIN32
#   ifndef  FD_SETSIZE
#       define  FD_SETSIZE      2048   /*MSDN: (The default value of FD_SETSIZE is 64, which can be modified by defining FD_SETSIZE to another value before including Winsock2.h.) */
#   endif
#   ifndef _WINSOCKAPI_
#       define _WINSOCKAPI_
#   endif
#   include <winsock2.h>   //����������ļ��а����˴��ļ�������˳���������ܳ��ֱ��������˾��ܸ��ļ�����ʹ�ã����˴���Ȼ�Ȱ������ļ�����ֹ�������
#   pragma comment(lib, "ws2_32.lib")
#   include <process.h>
#   include <direct.h>
#   include <io.h>

#   if defined(_AFXDLL)
#       include <afx.h>
#   else
#       include <windows.h>
#       include <winbase.h>
#       include <stddef.h>
#   endif
#else  //unix
#   include <unistd.h>
#include <pthread.h>
#endif

#include <time.h>

#include <assert.h>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>

/*#if defined(__sun) */
#if defined(_WIN32) || defined(__linux) || defined(_AIX) || defined(__hpux)
#else
#error "you must define your OS"
#endif


#if defined(_WIN32)
#else
typedef unsigned int        UINT32;
typedef int                 INT32;
typedef long                INT_PTR;
#endif


/*
//LP64��˼��long��pointer��64λ��
//ILP64ָint��long��pointer��64λ��
//LLPָlong long��pointer��32-bit�ġ�
//ILP32ָint��long��pointer��32λ�ģ�
//LP32ָlong��pointer��32λ�ġ�
//32λWindows���õ���ILP32����ģ�ͣ�64λWindows���õ���LLP64����ģ�͡�

type      | LP64 | ILP64 | LLP64 | ILP32 | LP32 |
char      |   8  |    8  |   8   |    8  |   8  |
short     |  16  |   16  |  16   |   16  |  16  |
_int32    | N/A  |   32  |  N/A  |   N/A |  N/A |
int       |  32  |   64  |  32   |   32  |  16  |
long      |  64  |   64  |  32   |   32  |  32  |
long long |  N/A |  N/A  |  64   |   N/A |  N/A |
pointer   |  64  |   64  |  64   |   32  |  32  |
*/

/*WinNT.h or basetsd.h(Windows):
 *  The INT_PTR is guaranteed to be the same size as a pointer.  Its
 * size with change with pointer size (32/64).  It should be used
 * anywhere that a pointer is cast to an integer type. UINT_PTR is
 * the unsigned variation.
*/
/* ע�⣺���INT_PTR��UINT32������������ϵͳδ�����壬����Ҫ�Լ��޸Ĵ���������.  
 *    INT_PTR����ָ����ͬ��С�����Σ���Windows���ѱ����壬����������ϵͳ���԰���
 * �ϱ��н��ж��壬�����Լ�����һ�����εĳ����ٶ���.
 * ���磺 typedef long INT_PTR
 */

#ifdef _WIN32
#define VAR2STR(x)   #x
#define INTVAL2STR(x)    VAR2STR(x)
#define compilemsg(desc) message(__FILE__"("INTVAL2STR(__LINE__)"): "desc)
/*usage sample: #pragma	compilemsg("hello") -- will print on compiling.*/
#else
#define compilemsg(desc) 
#endif


#define G_MAXPATHLEN                    2048

#ifdef _WIN32
#define mystricmp       stricmp
#define mystrnicmp      strnicmp
#define MY_DIRECTORY_SEPARATOR_STR      "\\"
#define MY_DIRECTORY_SEPARATOR_CHAR     '\\'
#else
#define mystricmp       strcasecmp
#define mystrnicmp      strncasecmp
#define MY_DIRECTORY_SEPARATOR_STR      "/"
#define MY_DIRECTORY_SEPARATOR_CHAR     '/'
#endif


struct STUSztErrCodeStr
{
	int             m_iErrCode;         /*�������*/
	std::string     m_ssErrString;      /*�����ַ���*/
};



class CMyToolkit
{
public:
    static int      daemon_init();
    static void     sock_signal_ignore();

    //[0x01000000] Windows ���õ���С�˷�: return 0;
    //[0x00000001]  Aix���õ��Ǵ�˷�: return 1;
    static int      IsBigEndian();

    static int      IsRegFileExist(const char* psPath);
    static int      GetRegFileSize(const char* psPath);
    static std::string     UGetModuleFileName(const char* argv0);

    static void     LRTrim(std::string& ssString, const char* pChars=" \r\n\t");
    static char*    ltrim(char* psString, const char* pChars=" \r\n\t");
    static char*    rtrim(char* psString, const char* pChars=" \r\n\t");
    static char*    lrtrim(char* psString, const char* pChars=" \r\n\t");
    static const char*  StrFindFirstOf(const char* pstring, const char* psToFindOneOf);
    static const char*  StrFindLastOf(const char* pstring, const char* psToFindOneOf);
    static const char*  StrFindFirstSub(const char* pstring, const char* psToFindText);
    static const char*  StrFindLastSub(const char* pstring, const char* psToFindText);
    static void     StrSplitByOneOf(std::vector<std::string>& vMultiStrings, const char* pstring, const char* psToFindOneOf);
    static void     StrSplitBySubOf(std::vector<std::string>& vMultiStrings, const char* pstring, const char* psToFindSub);
    static std::vector<char> StrAlign(const char* psString, int iFixAlignLength, int iFlag1Left2Right, const char cFillChar=' ');
    static unsigned char GenerateCheckSum(const char* pInBuf, int iLen);

    static void    SleepMillSec(long lMillSec);
    static long    MyTimeZone();
    static time_t  GetCurrentLongTime() { return time(NULL); }
    static std::string GetCurrentDateTime(int iFormat=0);
    static void    GetCurrentDateTime(time_t* pltSec, long* plMillSec);
    static void    LongTime2LocalTime(time_t lSecd, int* pYear, int* pMonth, int* pDay, int *pHour, int* pMin, int* pSec, int *piWeekDay);
    static void    LongTime2GMTTime(time_t lSecd, int* pYear, int* pMonth, int* pDay, int *pHour, int* pMin, int* pSec, int *piWeekDay);
    static time_t  LocalTime2LongTime(int iYear, int iMonth, int iDay, int iHour, int iMin, int iSecd, time_t* pLSecd);
    static time_t  GMTTime2LongTime(int iYear, int iMonth, int iDay, int iHour, int iMin, int iSecd, time_t* pLSecd);
	static std::string  GetUTCTimestamp();

    static std::string  GetCwd();
    static int   IsAbsolutePath(const char* psPath);
    static void  SplitPathDirFile(const char* psFullPathFile, std::string& ssDir, std::string& ssFileName);
    static void  SplitFilePrePost(const char* psFileName, std::string& ssFNamePre, std::string& ssFilePost);
    static void  SplitPathDirFilePrePost(const char* psAllFileName, std::string& ssDir, std::string& ssFileName, std::string& ssFilePre,std::string& ssFilePost);

    static int   my_mkdir_p(const char* psDir);
    static int   my_unlink(const char* psFileName);
    static int   my_rename(const char* psOldFileName, const char* psNewFileName);
	static int   my_copyfile(const char* psOldFileName, const char* psNewFileName);//wangcx20080304��ƽ̨�����ļ�

    static int   GetShellCmdOutput(const char* psCmdline, std::vector<std::string>& vOut);

    static std::string  BinaryToHex(const void* pvBinary, int iBinaryLen);

    //0-get kb; 1-timeout
    static int  WaitKeyboardHit(unsigned char* pucKBGet, int iTimeoutSec);

    static int  RunNewProcess(const char* psExeName, int iOthArgc, char** ppOthArgv);
};



struct CMyDateTime
{
public:
    time_t		m_ltSecond; 
    long        m_lMillSec;
public:
    CMyDateTime();
    CMyDateTime(time_t ltSecd, long lMillSec);
    void Update();
    std::string ToString();
public:
    static CMyDateTime GetCurrDateTime();
    friend int  operator ==(const CMyDateTime& a, const CMyDateTime& b);
    friend int  operator !=(const CMyDateTime& a, const CMyDateTime& b); 
    friend long operator -(const CMyDateTime& a, const CMyDateTime& b);   
};



#define   G_iMaxLengthOfIniFileLine    2048

class CMyReadIniFile
{
public:
    struct STUNameValuePair
    {
        int             m_iItemID;
        std::string     m_ssName;
        std::string     m_ssValue;
    };

    struct STUSectionInfo
    {
        int                                 m_iSectionID;
        std::string                         m_ssSectionName;
        std::map<int, STUNameValuePair>     m_mapItems;
    };

    //static const int                        m_ciMaxLengthOfLine;
protected:
    std::string                             m_ssIniPathFile;
    int                                     m_bIsParseIniFileOk;

    std::map<int, STUSectionInfo>           m_mapSections;
public:
    CMyReadIniFile(const char* psPathFile);
    int IsParseIniFileOk() { return m_bIsParseIniFileOk; }
    int enumerate_sections(std::map<int, std::string>& mapSections);
    int enumerate_values(int iSectionID, std::map<int, CMyReadIniFile::STUNameValuePair>& mapValues);
    int enumerate_values(const char* psSectionName, std::map<int, CMyReadIniFile::STUNameValuePair>& mapValues);
	int get_string_value(int iSectionID, const char* psItemName, std::string& ssItemValue);
    int get_string_value(const char* psSectionName, const char* psItemName, std::string& ssItemValue);
	
    int get_Item_value(int iSectionID, const char* psItemName, int& iItemValue);
	int get_Item_value(const char* psSectionName, const char* psItemName, int& iItemValue);

    int get_Item_value(int iSectionID, const char* psItemName, std::vector<std::string>& vItemValues);
    int get_Item_value(const char* psSectionName, const char* psItemName, std::vector<std::string>& vItemValues);

    static int GetValueFromNameValuePair(const std::map<int, CMyReadIniFile::STUNameValuePair>& mapValues, const char* psName, std::string& ssValue);
protected:
    static int  GetLineType(const char* psOneLine);   /*0:comment; 1:section; 2-Name-value*/
    static int  GetSectionName(const char* psOneLine, char* psSectionName, size_t iSizSectBuf);
    static int  GetItemNameValue(const char* psOneLine, char* psItemName, size_t iSizItemBuf, char* psItemVal, size_t iSizItemVal);
};





/********************************************************************/
/******************** thread relation begin *************************/
class CMyThread_Mutex
{
public:
#ifdef _WIN32
    CRITICAL_SECTION	m_mutexThread;
#else
    pthread_mutex_t		m_mutexThread;
#endif

public:
    CMyThread_Mutex();
    ~CMyThread_Mutex();

    void acquire();
    void release();    
};


class CMyMutexGuard
{
public:
    CMyThread_Mutex     *m_pmutexObj;
public:
    CMyMutexGuard(CMyThread_Mutex* pmutexObj) 
    {
        m_pmutexObj = pmutexObj;
        if(m_pmutexObj!=NULL) m_pmutexObj->acquire();
    }
    ~CMyMutexGuard() 
    {
        if(m_pmutexObj!=NULL) m_pmutexObj->release();
    }
};

class CMyCondition
{
public:
#ifdef _WIN32
    HANDLE            m_condition;      
#else
    pthread_cond_t    m_condition;    
#endif


public:
    CMyCondition(); 
    ~CMyCondition(); 
    
    void signal(); 
    int  wait(CMyThread_Mutex& mutex, long lMillSecdTimeout);   //return 1-timeout; 0-waited_ok
};
/*********************** sample ****************
CMyMutexGuard  oGuard(mutexInitFinish);
while(!m_bIsInitFinish)
{
    condInitFinish.wait(mutexInitFinish, 1000);
    break;
}
if(!bIsInitFinish)
{
}
*************************************************/

/*************************** template  begin ************************/
template<class TYPE>
class HTPAtomic
{
private:
    TYPE                m_value;
    CMyThread_Mutex     m_mutex;
public:
    HTPAtomic()                                                     { }
    HTPAtomic(const TYPE& value)                                    { m_value=value; }
    HTPAtomic(const HTPAtomic<TYPE>& oValue)                        { m_value=oValue.value(); }
    HTPAtomic<TYPE> &operator= (const HTPAtomic<TYPE>& oValue)      { m_value=oValue.value(); return *this; }
    HTPAtomic &operator= (const TYPE& value)                        { m_value=value; return *this; }
public:
    TYPE value(void)     /*return the copy value safety*/           { CMyMutexGuard mutexGuard(&m_mutex); return m_value; }
    void set(const TYPE& value)   /*set new value safety*/          { CMyMutexGuard mutexGuard(&m_mutex); m_value=value; }
    TYPE operator++ (void)  /*Atomically pre-increment*/            { CMyMutexGuard mutexGuard(&m_mutex); return ++m_value; }
    TYPE operator++ (int)   /*Atomically post-increment*/           { CMyMutexGuard mutexGuard(&m_mutex); return m_value++; }
    TYPE operator+= (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value+=value; }
    TYPE operator-- (void)  /*Atomically pre-decrement*/            { CMyMutexGuard mutexGuard(&m_mutex); return --m_value; }
    TYPE operator-- (int)   /*Atomically post-decrement*/           { CMyMutexGuard mutexGuard(&m_mutex); return m_value++; }
    TYPE operator-= (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value-=value; }
    bool operator== (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value==value; }
    bool operator!= (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value!=value; }
    bool operator>= (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value>=value; }
    bool operator> (const TYPE &value)                              { CMyMutexGuard mutexGuard(&m_mutex); return m_value>value;  }
    bool operator<= (const TYPE &value)                             { CMyMutexGuard mutexGuard(&m_mutex); return m_value<=value; }
    bool operator< (const TYPE &value)                              { CMyMutexGuard mutexGuard(&m_mutex); return m_value<value;  }
public:
    CMyThread_Mutex &mutex (void)  /*access lock. */                { return m_mutex; }
    void acquire(void)  /*access lock. */                           { return m_mutex.acquire(); }
    void release(void)  /*access lock. */                           { return m_mutex.release(); }
    TYPE& value_i(void)    /*danger: access the value not lock.*/           { return m_value; }
    void  value_i(const TYPE& value) /*danger: access the value not lock.*/ { m_value=value; }

    TYPE& _value(void)    /*danger: access the value not lock.*/            { return m_value; }
    void  _value(const TYPE& value) /*danger: access the value not lock.*/  { m_value=value; }

};
/*************************** template  end ************************/


//�߳���Ӧ�ô�CMyThread��������ʵ�ֺ���svc().
//��������̣߳�����activate()���ȴ��߳̽�������wait().
//�������ʹ���̵߳ķ�ʽ����������԰ѱ��൱��һ����ͨ���ֱ࣬�ӵ��ó�Ա����svc()���ɣ���Ϊ��ͨ�ĳ�Ա��������
class CMyThread
{
protected:
    HTPAtomic<int>              m_bIsRunning;
    HTPAtomic<int>              m_aiWriteLogLevel;

#ifdef _WIN32
    HANDLE                      m_handle;
    static unsigned __stdcall   WinThreadProc(void*);
#else
    pthread_t                   m_handle;
    static void*                UnixThreadProc(void*);
#endif

protected:

public:
    CMyThread()
    {
        m_bIsRunning = 1;
        m_aiWriteLogLevel = 0;
#ifdef _WIN32
        m_handle = NULL;
#else
        m_handle = 0;
#endif
    }
    virtual ~CMyThread() {}

public:  //��Щ�������Ա�����.
    virtual int svc();   

    virtual void OnEnterThread() {}
    virtual int  RunLoopOnce()   {return 0;}
    virtual void OnExitThread()  {}           //���ڱ��߳����ִ����������̵߳������һ���ڱ������еȴ����߳��˳���Ȼ���������������ͷ��ڴ�ȽϺ���.
    virtual void OnWriteLogV(const char* psFullFileName, int iLine, int iErrCode, const char *format, va_list ap); //�ú���Ӧ�ñ����أ�������.

public: //��Щ��������Ҫ���õĺ���.
    int  activate(int iStackSize=0);  //�������������̵߳ĺ����������߳�ʵ�ʾ������к���svc().
    int  wait();      //�ȴ��߳̽���. ������ֻ�ǵȴ��߳��˳�����������δ�svc()�˳��������û��Լ������飬����û���������svc()�˳�����ú���������Զ�Ȳ�����Ҳ�޷��˳���
                      //wait���߳���Դ���Ѿ��ͷ�, �߳��Ѿ��˳�, ���Ҳ�Ѿ��ͷ�, ������ҪClose�����.

    static int GetMaxSupportThreadCount();
    int  SetWriteLogLevel(int iLevel=0);

    void SendQuitMessage() { m_bIsRunning = 0; }
    int  IsRunning() { return m_bIsRunning.value(); }
    virtual void OnWriteLog(const char* psFullFileName, int iLine, int iErrCode, const char *format, ... ); 
};

/******************** thread relation end ***************************/
/********************************************************************/








/********************************************************************/
/*************************** tick  begin ****************************/

struct CMyTick
{
public:
    unsigned long   m_ltSecond; 
    int			    m_iMillSec;
public:
    CMyTick() 
    {
        m_ltSecond = 0;
        m_iMillSec = 0;
    }
    CMyTick(time_t ltSec, int iMillSec) 
    {
        m_ltSecond = (unsigned long)ltSec;
        m_iMillSec = iMillSec;
    }
    time_t sec()  { return m_ltSecond; }
    //int    millsec() { return m_iMillSec; }
    friend int  operator ==(const CMyTick& a, const CMyTick& b);
    friend int  operator !=(const CMyTick& a, const CMyTick& b); 
    friend long operator -(const CMyTick& a, const CMyTick& b);   

    static const CMyTick  zero;
};

class CMyTickCreator
{
protected:
    static CMyThread_Mutex  g_oMutexTickLast;   
    static int              m_bIsTickLastHasInit;
    static CMyTick		    g_tickLast;
    static CMyTick          GetUpTick();
public:
    static CMyTick   GetTickCountCurr();   
};
/*************************** tick  end ******************************/
/********************************************************************/









/********************************************************************/
/*************************** template function begin ************************/
template<class TUSER>
class HTPAutoFunc1
{
private:
    int  m_bValid;
    TUSER   *m_ptr;    /*the member pointer to managed.*/
    void (*m_DestroyFunc)(TUSER* ptr);
    HTPAutoFunc1<TUSER>& operator=(HTPAutoFunc1<TUSER>& rhs);  /*private*/
    void* operator new(size_t);  /*private*/
    void operator delete(void*){}   /*private*/
public:
    HTPAutoFunc1()                              { m_ptr=NULL; m_DestroyFunc=NULL; m_bValid=0; }
    HTPAutoFunc1(TUSER *ptr, void (*DestroyFunc)(TUSER *ptr)) { m_ptr=ptr; m_DestroyFunc=DestroyFunc; m_bValid=1; }
    void Destroy()                              { if(m_DestroyFunc) (*m_DestroyFunc)(m_ptr); m_ptr=NULL; m_DestroyFunc=NULL; m_bValid=0; }
    void SetPtr(TUSER *ptr, void (*DestroyFunc)(TUSER *ptr), int bDestoryOld) { if(bDestoryOld&&m_ptr) (*m_DestroyFunc)(m_ptr); m_ptr=ptr; m_DestroyFunc=DestroyFunc; m_bValid=1; }
    void SetInvalid()                           { m_bValid=0; }
    ~HTPAutoFunc1()                             { if(m_DestroyFunc && m_bValid) (*m_DestroyFunc)(m_ptr); }
public:  /*Don't use this function, it only for solaris compiler to compatible.*/
    HTPAutoFunc1(const HTPAutoFunc1<TUSER>& )   { assert(0); /*throw -1;*/ }
};



template<class TUSER, class TPARAM>
class HTPAutoFunc2
{
private:
    int  m_bValid;
    TUSER   *m_ptr;    /*the member pointer to managed.*/
    TPARAM&  m_param;
    void (*m_DestroyFunc)(TUSER* ptr, TPARAM& param);
    HTPAutoFunc2<TUSER, TPARAM>& operator=(HTPAutoFunc2<TUSER, TPARAM>& rhs);  /*private*/
    void* operator new(size_t);  /*private*/
    void operator delete(void*){}   /*private*/
public:
    HTPAutoFunc2(TUSER *ptr, TPARAM& param, void (*DestroyFunc)(TUSER *ptr, TPARAM& param)) 
        :m_ptr(ptr), m_param(param)
    { m_DestroyFunc=DestroyFunc; m_bValid=1; }
    void Destroy()                              { if(m_DestroyFunc) (*m_DestroyFunc)(m_ptr, m_param); m_ptr=NULL; m_DestroyFunc=NULL; m_bValid=0; }
    void SetInvalid()                           { m_bValid=0; }
    ~HTPAutoFunc2()                             { if(m_DestroyFunc && m_bValid) (*m_DestroyFunc)(m_ptr, m_param); }
public:  /*Don't use this function, it only for solaris compiler to compatible.*/
    HTPAutoFunc2(const HTPAutoFunc2<TUSER, TPARAM>& ) { assert(0); /*throw -1;*/ }
};
/*************************** template function end **************************/
/********************************************************************/








class CUUIDCreator
{
public:
    CUUIDCreator();
    ~CUUIDCreator(){}
public:
    void SetMacAddrHex(const char* psMacAddrHex); 

    /*ȫ��Ψһ��ID*/
    /*����32λOS, ����Ϊ47(8*4+2+1+12); ����64λOS, ����Ϊ63(8+8+1+16+1+16+13)*/
    std::string  CreateUUID();

    /*�ڱ��ؼ������Ψһ��ID�����Ҫʹ��ȫ��Ψһ�������ʹ��SetMacAddrHex()�����û�����*/
    /*����32λOS, ����Ϊ34(8*4+2); ����64λOS, ����Ϊ50(8+8+1+16+1+16)*/
    std::string  CreateLocalComputerUUID();
public:
    static std::string  GetMacAddrHex();   /*MAC�ĳ�����6���ֽ�.ת��ΪHex,��Ϊ12���ֽ�*/


    static std::string  GetPIDHex();
public: /*second_seq-this-pid-mac*/
    std::string     m_ssMacAddress;
    std::string     m_ssPID;
    std::string     m_ssThisPtr;

    CMyThread_Mutex m_mutex;
    unsigned int    m_uiCurrSeq;  //���ַ�ʽ��������40���ڸ������ظ���������Ҫ�ظ�
    unsigned int    m_uiLastSec;
};








//wangcx20080624���������{

void  usr_IPCMutexClose(void *pMutex);
void  usr_IPCMutexDestroy(void *pMutex);
void* usr_IPCMutexCreate(const char *psPath, char cNameID); /*name: not use the backslash character*/
void* usr_IPCMutexOpen(const char *psPath, char cNameID);
int   usr_IPCMutexEnter(void *pMutex, int iMillSecdTO);
void  usr_IPCMutexExit(void *pMutex);


class CIPCMutexGuard
{
public:
	void     *m_pmutexObj;
public:
	CIPCMutexGuard(void* pmutexObj, int iMillSecdTO = 0xFFFFFFFF) 
	{
		m_pmutexObj = pmutexObj;
		if(m_pmutexObj!=NULL)
		{
			usr_IPCMutexEnter(m_pmutexObj,  iMillSecdTO);
		}
	}
	~CIPCMutexGuard() 
	{
		if(m_pmutexObj!=NULL) 
		{
			usr_IPCMutexExit(m_pmutexObj);
		}
	}
};

//wangcx20080624���������}








#endif

