#include <shell.h>
/**
 * string_difference - Calculates the difference between two strings.
 * @str1: The first input string. 
 * @str2: The second input string.
 *
 * Return: The difference between the two strings.
 */
int string_difference(const char *str1, const char *str2)
{
        int diff = 0;

        while (*str1 != '\0' && *str2 != '\0')
        {
                if (*str1 != *str2)
                        diff++;
                str1++;
                str2++;
        }
        /*Add the remaining characters from str1*/
        while (*str1 != '\0')
        {
                diff++;
                str1++;
        }
        /*Add the remaining characters from str2*/
        while (*str2 != '\0')
        {
                diff++;
                str2++;
        }
        return (diff);
}
