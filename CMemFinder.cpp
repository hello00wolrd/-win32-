#include "CMemFinder.h"

CMemFinder::CMemFinder(DWORD dwProcessId)
{
	this->m_ProcessId = dwProcessId;
	this->m_hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->m_ProcessId);
}
CMemFinder::~CMemFinder()
{
	CloseHandle(m_hProcess);
}

BOOL CMemFinder::CompareAPage(DWORD dwBaseAddr, DWORD dwValue)
{
	//先读取一页的内存
	BYTE arBytes[4096];
	if (!::ReadProcessMemory(this->m_hProcess, (LPVOID)dwBaseAddr, arBytes, 4096, NULL))
		return FALSE; //读取此页失败
	//在这一页内存中查找
	DWORD* pdw;
	for (int i = 0; i < (int)4 * 1024 - 3; i++)
	{
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue) //等于要查找的值
		{
			if (this->m_nListCnt >= 1024)
				return FALSE;
			//添加到全局变量中
			this->m_arList[this->m_nListCnt++] = dwBaseAddr + i;
		}
	}
}

BOOL CMemFinder::FindFirst(DWORD dwValue)
{
	const DWORD dwOneGB = 1024 * 1024 * 1024; //1GB大小
	const DWORD dwOnePage = 4 * 1024; //4KB大小


	if (this->m_hProcess == NULL)
	{
		return FALSE;
	}
	//这里默认系统为windows10与以后的x64系统,决定开始地址
	DWORD dwBase;
	dwBase = 64 * 1024;
	//在开始地址到2gb的地址空间中查找
	for (; dwBase < 2 * dwOneGB; dwBase += dwOnePage)
	{
		//比较一页大小的内存
		CompareAPage(dwBase, dwValue);
	}
	return TRUE;
}

//ShowList函数可用类的[]重载函数表示

BOOL CMemFinder::FindNext(DWORD dwValue)
{
	//保存m_arList数组中有效地址的个数,初始化新的m_nListCnt值
	int nOrgCnt = this->m_nListCnt;
	this->m_nListCnt = 0;

	//在m_arList数组记录的地址中查找
	BOOL bRet = FALSE;
	DWORD dwReadValue;
	for (int i = 0; i < nOrgCnt; i++)
	{
		if (::ReadProcessMemory(this->m_hProcess, (LPVOID)this->m_arList[i], &dwReadValue, sizeof(DWORD),NULL))
		{
			if (dwReadValue == dwValue)
			{
				this->m_arList[this->m_nListCnt++] = this->m_arList[i];
				bRet = TRUE;
			}
		}
	}
	return bRet;
}

BOOL CMemFinder::WriteMemory(DWORD dwAddr, DWORD dwValue)
{
	return ::WriteProcessMemory(this->m_hProcess, (LPVOID)dwAddr, &dwValue, sizeof(DWORD), NULL);
}
