#include "exec.h"

#define GET 0
#define SET 1

static void	status_main(int action, int *value)
{
	static int	last_status = 0;

	if (action == GET)
		*value = last_status;
	else if (action == SET)
		last_status = *value;
}

int	status_get(void)
{
	int	value;

	status_main(GET, &value);
	return (value);
}

void	status_set(int value)
{
	status_main(SET, &value);
}
