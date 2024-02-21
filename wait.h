#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <sys/types.h>

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

#define WIFEXITED(status)
#define WIFSIGNALED(status)
#define WIFSTOPPED(status)
#define WIFCONTINUED(status)
#define WEXITSTATUS(status)
#define WTEMSIG(status)
#define WSTOPSIG(status)

#define WNCHANG
#define WUNTRACED

#endif /* _SYS_WAIT_H */
