#ifndef COMMON_H_
#define COMMON_H_

#define _BSD_SOURCE

#define QUEUE_NAME  "/test_queue"
#define MAX_SIZE    1024
#define MSG_STOP    "exit"

#define AGPS_QUEUE_NAME  "/stylagps_queue"

#define AGPS_DATA_FILE  "/tmp/stylagps.data"

#define AGPS_FREQ_SEC   3000000

#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \


#endif /* #ifndef COMMON_H_ */
