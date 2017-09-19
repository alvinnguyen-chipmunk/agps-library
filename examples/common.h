#ifndef COMMON_H_
#define COMMON_H_

#define _BSD_SOURCE

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define AGPS_QUEUE_NAME  "/stylagps_queue"

#define AGPS_DATA_FILE  "/tmp/stylagps.data"

#define AGPS_FREQ_SEC   3000000

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "\x1b[31m %s:%d:", __func__, __LINE__); \
            perror(#x); \
            fprintf(stderr, "\x1b[0m"); \
            exit(-1); \
        } \
    } while (0) \

#define errExit(msg)    do { fprintf(stderr, "\x1b[31m"); \
                             perror(msg); exit(EXIT_FAILURE); \
                             fprintf(stderr, "\x1b[0m"); \
                           } while (0)

#endif /* #ifndef COMMON_H_ */
