#pragma once
#include "Drive.h"

struct PID_LIST
{
	LIST_ENTRY List;
	ULONG PID;
};

#ifdef _AMD64_
static void *operator new (size_t lBlockSize)
{
	return ExAllocatePoolWithTag(NonPagedPool, lBlockSize, 111);
}

static void operator delete(void *p)
{
	if (!p)
	{
		return;
	}
	ExFreePoolWithTag(p, 111);
}
#else
static void * __CRTDECL operator new (size_t lBlockSize)
{
	return ExAllocatePoolWithTag(NonPagedPool, lBlockSize, 111);
}

static void __CRTDECL operator delete(void *p)
{
	if (!p)
	{
		return;
	}
	ExFreePoolWithTag(p, 111);
}
#endif