// #include "CMemFinder.h"
// #include <iostream>
//
// int main(int __argc, char* __argv)
// {
// 	//获得目标进程句柄
// 	DWORD dwId;
// 	std::cin >> dwId;
// 	CMemFinder Cmemfinder1 = CMemFinder(dwId);
// 	//输入要修改的值
// 	int iVal;
// 	printf_s("Input val = ");
// 	scanf_s("%d", &iVal);
//
// 	//进行第一次查找
// 	Cmemfinder1.FindFirst(iVal);
// 	//查验结果
// 	int i = Cmemfinder1.GetListCount();
// 	while (i > 1)
// 	{
// 		printf_s("now the list have %d members, Input val = ",i);
// 		scanf_s("%d", &iVal);
// 		//进行下次搜索
// 		Cmemfinder1.FindNext(iVal);
// 		i = Cmemfinder1.GetListCount();
// 	}
// 	printf_s("we find it, New value = ");
// 	scanf_s("%d", &iVal);
// 	if (Cmemfinder1.WriteMemory(Cmemfinder1[0], iVal))
// 		printf_s("Write data success \n");
//   getchar();
// return 0;
// }
