#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
printf("Executing execl.\n");
execl("/bin/ls", "exfork ls", "-la", (char *) 0);
/* 만약 execl이 복귀하면, 호출은 실패. */
perror("execl failed to run ls");
exit(1);
}
