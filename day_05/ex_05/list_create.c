#include <stdlib.h>

#include "list_internal.h"


t_list* list_create(void)
{
	return malloc(sizeof(t_list));
}
