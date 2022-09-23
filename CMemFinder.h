
#ifndef CMEMFINDER_H
#define CMEMFINDER_H
#include <windows.h>
class CMemFinder
{
public:
	CMemFinder(DWORD dwProcessId);
	virtual ~CMemFinder();

	//属性
public:
	BOOL IsFirst() const { return m_bFirst; }
	BOOL IsValid() const { return m_hProcess != NULL; }
	int GetListCount() const { return m_nListCnt; }
	DWORD operator[](int nIndex) { return m_arList[nIndex]; }

	//操作
	virtual BOOL FindFirst(DWORD dwValue);
	virtual BOOL FindNext(DWORD dwValue);
	virtual BOOL WriteMemory(DWORD dwAddr, DWORD dwValue);

	//实现
protected:
	virtual BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue);

	DWORD m_arList[1024]; //地址列表
	int m_nListCnt; //有效地址个数
	HANDLE m_hProcess; //目标进程句柄
	BOOL m_bFirst; //是否第一次搜索
	DWORD m_ProcessId;//目标进程Id
};

#endif
