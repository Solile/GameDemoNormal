// 动态内存分配
#include <iostream>
using namespace std;
int* intOnHeap();
// 会造成内存泄露的两种函数
void leak1();
void leak2();
int main()
{
	int* pHeap = new int;	// 建立在堆
	*pHeap = 10;
	cout << "*pHeap = " << *pHeap << "\n\n";
	int* pHeap2 = intOnHeap();	// int堆里分配一个内存块
	cout << "*pHeap2 = " << *pHeap2 << "\n\n";
	cout << "Freeing memory pointed by pHeap.\n\n";
	delete pHeap;
	cout << "Freeing memory pointed by pHeap2.\n\n";
	delete pHeap2;
	// ⭐删除悬空指针
	pHeap = 0;
	pHeap2 = 0;
	return 0;
}
int* intOnHeap()
{
	int* pTemp = new int(20);
	return pTemp;
}
void leak1()
{
	int* drip1 = new int(30);
	// 1. delete drip1
	// 2. return drip1/*drip1 且在其他函数delete 这个指针
}
void leak2()
{
	int* drip2 = new int(50);
	drip2 = new int(100);
	delete drip2;
	// 存储50的那片内存 没有被释放
	// 直接赋值 取代 重新开辟空间
}