/********************************************************************
 *
 *    FILE NAME    : sp_fmwk.c
 *
 *    DESCRIPTION  : The file contains functions for handling the
 *    sockets entries and buffers allocation and deacllocation.
 *
 *    Revision History
 *  -----------------------------------------------------------------
 *    DATE            NAME                REFERENCE        REASON
 *    8/8/2018        Inder/               -             Initial Draft
 *                    Prashant Upadhyaya                   for POC
 *
 *    Copyright , Truring Softek, 2018
 *******************************************************************/

#ifndef LINUX_DP
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif
#include <sp_fmwk.h>
#include <sys/syscall.h>

/* Thread Fw Start */
app_map_t g_app_map[MAX_TOTAL_APP_ID];
int g_buff_debug = BUFF_NO_DEBUG;
int g_fwRpcRegistered[MAX_TOTAL_APP_ID] =
    {
        0};
fw_buffer_pool_t fw_buffer_pool[MAX_BUFFER_POOLS];
int fw_buffer_busy[MAX_BUFFER_POOLS];
int fw_num_buffer_pools;
ipc_buffer_pool_t ipc_buffer_pool[MAX_BUFFER_POOLS];
int ipc_buffer_busy[MAX_BUFFER_POOLS];
int ipc_num_buffer_pools;
unsigned int g_curr_dyn_app_id = DYN_APP_ID_START;
int g_dyn_flag[DYN_APP_IDS] = {0};
int g_terminal_flag[MAX_ST_SESSIONS] = {0};
st_terminal_data g_st_terminal_data[MAX_ST_SESSIONS];
st_history_cmd_t g_history_cmd;
int no_of_sessions;
int st_commands_index = 0;
st_command_record g_st_command_table[ST_MAX_COMMANDS];
char g_sw_version[100] = "FW v0.1";
char g_prompt[100] = "DFWSHELL$ ";
char g_welcome_disclaimer[1024] = "Default Disclaimer";
int g_elog_flag = 0;
unsigned char *p_low = NULL, *p_high = NULL;
char *bit_map;
int bit_map_size = 0;
char *global = "~~elog~~:";
extern int _end[];
extern int _start[];
extern int _edata[];
extern int _etext[];
extern int _init[];
extern int _fini[];
extern int __data_start[];
int g_solaris = 0;
int elog_flag = 0;
/** Changes Start for Bug 234 **/
struct sigaction __tcpalarm;
/** Changes End for Bug 234 **/
/* Thread Fw End */

pthread_mutex_t fwsocketMu;
pthread_mutex_t fwqueueMu;
pthread_mutex_t fwtaskMu;
pthread_mutex_t fwserviceMu;
pthread_mutex_t fwtimerMu;
pthread_mutex_t fwtraceMu;
pthread_mutex_t fwbufferMu;
pthread_mutex_t ipcbufferMu;
pthread_mutex_t fwfileMu;

int fwRpcRegistered = 0;
TIMER timer;
FdList socklist;
qList mqlist;
TaskList tlist;
ServiceList servicelist;
int NumOfEntry;
int numberOfTask;
int numberOfService;
int verbosity;
int fwdebug = 0;
int __tracelevel__;
int __tracesize__;
char __tracefile__[1024];
char __filename__[1024];
int __lineno__;
int fwtimercbcalled;

struct sembuf op_lock[2];
struct sembuf op_endcreate[2];
struct sembuf op_open[1];
struct sembuf op_close[3];
struct sembuf op_unlock[1];
struct sembuf op_op[1];

static char ftpReplyString[4096];
static int ftpDebugFlag = 0;
static int yes = 1;

int (*pfwprompt)(void *clientdata);
void *fwpromptclientdata;

int (*pfwworkproc)(void *clientdata);
void *fwworkprocclientdata;

unsigned int ClearBitMaskUint1[] =
    {
        0xFE,
        0xFD,
        0xFB,
        0xF7,
        0xEF,
        0xDF,
        0xBF,
        0x7F};

unsigned int SetBitMask[] =
    {
        1,
        2,
        2 * 2,
        2 * 2 * 2,
        2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2,
        2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2};

/** threads ipc begin **/
/* each app bd queue */
tipc_bd_t g_tipc_bd[MAX_APP_ID][TIPC_NUM_BD];
tipc_rw_t g_tipc_rw[MAX_APP_ID];

/* postoffice queues for each thread */
tipc_bd_t g_po_tipc_bd[MAX_APP_ID][TIPC_NUM_BD];
tipc_rw_t g_tipc_po_rw[MAX_APP_ID];
int g_tipc_read_block[MAX_APP_ID];
int g_tipc_write_block[MAX_APP_ID];
tipc_counters_t g_tipc_counters;

int tipc_init()
{
    /* create the post office thread */
    pthread_t id;

    shell_add_cmd("tipc_counters", "tipc_counters", tipc_counters_disp);
    shell_add_cmd("reset_tipc_counters", "reset_tipc_counters", reset_tipc_counters);
    if (pthread_create(&id, NULL, tipc_po_thread, NULL) < 0)
    {
        fprintf(stderr, "could not start po thread\n");
        exit(1);
    }
    return 0;
}

int tipc_timer_cb(fw_timer_id_t tid, void *cdata)
{
    char *payload;
    int appid;

    appid = *(int *)cdata;

    payload = tipc_receive(appid);

    while (payload != NULL)
    {
        g_app_map[appid].tipc_callback(payload);
        payload = tipc_receive(appid);
    }
    return 0;
}

void tipc_register_callback(int appid, tipc_callback_t C)
{
    int *app_id;

    g_app_map[appid].tipc_callback = C;
    app_id = (int *)malloc(sizeof(int));
    if (NULL != app_id)
    {
        *app_id = appid;
        fwStartTimer(appid, 2, 1, (void *)app_id, tipc_timer_cb);
    }
    else
    {
        pprintf(("app_id Memory allocation failure "));
    }
}

int tipc_counters_disp(int argc, char **argv)
{
    int i, j;

    for (i = 0; i < MAX_APP_ID; i++)
    {
        if (g_tipc_counters.po_write_ok[i] != 0)
            pprintf(("po_write_ok[%d]: %d\n", i, g_tipc_counters.po_write_ok[i]));
    }

    for (i = 0; i < MAX_APP_ID; i++)
    {
        if (g_tipc_counters.po_write_drops[i] != 0)
            pprintf(("po_write_drops[%d]: %d\n", i, g_tipc_counters.po_write_drops[i]));
    }

    for (i = 0; i < MAX_APP_ID; i++)
    {
        for (j = 0; j < MAX_APP_ID; j++)
        {
            if (g_tipc_counters.app_send_ok[i][j] != 0)
                pprintf(("app_send_ok[%d][%d]: %d\n", i, j, g_tipc_counters.app_send_ok[i][j]));
        }
    }

    for (i = 0; i < MAX_APP_ID; i++)
    {
        for (j = 0; j < MAX_APP_ID; j++)
        {
            if (g_tipc_counters.app_send_drops[i][j] != 0)
                pprintf(("app_send_drops[%d][%]: %d\n", i, j, g_tipc_counters.app_send_drops[i][j]));
        }
    }
    return 0;
}

int reset_tipc_counters(int argc, char **argv)
{
    memset(&g_tipc_counters, 0, sizeof(g_tipc_counters));
    return 0;
}

void tipc_read_block(int appid, int flag)
{
    g_tipc_read_block[appid] = flag;
}

void tipc_write_block(int appid, int flag)
{
    g_tipc_write_block[appid] = flag;
}

int tipc_send(int src_app_id, int dst_app_id, char *payload)
{
    /* post on the corresponding po queue */
    int windex;

    windex = g_tipc_po_rw[src_app_id].windex;

    if (g_tipc_write_block[src_app_id])
    {
        while (g_po_tipc_bd[src_app_id][windex].ctl != 0)
        {
            usleep(4);
        }
    }

    if (g_po_tipc_bd[src_app_id][windex].ctl == 0)
    {
        g_po_tipc_bd[src_app_id][windex].payload = payload;
        g_po_tipc_bd[src_app_id][windex].app_id = dst_app_id;
        g_po_tipc_bd[src_app_id][windex].ctl = 1;
        g_tipc_po_rw[src_app_id].windex++;
        if (g_tipc_po_rw[src_app_id].windex == TIPC_NUM_BD)
        {
            g_tipc_po_rw[src_app_id].windex = 0;
        }
        g_tipc_counters.app_send_ok[src_app_id][dst_app_id]++;
    }
    else
    {
        g_tipc_counters.app_send_drops[src_app_id][dst_app_id]++;
        return 0;
    }

    return 1;
}

char *tipc_receive(int appid)
{
    int rindex;
    char *payload;

    /* this is from self queue */
    rindex = g_tipc_rw[appid].rindex;
    if (g_tipc_read_block[appid])
    {
        while (g_tipc_bd[appid][rindex].ctl == 0)
        {
            usleep(4);
        }
    }

    if (g_tipc_bd[appid][rindex].ctl != 0)
    {
        payload = g_tipc_bd[appid][rindex].payload;
        g_tipc_bd[appid][rindex].ctl = 0;
        g_tipc_rw[appid].rindex++;
        if (g_tipc_rw[appid].rindex == TIPC_NUM_BD)
        {
            g_tipc_rw[appid].rindex = 0;
        }
        return payload;
    }
    else
    {
        return NULL;
    }
    return NULL;
}

int tipc_po_send(int src_app_id, int dst_app_id, char *payload)
{
    int windex;

    windex = g_tipc_rw[dst_app_id].windex;
    if (g_tipc_bd[dst_app_id][windex].ctl == 0)
    {
        g_tipc_bd[dst_app_id][windex].payload = payload;
        g_tipc_bd[dst_app_id][windex].app_id = src_app_id;
        g_tipc_bd[dst_app_id][windex].ctl = 1;
        g_tipc_rw[dst_app_id].windex++;
        if (g_tipc_rw[dst_app_id].windex == TIPC_NUM_BD)
        {
            g_tipc_rw[dst_app_id].windex = 0;
        }
        g_tipc_counters.po_write_ok[dst_app_id]++;
    }
    else
    {
        g_tipc_counters.po_write_drops[dst_app_id]++;
        return 0;
    }

    return 1;
}

void tipc_po_receive()
{
    /* iterate over all the queues */
    int i;

    for (i = 0; i < MAX_APP_ID; i++)
    {
        while (tipc_po_process_queue(i))
            ;
    }
}

int tipc_po_process_queue(int appid)
{
    int rindex;
    int dst_app_id;
    char *payload;

    rindex = g_tipc_po_rw[appid].rindex;
    if (g_po_tipc_bd[appid][rindex].ctl != 0)
    {
        dst_app_id = g_po_tipc_bd[appid][rindex].app_id;
        payload = g_po_tipc_bd[appid][rindex].payload;
        g_po_tipc_bd[appid][rindex].ctl = 0;
        g_tipc_po_rw[appid].rindex++;
        if (g_tipc_po_rw[appid].rindex == TIPC_NUM_BD)
        {
            g_tipc_po_rw[appid].rindex = 0;
        }
        tipc_po_send(appid, dst_app_id, payload);
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

void *tipc_po_thread(void *data)
{
    /** infinite loop with wait **/
    while (1)
    {
        tipc_po_receive();
        usleep(1);
    }
}

/** threads ipc end **/

void fwInit(unsigned int appid)
{
    char tmp[16];
    char *env_temp = NULL;
    signal(SIGPIPE, SIG_IGN);
#ifdef EPOLL
    g_app_map[appid].EpollFd = epoll_create(1024);
    if (g_app_map[appid].EpollFd < 0)
    {
        perror("Epoll");
        exit(1);
    }
#endif
    fwmutexinit(appid);

    g_app_map[appid].NumOfEntry = 0;
    numberOfTask = 0;
    numberOfService = 0;
    lstInit(&(g_app_map[appid].timer.TimerList));
    lstInit(&g_app_map[appid].socklist);
    lstInit(&g_app_map[appid].socklistwrite);
    lstInit(&g_app_map[appid].socklistexception);

    g_app_map[appid].tid = pthread_self();
    lstInit(&(g_app_map[appid].buff_list));
    mqlist.list = NULL;
    tlist.list = NULL;
    servicelist.list = NULL;
    strcpy(tmp, "");
    env_temp = getenv("DEBUG");
    if (env_temp != NULL)
    {
        strncpy(tmp, env_temp, sizeof(tmp) - 1);
        tmp[sizeof(tmp) - 1] = '\0';
        if (strcmp(tmp, "1") == 0)
            fwdebug = 1;
        else
            fwdebug = 0;
    }
    else
        fwdebug = 0;

    fwtimercbcalled = 0;

    pfwprompt = NULL;
    fwpromptclientdata = NULL;

    pfwworkproc = NULL;
    fwworkprocclientdata = NULL;

    /** Changes Start for Bug 234 **/
    __tcpalarm.sa_handler = sockalarmhandler;
    sigaction(SIGALRM, &__tcpalarm, NULL);
    /** Changes End for Bug 234 **/
}

void fwDeinit(unsigned int appid)
{
}

void shellInit(unsigned int appid)
{
    char tmp[16];
    char *env_temp = NULL;
    fwmutexinit(appid);

    g_app_map[appid].NumOfEntry = 0;
    numberOfTask = 0;
    numberOfService = 0;
    lstInit(&g_app_map[appid].timer.TimerList);
    lstInit(&g_app_map[appid].socklist);
    lstInit(&g_app_map[appid].socklistwrite);
    lstInit(&g_app_map[appid].socklistexception);

    g_app_map[appid].tid = pthread_self();
    mqlist.list = NULL;
    tlist.list = NULL;
    servicelist.list = NULL;
    strcpy(tmp, "");
    env_temp = getenv("DEBUG");
    if (env_temp != NULL)
    {
        strncpy(tmp, env_temp, sizeof(tmp) - 1);
        tmp[sizeof(tmp) - 1] = '\0';
        if (strcmp(tmp, "1") == 0)
            fwdebug = 1;
        else
            fwdebug = 0;
    }
    else
        fwdebug = 0;

    fwtimercbcalled = 0;

    pfwprompt = NULL;
    fwpromptclientdata = NULL;

    pfwworkproc = NULL;
    fwworkprocclientdata = NULL;
#ifdef EPOLL
    g_app_map[appid].EpollFd = epoll_create(1024);
    if (g_app_map[appid].EpollFd < 0)
    {
        perror("Epoll");
        exit(1);
    }
#endif
}

void fwmutexinit(unsigned int appid)
{
    if (pthread_mutex_init(&(g_app_map[appid].fwsocketMu), NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&fwqueueMu, NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&fwtaskMu, NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&fwserviceMu, NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&(g_app_map[appid].fwtimerMu), NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&(g_app_map[appid].fwtraceMu), NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
    if (pthread_mutex_init(&(fwfileMu), NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }
}

/* data - period of timer, period if periodic or not, cdata - date to written on port*/
tNode *fwListAddTimerEntry(unsigned int appid, int data, int period, void *cdata, fw_timer_id_t tid, int (*fn)(fw_timer_id_t, void *))
{
    tNode *listNode;
    tNode *tscan;
    NODE *scan;

    if (fwdebug)
        printf(" Enter fwListAddTimerEntry() [1]\n");

    if (tid == NULL)
    {
        listNode = (tNode *)malloc(sizeof(tNode));
    }
    else
    {
        listNode = (tNode *)tid;
    }

    if (listNode == NULL)
    {
        printf("fwListAddTimerEntry: Unable to get Memory\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwtimerMu));
        return (NULL);
    }
    listNode->epoch = getEpochMs() + data;
    listNode->value = data;
    listNode->Period = period;
    listNode->clientData = cdata;
    listNode->timercallBack = fn;
    listNode->TimerId = listNode;

    scan = lstLast(&g_app_map[appid].timer.TimerList);
    while (scan != NULL)
    {
        tscan = (tNode *)scan;
        if (tscan->epoch > listNode->epoch)
        {
            scan = lstPrevious(scan);
            continue;
        }
        else
        {
            if (scan == lstLast(&g_app_map[appid].timer.TimerList))
            {
                lstAdd(&g_app_map[appid].timer.TimerList, (NODE *)listNode);
            }
            else
            {
                lstInsert(&g_app_map[appid].timer.TimerList, scan, (NODE *)listNode);
            }
            if (fwdebug)
                printf(" Exit fwListAddTimerEntry() [2]\n");
            return listNode;
        }
    }
    lstInsert(&g_app_map[appid].timer.TimerList, NULL, (NODE *)listNode);

    if (fwdebug)
        printf(" Exit fwListAddTimerEntry() [2]\n");

    return listNode;
}

int fwListRemoveTimerEntry(unsigned int appid, fw_timer_id_t TId)
{
    DLIST *tmp = &g_app_map[appid].timer.TimerList;

    if (fwdebug)
        printf(" Enter fwListRemoveTimerEntry() [1]\n");

    lstDelete(tmp, (NODE *)TId);
    free(TId);
    if (fwdebug)
        printf(" Exit fwListRemoveTimerEntry() [3]\n");
    return (1);
}

int fwListRemoveTimerEntryInternal(unsigned int appid, fw_timer_id_t TId)
{
    DLIST *tmp = &g_app_map[appid].timer.TimerList;
    if (fwdebug)
        printf(" Enter fwListRemoveTimerEntryInternal() [1]\n");

    lstDelete(tmp, (NODE *)TId);

    if (fwdebug)
        printf(" Exit fwListRemoveTimerEntryInternal() [3]\n");
    return (1);
}

void fwPrintTimerList()
{
    int i;
    DLIST *tmp;
    tNode *scan;

    printf("*********** Timer List *************\n");
    for (i = 0; i < MAX_TOTAL_APP_ID; i++)
    {
        tmp = &g_app_map[i].timer.TimerList;
        if (lstCount(tmp))
        {
            printf("Appid: <%d>\n", i);
            scan = (tNode *)lstFirst(tmp);
            while (scan != NULL)
            {
                printf("Val: <%d> TID: <%p> Period: <%d> clientData: <%p>\n", scan->value, scan->TimerId, scan->Period, scan->clientData);
                scan = (tNode *)lstNext((NODE *)scan);
            }
        }
    }
}

fw_timer_id_t fwStartTimer(unsigned int appid, int timerval, int period, void *cdata, int (*fn)(fw_timer_id_t, void *))
{
    tNode *b;
    if (fwdebug)
        printf(" Enter fwSetTimer() [1]\n");
    if (timerval < 0)
    {
        if (fwdebug)
            printf(" Exit fwSetTimer() [2]\n");
    }
    b = fwListAddTimerEntry(appid, timerval, period, cdata, NULL, fn);

    if (fwdebug)
        printf(" Exit fwSetTimer() [3]\n");
    return (b);
}

fw_timer_id_t fwSetTimerInternal(unsigned int appid, int timerval, int period, void *cdata, int (*fn)(fw_timer_id_t, void *), fw_timer_id_t tid)
{
    tNode *b;
    if (fwdebug)
        printf(" Enter fwSetTimerInternal() [1]\n");

    b = fwListAddTimerEntry(appid, timerval, period, cdata, tid, fn);
    if (b == NULL)
        return (NULL);
    if (fwdebug)
        printf(" Exit fwSetTimerInternal() [2]\n");
    return (b->TimerId);
}

int fwCancelTimer(unsigned int appid, fw_timer_id_t timerid)
{
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwtimerMu));
    if (fwdebug)
        printf(" Enter fwCancelTimer() [1]\n");
    status = fwListRemoveTimerEntry(appid, timerid);
    if (fwdebug)
        printf(" Exit fwCancelTimer() [2]\n");
    pthread_mutex_unlock(&(g_app_map[appid].fwtimerMu));
    return (status);
}

int fwCancelTimerInternal(unsigned int appid, fw_timer_id_t timerid)
{
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwtimerMu));
    if (fwdebug)
        printf(" Enter fwCancelTimerInternal() [1]\n");
    status = fwListRemoveTimerEntryInternal(appid, timerid);
    if (fwdebug)
        printf(" Exit fwCancelTimerInternal() [2]\n");
    pthread_mutex_unlock(&(g_app_map[appid].fwtimerMu));
    return (status);
}

#ifdef EPOLL
unsigned int fwEpollEventMapping(unsigned int event)
{
    if (event == READ_EVENT)
        return EPOLLIN;
    if (event == WRITE_EVENT)
        return EPOLLOUT;
    if (event == EXCEPTION_EVENT)
        return EPOLLPRI;
    return 0;
}
#endif

tFdNode *fwListAddSocketEntry(unsigned int appid, int socket, unsigned int event, tFdNode *listNode)
{
    if (fwdebug)
        printf(" Enter fwListAddSocketEntry() [1]\n");

    if (NULL == listNode)
    {
        listNode = (tFdNode *)malloc(sizeof(tFdNode));
        if (listNode == NULL)
        {
            return NULL;
        }
        memset(listNode, 0, sizeof(tFdNode));
        listNode->value = socket;
        lstAdd(&g_app_map[appid].socklist, (NODE *)listNode);

#ifdef EPOLL
        int ret;
        struct epoll_event ev;
        ev.events = fwEpollEventMapping(event);
        ev.data.fd = socket;
        ev.data.ptr = (void *)listNode;
        ret = epoll_ctl(g_app_map[appid].EpollFd, EPOLL_CTL_ADD, socket, &ev);
        if (ret < 0)
        {
            perror("epoll_ctl - add");
            exit(1);
        }
#endif
    }
    else
    {
#ifdef EPOLL
        /* Node already exists */
        fwEpollUpdateEvents(appid, socket, listNode);
#endif
    }
    if (fwdebug)
        printf(" Exit fwListAddSocketEntry() [3]\n");
    return (listNode);
}

int fwUpdateCallbackFuncs(tFdNode *listNode, unsigned int event)
{
    if (event == READ_EVENT)
        listNode->readCallBack = NULL;
    if (event == WRITE_EVENT)
        listNode->writeCallBack = NULL;
    if (event == EXCEPTION_EVENT)
        listNode->exceptionCallBack = NULL;
    return 1;
}

int fwListRemoveSocketEntry_fast(unsigned int appid, unsigned int event, tFdNode *listNode)
{
    DLIST *list = &g_app_map[appid].socklist;
#ifdef EPOLL
    int fd;
    fd = listNode->value;
#endif

    if (fwdebug)
        printf(" Enter fwListRemoveSocketEntry_fast() [1]\n");

    fwUpdateCallbackFuncs(listNode, event);
    if ((NULL == (listNode->readCallBack)) && (NULL == (listNode->writeCallBack)) && (NULL == (listNode->exceptionCallBack)))
    {
        lstDelete(list, (NODE *)listNode);
        free(listNode);
#ifdef EPOLL
        struct epoll_event ev;
        int ret;

        ret = epoll_ctl(g_app_map[appid].EpollFd, EPOLL_CTL_DEL, fd, &ev);
        if (ret < 0)
        {
            perror("epoll_ctl - del");
            exit(1);
        }
#endif
    }
    else
    {
#ifdef EPOLL
        fwEpollUpdateEvents(appid, fd, listNode);
#endif
    }
    if (fwdebug)
        printf(" Exit fwListRemoveSocketEntry_fast() [2]\n");
    return (1);
    if (fwdebug)
        printf(" Exit fwListRemoveSocketEntry() [3]\n");
    return (-1);
}

int fwListRemoveSocketEntry(unsigned int appid, int socket, unsigned int event)
{
    DLIST *list = &g_app_map[appid].socklist;
    NODE *tmp = lstFirst(list);
    NODE *current;

    if (fwdebug)
        printf(" Enter fwListRemoveSocketEntry() [1]\n");
    while (tmp != NULL)
    {
        current = tmp;
        tmp = lstNext(tmp);
        if (((tFdNode *)current)->value == socket)
        {
            fwUpdateCallbackFuncs((tFdNode *)current, event);
            if ((NULL == (((tFdNode *)current)->readCallBack)) && (NULL == (((tFdNode *)current)->writeCallBack)) && (NULL == (((tFdNode *)current)->exceptionCallBack)))
            {
                lstDelete(list, current);
                free(current);
#ifdef EPOLL
                struct epoll_event ev;
                int ret;

                ret = epoll_ctl(g_app_map[appid].EpollFd, EPOLL_CTL_DEL, socket, &ev);
                if (ret < 0)
                {
                    perror("epoll_ctl - del");
                    exit(1);
                }
#endif
            }
            else
            {
#ifdef EPOLL
                fwEpollUpdateEvents(appid, socket, (tFdNode *)current);
#endif
            }
            if (fwdebug)
                printf(" Exit fwListRemoveSocketEntry() [2]\n");
            return (1);
        }
    }
    if (fwdebug)
        printf(" Exit fwListRemoveSocketEntry() [3]\n");
    return (-1);
}

void *fwMultiplexAddException_fast(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->exceptionCallBack = fn;
        b->exceptionClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, EXCEPTION_EVENT, b);
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddException() [3]\n");
        return (0);
    }
    else
    {
        listNode->exceptionCallBack = fn;
        listNode->exceptionClientData = cdata;
        return (listNode);
    }
}

void *fwMultiplexAddWrite_fast(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->writeCallBack = fn;
        b->writeClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, WRITE_EVENT, b);
    if (listNode == NULL)
    {
        return NULL;
    }
    else
    {
        listNode->writeCallBack = fn;
        listNode->writeClientData = cdata;
        return (listNode);
    }
}

void *fwMultiplexAdd_fast(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->readCallBack = fn;
        b->readClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, READ_EVENT, b);
    if (NULL == listNode)
    {
        return NULL;
    }
    else
    {
        listNode->readCallBack = fn;
        listNode->readClientData = cdata;
        return (listNode);
    }
}

tFdNode *fwFindFdNode(unsigned int appid, int Fd)
{
    DLIST *list = &g_app_map[appid].socklist;
    NODE *tmp = lstFirst(list);
    tFdNode *FdNode;

    if (fwdebug)
        printf(" Enter fwFindFdNode() [1]\n");
    while (tmp != NULL)
    {
        FdNode = (tFdNode *)tmp;
        if (FdNode->value == Fd)
        {
            return FdNode;
        }
        tmp = lstNext(tmp);
    }
    if (fwdebug)
        printf(" Exit fwFindFdNode() [1]\n");
    return NULL;
}

#ifdef EPOLL
int fwEpollUpdateEvents(unsigned int appid, int Fd, tFdNode *listNode)
{
    int ret;
    struct epoll_event ev;
    ev.data.fd = Fd;
    if (NULL == listNode)
        return 0;
    ev.events = 0;
    ev.events &= ~(EPOLLIN | EPOLLOUT | EPOLLPRI);
    if (NULL != listNode->readCallBack)
        ev.events |= EPOLLIN;
    if (NULL != listNode->writeCallBack)
        ev.events |= EPOLLOUT;
    if (NULL != listNode->exceptionCallBack)
        ev.events |= EPOLLPRI;
    ev.data.ptr = (void *)listNode;
    ret = epoll_ctl(g_app_map[appid].EpollFd, EPOLL_CTL_MOD, Fd, &ev);
    if (ret < 0)
    {
        perror("epoll_ctl - MOD");
        exit(1);
    }
    return 1;
}
#endif

int fwMultiplexAdd(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexAdd() [1]\n");
    if (socket < 0)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAdd() [2]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->readCallBack = fn;
        b->readClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, READ_EVENT, b);
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAdd() [3]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }
    else
    {
        listNode->readCallBack = fn;
        listNode->readClientData = cdata;
        if (fwdebug)
            printf(" Exit fwMultiplexAdd() [4]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (1);
    }
}

int fwMultiplexAddWrite(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexAddWrite() [1]\n");
    if (socket < 0)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddWrite() [2]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->writeCallBack = fn;
        b->writeClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, WRITE_EVENT, b);
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddWrite() [3]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }
    else
    {
        listNode->writeCallBack = fn;
        listNode->writeClientData = cdata;
        if (fwdebug)
            printf(" Exit fwMultiplexAddWrite() [4]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (1);
    }
}

int fwMultiplexAddException(unsigned int appid, int socket, void *cdata, int (*fn)(int, void *))
{
    tFdNode *b;
    tFdNode *listNode;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexAddException() [1]\n");
    if (socket < 0)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddException() [2]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }

    b = fwFindFdNode(appid, socket);
    if (NULL != b)
    {
        b->exceptionCallBack = fn;
        b->exceptionClientData = cdata;
    }
    listNode = fwListAddSocketEntry(appid, socket, EXCEPTION_EVENT, b);
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddException() [3]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (0);
    }
    else
    {
        listNode->exceptionCallBack = fn;
        listNode->exceptionClientData = cdata;
        if (fwdebug)
            printf(" Exit fwMultiplexAddException() [4]\n");
        pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
        return (1);
    }
}

int fwMultiplexRemoveException_fast(unsigned int appid, void *node)
{
    tFdNode *tmp;
    tmp = (tFdNode *)node;
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemove_fast() [1]\n");
    status = fwListRemoveSocketEntry_fast(appid, EXCEPTION_EVENT, tmp);
    if (fwdebug)
        printf(" Exit fwMultiplexRemove_fast() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwMultiplexRemoveWrite_fast(unsigned int appid, void *node)
{
    tFdNode *tmp;
    tmp = (tFdNode *)node;
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemove_fast() [1]\n");
    status = fwListRemoveSocketEntry_fast(appid, WRITE_EVENT, tmp);
    if (fwdebug)
        printf(" Exit fwMultiplexRemove_fast() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwMultiplexRemove_fast(unsigned int appid, void *node)
{
    tFdNode *tmp;
    tmp = (tFdNode *)node;
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemove_fast() [1]\n");
    status = fwListRemoveSocketEntry_fast(appid, READ_EVENT, tmp);
    if (fwdebug)
        printf(" Exit fwMultiplexRemove_fast() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwMultiplexRemove_fast2(unsigned int appid, void *node)
{
    DLIST *list = &g_app_map[appid].socklist;
    tFdNode *tmp;

    tmp = (tFdNode *)node;
    lstDelete(list, (NODE *)node);
    free(tmp);
    return (1);
}

int fwMultiplexRemove(unsigned int appid, int socket)
{
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemove() [1]\n");
    status = fwListRemoveSocketEntry(appid, socket, READ_EVENT);
    if (fwdebug)
        printf(" Exit fwMultiplexRemove() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwMultiplexRemoveWrite(unsigned int appid, int socket)
{
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemoveWrite() [1]\n");
    status = fwListRemoveSocketEntry(appid, socket, WRITE_EVENT);
    if (fwdebug)
        printf(" Exit fwMultiplexRemoveWrite() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwMultiplexRemoveException(unsigned int appid, int socket)
{
    int status;

    pthread_mutex_lock(&(g_app_map[appid].fwsocketMu));
    if (fwdebug)
        printf(" Enter fwMultiplexRemoveException() [1]\n");
    status = fwListRemoveSocketEntry(appid, socket, EXCEPTION_EVENT);
    if (fwdebug)
        printf(" Exit fwMultiplexRemoveException() [2]\n");

    pthread_mutex_unlock(&(g_app_map[appid].fwsocketMu));
    return (status);
}

int fwfdsetup(unsigned int appid, fd_set *fdvar, fd_set *fdvarwrite, fd_set *fdvarexception)
{
    tFdNode *tmp;
    DLIST *list;
    int maxfd;

    maxfd = 0;
    FD_ZERO(fdvar);
    FD_ZERO(fdvarwrite);
    FD_ZERO(fdvarexception);

    if (g_fwRpcRegistered[appid])
    {
        *fdvar = svc_fdset;
        maxfd = getdtablesize();
    }
    list = &g_app_map[appid].socklist;
    tmp = (tFdNode *)lstFirst(list);
    ;
    while (tmp != NULL)
    {
        if (NULL != tmp->readCallBack)
            FD_SET(tmp->value, fdvar);
        if (NULL != tmp->writeCallBack)
            FD_SET(tmp->value, fdvarwrite);
        if (NULL != tmp->exceptionCallBack)
            FD_SET(tmp->value, fdvarexception);

        if (tmp->value > maxfd)
            maxfd = tmp->value;
        tmp = (tFdNode *)lstNext((NODE *)tmp);
    }

    if (g_fwRpcRegistered[appid])
        return maxfd;
    else
        return maxfd + 1;
}

struct timeval *fwchecktimer(unsigned int appid)
{
    /*  static struct timeval T; */
    /**     the above moved to app map to avoid race condition between applications **/

    int period;
    fw_timer_id_t tid;
    int value;
    void *cData;
    int (*cBack)(fw_timer_id_t, void *);
    time_t diff;
    NODE *scan;
    tNode *tlist;

    if (fwdebug)
        printf(" Enter fwTimeOut() [1]\n");

    fwtimercbcalled = 0;

    while (1)
    {
        scan = lstFirst(&g_app_map[appid].timer.TimerList);
        if (scan == NULL)
        {
            return NULL;
        }
        tlist = (tNode *)scan;
        if (getEpochMs() >= tlist->epoch)
        {
            value = tlist->value;
            period = tlist->Period;
            cData = tlist->clientData;
            tid = tlist->TimerId;
            cBack = tlist->timercallBack;
            cBack(tid, tlist->clientData);
            fwtimercbcalled = 1;
            if (scan != lstFirst(&g_app_map[appid].timer.TimerList))
            {
                /** someone cancelled the timer from callback ? **/
                /** weird but possible **/
                /** well continue in while loop then **/
                continue;
            }
            if (period <= 0)
            {
                fwCancelTimer(appid, tid);
            }
            else
            {
                fwCancelTimerInternal(appid, tid);
                fwSetTimerInternal(appid, value, period, cData, cBack, tid);
            }
        }
        else
        {
            pthread_mutex_lock(&g_app_map[appid].fwtimerMu);
            scan = lstFirst(&g_app_map[appid].timer.TimerList);
            tlist = (tNode *)scan;
            diff = tlist->epoch - getEpochMs();
            if (diff < 0)
            {
                g_app_map[appid].T.tv_sec = 0;
                g_app_map[appid].T.tv_usec = 0;
            }
            else if (diff <= 999)
            {
                g_app_map[appid].T.tv_sec = 0;
                g_app_map[appid].T.tv_usec = diff * 1000;
            }
            else
            {
                g_app_map[appid].T.tv_sec = diff / 1000;
                g_app_map[appid].T.tv_usec = (diff % 1000) * 1000;
            }
            /** for majorly overloaded systems **/
            pthread_mutex_unlock(&g_app_map[appid].fwtimerMu);
            break;
        }
    }
    if (fwdebug)
        printf(" Exit fwchecktimer() [2]\n");
    return (&g_app_map[appid].T);
}

int fwMultiplexMainLoop(unsigned int appid)
{
    /*int         tval;*/
    int result;
    struct timeval *ptimeout;
#ifdef EPOLL
    int timeout;
#endif

#ifndef EPOLL
    int maxfd;
    struct timeval T;
    fd_set fdvar, fdvarwrite, fdvarexception;
#endif

    if (fwdebug)
        printf(" Enter fwMultiplexMainLoop() [1]\n");

    while (1)
    {
        if (fwdebug)
        {
            printf("fwMultiplexMainLoop: Waiting on Select Call[]\n");
            fwPrintList();
        }

        ptimeout = fwchecktimer(appid);
        if (pfwprompt)
            pfwprompt(fwpromptclientdata);
        fflush(stdout);
        fflush(stderr);
#ifdef EPOLL
        struct epoll_event ev[MAX_EPOLL_EVENTS];
        if (ptimeout == NULL)
        {
            timeout = -1;
        }
        else
        {
            timeout = ptimeout->tv_sec * 1000 + ptimeout->tv_usec / 1000;
        }
        if (pfwworkproc)
        {
            timeout = 0;
        }
        result = epoll_wait(g_app_map[appid].EpollFd, ev, MAX_EPOLL_EVENTS, timeout);

#else
        maxfd = fwfdsetup(appid, &fdvar, &fdvarwrite, &fdvarexception);
        if (pfwworkproc)
        {
            T.tv_sec = 0;
            T.tv_usec = 0;
            ptimeout = &T;
        }
        result = select(maxfd, &fdvar, &fdvarwrite, &fdvarexception, ptimeout);
#endif
        if ((result < 0) && (errno == EINTR))
            continue;
        else if ((result < 0) && (errno != EINTR))
        {
#ifdef EPOLL
            perror("Panic, Epoll Error\n");
#else
            perror("Panic, Select Error\n");
#endif
            break;
        }
        else if (result == 0)
        {
            fwchecktimer(appid);
            if (fwtimercbcalled)
                continue; /** give priority to events **/
            if (pfwworkproc)
                pfwworkproc(fwworkprocclientdata);
            continue;
        }
        else
        {
#ifdef EPOLL
            fwProcessData_epoll(appid, result, ev);
#else
            fwProcessData(appid, result, &fdvar, &fdvarwrite, &fdvarexception, &g_app_map[appid].socklist);
#endif
        }
    }
    return 1;
}

void fwPrintSocketList()
{
    int i;
    DLIST *tmp;
    tFdNode *scan;

    printf("*********** Socket List *************\n");
    for (i = 0; i < MAX_TOTAL_APP_ID; i++)
    {
        tmp = &g_app_map[i].socklist;
        if (lstCount(tmp))
        {
            printf("Appid: <%d>\n", i);
            scan = (tFdNode *)lstFirst(tmp);
            while (scan != NULL)
            {
                printf("Socket: <%d>  readclientData: <%p> writeclientData <%p> excepClientData <%p>\n", scan->value, scan->readClientData, scan->writeClientData, scan->exceptionClientData);
                scan = (tFdNode *)lstNext((NODE *)scan);
            }
        }
    }
}

int fwProcessData(unsigned int appid, int num, fd_set *fdvar, fd_set *fdvarwrite, fd_set *fdvarexception, DLIST *list)
{
    int socket;
    int count = 0;
    tFdNode *temp;
    tFdNode *current;
    if (fwdebug)
        printf(" Enter fwProcessData() [1]\n");
    temp = (tFdNode *)lstFirst(list);
    while (temp != NULL)
    {
        current = temp;
        temp = (tFdNode *)lstNext((NODE *)temp);
        socket = current->value;
        if (FD_ISSET(socket, fdvar))
        {
            count++;
            current->readCallBack(socket, current->readClientData);
        }
        if (FD_ISSET(socket, fdvarwrite))
        {
            count++;
            current->writeCallBack(socket, current->writeClientData);
        }
        if (FD_ISSET(socket, fdvarexception))
        {
            count++;
            current->exceptionCallBack(socket, current->exceptionClientData);
        }

        if (count == num)
        {
            break;
        }
    }
    if (g_fwRpcRegistered[appid])
        svc_getreqset(fdvar);
    if (fwdebug)
        printf(" Exit fwProcessData() [2]\n");
    return (0);
}

#ifdef EPOLL
int fwProcessData_epoll(unsigned int appid, int num_events, struct epoll_event *ev)
{
    int socket;
    int callbackcalled = 0;
    tFdNode *temp;
    int i = 0;

    if (fwdebug)
        printf(" Enter fwProcessData_epoll() [1]\n");
    for (i = 0; i < num_events; i++)
    {
        temp = (tFdNode *)ev[i].data.ptr;
        socket = temp->value;
        if (ev[i].events & EPOLLIN)
            (temp->readCallBack)(socket, temp->readClientData);
        if (ev[i].events & EPOLLOUT)
            (temp->writeCallBack)(socket, temp->writeClientData);
        if (ev[i].events & EPOLLPRI)
            (temp->exceptionCallBack)(socket, temp->exceptionClientData);
        callbackcalled = 1;
    }
    if (fwdebug)
        printf(" Exit fwProcessData_epoll() [2]\n");
    callbackcalled = callbackcalled;
    return (0);
}
#endif

int tcpSocketServer(int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in serv_addr;
    int optval = 1;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketServer:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(localPort);
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketServer:bind");
        close(fd);
        return 0;
    }
    listen(fd, 5);

    return fd;
}

int tcpSocketServerExt(char *localip, int localPort)
{
    int fd;
    int ret;
    int opt;
    struct sockaddr_in serv_addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketServer:socket");
        exit(1);
    }
    opt = 1;
    if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockpttcp");
        exit(1);
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    ret = inet_pton(AF_INET, localip, &serv_addr.sin_addr);
    if (ret <= 0)
    {
        perror("inet_ntop");
        exit(1);
    }
    serv_addr.sin_port = htons(localPort);

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketServer:bind");
        exit(1);
    }
    listen(fd, 5);

    return fd;
}

int tcpSocketClient(int localPort)
{
    int fd = 0;
    int ret;
    struct sockaddr_in serv_addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketClient:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(localPort);

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketClient:bind");
        close(fd);
        return 0;
    }

    return fd;
}

int tcpSocketClientExt(char *localip, int localPort)
{
    int opt;
    int fd;
    int ret;
    struct sockaddr_in serv_addr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketClient:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(localip);
    serv_addr.sin_port = htons(localPort);

    opt = 1;
    if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockpttcp");
        close(fd);
        return 0;
    }

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketClient:bind");
        close(fd);
        return 0;
    }

    return fd;
}

int udpSocket(int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in serv_addr;
    int buf_value = 1000000;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("getUdpBoundSocket:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(localPort);

    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockopt1");
        exit(1);
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockop2");
        exit(1);
    }
    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("getUDPBoundSocket:bind");
        close(fd);
        return 0;
    }

    return fd;
}

int unixdomainSocket(char *file)
{
    int fd;
    int ret;
    int servlen;
    struct sockaddr_un serv_addr;
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("getUnixDomainBoundSocket:socket");
        return 0;
    }
    unlink(file);
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file);
    servlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

    ret = bind(fd, (struct sockaddr *)&serv_addr, servlen);
    if (ret < 0)
    {
        perror("getUnixDomainBoundSocket:bind");
        close(fd);
        return 0;
    }
    chmod(file, 00777);
    return fd;
}

int unixdomainStreamSocketServer(char *file)
{
    int fd;
    int ret;
    int servlen;
    struct sockaddr_un serv_addr;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("unixdomainStreamSocketServer:socket");
        return 0;
    }
    unlink(file);
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file);
    servlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

    ret = bind(fd, (struct sockaddr *)&serv_addr, servlen);
    if (ret < 0)
    {
        perror("unixdomainStreamSocketServer:bind");
        close(fd);
        return 0;
    }
    chmod(file, 00777);
    listen(fd, 5);
    return fd;
}

int unixdomainStreamSocketClient(char *file)
{
    int fd;
    int ret;
    int servlen;
    struct sockaddr_un serv_addr;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("unixdomainStreamSocketClient:socket");
        return 0;
    }
    unlink(file);
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file);
    servlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

    ret = bind(fd, (struct sockaddr *)&serv_addr, servlen);
    if (ret < 0)
    {
        perror("unixdomainStreamSocketClient:bind");
        close(fd);
        return 0;
    }
    return fd;
}

int udpWrite(int fd, char *remoteipaddress, int remotePort, char *data, int length)
{
    struct sockaddr_in cli_addr, serv_addr;
    int ret;

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(remoteipaddress);
    serv_addr.sin_port = htons(remotePort);

    ret = sendto(fd, data, length, 0, (struct sockaddr *)&serv_addr, sizeof(cli_addr));
    if (ret < 0)
    {
        perror("udpWrite:sendto");
        return 0;
    }
    return ret;
}

int unixdomainWrite(int fd, char *peerfile, char *data, int length)
{
    int servlen;
    int ret;
    struct sockaddr_un serv_addr;

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, peerfile);
    servlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

    ret = sendto(fd, data, length, 0, (struct sockaddr *)&serv_addr, servlen);
    if (ret != length)
    {
        perror("unixdomainWrite: sendto failed");
        return -1;
    }
    return length;
}

int udpRead(int fd, char *data)
{
    int n;

    n = recvfrom(fd, data, MAXUDPLEN, 0, (struct sockaddr *)0, (socklen_t *)0);

    return n;
}

int udpReadFrom(int fd, char *data, char *ip, unsigned short *port)
{
    int n;
    struct sockaddr_in s;
    socklen_t len;

    len = sizeof(s);
    n = recvfrom(fd, data, MAXUDPLEN, 0, (struct sockaddr *)&s, &len);
    if (n <= 0)
    {
        strcpy(ip, "");
        *port = 0;
        return n;
    }

    if (n > 0)
    {
        strcpy(ip, inet_ntoa(s.sin_addr));
        *port = ntohs(s.sin_port);
    }

    return n;
}

int tcpWrite(int fd, char *data, int length)
{
    int ret;

    ret = writen(fd, data, length);

    return ret;
}

int tcpRead(int fd, char *data, int length)
{
    int ret;

    ret = readn(fd, data, length);

    return ret;
}

int tcpConnect(int fd, char *remoteipaddress, int remoteport)
{
    int ret;
    struct sockaddr_in server_address;

    memset((char *)&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(remoteport);
    server_address.sin_addr.s_addr = inet_addr(remoteipaddress);

    ret = connect(fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if ((ret < 0) && (errno == EINTR))
    {
        /** timedout **/
        return ret;
    }
    if ((ret < 0) && (errno != EINTR))
    {
        /** error **/
        perror("tcpConnect");
        return ret;
    }
    return 1;
}

int tcpConnect6(int fd, char *remoteipaddress, int remoteport)
{
    int ret;
    struct sockaddr_in6 server_address;

    memset((char *)&server_address, '\0', sizeof(server_address));
    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons(remoteport);
    inet_pton(AF_INET6, remoteipaddress, &server_address.sin6_addr);

    ret = connect(fd, (struct sockaddr *)&server_address, sizeof(server_address));
    if ((ret < 0) && (errno == EINTR))
    {
        /** timedout **/
        return ret;
    }
    if ((ret < 0) && (errno != EINTR))
    {
        /** error **/
        perror("tcpConnect");
        return ret;
    }
    return 1;
}

/** Changes Start for Bug 234 **/

void sockalarmhandler(int alarmnum)
{
    __tcpalarm.sa_handler = sockalarmhandler;
    sigaction(SIGALRM, &__tcpalarm, NULL);
}

void uualarm(int microsec)
{
    struct itimerval tout_val;

    tout_val.it_interval.tv_sec = FW_CONST_ZERO;
    tout_val.it_interval.tv_usec = FW_CONST_ZERO;
    tout_val.it_value.tv_sec = microsec / 1000000;
    tout_val.it_value.tv_usec = microsec % 1000000;
    setitimer(ITIMER_REAL, &tout_val, FW_CONST_ZERO);
}

int tcpConnectExt(int fd, char *remoteipaddress, int remoteport, int timeout)
{
    int ret;
    struct sockaddr_in server_address;
    int alarmsetup = FW_CONST_ZERO;

    if (FAILURE != timeout)
    {
        /** setup the alarm here **/
        alarmsetup = FW_CONST_ONE;
        uualarm(timeout * 1000 * 1000);
    }

    memset((char *)&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(remoteport);
    server_address.sin_addr.s_addr = inet_addr(remoteipaddress);

    ret = connect(fd, (struct sockaddr *)&server_address, sizeof(server_address));

    if ((FW_CONST_ZERO > ret) && (EINTR == errno))
    {
        /** timedout **/
        alarmsetup = FW_CONST_ZERO;
    }
    if (FW_CONST_ONE == alarmsetup)
    {
        /** cancel the timer here **/
        alarm(FAILURE);
    }
    return ret;
}

int tcpConnectExt6(int fd, char *remoteipaddress, int remoteport, int timeout)
{
    int ret;
    struct sockaddr_in6 server_address;
    int alarmsetup = FW_CONST_ZERO;

    if (FAILURE != timeout)
    {
        /** setup the alarm here **/
        alarmsetup = FW_CONST_ONE;
        uualarm(timeout * 1000 * 1000);
    }

    memset((char *)&server_address, '\0', sizeof(server_address));
    server_address.sin6_family = AF_INET6;
    server_address.sin6_port = htons(remoteport);
    inet_pton(AF_INET6, remoteipaddress, &server_address.sin6_addr);

    ret = connect(fd, (struct sockaddr *)&server_address, sizeof(server_address));

    if ((FW_CONST_ZERO > ret) && (EINTR == errno))
    {
        /** timedout **/
        alarmsetup = FW_CONST_ZERO;
    }
    if (FW_CONST_ONE == alarmsetup)
    {
        /** cancel the timer here **/
        alarm(FAILURE);
    }
    return ret;
}

/** Changes End for Bug 234 **/

int tcpSocketClient6(int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in6 serv_addr;

    fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketClient:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_addr = in6addr_any;
    serv_addr.sin6_port = htons(localPort);

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketClient:bind");
        close(fd);
        return 0;
    }

    return fd;
}

int tcpSocketClientExt6(char *localip, int localPort)
{
    int opt;
    int fd;
    int ret;
    struct sockaddr_in6 serv_addr;

    fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("tcpSocketClient:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    ret = inet_pton(AF_INET6, localip, &serv_addr.sin6_addr);
    if (ret <= 0)
    {
        perror("inet_ntop");
        close(fd);
        return 0;
    }
    serv_addr.sin6_port = htons(localPort);

    opt = 1;
    if (-1 == setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockpttcp");
        close(fd);
        return 0;
    }

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("tcpSocketClient:bind");
        close(fd);
        return 0;
    }

    return fd;
}

int unixdomainConnect(int fd, char *file)
{
    int ret, servlen;
    struct sockaddr_un serv_addr;

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, file);
    servlen = sizeof(serv_addr.sun_family) + strlen(serv_addr.sun_path);

    ret = connect(fd, (struct sockaddr *)&serv_addr, servlen);
    if ((ret < 0) && (errno == EINTR))
    {
        /** timedout **/
        return ret;
    }
    if ((ret < 0) && (errno != EINTR))
    {
        /** error **/
        perror("unixdomainConnect");
        return ret;
    }
    return 1;
}

int tcpAccept(int fd)
{
    int newfd;
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);
    newfd = accept(fd, (struct sockaddr *)&cli_addr, &clilen);
    if (newfd < 0)
    {
        perror("accept");
        return -1;
    }
    return newfd;
}

int unixdomainAccept(int fd)
{
    int newfd;
    socklen_t clilen;
    struct sockaddr_un cli_addr;

    clilen = sizeof(cli_addr);
    newfd = accept(fd, (struct sockaddr *)&cli_addr, &clilen);
    if (newfd < 0)
    {
        perror("accept");
        return -1;
    }
    return newfd;
}

int writen(int fd, char *ptr, int nbytes)
{
    int nleft, nwritten;

    nleft = nbytes;

    while (nleft > 0)
    {
        nwritten = write(fd, ptr, nleft);
        if (nwritten <= 0)
            break;
        nleft -= nwritten;
        ptr += nwritten;
    }

    return (nbytes - nleft);
}

int readn(int fd, char *ptr, int nbytes)
{

    int nleft, nread;

    nleft = nbytes;

    while (nleft > 0)

    {
        nread = read(fd, ptr, nleft);
        if (nread <= 0)
            break;

        nleft -= nread;
        ptr += nread;
    }

    return (nbytes - nleft);
}

void getLvalRval(const char *buffer, char ch, char *lval, char *rval)
{
    int index = 0;
    int i;
    strcpy(lval, "");
    strcpy(rval, "");

    for (index = 0; index < (int)(strlen(buffer)); index++)
        if (buffer[index] == ch)
            break;
    if (index == (int)strlen(buffer))
    {
        strcpy(lval, buffer);
        rval[0] = '\0';
        {
            return;
        }
    }
    for (i = 0; i < index; i++)
        lval[i] = buffer[i];
    lval[i] = '\0';

    for (i = index + 1; i < (int)strlen(buffer); i++)
        rval[i - index - 1] = buffer[i];
    rval[i - index - 1] = '\0';

    trim(lval);
    trim(rval);

    {
        return;
    }
}

void trim(char *buffer)
{
    int i;
    char temp[4096];

    for (i = 0; i < (int)strlen(buffer); i++)
    {
        if ((buffer[i] == ' ') || (buffer[i] == '\t'))
            continue;
        else
            break;
    }
    strcpy(temp, buffer + i);
    strcpy(buffer, temp);

    for (i = strlen(buffer) - 1; i >= 0; i--)
    {
        if ((buffer[i] == ' ') || (buffer[i] == '\t'))
            continue;
        else
            break;
    }
    buffer[i + 1] = '\0';
    {
        return;
    }
}

void ltrim(char *buffer)
{
    int i;
    char temp[4096];

    for (i = 0; i < strlen(buffer); i++)
    {
        if ((buffer[i] == ' ') || (buffer[i] == '\t'))
            continue;
        else
            break;
    }
    strcpy(temp, buffer + i);
    strcpy(buffer, temp);
}
void rtrim(char *buffer)
{
    int i;

    for (i = strlen(buffer) - 1; i >= 0; i--)
    {
        if ((buffer[i] == ' ') || (buffer[i] == '\t'))
            continue;
        else
            break;
    }
    buffer[i + 1] = '\0';
    {
        return;
    }
}

void pdumpBytes(unsigned char *D, unsigned long count)
{
    unsigned long i,
        base = 0;
    pprintf(("-------- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ----------------\n"));
    for (; base + 16 < count; base += 16)
    {
        pprintf(("%08lX ", base));

        for (i = 0; i < 16; i++)
        {
            pprintf(("%02X ", D[base + i]));
        }

        for (i = 0; i < 16; i++)
        {
            pprintf(("%c", isprint(D[base + i]) ? D[base + i] : '.'));
        }
        pprintf(("\n"));
    }

    pprintf(("%08lX ", base));
    for (i = base; i < count; i++)
    {
        pprintf(("%02X ", D[i]));
    }
    for (; i < base + 16; i++)
    {
        pprintf(("   "));
    }
    for (i = base; i < count; i++)
    {
        pprintf(("%c", isprint(D[i]) ? D[i] : '.'));
    }
    for (; i < base + 16; i++)
    {
        pprintf((" "));
    }
    pprintf(("\n"));
    pprintf(("-------- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ----------------\n"));
    pprintf(("\n"));
}

void dumpBytesTo(FILE *fp, unsigned char *D, unsigned long count)
{
    unsigned long i,
        base = 0;
    fprintf(fp, "-------- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ----------------\n");
    for (; base + 16 < count; base += 16)
    {
        fprintf(fp, "%08lX ", base);

        for (i = 0; i < 16; i++)
        {
            fprintf(fp, "%02X ", D[base + i]);
        }

        for (i = 0; i < 16; i++)
        {
            fprintf(fp, "%c", isprint(D[base + i]) ? D[base + i] : '.');
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "%08lX ", base);
    for (i = base; i < count; i++)
    {
        fprintf(fp, "%02X ", D[i]);
    }
    for (; i < base + 16; i++)
    {
        fprintf(fp, "   ");
    }
    for (i = base; i < count; i++)
    {
        fprintf(fp, "%c", isprint(D[i]) ? D[i] : '.');
    }
    for (; i < base + 16; i++)
    {
        fprintf(fp, " ");
    }
    fprintf(fp, "\n");
    fprintf(fp, "-------- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ----------------\n");
    fprintf(fp, "\n");
    fflush(fp);
}

#ifdef DPDK_DP
void bufferAddUint8_linux(unsigned char *buffer, unsigned long long value)
{
    unsigned char *p;

    p = (unsigned char *)&value;

#ifdef __OCTEON__ /* Changes done for ODP on Cavium - Inder */
    buffer[0] = p[0];
    buffer[1] = p[1];
    buffer[2] = p[2];
    buffer[3] = p[3];
    buffer[4] = p[4];
    buffer[5] = p[5];
    buffer[6] = p[6];
    buffer[7] = p[7];
#else
    buffer[0] = p[7];
    buffer[1] = p[6];
    buffer[2] = p[5];
    buffer[3] = p[4];
    buffer[4] = p[3];
    buffer[5] = p[2];
    buffer[6] = p[1];
    buffer[7] = p[0];
#endif
}

void bufferAddUint4_linux(unsigned char *buffer, unsigned int value)
{
    unsigned char *p;

    p = (unsigned char *)&value;

#ifdef __OCTEON__ /* Changes done for ODP on Cavium - Inder */
    buffer[0] = p[0];
    buffer[1] = p[1];
    buffer[2] = p[2];
    buffer[3] = p[3];
#else
    buffer[0] = p[3];
    buffer[1] = p[2];
    buffer[2] = p[1];
    buffer[3] = p[0];
#endif
}

void bufferAddUint2_linux(unsigned char *buffer, unsigned short value)
{
    unsigned char *p;

    p = (unsigned char *)&value;

#ifdef __OCTEON__ /* Changes done for ODP on Cavium - Inder */
    buffer[0] = p[0];
    buffer[1] = p[1];

#else
    buffer[0] = p[1];
    buffer[1] = p[0];
#endif
}

#else
void bufferAddUint8_linux(unsigned char *buffer, unsigned long long value)
{
    unsigned char *p;
    p = (unsigned char *)&value;

    buffer[0] = p[0];
    buffer[1] = p[1];
    buffer[2] = p[2];
    buffer[3] = p[3];
    buffer[4] = p[4];
    buffer[5] = p[5];
    buffer[6] = p[6];
    buffer[7] = p[7];
}
/**  This function adds a unsigned int to the buffer **/
void bufferAddUint4_linux(unsigned char *buffer, unsigned int value)
{
    unsigned char *p;
    p = (unsigned char *)&value;

    buffer[0] = p[0];
    buffer[1] = p[1];
    buffer[2] = p[2];
    buffer[3] = p[3];
}

/**  This function adds a unsigned short to the buffer **/
void bufferAddUint2_linux(unsigned char *buffer, unsigned short value)
{
    unsigned char *p;
    p = (unsigned char *)&value;

    buffer[0] = p[0];
    buffer[1] = p[1];
}
#endif
void bufferAddUint1_linux(unsigned char *buffer, unsigned char value)
{
    unsigned char *p;
    p = (unsigned char *)&value;

    buffer[0] = p[0];
}

#ifdef DPDK_DP
unsigned long long bufferGetUint8_linux(unsigned char *buffer)
{

    unsigned char temp[8];
    unsigned long long *scan;

#ifdef __OCTEON__ /*ODP changes on Cavium - Inder */
    temp[0] = buffer[0];
    temp[1] = buffer[1];
    temp[2] = buffer[2];
    temp[3] = buffer[3];
    temp[4] = buffer[4];
    temp[5] = buffer[5];
    temp[6] = buffer[6];
    temp[7] = buffer[7];
#else
    temp[0] = buffer[7];
    temp[1] = buffer[6];
    temp[2] = buffer[5];
    temp[3] = buffer[4];
    temp[4] = buffer[3];
    temp[5] = buffer[2];
    temp[6] = buffer[1];
    temp[7] = buffer[0];
#endif
    scan = (unsigned long long *)temp;
    return *scan;
}
unsigned int bufferGetUint4_linux(unsigned char *buffer)
{

    unsigned char temp[4];
    unsigned int *scan;

#ifdef __OCTEON__ /*ODP changes on Cavium - Inder */
    temp[0] = buffer[0];
    temp[1] = buffer[1];
    temp[2] = buffer[2];
    temp[3] = buffer[3];
#else
    temp[0] = buffer[3];
    temp[1] = buffer[2];
    temp[2] = buffer[1];
    temp[3] = buffer[0];
#endif
    scan = (unsigned int *)temp;
    return *scan;
}

unsigned short bufferGetUint2_linux(unsigned char *buffer)
{
    unsigned char temp[2];
    unsigned short *scan;

#ifdef __OCTEON__
    temp[0] = buffer[0];
    temp[1] = buffer[1];
#else
    temp[0] = buffer[1];
    temp[1] = buffer[0];
#endif
    scan = (unsigned short *)temp;
    return *scan;
}

#else
unsigned long long bufferGetUint8_linux(unsigned char *buffer)
{
    unsigned char temp[8];
    unsigned long long *scan;
    temp[0] = buffer[0];
    temp[1] = buffer[1];
    temp[2] = buffer[2];
    temp[3] = buffer[3];
    temp[4] = buffer[4];
    temp[5] = buffer[5];
    temp[6] = buffer[6];
    temp[7] = buffer[7];

    scan = (unsigned long long *)temp;
    return *scan;
}
/**  This function gets a unsigned int to the buffer **/
unsigned int bufferGetUint4_linux(unsigned char *buffer)
{
    unsigned char temp[4];
    unsigned int *scan;
    temp[0] = buffer[0];
    temp[1] = buffer[1];
    temp[2] = buffer[2];
    temp[3] = buffer[3];

    scan = (unsigned int *)temp;
    return *scan;
}

/**  This function gets a unsigned short to the buffer **/
unsigned short bufferGetUint2_linux(unsigned char *buffer)
{
    unsigned char temp[2];
    unsigned short *scan;
    temp[0] = buffer[0];
    temp[1] = buffer[1];

    scan = (unsigned short *)temp;
    return *scan;
}
#endif

/**  This function gets a unsigned char to the buffer **/
unsigned char bufferGetUint1_linux(unsigned char *buffer)
{
    unsigned char temp[1];
    unsigned char *scan;
    temp[0] = buffer[0];

    scan = (unsigned char *)temp;
    return *scan;
}

/**  This function returns a 1 if the bit indicated in bitNumber [0..7] is set in source **/
int isBitSetUint1(unsigned char source, int bitNumber)
{
    /*unsigned int temp = (unsigned int)source;*/
    if ((bitNumber < 0) || (bitNumber > 7))
    {
        fprintf(stderr, "wtls: isBitSetUint1: invalid bit number <%d>\n", bitNumber);
        return 0;
    }
    if (source & SetBitMask[bitNumber])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**  This function sets the bit indicated in bitNumber [0..7] in source **/
void setBitUint1(unsigned char *source, int bitNumber)
{
    if ((bitNumber < 0) || (bitNumber > 7))
    {
        fprintf(stderr, "wtls: setBitUint1: invalid bit number <%d>\n", bitNumber);
        return;
    }
    *source = *source | SetBitMask[bitNumber];
}

/**  This function clears the bit indicated in bitNumber [0..7] in source **/
void clearBitUint1(unsigned char *source, int bitNumber)
{
    if ((bitNumber < 0) || (bitNumber > 7))
    {
        return;
    }
    *source = *source & ClearBitMaskUint1[bitNumber];
}

/** clears all bits in x and returns the value. does not change x **/
unsigned char clearBits(unsigned char x)
{
    return (x & ~(~0));
}

/* get n bits from position p */
/* rightmost bit is the 0th bit */
unsigned char getBits(unsigned char x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

/** This function returns the number of seconds elapsed since 1970 **/
time_t getEpoch()
{
    struct timeval t;
    gettimeofday(&t, (struct timezone *)NULL);
    return t.tv_sec;
}

time_t getEpochMs()
{
    struct timespec t;
    syscall(__NR_clock_gettime, CLOCK_MONOTONIC, &t);
    return t.tv_sec * 1000 + t.tv_nsec / (1000 * 1000);
}

unsigned long long getEpochUs()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (unsigned long long)(t.tv_sec * (unsigned long long)(1000 * 1000) + (unsigned long long)(t.tv_nsec / (1000)));
}

void readBuffer(unsigned char *buf, char *fileName, int *lengthOut)
{
    FILE *fpt;
    char buffer[1024];
    char token[1024];
    char *scan;
    int length;

    length = 0;
    fpt = fopen(fileName, "r");
    if (fpt == NULL)
    {
        fprintf(stdout, "readBuffer: could not open <%s>\n", fileName);
        return;
    }
    while (fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';
        trim(buffer);
        if (buffer[0] == '#')
            continue;
        if (strcmp(buffer, "") == 0)
            continue;
        strcpy(token, "");
        scan = strtok(buffer, " ");
        if (scan == NULL)
            break;
        buf[length] = strtoul(scan, NULL, 16);
        length++;
        while ((scan = strtok(NULL, " ")) != NULL)
        {
            buf[length] = strtoul(scan, NULL, 16);
            length++;
        }
    }
    *lengthOut = length;
    fclose(fpt);
}

void loadBuffer(unsigned char *buffer, char *fileName, int *lengthOut)
{
    FILE *fpt;
    char lineBuffer[1024];
    char *lineScan;
    int count;
    int bufferIndex;
    char array[5];

    fpt = fopen(fileName, "r");
    if (fpt == NULL)
    {
        fprintf(stderr, "analyze: could not open <%s> for reading !\n", fileName);
        return;
    }
    bufferIndex = 0;
    while (fgets(lineBuffer, 1023, fpt) != NULL)
    {
        lineBuffer[strlen(lineBuffer) - 1] = '\0';
        trim(lineBuffer);
        if (strcmp(lineBuffer, "") == 0)
            continue;
        if (lineBuffer[0] == '#')
            continue;
        if (lineBuffer[0] == '-')
            continue;
        lineScan = lineBuffer;
        lineScan += 8;
        lineScan++;
        count = 0;
        while (1)
        {
            if (
                (lineScan[0] == ' ') &&
                (lineScan[1] == ' '))
                break;
            if (count == 16)
                break;
            array[0] = '0';
            array[1] = 'x';
            array[2] = lineScan[0];
            array[3] = lineScan[1];
            array[4] = '\0';
            buffer[bufferIndex] = strtoul(array, NULL, 16);
            bufferIndex++;
            lineScan += 3;
            count++;
        }
    }
    *lengthOut = bufferIndex;
    fclose(fpt);
}

char *strreplace(char *source, char *search, char *replace)
{
    char replacedBuffer[8192];
    char localSource[8192];
    char *sourceScan;
    /*char* localScan;*/

    strcpy(localSource, source);
    strcpy(replacedBuffer, "");
    sourceScan = source;
    while ((sourceScan = strstr(sourceScan, search)) != NULL)
    {
        char *localScan = strstr(localSource, search);
        if (NULL == localScan)
        {
            return NULL;
        }
        *localScan = '\0';
        strcat(replacedBuffer, localSource);
        strcat(replacedBuffer, replace);
        sourceScan += strlen(search);
        strcpy(localSource, sourceScan);
    }
    strcat(replacedBuffer, localSource);
    strcpy(source, replacedBuffer);
    {
        return source;
    }
}

time_t getEpochTimeFromString(char *rval)
{
    char temp[1024];
    int mm, dd, yyyy, hh, mi, ss;
    int gindex;
    int lindex;
    struct tm aTm;

    gindex = 0;

    /** mm **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    mm = atoi(temp);

    gindex++;

    /** dd **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    dd = atoi(temp);

    gindex++;

    /** yyyy **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    yyyy = atoi(temp);

    gindex++;

    /** hh **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    hh = atoi(temp);

    gindex++;

    /** mi **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    mi = atoi(temp);

    gindex++;

    /** ss **/
    lindex = 0;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = rval[gindex];
    lindex++;
    gindex++;
    temp[lindex] = '\0';
    ss = atoi(temp);

    aTm.tm_mon = mm - 1;
    aTm.tm_mday = dd;
    aTm.tm_year = yyyy - 1900;
    aTm.tm_hour = hh;
    aTm.tm_min = mi;
    aTm.tm_sec = ss;
    aTm.tm_isdst = 0;

    return (mktime(&aTm));
}

char *num2Ascii(int num, char *buffer)
{
    strcpy(buffer, "");
    sprintf(buffer, "%d", num);
    return buffer;
}

char *float2Ascii(float num, char *buffer)
{
    strcpy(buffer, "");
    sprintf(buffer, "%f", num);
    return buffer;
}

void getMmDdYyHhMiSsDateString(time_t epoch, char *dst)
{
    /* epoch is number of seconds elapsed since 1970 */
    char buffer[1024];
    char yyyy[32];
    char mm[32];
    char dd[32];
    char hh[32];
    char mi[32];
    char ss[32];
    struct tm *outTm;
    int year;

    outTm = gmtime(&epoch);
    if (NULL == outTm)
    {
        return;
    }

    strcpy(buffer, "");
    year = outTm->tm_year + 1900;
    year = year - 2000;
    sprintf(buffer, "%02d", year);
    strcpy(yyyy, buffer);

    strcpy(buffer, "");
    sprintf(buffer, "%02d", outTm->tm_mon + 1);
    strcpy(mm, buffer);

    strcpy(buffer, "");
    sprintf(buffer, "%02d", outTm->tm_mday);
    strcpy(dd, buffer);

    strcpy(buffer, "");
    sprintf(buffer, "%02d", outTm->tm_hour);
    strcpy(hh, buffer);

    strcpy(buffer, "");
    sprintf(buffer, "%02d", outTm->tm_min);
    strcpy(mi, buffer);

    strcpy(buffer, "");
    sprintf(buffer, "%02d", outTm->tm_sec);
    strcpy(ss, buffer);

    strcpy(dst, "");
    strcat(dst, mm);
    strcat(dst, "/");
    strcat(dst, dd);
    strcat(dst, "/");
    strcat(dst, yyyy);
    strcat(dst, " ");
    strcat(dst, hh);
    strcat(dst, ":");
    strcat(dst, mi);
    strcat(dst, ":");
    strcat(dst, ss);
}

unsigned int upow(unsigned int num, unsigned int raisedto)
{
    unsigned int number;
    unsigned int i;

    number = 1;
    for (i = 0; i < raisedto; i++)
        number *= num;

    return number;
}

void fwtraceinit()
{
    char *env;
    char logfile[1024];
    static int logFd = -1;
    int index;
    unsigned long base = 0, count;
    unsigned char *p;
    FILE *fp;
    elog_flag = 1;
    env = getenv("VERBOSITY");
    fp = fopen("/proc/version", "r");
    if (fp == NULL)
    {
        g_solaris = 1;
    }
    else
    {
        fclose(fp);
    }
    if (g_solaris)
    {
        p = (unsigned char *)_init;
        count = (char *)_etext - (char *)_init;
    }
    else
    {
        p = (unsigned char *)_etext;
        count = elog_end() - (char *)_etext;
    }
    for (index = 0; index < MAX_APP_ID; index++)
    {
        if (env)
        {
            g_app_map[index].__tracelevel__ = atoi(env);
        }
        else
        {
            g_app_map[index].__tracelevel__ = 1;
        }
    }

    /** redirect io **/
    env = getenv("LOGFILE");
    if (env)
    {
        if (logFd == -1)
        {
            strcpy(__tracefile__, "");
            __tracesize__ = MAX_LOG_FILE_SIZE;
            strncpy(__tracefile__, env, sizeof(__tracefile__) - 1);
            __tracefile__[sizeof(__tracefile__) - 1] = '\0';
            strncpy(logfile, env, sizeof(logfile) - 1);
            logfile[sizeof(logfile) - 1] = '\0';
            remove(logfile);
            logFd = open(logfile, O_CREAT | O_WRONLY, 0777);
            if (logFd < 0)
            {
                perror("open");
                fprintf(stderr, "fw: could not open <%s> for logging - defaulting to stdout\n", logfile);
                return;
            }
            fchmod(logFd, 00777);
            close(1);
            dup2(logFd, 1);
            env = getenv("LOGSIZE");
            if (env)
            {
                __tracesize__ = atoi(env);
            }
        }
    }
    for (; base < count; base++)
    {
        if (p[base] == '~')
        {
            if (0 == strncmp((char *)p + base, global, strlen(global)) && isprint(p[base + strlen(global)]))
            {
                p_low = p + base;
                break;
            }
        }
    }
    base = count - strlen(global);
    for (; base > 0; base--)
    {
        if (p[base] == '~')
        {
            if (0 == strncmp((char *)p + base, global, strlen(global)) && isprint(p[base + strlen(global)]))
            {
                p_high = p + base;
                break;
            }
        }
    }
    if (p_high != NULL && p_low != NULL)
        bit_map_size = (int)(p_high - p_low);
    bit_map_size = bit_map_size / 8 + 1;
    bit_map = (char *)malloc(bit_map_size * sizeof(char));
    memset(bit_map, '\0', bit_map_size);
}

int fwgettracelevel(int appid)
{
    return g_app_map[appid].__tracelevel__;
}

int fwwrapcheck(unsigned int appid)
{
    /*struct stat F;*/
    int ret;
    if (strcmp(__tracefile__, "") != 0)
    {
        /** confirmed that it is going to file **/
        /** check if LOGSIZE is defined **/
        if (__tracesize__)
        {
            ret = ftell(stdout);
            if (ret < 0)
            {
                perror("fw: ftell failed\n");
                return 0;
            }
            if (ret >= __tracesize__)
            {
                ret = fseek(stdout, 0, SEEK_SET);
                if (ret < 0)
                {
                    perror("fseek failed");
                    return 0;
                }
                return 0;
            }
        }
        else
        {
            return 1;
        }
    }
    return 1;
}

int fwstoretracedata(unsigned int appid, char *filename, int lineno)
{
    printf("APPID is %d for file %s line %d \n", appid, filename, lineno);
    strcpy(g_app_map[appid].__filename__, filename);
    g_app_map[appid].__lineno__ = lineno;
    return 0;
}

void fwactualtracebytes(unsigned int appid, char *filename, int lineno, int level, unsigned char *buffer, unsigned long length)
{
    char *T;
    if (!fwwrapcheck(appid))
    {
        return;
    }

    if (g_app_map[appid].__tracelevel__ >= level)
    {
        printf("[%lu]", pthread_self());
        printf("[%u]", appid);
        T = fwtimestring();
        if (T)
        {
            printf("[%s]", T);
            printf("[%s]", filename);
            printf("[%d]\n", lineno);
            free(T);
        }
        dumpBytesTo(stdout, buffer, length);
    }
    fflush(stdout);
}

char *fwtimestring()
{
    time_t epoch;
    char *buf;
    struct tm *outTm;

    buf = (char *)malloc(256);
    if (buf == NULL)
        return NULL;
    epoch = getEpoch();

    outTm = gmtime((const time_t *)&epoch);
    if (NULL == outTm)
    {
        free(buf);
        return NULL;
    }
    strcpy(buf, asctime(outTm));
    buf[strlen(buf) - 1] = '\0';

    return buf;
}

int fwsemcreate(key_t key, int initval)
{
#if 0
    register int    semval = 0;
    int id;
    union semun
    {
        int val;
        struct semid_ds *buf;
        ushort *array;
    } semctl_arg;

    if(key == IPC_PRIVATE)
        return -1;
    else if (key == (key_t) -1)
        return -1;

    again:
    printf("before semget\n");
    if((id = semget(key, 3, 0777 | IPC_CREAT)) <0)
    {
        perror("semget");
        return -1;
    }
    printf("after semget\n");

    printf("before semop\n");
    if(semop(id, &op_lock[0], 2) < 0)
    {
        if(errno == EINVAL)
            goto again;
        perror("can't lock");
    }
    printf("after semop\n");

    if((semval == semctl(id, 1, GETVAL, 0)) <0)
        perror("can't GETVAL");

    printf("after semctl1\n");
    printf("<%d>\n", semval);
    if(semval == 0)
    {
        semctl_arg.val = initval;
        if(semctl(id, 0, SETVAL, semctl_arg) < 0)
            perror("can't SETVAL[0]");
        semctl_arg.val = BIGCOUNT;
        if(semctl(id, 1, SETVAL, semctl_arg) < 0)
            perror("can't SETVAL[1]");
    }

    printf("before semop\n");
    if(semop(id, &op_endcreate[0], 2) < 0)
        perror("can't end create");
    printf("after semop\n");
    return id;
#endif
    return 0;
}

int fwsemopen(key_t key)
{
    int id;

    if (key == IPC_PRIVATE)
        return -1;

    else if (key == (key_t)-1)
        return -1;
    if ((id = semget(key, 3, 0)) < 0)
        return -1;

    if (semop(id, &op_open[0], 1) < 0)
        perror("can't open");
    return id;
}

void fwsemrm(int passed_id)
{
    if (semctl(passed_id, 0, IPC_RMID, 0) < 0)
        perror("can't IPC_RMID");
}

void fwsemclose(int passed_id)
{
    register int semval;

    if (semop(passed_id, &op_close[0], 3) < 0)
        perror("can't semop");

    if ((semval = semctl(passed_id, 1, GETVAL, 0)) < 0)
        perror("can't GETVAL");

    if (semval > BIGCOUNT)
        perror("sem[1] > BIGCOUNT");
    else if (semval == BIGCOUNT)
        fwsemrm(passed_id);
    else if (semop(passed_id, &op_unlock[0], 1) < 0)
        perror("can't unlock");
}

void fwsemwait(int passed_id)
{
    fwsemop(passed_id, -1);
}

void fwsemsignal(int passed_id)
{
    fwsemop(passed_id, 1);
}

void fwsemop(int passed_id, int value)
{
    if ((op_op[0].sem_op = value) == 0)
        perror("can't have value == 0");

    if (semop(passed_id, &op_op[0], 1) < 0)
        perror("fwsemop error");
}

int fwsemget(key_t semKey, int option)
{
    int id;
    id = -1;
    switch (option)
    {
    case 1:
        id = fwsemcreate(semKey, 1);
        break;

    case 0:
        id = fwsemopen(semKey);
        break;
    }
    return id;
}

void fwlock(int id)
{
    fwsemwait(id);
}

void fwunlock(int id)
{
    fwsemsignal(id);
}

int queueRead(int qid, int type, int length, char **payload, int *typeread)
{
    int ret;
    char *buffer;
    unsigned char *scan;

    buffer = (char *)malloc(length + 4);
    if (buffer == NULL)
    {
        fprintf(stderr, "fw: malloc failed <%s><%d>\n", __FILE__, __LINE__);
        *payload = NULL;
        return 0;
    }
    ret = msgrcv(qid, buffer, length, type, 0);
    if (ret < 0)
    {
        perror("msgrcv\n");
        return -1;
    }
    scan = (unsigned char *)buffer;
    *typeread = bufferGetUint4_linux(scan);
    scan += 4;
    *payload = (char *)scan;
    return length;
}

int queueWrite(int qid, int type, int length, char *payload)
{
    unsigned char buffer[MAXUDPLEN];
    unsigned char *scan;
    int ret;

    scan = buffer;
    bufferAddUint4_linux(scan, type);
    scan += 4;
    memcpy(scan, payload, length);
    scan += length;

    ret = msgsnd(qid, (void *)buffer, length, 0);
    if (ret < 0)
    {
        perror("msgsnd\n");
        return -1;
    }
    return length;
}

mQueue *fwListAddMqEntry(int qid, int length, int type, int pipeFd0, int pipeFd1, void *cdata, int (*fn)(int, int, int, void *, void *))
{
    mQueue *listNode = (mQueue *)malloc(sizeof(mQueue));
    if (NULL == listNode)
    {
        return NULL;
    }

    if (fwdebug)
        printf(" Enter fwListAddMqEntry() [1]\n");
    listNode->qid = qid;
    listNode->length = length;
    listNode->type = type;
    listNode->pipeFd[0] = pipeFd0;
    listNode->pipeFd[1] = pipeFd1;
    listNode->clientData = cdata;
    listNode->callBack = fn;
    if (mqlist.list == NULL)
    {
        mqlist.list = NULL;
        mqlist.list = listNode;
    }
    else
    {
        mQueue *tmp = mqlist.list;
        mQueue *prev = NULL;
        while (tmp != NULL)
        {
            /* Checks Before adding a node */
            if (tmp->qid == listNode->qid)
            {
                if ((tmp->type == listNode->type) || tmp->type <= 0 ||
                    listNode->type <= 0)
                {
                    if (fwdebug)
                        printf(" Exit fwListAddMqEntry() [2]\n");
                    free(listNode);
                    return (NULL);
                }
            }

            prev = tmp;
            tmp = tmp->nextEntry;
        }
        listNode->nextEntry = tmp;
        prev->nextEntry = listNode;
    }
    if (fwdebug)
        printf(" Exit fwListAddMqEntry() [3]\n");
    return (listNode);
}

int fwListRemoveMqEntry(unsigned int appid, int quid, int type)
{
    int ret;
    mQueue *tmp = mqlist.list;
    mQueue *prev = NULL;
    if (fwdebug)
        printf(" Enter fwListRemoveMqEntry() [1]\n");
    while (tmp != NULL)
    {
        if ((tmp->qid == quid) && (tmp->type == type))
        {
            if (tmp == mqlist.list)
                mqlist.list = tmp->nextEntry;
            else
            {
                prev->nextEntry = tmp->nextEntry;
            }

            ret = pthread_cancel(tmp->threadId);
            pthread_join(tmp->threadId, NULL);
            if (ret < 0)
                perror("pthread_cancel\n");
            fwMultiplexRemove(appid, tmp->pipeFd[0]);
            close(tmp->pipeFd[0]);
            close(tmp->pipeFd[1]);
            free(tmp);
            if (fwdebug)
                printf(" Exit fwListRemoveMqEntry() [2]\n");
            return (1);
        }
        prev = tmp;
        tmp = tmp->nextEntry;
    }
    if (fwdebug)
        printf(" Exit fwListRemoveMqEntry() [3]\n");
    return (-1);
}

int fwMultiplexAddQueue(unsigned int appid, int qid, int type, int length, void *cdata, int (*fn)(int, int, int, void *, void *))
{
    mQueue *b;
    int pipefd[2];
    /*pthread_t     tid;*/

    pthread_mutex_lock(&fwqueueMu);
    if (fwdebug)
        printf(" Enter fwMultiplexAddQue() [1]\n");
    if (qid < 0)
    {
        fprintf(stderr, "fwMultiplexAddQueue: bad qid\n");
        pthread_mutex_unlock(&fwqueueMu);
        return (0);
    }
    if (pipe(pipefd) < 0)
    {
        perror("fwMultiplexAddQue : Pipe Error");
        pthread_mutex_unlock(&fwqueueMu);
        return (0);
    }
    b = fwListAddMqEntry(qid, length, type, pipefd[0], pipefd[1], cdata, fn);
    if (b == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddQue() [3]\n");
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwqueueMu);
        return (0);
    }
    fwMultiplexAdd(appid, pipefd[0], (void *)&appid, fwReadFromPipe);
    if (pthread_create(&b->threadId, NULL, fwThreadFn, b) < 0)
    {
        if (fwdebug)
            perror("fwMultiplexAddQue:pthread_create");
        free(b);
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwqueueMu);
        return (0);
    }

    if (fwdebug)
        printf(" Exit fwMultiplexAddQue() [4]\n");
    pthread_mutex_unlock(&fwqueueMu);
    return (1);
}

int fwMultiplexRemoveQueue(unsigned int appid, int qid, int type)
{
    int status;

    pthread_mutex_lock(&fwqueueMu);
    if (fwdebug)
        printf(" Enter fwMultiplexRemove() [1]\n");
    status = fwListRemoveMqEntry(appid, qid, type);
    if (fwdebug)
        printf(" Exit fwMultiplexRemove() [2]\n");
    pthread_mutex_unlock(&fwqueueMu);
    return (status);
}

void fwmask()
{
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGALRM);
    sigaddset(&newset, SIGUSR1);
    sigaddset(&newset, SIGUSR2);
    pthread_sigmask(SIG_BLOCK, &newset, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}

void *fwThreadFn(void *tnode)
{
    return NULL;
}

int fwReadFromPipe(int fd, void *cData)
{
    return (1);
}

void fwPrintQueueList()
{
    mQueue *tmp = mqlist.list;
    printf("*********** Queue List *************\n");
    while (tmp != NULL)
    {
        printf("Queue Id: <%d>\n", tmp->qid);
        tmp = tmp->nextEntry;
    }
}

/*****************************************************************************/
/** ftpDebug *****************************************************************/
/*****************************************************************************/
void ftpDebug(int flag)
{
    ftpDebugFlag = flag;
}

/*****************************************************************************/
/** ftpClose *****************************************************************/
/*****************************************************************************/
void ftpClose(ftp_t *F)
{
    if (F->cin)
    {
        fclose(F->cin);
        F->cin = NULL;
    }
    if (F->cout)
    {
        fclose(F->cout);
        F->cout = NULL;
    }
    if (!(F->sd < 0))
    {
        close(F->sd);
    }
    if (!(F->sd_data < 0))
    {
        close(F->sd_data);
    }
    free(F);
}

/*****************************************************************************/
/** ftpCommand ***************************************************************/
/*****************************************************************************/
void ftpCommand(ftp_t *F, char *format, ...)
{
    va_list P;

    va_start(P, format);
    if (ftpDebugFlag)
    {
        fprintf(stderr, "-->   ");
        vfprintf(stderr, format, P);
        fprintf(stderr, "\n");
    }
    vfprintf(F->cout, format, P);
    fprintf(F->cout, "\r\n");
    va_end(P);
}

/*****************************************************************************/
/** ftpReplyGet **************************************************************/
/*****************************************************************************/
int ftpReplyGet(ftp_t *F, int expecteof)
{
    int c,
        dig,
        code;
    char *cp;
    int originalcode = 0,
        continuation = 0;

    for (;;)
    {
        dig = code = 0;
        cp = ftpReplyString;
        while ((c = getc(F->cin)) != '\n')
        {
            if (c == IAC)
            { /* handle telnet commands */
                switch (c = getc(F->cin))
                {
                case WILL:
                case WONT:
                    c = getc(F->cin);
                    fprintf(F->cout, "%c%c%c", IAC, DONT, c);
                    fflush(F->cout);
                    break;
                case DO:
                case DONT:
                    c = getc(F->cin);
                    fprintf(F->cout, "%c%c%c", IAC, WONT, c);
                    fflush(F->cout);
                    break;
                default:
                    break;
                }
                continue;
            }
            dig++;
            if (c == EOF)
            {
                if (expecteof)
                {
                    return (221);
                }
                return (421);
            }

            if (dig < 4 && isdigit(c))
                code = code * 10 + (c - '0');

            if (dig == 4 && c == '-')
            {
                if (continuation)
                    code = 0;
                continuation++;
            }
            if (cp < &ftpReplyString[sizeof(ftpReplyString) - 1])
                *cp++ = c;
        }
        *cp = '\0';
        if (ftpDebugFlag)
        {
            fprintf(stderr, "<--   ");
            fprintf(stderr, "%s\n", ftpReplyString);
        }

        if (continuation && code != originalcode)
        {
            if (originalcode == 0)
                originalcode = code;
            continue;
        }
        return (code);
    }
}

/*****************************************************************************/
/** ftpConnect ***************************************************************/
/*****************************************************************************/
ftp_t *ftpConnect(char *host, unsigned short port, char *user, char *password)
{
    ftp_t *F;
    unsigned int len,
        reply;
    struct hostent *hp = 0;

    F = NULL;
    if (!(F = (ftp_t *)malloc(sizeof(ftp_t))))
    {
        return NULL;
    }
    memset(F, 0, sizeof(ftp_t));
    F->sd = -1;
    F->sd_data = -1;

    F->remotectladdr.sin_addr.s_addr = inet_addr(host);

    if ((int)F->remotectladdr.sin_addr.s_addr != (-1))
    {
        /** Internet address supplied **/
        F->remotectladdr.sin_family = AF_INET;
    }
    else
    {
        if ((hp = gethostbyname(host)) == NULL)
        {
            /** Not a valid hostname either **/
            free(F);
            return NULL;
        }
        /** Take this address to be the first approximation **/
        F->remotectladdr.sin_family = hp->h_addrtype;
        memcpy((caddr_t) & (F->remotectladdr.sin_addr), hp->h_addr_list[0], hp->h_length);
    }

    if ((F->sd = socket(F->remotectladdr.sin_family, SOCK_STREAM, 0)) < 0)
    {
        perror("ftpConnect (socket)");
        free(F);
        return NULL;
    }

    F->remotectladdr.sin_port = port;

    while (connect(F->sd, (struct sockaddr *)&(F->remotectladdr), sizeof(struct sockaddr_in)) < 0)
    {
        if (hp && hp->h_addr_list[1])
        {
            int oerrno = errno;

            errno = oerrno;
            perror(NULL);
            hp->h_addr_list++;
            memcpy((caddr_t) & (F->remotectladdr.sin_addr), hp->h_addr_list[0], hp->h_length);

            close(F->sd);

            if ((F->sd = socket(F->remotectladdr.sin_family, SOCK_STREAM, 0)) < 0)
            {
                perror("ftpConnect (socket)");
                free(F);
                return NULL;
            }

            continue;
        }

        perror("ftpConnect (connect)");
        ftpClose(F);
        return NULL;
    }

    len = sizeof(struct sockaddr_in);

    if (getsockname(F->sd, (struct sockaddr *)&(F->localctladdr), &len) < 0)
    {
        perror("ftpConnect (getsockname)");
        ftpClose(F);
        return NULL;
    }

    F->cin = fdopen(F->sd, "r");
    F->cout = fdopen(dup(F->sd), "w");

    if (F->cin == NULL || F->cout == NULL)
    {
        fprintf(stderr, "ftpConnect (fdopen) failed\n");
        ftpClose(F);
        return NULL;
    }

    setbuf(F->cout, NULL);
    /** The Startup Message **/
    if (ftpReplyGet(F, 0) / 100 > 2)
    {
        ftpClose(F);
        return NULL;
    }

    ftpCommand(F, (char *)"USER %s", user);
    reply = ftpReplyGet(F, 0);
    if (reply == 331)
    {
        /** Password Required **/
        ftpCommand(F, (char *)"PASS %s", password);
        reply = ftpReplyGet(F, 0);
    }
    if (reply != 230)
    {
        ftpClose(F);
        return NULL;
    }
    ftpCommand(F, (char *)"TYPE I");
    reply = ftpReplyGet(F, 0);
    if (reply != 200)
    {
        ftpClose(F);
        return NULL;
    }

    F->data_addr = F->localctladdr;
    F->data_addr.sin_port = 0; /** System picks one **/

    if ((F->sd_data = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("ftpConnect (socket:data)");
        ftpClose(F);
        return NULL;
    }

    if (setsockopt(F->sd_data, SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes)) < 0)
    {
        perror("ftpConnect (setsockopt:REUSEADDR:data)");
        ftpClose(F);
        return NULL;
    }
    if (bind(F->sd_data, (struct sockaddr *)&(F->data_addr), sizeof(struct sockaddr_in)) < 0)
    {
        perror("ftpConnect (bind:data)");
        ftpClose(F);
        return NULL;
    }
    len = sizeof(struct sockaddr_in);

    if (getsockname(F->sd_data, (struct sockaddr *)&(F->data_addr), &len) < 0)
    {
        perror("ftpConnect (getsockname:data)");
        ftpClose(F);
        return NULL;
    }

    if (listen(F->sd_data, 1) < 0)
    {
        perror("ftpConnect (listen:data)");
        ftpClose(F);
        return NULL;
    }

    return (F);
}

/*****************************************************************************/
/** ftpPort ******************************************************************/
/*****************************************************************************/
int ftpPort(ftp_t *F)
{
    char *a,
        *p;

    /** WARNING: Check for Endian problems here! **/
    a = (char *)&(F->data_addr.sin_addr.s_addr);
    p = (char *)&(F->data_addr.sin_port);

    ftpCommand(F, (char *)"PORT %d,%d,%d,%d,%d,%d",
               ((int)(a[0]) & 0x00FF),
               ((int)(a[1]) & 0x00FF),
               ((int)(a[2]) & 0x00FF),
               ((int)(a[3]) & 0x00FF),
               ((int)(p[0]) & 0x00FF),
               ((int)(p[1]) & 0x00FF));
    return (ftpReplyGet(F, 0));
}

/*****************************************************************************/
/** ftpSend ******************************************************************/
/*****************************************************************************/
int ftpSend(ftp_t *F, char *local, char *remote)
{
    int fd, sd;
    socklen_t len;
    int count;
    char buffer[4096];
    struct sockaddr_in
        S;

    if ((fd = open(local, O_RDONLY)) < 0)
    {
        /** Fail **/
        return 0;
    }

    ftpPort(F);

    ftpCommand(F, (char *)"STOR %s", remote);
    ftpReplyGet(F, 0);
    len = sizeof(struct sockaddr_in);
    if ((sd = accept(F->sd_data, (struct sockaddr *)&S, &len)) < 0)
    {
        /** Fail **/
        close(fd);
        return 0;
    }

    int ret = 0;
    ret = ret;
    while ((count = read(fd, buffer, sizeof(buffer))) > 0)
    {
        ret = write(sd, buffer, count);
    }

    close(fd);
    close(sd);

    ftpReplyGet(F, 0); /** The Transfer End indication **/
    return 1;
}

/*****************************************************************************/
/** ftpTerminate *************************************************************/
/*****************************************************************************/
void ftpTerminate(ftp_t *F)
{
    ftpCommand(F, (char *)"QUIT");
    ftpReplyGet(F, 0);
    ftpClose(F);
}

/*****************************************************************************/
/** ftpRecv ******************************************************************/
/*****************************************************************************/
int ftpRecv(ftp_t *F, char *local, char *remote)
{
    int fd,
        sd;
    socklen_t len;
    int reply,
        count;
    char buffer[4096];
    struct sockaddr_in
        S;

    if ((fd = open(local, O_WRONLY | O_CREAT, 0666)) < 0)
    {
        /** Fail **/
        return 0;
    }

    ftpPort(F);

    ftpCommand(F, (char *)"RETR %s", remote);
    reply = ftpReplyGet(F, 0);
    if (reply == 550)
    {
        close(fd);
        return 0;
    }

    len = sizeof(struct sockaddr_in);
    if ((sd = accept(F->sd_data, (struct sockaddr *)&S, &len)) < 0)
    {
        /** Fail **/
        close(fd);
        return 0;
    }

    int ret = 0;
    ret = ret;
    while ((count = read(sd, buffer, sizeof(buffer))) > 0)
    {
        ret = write(fd, buffer, count);
    }

    close(fd);
    close(sd);

    ftpReplyGet(F, 0); /** The Transfer End indication **/
    return 1;
}

/*****************************************************************************/
/** ftpGet *******************************************************************/
/*****************************************************************************/
int ftpGet(char *local, char *remote, char *host, char *user, char *password)
{
    ftp_t *F;

    if (!local || !host)
    {
        /** Fail **/
        return 0;
    }

    /** Set Defaults ... **/
    remote = remote ? remote : local;
    user = user ? user : (char *)"anonymous";
    password = password ? password : (char *)"anon@";

    if (!(F = ftpConnect(host, 21, user, password)))
    {
        /** Fail **/
        return 0;
    }

    if (ftpRecv(F, local, remote))
    {
        ftpClose(F);
        return 0;
    }
    remove(local);
    ftpTerminate(F);
    return 1;
}

/*****************************************************************************/
/** ftpPut *******************************************************************/
/*****************************************************************************/
int ftpPut(char *local, char *remote, char *host, char *user, char *password)
{
    ftp_t *F;

    if (!local || !host)
    {
        /** Fail **/
        return 0;
    }

    /** Set Defaults ... **/
    remote = remote ? remote : local;
    user = user ? user : (char *)"anonymous";
    password = password ? password : (char *)"anon@";

    if (!(F = ftpConnect(host, 21, user, password)))
    {
        /** Fail **/
        return 0;
    }

    if (ftpSend(F, local, remote))
    {
        ftpClose(F);
        return 0;
    }

    ftpTerminate(F);
    return 1;
}

/*****************************************************************************/
/*******************************TASK******************************************/
/*****************************************************************************/
TASK *fwListAddTaskEntry(int taskId, int pipeFd0, int pipeFd1, void *cdata, int (*fn)(int, int, void *), int (*workFn)(void *), void *params)
{
    TASK *listNode = (TASK *)malloc(sizeof(TASK));

    if (fwdebug)
        printf(" Enter fwListAddTaskEntry() [1]\n");
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" fwListAddTaskEntry(): Buffer Allocation Failure\n");
        return NULL;
    }
    listNode->taskId = taskId;
    listNode->pipeFd[0] = pipeFd0;
    listNode->pipeFd[1] = pipeFd1;
    listNode->clientData = cdata;
    listNode->callBack = fn;
    listNode->workFn = workFn;
    listNode->params = params;
    listNode->nextEntry = NULL;
    if (tlist.list == NULL)
    {
        tlist.list = NULL;
        tlist.list = listNode;
    }
    else
    {
        TASK *tmp = tlist.list;
        TASK *prev = NULL;
        while (tmp != NULL)
        {
            prev = tmp;
            tmp = tmp->nextEntry;
        }
        listNode->nextEntry = tmp;
        prev->nextEntry = listNode;
    }
    if (fwdebug)
        printf(" Exit fwListAddTaskEntry() [3]\n");
    return (listNode);
}

int fwListRemoveTaskEntry(unsigned int appid, int taskId)
{
    int ret;
    TASK *tmp = tlist.list;
    TASK *prev = NULL;
    if (fwdebug)
        printf(" Enter fwListRemoveTaskEntry() [1]\n");
    while (tmp != NULL)
    {
        if (tmp->taskId == taskId)
        {
            if (tmp == tlist.list)
                tlist.list = tmp->nextEntry;
            else
            {
                prev->nextEntry = tmp->nextEntry;
            }

            ret = pthread_cancel(tmp->threadId);
            pthread_join(tmp->threadId, NULL);
            if (ret < 0)
                perror("pthread_cancel\n");
            fwMultiplexRemove(appid, tmp->pipeFd[0]);
            close(tmp->pipeFd[0]);
            close(tmp->pipeFd[1]);
            free(tmp);
            if (fwdebug)
                printf(" Exit fwListRemoveTaskEntry() [2]\n");
            return (1);
        }
        prev = tmp;
        tmp = tmp->nextEntry;
    }
    if (fwdebug)
        printf(" Exit fwListRemoveTaskEntry() [3]\n");
    return (-1);
}

int fwGetTaskId()
{
    TASK *tmp;
    numberOfTask++;
    if (numberOfTask == 0)
        numberOfTask++;
    tmp = tlist.list;
    if (tmp == NULL)
        return numberOfTask;
    while (tmp != NULL)
    {
        if (tmp->taskId == numberOfTask)
        {
            numberOfTask++;
            tmp = tlist.list;
        }
        else
            tmp = tmp->nextEntry;
    }
    return (numberOfTask);
}

int fwStartTask(unsigned int appid, int (*workFn)(void *), void *arg, void *cdata, int (*cb)(int, int, void *))
{
    TASK *b;
    int pipefd[2];
    /*pthread_t     tid;*/
    int taskId;

    pthread_mutex_lock(&fwtaskMu);
    if (fwdebug)
        printf(" Enter fwStartTask() [1]\n");

    taskId = fwGetTaskId();
    if (pipe(pipefd) < 0)
    {
        perror("fwStartTask: Pipe Error");
        pthread_mutex_unlock(&fwtaskMu);
        return (0);
    }
    b = fwListAddTaskEntry(taskId, pipefd[0], pipefd[1], cdata, cb, workFn, arg);
    if (b == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddQue() [3]\n");
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwtaskMu);
        return (0);
    }
    fwMultiplexAdd(appid, pipefd[0], (void *)&appid, fwReadFromTaskPipe);
    if (pthread_create(&b->threadId, NULL, fwTaskThreadFn, b) < 0)
    {
        if (fwdebug)
            perror("fwMultiplexAddQue:pthread_create");
        free(b);
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwtaskMu);
        return (0);
    }

    if (fwdebug)
        printf(" Exit fwMultiplexAddQue() [4]\n");
    pthread_mutex_unlock(&fwtaskMu);
    return (taskId);
}

int fwCancelTask(unsigned int appid, int taskId)
{
    int status;

    pthread_mutex_lock(&fwtaskMu);
    if (fwdebug)
        printf(" Enter fwCancelTask() [1]\n");
    status = fwListRemoveTaskEntry(appid, taskId);
    if (fwdebug)
        printf(" Exit fwCancelTask() [2]\n");
    pthread_mutex_unlock(&fwtaskMu);
    return (status);
}

void *fwTaskThreadFn(void *tnode)
{
    TASK *node;
    int ret;

    if (fwdebug)
        printf(" Enter fwTaskThreadFn() [1]\n");
    fwmask();
    node = (TASK *)tnode;
    ret = (*node->workFn)((void *)node->params);
    ret = tcpWrite(node->pipeFd[1], (char *)&ret, sizeof(int));
    if (ret < 0)
    {
        pthread_exit((void *)0);
    }
    if (fwdebug)
        printf(" Exit fwTaskThreadFn() [1]\n");
    return NULL;
}

int fwReadFromTaskPipe(int fd, void *cData)
{
    int length;
    int ret;
    TASK *tmp = tlist.list;
    int match = 0;
    unsigned int appid = *((unsigned int *)cData);
    if (fwdebug)
        printf(" Enter readFromtaskPipe() [1]\n");
    while (tmp != NULL)
    {
        if ((tmp->pipeFd[0] == fd))
        {
            match = 1;
            break;
        }
        tmp = tmp->nextEntry;
    }
    if (match == 0)
    {
        if (fwdebug)
            printf(" Exit readFromTaskPipe() [1]\n");
        return (0);
    }
    length = tcpRead(fd, (char *)&ret, sizeof(int));
    if (length == 0)
    {
        fwListRemoveTaskEntry(appid, tmp->taskId);
        return (0);
    }
    (*tmp->callBack)(tmp->taskId, ret, tmp->clientData);
    fwListRemoveTaskEntry(appid, tmp->taskId);
    if (fwdebug)
        printf(" Exit readFromTaskPipe() [2]\n");
    return (1);
}

void fwPrintTaskList()
{
    TASK *tmp = tlist.list;
    printf("*********** Task List *************\n");
    while (tmp != NULL)
    {
        printf("Task Id: <%d>\n", tmp->taskId);
        tmp = tmp->nextEntry;
    }
}

void fwPrintList()
{
    fwPrintTimerList();
    fwPrintSocketList();
    fwPrintQueueList();
    fwPrintTaskList();
    fwPrintServiceList();
}

/*****************************************************************************/
/*******************************SERVICE******************************************/
/*****************************************************************************/
SERVICE *fwListAddServiceEntry(int serviceId, int pipeFd0, int pipeFd1, void *cdata, int (*fn)(int, int, void *), int (*workFn)(void *, void *), void *params)
{
    SERVICE *listNode = (SERVICE *)malloc(sizeof(SERVICE));

    if (fwdebug)
        printf(" Enter fwListAddServiceEntry() [1]\n");
    if (listNode == NULL)
    {
        if (fwdebug)
            printf(" fwListAddServiceEntry(): Buffer Allocation Failure\n");
        return NULL;
    }
    listNode->serviceId = serviceId;
    listNode->pipeFd[0] = pipeFd0;
    listNode->pipeFd[1] = pipeFd1;
    listNode->clientData = cdata;
    listNode->callBack = fn;
    listNode->workFn = workFn;
    listNode->params = params;
    listNode->nextEntry = NULL;
    if (servicelist.list == NULL)
    {
        servicelist.list = NULL;
        servicelist.list = listNode;
    }
    else
    {
        SERVICE *tmp = servicelist.list;
        SERVICE *prev = NULL;
        while (tmp != NULL)
        {
            prev = tmp;
            tmp = tmp->nextEntry;
        }
        listNode->nextEntry = tmp;
        prev->nextEntry = listNode;
    }
    if (fwdebug)
        printf(" Exit fwListAddServiceEntry() [3]\n");
    return (listNode);
}

int fwListRemoveServiceEntry(unsigned int appid, int serviceId)
{
    int ret;
    SERVICE *tmp = servicelist.list;
    SERVICE *prev = NULL;
    if (fwdebug)
        printf(" Enter fwListRemoveServiceEntry() [1]\n");
    while (tmp != NULL)
    {
        if (tmp->serviceId == serviceId)
        {
            if (tmp == servicelist.list)
                servicelist.list = tmp->nextEntry;
            else
            {
                prev->nextEntry = tmp->nextEntry;
            }

            ret = pthread_cancel(tmp->threadId);
            pthread_join(tmp->threadId, NULL);
            if (ret < 0)
                perror("pthread_cancel\n");
            fwMultiplexRemove(appid, tmp->pipeFd[0]);
            close(tmp->pipeFd[0]);
            close(tmp->pipeFd[1]);
            free(tmp);
            if (fwdebug)
                printf(" Exit fwListRemoveServiceEntry() [2]\n");
            return (1);
        }
        prev = tmp;
        tmp = tmp->nextEntry;
    }
    if (fwdebug)
        printf(" Exit fwListRemoveServiceEntry() [3]\n");
    return (-1);
}

int fwGetServiceId()
{
    SERVICE *tmp;
    numberOfService++;
    if (numberOfService == 0)
        numberOfService++;
    tmp = servicelist.list;
    if (tmp == NULL)
        return numberOfService;
    while (tmp != NULL)
    {
        if (tmp->serviceId == numberOfService)
        {
            numberOfService++;
            tmp = servicelist.list;
        }
        else
            tmp = tmp->nextEntry;
    }
    return (numberOfService);
}

int fwStartService(unsigned int appid, int (*workFn)(void *, void *), void *arg, void *cdata, int (*cb)(int, int, void *))
{
    SERVICE *b;
    int pipefd[2];
    /*pthread_t     tid;*/
    int serviceId;

    pthread_mutex_lock(&fwserviceMu);
    if (fwdebug)
        printf(" Enter fwStartService() [1]\n");

    serviceId = ++numberOfService;
    if (pipe(pipefd) < 0)
    {
        perror("fwStartService: Pipe Error");
        pthread_mutex_unlock(&fwserviceMu);
        return (0);
    }
    b = fwListAddServiceEntry(serviceId, pipefd[0], pipefd[1], cdata, cb, workFn, arg);
    if (b == NULL)
    {
        if (fwdebug)
            printf(" Exit fwMultiplexAddQue() [3]\n");
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwserviceMu);
        return (0);
    }
    fwMultiplexAdd(appid, pipefd[0], NULL, fwReadFromServicePipe);
    if (pthread_create(&b->threadId, NULL, fwServiceThreadFn, b) < 0)
    {
        if (fwdebug)
            perror("fwMultiplexAddQue:pthread_create");
        free(b);
        close(pipefd[0]);
        close(pipefd[1]);
        pthread_mutex_unlock(&fwserviceMu);
        return (0);
    }

    if (fwdebug)
        printf(" Exit fwMultiplexAddQue() [4]\n");
    pthread_mutex_unlock(&fwserviceMu);
    return (serviceId);
}

int fwCancelService(unsigned int appid, int serviceId)
{
    int status;

    pthread_mutex_lock(&fwserviceMu);
    if (fwdebug)
        printf(" Enter fwCancelService() [1]\n");
    status = fwListRemoveServiceEntry(appid, serviceId);
    if (fwdebug)
        printf(" Exit fwCancelService() [2]\n");
    pthread_mutex_unlock(&fwserviceMu);
    return (status);
}

void *fwServiceThreadFn(void *tnode)
{
    SERVICE *node;
    int ret;

    if (fwdebug)
        printf(" Enter fwServiceThreadFn() [1]\n");
    fwmask();
    node = (SERVICE *)tnode;
    ret = (*node->workFn)((void *)node->params, tnode);
    ret = tcpWrite(node->pipeFd[1], (char *)&ret, sizeof(int));
    if (ret < 0)
    {
        pthread_exit((void *)0);
    }
    if (fwdebug)
        printf(" Exit fwServiceThreadFn() [1]\n");
    return NULL;
}

int fwReadFromServicePipe(int fd, void *cData)
{
    int length;
    int ret;
    SERVICE *tmp = servicelist.list;
    int match = 0;
    if (fwdebug)
        printf(" Enter readFromtaskPipe() [1]\n");
    while (tmp != NULL)
    {
        if ((tmp->pipeFd[0] == fd))
        {
            match = 1;
            break;
        }
        tmp = tmp->nextEntry;
    }
    if (match == 0)
    {
        if (fwdebug)
            printf(" Exit readFromServicePipe() [1]\n");
        return (0);
    }
    length = tcpRead(fd, (char *)&ret, sizeof(int));
    if (length == 0)
    {
        fwListRemoveServiceEntry(0, tmp->serviceId);
        return (0);
    }
    (*tmp->callBack)(tmp->serviceId, ret, tmp->clientData);
    /*	fwListRemoveServiceEntry( tmp->serviceId ); */
    if (fwdebug)
        printf(" Exit readFromServicePipe() [2]\n");
    return (1);
}

void fwPrintServiceList()
{
    SERVICE *tmp = servicelist.list;
    printf("*********** Service List *************\n");
    while (tmp != NULL)
    {
        printf("Service Id: <%d>\n", tmp->serviceId);
        tmp = tmp->nextEntry;
    }
}

void *fwSync(int result, void *tnode)
{
    SERVICE *node;
    int ret;

    if (fwdebug)
        printf(" Enter fwSync() [1]\n");
    node = (SERVICE *)tnode;
    ret = tcpWrite(node->pipeFd[1], (char *)&result, sizeof(int));
    if (ret < 0)
    {
        pthread_exit((void *)0);
    }
    if (fwdebug)
        printf(" Exit fwSync() [1]\n");
    return NULL;
}

int genRandom(int min, int max)
{
    double x = (double)rand() / RAND_MAX;

    return (max - min + 1) * x + min;
}

int fileGetString(char *filename, char *begintoken, char delim, char *lval, char *rval)
{
    FILE *fpt;
    char buffer[1024];
    char starttoken[1024];
    char locallval[1024];

    strcpy(rval, "");
    strcpy(buffer, "");
    strcpy(starttoken, "BEGIN_");
    strcat(starttoken, begintoken);

    fpt = fopen(filename, "r");
    if (fpt == NULL)
    {
        fprintf(stderr, "fw: fileGetString: could not open <%s> for reading\n", filename);
        return 0;
    }

    while (fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';
        trim(buffer);
        if (buffer[0] == '#')
            continue;
        if (strcmp(buffer, "") == 0)
            continue;
        if (strcmp(starttoken, buffer) == 0)
        {
            while (fgets(buffer, 1023, fpt) != NULL)
            {
                buffer[strlen(buffer) - 1] = '\0';
                trim(buffer);
                if (buffer[0] == '#')
                    continue;
                if (strcmp(buffer, "") == 0)
                    continue;
                if (strcmp(buffer, "END") == 0)
                {
                    fprintf(stderr, "fw: fwGetString: could not find lval: <%s> in block beginning with <%s> [Encountered END token !]\n",
                            lval, starttoken);
                    strcpy(rval, "");
                    fclose(fpt);
                    return 0;
                }
                strcpy(locallval, "");
                getLvalRval(buffer, delim, locallval, rval);
                if (strcmp(locallval, lval) == 0)
                {
                    fclose(fpt);
                    return 1;
                }
            }
            fprintf(stderr, "fw: fwGetString: could not find lval: <%s> in block beginning with <%s> [Could not find END token also !]\n",
                    lval, starttoken);
            strcpy(rval, "");
            fclose(fpt);
            return 0;
        }
    }
    fprintf(stderr, "fw: fwGetString: could not find the block beginning with <%s>\n", starttoken);
    strcpy(rval, "");
    fclose(fpt);
    return 0;
}

int fileGetInt(char *filename, char *begintoken, char delim, char *lval, int *target)
{
    char rval[1024];
    int ret;

    strcpy(rval, "");
    ret = fileGetString(filename, begintoken, delim, lval, rval);
    if (ret)
    {
        *target = atoi(rval);
        return 1;
    }
    return 0;
}

int fileGetFloat(char *filename, char *begintoken, char delim, char *lval, float *target)
{
    char rval[1024];
    int ret;

    strcpy(rval, "");
    ret = fileGetString(filename, begintoken, delim, lval, rval);
    if (ret)
    {
        *target = (float)atof(rval);
        return 1;
    }
    return 0;
}

void fwRegisterPrompt(void *clientdata, int (*cb)(void *))
{
    pfwprompt = cb;
    fwpromptclientdata = clientdata;

    return;
}

void fwRegisterWorkProc(void *clientdata, int (*cb)(void *))
{
    pfwworkproc = cb;
    fwworkprocclientdata = clientdata;

    return;
}

void fwRemoveWorkProc()
{
    pfwworkproc = NULL;

    return;
}

void tokenize(char *buffer, char *delimstring, char tbuffer[][256], int *numtokens)
{
    char localbuffer[65536];
    char tokenbuffer[65536];
    char *scan;
    int count;

    count = 0;
    strcpy(localbuffer, buffer);
    scan = strtok(localbuffer, delimstring);
    if (scan == NULL)
    {
        *numtokens = count;
        return;
    }
    strcpy(tokenbuffer, scan);
    trim(tokenbuffer);
    strcpy(tbuffer[count], tokenbuffer);
    count++;
    while ((scan = strtok(NULL, delimstring)) != NULL)
    {
        strcpy(tokenbuffer, scan);
        trim(tokenbuffer);
        strcpy(tbuffer[count], tokenbuffer);
        count++;
    }
    *numtokens = count;
    return;
}

/** Doubly Linked List Library **/

#ifndef NIL
#define NIL ((NODE *)0)
#endif

/** Initialize the Linked List **/
void lstInit(DLIST *pList)
{
    pList->count = 0;
    pList->node.next = NIL;
    pList->node.previous = NIL;
}

/** Add to the end of the list **/
void lstAdd(DLIST *pList, NODE *pNode)
{
    if (pList->node.next == NIL)
    {
        /** This is the first element of the list **/
        pList->node.next = pNode;
        pList->node.previous = pNode;
        pNode->next = NIL;
        pNode->previous = NIL;
        pList->count = 1;
    }
    else
    {
        pNode->next = NIL;
        pNode->previous = pList->node.previous;
        pList->node.previous->next = pNode;
        pList->node.previous = pNode;
        pList->count++;
    }
}

int lstCount(DLIST *pList)
{
    return (pList->count);
}

void lstDelete(DLIST *pList, NODE *pNode)
{
    if (pNode->next == NIL)
    {
        /** Last in List **/
        pList->node.previous = pNode->previous;
    }
    else
    {
        pNode->next->previous = pNode->previous;
    }

    if (pNode->previous == NIL)
    {
        /** First in List **/
        pList->node.next = pNode->next;
    }
    else
    {
        pNode->previous->next = pNode->next;
    }

    pList->count--;
}

NODE *lstFirst(DLIST *pList)
{
    return (pList->node.next);
}

void lstInsert(DLIST *pList, NODE *pPrev, NODE *pNode)
{
    if (pList->count == 0)
    {
        /** Empty List, treat the same a lstAdd **/
        lstAdd(pList, pNode);
        return;
    }

    if (pPrev == NIL)
    {
        pNode->next = pList->node.next;
        pNode->previous = NIL;
        pList->node.next->previous = pNode;
        pList->node.next = pNode;
    }
    else
    {
        pNode->next = pPrev->next;
        pNode->previous = pPrev;
        pPrev->next->previous = pNode;
        pPrev->next = pNode;
    }

    if (pNode->next == NIL)
    {
        pList->node.previous = pNode;
    }

    pList->count++;
}

NODE *lstLast(DLIST *pList)
{
    return (pList->node.previous);
}

NODE *lstNext(NODE *pNode)
{
    return (pNode->next);
}

NODE *lstPrevious(NODE *pNode)
{
    return (pNode->previous);
}

NODE *lstGet(DLIST *pList)
{
    NODE *N;

    N = pList->node.next;
    if (N)
        lstDelete(pList, N);
    return (N);
}

NODE *lstNStep(NODE *pNode, int nStep)
{
    int i;
    NODE *p = pNode;

    if (nStep > 0)
    {
        for (i = 0; i < nStep; i++)
        {
            if (p->next)
                p = p->next;
            else
                return NIL;
        }
    }
    else if (nStep < 0)
    {
        for (i = 0; i < (-nStep); i++)
        {
            if (p->previous)
                p = p->previous;
            else
                return NIL;
        }
    }

    return (p);
}

NODE *lstNth(DLIST *pList, int nodenum)
{
    NODE *p;

    p = lstFirst(pList);

    /** Assuming that numbering starts from 1 **/
    return (lstNStep(p, (nodenum - 1)));
}

int lstFind(DLIST *pList, NODE *pNode)
{
    NODE *p;
    int i = 1;

    p = lstFirst(pList);
    for (;; i++, p = p->next)
    {
        if (p == pNode)
            return i;
        if (p == NIL)
            return (-1);
    }
}

void lstFree(DLIST *pList)
{
    /** This function calls `free' to free up individual nodes, caution! **/
    NODE *p,
        *pnext;

    p = lstFirst(pList);

    while (p)
    {
        pnext = p->next;
        lstDelete(pList, p);
        free(p);
        p = pnext;
    }
}

/*NOTYET*/ extern void lstConcat(DLIST *pDstList, DLIST *pAddList);
/*NOTYET*/ extern void lstExtract(DLIST *pSrcList, NODE *pStartNode, NODE *pEndNode, DLIST *pDstList);

/* Reference Time and period is seconds */
int fwTimeLeftToAlignToWallClock(int referenceTime, int period)
{
    time_t currentTime;
    int step;
    currentTime = getEpoch();
    step = 1;
    while ((referenceTime + (step * period)) < currentTime)
    {
        step += 1;
    }
    return ((referenceTime + (step * period)) - currentTime);
}

int isRpcEnabled()
{
    int index;
    int flag = 0;
    for (index = 0; index < MAX_TOTAL_APP_ID; index++)
    {
        if (g_fwRpcRegistered[index] == 1)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void fwRegisterRpc(unsigned int appid)
{
    if (0 == isRpcEnabled())
    {
        g_fwRpcRegistered[appid] = 1;
    }
}

void fwDeRegisterRpc(unsigned int appid)
{
    if (g_fwRpcRegistered[appid] == 1)
    {
        g_fwRpcRegistered[appid] = 0;
    }
}

int ipc_msg_snd(ipc_packet_t *P)
{
    udpWrite(g_app_map[P->hdr.src_app_id].ipc_socket, "127.0.0.1", P->hdr.dst_app_id + APP_PORT_BASE, (char *)&P, sizeof(ipc_packet_t *));
    return 0;
}

/******************/
/***** Buffers ****/
/******************/

void fw_buffer_init(fw_buffer_config_t *F, int numentries)
{
    int i;
    if (pthread_mutex_init(&fwbufferMu, NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }

    fw_num_buffer_pools = numentries;

    for (i = 0; i < numentries; i++)
    {
        fw_buffer_busy[i] = 0;
        fw_buffer_pool_init(&fw_buffer_pool[i], &F[i], i);
    }
}

void fw_buffer_pool_init(fw_buffer_pool_t *P, fw_buffer_config_t *C, int poolid)
{
    char *mem;
    char *scan;
    fw_buffer_hdr_t *F = NULL;
    int i;
    unsigned long size;
    unsigned char *magic;
    unsigned long residual;
    unsigned long totalblocksize;

    /* we want a multiple of 8 for size + magicnumber */
    /* header is presumed multiple of 8 */
    residual = 8 - ((C->size + FW_MAGIC_NUM_SIZE) % 8);
    totalblocksize = C->size + FW_MAGIC_NUM_SIZE + sizeof(fw_buffer_hdr_t) + residual;

    size = (C->num_buffers) * totalblocksize;

    if (!(C->useBuff))
        mem = (char *)malloc(size);
    else
        mem = C->useBuff;

    assert(mem != NULL);
    memset(mem, 0, size);
    /* init the buffer pool main entry in the array */
    P->pfirst = (fw_buffer_hdr_t *)mem;
    P->pstart = (fw_buffer_hdr_t *)mem;
    P->size = C->size;
    P->num_buffers = C->num_buffers;
    P->threshold = 0;

    /** now init the mem itself **/
    scan = mem;
    for (i = 0; i < C->num_buffers; i++)
    {
        F = (fw_buffer_hdr_t *)scan;
        F->pnext = (fw_buffer_hdr_t *)(scan + totalblocksize);
        F->poolid = poolid;
        F->busyflag = 0;
        F->appid = 0;
        F->func = NULL;
        F->line = 0;
        magic = (unsigned char *)(scan + sizeof(fw_buffer_hdr_t) + C->size);
        bufferAddUint2_linux(magic, FW_MAGIC_NUM);
        scan += totalblocksize;
    }
    if (NULL != F)
    {
        F->pnext = NULL;
    }
}

int fw_audit_buffer_pools(int shell, int pool)
{
    int i = 0;
    unsigned char *scan;
    unsigned short magic;
    int residual;
    int totalblocksize;
    unsigned char *magicscan;

    scan = (unsigned char *)fw_buffer_pool[pool].pstart;
    residual = 8 - ((fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE) % 8);
    totalblocksize = fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE + sizeof(fw_buffer_hdr_t) + residual;

    for (i = 0; i < fw_buffer_pool[pool].num_buffers; i++)
    {

        magicscan = scan;
        magicscan += sizeof(fw_buffer_hdr_t) + fw_buffer_pool[pool].size;
        magic = bufferGetUint2_linux(magicscan);
        if (magic != FW_MAGIC_NUM)
        {
            if (shell)
                pprintf(("Buffer<%p> corrupted. Magic Number Mismatch\n", scan + sizeof(fw_buffer_hdr_t)));
            else
                printf("Buffer<%p> corrupted. Magic Number Mismatch\n", scan + sizeof(fw_buffer_hdr_t));
            return 0;
        }
        scan += totalblocksize;
    }
    return 1;
}

int fw_audit_buffer_management(int shell)
{
    int i = 0;
    for (i = 0; i < fw_num_buffer_pools; i++)
    {
        if (!fw_audit_buffer_pools(shell, i))
        {
            if (shell)
                pprintf(("Audit of Pool %d Failed\n", i));
            else
                printf("Audit of Pool %d Failed\n", i);
            return 0;
        }
    }
    return 1;
}

void fw_dump_free_buffs(int pool)
{
    int i = 0;
    fw_buffer_hdr_t *F;
    char *scan;
    int used = 0;
    int residual;
    int totalblocksize;

    if (pool >= MAX_BUFFER_POOLS)
    {
        printf("Invalid Pool Id\n");
        return;
    }
    F = (fw_buffer_hdr_t *)fw_buffer_pool[pool].pstart;
    scan = (char *)F;

    if (!F)
    {
        printf("Pool Not Created\n");
        return;
    }
    residual = 8 - ((fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE) % 8);
    totalblocksize = fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE + sizeof(fw_buffer_hdr_t) + residual;
    pprintf(("Pool Id\tLast Function(Line Number)\tAddress\n"));
    for (i = 0; i < fw_buffer_pool[pool].num_buffers; i++)
    {
        F = (fw_buffer_hdr_t *)scan;
        if (!F->busyflag && F->func)
        {
            pprintf(("%d\t%s(%d)\t%d\n", pool, F->func, F->line, (char *)F + sizeof(fw_buffer_hdr_t)));
            used = 1;
        }
        scan += totalblocksize;
    }
    if (used == 0)
        pprintf(("No free buffer which had been earlier used\n"));
}

void fw_dump_buff_pool_usage(int shell, int pool)
{
    int i = 0;
    fw_buffer_hdr_t *F;
    char *scan;
    int used = 0;
    int residual;
    int totalblocksize;

    F = (fw_buffer_hdr_t *)fw_buffer_pool[pool].pstart;
    scan = (char *)F;

    residual = 8 - ((fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE) % 8);
    totalblocksize = fw_buffer_pool[pool].size + FW_MAGIC_NUM_SIZE + sizeof(fw_buffer_hdr_t) + residual;

    if (!shell)
        printf("App Id\tFunction(Line Number)\t\tAddress\n");
    else
        pprintf(("App Id\tFunction(Line Number)\t\tAddress\n"));
    for (i = 0; i < fw_buffer_pool[pool].num_buffers; i++)
    {
        F = (fw_buffer_hdr_t *)scan;
        if (F->busyflag)
        {
            if (!shell)
                printf("%d\t%s\t%d\t0x%p\n", F->appid, F->func, F->line, (char *)F + sizeof(fw_buffer_hdr_t));
            else
                pprintf(("%d\t%s\t%d\t0x%p\n", F->appid, F->func, F->line, (char *)F + sizeof(fw_buffer_hdr_t)));
            used = 1;
        }
        scan += totalblocksize;
    }
    if (used == 0)
    {
        if (!shell)
            printf("No buffer allocated to the pool\n");
        else
            pprintf(("No buffer allocated to the pool\n"));
    }
}

void fw_clear_app_buffers(unsigned int appid)
{
    NODE *node;

    node = lstFirst(&g_app_map[appid].buff_list);
    while (node != NULL)
    {
        fw_buffer_release(appid, (char *)node + sizeof(fw_buffer_hdr_t));
        node = lstNext(node);
    }
}

char *fw_buffer_get_dbg(char *func, int line, unsigned int appid, int size)
{
    int i;
    char *palloc;

    if (BUFF_DEBUG == g_buff_debug)
    {
        if (appid >= MAX_TOTAL_APP_ID || (signed int)appid < 0)
        {
            printf("Invalid App Id\n");
            return NULL;
        }
    }

    pthread_mutex_lock(&fwbufferMu);
    for (i = 0; i < fw_num_buffer_pools; i++)
    {
        if (fw_buffer_pool[i].size >= size)
        {
            if (fw_buffer_pool[i].pfirst == NULL)
            {
                continue;
            }
            palloc = (char *)fw_buffer_pool[i].pfirst;
            fw_buffer_pool[i].pfirst->busyflag = 1;
            fw_buffer_pool[i].pfirst->appid = appid;
            fw_buffer_pool[i].pfirst->func = func;
            fw_buffer_pool[i].pfirst->line = line;

            lstAdd(&g_app_map[appid].buff_list, &fw_buffer_pool[i].pfirst->anchor);

            fw_buffer_pool[i].pfirst = fw_buffer_pool[i].pfirst->pnext;
            fw_buffer_busy[i]++;
            if (fw_buffer_busy[i] >= fw_buffer_pool[i].threshold && fw_buffer_pool[i].threshold)
            {
                fprintf(stdout, "Threshold violation for poolid: <%d>\n", i);
                fw_dump_buff_pool_usage(0, i);
                fw_buffer_pool[i].threshold = 0;
            }
            pthread_mutex_unlock(&fwbufferMu);
            return ((char *)palloc + sizeof(fw_buffer_hdr_t));
        }
    }
    pthread_mutex_unlock(&fwbufferMu);
    return NULL;
}

int fw_valid_add_for_rel(char *buff)
{

    int residual;
    int totalblocksize;

    char *extent1;
    char *extent2;
    int i = 0;

    if (!buff)
    {
        printf("Invalid Buffer Address\n");
        return 0;
    }

    for (i = 0; i < fw_num_buffer_pools; i++)
    {
        residual = 8 - ((fw_buffer_pool[i].size + FW_MAGIC_NUM_SIZE) % 8);
        totalblocksize = fw_buffer_pool[i].size + FW_MAGIC_NUM_SIZE + sizeof(fw_buffer_hdr_t) + residual;
        extent1 = (char *)fw_buffer_pool[i].pstart;
        extent2 = extent1 + (fw_buffer_pool[i].num_buffers * totalblocksize);
        if ((buff < extent1) || (buff > extent2))
        {
            continue;
        }
        else
        {
            /** if buff lies exactly at payload deserved address **/
            /** then buff minus the first payload address divided totalblocksize should give zero **/
            if (((buff - (char *)fw_buffer_pool[i].pstart - sizeof(fw_buffer_hdr_t)) % totalblocksize) != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int fw_buffer_release_dbg(char *func, int line, unsigned int appid, char *buf)
{
    char *scan;
    fw_buffer_hdr_t *H;
    int poolid;
    unsigned char *magicscan;
    unsigned short magicnum;

    if (BUFF_DEBUG == g_buff_debug)
    {
        if (!buf)
        {
            printf("buffer release error: Invalid Buffer Address passed from <%s> <%d>, buffer address: <%p>\n", func, line, buf);
            return 0;
        }
        if (!fw_valid_add_for_rel(buf))
        {
            printf("buffer release error: Address %p isn't a valid address to be freed by the buffer management framework, passed from <%s> <%d>\n", buf, func, line);
            return 0;
        }
    }

    scan = buf - sizeof(fw_buffer_hdr_t);
    H = (fw_buffer_hdr_t *)scan;
    poolid = H->poolid;

    if (BUFF_DEBUG == g_buff_debug)
    {
        if (!H->busyflag)
        {
            printf("buffer release error: Releasing an already free buffer from <%s> <%d>\n", func, line);
            printf("Previous release done at: <%s> <%d>\n", H->func, H->line);
            return 0;
        }
        if (H->appid != appid)
        {
            printf("buffer release error: App Id <%d> not the owner of buffer. Actual Owner<%d>, attempted at: <%s> <%d>\n", appid, H->appid, func, line);
            return 0;
        }
        if ((poolid > (MAX_BUFFER_POOLS - 1)) || (poolid < 0))
        {
            printf("buffer release error: buffer <%p> released at <%s> <%d> does not have the valid poolid in header, poolid <%d>\n", buf, func, line, H->poolid);
            printf("here is the dump of header -- \n");
            dumpBytesTo(stdout, (unsigned char *)buf - sizeof(fw_buffer_hdr_t), sizeof(fw_buffer_hdr_t));
            return 0;
        }
        magicscan = (unsigned char *)(buf + fw_buffer_pool[poolid].size);
        magicnum = bufferGetUint2_linux(magicscan);
        if (magicnum != FW_MAGIC_NUM)
        {
            printf("buffer release error: buffer <%p> released at <%s> <%d> does not have the valid signature towards the end, poolid used <%d>\n", buf, func, line, H->poolid);
            return 0;
        }
    }

    pthread_mutex_lock(&fwbufferMu);

    lstDelete(&g_app_map[appid].buff_list, &H->anchor);

    H->busyflag = 0;
    H->appid = 0;
    H->func = func;
    H->line = line;
    fw_buffer_busy[poolid]--;
    if (fw_buffer_pool[poolid].pfirst == NULL)
    {
        /** all buffers full **/
        fw_buffer_pool[poolid].pfirst = H;
        H->pnext = NULL;
    }
    else
    {
        H->pnext = fw_buffer_pool[poolid].pfirst;
        fw_buffer_pool[poolid].pfirst = H;
    }
    pthread_mutex_unlock(&fwbufferMu);
    return 1;
}

void fw_buffer_stat()
{
    int index;

    int size;

    pprintf(("\nBuffer Size \t Busy Buffers \t Free Buffers\n"));
    for (index = 0; index < fw_num_buffer_pools; index++)
    {
        size = fw_buffer_pool[index].size;

        pprintf(("%d\t\t%d\t\t%d\n", size, fw_buffer_busy[index], fw_buffer_pool[index].num_buffers - fw_buffer_busy[index]));
    }
}

/******************/
/***** IPC Buffers ****/
/******************/

void ipc_buffer_init(ipc_buffer_config_t *F, int numentries)
{
    int i;
    if (pthread_mutex_init(&ipcbufferMu, NULL) < 0)
    {
        perror("pthread_mutex_init");
        exit(1);
    }

    ipc_num_buffer_pools = numentries;

    for (i = 0; i < numentries; i++)
    {
        ipc_buffer_busy[i] = 0;
        ipc_buffer_pool_init(&ipc_buffer_pool[i], &F[i], i);
    }
}

void ipc_buffer_pool_init(ipc_buffer_pool_t *P, ipc_buffer_config_t *C, int poolid)
{
    char *mem;
    char *scan;
    ipc_buffer_hdr_t *F = NULL;
    int i;
    int size;

    size = (C->num_buffers) * (C->size + sizeof(ipc_buffer_hdr_t) + sizeof(fw_ipc_hdr_t));
    mem = (char *)malloc((C->num_buffers) * (C->size + sizeof(ipc_buffer_hdr_t) + sizeof(fw_ipc_hdr_t)));
    assert(mem != NULL);
    memset(mem, 0, size);
    /** init the buffer pool main entry in the array **/
    P->pfirst = (ipc_buffer_hdr_t *)mem;
    P->size = C->size;
    P->num_buffers = C->num_buffers;

    /** now init the mem itself **/
    scan = mem;
    for (i = 0; i < C->num_buffers; i++)
    {
        F = (ipc_buffer_hdr_t *)scan;
        F->pnext = (ipc_buffer_hdr_t *)(scan + sizeof(ipc_buffer_hdr_t) + sizeof(fw_ipc_hdr_t) + C->size);
        F->poolid = poolid;
        F->busyflag = 0;
        F->appid = 0;
        scan += sizeof(fw_ipc_hdr_t) + sizeof(ipc_buffer_hdr_t) + C->size;
    }
    if (NULL != F)
    {
        F->pnext = NULL;
    }
}

ipc_packet_t *ipc_buffer_get(unsigned int appid, int size)
{
    int i;
    char *palloc;
    pthread_mutex_lock(&ipcbufferMu);
    size = size + sizeof(fw_ipc_hdr_t);
    for (i = 0; i < ipc_num_buffer_pools; i++)
    {
        if (ipc_buffer_pool[i].size >= size)
        {
            if (ipc_buffer_pool[i].pfirst == NULL)
            {
                continue;
            }
            palloc = (char *)ipc_buffer_pool[i].pfirst;
            ipc_buffer_pool[i].pfirst->busyflag = 1;
            ipc_buffer_pool[i].pfirst->appid = appid;
            ipc_buffer_pool[i].pfirst = ipc_buffer_pool[i].pfirst->pnext;
            ipc_buffer_busy[i]++;
            pthread_mutex_unlock(&ipcbufferMu);
            return ((ipc_packet_t *)palloc + sizeof(ipc_buffer_hdr_t));
        }
    }
    pthread_mutex_unlock(&ipcbufferMu);
    return NULL;
}

int ipc_buffer_release(unsigned int appid, ipc_packet_t *buf)
{
    ipc_packet_t *scan;
    ipc_buffer_hdr_t *H;
    int poolid;

    pthread_mutex_lock(&ipcbufferMu);
    scan = buf - sizeof(ipc_buffer_hdr_t);
    H = (ipc_buffer_hdr_t *)scan;
    poolid = H->poolid;
    H->busyflag = 0;
    H->appid = 0;
    ipc_buffer_busy[poolid]--;
    if (ipc_buffer_pool[poolid].pfirst == NULL)
    {
        /** all buffers full **/
        ipc_buffer_pool[poolid].pfirst = H;
        H->pnext = NULL;
    }
    else
    {
        H->pnext = ipc_buffer_pool[poolid].pfirst;
        ipc_buffer_pool[poolid].pfirst = H;
    }
    pthread_mutex_unlock(&ipcbufferMu);
    return 1;
}

void ipc_buffer_stat()
{
    int index;

    int size;

    pprintf(("\nBuffer Size \t Busy Buffers \t Free Buffers\n"));
    for (index = 0; index < ipc_num_buffer_pools; index++)
    {
        size = ipc_buffer_pool[index].size;

        pprintf(("%d\t\t%d\t\t%d\n", size, ipc_buffer_busy[index], ipc_buffer_pool[index].num_buffers - ipc_buffer_busy[index]));
    }
}

int ipc_buffer_change_owner(unsigned int appid, ipc_packet_t *buf)
{
    ipc_packet_t *scan;
    ipc_buffer_hdr_t *H;
    scan = buf - sizeof(ipc_buffer_hdr_t);
    H = (ipc_buffer_hdr_t *)scan;
    H->appid = appid;
    return 1;
}

int fw_get_self_appid(unsigned int *p_app_id)
{
    int index = 0;
    st_get_index_of_command(&index);
    *p_app_id = g_st_terminal_data[index].cmd_appid;
    return 1;
}

int fw_get_appid(unsigned int *p_app_id)
{
    unsigned int i;
    for (i = 0; i < DYN_APP_IDS; i++)
    {
        if (g_dyn_flag[i] == 0)
        {
            g_dyn_flag[i] = 1;
            *p_app_id = DYN_APP_ID_START + i;
            return 1;
        }
    }
    return 0;
}

int fw_return_appid(unsigned int appid)
{
    if (appid > DYN_APP_ID_END)
        return 0;

    if (g_dyn_flag[appid - DYN_APP_ID_START] == 1)
    {
        g_dyn_flag[appid - DYN_APP_ID_START] = 0;
        fw_clear_app_buffers(appid);
        return 1;
    }
    else
        return 0;
}

int st_get_terminal_index(int *p_index)
{
    int i;
    for (i = 0; i < MAX_ST_SESSIONS; i++)
    {
        if (g_terminal_flag[i] == 0)
        {
            g_terminal_flag[i] = 1;
            *p_index = i;
            return 1;
        }
    }
    return -1;
}

int st_get_index_of_terminal(int *p_index)
{
    int i;
    pthread_t tid = pthread_self();
    for (i = 0; i < MAX_ST_SESSIONS; i++)
    {
        if (g_st_terminal_data[i].Ttid == tid)
        {
            *p_index = i;
            return 1;
        }
    }
    return 0;
}

int st_get_index_of_appid(unsigned int appid, int *p_index)
{
    int index;
    for (index = 0; index < MAX_ST_SESSIONS; index++)
    {
        if (g_st_terminal_data[index].appid == appid)
        {
            *p_index = index;
            return 1;
        }
    }
    return 0;
}

int st_get_index_of_command(int *p_index)
{
    int i;
    pthread_t tid = pthread_self();
    for (i = 0; i < MAX_ST_SESSIONS; i++)
    {
        if (g_st_terminal_data[i].Ctid == tid)
        {
            *p_index = i;
            return 1;
        }
    }
    return 0;
}

char *logst_proxy_fn(char *fmt, ...)
{

    /* For storage of variable arguement string */
    va_list va;
    char *p_alloc_buff;
    char g_log_str[1500];
    char temp[1500];
    int length;
    int i;
    int j = 0;
    /* Extracting the string */
    va_start(va, fmt);
    vsprintf((char *)g_log_str, fmt, va);
    va_end(va);
    length = strlen(g_log_str);
    /* Used for stretS8*ble array */
    for (i = 0; i < length; i++)
    {
        temp[j] = g_log_str[i];
        if (g_log_str[i] == '\n')
        {
            temp[++j] = '\r';
        }
        j++;
    }
    temp[j] = '\0';

    p_alloc_buff = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
    ;
    if (NULL == p_alloc_buff)
    {
        return NULL;
    }
    memcpy(p_alloc_buff, temp, strlen(temp) + 1);
    return p_alloc_buff;
}

void shell_add_cmd(char *cmd_name, char *desc,
                   CmdCallBackFnType funcPtr)
{
    g_st_command_table[st_commands_index].cmdName = cmd_name;
    g_st_command_table[st_commands_index].callBack = funcPtr;
    g_st_command_table[st_commands_index].cmdHelp = desc;
    st_commands_index++;
    g_st_command_table[st_commands_index].cmdName = NULL;
}

void st_command_handler(char *command)
{
    char temp_command[1024];
    char *T;
    char *str = NULL;
    char *argv[10];
    int argc = 0;
    int i;
    int length;
    int flag = 0;
    strcpy(temp_command, command);
    length = strlen(temp_command);

    for (i = 0; i < length; i++)
    {
        if (flag == 1 && temp_command[i] == ' ')
        {
            temp_command[i] = '-';
        }
        if (flag == 1 && temp_command[i] == '"')
            flag = 0;
        else if (temp_command[i] == '"')
        {
            flag = 1;
        }
    }
    str = strtok(temp_command, " ");

    memset(argv, 0, sizeof(argv));
    while (str != NULL)
    {
        argv[argc] = str;
        length = strlen(argv[argc]);
        for (i = 0; i < length; i++)
        {
            if (argv[argc][i] == '-')
                argv[argc][i] = ' ';
        }
        argc++;
        str = strtok(NULL, " ");
    }
    for (i = 0; i < st_commands_index; i++)
    {
        if (g_st_command_table[i].cmdName == NULL)
            break;
        if (NULL == argv[0])
            break;
        if (strcmp(argv[0], g_st_command_table[i].cmdName) == 0)
        {
            T = fwtimestring();
            pprintf(("[++%s++][%s]\n", argv[0], T));
            free(T);
            g_st_command_table[i].callBack(argc, argv);
            return;
        }
    }
    pprintf(("Command \"%s\" Not Found!!", argv[0]));
}

void *ST_CMD_HANDLER(void *cData)
{

    unsigned int appid;
    int i = 0;
    int state;
    appid = (*(unsigned int *)cData);
    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, &state);
    st_get_index_of_appid(appid, &i);
    g_st_terminal_data[i].Ctid = pthread_self();
    fw_get_appid(&(g_st_terminal_data[i].cmd_appid));
    st_command_handler(g_st_terminal_data[i].command);
    fw_return_appid(g_st_terminal_data[i].cmd_appid);
    pprintf(("\n%s", g_st_terminal_data[i].g_prompt));
    g_st_terminal_data[i].flag = 0;
    g_st_terminal_data[i].Ctid = 0;
    pthread_detach(pthread_self());
    return NULL;
}

int ter_cb(int sockfd, void *cData)
{
    int length;
    char buff[1024];
    unsigned int appid = *((unsigned int *)cData);
    pthread_t tid;
    char command[100];
    int index = 0;
    st_get_index_of_appid(appid, &index);
    length = tcpRead(sockfd, buff, 1);
    if (buff[0] == 3)
    {
        if (fwdebug)
            printf("Ctrl C recieved\n");
        if (g_st_terminal_data[index].Ctid != 0)
        {
            if (fwdebug)
                printf("Going to kill %s command \n", g_st_terminal_data[index].command);
            pthread_cancel(g_st_terminal_data[index].Ctid);
            g_st_terminal_data[index].flag = 0;
            g_st_terminal_data[index].Ctid = 0;
        }
        strcpy(command, "");
        tcpWrite(sockfd, "\n", 2);
        tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
        return 1;
    }
    if (g_st_terminal_data[index].flag == 0)
    {
        if (buff[0] == 127)
        {
            g_st_terminal_data[index].count--;
            tcpWrite(sockfd, buff, length);
            return 1;
        }
        else
            tcpWrite(sockfd, buff, length);
        if (buff[0] == '\n')
        {
            g_st_terminal_data[index].flag = 1;
            if (g_st_terminal_data[index].count != 0)
            {
                command[g_st_terminal_data[index].count] = '\0';
                g_st_terminal_data[index].count = 0;
                if (strcmp(command, "exit") == 0)
                {
                    tcpWrite(sockfd, "", 2);
                    fwMultiplexRemove(appid, sockfd);
                    no_of_sessions--;
                    fw_return_appid(appid);
                    close(sockfd);
                }
                else
                {
                    g_st_terminal_data[index].sockfd = sockfd;
                    strcpy(g_st_terminal_data[index].command, command);
                    pthread_create(&tid, NULL, ST_CMD_HANDLER, (void *)&appid);
                }
            }
            else
            {
                g_st_terminal_data[index].flag = 0;
                tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
            }
        }
        else
        {
            command[g_st_terminal_data[index].count++] = buff[0];
        }
    }
    return 0;
}

int telnet_ter_cb(int sockfd, void *cData)
{
    int length;
    char buff[1024];
    char tempmsg[1024];
    int ret;
    unsigned int cur_idx = 0;
    unsigned int appid = *((unsigned int *)cData);
    pthread_t tid;
    static char command[MAX_ST_SESSIONS][1024];
    int index = 0;
    ret = st_get_index_of_appid(appid, &index);
    length = tcpRead(sockfd, buff, 1);
    if (length == 0)
    {
        if (ret == 1)
        {
            g_terminal_flag[index] = 0;
        }
        tcpWrite(sockfd, "^D", 2);
        fwMultiplexRemove(appid, sockfd);
        no_of_sessions--;
        fw_return_appid(appid);
        g_st_terminal_data[index].flag = 0;
        g_st_terminal_data[index].Ctid = 0;
        close(sockfd);
        pthread_detach(pthread_self());
        pthread_exit(NULL);
    }
    if (buff[0] == 10)
        return 1;
    if (fwdebug)
        printf("%d\n", buff[0]);
    if (buff[0] == 3)
    {
        if (fwdebug)
            printf("Ctrl C recieved\n");
        if (g_st_terminal_data[index].Ctid != 0)
        {
            if (fwdebug)
                printf("Going to kill %s command \n", g_st_terminal_data[index].command);
            pthread_cancel(g_st_terminal_data[index].Ctid);
            g_st_terminal_data[index].flag = 0;
            g_st_terminal_data[index].Ctid = 0;
            fwDeinit(g_st_terminal_data[index].cmd_appid);
            fw_return_appid(g_st_terminal_data[index].cmd_appid);
        }
        strcpy(command[index], "");
        g_st_terminal_data[index].count = 0;
        tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
        return 1;
    }
    if (buff[0] == 6)
    {
        tcpWrite(sockfd, &buff[0], 1);
        if (fwdebug)
            printf("Ctrl C recieved\n");
        if (g_st_terminal_data[index].Ctid != 0)
        {
            if (fwdebug)
                printf("Going to kill %s command \n", g_st_terminal_data[index].command);
            pthread_cancel(g_st_terminal_data[index].Ctid);
            g_st_terminal_data[index].flag = 0;
            g_st_terminal_data[index].Ctid = 0;
            fwDeinit(g_st_terminal_data[index].cmd_appid);
            fw_return_appid(g_st_terminal_data[index].cmd_appid);
        }
        strcpy(command[index], "");
        g_st_terminal_data[index].count = 0;
        tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
        return 1;
    }
    {
        if (buff[0] == 8)
        {
            g_st_terminal_data[index].count--;
            return 1;
        }
        if (buff[0] == 13)
        {
            if (g_st_terminal_data[index].state == LOGIN_STATE)
            {
                command[index][g_st_terminal_data[index].count] = '\0';
                strcpy(g_st_terminal_data[index].login, command[index]);
                /* printf("login: <%s>\n", g_st_terminal_data[index].login); */
                strcpy(tempmsg, "password: ");
                tcpWrite(sockfd, tempmsg, strlen(tempmsg) + 1);
                /** IAC WILL ECHO **/
                tempmsg[0] = 255;
                tempmsg[1] = 251;
                tempmsg[2] = 1;
                tcpWrite(sockfd, tempmsg, 3);
                strcpy(command[index], "");
                g_st_terminal_data[index].count = 0;
                g_st_terminal_data[index].state = PASSWORD_STATE;
                return 1;
            }

            if (g_st_terminal_data[index].state == PASSWORD_STATE)
            {
                command[index][g_st_terminal_data[index].count] = '\0';
                strcpy(g_st_terminal_data[index].password, command[index]);
                /* printf("password: <%s>\n", g_st_terminal_data[index].password);*/
                strcpy(command[index], "");
                g_st_terminal_data[index].count = 0;
                /** IAC WON'T ECHO **/
                tempmsg[0] = 255;
                tempmsg[1] = 252;
                tempmsg[2] = 1;
                tcpWrite(sockfd, tempmsg, 3);

                tempmsg[0] = 10;
                tempmsg[1] = 13;
                tcpWrite(sockfd, tempmsg, 2);

                /***********************************/
                /** authentication to be done here **/
                /***********************************/
                if (!fw_validate_user(g_st_terminal_data[index].login, g_st_terminal_data[index].password))
                {
                    strcpy(tempmsg, "login incorrect\n");
                    tcpWrite(sockfd, tempmsg, strlen(tempmsg) + 1);
                    sleep(1);
                    if (ret == 1)
                    {
                        g_terminal_flag[index] = 0;
                    }
                    /*tcpWrite(sockfd,"^D",2);*/
                    fwMultiplexRemove(appid, sockfd);
                    no_of_sessions--;
                    fw_return_appid(appid);
                    g_st_terminal_data[index].flag = 0;
                    g_st_terminal_data[index].Ctid = 0;
                    close(sockfd);
                    pthread_detach(pthread_self());
                    pthread_exit(NULL);
                    return 1;
                }

                tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
                g_st_terminal_data[index].state = AUTHENTICATED_STATE;
                return 1;
            }

            if (g_st_terminal_data[index].count != 0)
            {
                command[index][g_st_terminal_data[index].count] = '\0';
                g_st_terminal_data[index].count = 0;
                if (strcmp(command[index], "exit") == 0)
                {
                    if (ret == 1)
                    {
                        g_terminal_flag[index] = 0;
                    }
                    tcpWrite(sockfd, "^D", 2);
                    fwMultiplexRemove(appid, sockfd);
                    no_of_sessions--;
                    fw_return_appid(appid);
                    g_st_terminal_data[index].flag = 0;
                    g_st_terminal_data[index].Ctid = 0;
                    close(sockfd);
                    pthread_detach(pthread_self());
                    pthread_exit(NULL);
                }
                else
                {
                    g_st_terminal_data[index].sockfd = sockfd;
                    strcpy(g_st_terminal_data[index].command, command[index]);
                    if (strcmp(command[index], "fwstop") == 0)
                    {
                        if (g_st_terminal_data[index].Ctid != 0)
                        {
                            pthread_cancel(g_st_terminal_data[index].Ctid);
                            g_st_terminal_data[index].flag = 0;
                            g_st_terminal_data[index].Ctid = 0;
                            fwDeinit(g_st_terminal_data[index].cmd_appid);
                            fw_return_appid(g_st_terminal_data[index].cmd_appid);
                        }
                        strcpy(command[index], "");
                        if (g_st_terminal_data[index].state == AUTHENTICATED_STATE)
                        {
                            tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
                        }
                        return 1;
                    }
                    if (g_st_terminal_data[index].flag == 0)
                    {
                        g_st_terminal_data[index].flag = 1;
                        if (0 == is_command_repleated(command[index]))
                        {
                            cur_idx = g_history_cmd.current_index;
                            strcpy(g_history_cmd.command[cur_idx], command[index]);
                            if (cur_idx == ST_MAX_HISTORY_CMDS - 1)
                            {
                                g_history_cmd.current_index = 0;
                            }
                            else
                            {
                                g_history_cmd.current_index++;
                            }
                        }
                        pthread_create(&tid, NULL, ST_CMD_HANDLER, cData);
                    }
                }
            }
            else
            {
                g_st_terminal_data[index].flag = 0;
                if (g_st_terminal_data[index].state == AUTHENTICATED_STATE)
                {
                    tcpWrite(sockfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
                }
            }
        }
        else
        {
            if (isprint(buff[0]))
                command[index][g_st_terminal_data[index].count++] = buff[0];
            else
            {
                if (g_st_terminal_data[index].state == AUTHENTICATED_STATE)
                {
                    tcpWrite(sockfd, &buff[0], 1);
                }
            }
        }
    }
    return 0;
}

int fw_validate_user(char *user, char *password)
{
    if (strcmp(user, "admin") != 0)
    {
        return 0;
    }
    if (strcmp(password, "admin") != 0)
    {
        return 0;
    }
    return 1;
}

void *ST_TERMINAL_HANDLER(void *cData)
{
    int newfd = *((int *)cData);

    unsigned int appid;
    int index = 0;
    char buff[] = "No More Sessions Allowed\n";
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);
    free(cData);
    st_get_terminal_index(&index);
    if (no_of_sessions < MAX_ST_SESSIONS)
    {
        fw_get_appid(&appid);
        shellInit(appid);
        fwMultiplexAdd(appid, newfd, &appid, ter_cb);
        tcpWrite(newfd, g_welcome_disclaimer, strlen(g_welcome_disclaimer) + 1);
        tcpWrite(newfd, "\n", 1);
        strcpy(g_st_terminal_data[index].g_prompt, g_prompt);
        tcpWrite(newfd, g_st_terminal_data[index].g_prompt, strlen(g_st_terminal_data[index].g_prompt) + 1);
        no_of_sessions++;
        g_st_terminal_data[index].Ttid = pthread_self();
        g_st_terminal_data[index].flag = 0;
        g_st_terminal_data[index].appid = appid;
        g_st_terminal_data[index].count = 0;
        fwMultiplexMainLoop(appid);
    }
    tcpWrite(newfd, buff, strlen(buff) + 1);
    return NULL;
}

void *ST_TELNET_TERMINAL_HANDLER(void *cData)
{
    char tempmsg[1024];
    int ret;
    int state;
    int newfd = *((int *)cData);
    unsigned int appid;
    int index;
    char buff[] = "No More Sessions Allowed\n";
    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, &state);
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);
    free(cData);
    ret = st_get_terminal_index(&index);
    if (ret == -1)
    {
        tcpWrite(newfd, buff, strlen(buff) + 1);
        sleep(1);
        close(newfd);
        pthread_detach(pthread_self());
        pthread_exit(NULL);
    }
    else
    {
        if (fwdebug)
            printf("no_of_sessions %d\n", no_of_sessions);
        if (no_of_sessions < MAX_ST_SESSIONS)
        {
            fw_get_appid(&appid);
            shellInit(appid);
            strcpy(g_st_terminal_data[index].g_prompt, g_prompt);
            fwMultiplexAdd(appid, newfd, &appid, telnet_ter_cb);
            strcpy(tempmsg, "login: ");
            tcpWrite(newfd, tempmsg, strlen(tempmsg) + 1);
            no_of_sessions++;
            g_st_terminal_data[index].state = LOGIN_STATE;
            g_st_terminal_data[index].Ttid = pthread_self();
            g_st_terminal_data[index].flag = 0;
            g_st_terminal_data[index].appid = appid;
            g_st_terminal_data[index].count = 0;
            fwMultiplexMainLoop(appid);
        }
        tcpWrite(newfd, buff, strlen(buff) + 1);
        sleep(1);
        close(newfd);
        pthread_detach(pthread_self());
        pthread_exit(NULL);
    }
}

int st_cb(int sockfd, void *cData)
{
    int *p_newfd;

    pthread_t tid;
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);
    p_newfd = (int *)malloc(sizeof(int));
    if (NULL == p_newfd)
    {
        return 0;
    }
    *p_newfd = tcpAccept(sockfd);
    if (fwdebug)
        printf("Accepted %d\n", sockfd);
    pthread_create(&tid, NULL, ST_TERMINAL_HANDLER, p_newfd);
    return 0;
}

int st_telnet_cb(int sockfd, void *cData)
{
    int *p_newfd;
    int new_fd = 0;

    pthread_t tid;
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);
    p_newfd = (int *)malloc(sizeof(int));
    if (p_newfd == NULL)
    {
        sleep(1);
        return 0;
    }
    new_fd = tcpAccept(sockfd);
    if (new_fd < 0)
    {
        free(p_newfd);
        sleep(1);
        return 0;
    }
    *p_newfd = new_fd;
    if (fwdebug)
        printf("Accepted\n");
    pthread_create(&tid, NULL, ST_TELNET_TERMINAL_HANDLER, p_newfd);
    return 0;
}

void *ST_HANDLER(void *args)
{
    int sock_fd;
    unsigned int appid = 0;
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);
    fw_get_appid(&appid);
    shellInit(appid);
    sock_fd = tcpSocketServer(ST_TERMINAL_PORT);
    fwMultiplexAdd(appid, sock_fd, NULL, st_cb);
    fwMultiplexMainLoop(appid);
    return NULL;
}

void *ST_TELNET_HANDLER(void *args)
{
    int sock_fd;
    int state;
    unsigned int appid = 0;
    char *env_tmp = NULL;
    char local_ip[1024];
    unsigned int ip_addr;
    int ret;

    pthread_setcancelstate(PTHREAD_CANCEL_ASYNCHRONOUS, &state);
    if (fwdebug)
        printf("Entered %s \n", __FUNCTION__);

    fw_get_appid(&appid);
    shellInit(appid);

    env_tmp = getenv("TELNET_IP");
    if (env_tmp == NULL)
    {
        strcpy(local_ip, "127.0.0.1");
    }
    else
    {
        strcpy(local_ip, env_tmp);
    }
    if (0 != strcmp(local_ip, ""))
    {
        ret = inet_pton(AF_INET, local_ip, (void *)&ip_addr);
        if (1 != ret)
        {
            fprintf(stderr, "Invalid LINUX_IP : telnet might not work\n");
            return NULL;
        }
    }
    env_tmp = getenv("TELNET_PORT");
    if (env_tmp == NULL)
    {
        sock_fd = tcpSocketServerExt(local_ip, ST_TERMINAL_PORT + 1);
    }
    else
    {
        sock_fd = tcpSocketServerExt(local_ip, atoi(env_tmp));
    }
    if (sock_fd != 0)
        fwMultiplexAdd(appid, sock_fd, NULL, st_telnet_cb);
    else
        fprintf(stderr, "ST_TELNET_HANDLER: telnet might not work !\n");
    fwMultiplexMainLoop(appid);
    return NULL;
}

int st_cmd_help(int argc, char **argv)
{
    int i;
    if (argc == 1)
    {
        pprintf(("Command Name \t\t Help\n"));
        for (i = 0; i < st_commands_index; i++)
        {
            pprintf(("%s \t\t %s \n", g_st_command_table[i].cmdName, g_st_command_table[i].cmdHelp));
        }
    }
    else if (argc == 2)
    {
        for (i = 0; i < st_commands_index; i++)
        {
            if (strcmp(argv[1], g_st_command_table[i].cmdName) == 0)
            {
                pprintf(("%s\t %s\n", g_st_command_table[i].cmdName, g_st_command_table[i].cmdHelp));
                return 1;
            }
        }
        pprintf(("Invalid Command %s\n", argv[1]));
    }
    return 0;
}

int st_cmd_ipcdbu(int argc, char **argv)
{
    if (argc == 1)
    {
        ipc_buffer_stat();
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_dbu(int argc, char **argv)
{
    if (argc == 1)
    {
        fw_buffer_stat();
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_sll(int argc, char **argv)
{
    int index;
    if (argc == 3)
    {
        index = atoi(argv[1]);
        if (index < 100)
        {
            if (1 == fw_set_log_level(index, atoi(argv[2])))
            {
                pprintf(("Log Level %d Set for appid %d Successfully\n", atoi(argv[2]), index));
            }
        }
        else
        {
            pprintf(("AppId %d is incorrect \n ", index));
            return 0;
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_dll(int argc, char **argv)
{
    int index;
    if (argc == 2)
    {
        index = atoi(argv[1]);
        if (index < 100)
        {
            pprintf(("Current Log Level for appid %d is %d \n", atoi(argv[1]), fw_display_log_level(index)));
        }
        else
        {
            pprintf(("AppId %d is incorrect \n ", index));
            return 1;
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_set(int argc, char **argv)
{
    unsigned char *p_cur;
    if (argc == 3)
    {
        p_cur = elog_getAddr(argv[1], atoi(argv[2]));
        if (p_cur != NULL)
        {
            elog_set_bit_map(p_cur);
            pprintf(("Elog set successfully\n"));
        }
        else
        {
            pprintf(("No Log present for the filename,lineno specified\n"));
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_unset(int argc, char **argv)
{
    unsigned char *p_cur;
    if (argc == 3)
    {
        if (g_elog_flag)
        {
            p_cur = elog_getAddr(argv[1], atoi(argv[2]));
            if (p_cur != NULL)
            {
                elog_reset_bit_map(p_cur);
            }
            else
            {
                pprintf(("No Log present for the filename,lineno specified\n"));
            }
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog(int argc, char **argv)
{
    int flag;
    if (argc == 2)
    {
        flag = atoi(argv[1]);
        g_elog_flag = flag;
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_file(int argc, char **argv)
{

    if (argc == 2)
    {
        elog_get_log_from_filename(argv[1]);
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_path(int argc, char **argv)
{
    char *p;
    unsigned char *curr;
    char temp[MAX_FILE_SIZE];
    char temp1[MAX_FILE_SIZE] = "";
    unsigned long base = 0;
    unsigned long count;

    int index;
    if (argc == 2)
    {
        if (strlen(argv[1]) > MAX_FILE_SIZE)
            return 0;
        count = (unsigned long)(p_high - p_low);
        if (count == 0)
        {
            pprintf(("No Logs \n"));
            return 0;
        }
        p = (char *)p_low;
        for (; base <= count; base++)
        {
            if (p[base] == '~')
            {
                if (0 == strncmp(p + base, global, strlen(global)))
                {
                    curr = (unsigned char *)(p + base + strlen(global));
                    for (index = 0; index < MAX_FILE_SIZE; index++)
                    {
                        if (curr[index] == ':')
                        {
                            temp[index] = '\0';
                            break;
                        }
                        temp[index] = curr[index];
                    }
                    if ((0 == strcmp(temp + strlen(temp) - strlen(argv[1]), argv[1])) || (0 == strcmp(temp, argv[1])))
                    {
                        if (strcmp(temp, temp1))
                            pprintf(("%s\n", temp));
                    }
                    strcpy(temp1, temp);
                }
            }
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_stat(int argc, char **argv)
{
    if (argc == 1)
    {
        if (g_elog_flag)
        {
            pprintf(("Exclusive Logging is enabled\n"));
        }
        else
        {
            pprintf(("Exclusive Logging is Disabled\n"));
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_elog_list(int argc, char **argv)
{
    if (argc == 1)
    {
        elog_display(NULL);
    }
    else if (argc == 2)
    {
        elog_display(argv[2]);
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_shell_run_n_times(int argc, char **argv)
{
    int n;
    int index;
    char command[1024];
    strcpy(command, "");
    if (argc >= 3)
    {
        n = atoi(argv[1]);
        for (index = 2; index < argc; index++)
        {
            strcat(command, argv[index]);
            strcat(command, " ");
        }
        for (index = 0; index < n; index++)
        {
            shell_run_cmd(command);
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_shell_run_forever(int argc, char **argv)
{
    int n;
    int index;
    int st_index;
    char command[1024];
    strcpy(command, "");
    if (argc >= 3)
    {
        n = atoi(argv[1]);
        for (index = 2; index < argc; index++)
        {
            strcat(command, argv[index]);
            strcat(command, " ");
        }
        while (1)
        {
            shell_run_cmd(command);
            usleep(n * 1000);
            /** Changes start for bug 213 **/
            if (SUCCESS != st_get_index_of_command(&st_index))
            {
                return FAILURE;
            }
            /** Changes End for bug 213 **/
        }
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_shell_buff_debug(int argc, char **argv)
{
    if (argc != 2)
    {
        pprintf(("Invalid Command Syntax: %s \n", argv[0]));
        return 0;
    }
    if (1 == atoi(argv[1]))
    {
        g_buff_debug = BUFF_DEBUG;
    }
    else if (0 == atoi(argv[1]))
    {
        g_buff_debug = BUFF_NO_DEBUG;
    }
    else
    {
        pprintf(("Invalid Command Argument: \"buff_debug <1(ON)/0(OFF)\"\n"));
    }
    return 0;
}

int st_cmd_shell_buff_debug_stat(int argc, char **argv)
{
    pprintf(("%d\n", g_buff_debug));
    return 0;
}

int st_cmd_shell_buff_audit(int argc, char **argv)
{
    if (argc != 1)
    {
        pprintf(("Invalid Command Syntax: %s \n", argv[0]));
        return 0;
    }
    if (fw_audit_buffer_management(1))
    {
        pprintf(("Buffer Audit Successfull\n"));
    }
    else
    {
        pprintf(("Buffer Audit Failed"));
    }
    return 0;
}

int st_cmd_shell_buffpool_threshold(int argc, char **argv)
{
    int i = 0;
    int size;
    int threshold;

    if (argc != 3)
    {
        pprintf(("Invalid Command Syntax: %s \n", argv[0]));
        return 0;
    }
    if ((0 >= atoi(argv[1])) || (0 >= atoi(argv[2])))
    {
        pprintf(("Zero or negative numbers aren't valid threshold value or buffer size\n"));
        return 0;
    }

    size = atoi(argv[1]);
    threshold = atoi(argv[2]);

    for (i = 0; i < fw_num_buffer_pools; i++)
    {
        if (fw_buffer_pool[i].size == size)
        {
            break;
        }
    }
    if (i == fw_num_buffer_pools)
    {
        pprintf(("Invalid Buffer Size\n"));
        return 0;
    }
    if (threshold > fw_buffer_pool[i].num_buffers)
    {
        pprintf(("Invalid Threshold Value\n"));
        return 0;
    }
    fw_buffer_pool[i].threshold = threshold;
    pprintf(("Threshold Value of pool with buffer size %d(pool id: %d) set to %d\n", size, i, threshold));
    return 0;
}

int st_cmd_shell_buffpool_free_buffs(int argc, char **argv)
{
    int i = 0;
    int size;
    if (argc != 2)
    {
        pprintf(("Invalid Command Syntax: %s \n", argv[0]));
        return 0;
    }
    if (0 >= atoi(argv[1]))
    {
        pprintf(("Zero or negative numbers aren't valid values of buffer size\n"));
        return 0;
    }
    size = atoi(argv[1]);

    for (i = 0; i < fw_num_buffer_pools; i++)
    {
        if (fw_buffer_pool[i].size == size)
        {
            break;
        }
    }
    if (i == fw_num_buffer_pools)
    {
        pprintf(("Invalid buffer size\n"));
        return 0;
    }
    fw_dump_free_buffs(i);
    return 0;
}

int st_cmd_shell_wait(int argc, char **argv)
{
    int msec;
    if (argc == 2)
    {
        msec = atoi(argv[1]);
        usleep(msec * 1000);
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int st_cmd_shell_run_script(int argc, char **argv)
{
    FILE *fp;
    char cmd[1024];
    char *ret = NULL;

    ret = ret;

    if (argc == 2)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            pprintf(("File <%s> not found\n", argv[1]));
            return 0;
        }
        while (!feof(fp))
        {
            ret = fgets(cmd, 1023, fp);
            if (feof(fp))
            {
                fclose(fp);
                return 1;
            }
            cmd[strlen(cmd) - 1] = '\0';
            trim(cmd);
            if (strcmp(cmd, "") == 0)
                continue;
            if (cmd[0] == '#')
                continue;
            shell_run_cmd(cmd);
        }
        fclose(fp);
    }
    else
    {
        pprintf(("Invalid Command Syntax:%s \n", argv[0]));
    }
    return 0;
}

int stInit(char *prompt, char *welcome_disclaimer)
{
    pthread_t tid;
    strcpy(g_prompt, prompt);
    strcpy(g_welcome_disclaimer, welcome_disclaimer);
    /*	pthread_create(&tid,NULL,ST_HANDLER,NULL);*/
    pthread_create(&tid, NULL, ST_TELNET_HANDLER, NULL);
    shell_add_cmd("sll", "Set Log Level", st_cmd_sll);
    shell_add_cmd("dll", "Display Log Level", st_cmd_dll);
    shell_add_cmd("?", "List Commands Supported", st_cmd_help);
    shell_add_cmd("help", "Print the help", st_cmd_help);
    shell_add_cmd("dbu", "Display buffer Usage", st_cmd_dbu);
    shell_add_cmd("ipcdbu", "Display IPC buffer Usage", st_cmd_ipcdbu);
    shell_add_cmd("elog", "Enable/Disable Exclusive Logging 0/1", st_cmd_elog);
    shell_add_cmd("elog_set", "Enable Exclusive Logging for particular log", st_cmd_elog_set);
    shell_add_cmd("elog_unset", "Disable Exclusive Logging for particular log", st_cmd_elog_unset);
    shell_add_cmd("elog_file", "Display elog for a file", st_cmd_elog_file);
    shell_add_cmd("elog_path", "Display absolute path of a file", st_cmd_elog_path);
    shell_add_cmd("elog_list", "Display Enabled elog", st_cmd_elog_list);
    shell_add_cmd("elog_stat", "Check whether elog is enabled or disabled", st_cmd_elog_stat);
    shell_add_cmd("shell_run_script", "Specify filename to run script", st_cmd_shell_run_script);
    shell_add_cmd("shell_wait", "shell_wait <number of miliseonds>", st_cmd_shell_wait);
    shell_add_cmd("shell_run_n_times", "shell_run_n_times <n-times> <cmd>", st_cmd_shell_run_n_times);
    shell_add_cmd("shell_run_forever", "shell_run_forever <number_of_miliseconds_to_wait> <cmd>", st_cmd_shell_run_forever);
    shell_add_cmd("buff_debug", "buff_debug <1(ON)/0(OFF)>", st_cmd_shell_buff_debug);
    shell_add_cmd("buff_debug_stat", "buff_debug_stat", st_cmd_shell_buff_debug_stat);
    shell_add_cmd("buffpool_threshold", "buffpool_thred <buff size> <pool threshold>", st_cmd_shell_buffpool_threshold);
    shell_add_cmd("buffpool_free_buffs", "buffpool_free_buffs <buff size>", st_cmd_shell_buffpool_free_buffs);
    shell_add_cmd("buffaudit", "buffaudit", st_cmd_shell_buff_audit);
    shell_add_cmd("history", "history", history_cb);
    return 0;
}

int is_command_repleated(char *current_cmd)
{
    unsigned int last_cmd_index = 0;

    if (g_history_cmd.current_index == 0)
    {
        last_cmd_index = ST_MAX_HISTORY_CMDS - 1;
    }
    else
    {
        last_cmd_index = g_history_cmd.current_index - 1;
    }

    if ((strlen(g_history_cmd.command[last_cmd_index])) &&
        (0 == strcmp(g_history_cmd.command[last_cmd_index], current_cmd)))
    {
        return 1;
    }
    return 0;
}

int history_cb(int argc, char **argv)
{
    unsigned int index = 0;
    unsigned int start_index = 0;
    unsigned int end_index = 0;

    start_index = g_history_cmd.current_index; /* oldest first, current always points on index to be overwritten */
    if (g_history_cmd.current_index == 0)
    {
        end_index = ST_MAX_HISTORY_CMDS - 1; /* newest last */
    }
    else
    {
        end_index = g_history_cmd.current_index - 1; /* newest last */
    }

    for (index = start_index; index != end_index; index = ((index + 1) % ST_MAX_HISTORY_CMDS))
    {
        if (0 != strlen(g_history_cmd.command[index]))
        {
            pprintf(("%s\n", g_history_cmd.command[index]));
        }
    }

    /** Print final index **/
    if (0 != strlen(g_history_cmd.command[index]))
    {
        pprintf(("%s\n", g_history_cmd.command[index]));
    }

    return 0;
}

int fw_set_log_level(unsigned int appid, int level)
{
    g_app_map[appid].__tracelevel__ = level;
    return 1;
}

int fw_display_log_level(unsigned int appid)
{
    return g_app_map[appid].__tracelevel__;
}

int elog_set_bit_map(unsigned char *p_curr)
{
    unsigned long count;
    int byte;
    int bit;
    int temp;
    count = (unsigned long)(p_curr - p_low);
    //	printf("count is %d\n",count);
    byte = count / 8;
    bit = 7 - count % 8;
    temp = 1 << bit;
    bit_map[byte] = bit_map[byte] | temp;
    return 0;
}

int elog_reset_bit_map(unsigned char *p_curr)
{
    unsigned long count;
    int byte;
    int bit;
    int temp;
    count = (unsigned long)(p_curr - p_low);
    byte = count / 8;
    bit = 7 - count % 8;
    temp = 1 << bit;
    bit_map[byte] = bit_map[byte] & ~temp;
    return 0;
}

int elog_display(char *search_filename)
{
    unsigned long index;
    unsigned char *p;
    char filename[MAX_FILE_SIZE];
    char data[MAX_DATA_LENGTH];
    int lineno;
    unsigned long count = (unsigned long)(p_high - p_low);
    int flag = 1;
    if (search_filename == NULL)
    {
        flag = 0;
    }
    p = p_low;
    for (index = 0; index <= count; index++)
    {
        if (1 == elog_isset_bit_map(p + index))
        {
            elog_getData(p + index, filename, &lineno, data);
            if (flag == 1)
            {
                if (strcmp(search_filename, filename) == 0)
                    pprintf(("<%s>:<%d>:<%s>\n", filename, lineno, data));
            }
            else
                pprintf(("<%s>:<%d>:<%s>\n", filename, lineno, data));
        }
    }
    return 0;
}

int elog_isset_bit_map(unsigned char *p_curr)
{
    unsigned long count;
    int byte;
    int bit;
    int temp;

    if (p_curr > p_high)
        return 0;
    if (p_curr < p_low)
        return 0;

    count = (unsigned long)(p_curr - p_low);
    byte = count / 8;
    bit = 7 - count % 8;
    temp = 1 << bit;
    if ((temp ^ bit_map[byte]) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void elog_disp_bit_map()
{
    int index;
    for (index = 0; index < bit_map_size; index++)
    {
        printf("Index %d Value %d\n", index, bit_map[index]);
    }
}

unsigned char *elog_getAddr(char *search_file_name, int lineno)
{
    char *p;
    char filename_line[10 + MAX_FILE_SIZE + MAX_LINE_NO_LENGTH];
    unsigned long base = 0;
    unsigned long count;

    if (strlen(search_file_name) > MAX_FILE_SIZE)
        return NULL;
    sprintf(filename_line, "%s%s:%d:", global, search_file_name, lineno);
    count = (unsigned long)(p_high - p_low);
    if (count == 0)
    {
        pprintf(("No Logs \n"));
        return 0;
    }
    p = (char *)p_low;
    for (; base <= count; base++)
    {
        if (p[base] == '~')
        {
            if (0 == strncmp(p + base, filename_line, strlen(filename_line)))
            {
                return (unsigned char *)(p + base);
            }
        }
    }
    return NULL;
}

int elog_get_log_from_filename(char *search_file_name)
{
    char *p;
    unsigned char *curr;
    char temp[MAX_DATA_LENGTH];
    char filename_line[10 + MAX_FILE_SIZE];
    unsigned long base = 0;
    unsigned long count;

    int index;
    if (strlen(search_file_name) > MAX_FILE_SIZE)
        return 0;
    sprintf(filename_line, "%s%s:", global, search_file_name);
    count = (unsigned long)(p_high - p_low);
    if (count == 0)
    {
        pprintf(("No Logs \n"));
        return 0;
    }
    p = (char *)p_low;
    for (; base <= count; base++)
    {
        if (p[base] == '~')
        {
            if (0 == strncmp(p + base, filename_line, strlen(filename_line)))
            {
                curr = (unsigned char *)(p + base + strlen(filename_line));
                for (index = 0; index < MAX_LINE_NO_LENGTH; index++)
                {
                    if (curr[index] == ':')
                    {
                        temp[index] = '\0';
                        break;
                    }
                    temp[index] = curr[index];
                }
                curr = curr + index + 1;
                pprintf(("<%s>:<%d>", search_file_name, atoi(temp)));
                for (index = 0; index < MAX_DATA_LENGTH; index++)
                {
                    if (curr[index] == ':')
                    {
                        temp[index] = '\0';
                        break;
                    }
                    temp[index] = curr[index];
                }
                pprintf(("<%s>\n", temp));
            }
        }
    }
    return 0;
}

int elog_getData(unsigned char *address, char *file_name, int *lineno, char *data)
{
    char temp[MAX_FILE_SIZE + MAX_LINE_NO_LENGTH + MAX_DATA_LENGTH];
    int index;
    int flag = 0;
    unsigned char *curr;
    char *token = NULL;
    if (address < p_low || address > p_high)
    {
        return 0;
    }
    if (0 == strncmp((const char *)address, global, 8))
    {
        curr = address + strlen(global);
        for (index = 0; index < MAX_FILE_SIZE + MAX_LINE_NO_LENGTH + MAX_DATA_LENGTH; index++)
        {
            if (flag == 2 && curr[index] == ':')
            {
                flag = 3;
                temp[index] = '\0';
                break;
            }
            if (flag == 1 && curr[index] == ':')
            {
                flag = 2;
            }
            if (flag == 0 && curr[index] == ':')
            {
                flag = 1;
            }
            temp[index] = curr[index];
        }
    }
    if (flag != 3)
        return 0;

    token = strtok(temp, ":");
    if (NULL == token)
    {
        pprintf(("Error while tokanizing file name in elog_getdata:\n"));
        return 0;
    }
    strcpy(file_name, token);

    token = strtok(NULL, ":");
    if (NULL == token)
    {
        pprintf(("Error while tokanizing line number in elog_getdata:\n"));
        return 0;
    }
    *lineno = atoi(token);

    token = strtok(NULL, ":");
    if (NULL == token)
    {
        pprintf(("Error while tokanizing data in elog_getdata:\n"));
        return 0;
    }
    strcpy(data, token);
    return 1;
}

void myfunc(char *string, int opcode)
{
    FILE *fp;
    pthread_mutex_lock(&(fwfileMu));
    fp = fopen("rtfile", "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s:%d\n", string, opcode);
        fclose(fp);
    }
    pthread_mutex_unlock(&(fwfileMu));
}

int fw_tid_to_appid()
{
    int index;
    pthread_t tid = pthread_self();
    for (index = 0; index < MAX_TOTAL_APP_ID; index++)
    {
        if (g_app_map[index].tid == tid)
        {
            return index;
        }
    }
    return -1;
}

void shell_run_cmd(char *cmd)
{
    if (cmd != NULL)
    {
        st_command_handler(cmd);
    }
}

int tapSocket(char *ifname)
{
    struct ifreq ifr;
    int ret;
    int fd;

    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "could not open the tun device\n");
        perror("could not opent the tun device\n");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    ret = ioctl(fd, TUNSETIFF, (void *)&ifr);
    if (ret < 0)
    {
        perror("Creating Interface");
        close(fd);
        exit(1);
    }

    ret = ioctl(fd, TUNSETPERSIST, 1);
    if (ret < 0)
    {
        perror("Enabling Persistant");
        close(fd);
        exit(1);
    }

    return fd;
}

void tapSetMac(char *ifname, unsigned char *mac)
{
    struct ifreq ifr;
    int s;
    int i;
    int ret;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0)
    {
        perror("problem in obtaing socket in tapSetMac\n");
        return;
    }
    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFHWADDR, &ifr);
    for (i = 0; i < 6; i++)
    {
        ifr.ifr_hwaddr.sa_data[i] = mac[i];
    }
    ret = ioctl(s, SIOCSIFHWADDR, &ifr);
    if (ret < 0)
    {
        perror("problem in setting the mac in tapSetMac\n");
        close(s);
        return;
    }
    close(s);
}

int tapRead(int fd, char *ptr)
{
    int nread;

    nread = read(fd, ptr, 65535);
    if (nread <= 0)
    {
        perror("problem in reading from tap\n");
        return nread;
    }
    return (nread);
}

int udpSocket6(int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in6 serv_addr;
    int buf_value = 1000000;

    fd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("getUdpBoundSocket6:socket");
        return 0;
    }

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    serv_addr.sin6_addr = in6addr_any;
    serv_addr.sin6_port = htons(localPort);

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("getUDPBoundSocket6:bind");
        close(fd);
        return 0;
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsock6opt1");
        exit(1);
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsock6op2");
        exit(1);
    }

    return fd;
}

int udpRead6(int fd, char *data)
{
    int n;
    struct sockaddr_in6 S;

    socklen_t len;

    len = sizeof(S);
    n = recvfrom(fd, data, MAXUDPLEN, 0, (struct sockaddr *)&S, &len);

    if (n < 0)
        perror("Error in udpRead6\n");

    return n;
}

int udpWrite6(int fd, char *remoteipaddress, int remotePort, char *data, int length)
{
    struct sockaddr_in6 cli_addr, serv_addr;
    int ret;

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, remoteipaddress, &serv_addr.sin6_addr);
    serv_addr.sin6_port = htons(remotePort);

    ret = sendto(fd, data, length, 0, (struct sockaddr *)&serv_addr, sizeof(cli_addr));
    if (ret < 0)
    {
        perror("udpWrite6:sendto");
        return 0;
    }
    return ret;
}

int udpReadFrom6(int fd, char *data, char *ip, unsigned short *port)
{
    int n;
    struct sockaddr_in6 s;
    socklen_t len;

    len = sizeof(s);
    n = recvfrom(fd, data, MAXUDPLEN, 0, (struct sockaddr *)&s, &len);
    if (n <= 0)
    {
        strcpy(ip, "");
        *port = 0;
        return n;
    }

    if (n > 0)
    {
        inet_ntop(AF_INET6, &s.sin6_addr, ip, 1024);
        *port = ntohs(s.sin6_port);
    }

    return n;
}

int udpSocketExt(char *localip, int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in serv_addr;
    int so_broadcast;
    int buf_value = 1000000;
    int one = 1;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("getUdpBoundSocket:socket");
        exit(1);
    }

#ifdef MULTIQGTP
    int optval = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(localip);
    serv_addr.sin_port = htons(localPort);

    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockopt1");
        exit(1);
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockop2");
        exit(1);
    }

    so_broadcast = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof so_broadcast);
    if (ret)
        perror("setsockopt(broadcast)");

    ret = setsockopt(fd, IPPROTO_IP, IP_PKTINFO, (const char[]){1},
                     sizeof(one));
    ret = setsockopt(fd, IPPROTO_IP, IP_RECVTOS, (const char[]){1},
                     sizeof(one));
    ret = setsockopt(fd, IPPROTO_IP, IP_RECVTTL, (const char[]){1},
                     sizeof(one));

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("getUDPBoundSocket:bind");
        exit(1);
    }

    return fd;
}

int udpSocketExt6(char *localip, int localPort)
{
    int fd;
    int ret;
    struct sockaddr_in6 serv_addr;
    int so_broadcast;
    int buf_value = 1000000;
    int one = 1;

    fd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("getUdpBoundSocket:socket");
        return 0;
    }

#ifdef MULTIQGTP
    int optval = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
#endif

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    ret = inet_pton(AF_INET6, localip, &serv_addr.sin6_addr);
    if (ret <= 0)
    {
        perror("inet_ntop");
        exit(1);
    }
    serv_addr.sin6_port = htons(localPort);

    so_broadcast = 1;
    ret = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &so_broadcast, sizeof so_broadcast);
    if (ret)
        perror("setsockopt(broadcast)");

    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsock6opt1");
        exit(1);
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsock6op2");
        exit(1);
    }

    if (setsockopt(fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, (const char[]){1},
                   sizeof(one)) < 0)
    {
        perror("ip packet info setsockopt() IPV6_PKTINFO error");
        exit(1);
    }

    ret = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, (const char[]){1},
                     sizeof(ret));
    ret = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVTCLASS, (const char[]){1},
                     sizeof(ret));

    ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0)
    {
        perror("getUDPBoundSocket:bind");
        close(fd);
        return 0;
    }

    return fd;
}

void stringkey2hex(char *key, unsigned char *digestkey, int *digestkeylength)
{
    int i;
    char temp[1024];
    char *scan;
    int lengthstring;
    int count = 0;

    trim(key);

    scan = key;

    if (*scan != '0')
    {
        fprintf(stderr, "improper key format, must begin with 0x\n");
        exit(1);
    }
    scan++;
    if ((*scan != 'x') && (*scan != 'X'))
    {
        fprintf(stderr, "improper key format, must begin with 0x\n");
        exit(1);
    }
    scan++;
    lengthstring = strlen(scan);
    if (lengthstring % 2)
    {
        fprintf(stderr, "improper key format, must have even number of digits\n");
        exit(1);
    }
    for (i = 0; i < lengthstring; i += 2)
    {
        temp[0] = '0';
        temp[1] = 'x';
        temp[2] = scan[i];
        temp[3] = scan[i + 1];
        temp[4] = '\0';
        if (count == 1024)
        {
            fprintf(stderr, "md5 key overflow\n");
            exit(1);
        }
        digestkey[count] = strtoul(temp, NULL, 0);
        count++;
    }
    *digestkeylength = count;
}

int extract_ipv4_interface(char *ipv4_addr, char *interface)
{
    FILE *fpt_ipv4;
    FILE *fpt_default;
    int ret;

    if (strcmp(ipv4_addr, "0.0.0.0") == 0)
    {
        return 0;
    }

    fpt_ipv4 = popen("ip r s", "r");
    if (fpt_ipv4 == NULL)
    {
        fprintf(stderr, "Warning: Could not open <ip r s>\n");
        return 0;
    }

    //Call function to search the interface for the ip
    ret = search_interface_ipv4(fpt_ipv4, ipv4_addr, interface);
    if (0 == ret)
    {
        fpt_default = popen("ip r s", "r");
        if (fpt_default == NULL)
        {
            fprintf(stderr, "Warning: Could not open <ip r s>\n");
            pclose(fpt_ipv4);
            return 0;
        }

        ret = search_default_interface(fpt_default, interface);
        if (0 == ret)
        {
            fprintf(stderr, "Warning: Interface entry not found: <ip r s>\n");
        }
        pclose(fpt_default);
    }
    pclose(fpt_ipv4);
    return ret;
}

int search_interface_ipv4(FILE *fpt, char *ip_addr, char *interface)
{
    char buffer[1024];
    char *token;
    unsigned int dest_ip;
    unsigned int dest_ip_compare;
    unsigned int buffer_ip;
    unsigned int entry_found = 0;
    unsigned int r_shf_val;
    unsigned int prev_r_shf_val = 32;
    unsigned int subnet_ip;

    inet_pton(AF_INET, ip_addr, (void *)&dest_ip);
    dest_ip = ntohl(dest_ip);

    while (fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';

        r_shf_val = 0;
        dest_ip_compare = dest_ip;

        //Tokenize the buffer with delimiter 'space' and '/'
        token = strtok(buffer, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: Ip address not found: <ip r s>\n");
            return 0;
        }
        else if ((strcmp(token, "unreachable") != 0) && (strcmp(token, "default") != 0) && (strcmp(token, "cache") != 0))
        {
            inet_pton(AF_INET, token, (void *)&buffer_ip);
            buffer_ip = ntohl(buffer_ip);
        }
        else
        {
            continue;
        }

        token = strtok(NULL, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: Subnet not found: <ip r s>\n");
            return 0;
        }
        else if ((strcmp(token, "dev") != 0) && (strcmp(token, "via") != 0))
        {
            r_shf_val = 32 - atoi(token);
            subnet_ip = (0xFFFFFFFF << r_shf_val);
            dest_ip_compare &= subnet_ip;
            buffer_ip &= subnet_ip;
        }

        if (dest_ip_compare == buffer_ip)
        {
            if (r_shf_val <= prev_r_shf_val)
            {
                entry_found = 1;
                while (strcmp(token, "dev") != 0)
                {
                    token = strtok(NULL, " /");
                    if (token == NULL)
                    {
                        fprintf(stderr, "Warning: dev not found: <ip r s>\n");
                        return 0;
                    }
                }

                token = strtok(NULL, " /");
                if (token == NULL)
                {
                    fprintf(stderr, "Warning: Interface not found: <ip r s>\n");
                    return 0;
                }
                strcpy(interface, token);
                trim(interface);
                prev_r_shf_val = r_shf_val;
            }
            if (r_shf_val == 0)
            {
                break;
            }
        }
    }
    return entry_found;
}

int extract_src_ipv4_from_interface(char *interface)
{
    FILE *fpt_src_ipv4;
    char command[1024];
    char buffer[1024];
    char source_ip[1024];
    unsigned int src_ip;
    char *token;

    strcpy(source_ip, "0.0.0.0");

    strcpy(command, "ip a s ");
    strcat(command, interface);
    fpt_src_ipv4 = popen(command, "r");
    if (fpt_src_ipv4 == NULL)
    {
        fprintf(stderr, "Warning: Could not open <ip a s> \n");
        inet_pton(AF_INET, source_ip, (void *)&src_ip);
        src_ip = ntohl(src_ip);
        return src_ip;
    }

    while (fgets(buffer, 1023, fpt_src_ipv4) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';

        //Tokenize the buffer with delimiter 'space' and '/'
        token = strtok(buffer, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: inet not found: <ip a s>\n");
            break;
        }
        else if (strcmp(token, "inet") == 0)
        {
            token = strtok(NULL, " /");
            if (token == NULL)
            {
                fprintf(stderr, "Warning: Source IP not found: <ip a s>\n");
                break;
            }
            strcpy(source_ip, token);
            trim(source_ip);
            break;
        }
    }
    pclose(fpt_src_ipv4);

    inet_pton(AF_INET, source_ip, (void *)&src_ip);
    src_ip = ntohl(src_ip);
    return src_ip;
}

int extract_ipv6_interface(char *ipv6_addr, char *interface)
{
    FILE *fpt_ipv6;
    FILE *fpt_default;
    int ret;

    if (strcmp((char *)ipv6_addr, "::") == 0)
    {
        return 0;
    }

    fpt_ipv6 = popen("ip -6 r s", "r");
    if (fpt_ipv6 == NULL)
    {
        fprintf(stderr, "Warning: Could not open <ip -6 r s>\n");
        return 0;
    }

    //Call function to search the interface for the ip
    ret = search_interface_ipv6(fpt_ipv6, ipv6_addr, interface);
    if (0 == ret)
    {
        fpt_default = popen("ip -6 r s", "r");
        if (fpt_default == NULL)
        {
            fprintf(stderr, "Warning: Could not open <ip -6 r s>\n");
            pclose(fpt_ipv6);
            return 0;
        }
        ret = search_default_interface(fpt_default, interface);
        if (0 == ret)
        {
            fprintf(stderr, "Warning: Interface entry not found: <ip -6 r s>\n");
        }
        pclose(fpt_default);
    }
    pclose(fpt_ipv6);
    return ret;
}

int search_interface_ipv6(FILE *fpt, char *ip_addr, char *interface)
{
    char buffer[1024];
    char *token;
    unsigned char buffer_ip[16];
    unsigned int entry_found = 0;
    unsigned char dest_ip[16];
    unsigned char dest_ip_compare[16];
    unsigned int subnet;
    unsigned int prev_subnet = 128;
    unsigned int temp_subnet;

    inet_pton(AF_INET6, ip_addr, (void *)dest_ip);

    while (fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';

        subnet = 0;
        memcpy(dest_ip_compare, dest_ip, 16);

        //Tokenize the buffer with delimiter 'space' and '/'
        token = strtok(buffer, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: Ip address not found: <ip -6 r s>\n");
            return 0;
        }
        else if ((strcmp(token, "unreachable") != 0) && (strcmp(token, "default") != 0) && (strcmp(token, "cache") != 0))
        {
            inet_pton(AF_INET6, token, (void *)buffer_ip);
        }
        else
        {
            continue;
        }

        token = strtok(NULL, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: Subnet not found: <ip -6 r s>\n");
            return 0;
        }
        else if ((strcmp(token, "dev") != 0) && (strcmp(token, "via") != 0))
        {
            temp_subnet = atoi(token);
            if (128 < temp_subnet)
            {
                fprintf(stderr, "Warning : subnet length is greater than 128\n");
                return 0;
            }

            subnet = 128 - temp_subnet;
            form_ip_address_with_subnet(dest_ip_compare, subnet);
            form_ip_address_with_subnet(buffer_ip, subnet);
        }

        if (memcmp(dest_ip_compare, buffer_ip, 16) == 0)
        {
            if (subnet <= prev_subnet)
            {
                entry_found = 1;
                while (strcmp(token, "dev") != 0)
                {
                    token = strtok(NULL, " /");
                    if (token == NULL)
                    {
                        fprintf(stderr, "Warning: dev not found: <ip -6 r s>\n");
                        return 0;
                    }
                }

                token = strtok(NULL, " /");
                if (token == NULL)
                {
                    fprintf(stderr, "Warning: Interface not found: <ip -6 r s>\n");
                    return 0;
                }
                strcpy(interface, token);
                trim(interface);
                prev_subnet = subnet;
            }
            if (subnet == 0)
            {
                break;
            }
        }
    }
    return entry_found;
}

int search_default_interface(FILE *fpt, char *interface)
{
    char buffer[1024];
    char *token;
    unsigned int entry_found = 0;

    while (fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';

        //Tokenize the buffer with delimiter 'space' and '/'
        token = strtok(buffer, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: default route entry not found\n");
            return 0;
        }
        else if (strcmp(token, "default") == 0)
        {
            entry_found = 1;
            while (strcmp(token, "dev") != 0)
            {
                token = strtok(NULL, " /");
                if (token == NULL)
                {
                    fprintf(stderr, "Warning: dev not found in default route entry\n");
                    return 0;
                }
            }

            token = strtok(NULL, " /");
            if (token == NULL)
            {
                fprintf(stderr, "Warning: Interface not found in default route entry\n");
                return 0;
            }
            strcpy(interface, token);
            trim(interface);
            break;
        }
        else
        {
            continue;
        }
    }
    return entry_found;
}

void form_ip_address_with_subnet(unsigned char *ip_addr, unsigned int subnet)
{
    int *temp_ip;
    int rounds;
    int remaining_bits;
    int i, temp;

    temp_ip = (int *)ip_addr;
    rounds = subnet / 32;
    remaining_bits = subnet % 32;

    for (i = 0; i < rounds; i++)
    {
        temp_ip[3 - i] = 0;
    }

    if (remaining_bits != 0)
    {
        temp = temp_ip[3 - i];
        temp = (temp << remaining_bits);
        temp_ip[3 - i] = temp;
    }
}

void extract_src_ipv6_from_interface(char *interface, unsigned char *src_ip)
{
    FILE *fpt_src_ipv6;
    char command[2048];
    char buffer[1024];
    char source_ip[1024];
    char *token;

    strcpy(source_ip, "::");

    strcpy(command, "ip a s ");
    strcat(command, interface);
    fpt_src_ipv6 = popen(command, "r");

    if (fpt_src_ipv6 == NULL)
    {
        fprintf(stderr, "could not open file ip a s \n");
        inet_pton(AF_INET6, source_ip, (void *)src_ip);
        return;
    }
    while (fgets(buffer, 1023, fpt_src_ipv6) != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0';
        //Tokenize the buffer with delimiter 'space' and '/'
        token = strtok(buffer, " /");
        if (token == NULL)
        {
            fprintf(stderr, "Warning: inet6 not found: <ip a s>\n");
            break;
        }
        else if (strcmp(token, "inet6") == 0)
        {
            token = strtok(NULL, " /");
            if (token == NULL)
            {
                fprintf(stderr, "Warning: Source IP not found: <ip a s>\n");
                break;
            }
            strcpy(source_ip, token);
            trim(source_ip);
            break;
        }
    }
    pclose(fpt_src_ipv6);

    inet_pton(AF_INET6, source_ip, (void *)src_ip);
}

int fw_init_ipc_socket()
{
    char filepath[256] = {0};
    uint8_t app_id = 0;
    int ipc_socket_fd = 0;

    /** changes start for bug 180 **/
    sprintf(filepath, "/tmp/upf_%d_%d", getpid(), app_id);
    /** changes end for bug 180 **/
    ipc_socket_fd = unixdomainSocket(filepath);
    if (ipc_socket_fd <= 0)
    {
        fprintf(stderr, "could not open unix domain socket\n");
        exit(1);
    }
    return ipc_socket_fd;
}

int fw_init_ipc_ack_socket()
{
    int ipc_ack_socket_fd = 0;

    /** changes start for bug 180 **/
    char filepath[256] = {0};
    sprintf(filepath, "/tmp/agent_recv_%d", getpid());
    ipc_ack_socket_fd = unixdomainSocket(filepath);
    /** changes end for bug 180 **/
    if (ipc_ack_socket_fd <= 0)
    {
        fprintf(stderr, "could not open unix domain socket\n");
        exit(1);
    }
    return ipc_ack_socket_fd;
}

int fw_core_count()
{
    int ret;

    ret = sysconf(_SC_NPROCESSORS_CONF);
    if (ret < 0)
    {
        fprintf(stderr, "fw_core_count: could not obtain core count\n");
        exit(1);
    }

    return ret;
}

int fw_raw_socket(int protocol, char *ip_addr)
{
    int fd;
    int buf_value = 1000000;
    struct sockaddr_in serv_addr;
    int ret = 0;

    fd = socket(AF_INET, SOCK_RAW, protocol);
    if (fd < 0)
    {
        fprintf(stderr, "problem in opening raw socket\n");
        exit(1);
    }

    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockop2");
        exit(1);
    }

    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockopt1");
        exit(1);
    }

    if (strcmp(ip_addr, "") != 0)
    {
        memset((char *)&serv_addr, '\0', sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(ip_addr);
        ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (ret < 0)
        {
            perror("raw socket:bind fail in ipv4");
            exit(1);
        }
    }

#if 0
    if(setsockopt(fd, IPPROTO_IP, IP_HDRINCL, (const char[]){1},
        sizeof(one)) < 0)
    {
        perror("ip header setsockopt() IP_HDRINCL error");
        exit(1);
    }

    if(setsockopt(fd, IPPROTO_IP, IP_PKTINFO, (const char[]){1},
        sizeof(one)) < 0)
    {
        perror("ip packet info setsockopt() IP_PKTINFO error");
        exit(1);
    }

    if(ioctl(fd,(int)FIONBIO,(char*)&on))
    {
        fprintf(stderr,"problem in socket non-blocking\n");
        exit(1);
    }
#endif

    return fd;
}

int fw_raw_socket6(int protocol, char *ip_addr)
{
    int fd;
    int buf_value = 1000000;
    int ret = 0;
    struct sockaddr_in6 serv_addr;

    fd = socket(AF_INET6, SOCK_RAW, protocol);
    if (fd < 0)
    {
        fprintf(stderr, "problem in opening raw socket\n");
        exit(1);
    }

    if ((setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockop2");
        exit(1);
    }
    if ((setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *)&buf_value, sizeof(int))) == -1)
    {
        perror("setsockopt1");
        exit(1);
    }

    if (strcmp(ip_addr, "") != 0)
    {
        memset((char *)&serv_addr, '\0', sizeof(serv_addr));
        serv_addr.sin6_family = AF_INET6;
        inet_pton(AF_INET6, ip_addr, &serv_addr.sin6_addr);
        ret = bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (0 > ret)
        {
            perror("raw socket:bind fail in ipv6");
            exit(1);
        }
    }

#if 0
    if(setsockopt(fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, (const char[]){1},
        sizeof(one)) < 0)
    {
        perror("ip packet info setsockopt() IPV6_PKTINFO error");
        exit(1);
    }
    ret = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, (const char[]){1},
        sizeof(ret));
    ret = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVTCLASS, (const char[]){1},
        sizeof(ret));
#endif
    return fd;
}

void print_in_addr(struct in_addr *i)
{
    char foo[1024];

    inet_ntop(AF_INET, i, foo, INET_ADDRSTRLEN);
    printf("<%s>\n", foo);
}

void print_in_addr6(struct in6_addr *i)
{
    dumpBytesTo(stdout, i->s6_addr, 16);
}

/** changes start for bug 155 **/
int linux_myendian()
{
    char *scan;
    int a = 1;

    scan = (char *)&a;
    if (scan[3] == 1)
    {
        return BIG_ENDIAN_MACHINE;
    }
    return LITTLE_ENDIAN_MACHINE;
}

/** changes end for bug 155 **/

#ifdef DPDK_DP
int fw_read_ext(int fd, char *buffer, char *srcip, char *dstip, unsigned short *srcport, unsigned int *ttl, unsigned int *tos)
{
    /** refer to http://alas.matf.bg.ac.rs/manuals/lspe/snode=153.html for stuns on cmsg **/
    int n;
    struct in_pktinfo *pIpPktInfo = NULL;
    struct sockaddr_in RecvNode;
    struct iovec Iov;
    struct cmsghdr *pCmsgInfo = NULL;
    char au1Cmsg[CMSG_SPACE(CMSG_LEN(sizeof(struct in_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char)))];
    struct msghdr PktInfo;

    memset(&PktInfo, 0, sizeof(struct msghdr));
    memset(&RecvNode, 0, sizeof(struct sockaddr_in));
    memset(au1Cmsg, 0, CMSG_SPACE(CMSG_LEN(sizeof(struct in_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char))));

    PktInfo.msg_name = (void *)&RecvNode;
    PktInfo.msg_namelen = sizeof(struct sockaddr_in);
    Iov.iov_base = buffer;
    Iov.iov_len = 65536;
    PktInfo.msg_iov = &Iov;
    PktInfo.msg_iovlen = 1;
    PktInfo.msg_control = (void *)au1Cmsg;
    PktInfo.msg_controllen = CMSG_SPACE(CMSG_LEN(sizeof(struct in_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char))) + CMSG_SPACE(CMSG_LEN(sizeof(unsigned char)));
    pCmsgInfo = CMSG_FIRSTHDR(&PktInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IP;
    pCmsgInfo->cmsg_type = IP_PKTINFO;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));

    pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IP;
    pCmsgInfo->cmsg_type = IP_TTL;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(unsigned char));

    pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IP;
    pCmsgInfo->cmsg_type = IP_TOS;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(unsigned char));

    /** likewise use CMNSG_NXTHDR **/

    n = recvmsg(fd, &PktInfo, 0);
    for (pCmsgInfo = CMSG_FIRSTHDR(&PktInfo); pCmsgInfo != NULL; pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo))
    {
        if (pCmsgInfo->cmsg_type == IP_PKTINFO)
        {
            pIpPktInfo = (struct in_pktinfo *)CMSG_DATA(pCmsgInfo);
            strcpy(srcip, inet_ntoa(RecvNode.sin_addr));
            *srcport = ntohs(RecvNode.sin_port);
            strcpy(dstip, inet_ntoa(pIpPktInfo->ipi_addr));
        }
        if (pCmsgInfo->cmsg_type == IP_TTL)
        {
            *ttl = *(unsigned char *)CMSG_DATA(pCmsgInfo);
        }

        if (pCmsgInfo->cmsg_type == IP_TOS)
        {
            *tos = *(unsigned char *)CMSG_DATA(pCmsgInfo);
        }
    }
    return n;
}

int fw_read6_ext(int fd, char *buffer, char *srcip, char *dstip, unsigned short *srcport, unsigned int *hoplimit, unsigned int *tos)
{
    int n;
    struct in6_pktinfo *pIpPktInfo = NULL;
    struct sockaddr_in6 RecvNode;
    struct iovec Iov;
    struct cmsghdr *pCmsgInfo = NULL;
    char au1Cmsg[CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(int))) + CMSG_SPACE(CMSG_LEN(sizeof(int)))];
    struct msghdr PktInfo;

    memset(&PktInfo, 0, sizeof(struct msghdr));
    memset(&RecvNode, 0, sizeof(struct sockaddr_in6));

    memset(au1Cmsg, 0, CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(int))) + CMSG_SPACE(CMSG_LEN(sizeof(int))));
    PktInfo.msg_name = (void *)&RecvNode;
    PktInfo.msg_namelen = sizeof(struct sockaddr_in6);
    Iov.iov_base = buffer;
    Iov.iov_len = 65536;
    PktInfo.msg_iov = &Iov;
    PktInfo.msg_iovlen = 1;
    PktInfo.msg_control = (void *)au1Cmsg;
    PktInfo.msg_controllen = CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(int))) + CMSG_SPACE(CMSG_LEN(sizeof(int)));

    pCmsgInfo = CMSG_FIRSTHDR(&PktInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IPV6;
    pCmsgInfo->cmsg_type = IPV6_PKTINFO;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));

    pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IPV6;
    pCmsgInfo->cmsg_type = IPV6_HOPLIMIT;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(int));

    pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IPV6;
    pCmsgInfo->cmsg_type = IPV6_TCLASS;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(int));

    n = recvmsg(fd, &PktInfo, 0);

    for (pCmsgInfo = CMSG_FIRSTHDR(&PktInfo); pCmsgInfo != NULL; pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo))
    {
        if (pCmsgInfo->cmsg_type == IPV6_PKTINFO)
        {
            pIpPktInfo = (struct in6_pktinfo *)CMSG_DATA(pCmsgInfo);
            memcpy(srcip, RecvNode.sin6_addr.s6_addr, 16);
            memcpy(dstip, pIpPktInfo->ipi6_addr.s6_addr, 16);
            *srcport = ntohs(RecvNode.sin6_port);
        }
        if (pCmsgInfo->cmsg_type == IPV6_HOPLIMIT)
        {
            unsigned int *temp = (unsigned int *)CMSG_DATA(pCmsgInfo);
            *hoplimit = *temp;
        }

        if (pCmsgInfo->cmsg_type == IPV6_TCLASS)
        {
            unsigned int *temp = (unsigned int *)CMSG_DATA(pCmsgInfo);
            *tos = *temp;
        }
    }
    return n;
}

int fw_raw_read6(int fd, char *data)
{
    int n;
    struct sockaddr_in6 S;

    socklen_t len;

    len = sizeof(S);
    n = recvfrom(fd, data, MAXUDPLEN, 0, (struct sockaddr *)&S, &len);
    return n;
}

int fw_raw_read(int fd, char *data)
{
    int n;
    n = udpRead(fd, data);
    return n;
}

int fw_raw_write(int fd, char *remoteipaddress, char *data, int length)
{
    struct sockaddr_in cli_addr, serv_addr;
    int ret;

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(remoteipaddress);

    ret = sendto(fd, data, length, 0, (struct sockaddr *)&serv_addr, sizeof(cli_addr));
    if (ret < 0)
    {
        perror("fw_raw_write:sendto");
        return 0;
    }
    return ret;
}

int fw_raw_write6(int fd, char *remoteipaddress, char *data, int length)
{
    struct sockaddr_in6 cli_addr, serv_addr;
    int ret;
    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, remoteipaddress, &serv_addr.sin6_addr);

    ret = sendto(fd, data, length, 0, (struct sockaddr *)&serv_addr, sizeof(cli_addr));
    if (ret < 0)
    {
        perror("fw_raw_write6:sendto");
        return 0;
    }
    return ret;
}

int fw_write6_ext(int fd, char *buffer, unsigned int tos, char *remoteipaddress, unsigned short remotePort, int payload_length)
{
    int n;
#if 0
    struct in6_pktinfo  *pIpPktInfo = NULL;
#endif
    struct sockaddr_in6 serv_addr;
    struct iovec Iov;
    struct cmsghdr *pCmsgInfo = NULL;
    char au1Cmsg[CMSG_SPACE(CMSG_LEN(sizeof(int))) + CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo)))];
    struct msghdr PktInfo;

    memset(&PktInfo, 0, sizeof(struct msghdr));
    memset(&Iov, 0, sizeof(Iov));

    memset((char *)&serv_addr, '\0', sizeof(serv_addr));
    /*    serv_addr.sin6_family = AF_INET6;*/

    memcpy(serv_addr.sin6_addr.s6_addr, remoteipaddress, 16);
    /*    inet_pton(AF_INET6, remoteipaddress, &serv_addr.sin6_addr);*/
    serv_addr.sin6_port = remotePort;

    memset(au1Cmsg, 0, CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo))) + CMSG_SPACE(CMSG_LEN(sizeof(int))));
    PktInfo.msg_name = (void *)&serv_addr;
    PktInfo.msg_namelen = sizeof(struct sockaddr_in6);
    Iov.iov_base = buffer;
    Iov.iov_len = payload_length;
    PktInfo.msg_iov = &Iov;
    PktInfo.msg_iovlen = 1;
    PktInfo.msg_control = (void *)au1Cmsg;
    PktInfo.msg_controllen = CMSG_SPACE(CMSG_LEN(sizeof(int))) + CMSG_SPACE(CMSG_LEN(sizeof(struct in6_pktinfo)));

    pCmsgInfo = CMSG_FIRSTHDR(&PktInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IPV6;
    pCmsgInfo->cmsg_type = IPV6_PKTINFO;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));
#if 0
    pIpPktInfo = (struct in6_pktinfo *)CMSG_DATA(pCmsgInfo);
    memset(pIpPktInfo,0,sizeof(pIpPktInfo));
#endif
    pCmsgInfo = CMSG_NXTHDR(&PktInfo, pCmsgInfo);
    pCmsgInfo->cmsg_level = IPPROTO_IPV6;
    pCmsgInfo->cmsg_type = IPV6_TCLASS;
    pCmsgInfo->cmsg_len = CMSG_LEN(sizeof(int));
    unsigned int *temp = (unsigned int *)CMSG_DATA(pCmsgInfo);
    *temp = tos;
    n = sendmsg(fd, &PktInfo, 0);

    return n;
}
#endif

/** Pool **/
unsigned long long fw_single_buffer_pool_init(fw_single_buffer_pool_t *p, unsigned long long element_size, unsigned long long num_elements)
{
    unsigned char *scan;
    unsigned long long i;
    unsigned long long size = 0;
    unsigned long long total_size = 0;
    unsigned long long pad = 0;

    if (element_size % 8)
    {
        pad = 0;
    }
    else
    {
        pad = 8 - (element_size % 8);
    }

    size = (sizeof(fw_single_buffer_t) + element_size + pad);
    total_size = size * num_elements;

    scan = (unsigned char *)malloc(total_size);
    lstInit(&p->L);
    for (i = 0; i < num_elements; i++)
    {
        lstAdd(&p->L, (NODE *)scan);
        scan += size;
    }
    return total_size;
}

void *fw_single_buffer_alloc(fw_single_buffer_pool_t *p)
{
    NODE *c;
    fw_single_buffer_t *b;
    if (lstCount(&p->L) == 0)
    {
        return NULL;
    }
    c = lstFirst(&p->L);
    b = (fw_single_buffer_t *)c;
    lstDelete(&p->L, c);
    return (void *)b->data;
}

void fw_single_buffer_free(fw_single_buffer_pool_t *p, void *buf)
{
    NODE *n;

    n = (NODE *)((unsigned long long)buf - offsetof(fw_single_buffer_t, data));
    lstAdd(&p->L, n);

    return;
}

/** Hash **/

unsigned long long fw_hash_n(void *data, unsigned long long n_bytes)
{
    unsigned long long i;
    unsigned long long total = 0;
    unsigned char *scan = (unsigned char *)data;

    for (i = 0; i < n_bytes; i++)
    {
        total = total * 31 + scan[i];
    }
    return total;
}

int fw_hash_init(fw_hash_t *h, unsigned long long num_elements, unsigned long long num_buckets, unsigned long long key_size, unsigned long long value_size)
{
    unsigned long long i;

    h->num_elements = num_elements;
    h->num_buckets = num_buckets;
    h->key_size = key_size;
    h->value_size = value_size;
    h->current_elements = 0;
    h->mem_hash_nodes = fw_single_buffer_pool_init(&h->p_hash_nodes, sizeof(fw_hash_node_t) + key_size + value_size, num_elements);
    h->p_hash_bucket = (fw_hash_bucket_t *)malloc(sizeof(fw_hash_bucket_t) * num_buckets);
    h->mem_hash_buckets = sizeof(fw_hash_bucket_t) * num_buckets;
    for (i = 0; i < num_buckets; i++)
    {
        lstInit(&h->p_hash_bucket[i].L);
    }
    return 0;
}

int fw_hash_add(fw_hash_t *h, void *key, void *val)
{
    unsigned long long hash;
    unsigned long long bucket;
    fw_hash_node_t *node;
    unsigned char *key_val;

    if (h->current_elements == h->num_elements)
        return -1;

    hash = fw_hash_n(key, h->key_size);
    bucket = hash % h->num_buckets;
    node = (fw_hash_node_t *)fw_single_buffer_alloc(&h->p_hash_nodes);
    if (node == NULL)
        return -1;

    key_val = node->data;
    memcpy(key_val, key, h->key_size);
    memcpy(key_val + h->key_size, val, h->value_size);

    lstAdd(&h->p_hash_bucket[bucket].L, (NODE *)node);
    h->current_elements++;

    return 0;
}

int fw_hash_del(fw_hash_t *h, void *key)
{
    unsigned long long hash;
    unsigned long long bucket;
    fw_hash_node_t *node;
    unsigned char *key_value_scan;
    ;
    NODE *scan;

    hash = fw_hash_n(key, h->key_size);
    bucket = hash % h->num_buckets;

    scan = lstFirst(&h->p_hash_bucket[bucket].L);
    while (scan != NULL)
    {
        node = (fw_hash_node_t *)scan;
        scan = lstNext(scan);
        key_value_scan = (unsigned char *)node->data;
        if (memcmp(key, key_value_scan, h->key_size) != 0)
        {
            continue;
        }
        lstDelete(&h->p_hash_bucket[bucket].L, (NODE *)node);
        fw_single_buffer_free(&h->p_hash_nodes, (void *)node);
        h->current_elements--;
        return 0;
    }
    return -1;
}

int fw_hash_search(fw_hash_t *h, void *key, void *val)
{
    unsigned long long hash;
    unsigned long long bucket;
    fw_hash_node_t *node;
    unsigned char *key_value_scan;
    ;
    NODE *scan;

    hash = fw_hash_n(key, h->key_size);
    bucket = hash % h->num_buckets;

    scan = lstFirst(&h->p_hash_bucket[bucket].L);
    while (scan != NULL)
    {
        node = (fw_hash_node_t *)scan;
        scan = lstNext(scan);
        key_value_scan = node->data;
        if (memcmp(key, key_value_scan, h->key_size) != 0)
        {
            continue;
        }
        memcpy(val, key_value_scan + h->key_size, h->value_size);
        return 0;
    }
    return -1;
}

void fw_hash_walk(fw_hash_t *h, fw_hash_walk_callback_t cb, void *arg)
{
    unsigned long long i;
    NODE *scan;
    fw_hash_node_t *node;
    unsigned char *key_value_scan;
    for (i = 0; i < h->num_buckets; i++)
    {
        scan = lstFirst(&h->p_hash_bucket[i].L);
        while (scan != NULL)
        {
            node = (fw_hash_node_t *)scan;
            key_value_scan = (unsigned char *)node->data;
            cb((void *)key_value_scan, (void *)(key_value_scan + h->key_size), arg);
            scan = lstNext(scan);
        }
    }
    return;
}

void fw_hash_debug_print(fw_hash_t *h)
{

    fprintf(stdout, "max_num_elements %llu", h->num_elements);
    fprintf(stdout, "current_elements %llu", h->current_elements);
    fprintf(stdout, "num_buckets %llu", h->num_buckets);
    fprintf(stdout, "key_size %llu", h->key_size);
    fprintf(stdout, "value_size %llu", h->value_size);
    fprintf(stdout, "mem_hash_nodes %llu", h->mem_hash_nodes);
    fprintf(stdout, "mem_hash_buckets %llu", h->mem_hash_buckets);
}

void fw_hash_bucket_print(fw_hash_t *h)
{
    unsigned long long i;

    for (i = 0; i < h->num_buckets; i++)
    {
        fprintf(stdout, "bucket[%llu]: %d\n", i, lstCount(&h->p_hash_bucket[i].L));
    }
}

void rfcstring2hex(char *string, unsigned char *buffer, int allowedlength, int *loadedlength)
{
    int i;
    char temp[1024];
    char *scan;
    int lengthstring;
    int count = 0;

    trim(string);

    scan = string;

    if (*scan != '0')
    {
        fprintf(stderr, "improper rfc string format, must begin with 0x\n");
        exit(1);
    }
    scan++;
    if ((*scan != 'x') && (*scan != 'X'))
    {
        fprintf(stderr, "improper rfc string format, must begin with 0x\n");
        exit(1);
    }
    scan++;
    lengthstring = strlen(scan);
    if (lengthstring % 2)
    {
        fprintf(stderr, "improper rfc string format, must have even number of digits\n");
        exit(1);
    }
    for (i = 0; i < lengthstring; i += 2)
    {
        temp[0] = '0';
        temp[1] = 'x';
        temp[2] = scan[i];
        temp[3] = scan[i + 1];
        temp[4] = '\0';
        if (count == allowedlength)
        {
            fprintf(stderr, "buffer not big enough to hold rfc string\n");
            exit(1);
        }
        buffer[count] = strtoul(temp, NULL, 0);
        count++;
    }
    *loadedlength = count;
}

/***********************/
/***** Timer Wheel *****/
/***********************/
fw_timer_wheel_t *fw_timer_wheel_init(unsigned long long interval_us, unsigned long long spokes, unsigned long long horizon_multiplier)
{
    unsigned long long i;
    unsigned long long current_time;

    fw_timer_wheel_t *wheel;
    wheel = (fw_timer_wheel_t *)malloc(sizeof(fw_timer_wheel_t));
    if (wheel == NULL)
    {
        fprintf(stderr, "panic: failed to allocate timer wheel\n");
        exit(1);
    }

    wheel->interval_us = interval_us;
    wheel->spokes = spokes;
    wheel->current_spoke = 0;
    wheel->pLists = (DLIST *)malloc(spokes * sizeof(DLIST));
    wheel->horizon_multiplier = horizon_multiplier;
    if (wheel->pLists == NULL)
    {
        fprintf(stderr, "panic: could not allocate memory for wheel lists\n");
        exit(1);
    }
    for (i = 0; i < spokes; i++)
    {
        lstInit(&wheel->pLists[i]);
    }
    lstInit(&wheel->nowList);
    current_time = getEpochUs();
    wheel->last_rotation_epoch_us = current_time;
    wheel->inside_callback = current_time;
    wheel->inside_callback = 0;
    fw_timer_wheel_lock_init(wheel);
    return wheel;
}

void fw_timer_wheel_lock_init(fw_timer_wheel_t *wheel)
{
    pthread_mutex_init(&wheel->lock, NULL);
}

void fw_timer_wheel_lock_deinit(fw_timer_wheel_t *wheel)
{
    pthread_mutex_destroy(&wheel->lock);
}

void fw_timer_wheel_lock(fw_timer_wheel_t *wheel)
{
    if (wheel->inside_callback)
        return;
    pthread_mutex_lock(&wheel->lock);
}

void fw_timer_wheel_unlock(fw_timer_wheel_t *wheel)
{
    if (wheel->inside_callback)
        return;
    pthread_mutex_unlock(&wheel->lock);
}

/** to expire the timers with immediate effect **/
void *fw_timer_wheel_timer_head_start(fw_timer_wheel_t *wheel, void *cdata, fw_timer_wheel_callback_t cb)
{
    fw_timer_wheel_spoke_payload_t *sp;

    sp = (fw_timer_wheel_spoke_payload_t *)malloc(sizeof(fw_timer_wheel_spoke_payload_t));
    if (sp == NULL)
    {
        fprintf(stderr, "panic: could not allocate spoke payload\n");
        exit(1);
    }
    sp->cdata = cdata;
    sp->cb = cb;
    sp->rotation_count = 1;
    sp->spoke = INVALID_SPOKE;

    fw_timer_wheel_lock(wheel);

    lstAdd(&wheel->nowList, (NODE *)sp);

    fw_timer_wheel_unlock(wheel);

    return sp;
}

void *fw_timer_wheel_timer_start(fw_timer_wheel_t *wheel, unsigned long long value_us, void *cdata, fw_timer_wheel_callback_t cb)
{
    unsigned long long spoke;
    unsigned long long spoke_offset;
    unsigned long long distance_to_horizon;
    fw_timer_wheel_spoke_payload_t *sp;
    unsigned long long rotation_count;
    unsigned long long actual_spokes;
    unsigned long long current_time;

    if (value_us < wheel->interval_us)
    {
        value_us = wheel->interval_us;
    }

    current_time = getEpochUs();

    fw_timer_wheel_lock(wheel);

    actual_spokes = (value_us + (current_time - wheel->last_rotation_epoch_us)) / wheel->interval_us;

    /** we must push the spoke_offset further by difference between now and the last rotation time **/
    /** this is because the user wishes to start the timer always from 'now' into the future **/
    spoke_offset = actual_spokes % wheel->spokes;

    rotation_count = (actual_spokes / wheel->spokes) + 1;
    if (rotation_count > wheel->horizon_multiplier)
    {
        fw_timer_wheel_unlock(wheel);
        return NULL;
    }

    distance_to_horizon = wheel->spokes - wheel->current_spoke;
    if (spoke_offset < distance_to_horizon)
    {
        spoke = wheel->current_spoke + spoke_offset;
    }
    else
    {
        spoke = spoke_offset - distance_to_horizon;
    }
    sp = (fw_timer_wheel_spoke_payload_t *)malloc(sizeof(fw_timer_wheel_spoke_payload_t));
    if (sp == NULL)
    {
        fprintf(stderr, "panic: could not allocate spoke payload\n");
        exit(1);
    }
    sp->cdata = cdata;
    sp->cb = cb;
    sp->spoke = spoke;
    sp->rotation_count = rotation_count;
    lstAdd(&wheel->pLists[spoke], (NODE *)sp);

    fw_timer_wheel_unlock(wheel);

    return sp;
}

void fw_timer_wheel_timer_stop(fw_timer_wheel_t *wheel, void *timerid)
{
    fw_timer_wheel_spoke_payload_t *sp;

    fw_timer_wheel_lock(wheel);

    sp = (fw_timer_wheel_spoke_payload_t *)timerid;
    if (INVALID_SPOKE == sp->spoke)
    {
        lstDelete(&wheel->nowList, (NODE *)timerid);
    }
    else
    {
        lstDelete(&wheel->pLists[sp->spoke], (NODE *)timerid);
    }

    fw_timer_wheel_unlock(wheel);

    free(timerid);
}

unsigned long long fw_timer_wheel_rotate2(fw_timer_wheel_t *wheel, fw_timer_wheel_expired_timer_t **timerData, unsigned long long max_expirations)
{
    unsigned long long num_spokes;
    unsigned long long i;
    fw_timer_wheel_spoke_payload_t *sp;
    NODE *node;
    NODE *todelete;
    fw_timer_wheel_expired_timer_t *timer = NULL;
    unsigned long long count = 0;
    unsigned long long memcount = 1;
    unsigned long long current_time;

    current_time = getEpochUs();

    fw_timer_wheel_lock(wheel);

    num_spokes = (current_time - wheel->last_rotation_epoch_us) / wheel->interval_us;
    if (num_spokes > (wheel->spokes * wheel->horizon_multiplier))
    {
        num_spokes = (wheel->spokes * wheel->horizon_multiplier);
    }

    if (num_spokes)
    {
        wheel->last_rotation_epoch_us = current_time;
    }
    node = lstFirst(&wheel->nowList);
    while (NULL != node)
    {
        todelete = node;
        sp = (fw_timer_wheel_spoke_payload_t *)node;
        node = lstNext(node);
        if (0 == (count % FW_TIMER_WHEEL_MEMORY_ALLOC_COUNT))
        {
            timer = (fw_timer_wheel_expired_timer_t *)realloc(timer, FW_TIMER_WHEEL_MEMORY_ALLOC_COUNT * memcount * sizeof(fw_timer_wheel_expired_timer_t));
            memcount++;
        }
        if (NULL == timer)
        {
            fprintf(stderr, "Error in allocating memory\n");
            fw_timer_wheel_unlock(wheel);
            return 0;
        }
        timer[count].cdata = sp->cdata;
        timer[count].timerId = (void *)sp;
        lstDelete(&wheel->nowList, todelete);
        count++;
        if (0 != max_expirations)
        {
            if (count == max_expirations)
            {
                break;
            }
        }
    }
    i = wheel->current_spoke;
    while (num_spokes)
    {
        node = lstFirst(&wheel->pLists[i]);
        while (node != NULL)
        {
            todelete = node;
            sp = (fw_timer_wheel_spoke_payload_t *)node;
            node = lstNext(node);
            if (0 != max_expirations)
            {
                if (count == max_expirations)
                {
                    sp->rotation_count--;
                    if (0 == sp->rotation_count)
                    {
                        sp->spoke = INVALID_SPOKE;
                        lstDelete(&wheel->pLists[i], todelete);
                        lstAdd(&wheel->nowList, todelete);
                    }
                    continue;
                }
            }
            if (0 == (count % FW_TIMER_WHEEL_MEMORY_ALLOC_COUNT))
            {
                timer = (fw_timer_wheel_expired_timer_t *)realloc(timer, FW_TIMER_WHEEL_MEMORY_ALLOC_COUNT * memcount * sizeof(fw_timer_wheel_expired_timer_t));
                memcount++;
            }
            if (NULL == timer)
            {
                fprintf(stderr, "Error in allocating memory\n");
                fw_timer_wheel_unlock(wheel);
                return 0;
            }
            sp->rotation_count--;
            if (0 == sp->rotation_count)
            {
                (timer[count]).cdata = sp->cdata;
                (timer[count]).timerId = (void *)sp;
                lstDelete(&wheel->pLists[i], todelete);
                count++;
            }
        }
        num_spokes--;
        wheel->current_spoke++;
        if (wheel->current_spoke >= wheel->spokes)
        {
            wheel->current_spoke = 0;
        }
        i++;
        if (i >= wheel->spokes)
        {
            i = 0;
        }
    }
    *timerData = timer;

    fw_timer_wheel_unlock(wheel);

    return count;
}

void fw_free_timer_id_data(fw_timer_wheel_expired_timer_t *timerData, unsigned long long count)
{
    unsigned long long i;
    for (i = 0; i < count; i++)
    {
        free(timerData[i].timerId);
    }
    if (count)
    {
        free(timerData);
    }
}

void fw_timer_wheel_readjust_expiry_list(DLIST *L, NODE *target_node)
{
    NODE *node;
    fw_timer_wheel_spoke_payload_t *sp;

    node = lstFirst(L);
    while (node != NULL)
    {
        if (node == target_node)
            break;
        sp = (fw_timer_wheel_spoke_payload_t *)node;
        sp->rotation_count++;
        node = lstNext(node);
    }
}

void fw_timer_wheel_rotate(fw_timer_wheel_t *wheel)
{
    unsigned long long num_spokes;
    unsigned long long i;
    fw_timer_wheel_spoke_payload_t *sp;
    NODE *node;
    NODE *todelete;
    fw_timer_wheel_expired_timer_t timerData;
    unsigned long long current_time;

    current_time = getEpochUs();

    fw_timer_wheel_lock(wheel);

    num_spokes = (current_time - wheel->last_rotation_epoch_us) / wheel->interval_us;
    if (num_spokes > (wheel->spokes * wheel->horizon_multiplier))
    {
        num_spokes = (wheel->spokes * wheel->horizon_multiplier);
    }

    if (num_spokes)
    {
        wheel->last_rotation_epoch_us = current_time;
    }

    node = lstFirst(&wheel->nowList);
    while (NULL != node)
    {
        /* Traverse the 'Now' List node first */
        todelete = node;
        sp = (fw_timer_wheel_spoke_payload_t *)node;
        timerData.cdata = sp->cdata;
        timerData.timerId = (void *)sp;
        wheel->inside_callback = 1;
        sp->cb(&timerData);
        wheel->inside_callback = 0;
        lstDelete(&wheel->nowList, todelete);
        free(todelete);
        node = lstFirst(&wheel->nowList);
    }
    i = wheel->current_spoke;
    while (num_spokes)
    {
        node = lstFirst(&wheel->pLists[i]);
        while (node != NULL)
        {
            todelete = node;
            sp = (fw_timer_wheel_spoke_payload_t *)node;
            sp->rotation_count--;
            if (0 == sp->rotation_count)
            {
                timerData.cdata = sp->cdata;
                timerData.timerId = (void *)sp;
                wheel->inside_callback = 1;
                sp->cb(&timerData);
                wheel->inside_callback = 0;
                fw_timer_wheel_readjust_expiry_list(&wheel->pLists[i], node);
                lstDelete(&wheel->pLists[i], todelete);
                free(todelete);
                node = lstFirst(&wheel->pLists[i]);
            }
            else
            {
                node = lstNext(node);
            }
        }
        num_spokes--;
        wheel->current_spoke++;
        if (wheel->current_spoke >= wheel->spokes)
        {
            wheel->current_spoke = 0;
        }
        i++;
        if (i >= wheel->spokes)
        {
            i = 0;
        }
    }

    fw_timer_wheel_unlock(wheel);
}

void fw_timer_wheel_rotate_to_update_now_list(fw_timer_wheel_t *wheel)
{
    unsigned long long num_spokes;
    unsigned long long i;
    fw_timer_wheel_spoke_payload_t *sp;
    NODE *node;
    NODE *todelete;
    unsigned long long current_time;

    current_time = getEpochUs();

    fw_timer_wheel_lock(wheel);

    num_spokes = (current_time - wheel->last_rotation_epoch_us) / wheel->interval_us;
    if (num_spokes > (wheel->spokes * wheel->horizon_multiplier))
    {
        num_spokes = (wheel->spokes * wheel->horizon_multiplier);
    }

    if (num_spokes)
    {
        wheel->last_rotation_epoch_us = current_time;
    }
    i = wheel->current_spoke;
    while (num_spokes)
    {
        node = lstFirst(&wheel->pLists[i]);
        while (node != NULL)
        {
            todelete = node;
            sp = (fw_timer_wheel_spoke_payload_t *)node;
            node = lstNext(node);
            sp->rotation_count--;
            if (0 == sp->rotation_count)
            {
                sp->spoke = INVALID_SPOKE;
                lstDelete(&wheel->pLists[i], todelete);
                lstAdd(&wheel->nowList, todelete);
            }
        }
        num_spokes--;
        wheel->current_spoke++;
        if (wheel->current_spoke >= wheel->spokes)
        {
            wheel->current_spoke = 0;
        }
        i++;
        if (i >= wheel->spokes)
        {
            i = 0;
        }
    }

    fw_timer_wheel_unlock(wheel);
}

void fw_timer_wheel_destroy(fw_timer_wheel_t *wheel)
{
    unsigned long long i;

    for (i = 0; i < wheel->spokes; i++)
    {
        lstFree(&wheel->pLists[i]);
    }

    fw_timer_wheel_lock_deinit(wheel);

    free(wheel);
}

/** Pool implementation **/
int fw_indexed_pool_init(fw_indexed_pool_t *p, unsigned long long payload_size, unsigned long long n_elements, char *name)
{
    unsigned long long total_size;
    unsigned long long i;

    if (n_elements == 0)
    {
        fprintf(stderr, "pool cannot be made with zero elements\n");
        return -1;
    }

    if (payload_size % 8)
    {
        payload_size += (8 - (payload_size % 8));
    }

    total_size = sizeof(fw_indexed_pool_element_t) + payload_size;
    p->mem_base = (void *)malloc(total_size * n_elements);
    if (p->mem_base == NULL)
    {
        fprintf(stderr, "could not allocate memory for pool\n");
        return -1;
    }
    strcpy(p->name, name);
    p->current_head = 0;
    p->current_tail = n_elements - 1;
    p->element_size = total_size;
    p->n_elements = n_elements;

    fw_indexed_pool_element_t *e;
    for (i = 0; i < n_elements; i++)
    {
        e = p->mem_base + i * p->element_size;
        e->self_index = i;
        if (i == (n_elements - 1))
        {
            e->next = ~0;
        }
        else
        {
            e->next = i + 1;
        }

        if (i == 0)
        {
            e->prev = ~0;
        }
        else
        {
            e->prev = i - 1;
        }
        e->allocated_flag = 0;
    }

    return 0;
}

void *fw_indexed_pool_alloc(fw_indexed_pool_t *p)
{
    if (p->current_head == ~0)
    {
        return NULL;
    }

    fw_indexed_pool_element_t *e;
    fw_indexed_pool_element_t *e_next;

    e = p->mem_base + p->current_head * p->element_size;
    e->allocated_flag = 1;
    p->n_allocated_elements++;

    if (e->next == ~0)
    {
        p->current_head = ~0;
        p->current_tail = ~0;
        return e->data;
    }
    e_next = p->mem_base + e->next * p->element_size;
    e_next->prev = ~0;
    p->current_head = e->next;

    return e->data;
}

unsigned long long fw_indexed_pool_max_elements(fw_indexed_pool_t *p)
{
    return p->n_elements;
}

unsigned long long fw_indexed_pool_allocated_elements(fw_indexed_pool_t *p)
{
    return p->n_allocated_elements;
}

void fw_indexed_pool_free_head(fw_indexed_pool_t *p, void *element)
{
    fw_indexed_pool_element_t *e;
    fw_indexed_pool_element_t *e_old_head;

    e = element - offsetof(fw_indexed_pool_element_t, data);

    if (p->current_head == ~0)
    {
        p->current_head = e->self_index;
        p->current_tail = e->self_index;
        e->next = ~0;
        e->prev = ~0;
        e->allocated_flag = 0;
        p->n_allocated_elements--;
        return;
    }

    e_old_head = p->mem_base + p->current_head * p->element_size;
    e->allocated_flag = 0;
    p->n_allocated_elements--;
    e->prev = ~0;
    e->next = p->current_head;
    e_old_head->prev = e->self_index;
    p->current_head = e->self_index;
}

void fw_indexed_pool_free_tail(fw_indexed_pool_t *p, void *element)
{
    fw_indexed_pool_element_t *e;
    fw_indexed_pool_element_t *e_old_tail;

    e = element - offsetof(fw_indexed_pool_element_t, data);

    if (p->current_tail == ~0)
    {
        p->current_head = e->self_index;
        p->current_tail = e->self_index;
        e->next = ~0;
        e->prev = ~0;
        e->allocated_flag = 0;
        p->n_allocated_elements--;
        return;
    }

    e_old_tail = p->mem_base + p->current_tail * p->element_size;
    e->allocated_flag = 0;
    p->n_allocated_elements--;
    e->next = ~0;
    e->prev = p->current_tail;
    e_old_tail->next = e->self_index;
    p->current_tail = e->self_index;
}

unsigned long long fw_indexed_pool_get_element_index(fw_indexed_pool_t *p, void *element)
{
    fw_indexed_pool_element_t *e;

    e = element - offsetof(fw_indexed_pool_element_t, data);
    return e->self_index;
}

void *fw_indexed_pool_get_element_at_index(fw_indexed_pool_t *p, unsigned long long index)
{
    if (index >= p->n_elements)
    {
        return NULL;
    }

    fw_indexed_pool_element_t *e;
    e = p->mem_base + index * p->element_size;
    return e->data;
}

unsigned char fw_indexed_pool_is_index_allocated(fw_indexed_pool_t *p, unsigned long long index)
{
    fw_indexed_pool_element_t *e;
    e = p->mem_base + index * p->element_size;
    if (index >= p->n_elements)
    {
        return 0;
    }
    return e->allocated_flag;
}

unsigned char fw_indexed_pool_is_element_part_of_pool(fw_indexed_pool_t *p, void *element)
{
    void *left = p->mem_base;
    void *right = left + p->element_size * p->n_elements;
    if (element < left)
        return 0;
    if (element > right)
        return 0;
    return 1;
}

unsigned char fw_indexed_pool_is_index_valid(fw_indexed_pool_t *p, unsigned long long index)
{
    if (index >= p->n_elements)
    {
        return 0;
    }
    return 1;
}

void fw_indexed_pool_destroy(fw_indexed_pool_t *p)
{
    free(p->mem_base);
}

void fw_indexed_pool_print(fw_indexed_pool_t *p)
{
    fw_indexed_pool_element_t *e;
    unsigned long long eindex;

    fprintf(stdout, "ch: %llu ct: %llu\n", p->current_head, p->current_tail);
    eindex = p->current_head;
    while (eindex != ~0)
    {
        e = p->mem_base + eindex * p->element_size;
        fprintf(stdout, "[%llu][%llu][%llu][%u]\n", e->self_index, e->next, e->prev, e->allocated_flag);
        eindex = e->next;
    }
    fprintf(stdout, "wall\n");
}

/** Stateless DB **/


void fw_boundary_process_collected_data(unsigned char *collected, unsigned int collected_size, fw_boundary_token_t *t)
{
    char *scan;

    scan = (char *)collected;
    collected[collected_size] = '\0';

    strcpy(t->content_type, "");
    strcpy(t->content_id, "");
    strcpy((char *)t->data, "");
    t->size = 0;
    scan = strstr(scan, "Content-Type: application/json");
    if (scan != NULL)
    {
        strcpy(t->content_type, "application/json");
        scan += strlen("Content-Type: application/json");
        scan = strstr(scan, "{");
        if (scan != NULL)
        {
            strcpy((char *)t->data, scan);
            t->size = strlen((char *)t->data);
            return;
        }
    }

    scan = (char *)collected;
    scan = strstr(scan, "Content-Type: application/vnd.3gpp.ngap");
    if (scan != NULL)
    {
        strcpy(t->content_type, "application/vnd.3gpp.ngap");
        scan += strlen("Content-Type: application/vnd.3gpp.ngap");
        scan = strstr(scan, "Content-Id: ");
        if (scan != NULL)
        {
            scan += strlen("Content-Id: ");
            int count = 0;
            while ((*scan != '\n') && (*scan != '\r'))
            {
                t->content_id[count] = *scan;
                scan++;
                count++;
            }
            t->content_id[count] = '\0';
            scan = strstr(scan, "{");
            if (scan != NULL)
            {
                scan++;
                unsigned char *start = (unsigned char *)scan;

                unsigned char *end = collected + collected_size;
                while (*end != '}')
                    end--;
                if (end > start)
                {
                    memcpy(t->data, start, end - start);
                    t->size = end - start;
                    return;
                }
            }
        }
    }
    scan = (char *)collected;
    scan = strstr(scan, "Content-Type: application/vnd.3gpp.5gnas");
    if (scan != NULL)
    {
        strcpy(t->content_type, "application/vnd.3gpp.5gnas");
        scan += strlen("Content-Type: application/vnd.3gpp.5gnas");
        scan = strstr(scan, "Content-Id: ");
        if (scan != NULL)
        {
            scan += strlen("Content-Id: ");
            int count = 0;
            while ((*scan != '\n') && (*scan != '\r'))
            {
                t->content_id[count] = *scan;
                scan++;
                count++;
            }
            t->content_id[count] = '\0';
            scan = strstr(scan, "{");
            if (scan != NULL)
            {
                scan++;
                unsigned char *start = (unsigned char *)scan;

                unsigned char *end = collected + collected_size;
                while (*end != '}')
                    end--;
                if (end > start)
                {
                    memcpy(t->data, start, end - start);
                    t->size = end - start;
                    return;
                }
            }
        }
    }
}

unsigned int fw_boundary_parse(void *input, unsigned int length_input, char *boundary, fw_boundary_token_t *t)
{
    unsigned char begin_boundary[256];
    unsigned char end_boundary[256];
    unsigned char collected[65536];
    unsigned int collected_size;
    unsigned int num_collected;
    int begin_boundary_length;
    int end_boundary_length;

    unsigned int remaining_length = length_input;

    begin_boundary[0] = '-';
    begin_boundary[1] = '-';
    memcpy(&begin_boundary[2], boundary, strlen(boundary));
    begin_boundary_length = strlen(boundary) + 2;

    memcpy(end_boundary, begin_boundary, begin_boundary_length);
    end_boundary[begin_boundary_length] = '-';
    end_boundary[begin_boundary_length + 1] = '-';

    end_boundary_length = begin_boundary_length + 2;

    void *scan = input;
    int first_boundary = 1;

    collected_size = 0;
    num_collected = 0;

    while (remaining_length > end_boundary_length)
    {
        if (memcmp(scan, end_boundary, end_boundary_length) == 0)
        {
            if (!first_boundary)
            {
                fw_boundary_process_collected_data(collected, collected_size, &t[num_collected]);
                collected_size = 0;
                num_collected++;
            }
            break;
        }

        if (memcmp(scan, begin_boundary, begin_boundary_length) == 0)
        {
            scan += begin_boundary_length;
            remaining_length -= begin_boundary_length;

            if (first_boundary)
            {
                first_boundary = 0;
                continue;
            }

            fw_boundary_process_collected_data(collected, collected_size, &t[num_collected]);
            collected_size = 0;
            num_collected++;
            continue;
        }

        memcpy(&collected[collected_size], scan, 1);
        collected_size++;

        scan++;
        remaining_length--;
    }

    return num_collected;
}

/* Dont Add Any Function After this */
char *elog_end()
{
    char *end_local = "ELOG_END";
    return end_local;
}

/* Dont Add Any Function After this */
