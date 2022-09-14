#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;

int main(int argc, char **argv)
{
    int priority;
    //get priority of porcess pid 2, the shell, expects 20

    priority = get_priority(2);
    printf(stdout, "priority of process 2 is %d \n", priority);

    //check if priority out of range
    if(priority > 19 || priority < -20)
        printf(stdout, "Priority is not a value between -20 and +19\n");

    //set priority of process with pid 2 to 12
    printf(stdout, "Setting process pid 2 to priority 12, set_priority returns %d\n", set_priority(2, 12));

    //get priority of this process again to confirm change
    priority = get_priority(2);
    printf(stdout, "priority of process 2 AFTER setting is %d\n", priority);

    //check if priority out of range
    if(priority > 19 || priority < -20)
        printf(stdout, "Priority is not a value between -20 and +19\n");

    


    exit();
}