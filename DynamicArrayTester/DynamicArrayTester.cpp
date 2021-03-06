// DynamicArrayTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../DynamicArray/DynamicArray.h"

typedef struct
{
	bool a;
	int b;
	char c[32];
	double d;

} EXAMPLE;



int main()
{
	std::cout << sizeof(char) << std::endl;
	std::cout << sizeof(EXAMPLE) << std::endl;
	
	int h = darr_new(sizeof(EXAMPLE));
	EXAMPLE e1, e2, e3;
	memset(&e1, 0, sizeof(EXAMPLE));
	memset(&e2, 0, sizeof(EXAMPLE));
	memset(&e3, 0, sizeof(EXAMPLE));
	e1 = { true,20,"banana",24.5 };
	e2 = { false,-50,"orange", 51.4 };
	e3 = { true,30,"cherry", 68.5 };
	darr_reserve(h, 5);
	darr_push_back(h, (void*)&e1);
	darr_push_back(h, (void*)&e2);
	darr_push_back(h, (void*)&e3);
	darr_push_back(h, (void*)&EXAMPLE({false, -10, "bud light lime", 58.4 }));
	int size = darr_size(h);
	std::cout << "size: " << size << std::endl;
	EXAMPLE* pEx = (EXAMPLE*)darr_pointer(h, 0);
	for (int i = 0; i < size; i++)
	{
		const char* tf;
		if (pEx[i].a) tf = "true";
		else tf = "false";
		printf("i: %d, %s, %d, %s, %.2f\n", i, tf, pEx[i].b, pEx[i].c, pEx[i].d);
	}

	pEx = (EXAMPLE*)darr_pointer(h, 3);
	char* pExc = pEx[0].c;
	for (int j = 0; j < 32; j++)
	{
		char a = pExc[j];
		if (a == '\0') putchar('_');
		else putchar(pExc[j]);
	}
	printf("\r\n");

	return 0;
}

