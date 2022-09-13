#include "types.h"
#include "stat.h"
#include "user.h"

int stdout = 1;

int main(int argc, char **argv)
{
    
    //get priority of porcess pid 2, the shell
    
    printf(stdout, "priority of process 2 is %d \n", get_priority(2));
    //set priority of process pid 5 to 10
    
    set_priority(2, 10);
    printf(stdout, "Setting process pid 2 to priority 10\n");

    //get priority of this process again
    
    printf(stdout, "priority of process 2 AFTER setting is %d\n", get_priority(2));

    exit();
}