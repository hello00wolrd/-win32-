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
	//�ȶ�ȡһҳ���ڴ�
	BYTE arBytes[4096];
	if (!::ReadProcessMemory(this->m_hProcess, (LPVOID)dwBaseAddr, arBytes, 4096, NULL))
		return FALSE; //��ȡ��ҳʧ��
	//����һҳ�ڴ��в���
	DWORD* pdw;
	for (int i = 0; i < (int)4 * 1024 - 3; i++)
	{
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue) //����Ҫ���ҵ�ֵ
		{
			if (this->m_nListCnt >= 1024)
				return FALSE;
			//��ӵ�ȫ�ֱ�����
			this->m_arList[this->m_nListCnt++] = dwBaseAddr + i;
		}
	}
}

BOOL CMemFinder::FindFirst(DWORD dwValue)
{
	const DWORD dwOneGB = 1024 * 1024 * 1024; //1GB��С
	const DWORD dwOnePage = 4 * 1024; //4KB��С


	if (this->m_hProcess == NULL)
	{
		return FALSE;
	}
	//����Ĭ��ϵͳΪwindows10���Ժ��x64ϵͳ,������ʼ��ַ
	DWORD dwBase;
	dwBase = 64 * 1024;
	//�ڿ�ʼ��ַ��2gb�ĵ�ַ�ռ��в���
	for (; dwBase < 2 * dwOneGB; dwBase += dwOnePage)
	{
		//�Ƚ�һҳ��С���ڴ�
		CompareAPage(dwBase, dwValue);
	}
	return TRUE;
}

//ShowList�����������[]���غ�����ʾ

BOOL CMemFinder::FindNext(DWORD dwValue)
{
	//����m_arList��������Ч��ַ�ĸ���,��ʼ���µ�m_nListCntֵ
	int nOrgCnt = this->m_nListCnt;
	this->m_nListCnt = 0;

	//��m_arList�����¼�ĵ�ַ�в���
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
