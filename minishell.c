#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
int main(){
  while(1){
    printf("[dev@localhost ~]$ ");
    fflush(stdout);
    char tmp[1024] = {0};
    scanf("%[^\n]%*c",tmp);
    printf("[%s]\n",tmp);
  //解析命令行
  char* ptr = tmp;
  int argc = 0;
  char* argv[32] = {NULL};
  while(*ptr!='\0'){
    if(!isspace(*ptr)){
        argv[argc] = ptr;
        argc++;
        while(!isspace(*ptr)&&*ptr!='\0'){
          ptr++;
        }
        *ptr = '\0';
        ptr++;
        continue;
    }
    ptr++;
  }
  for(int i=0; i<argc;++i){
    printf("argv[%d] = [%s]\n",i,argv[i]);
  }
  argv[argc] = NULL;
  if(!strcmp(argv[0],"cd")){
    //改变当前工作路径
    chdir(argv[1]);
    continue;
  }
  //建立一个子进程，替换子进程
  int pid = fork();
  if(pid == 0){
    execvp(argv[0],argv);
    exit(0);
  }
  //等待子进程退出，避免出现僵尸进程
  wait(NULL);
 }
  return 0;
}
