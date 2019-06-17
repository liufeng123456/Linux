#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret<0){
    perror("pipe error");
    return -1;
  }
  int pid = fork();
  if(pid == 0){
    //child
    close(pipefd[0]);
   // printf("-------------\n");
    char buf[1024] = {0};
    //若所有写端被关闭，则read不再阻塞，读完数据后返回0;
   int count =  read(pipefd[0],buf,1023);
    printf("child read buf:[%d-%s]\n",count,buf);
    exit(0);
  }else if(pid > 0){
    //parent
    sleep(1);
    close(pipefd[0]);
   write(pipefd[1],"hello world",11);
  printf("--------line--------\n");
  }
  return 0;
}
