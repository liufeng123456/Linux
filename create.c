#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void* thr_entry(void* arg){
  while(1){
    printf("i am common thread-----%s\n",(char*)arg);
    sleep(1);
  }
  return NULL;
}
int main(){
/*int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);*/
  pthread_t tid;
  const char* param = "jintian quwan"; 
  int ret = pthread_create(&tid,NULL,thr_entry,(void*)param);
  if(ret!=0){
    printf("pthread_create error\n");
    return -1;
  }
  printf("tid:%p\n",tid);
  while(1){
    printf("i am main thread------\n");
    sleep(1);
  }  
  return 0;
}
