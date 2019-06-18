#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
  //int mkfifo(const char *pathname, mode_t mode);
 const char* fifo = "./test.fifo";//命名管道的文件名称
 umask(0);//让管道的文件权限不受限于掩码，由我们自己决定
 int ret = mkfifo(fifo,0664);
 if(ret<0){
   if(errno != EEXIST){
   perror("mkfifo error");
   return -1;
   }
 }
 int fd = open(fifo,O_WRONLY);
 if(fd<0){
   perror("open error");
   return -1;
 }
 printf("fifo:%s open success!!!\n",fifo);
  return 0;
}
