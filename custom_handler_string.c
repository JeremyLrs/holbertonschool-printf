#include "main.h"
#include <stdarg.h>
#include <stdlib.h>
/* Function declarations */
char *custom_hex_helper(unsigned char str);

/**
 * custom_string_cpy - Copies a string from a va_list, converting
 *                     non-printable characters to their
 *                     hexadecimal escape sequences.
 * @format_specifier: Pointer to format_specifier_t (unused).
 * @args: va_list containing the string to copy.
 *
 * Return: Pointer to a newly allocated string with non-printable
 *         characters replaced by their '\xHH' hex code representation,
 *         or NULL if malloc fails.
 *         The caller is responsible for freeing the returned string.
 */
char *custom_string_cpy(format_specifier_t *format_specifier, va_list args)
{
	unsigned int i = 0, j = 0;
	int size = 0;
	char *to_print;
	char *strcpy, *temp;

	(void)format_specifier;
	to_print = va_arg(args, char *);
	if (to_print == NULL)
		to_print = "(null)";

	for (i = 0; to_print[i] != '\0'; i++)
	{
		if (to_print[i] >= 32 && to_print[i] < 127)
		{
			size++;
		}
		else
		{
			size += 4;
		}
	}

	strcpy = malloc(size + 1);
	if (strcpy == NULL)
		return (NULL);

	for (i = 0; to_print[i] != '\0'; i++)
	{
		if (to_print[i] >= 32 && to_print[i] < 127)
		{
			strcpy[j++] = to_print[i];
		}
		else
		{
			temp = custom_hex_helper((unsigned char)to_print[i]);
			if (temp == NULL)
				return (NULL);

			strcpy[j++] = '\\';
			strcpy[j++] = 'x';
			strcpy[j++] = temp[0];
			strcpy[j++] = temp[1];
			free(temp);
		}
	}

	strcpy[j] = '\0';
	return (strcpy);
}

/**
 * custom_hex_helper - Converts a byte to a 2-digit
 * uppercase hexadecimal string
 * @str: The byte (unsigned char) to convert
 *
 * This function takes a single byte and returns a newly allocated string
 * containing its hexadecimal representation in uppercase. The returned
 * string is always 2 characters long, plus a null terminator.
 *
 * Example: input 10 returns "0A", input 255 returns "FF".
 *
 * Return: A pointer to a 3-character null-terminated string,
 *         or NULL if memory allocation fails
 */
char *custom_hex_helper(unsigned char str)
{
	const char *hex_digits = "0123456789ABCDEF";
	char *result;
	int high = str >> 4; /* getting high nibble */
	int low = str & 0x0F; /* getting low nibble */

	result = malloc(3);
	if (result == NULL)
		return (NULL);

	result[0] = hex_digits[high]; /* printing high nibble */
	result[1] = hex_digits[low]; /* printing low nibble */
	result[2] = '\0';

	return (result);
}
