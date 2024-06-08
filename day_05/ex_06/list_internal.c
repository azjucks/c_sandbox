#include <stdlib.h>

#include "list_internal.h"

int compare(void* data1, void* data2)
{
	if (data1 == NULL || data2 == NULL)
		return 1;
	
	if (data1 < data2)
		return -1;
	
	return 1;
}
