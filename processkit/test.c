#include <jetspace/processkit.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int size;
  int *pids = jetspace_get_pids(&size);

  for(int x = 0; x < size; x++)
  {
    puts("-----------------------------");
    printf("PID: %d\n", pids[x]);
    JetSpaceProcess *p = jetspace_get_process(pids[x]);
    printf("state> %c\n", p->state);
    printf("name > %s\n", p->name);
    printf("prio > %d\n", p->priority);
    printf("UID  > %d (%s)\n", p->uid, p->user->pw_name);
    free(p);
  }


  free(pids);
  return 0;
}
