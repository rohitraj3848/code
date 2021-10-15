/********************************************************************
 *
 *    FILE NAME    : sp_fmwk.h
 *
 *    DESCRIPTION  : The file contains the declaration for the functions
 *      used by sp_fmwk.c
 *
 *    Revision History
 *  -----------------------------------------------------------------
 *    DATE            NAME                REFERENCE        REASON
 *    08/08/2018      Inder/                -             Initial Draft       
 *                    Prashant Upadhyaya                   for POC
 *
 *    Copyright , Truring Softek, 2018
 *******************************************************************/

#ifndef __FWH__
#define __FWH__

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/telnet.h>
#include <netdb.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include<dirent.h>
#include<sys/wait.h>
#include <libgen.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <pthread.h>
#include <rpc/rpc.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_tun.h>
#include <linux/filter.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/netlink.h>
#include <linux/xfrm.h>
#include <net/route.h>
#include <linux/rtnetlink.h>
#include <netinet/tcp.h>
#include <sys/uio.h>
#ifndef DPDK_DP
#include <net/ethernet.h>
#endif



#ifdef LINUX_DP
#include <packet_handler.h>
#endif

#ifdef EPOLL
#include <sys/epoll.h>
#endif


#define SUCCESS 1
#define FAILURE 0
#define FW_CONST_ONE  1
#define FW_CONST_ZERO 0

#define READ_EVENT 0
#define WRITE_EVENT 1
#define EXCEPTION_EVENT 2

/************************************************************************************/
/***** Types ************************************************************************/
/************************************************************************************/

/************************************************************************************/
/***** Forward Declarations For Linked Lists ****************************************/
/************************************************************************************/

typedef struct  tLIST 	LIST;
typedef struct tTIMER 	TIMER;
typedef struct tFdList  FdList;
typedef struct tQueue mQueue;
typedef struct tqList qList;
typedef struct tTASK TASK;
typedef struct tTaskList TaskList;
typedef struct tSERVICE SERVICE;
typedef struct tServiceList ServiceList;


/************************************************************************************/
/***** Init *************************************************************************/
/************************************************************************************/

void fwInit(unsigned int appid);
void shellInit(unsigned int appid);
void fwSetupExtraFdset(fd_set aset);
/************************************************************************************/
/***** MainLoop *********************************************************************/
/************************************************************************************/

int fwMultiplexMainLoop(unsigned int appid);

/************************************************************************************/
/***** ThreadMask *******************************************************************/
/************************************************************************************/

void fwmask();

/************************************************************************************/
/***** Debug ************************************************************************/
/************************************************************************************/

void fwPrintList();
int fw_display_log_level(unsigned int appid);

/************************************************************************************/
/***** FTP **************************************************************************/
/************************************************************************************/

typedef struct  ftp_s {
	int             sd,
	sd_data;
	struct sockaddr_in
	remotectladdr,
	localctladdr,
	data_addr;
	FILE            *cin,
	    *cout;
} ftp_t;

int     ftpGet( char *local, char *remote, char *host, char *user, char *password );
int     ftpPut( char *local, char *remote, char *host, char *user, char *password );
void    ftpDebug( int flag );
void    ftpClose( ftp_t *F );
void    ftpCommand( ftp_t *F, char *format, ... );
int     ftpReplyGet( ftp_t *F, int expecteof );
ftp_t   *ftpConnect( char *host, unsigned short port, char *user, char *password );
int     ftpPort( ftp_t *F );
int     ftpSend( ftp_t *F, char *local, char *remote );
void    ftpTerminate( ftp_t *F );
int     ftpRecv( ftp_t *F, char *local, char *remote );

/************************************************************************************/
/***** Sockets **********************************************************************/
/************************************************************************************/

struct tFdList
{
	LIST * 	fdlist;
};


#define MAXUDPLEN       65536
/** change start for bug 155 **/
#define LITTLE_ENDIAN_MACHINE 1
#define BIG_ENDIAN_MACHINE    2
/** changes end for bug 155 **/

int tcpSocketServer(int localPort);
int tcpSocketServerExt(char* localip, int localPort);
int tcpSocketClient(int localPort);
int tcpSocketClientExt(char* localip, int localPort);
int udpSocket(int localPort);
int unixdomainSocket(char* file);
int unixdomainStreamSocketServer(char* file);
int unixdomainStreamSocketClient(char* file);
int unixdomainConnect(int fd, char* file);
int unixdomainAccept(int fd);
int udpWrite(int fd, char* remoteipaddress, int remoteport, char* data, int length);
int unixdomainWrite(int fd, char* peerfile, char* data, int length);
int udpRead(int fd, char* data);
int udpReadFrom(int fd, char* data, char* ip, unsigned short* port);
int tcpWrite(int fd, char* data, int length);
int tcpRead(int fd, char* data, int length);
int tcpConnect(int fd, char* remoteipaddress, int remoteport);
int tcpConnect6(int fd, char* remoteipaddress, int remoteport);
/** Changes Start for Bug 234 **/
void uualarm(int microsec);
void sockalarmhandler(int alarmnum);
int tcpConnectExt(int fd, char* remoteipaddress, int remoteport, int timeout);
int tcpConnectExt6(int fd, char* remoteipaddress, int remoteport,int timeout);
/** Changes End for Bug 234 **/
int tcpSocketClient6(int localPort);
int tcpSocketClientExt6(char* localip, int localPort);
int tcpAccept(int fd);
int writen(int fd, char* ptr, int nbytes);
int readn(int fd, char* ptr, int nbytes);


/************************************************************************************/
/***** Queues ***********************************************************************/
/************************************************************************************/

struct tQueue
{
	int           qid;
	int           length;
	int           type;
	void *        clientData;
	int           ( * callBack)( int qid,int length,int type, void * clientData, void * callData);
	pthread_t     threadId;
	int           typeRead;
	int           pipeFd[2];
	mQueue *      nextEntry;
};

struct tqList
{
	mQueue * list;
};


int fwMultiplexAddQueue(unsigned int appid,int qid, int type, int length, void *cdata, int (*fn)(int, int, int, void *, 
void*));
int fwMultiplexRemoveQueue(unsigned int appid, int qid, int type);
int queueWrite(int qid, int type, int length, char* payload);
int queueRead(int qid, int type, int length, char** payload, int* typeread);

mQueue * fwListAddMqEntry( int qid, int length, int type, int pipeFd0 , int pipeFd1, void * cdata, int (*fn)(int, int, int,
void * , void*) );
int fwListRemoveMqEntry(unsigned int appid, int quid, int type  );
#ifdef __cplusplus
extern "C"
#endif
void * fwThreadFn ( void * tnode );
int fwReadFromPipe (int fd, void * cData );
void fwPrintQueueList();

/************************************************************************************/
/***** Doubly linked list util ******************************************************/
/************************************************************************************/

typedef struct node {
    struct node *next;      /* Points at the next node in the list */
    struct node *previous;  /* Points at the previous node in the list */
} NODE;


typedef struct{                 /* Header for a linked list. */
    NODE node;              /* Header list node */
    int count;              /* Number of nodes in list */
} DLIST;

extern    void         lstInit (DLIST *pList);
extern    void         lstAdd (DLIST *pList, NODE *pNode);
extern    void         lstConcat (DLIST *pDstList, DLIST *pAddList);
extern    int          lstCount (DLIST *pList);
extern    void         lstDelete (DLIST *pList, NODE *pNode);
extern    void         lstExtract (DLIST *pSrcList, NODE *pStartNode, NODE *pEndNode, DLIST *pDstList);
extern    NODE *       lstFirst (DLIST *pList);
extern    NODE *       lstGet (DLIST *pList);
extern    void         lstInsert (DLIST *pList, NODE *pPrev, NODE *pNode);
extern    NODE *       lstLast (DLIST *pList);
extern    NODE *       lstNext (NODE *pNode);
extern    NODE *       lstNth (DLIST *pList, int nodenum);
extern    NODE *       lstPrevious (NODE *pNode);
extern    NODE *       lstNStep (NODE *pNode, int nStep);
extern    int          lstFind (DLIST *pList, NODE *pNode);
extern    void         lstFree (DLIST *pList);


/**************************************************************************************/
/****** Timer *************************************************************************/
/**************************************************************************************/

typedef void* fw_timer_id_t;

struct  tLIST
{
    LIST *  NextEntry;
    int     value;
    void *  clientData;
    int     (* callBack)(int, void*);
};

typedef struct
{
    NODE    __anchor__;
    int     value;
    void *  readClientData;
    void *  writeClientData;
    void *  exceptionClientData;
    int     (* readCallBack)(int, void*);
    int     (* writeCallBack)(int, void*);
    int     (* exceptionCallBack)(int, void*);
}tFdNode;

typedef struct
{
    NODE    __anchor__;
    time_t  epoch;
    int value;
    int     Period;
    void *  clientData;
    int     (* timercallBack)(fw_timer_id_t, void*);
    fw_timer_id_t   TimerId;
}tNode;

struct tTIMER
{
    DLIST       TimerList;
};

int fwUpdateCallbackFuncs(tFdNode* listNode,unsigned int event);
int fwProcessData( unsigned int appid, int num, fd_set *fdvar,fd_set *fdvarwrite,fd_set *fdvarexception, DLIST* list);
fw_timer_id_t fwStartTimer( unsigned int appid,int timerval, int period, void * clientData,int (*) (fw_timer_id_t,void *));
int fwCancelTimer( unsigned int appid, fw_timer_id_t timerid);
int fwCancelTimerInternal( unsigned int appid, fw_timer_id_t timerid);

tNode *  fwListAddTimerEntry( unsigned int appid, int data, int periodic, void *  cdata, fw_timer_id_t tid,int (*fn)(fw_timer_id_t , void*) ) ;
int fwListRemoveTimerEntry( unsigned int appid, fw_timer_id_t TId);
int fwListRemoveTimerEntryInternal( unsigned int appid, fw_timer_id_t TId);
void fwPrintTimerList();
fw_timer_id_t fwSetTimerInternal( unsigned int appid, int timerval, int period,void * clientData, int (*) (fw_timer_id_t,void *), fw_timer_id_t tid);
struct timeval* fwchecktimer(unsigned int appid);

typedef int (*fw_multiplex_add_cb_t)(int, void*);
int fwMultiplexAdd( unsigned int appid, int socket,void * clientData, int (*) (int,void *));
void* fwMultiplexAdd_fast(unsigned int appid, int socket, void *cdata, int (*fn)(int, void*));
int fwMultiplexAddWrite( unsigned int appid, int socket,void * clientData, int (*) (int,void *));
int fwMultiplexAddException( unsigned int appid,int socket,void * clientData, int (*) (int,void *));
tFdNode* fwlistAddSocketEntry(int socket,unsigned int event,tFdNode* listNode);
int fwMultiplexRemove( unsigned int appid, int socket);
int fwMultiplexRemove_fast(unsigned int appid, void* node);
int fwMultiplexRemove_fast2(unsigned int appid, void* node);
int fwMultiplexRemoveWrite( unsigned int appid, int socket);
int fwMultiplexRemoveException( unsigned int appid, int socket);
int fwlistRemoveSocketEntry(unsigned int appid, int socket,unsigned int event);
int fwListRemoveSocketEntry_fast( unsigned int appid,unsigned int event,tFdNode* listNode);
int fwMultiplexRemoveException_fast(unsigned int appid, void* node);
int fwMultiplexRemoveWrite_fast(unsigned int appid, void* node);
void fwPrintSocketList();
int fwfdsetup(unsigned int appid, fd_set* fdvar, fd_set* fdvarwrite, fd_set* fdvarexception);
tFdNode* fwFindFdNode(unsigned int appid,int Fd);
int fwUpdateCallbackFuncs(tFdNode* listNode,unsigned int event);
#ifdef EPOLL
#define MAX_EPOLL_EVENTS 	64
int fwProcessData_epoll( unsigned int appid, int num_events, struct epoll_event* ev);
unsigned int fwEpollEventMapping(unsigned int event);
int fwEpollUpdateEvents(unsigned int appid,int Fd,tFdNode *listNode);
#endif
/************************************************************************************/
/***** Tasks ************************************************************************/
/************************************************************************************/

struct tTASK
{
	int           taskId;
	void *        clientData;
	int           ( * callBack)( int id,int result, void * clientData);
	pthread_t     threadId;
	int           pipeFd[2];
	void * 	params;
	int (*workFn)(void *);
	TASK *      nextEntry;
};

struct tTaskList
{
	TASK * list;
};


int fwStartTask( unsigned int appid, int (* workFn)( void * ), void * arg, void *cdata, int (*cb)(int, int, void *));
int fwCancelTask( unsigned int appid, int taskId);

TASK * fwListAddTaskEntry( int taskId, int pipeFd0 , int pipeFd1, void * cdata, int (*fn)(int, int, void * ), int (*workFn)(void
*), void * params );
int fwListRemoveTaskEntry( unsigned int appid, int taskId );
#ifdef __cplusplus
extern "C"
#endif
void * fwTaskThreadFn ( void * arg );
int fwReadFromTaskPipe (int fd, void * cData );
void fwPrintTaskList();
void fwPrintList();
int fwGetTaskId();

/************************************************************************************/
/***** Service **********************************************************************/
/************************************************************************************/

struct tSERVICE
{
	int           serviceId;
	void *        clientData;
	int           ( * callBack)( int id,int result, void * clientData);
	pthread_t     threadId;
	int           pipeFd[2];
	void * 	params;
	int (*workFn)(void *,  void *);
	SERVICE *      nextEntry;
};

struct tServiceList
{
	SERVICE * list;
};


int fwStartService(unsigned int appid, int (* workFn)( void *, void *), void * arg, void *cdata, int (*cb)(int, int, void
*));
int fwCancelService(unsigned int appid, int serviceId);
void * fwSync (int result, void * tnode );

SERVICE * fwListAddServiceEntry( int taskId, int pipeFd0 , int pipeFd1, void * cdata, int (*fn)(int, int, void * ), int (*
workFn)(void *, void *), void * params );
int fwListRemoveServiceEntry( unsigned int appid, int taskId );
#ifdef __cplusplus
extern "C"
#endif
void * fwServiceThreadFn ( void * arg );
int fwReadFromServicePipe (int fd, void * cData );
void fwPrintServiceList();
int fwGetServiceId();

/************************************************************************************/
/***** WorkProc *********************************************************************/
/************************************************************************************/

void fwRegisterWorkProc(void* clientdata, int (*cb)(void*) );
void fwRemoveWorkProc();

/************************************************************************************/
/***** Prompt ***********************************************************************/
/************************************************************************************/

void fwRegisterPrompt(void* clientdata, int (*cb)(void*) );

/************************************************************************************/
/***** Trace ************************************************************************/
/************************************************************************************/

void fwtraceinit();

int fwactualtrace(unsigned int appid,int level, char* formatString);
int fwstoretracedata(unsigned int appid, char* filename, int lineno);

void fwactualtracebytes(unsigned int appid, char* filename, int lineno, int level, unsigned char* buffer, unsigned long length);
char* fwtimestring();
int fwwrapcheck(unsigned int appid);
void dumpBytesTo(FILE *fp, unsigned char *D, unsigned long count);

/************************************************************************************/
/***** Mutex ************************************************************************/
/************************************************************************************/

void fwmutexinit(unsigned int appid);

/************************************************************************************/
/***** Semaphores *******************************************************************/
/************************************************************************************/

#define BIGCOUNT        10000

int fwsemget(key_t semKey, int option);
void fwlock(int id);
void fwunlock(int id);
int fwsemcreate(key_t key, int initval);
int fwsemopen(key_t key);
void fwsemrm(int passed_id);
void fwsemclose(int passed_id);
void fwsemwait(int passed_id);
void fwsemsignal(int passed_id);
void fwsemop(int passed_id, int value);

/************************************************************************************/
/***** FileUtil *********************************************************************/
/************************************************************************************/

int fileGetString(char* filename, char* begintoken, char delim, char* lval, char* rval);
int fileGetInt(char* filename, char* begintoken, char delim, char* lval, int* rval);
int fileGetFloat(char* filename, char* begintoken, char delim, char* lval, float* rval);


/************************************************************************************/
/***** StringUtil *******************************************************************/
/************************************************************************************/

void trim(char* buffer);
void ltrim(char* buffer);
void rtrim(char* buffer);
void readBuffer(unsigned char* buf, char* fileName, int* lengthOut);
void loadBuffer(unsigned char* buffer, char* fileName, int* lengthOut);
void getLvalRval(const char *buffer, char ch, char *lval, char *rval);
char* strreplace(char* source, char* search, char* replace);
char* float2Ascii(float num, char* buffer);
char* num2Ascii(int num, char* buffer);
void tokenize(char* buffer, char* delimstring, char tbuffer[][256], int* numtokens); /* kw fix */

/************************************************************************************/
/***** BufferUtil *******************************************************************/
/************************************************************************************/

void bufferAddUint8_linux(unsigned char* buffer, unsigned long long value);
void bufferAddUint4_linux(unsigned char* buffer, unsigned int value);
void bufferAddUint2_linux(unsigned char* buffer, unsigned short value);
void bufferAddUint1_linux(unsigned char* buffer, unsigned char value);
unsigned long long bufferGetUint8_linux(unsigned char* buffer);
unsigned int bufferGetUint4_linux(unsigned char* buffer);
unsigned short bufferGetUint2_linux(unsigned char* buffer);
unsigned char bufferGetUint1_linux(unsigned char* buffer);

/************************************************************************************/
/***** BitUtil **********************************************************************/
/************************************************************************************/

int isBitSetUint1(unsigned char source, int bitNumber);
void setBitUint1(unsigned char* source, int bitNumber);
void clearBitUint1(unsigned char* source, int bitNumber);
unsigned char getBits(unsigned char x, int p, int n);
unsigned char clearBits( unsigned char x);

/************************************************************************************/
/***** TimeUtil *********************************************************************/
/************************************************************************************/

time_t getEpoch();
time_t getEpochMs();
unsigned long long getEpochUs();
void getMmDdYyHhMiSsDateString(time_t epoch, char* dst);
time_t getEpochTimeFromString(char* rval);
int fwTimeLeftToAlignToWallClock( int referenceTime, int period);

/************************************************************************************/
/***** MathUtil *********************************************************************/
/************************************************************************************/

unsigned int upow(unsigned int num, unsigned int raisedto);
int genRandom(int l, int r);

extern void fwRegisterRpc(unsigned int appid);
extern void fwRegisterRpc(unsigned int appid);
/* FWT Changes Start */
#define MAX_APP_ID 80
#define DYN_APP_IDS 20
#define DYN_APP_ID_START (MAX_APP_ID+1)
#define DYN_APP_ID_END MAX_APP_ID+DYN_APP_IDS
#define MAX_TOTAL_APP_ID MAX_APP_ID+DYN_APP_IDS
#define APP_PORT_BASE	6000

typedef struct
{
	unsigned int src_app_id;
	unsigned int dst_app_id;
	unsigned int msg_length;
	unsigned int msg_type;
}fw_ipc_hdr_t;

typedef struct
{
	fw_ipc_hdr_t hdr;
	char payload[1];
}ipc_packet_t;

typedef int (*ipc_callback_t)(ipc_packet_t*);
typedef void (*tipc_callback_t)(char* payload);
int ipc_msg_snd(ipc_packet_t*);

/************************************************************************************/
/***** Buffer Management ************************************************************/
/************************************************************************************/
#define MAX_BUFFER_POOLS        80
#define FW_MAGIC_NUM_SIZE       sizeof(unsigned short)
#define FW_MAGIC_NUM            0xaaaa

typedef struct __fw_buffer_hdr_t__
{
	NODE    anchor;
	struct __fw_buffer_hdr_t__* pnext;
	int     poolid;
	int     busyflag;
	unsigned int             appid;
	char    *func;
	int     line;
	int     *pad1;
	int     *pad2;
}fw_buffer_hdr_t;

typedef struct
{
	fw_buffer_hdr_t*        pfirst;
	fw_buffer_hdr_t*        pstart;
	int                     size;
	int                     num_buffers;
	int                     threshold;
}fw_buffer_pool_t;

typedef struct
{
	int size;
	int num_buffers;
	char *useBuff;
}fw_buffer_config_t;

typedef struct __ipc_buffer_hdr_t__
{
	struct __ipc_buffer_hdr_t__* pnext;
	int     poolid;
	int     busyflag;
	int     pad;
	unsigned int             appid;
}ipc_buffer_hdr_t;

typedef struct
{
	ipc_buffer_hdr_t*        pfirst;
	int                     size;
	int                     num_buffers;

}ipc_buffer_pool_t;

typedef struct
{
	int size;
	int num_buffers;
}ipc_buffer_config_t;

#define BUFF_NO_DEBUG 0
#define BUFF_DEBUG    1

#define fw_buffer_get(appid, size)\
	fw_buffer_get_dbg(__FILE__, __LINE__, appid, size)
#define fw_buffer_release(appid, size)\
	fw_buffer_release_dbg(__FILE__, __LINE__, appid, size)

void fw_buffer_init(fw_buffer_config_t*, int numentries);
void fw_buffer_pool_init(fw_buffer_pool_t*, fw_buffer_config_t*, int poolid);
char* fw_buffer_get_dbg(char *func, int line, unsigned int appid, int size);
int fw_buffer_release_dbg(char *func, int line, unsigned int appid, char*);
void fw_buffer_stat();

void ipc_buffer_init(ipc_buffer_config_t*, int numentries);
void ipc_buffer_pool_init(ipc_buffer_pool_t*, ipc_buffer_config_t*, int poolid);
ipc_packet_t* ipc_buffer_get(unsigned int appid, int size);
int ipc_buffer_release(unsigned int appid, ipc_packet_t *);
void ipc_buffer_stat();
int ipc_buffer_change_owner(unsigned int appid, ipc_packet_t*);
int fw_get_appid(unsigned int *appid);
int fw_return_appid(unsigned int appid);
int st_get_terminal_index(int *p_index);
int stInit(char *prompt, char *welcome_disclaimer);
int st_get_index_of_command(int *p_index);
// ST CHANGES
#define ST_APP_ID 0
#define ST_TERMINAL_PORT 5353
#define MAX_ST_SESSIONS 5
typedef int
(*CmdCallBackFnType) (int argc, char ** argv);

typedef struct
{
	char      *cmdName;
	char      *cmdHelp;
	CmdCallBackFnType  callBack;
}st_command_record;

#define LOGIN_STATE             1
#define PASSWORD_STATE          2
#define AUTHENTICATED_STATE     3

typedef struct
{
    unsigned int appid;
    unsigned int cmd_appid;
    int sockfd;
    int count;
    int flag;
    pthread_t Ttid;
    pthread_t Ctid;
    pthread_t cmd_tid;
    char command[1024];
    char g_prompt[100];
    int state;
    char login[1024];
    char password[1024];
    unsigned char lastChar;
}st_terminal_data;

extern st_terminal_data g_st_terminal_data[MAX_ST_SESSIONS];
extern int st_commands_index ;
#define ST_MAX_COMMANDS 1024
extern st_command_record g_st_command_table[ST_MAX_COMMANDS];
extern char g_sw_version[100];

typedef struct
{
    unsigned int current_index;
#define ST_MAX_HISTORY_CMDS 50
    char command[ST_MAX_HISTORY_CMDS][256];
}st_history_cmd_t;

#define pprintf(str)\
	do{\
		int st_index;\
		void *st_ptr;\
		if(1 == st_get_index_of_command(&st_index))\
		{\
			st_ptr = (void *)logst_proxy_fn str;\
			if(st_ptr != NULL)\
			{\
				if(0 != g_st_terminal_data[st_index].sockfd)\
				{\
                                         tcpWrite(g_st_terminal_data[st_index].sockfd,(char*)st_ptr,strlen((char*)st_ptr)+1);\
                                }\
				free(st_ptr);\
			}\
		}\
	}while(0)
void *ST_HANDLER(void *args);
int fw_set_log_level(unsigned int appid, int level);
int fw_display_log_leve(unsigned int appid);
typedef struct
{
    TIMER           timer;
    struct timeval T;
    DLIST          socklist;
    DLIST      socklistwrite;
    DLIST      socklistexception;
    pthread_mutex_t fwsocketMu;
    pthread_mutex_t fwtimerMu;
    pthread_mutex_t fwtraceMu;
    int             NumOfEntry;
    int         ipc_socket;
    ipc_callback_t ipc_callback;
    tipc_callback_t tipc_callback;
    int __tracelevel__;
    char __filename__[1024];
    int __lineno__;
    char thread_name[1024];
    DLIST           buff_list;
    pthread_t tid;
    int EpollFd;
}app_map_t;

extern app_map_t g_app_map[MAX_TOTAL_APP_ID];
char *logst_proxy_fn(char *fmt,...);
extern int g_elog_flag ;
char *elog_end();
int elog_get_log_from_filename( char *search_file_name );
int elog_display( char *search_filename);
int fwgettracelevel(int appid);

extern int elog_flag ;
#define DATA(x,y) "~~elog~~:" x ":" #y ":"
#define XDATA(x,y) DATA(x,y)
#ifndef NOTRACE
#define fwtrace(appid,level,str) do{int lineno=__LINE__;\
    char filename[] = __FILE__;\
	char *str1 =XDATA(__FILE__,__LINE__) #str ":";\
        char* T;\
	if(!fwwrapcheck(appid))\
		break;\
    if( g_app_map[appid].__tracelevel__ >= level || g_elog_flag)\
    {\
	if(elog_flag)\
		{\
		if(!elog_isset_bit_map((unsigned char*)str1) && g_elog_flag)\
			break;\
		}\
		printf("[%lu]", pthread_self());\
		printf("[%u]", appid);\
        T = fwtimestring();\
        if(T)\
        {\
            printf("[%s]", T);\
            printf("[%s]", filename);\
            printf("[%d]", lineno);\
            free(T);\
        }\
    printf str;\
	}\
}while(0);

#define fwtracebytes(appid, level, str ,length )do{\
	char* T;\
	char *str1 =XDATA(__FILE__,__LINE__) "\"tracebyte\":";\
    if(fwwrapcheck(appid))\
    {\
	    if(g_app_map[appid].__tracelevel__ >= level || g_elog_flag)\
	    {\
		if(elog_flag)\
			{\
			if(!elog_isset_bit_map((unsigned char*)str1) && g_elog_flag)\
				break;\
			}\
		printf("[%lu]", pthread_self());\
		printf("[%u]", appid);\
		T = fwtimestring();\
		if(T)\
		{\
		    printf("[%s]", T);\
		    printf("[%s]", __FILE__);\
		    printf("[%d]\n", __LINE__);\
		    free(T);\
		}\
		dumpBytesTo(stdout, str, length);\
	    }\
    }\
    fflush(stdout);\
	}while(0);


//fwactualtracebytes(a,__FILE__, __LINE__, b, c, d)
#else
#define fwtrace(a,b,c) /* fwstoretracedata(__FILE__, __LINE__)+fwactualtrace */
#define fwtracebytes(a, b, c,d) /* fwactualtracebytes(__FILE__, __LINE__, a, b, c) */
#endif
void pdumpBytes(unsigned char *D, unsigned long count);
#define MAX_FILE_SIZE 250
#define MAX_DATA_LENGTH 250
#define MAX_LINE_NO_LENGTH 10
#define MAX_LOG_FILE_SIZE 4000000 /* 4MB */

int elog_getData(unsigned char *address, char *file_name, int *lineno, char *data);
unsigned char* elog_getAddr(char *search_file_name, int lineno);
void elog_disp_bit_map();
int elog_isset_bit_map(unsigned char *p_curr);
int elog_set_bit_map(unsigned char *p_curr);
int elog_reset_bit_map(unsigned char *p_curr);
void myfunc(char* string, int opcode);
int fw_tid_to_appid();
void shell_run_cmd(char* cmd);
/* FWT Changes End */

/************************************************************************************/
/***** IPC for Threads **************************************************************/
/************************************************************************************/

#define TIPC_NUM_BD	1

typedef struct
{
	char ctl;
	int app_id;
	char* payload;
}tipc_bd_t;

typedef struct
{
	int rindex;
	int windex;
}tipc_rw_t;

typedef struct
{
	int po_write_ok[MAX_APP_ID];
	int po_write_drops[MAX_APP_ID];
	int app_send_ok[MAX_APP_ID][MAX_APP_ID];
	int app_send_drops[MAX_APP_ID][MAX_APP_ID];
}tipc_counters_t;


extern tipc_bd_t g_tipc_bd[MAX_APP_ID][TIPC_NUM_BD];
extern tipc_rw_t g_tipc_rw[MAX_APP_ID];

extern tipc_bd_t g_po_tipc_bd[MAX_APP_ID][TIPC_NUM_BD];
extern tipc_rw_t g_tipc_po_rw[MAX_APP_ID];
extern int g_tipc_read_block[MAX_APP_ID];
extern int g_tipc_write_block[MAX_APP_ID];
extern tipc_counters_t g_tipc_counters;

int tipc_init();
int tipc_send(int src_app_id, int dst_app_id, char* payload);
char* tipc_receive(int appid);
int tipc_po_send(int src_app_id, int dst_app_id, char* payload);
void tipc_po_receive();
int tipc_po_process_queue(int appid);
void * tipc_po_thread(void * data);
void tipc_read_block(int appid, int flag);
void tipc_write_block(int appid, int flag);
int tipc_counters_disp(int argc, char** argv);
int reset_tipc_counters(int argc, char** argv);
#ifdef EPOLL
extern int EpollFd;
#endif
int fw_validate_user(char* user, char* password);
void  shell_add_cmd(char* cmd_name , char *desc , CmdCallBackFnType funcPtr);
int tapSocket(char* ifname);
void tapSetMac(char* ifname, unsigned char* mac);
int tapRead(int fd, char* ptr);
int tapWrite(int fd, char* ptr);
int udpWrite6(int fd, char* remoteipaddress, int remotePort, char* data, int length);
int udpRead6(int fd, char* data);
int udpSocket6(int localPort);
int udpReadFrom6(int fd, char* data, char* ip, unsigned short* port);
int udpSocketExt(char* localip, int localPort);
int udpSocketExt6(char* localip, int localPort);
void stringkey2hex(char* key, unsigned char* digestkey, int * digestkeylength);
int fw_valid_add_for_rel(char *buff);
int extract_ipv4_interface(char* ipv4_addr, char* interface);
int search_interface_ipv4(FILE* fpt, char* ip_addr, char* interface);
int extract_src_ipv4_from_interface(char* interface);
int extract_ipv6_interface(char* ipv6_addr, char* interface);
int search_interface_ipv6(FILE* fpt, char* ip_addr, char* interface);
int search_default_interface(FILE* fpt, char* interface);
void form_ip_address_with_subnet(unsigned char* ip_addr, unsigned int subnet);
void extract_src_ipv6_from_interface(char* interface, unsigned char* src_ip);
int fw_init_ipc_socket();
int fw_init_ipc_ack_socket();
#define IPV4    4
#define IPV6    6
int fw_core_count();
int fw_raw_socket(int protocol, char* ip_addr);
int fw_raw_socket6(int protocol, char* ip_addr);
int fw_raw_read(int fd, char* data);
int fw_raw_read6(int fd, char* data);
int fw_raw_write(int fd, char* remoteipaddress,char* data, int length);
int fw_raw_write6(int fd, char* remoteipaddress,char* data, int length);
int fw_read6_ext(int fd, char* buffer, char* srcip, char* dstip, unsigned short *srcport, unsigned int *hoplimit, unsigned int *tos);
int fw_read_ext(int fd, char* buffer, char* srcip, char* dstip, unsigned short *srcport, unsigned int *ttl, unsigned int *tos);
int fw_write6_ext(int fd, char* buffer, unsigned int tos, char *remoteipaddress, unsigned short remotePort,int payload_length);
/** changes start for bug 155 **/
int linux_myendian();
void rfcstring2hex(char* string, unsigned char* buffer, int allowedlength, int * loadedlength);
/** change end for bug 155 **/
/***********************************************************************************/


/************************************************************************************/
/***** Pool *************************************************************/
/************************************************************************************/

typedef struct
{
	DLIST		     L;	
}fw_single_buffer_pool_t;

typedef struct __fw_single_buffer_hdr_t__
{
        NODE    	anchor;
	unsigned char	data[0];
}fw_single_buffer_t;


unsigned long long fw_single_buffer_pool_init(fw_single_buffer_pool_t* p, unsigned long long element_size, unsigned long long num_elements);
void* fw_single_buffer_alloc(fw_single_buffer_pool_t* p);
void fw_single_buffer_free(fw_single_buffer_pool_t* p, void* buf);

/************************************************************************************/
/***** Hash Tables ******************************************************************/
/************************************************************************************/

typedef struct
{
	DLIST L;
}fw_hash_bucket_t;

typedef struct
{
	NODE anchor;
	unsigned char data[0];   /* key value goes here */
}fw_hash_node_t;

typedef struct
{
	unsigned long long num_elements; /* Total elements present in hash */
	unsigned long long num_buckets; /* Number of Hash Buckets */
	unsigned long long key_size;
	unsigned long long value_size;
	unsigned long long current_elements; /* Number of elements present in hash at the moment */
	unsigned long long mem_hash_nodes; /* memory allocated to nodes in hash which hold pointers to key value holdings */
	unsigned long long mem_hash_buckets; /* memory allocated to buckets in hash */
	fw_single_buffer_pool_t p_hash_nodes;
	fw_hash_bucket_t* p_hash_bucket; 
}fw_hash_t;

typedef void (*fw_hash_walk_callback_t)(void* key, void* val, void* arg);

int fw_hash_init(fw_hash_t* h, unsigned long long num_elements, unsigned long long num_buckets, unsigned long long key_size, unsigned long long value_size);
int fw_hash_add(fw_hash_t* h, void* key, void* val);
int fw_hash_del(fw_hash_t* h, void* key);
int fw_hash_search(fw_hash_t* h, void* key, void* val);
void fw_hash_walk(fw_hash_t* h, fw_hash_walk_callback_t c, void* arg);
void fw_hash_debug_print(fw_hash_t* h);
void fw_hash_bucket_print(fw_hash_t* h);
int history_cb(int argc, char** argv);
int is_command_repleated(char* current_cmd);

/** Timer Wheel **/

#define INVALID_SPOKE 0xFFFFFFFFFFFFFFFFULL
#define FW_TIMER_WHEEL_MEMORY_ALLOC_COUNT 64
typedef struct
{
    void*  cdata;
    void*  timerId;
}fw_timer_wheel_expired_timer_t;

typedef struct
{
    unsigned long long                  interval_us;
    unsigned long long                  spokes;
    unsigned long long                  current_spoke;
    unsigned long long                  last_rotation_epoch_us;
    DLIST*                              pLists;   /** there will be as many lists required as the number of spokes **/
    DLIST                               nowList;   /** now List will contain the timers which will expire immediately  **/
    unsigned long long                  horizon_multiplier;
    pthread_mutex_t				lock;
    int					inside_callback;
    
}fw_timer_wheel_t;

typedef void
(*fw_timer_wheel_callback_t) (fw_timer_wheel_expired_timer_t *timerData); /** first arg is timer id, second arg is client data **/

typedef struct
{
    NODE                        __anchor__;
    void*                       cdata;
    fw_timer_wheel_callback_t  cb; 
    unsigned long long          spoke;
    unsigned long long rotation_count;
}fw_timer_wheel_spoke_payload_t;

fw_timer_wheel_t* fw_timer_wheel_init(unsigned long long interval_us, unsigned long long spokes,unsigned long long horizon_multiplier);
void fw_timer_wheel_lock_init(fw_timer_wheel_t* wheel);
void fw_timer_wheel_lock_deinit(fw_timer_wheel_t* wheel);
void fw_timer_wheel_lock(fw_timer_wheel_t* wheel);
void fw_timer_wheel_unlock(fw_timer_wheel_t* wheel);
void* fw_timer_wheel_timer_head_start(fw_timer_wheel_t* wheel,void* cdata,fw_timer_wheel_callback_t cb);
void* fw_timer_wheel_timer_start(fw_timer_wheel_t* wheel, unsigned long long value_us, void* cdata, fw_timer_wheel_callback_t cb);
void fw_timer_wheel_timer_stop(fw_timer_wheel_t* wheel, void* timerid);
void fw_timer_wheel_destroy(fw_timer_wheel_t* wheel);
void fw_timer_wheel_rotate(fw_timer_wheel_t* wheel);
unsigned long long fw_timer_wheel_rotate2(fw_timer_wheel_t* wheel, fw_timer_wheel_expired_timer_t **timerData,unsigned long long max_expirations);
void fw_timer_wheel_rotate_to_update_now_list(fw_timer_wheel_t* wheel);
void fw_free_timer_id_data(fw_timer_wheel_expired_timer_t *timerData,unsigned long long count);
void common_mod_shared_pool_allocate_memory_chunk();
unsigned short fp_mod_get_udp_psd_cksum(char* buffer);
unsigned short fp_mod_get_udp_psd_cksum6(char* buffer);
unsigned short ipUtilIpHdrChecksumGeneric(char* buffer);

/** Pool implementation **/
typedef struct
{
	void* mem_base;
	char  name[256];
	unsigned long long current_head;
	unsigned long long current_tail;
	unsigned long long element_size;
	unsigned long long n_elements;
	unsigned long long n_allocated_elements;
}fw_indexed_pool_t;

typedef struct
{
	unsigned long long next;
	unsigned long long prev;
	unsigned long long self_index;
	unsigned char allocated_flag;
        unsigned long long pad;
	unsigned char data[0];
}fw_indexed_pool_element_t;

int fw_indexed_pool_init(fw_indexed_pool_t* p, unsigned long long payload_size, unsigned long long n_elements, char* name);
void* fw_indexed_pool_alloc(fw_indexed_pool_t* p);
unsigned long long fw_indexed_pool_max_elements(fw_indexed_pool_t* p);
unsigned long long fw_indexed_pool_allocated_elements(fw_indexed_pool_t* p);
void fw_indexed_pool_free_head(fw_indexed_pool_t* p, void* element);
void fw_indexed_pool_free_tail(fw_indexed_pool_t* p, void* element);
unsigned long long fw_indexed_pool_get_element_index(fw_indexed_pool_t* p, void* element);
void* fw_indexed_pool_get_element_at_index(fw_indexed_pool_t* p, unsigned long long index);
unsigned char fw_indexed_pool_is_index_allocated(fw_indexed_pool_t* p, unsigned long long index);
unsigned char fw_indexed_pool_is_index_valid(fw_indexed_pool_t* p, unsigned long long index);
unsigned char fw_indexed_pool_is_element_part_of_pool(fw_indexed_pool_t* p, void* element);
void fw_indexed_pool_destroy(fw_indexed_pool_t* p);



/**http2 boundary data parsing**/
typedef struct
{
	char content_type[256];
	char content_id[256];
	unsigned char data[65536];
	unsigned int size;
}fw_boundary_token_t;

void fw_boundary_process_collected_data(unsigned char* collected, unsigned int collected_size, fw_boundary_token_t* t);
unsigned int fw_boundary_parse(void* input, unsigned int length_input, char* boundary, fw_boundary_token_t* t);
/**http2 boundary data parsing end**/
#endif
