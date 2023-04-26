#include "philosophers.h"

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	if (parsing(ac, av, &vars) == false)
		return (EXIT_FAILURE);
	if (init(&vars) == false)
		return (EXIT_FAILURE);


}
