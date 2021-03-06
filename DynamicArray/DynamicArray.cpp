// DynamicArray.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DynamicArray.h"
#include <vector>
#include <deque>
typedef std::vector<char> v_char;
static int last_handle = 0;

class DArray
{
public:
	DArray(int sizeof_type) :
		handle(++last_handle),
		sizeof_type(sizeof_type)
	{
	}
	~DArray()
	{
	}
	int get_handle()
	{
		return handle;
	}
	int get_sizeof_type()
	{
		return sizeof_type;
	}
	v_char darray;
private:
	int handle;
	int sizeof_type;

};
std::deque<DArray> dq_da;


DLLFUNC_C int darr_new(int sizeof_type)
{
	try {
		if (sizeof_type <= 0) return 0;
		DArray da(sizeof_type);
		dq_da.push_back(da);
		return da.get_handle();
	}
	catch (...) { return 0; }
}
DLLFUNC_C int darr_size(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle) return da.darray.size() / da.get_sizeof_type();
		}
		return 0; // no matches
	}
	catch (...) { return 0; }
}
DLLFUNC_C int darr_typesize(int handle)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle) return da.get_sizeof_type();
		}
		return 0; // no matches
	}
	catch (...) { return 0; }
}
DLLFUNC_C int darr_push_back(int handle, void* pElement)
{
	try {
		if (!pElement) return 0;
		char* pChar = (char*)pElement;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				// make sure enough memory is allocated for the entire push back operation
				if (da.darray.capacity() < (da.darray.size() + da.get_sizeof_type()))
					da.darray.reserve(da.darray.size() + da.get_sizeof_type());
				// push back all bytes one at a time
				for (int i = 0; i < da.get_sizeof_type(); i++)
				{
					da.darray.push_back(pChar[i]);
				}
				return (da.darray.size() / da.get_sizeof_type());
			}
		}
		return 0; // fail case
	}
	catch (...) { return 0; }
}
DLLFUNC_C void* darr_pointer(int handle, int nElement)
{
	try {
		char *ptr0 = NULL, *ptrN = NULL;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				ptr0 = da.darray.data();
				if (ptr0) ptrN = ptr0 + (nElement * da.get_sizeof_type());
			}
		}
		return (void*)ptrN;
	}
	catch (...) { return NULL; }

}
DLLFUNC_C bool darr_resize(int handle, int nSize)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				da.darray.resize(nSize * da.get_sizeof_type());
				return true;
			}
		}
		return false;
	}
	catch (...) { return false; }

}
DLLFUNC_C bool darr_reserve(int handle, int nSize)
{
	try {
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				da.darray.reserve(da.get_sizeof_type() * nSize);
				return true;
			}
		}
		return false;
	}
	catch (...) { return false; }
}
DLLFUNC_C bool darr_destroy(int handle)
{
	try {
		int i = 0; bool found = false;
		for (auto& da : dq_da)
		{
			if (da.get_handle() == handle)
			{
				found = true;
				break;
			}
			++i;
		}
		if (!found) return false;
		else
		{
			dq_da.erase(dq_da.begin() + i);
			return true;
		}
	}
	catch (...) { return false; }
}


