#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	int pipefd[2];
		pid_t cpid;
		char buf;

		if (argc != 2) {
			fprintf(stderr, "Usage: %s <string> which is one seperated char\n", argv[0]);
			exit(EXIT_FAILURE);
		}

		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		cpid = fork();
		if (cpid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (cpid == 0) {    /* Child writes to pipe[1]*/
			close(pipefd[0]);          /* Close unused read end */
			dup2(pipefd[1],1);
			execl("/bin/ls", "/bin/ls", (char *) NULL);

		} else {            /* Parent reads from pipe[0]  */
			wait(NULL);                /* Wait for child */

			close(pipefd[1]);          /* Close unused write end */
			while (read(pipefd[0], &buf, 1) > 0){
				if(write(STDOUT_FILENO, argv[1], 1)!=1){
					perror("write failed");
					exit(EXIT_FAILURE);
				}
				if(write(STDOUT_FILENO, &buf, 1)!=1){
					perror("write failed");
					exit(EXIT_FAILURE);
				}
			}
			if(write(STDOUT_FILENO, "\t", 1)!=1){
				perror("write failed");
				exit(EXIT_FAILURE);
			}

			close(pipefd[0]);
		}

		return 0;
}
