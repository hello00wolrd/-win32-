// #include "CMemFinder.h"
// #include <iostream>
//
// int main(int __argc, char* __argv)
// {
// 	//���Ŀ����̾��
// 	DWORD dwId;
// 	std::cin >> dwId;
// 	CMemFinder Cmemfinder1 = CMemFinder(dwId);
// 	//����Ҫ�޸ĵ�ֵ
// 	int iVal;
// 	printf_s("Input val = ");
// 	scanf_s("%d", &iVal);
//
// 	//���е�һ�β���
// 	Cmemfinder1.FindFirst(iVal);
// 	//������
// 	int i = Cmemfinder1.GetListCount();
// 	while (i > 1)
// 	{
// 		printf_s("now the list have %d members, Input val = ",i);
// 		scanf_s("%d", &iVal);
// 		//�����´�����
// 		Cmemfinder1.FindNext(iVal);
// 		i = Cmemfinder1.GetListCount();
// 	}
// 	printf_s("we find it, New value = ");
// 	scanf_s("%d", &iVal);
// 	if (Cmemfinder1.WriteMemory(Cmemfinder1[0], iVal))
// 		printf_s("Write data success \n");
// }
