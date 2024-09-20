#ifndef _QNJ_CONFIG_H_
#define _QNJ_CONFIG_H_
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
#include <random>
#include <sstream>
#include <atomic>
#include <string_view>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <mutex>
#include <map>                  
#include <algorithm>
#include <sys/vfs.h>            
#include <thread>
#include <fstream>

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
#include <sys/epoll.h>

#include <ctime>                /* C++ equivalent of <time.h> */
#include <malloc.h>             /* memalign() */
#include <climits>              /* C++ equivalent of <limits.h> */
#include <sys/ioctl.h>
#include <crypt.h>
#include <sys/utsname.h>        /* uname() */

#include <dlfcn.h>

#define pass (void)0

std::string payload_config_path = "/root/qnj-server/payloads.cfg";
std::string payload_file_path = "/root/qnj-server/client_cmds/";

std::string data_0x00_client_path = "/root/qnj-server/user_client_data-0x00.json";

std::string screen_shot_save_path = "/home/magician/Desktop/QNJ/QNJ-Cloud/assets/ssusers/";
std::string full_path_extra_path = "/home/magician/Desktop/QNJ";
std::string qnj_screen_shot_path = "/QNJ-Cloud/assets/ssusers/";

#endif