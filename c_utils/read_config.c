#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    int num_ia;
    char** ia;
    int num_ea;
    char** ea;
    unsigned char   amf_region_id;
    unsigned short  amf_set_id;
    unsigned char   amf_pointer;
    char   amf_instance_id[256];

    char   amf_api_root[256];
    char        amf_http_ip[128];
    unsigned short     amf_http_port;

}amf_config_t;

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


int fileGetString(char* filename, char* begintoken, char delim, char* lval, char* rval)
{
    FILE* fpt;
    char buffer[1024];
    char starttoken[1024];
    char locallval[1024];

    strcpy(rval, "");
    strcpy(buffer, "");
    strcpy(starttoken, "BEGIN_");
    strcat(starttoken, begintoken);

    fpt = fopen(filename, "r");
    if(fpt == NULL)
    {
        fprintf(stderr, "fw: fileGetString: could not open <%s> for reading\n", filename);
        return 0;
    }

    while(fgets(buffer, 1023, fpt) != NULL)
    {
        buffer[strlen(buffer)-1] = '\0';
        trim(buffer);
        if(buffer[0] == '#')
            continue;
        if(strcmp(buffer, "") == 0)
            continue;
        if(strcmp(starttoken, buffer) == 0)
        {
            while(fgets(buffer, 1023, fpt) != NULL)
            {
                buffer[strlen(buffer)-1] = '\0';
                trim(buffer);
                if(buffer[0] == '#')
                    continue;
                if(strcmp(buffer, "") == 0)
                    continue;
                if(strcmp(buffer, "END") == 0)
                {
                    fprintf(stderr, "fw: fwGetString: could not find lval: <%s> in block beginning with <%s> [Encountered END token !]\n",
                        lval, starttoken);
                    strcpy(rval, "");
                    fclose(fpt);
                    return 0;
                }
                strcpy(locallval, "");
                getLvalRval(buffer, delim, locallval, rval);
                if(strcmp(locallval, lval) == 0)
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


void amf_config_load_amf_ids()
{
    char rval[AMF_MAX_BUF_LEN];

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_REGION_ID", rval);
    g_amf_main.config.amf_region_id = strtoul(rval, NULL, 0);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_SET_ID", rval);
    g_amf_main.config.amf_set_id = strtoul(rval, NULL, 0);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_POINTER", rval);
    g_amf_main.config.amf_pointer = strtoul(rval, NULL, 0);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_INSTANCE_ID", rval);
    strcpy(g_amf_main.config.amf_instance_id, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_HTTP_IP", rval);
    strcpy(g_amf_main.config.amf_http_ip, rval);

}

void amf_config_load_ea()
{
        char rval[AMF_MAX_BUF_LEN];

    
        fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "EA", rval);
    if(strcmp(rval, "") == 0)
    {
        g_amf_main.config.ea = realloc(g_amf_main.config.ea, sizeof(char*)*(g_amf_main.config.num_ea+1));
        if(g_amf_main.config.ea == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        g_amf_main.config.ea[g_amf_main.config.num_ea] = malloc(16);
        if(g_amf_main.config.ea[g_amf_main.config.num_ea] == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        strcpy(g_amf_main.config.ea[g_amf_main.config.num_ea], "EA0");
        g_amf_main.config.num_ea += 1;
        return;
    }

    char* tok;
    tok = strtok(rval, ",");
    while(tok != NULL)
    {
        g_amf_main.config.ea = realloc(g_amf_main.config.ea, sizeof(char*)*(g_amf_main.config.num_ea+1));
        if(g_amf_main.config.ea == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        g_amf_main.config.ea[g_amf_main.config.num_ea] = malloc(16);
        if(g_amf_main.config.ea[g_amf_main.config.num_ea] == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        strcpy(g_amf_main.config.ea[g_amf_main.config.num_ea], tok);
        g_amf_main.config.num_ea += 1;
    }
}

void amf_config_load_ia()
{

        char rval[AMF_MAX_BUF_LEN];

    
        fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "IA", rval);
    if(strcmp(rval, "") == 0)
    {
        g_amf_main.config.ia = realloc(g_amf_main.config.ia, sizeof(char*)*(g_amf_main.config.num_ia+1));
        if(g_amf_main.config.ia == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        g_amf_main.config.ia[g_amf_main.config.num_ia] = malloc(16);
        if(g_amf_main.config.ia[g_amf_main.config.num_ia] == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        strcpy(g_amf_main.config.ia[g_amf_main.config.num_ia], "IA0");
        g_amf_main.config.num_ia += 1;
        return;
    }

    char* tok;
    tok = strtok(rval, ",");
    while(tok != NULL)
    {
        g_amf_main.config.ia = realloc(g_amf_main.config.ia, sizeof(char*)*(g_amf_main.config.num_ia+1));
        if(g_amf_main.config.ia == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        g_amf_main.config.ia[g_amf_main.config.num_ia] = malloc(16);
        if(g_amf_main.config.ia[g_amf_main.config.num_ia] == NULL)
        {
            fprintf(stderr, "panic: could not allocate memory at file: %s line: %d\n", __FILE__, __LINE__);
            exit(1);
        }
        strcpy(g_amf_main.config.ia[g_amf_main.config.num_ia], tok);
        g_amf_main.config.num_ia += 1;
    }
}

void amf_read_cfg()
{
    char rval[AMF_MAX_BUF_LEN];

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_API_ROOT", rval);
    strcpy(g_amf_main.config.amf_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_HTTP_IP", rval);
    strcpy(g_amf_main.config.amf_http_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AMF_HTTP_PORT", rval);
    g_amf_main.config.amf_http_port = atoi(rval);
    
}
int main()
{
    printf("%s\n", rval);
}