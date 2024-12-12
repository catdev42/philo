#include "./include/philo.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*string;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	string = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!(string))
		return (NULL);
	while (i < (len_s1))
	{
		string[i] = s1[i];
		i++;
	}
	while (i < (len_s1 + len_s2))
	{
		string[i++] = s2[j++];
	}
	string[i] = 0;
	return (string);
}

static size_t	ft_length(int n)
{
	size_t		len;
	long int	num;

	num = n;
	len = 1;
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

/* Returns a pointer to the string - caller must free */
char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	long int	num;

	num = n;
	len = ft_length(num);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	str[len] = 0;
	while (num >= 10)
	{
		str[len - 1] = num % 10 + 48;
		num /= 10;
		len--;
	}
	str[len - 1] = num + 48;
	return (str);
}

char	**generate_sem_names(int num_philos, t_table * table)
{
	char **semaphore_names;
	char *temp_ltoa_alloc;

	semaphore_names = (char **)safe_calloc(num_philos + 1, sizeof(char *), table);
	if (semaphore_names == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < num_philos; i++)
	{
		semaphore_names[i] = (char *)malloc(20 * sizeof(char));
		if (semaphore_names[i] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		temp_ltoa_alloc = ft_itoa(i);
		semaphore_names[i] = ft_strjoin("/fork_", temp_ltoa_alloc);
		free(temp_ltoa_alloc);
	}
	return (semaphore_names);
}