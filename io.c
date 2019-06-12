//这是一个演示C文件接口的demo
#include<stdio.h>
#include<string.h>
int main(){
  // size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
  // size_t fwrite(const void *ptr, size_t size, size_t nmemb, *stream);
  // FILE *fopen(const char *path, const char *mode);
  // int fseek(FILE *stream, long offset, int whence);
  // 对stream文件的读写位置跳转到whence位置偏移offset个字节处
  // whence：跳转的起始位置
  // SEEK_SET   文件起始位置
  // SEEK_CUR   文件读写位置
  // SEEK_END   文件末尾位置
  // offset：   偏移量
  FILE* fp =fopen ("./io.txt","w+");
  if(fp == NULL){
    perror("fopen error\n");
    return -1;
  }

  fseek(fp,10,SEEK_END);
 char* ptr = "hello\n";
  size_t ret = fwrite(ptr,strlen(ptr),1,fp);
  if(ret == 0){
    perror("fwrite error\n");
    return -1;
  }
  fseek(fp,0,SEEK_SET);
  char buf[1024] = {0};
ret = fread(buf,1023,1,fp);
perror("fread error");
printf("ret:%d-[%s]\n",ret,&buf[10]);
//int fclose(FILE *stream);
fclose(fp);
  return 0;
}
