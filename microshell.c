#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

void ft_putchar_err(char c)
{
	write(2, &c, 1);
}

void ft_error(char *str)
{
	while (*str)
		ft_putchar_err(*str++);
}

int ft_fatal()
{
	ft_error("error: fatal\n");
	exit(1);
}

int size_cmd(char **cmd)
{
	if (!cmd)
		return (0);
	int i = 0;
	while (cmd[i])
		++i;
	return (i);
}

int size_cmd_pipe(char **cmd)
{
	int i = 0;
	while (cmd[i] && cmd[i][0] != '|')
		i++;
	return (i);
}

char** add_cmd(char **cmd, char *arg)
{
	char **tmp = malloc(sizeof(*tmp) * (size_cmd(cmd) + 2));
	
	if (!size_cmd(cmd))
	{
		tmp[0] = arg;
		tmp[1] = NULL;
	}
	else
	{
		int i = -1;
		while (cmd[++i])
			tmp[i] = cmd[i];
		tmp[i] = arg;
		tmp[i + 1] = NULL;
	}
	return (tmp);
}

void print_cmd(char **cmd)
{
	int i = -1;
	while (cmd[++i])
		printf("%s\n", cmd[i]);
	printf("---------\n");
}

int builtin_cd(char **cmd)
{
	if (size_cmd(cmd) != 2)
	{
		ft_error("error: cd: bad arguments\n");
		return (1);
	}

	if (chdir(cmd[1]) == -1)
	{
		ft_error("error: cd: cannot change directory to ");
		ft_error(cmd[1]);
		ft_error("\n");
	}
	else
		printf("pwd = %s\n", getcwd(NULL, 0));
	return (0);
}

char** find_next_pipe(char **cmd)
{
	int i = -1;
	while (cmd[++i])
		if (cmd[i][0] == '|')
			return (&cmd[i + 1]);
	return (NULL);
}

int exec_cmd(char **cmd, char **env)
{
	int ret = 0;
	int status;

	pid_t pid = fork();
	if (pid < 0)
		ft_fatal();
	else if (!pid) //son
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			ft_error("error: cannot execute ");
			ft_error(cmd[0]);
			ft_error("\n");
		}
		return (127);
	}
	else
	{
		waitpid(pid, &status, 0);
		ret = WEXITSTATUS(status);
	}
	return (ret);
}

int exec_son(char **cmd, char **env, int fd_pipe[2], int fd_in)
{
	dup2(fd_in, STDIN_FILENO);
	if (find_next_pipe(cmd))
		dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_in);
	close(fd_pipe[0]);
	close(fd_pipe[1]);

	if (!find_next_pipe(cmd))
		exec_cmd(cmd, env);
	else
	{
		char **tmp;
		int i = 0;
		
		tmp = malloc(sizeof(*tmp) * (size_cmd_pipe(cmd) + 1));
		while (cmd[i] && cmd[i][0] != '|')
		{	
			tmp[i] = cmd[i];
			i++;
		}
		tmp[i] = NULL;
		exec_cmd(tmp, env);
	}
	exit(0);
}

int execute(char **cmd, char **env)
{
	int ret = 0;
	int fdpipe[2];
	int status = 0;
	int nb_wait = 0;
	pid_t pid;


	if (!find_next_pipe(cmd))
		return (exec_cmd(cmd, env));
	else
	{
		int fd_in = dup(STDIN_FILENO);
		while (cmd)
		{
			if (pipe(fdpipe) == -1)
				ft_fatal();
			if ((pid = fork()) == -1)
				ft_fatal();
			else if (!pid)
				exec_son(cmd, env, fdpipe, fd_in);
			else
			{
				close(fd_in);
				fd_in = dup(fdpipe[0]);
				close(fdpipe[0]);
				close(fdpipe[1]);
				++nb_wait;
			}
			cmd = find_next_pipe(cmd);
		}
		close(fd_in);
		while (nb_wait-- != 0)
			if (waitpid(0, &status, 0) == pid)
				ret = WEXITSTATUS(status);
	}
	return (ret);
}

int main(int ac, char **av, char **env)
{
	int ret = 0;
	int i = 0;
	char **cmd = NULL;

	while (++i < ac)
	{
		while (av[i] && strcmp(av[i], ";"))
			cmd = add_cmd(cmd, av[i++]);
		print_cmd(cmd);
		if (!strcmp("cd", cmd[0]))
			ret = builtin_cd(cmd);
		else
			execute(cmd, env);
		free(cmd);
		cmd = NULL;
	}
	return (ret);
}
