#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// sets the nice value of the specified process
// clamps bound of the nice value
int sys_set_priority(void)
{
  int pid;
  int nice;

  // load pid
  if(argint(0, &pid) < 0)
    return -1;

  // load nice
  if(argint(1, &nice) < 0)
    return -1;

  // Clamp value if nessary
  if (nice < 0){
      nice = 0;
  } else if (nice > 39){
      nice = 39;
  }

  return set_priority(pid, nice);
}

int sys_get_priority(void)
{
  int pid;

  //if invalid pid
  if(argint(0, &pid) < 0)
    return -1;

  return get_priority(pid);


}

int sys_cps(void)
{

  return cps();

}

// Spawns a new thread with shared resources and a unique pid
int sys_thread_create(void)
{
  char *fn;
  char *stack;
  char *arg;

  // load fn
  if(argptr(0, &fn, sizeof(unsigned int)) < 0)
    return -1;

  // load stack
  if(argptr(1, &stack, sizeof(unsigned int)) < 0)
    return -1;

  // load arg
  if(argptr(2, &arg, sizeof(unsigned int)) < 0)
    return -1;

  return thread_create((void *)fn, stack, arg);
}


// waits for a thread.
int sys_thread_join(void)
{
  return thread_join();
}

// kills a thread.
int sys_thread_exit(void)
{
  return thread_exit();
}

// create a new lock
int sys_lock_init(void)
{
  char *lk;

  // load lk
  if(argptr(0, &lk, sizeof(unsigned int)) < 0)
    return -1;

  return lock_init((void *)lk);
}

// wait to aquire a lock
int sys_lock_acquire(void)
{
  char *lk;

  // load lk
  if(argptr(0, &lk, sizeof(unsigned int)) < 0)
    return -1;

  return lock_acquire((void *)lk);
}

// drop a lock
int sys_lock_release(void)
{
  char *lk;

  // load lk
  if(argptr(0, &lk, sizeof(unsigned int)) < 0)
    return -1;

  return lock_release((void *)lk);
}
