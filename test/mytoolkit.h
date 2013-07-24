/**  
* Copyright (C), 2006-2008, 深圳证券通信有限公司
* @filename    mytoolkit.h      
* @disp        各种跨平台基础函数（如读写文件，线程，互斥等）头文件      
* 
* @author      蒋春风
* @version     1.0
* @date        
*/

#ifndef  __SSCC_MYTOOLKIT_H__
#define  __SSCC_MYTOOLKIT_H__


/* 功能描述:  基础库函数
*  创建:  　 蒋春风
*  更新历史: 
*      2006.3　 蒋春风: 创建 
*      2007.8.7 蒋春风: 整理
*/


#ifdef _WIN32
#   ifndef  FD_SETSIZE
#       define  FD_SETSIZE      2048   /*MSDN: (The default value of FD_SETSIZE is 64, which can be modified by defining FD_SETSIZE to another value before including Winsock2.h.) */
#   endif
#   ifndef _WINSOCKAPI_
#       define _WINSOCKAPI_
#   endif
#   include <winsock2.h>   //如果在其他文件中包含了此文件，并且顺序错误，则可能出现编译错误。因此尽管该文件不被使用，但此处仍然先包含此文件，防止编译错误。
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
//LP64意思是long和pointer是64位，
//ILP64指int，long，pointer是64位，
//LLP指long long和pointer是32-bit的。
//ILP32指int，long和pointer是32位的，
//LP32指long和pointer是32位的。
//32位Windows采用的是ILP32数据模型，64位Windows采用的是LLP64数据模型。

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
/* 注意：如果INT_PTR和UINT32等在其它操作系统未被定义，则需要自己修改代码来定义.  
 *    INT_PTR是与指针相同大小的整形，在Windows上已被定义，在其他操作系统可以按照
 * 上表中进行定义，或者自己测试一下整形的长度再定义.
 * 例如： typedef long INT_PTR
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
	int             m_iErrCode;         /*错误代码*/
	std::string     m_ssErrString;      /*错误字符串*/
};



class CMyToolkit
{
public:
    static int      daemon_init();
    static void     sock_signal_ignore();

    //[0x01000000] Windows 采用的是小端法: return 0;
    //[0x00000001]  Aix采用的是大端法: return 1;
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
	static int   my_copyfile(const char* psOldFileName, const char* psNewFileName);//wangcx20080304跨平台拷贝文件

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


//线程类应该从CMyThread派生，并实现函数svc().
//如果启动线程，调用activate()，等待线程结束调用wait().
//如果不想使用线程的方式启动，则可以把本类当作一个普通的类，直接调用成员函数svc()即可，作为普通的成员函数处理。
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

public:  //这些函数可以被重载.
    virtual int svc();   

    virtual void OnEnterThread() {}
    virtual int  RunLoopOnce()   {return 0;}
    virtual void OnExitThread()  {}           //对于本线程中又创建了其它线程的情况，一般在本函数中等待子线程退出，然后再析构函数中释放内存比较合理.
    virtual void OnWriteLogV(const char* psFullFileName, int iLine, int iErrCode, const char *format, va_list ap); //该函数应该被重载，并加锁.

public: //这些函数是需要调用的函数.
    int  activate(int iStackSize=0);  //本函数是启动线程的函数，启动线程实际就是运行函数svc().
    int  wait();      //等待线程结束. 本函数只是等待线程退出，而真正如何从svc()退出，则是用户自己的事情，如果用户不主动从svc()退出，则该函数可能永远等不到，也无法退出。
                      //wait后线程资源就已经释放, 线程已经退出, 句柄也已经释放, 不再需要Close句柄了.

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

    /*全局唯一的ID*/
    /*对于32位OS, 长度为47(8*4+2+1+12); 对于64位OS, 长度为63(8+8+1+16+1+16+13)*/
    std::string  CreateUUID();

    /*在本地计算机上唯一的ID，如果要使得全局唯一，则可以使用SetMacAddrHex()加入用户名等*/
    /*对于32位OS, 长度为34(8*4+2); 对于64位OS, 长度为50(8+8+1+16+1+16)*/
    std::string  CreateLocalComputerUUID();
public:
    static std::string  GetMacAddrHex();   /*MAC的长度是6个字节.转化为Hex,则为12个字节*/


    static std::string  GetPIDHex();
public: /*second_seq-this-pid-mac*/
    std::string     m_ssMacAddress;
    std::string     m_ssPID;
    std::string     m_ssThisPtr;

    CMyThread_Mutex m_mutex;
    unsigned int    m_uiCurrSeq;  //这种方式可以容纳40多亿个包不重复，超过就要重复
    unsigned int    m_uiLastSec;
};








//wangcx20080624加入进程锁{

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

//wangcx20080624加入进程锁}








#endif

