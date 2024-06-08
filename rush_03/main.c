#include <stdio.h>
#include <stdlib.h>

#include "directory.h"
#include "directory_tools.h"
#include "directory_read.h"
#include "directory_write.h"
#include "commands.h"

int	main(int argc, char** argv)
{
	(void)argc;
	char** attributes = &argv[7];

	char* infos[5] = {argv[3], argv[4], argv[5], argv[6], NULL};

	exec_cmd(argv[1], argv[2], infos, attributes);

	return 0;
}
