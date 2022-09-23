
#ifndef CMEMFINDER_H
#define CMEMFINDER_H
#include <windows.h>
class CMemFinder
{
public:
	CMemFinder(DWORD dwProcessId);
	virtual ~CMemFinder();

	//����
public:
	BOOL IsFirst() const { return m_bFirst; }
	BOOL IsValid() const { return m_hProcess != NULL; }
	int GetListCount() const { return m_nListCnt; }
	DWORD operator[](int nIndex) { return m_arList[nIndex]; }

	//����
	virtual BOOL FindFirst(DWORD dwValue);
	virtual BOOL FindNext(DWORD dwValue);
	virtual BOOL WriteMemory(DWORD dwAddr, DWORD dwValue);

	//ʵ��
protected:
	virtual BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue);

	DWORD m_arList[1024]; //��ַ�б�
	int m_nListCnt; //��Ч��ַ����
	HANDLE m_hProcess; //Ŀ����̾��
	BOOL m_bFirst; //�Ƿ��һ������
	DWORD m_ProcessId;//Ŀ�����Id
};

#endif
