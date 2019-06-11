//这是一个实现进程等待的demo

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
int main(){
  int pid = fork();
  if(pid<0){
    //error是一个全局变量，存储每次系统调用出现错误原因编号
    //strerror通过错误编号获取字符串错误原因
    printf("fork error:%s\n",strerror(errno));
    //perror直接打印上一个系统的调用错误原因
    perror("fork perror");
  }else if(pid == 0){
    sleep(3);
    exit(111);
  }
  //pid_t wait(int* status);
  //阻塞等待任意一个子进程退出，获取返回值
 // wait(NULL);
 //
 // pid_t waitpid(pid_t pid,int* status,int options);
 // 阻塞等待任意一个子进程或者指定的子进程退出
 // pid:-1:等待任意一个子进程  pid>0：等待指定子进程
 // options:WNOHANG:将waitpid设置为非阻塞,0是默认阻塞
  //返回值:若WNOHANG被指定，没有子进程退出则立即报错返回0；错误：-1；
  int statu;
  while( waitpid(-1,&statu,WNOHANG) == 0){
    //非阻塞轮询操作
    printf("drink water\n");
    sleep(1);
  }
  if((statu&0x7f) == 0){
    printf("exit code:%d\n",(statu>>8)&0xff);
  }
  if(WIFEXITED(statu)){
    printf("exit code:%d\n",WEXITSTATUS(statu));
  }
  while(1){
    printf("i am parent\n");
    sleep(1);
  }
  return 0;
}
