#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

void amf_read_cfg()
{
    char rval[AMF_MAX_BUF_LEN];

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "MANAGEMENT_IP", rval);
    strcpy(g_amf_main.config.management_ip, rval);
    

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "MANAGEMENT_IP6", rval);
    strcpy(g_amf_main.config.management_ip6, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "ACCESS_IP", rval);
    strcpy(g_amf_main.config.access_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "ACCESS_IP6", rval);
    strcpy(g_amf_main.config.access_ip6, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "SERVING_NETWORK", rval);
    strcpy(g_amf_main.config.serving_network, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AUSF_API_ROOT", rval);
    strcpy(g_amf_main.config.ausf_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AUSF_IP", rval);
    strcpy(g_amf_main.config.ausf_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "AUSF_PORT", rval);
    g_amf_main.config.ausf_port = atoi(rval);


    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "UDM_API_ROOT", rval);
    strcpy(g_amf_main.config.udm_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "UDM_IP", rval);
    strcpy(g_amf_main.config.udm_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "UDM_PORT", rval);
    g_amf_main.config.udm_port = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "EIR_PRESENT", rval);
    g_amf_main.config.eir_present = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "EIR_API_ROOT", rval);
    strcpy(g_amf_main.config.eir_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "EIR_IP", rval);
    strcpy(g_amf_main.config.eir_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "EIR_PORT", rval);
    g_amf_main.config.eir_port = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "SMF_API_ROOT", rval);
    strcpy(g_amf_main.config.smf_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "SMF_IP", rval);
    strcpy(g_amf_main.config.smf_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "SMF_PORT", rval);
    g_amf_main.config.smf_port = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "PCF_PRESENT", rval);
    g_amf_main.config.pcf_present = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "PCF_API_ROOT", rval);
    strcpy(g_amf_main.config.pcf_api_root, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "PCF_IP", rval);
    strcpy(g_amf_main.config.pcf_ip, rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "PCF_PORT", rval);
    g_amf_main.config.pcf_port = atoi(rval);

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "ACCESS_PORT", rval);
    if(strcmp(rval, "") != 0)
    {
        g_amf_main.config.access_port = atoi(rval);
    }
    else
    {
        g_amf_main.config.access_port = AMF_ACCESS_PORT;
    }
}
int main()
{
    char rval[AMF_MAX_BUF_LEN];

    fileGetString(AMF_CFG_FILE, "AMF_CFG", '=', "MANAGEMENT_IP", rval);
    printf("%s\n", rval);
}