#include "main.h"
#include <stdlib.h>
#include <stdarg.h>
/**
* get_print_function - a function that returns a pointer to
* a function that returns an int and takes a va_list in parameter
*
* @specifier: the specifier to test
* Return: the function pointer on success
* NULL on fail
*/
print_func_t get_print_function(char specifier)
{
	unsigned int i;

	factory_t factory[] = {
		{'c', char_to_string},
		{'d', int_to_string_handler},
		{'i', int_to_string_handler},
		{'s', string_cpy},
		{'b', binary_to_string_handler},
		{'u', uint_to_string_handler},
		{'x', hexa_lower_to_string_handler},
		{'X', hexa_upper_to_string_handler},
		{'o', octal_to_string_handler},
		{'S', custom_string_cpy},
		{'p', pointer_to_string},
		{'r', reversed_string_handler},
		{'R', rot13_string_handler},
		{'\0', NULL}
	};

	for (i = 0; factory[i].specifier != '\0'; i++)
		if (factory[i].specifier == specifier)
			return (factory[i].handler);

	return (NULL);
}
