#include<queue>

typedef struct lock_t
{
    int flag;
};

void init(lock_t *lock)
{
    lock->flag = 0;
}


int TestAndSet(int *oldptr,int newptr){
    int old=*oldptr;
    *oldptr=newptr;
    return old;
}
void lock(lock_t *lock){
    while (TestAndSet(&lock->flag,1)==1)
     ;//do nothing
}

void unlock(lock_t *lock){
    lock->flag=0;
}
// 无忙等锁
typedef struct unwait_lock_t
{
    int flag;
    //queue_t *q;//等待队列
};

void init_unwait_lock(unwait_lock_t *lock){
    lock->flag=0;
    //queue_init(lock->q);
}

void lock(unwait_lock_t *lock){
   while (TestAndSet(&lock->flag,1)==1)
   {
       //保存现在运行线程TCB;
       //将现在运行的线程插入到等待队列；
       //设置该线程为等待队列；
       //调度选择
   }
}

void unlock(unwait_lock_t *lock){
  //  if(lock->q!=nullptr){
        //移出等待队列的队头元素
        //将该线程的TCB插入到就绪队列；
        //设置该线程为就绪状态；
  //  }
    lock->flag=0;
}

void unlock(unwait_lock_t *lock){

}