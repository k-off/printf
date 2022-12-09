/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcovalio <pcovalio@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:53:14 by pcovalio          #+#    #+#             */
/*   Updated: 2022/12/03 10:59:38 by pcovalio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ****************************************************************************
** Header containing `size_t` definition
**************************************************************************** */
# include <stddef.h>

/* ****************************************************************************
** Linked list node
**************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* ****************************************************************************
** Standard library functions
**************************************************************************** */

/**
 * @brief Checks whether c is a 7-bit unsigned char value that fits into the 
  		ASCII character set.
 * @param c character
 * @return On a successfull check returns 1, otherwise 0
*/
int		ft_isascii(int c);

/**
 * @brief Checks for an alphanumeric characte
 * @param c character
 * @return On a successfull check returns 1, otherwise 0
*/
int		ft_isalnum(int c);

/**
 * @brief Checks for an alphabetic character
 * @param c character
 * @return On a successfull check returns 1, otherwise 0
*/
int		ft_isalpha(int c);

/**
 * @brief Checks for a digit
 * @param c character
 * @return On a successfull check returns 1, otherwise 0
*/
int		ft_isdigit(int c);

/**
 * @brief Checks for any printable character including space
 * @param c character
 * @return On a successfull check returns 1, otherwise 0
*/
int		ft_isprint(int c);

/**
 * @brief Calculates the length of the string pointed
       to by s, excluding the terminating null byte ('\0').
 * @param s c-string
 * @return Number of bytes in the string pointed to by s.
*/
size_t	ft_strlen(const char *s);

/**
 * @brief Fills the first n bytes of the memory area
       pointed to by s with the constant byte c.
 * @param s start of memory area
 * @param c value
 * @param n amount of bytes to fill
 * @return Pointer to the memory area s.
*/
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Erases the data in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros (bytes
       containing '\0') to that area.
 * @param s start of memory area
 * @param n amount of bytes to fill
*/
void	ft_bzero(void *s, size_t n);

/**
 * @brief Copies n bytes from memory area src to
       memory area dest.  The memory areas must not overlap.
 * @param dest start of memory area
 * @param src start of memory area
 * @param n amount of bytes to fill
 * @return Pointer to dest
*/
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies n bytes from memory area src to
       memory area dest.  The memory areas may overlap: copying takes
       place as though the bytes in src are first copied into a
       temporary array that does not overlap src or dest, and the bytes
       are then copied from the temporary array to dest.
 * @param dest start of memory area
 * @param src start of memory area
 * @param n amount of bytes to fill
*/
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Copy strings taking the full size of the buffer (not just the length)
  		and guarantee to NUL-terminate the result (as long as size is larger
  		than 0). Note that a byte for the NUL should be included in size.
		Copies up to size - 1 characters from the NUL-terminated string src 
		to dst, NUL-terminating the result.
 * @param dest start of memory area
 * @param src start of memory area
 * @param size full size of the buffer (not just the length)
 * @return Total length of the string they tried to create (length of src).
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Concatenates strings taking the full size of the buffer
  		(not just the length) and guarantee to NUL-terminate the result 
		(as long as there is at least one byte free in dst). Note that a 
		byte for the NUL should be included in size. Appends the NUL-terminated
		string src to the end of dst. It will append at most 
		size - strlen(dst) - 1 bytes, NUL-terminating the result.
 * @param dest start of memory area
 * @param src start of memory area
 * @param size full size of the buffer (not just the length)
 * @return Total length of the string they tried to create 
  		(length of dst plus the length of src).
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Converts lowercase letters to uppercase
 * @param c character
 * @return Uppercase equivalent, if an uppercase representation exists in the
  		current locale.  Otherwise, it returns c.
*/
int		ft_toupper(int c);

/**
 * @brief Converts lowercase letters to lowercase
 * @param c character
 * @return Lowercase equivalent, if an lowercase representation exists in the
  		current locale.  Otherwise, it returns c.
*/
int		ft_tolower(int c);

/**
 * @brief Returns a pointer to the first occurrence of the
  		character c in the string s.
 * @param s c-string
 * @param c character
 * @return Pointer to the first occurrence of the character c in the string s.
*/
char	*ft_strchr(const char *s, int c);

/**
 * @brief Returns a pointer to the last occurrence of the
 		character c in the string s.
 * @param s c-string
 * @param c character
 * @return Pointer to the last occurrence of the character c in the string s.
*/
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Compares the two strings s1 and s2. It returns an integer less than,
  		equal to, or greater than zero if s1 is found, respectively, to be
  		less than, to match, or be greater than s2.
 * @param s1 c-string
 * @param s2 c-string
 * @param n amount of bytes to compare
 * @return Integer less than, equal to, or greater than zero if s1 is found,
  		respectively, to be less than, to match, or be greater than s2
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Scans the initial n bytes of the memory area pointed to by s for the
 		first instance of c.
 * @param s start of memory area
 * @param c interpreted as unsigned char
 * @param n amount of bytes to scan
 * @return Pointer to the matching byte or NULL if the character does not occur
  		in the given memory area.
*/
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares the first n bytes (each interpreted as unsigned char)
  		of the memory areas s1 and s2.
 * @param s1 start of memory area
 * @param s2 start of memory area
 * @param n amount of bytes to compare
 * @return Integer less than, equal to, or
       greater than zero if the first n bytes of s1 is found,
       respectively, to be less than, to match, or be greater than the
       first n bytes of s2.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Locates the first occurrence of the null-terminated string 
  		s2 in the string s1, where not more than n chars of s1 are searched.
 * @param s1 c-string
 * @param s2 c-string
 * @param n amount of bytes to compare
 * @return If little is an empty string, big is returned; if little occurs
  		nowhere in big, NULL is returned; otherwise a pointer to the first
  		character of the first occurrence of little is returned.
*/
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/**
 * @brief Converts the initial portion of the string pointed to by nptr to int.
 * @param nptr c-string
 * @return The converted value or 0 on error.
*/
int		ft_atoi(const char *nptr);

/**
 * @brief Allocates memory for an array of nmemb elements of size bytes each 
  		and returns a pointer to the allocated memory.
 * @param nmemb number of elements
 * @param size of one element
 * @return Pointer to the allocated memory
*/
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Duplicates the string
 * @param s c-string
 * @return Pointer to a newly allocated string
*/
char	*ft_strdup(const char *s);

/* ****************************************************************************
** Additional functions
**************************************************************************** */

/**
 * @brief Allocates (with malloc(3)) and returns a substring
		from the string ’s’. The substring begins at index ’start’ and is of
		maximum size ’len’.
 * @param s: The string from which to create the substring.
 * @param start: The start index of the substring in the string ’s’.
 * @param len: The maximum length of the substring.
 * @return The substring. NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a new
		string, which is the result of the concatenation
		of ’s1’ and ’s2’.
 * @param s1: The prefix string.
 * @param s2: The suffix string.
 * @return The new string. NULL if the allocation fails.
*/
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of
		’s1’ with the characters specified in ’set’ removed
		from the beginning and the end of the string.
 * @param s1: The string to be trimmed.
 * @param set: The reference set of characters to trim.
 * @return The trimmed string. NULL if the allocation fails.
*/
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Allocates (with malloc(3)) and returns an array
		of strings obtained by splitting ’s’ using the
		character ’c’ as a delimiter. The array must end
		with a NULL pointer.
 * @param s: The string to be split.
 * @param c: The delimiter character.
 * @return The array of new strings resulting from the split.
		NULL if the allocation fails.
*/
char	**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc(3)) and returns a string
		representing the integer received as an argument.
		Negative numbers must be handled.
 * @param n: the integer to convert.
 * @return The string representing the integer.
		NULL if the allocation fails.
*/
char	*ft_itoa(int n);

/**
 * @brief Applies the function ’f’ to each character of the
		string ’s’, and passing its index as first argument
		to create a new string (with malloc(3)) resulting
		from successive applications of ’f’.
 * @param s: The string on which to iterate.
 * @param f: The function to apply to each character.
 * @return The string created from the successive applications of ’f’.
		Returns NULL if the allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function ’f’ on each character of
		the string passed as argument, passing its index
		as first argument. Each character is passed by
		address to ’f’ to be modified if necessary.
 * @param s: The string on which to iterate.
 * @param f: The function to apply to each character.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 * @param c: The character to output.
 * @param fd: The file descriptor on which to write.
*/
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor.
 * @param s: The string to output.
 * @param fd: The file descriptor on which to write.
*/
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor 
 		followed by a newline.
 * @param s: The string to output.
 * @param fd: The file descriptor on which to write.
*/
void	ft_putendl_fd(char *s, int fd);

/**
 * @briefOutputs the integer ’n’ to the given file descriptor.
 * @param n: The integer to output.
 * @param fd: The file descriptor on which to write.
*/
void	ft_putnbr_fd(int n, int fd);

/* ****************************************************************************
** Bonus functions
**************************************************************************** */

/**
 * @brief Allocates (with malloc(3)) and returns a new node.
		The member variable ’content’ is initialized with
		the value of the parameter ’content’. The variable
		’next’ is initialized to NULL.
 * @param content: The content to create the node with.
 * @return The new node
*/
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the node ’new’ at the beginning of the list.
 * @param lst: The address of a pointer to the first link of a list.
 * @param new: The address of a pointer to the node to be added to the list.
*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 * @param lst: The beginning of the list.
 * @return The length of the list
*/
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last node of the list.
 * @param lst: The beginning of the list.
 * @return Last node of the list
*/
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds the node ’new’ at the end of the list.
 * @param lst: The address of a pointer to the first link of a list.
 * @param new: The address of a pointer to the node to be added to the list.
*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Takes as a parameter a node and frees the memory of
		the node’s content using the function ’del’ given
		as a parameter and free the node. The memory of
		’next’ must not be freed.

 * @param lst: The node to free.
 * @param del: The address of the function used to delete the content.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Deletes and frees the given node and every successor of that node,
 		using the function ’del’ and free(3). Finally, the pointer to the list
 		must be set to NULL.
 * @param lst: The address of a pointer to a node.
 * @param del: The address of the function used to delete the content of node.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Iterates the list ’lst’ and applies the function
		’f’ on the content of each node.
 * @param lst: The address of a pointer to a node.
 * @param f: The address of the function used to iterate on the list.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function
		’f’ on the content of each node. Creates a new
		list resulting of the successive applications of
		the function ’f’. The ’del’ function is used to
		delete the content of a node if needed.
 * @param lst: The address of a pointer to a node
 * @param f: The address of the function used to iterate on the list
 * @param del: The address of the function used to delete
 * @return The new list. NULL if the allocation fails.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
