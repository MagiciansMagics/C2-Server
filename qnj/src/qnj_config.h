#include <sys/types.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             /* offsetof() */
#include <cstdio>               /* C++ equivalent of <stdio.h> */
#include <cstring>              /* C++ equivalent of <string.h> */
#include <vector>               /* C++ library */
#include <cstdlib>              /* C++ equivalent of <stdlib.h> */
#include <cctype>               /* C++ equivalent of <ctype.h> */
#include <cerrno>               /* C++ equivalent of <errno.h> */
#include <string.h>             /* <string.h> is needed for strerror, keep if using strerror */
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <mutex>
#include <map>                  
#include <algorithm>
#include <sys/vfs.h>            

#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        /* TCP_NODELAY, TCP_CORK */
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>

#include <ctime>                /* C++ equivalent of <time.h> */
#include <malloc.h>             /* memalign() */
#include <climits>              /* C++ equivalent of <limits.h> */
#include <sys/ioctl.h>
#include <crypt.h>
#include <sys/utsname.h>        /* uname() */

#include <dlfcn.h>

#define pass (void)0