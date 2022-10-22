#include "types.h"
#include "stat.h"
#include "user.h"

// Mutual exclusion lock.
struct lock_t {
  uint locked;       // Is the lock held?

  // For debugging:
  struct proc *thread;   // The thread holding the lock.
};

struct balance {
    char name[32];
    int amount;
};

struct lock_t bal_lock;

volatile int total_balance = 0;

volatile unsigned int delay (unsigned int d) {
   unsigned int i; 
   for (i = 0; i < d; i++) {
       __asm volatile( "nop" ::: );
   }

   return i;   
}

void do_work(void *arg){
    int i; 
    int old;
   
    struct balance *b = (struct balance*) arg; 
    printf(1, "Starting do_work: s:%s\n", b->name);
    lock_acquire(&bal_lock);

    for (i = 0; i < b->amount; i++) { 
         old = total_balance;
         delay(100000);
         total_balance = old + 1;
    }
  
    printf(1, "Done s:%x\n", b->name);

    lock_release(&bal_lock);
    thread_exit();
    for(;;){
    }
    return;
}

int main(int argc, char *argv[]) {

  struct balance b1 = {"b1", 3200};
  struct balance b2 = {"b2", 2800};

  //create lock
  lock_init(&bal_lock);
 
  void *s1, *s2;
  int t1, t2, r1, r2;

  s1 = malloc(4096);
  s2 = malloc(4096);

  t1 = thread_create(do_work, s1, (void*)&b1);
  t2 = thread_create(do_work, s2, (void*)&b2); 


  r1 = thread_join();
  r2 = thread_join();
  
  printf(1, "Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", 
      t1, r1, t2, r2, total_balance);

  exit();
}
