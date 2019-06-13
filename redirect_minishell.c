#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
int main(){
  while(1){
    printf("[dev@localhost ~]$ ");
    fflush(stdout);
    char tmp[1024] = {0};
    scanf("%[^\n]%*c",tmp);
    printf("[%s]\n",tmp);
    char* pl = tmp;
    int redirect_flag = 0;//重定向的标志
    char* redirect_file = NULL;
    while(*pl != '\0'){
      if(*pl == '>'){
        *pl = '\0';
        redirect_flag = 1;//清空重定向
        pl++;
        if(*pl == '>'){
          *pl = '\0';
          pl++;
          redirect_flag = 2;//追加重定向
        }
        while(isspace(*pl)&&*pl!='\0'){
          pl++;
        }
        redirect_file = pl;
        while(!isspace(*pl)&&*pl!='\0'){
          pl++;
        }
      }
      pl++;
      //ls> >test.txt
    }
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
        continue;
      }
      *ptr = '\0';
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
      int fd = 1;
      if(redirect_flag == 1){
        fd = open(redirect_file,O_CREAT|O_WRONLY|O_TRUNC,0664);
      }else if(redirect_flag == 2){
        fd = open(redirect_file,O_CREAT|O_WRONLY|O_APPEND,0664);
      }
      dup2(fd,1);//标准输出重定向，将原本要写入标准输出1的数据写入到新文件中

      execvp(argv[0],argv);
      exit(0);
    }
    //等待子进程退出，避免出现僵尸进程
    wait(NULL);
  }
  return 0;
}
