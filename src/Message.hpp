#ifndef __MESSAGE_M__
#define __MESSAGE_M__

// server, client 공통 공유

struct __MsgCalc {
    long mtype;
    char id[20];
    char pw[20];
    int mode;
};
typedef struct __MsgCalc MsgCalc;

struct __MsgRslt {
    long mtype;
    int result;
};
typedef struct __MsgRslt MsgRslt;

#endif
