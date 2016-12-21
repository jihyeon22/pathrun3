#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int tools_check_exist_file(const char *filename)
{
	int count = 10;

	while(count--) {
		if(access(filename, F_OK) == 0)
			return 0;
		usleep(100);
	}
	return -1;
}

int main(int argc, char* argv[])
{
	char cmd_buf[512] = {0,};
	char run_cmd_buf[512] = {0,};

	char find_path[64] = {0,};
	char file_name[32] = {0,};

	// path + file name
	char full_path[512] = {0,};

	int i = 0;
	int j = 0;

	// --------------------------------------------
	// std input / output init, redirect
	// --------------------------------------------

	close(0);
	close(1);
	close(2);

	stdin = freopen("/dev/null", "r", stdin);
	stdout = freopen("/dev/null", "w", stdout);
	stderr = freopen("/dev/null", "rw", stderr);

	printf("r_ssh program start \r\n");


	// check argument count

	if (!(argc > 2))
		return ;

	// get path
	if ( ( argv[1][strlen(argv[1])-1] ) == '/' )
		sprintf(find_path,"%s",argv[1]);
	else
		sprintf(find_path,"%s/",argv[1]);

	printf("find path is [%s]\r\n", find_path);


	// get file name
	strncpy(file_name, argv[2], strlen(argv[2]));
	printf("file_name is [%s]\r\n", file_name);

	// get command line
	for (i = 2 ; i<argc; i++)
	{
		int len = strlen(argv[i]);

		strncpy( (cmd_buf+j), argv[i], len);
		strncpy( (cmd_buf+len+j), " ", 1);

		j += (len + 1);

	}	
	printf ("cmd_buff is [%s]\r\n",cmd_buf);

	// find file 
	sprintf(full_path, "%s%s", find_path, file_name);
	printf("full path is [%s]\r\n",full_path);

	if ( tools_check_exist_file(full_path) == 0 )
	{
		char full_cmd[128] = {0,};
		sprintf(full_cmd, "%s%s", find_path, cmd_buf);
		printf("target file exist : run target path binary\r\n");
		printf("  -> run : %s\r\n",full_cmd);
		sprintf(run_cmd_buf, "%s &", full_cmd);
		//system(full_cmd);
		system(run_cmd_buf);
	}
	else
	{
		printf("target file not exist : run default path binary\r\n");
		printf("  -> run : %s\r\n",cmd_buf);
		sprintf(run_cmd_buf, "%s &", cmd_buf);
		//system(cmd_buf);
		system(run_cmd_buf);
	}

	exit(0);

}
