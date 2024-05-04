/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:01:13 by tauer             #+#    #+#             */
/*   Updated: 2024/05/05 01:18:25 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef pthread_mutex_t	mtx;
typedef struct s_data	t_data;

typedef struct s_philo
{
	long				id;
	long				t_meal;
	long				n_meal;
	bool				dead;
	pthread_t			thread;
	mtx					l_fork;
	mtx					*r_fork;
	mtx					philo;
	t_data				*data;
}						t_philo;

struct					s_data
{
	long				n_philo;
	long				n_meal;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				t_simulation;
	bool				b_end;
	bool				b_ready;
	mtx					table;
	mtx					write;
	t_philo				*philo;
}						data;

typedef enum e_thread
{
	T_CREATE,
	T_JOIN,
	M_INIT,
	M_LOCK,
	M_UNLOCK,
	M_DESTROY,
}						t_thread;

typedef enum e_statut
{
	EAT,
	SLEEP,
	THINK,
	L_FORK,
	R_FORK,
	DEAD,
}						t_statut;

typedef enum e_metric
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_metric;

void					thread_handler(t_data *data, t_philo *philo,
							t_thread code);
void					mutex_handler(t_data *data, mtx mutex, t_thread code);
bool					get_bool(t_data *data, mtx mutex, bool *value);
long					get_time(t_data *data, t_metric code);
bool					end(t_data *data);

bool	ft_atoi(const char *str, long *out_value)
{
	int	sign;
	int	value;
	int	i;

	value = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (*out_value = -1, false);
	while (str[i] && (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str && str[i] >= '0' && str[i] <= '9')
	{
		if (value > (__INT_MAX__ - str[i] + '0') / 10)
			return (*out_value = -1, false);
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (true);
	return (*out_value = value * sign, true);
}

void	s_exit(t_data *data, int exit_statut)
{
	long index;

	index = -1;
	while(++index < data->n_philo)
		thread_handler(data, &data->philo[index], M_DESTROY);
	if (data->philo)
		free(data->philo);
	exit(exit_statut);
}

void	*s_malloc(t_data *data, size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		s_exit(data, EXIT_FAILURE);
	return (ret);
}

void	print_data(t_data *data)
{
	printf("\n");
	printf("n_philo %ld\n", data->n_philo);
	printf("n_meal %ld\n", data->n_meal);
	printf("t_eat %ldms\n", data->t_eat);
	printf("t_die %ldms\n", data->t_die);
	printf("t_sleep %ldms\n", data->t_sleep);
}

long	get_time(t_data *data, t_metric code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		s_exit(data, EXIT_FAILURE);
	else if (code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (s_exit(data, EXIT_FAILURE), -1);
}

void	t_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	rest;

	start = get_time(data, MICROSECOND);
	while (get_time(data, MICROSECOND) - start < usec)
	{
		if (end(data))
			break ;
		elapsed = get_time(data, MICROSECOND) - start;
		rest = usec - elapsed;
		if (rest > 1e3)
			usleep(rest / 2);
		else
			while (get_time(data, MICROSECOND) - start < usec)
				;
	}
}

void	wait_threads(t_data *data)
{
	while (!get_bool(data, data->table, &data->b_ready))
		;
}

void	debug_print(t_data *data, t_statut code, t_philo *philo, long elapsed)
{
	if (philo->id % 2 == 0 && code == L_FORK && !end(data))
		printf("%-6ld : %ld has taken left fork [%ld]\n", elapsed, philo->id,
			philo->id);
	else if (philo->id % 2 != 0 && code == L_FORK && !end(data))
		printf("%-6ld : %ld has taken left fork [%ld]\n", elapsed, philo->id,
			(philo->id + 1) % data->n_philo);
	else if (philo->id % 2 != 0 && code == R_FORK && !end(data))
		printf("%-6ld : %ld has taken left fork [%ld]\n", elapsed, philo->id,
			philo->id);
	else if (philo->id % 2 == 0 && code == R_FORK && !end(data))
		printf("%-6ld : %ld has taken left fork [%ld]\n", elapsed, philo->id,
			(philo->id + 1) % data->n_philo);
	else if (code == EAT && !end(data))
		printf("%-6ld : %ld is eating\n", elapsed, philo->id);
	else if (code == SLEEP && !end(data))
		printf("%-6ld : %ld is sleeping\n", elapsed, philo->id);
	else if (code == THINK && !end(data))
		printf("%-6ld : %ld is thinking\n", elapsed, philo->id);
	else if (code == DEAD)
		printf("%-6ld : %ld is dead\n", elapsed, philo->id);
}

void	print_statut(t_statut code, t_data *data, t_philo *philo,
		bool subject_print)
{
	long	elapsed;

	elapsed = get_time(data, MILLISECOND) - data->t_simulation;
	if (philo->dead)
		return ;
	mutex_handler(data, data->write, M_LOCK);
	if (!subject_print)
		debug_print(data, code, philo, elapsed);
	else if ((code == L_FORK || code == R_FORK) && !end(data))
		printf("%-6ld : %ld has taken a fork\n", elapsed, philo->id);
	else if (code == EAT && !end(data))
		printf("%-6ld : %ld is eating\n", elapsed, philo->id);
	else if (code == SLEEP && !end(data))
		printf("%-6ld : %ld is sleeping\n", elapsed, philo->id);
	else if (code == THINK && !end(data))
		printf("%-6ld : %ld is thinking\n", elapsed, philo->id);
	else if (code == DEAD)
		printf("%-6ld : %ld is dead\n", elapsed, philo->id);
	else
		printf("WRONG CODE\n");
	mutex_handler(data, data->write, M_UNLOCK);
}

void					set_long(t_data *data, mtx mutex, long *dest,
							long value);
void					set_bool(t_data *data, mtx mutex, bool *dest,
							bool value);

void	eat(t_philo *philo)
{
	mutex_handler(philo->data, philo->l_fork, M_LOCK);
	print_statut(L_FORK, philo->data, philo, false);
	mutex_handler(philo->data, *philo->r_fork, M_LOCK);
	print_statut(R_FORK, philo->data, philo, false);
	set_long(philo->data, philo->philo, &philo->t_meal, get_time(philo->data,
			MILLISECOND));
	philo->n_meal++;
	print_statut(EAT, philo->data, philo, false);
	t_usleep(philo->data->t_sleep, philo->data);
	if (philo->data->n_meal > 0 && philo->n_meal == philo->data->n_meal)
		set_bool(philo->data, philo->philo, &philo->dead, true);
	mutex_handler(philo->data, philo->l_fork, M_UNLOCK);
	mutex_handler(philo->data, *philo->r_fork, M_UNLOCK);
}

void	thinking(t_philo *philo)
{
	print_statut(THINK, philo->data, philo, false);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// printf("[ %ld ]\n", philo->id);
	wait_threads(philo->data);
	while (!end(data))
	{
		//! eat
		eat(philo);
		//! sleep
		print_statut(SLEEP, data, philo, false);
		printf("TIME SLEEP %ld\n", philo->data->t_sleep);
		t_usleep(philo->data->t_sleep, data);
		//! thinkin
		thinking(philo);
	}
	return (NULL);
}

void	thread_handler(t_data *data, t_philo *philo, t_thread code)
{
	long	ret_check;

	ret_check = 0;
	if (code == T_CREATE)
		ret_check = pthread_create(&philo->thread, NULL, routine, philo);
	else if (code == T_JOIN)
		ret_check = pthread_join(philo->thread, NULL);
	else
		ret_check = printf("wrong code for handling threads\n");
	if (ret_check > 0 || ret_check < 0)
		s_exit(data, EXIT_FAILURE);
}

void	mutex_handler(t_data *data, mtx mutex, t_thread code)
{
	long	ret_check;

	ret_check = 0;
	if (code == M_INIT)
		ret_check = pthread_mutex_init(&mutex, NULL);
	else if (code == M_LOCK)
		ret_check = pthread_mutex_lock(&mutex);
	else if (code == M_UNLOCK)
		ret_check = pthread_mutex_unlock(&mutex);
	else if (code == M_DESTROY)
		ret_check = pthread_mutex_destroy(&mutex);
	else
		ret_check = printf("wrong code for handling mutex\n");
	if (ret_check > 0 || ret_check < 0)
		s_exit(data, EXIT_FAILURE);
}

void	fork_giver(t_data *data)
{
	long	index;

	index = -1;
	while (++index < data->n_philo)
	{
		if (index % 2 == 0)
		{
			data->philo[index].l_fork = data->philo[index].l_fork;
			data->philo[index].r_fork = &data->philo[(index + 1)
				% data->n_philo].l_fork;
		}
		else
		{
			data->philo[index].l_fork = data->philo[(index + 1)
				% data->n_philo].l_fork;
			data->philo[index].r_fork = &data->philo[index].l_fork;
		}
	}
}

void	philos_knowledge(t_data *data)
{
	long	index;
	long	pos;

	index = -1;
	while (++index < data->n_philo)
	{
		data->philo[index].id = index;
		data->philo[index].t_meal = 0;
		data->philo[index].n_meal = 0;
		data->philo[index].dead = false;
		data->philo[index].data = data;
		// data->philo[index].philo = s_malloc(data, sizeof(mtx));
		mutex_handler(data, data->philo[index].philo, M_INIT);
		mutex_handler(data, data->philo[index].l_fork, M_INIT);
	}
	fork_giver(data);
}

void	set_bool(t_data *data, mtx mutex, bool *dest, bool value)
{
	mutex_handler(data, mutex, M_LOCK);
	*dest = value;
	mutex_handler(data, mutex, M_UNLOCK);
}

bool	get_bool(t_data *data, mtx mutex, bool *value)
{
	bool	ret;

	mutex_handler(data, mutex, M_LOCK);
	ret = *value;
	mutex_handler(data, mutex, M_UNLOCK);
	return (ret);
}

void	set_long(t_data *data, mtx mutex, long *dest, long value)
{
	mutex_handler(data, mutex, M_LOCK);
	*dest = value;
	mutex_handler(data, mutex, M_UNLOCK);
}

bool	get_long(t_data *data, mtx mutex, long *value)
{
	bool	ret;

	mutex_handler(data, mutex, M_LOCK);
	ret = *value;
	mutex_handler(data, mutex, M_UNLOCK);
	return (ret);
}

bool	end(t_data *data)
{
	return (get_bool(data, data->table, &data->b_end));
}

bool	setup(t_data *data, char **argv)
{
	data->philo = NULL;
	if (ft_atoi(argv[0], &data->n_philo) && ft_atoi(argv[1], &data->t_die)
		&& ft_atoi(argv[2], &data->t_eat) && ft_atoi(argv[3], &data->t_sleep))
		return (data->t_die *= 1e3, data->t_eat *= 1e3, data->t_sleep *= 1e3,
			ft_atoi(argv[4], &data->n_meal), data->b_ready = false,
			data->b_end = false, mutex_handler(data, data->table, M_INIT),
			mutex_handler(data, data->write, M_INIT),
			data->philo = s_malloc(data, data->n_philo * sizeof(t_philo)),
			philos_knowledge(data), print_data(data), (data->t_die < 6e3
				&& data->t_eat < 6e3 && data->t_sleep < 6e3));
	return (true);
}

void	simulation(t_data *data)
{
	long	index;

	// data->table = s_malloc(data, sizeof(mtx));
	// data->write = s_malloc(data, sizeof(mtx));
	index = -1;
	while (++index < data->n_philo)
		thread_handler(data, &data->philo[index], T_CREATE);
	data->t_simulation = get_time(data, MILLISECOND);
	set_bool(data, data->table, &data->b_ready, true);
	index = -1;
	while (++index < data->n_philo)
		thread_handler(data, &data->philo[index], T_JOIN);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 4 || argc > 6 || setup(&data, argv + 1))
		return (1);
	return (simulation(&data), printf("\n\nCHILL IT IS\n\n"), s_exit(&data,
			EXIT_SUCCESS), 0);
}
