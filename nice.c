#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{

  if(argc < 3){
    printf(2, "Usage: nice pid priority\n");
    exit();
  }
    int pid = atoi(argv[1]); //atoi returns 0 if something non-numerical was entered. Priority o
    int priority = atoi(argv[2]);
    
    if(pid < 1)
    {
        printf(2,"Parameter pid was either non-numerical or 0. Please enter pids > 0 and the process should exist, ideally.");
    }

    if(priority < -20 || priority > 19)
    {
        printf(2,"Please enter nice values between -20 and +19 (inclusive).\n");
        exit();
    }

 if(set_priority(pid, priority) < 0)
 {
    printf(2,"Error setting priority. Bam.\n");
    exit();
 }

  exit();
}