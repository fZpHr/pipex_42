#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// change le fd de stdout pour qu'il pointe vers example.txt
/*int main()
{
	int		fd;
	char	*args[3];
	pid_t	pid;
	int		fd[2];
	pid_t	pid;
	char	buffer[13];
	pid_t	pid;
	pid_t	pid;
	pid_t	pid;
	pid_t	pid;
	int		fd[0] = open("file1", O_RDONLY);
	int		fd[1] = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid_t	pid;
	int		fd[0] = open("file1", O_RDONLY);
	int		fd[1] = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("This is printed in example.txt!\n");
	return (0);
}*/
// regarde si on a les droits de lecture/ecrire/exec sur example.txt
/*int main()
{
	if (access("example.txt", R_OK) != -1) // R_OK for read, W_OK for write,
		X_OK for execute
		printf("I have permission\n");
	else
		printf("I don't have permission\n");
	return (0);
}*/
// execute ls -l
/*int main()
{
	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("This line will not be executed.\n");
	return (0);
}*/
// execute 2 commandes en meme temps
/*int main()
{
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("This is the child process. (pid: %d)\n", getpid());
	else
		printf("This is the parent process. (pid: %d)\n", getpid());
	return (0);
}*/
// permet de faire un pipe entre 2 commandes

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int	main(void)
{
	pid_t	pid;
	int		fd[2];
	char buffer[100];
	fd[0] = open("file1", O_RDONLY);
	fd[1] = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]); // close the read end of the pipe
		write(fd[1], "Hello parent!", 13);
		close(fd[1]); // close the write end of the pipe
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]); // close the write end of the pipe
		read(fd[0], buffer, 13);
		close(fd[0]); // close the read end of the pipe
		printf("Message from child: '%s'\n", buffer);
		exit(EXIT_SUCCESS);
	}
}

// delete un fichier
/*int main()
{
	if (unlink("example.txt") == 0)
		printf("File successfully deleted");
	else
		printf("Error deleting file");

	return (0);
}*/
