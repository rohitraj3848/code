#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

void *amf_malloc(int size)
{
    return malloc(size);
}

void amf_free(void *ptr)
{
    free(ptr);
}

typedef struct
{
    char* val;
}SupiOrSuci_t;

typedef struct
{
    char* val;
}ServingNetworkName_t;

typedef struct
{
    char* val;
}Rand_t;

typedef struct
{
    char* val;
}Auts_t;

typedef struct
{
    Rand_t* rand;
    Auts_t* auts;
}ResynchronizationInfo_t;


typedef struct
{
    char* val;
}Pei_t;

typedef struct
{
    char* val;
}Ipv4Addr_t;

typedef struct
{
    char* val;
}Ipv6Addr_t;


typedef struct
{
    char* val;
}TraceDepth_t;

typedef struct
{
    char* traceRef;
    TraceDepth_t* traceDepth;
    char* neTypeList;
    char* eventList;
    Ipv4Addr_t* collectionEntityIpv4Addr;
    Ipv6Addr_t* collectionEntityIpv6Addr;
    char* interfaceList;
}TraceData_t;

typedef struct
{
    char* val;
}NfGroupId_t;

typedef struct
{
    char* val;
}CagId_t;

typedef struct
{
    char* val;
}SupportedFeatures_t;


typedef struct
{
    SupiOrSuci_t* supiOrSuci;
    ServingNetworkName_t* servingNetworkName;
    ResynchronizationInfo_t* resynchronizationInfo;
    Pei_t* pei;
    TraceData_t* traceData;
    NfGroupId_t* udmGroupId;
    char* routingIndicator;
    int num_callCagInfo;
    CagId_t* cellCagInfo;
    unsigned char* n5gcInd;
    SupportedFeatures_t* supportedFeatures;
}AuthenticationInfo_t;

SupiOrSuci_t* amf_json_decode_SupiOrSuci_t(json_t* obj, SupiOrSuci_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(SupiOrSuci_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(SupiOrSuci_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

ServingNetworkName_t* amf_json_decode_ServingNetworkName_t(json_t* obj, ServingNetworkName_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(ServingNetworkName_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(ServingNetworkName_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

Rand_t* amf_json_decode_Rand_t(json_t* obj, Rand_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(Rand_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(Rand_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

Auts_t* amf_json_decode_Auts_t(json_t* obj, Auts_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(Auts_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(Auts_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

ResynchronizationInfo_t* amf_json_decode_ResynchronizationInfo_t(json_t* obj, ResynchronizationInfo_t* p)
{
    const char* key;
    json_t* value;

    if(p == NULL)
    {
        p = amf_malloc(sizeof(ResynchronizationInfo_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(ResynchronizationInfo_t));
    }

    json_object_foreach(obj, key, value)
    {
        if(strcmp(key, "rand") == 0)
        {
            p->rand = amf_json_decode_Rand_t(value, p->rand);
        }
        if(strcmp(key, "auts") == 0)
        {
            p->auts = amf_json_decode_Auts_t(value, p->auts);
        }
    }

    return p;
}

Pei_t* amf_json_decode_Pei_t(json_t* obj, Pei_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(Pei_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(Pei_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

TraceDepth_t* amf_json_decode_TraceDepth_t(json_t* obj, TraceDepth_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(TraceDepth_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(TraceDepth_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

Ipv4Addr_t* amf_json_decode_Ipv4Addr_t(json_t* obj, Ipv4Addr_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(Ipv4Addr_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(Ipv4Addr_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

Ipv6Addr_t* amf_json_decode_Ipv6Addr_t(json_t* obj, Ipv6Addr_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(Ipv6Addr_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(Ipv6Addr_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}


TraceData_t* amf_json_decode_TraceData_t(json_t* obj, TraceData_t* p)
{
    const char* key;
    json_t* value;

    if(p == NULL)
    {
        p = amf_malloc(sizeof(TraceData_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(TraceData_t));
    }

    json_object_foreach(obj, key, value)
    {
        if(strcmp(key, "traceRef") == 0)
        {
            size_t len = json_string_length(value);
            if(len)
            {
                p->traceRef = amf_malloc(len+1);
                strcpy(p->traceRef, json_string_value(value));
            }
        }
        if(strcmp(key, "traceDepth") == 0)
        {
            p->traceDepth = amf_json_decode_TraceDepth_t(value, p->traceDepth);
        }
        if(strcmp(key, "neTypeList") == 0)
        {
            size_t len = json_string_length(value);
            if(len)
            {
                p->neTypeList = amf_malloc(len+1);
                strcpy(p->neTypeList, json_string_value(value));
            }
        }
        if(strcmp(key, "eventList") == 0)
        {
            size_t len = json_string_length(value);
            if(len)
            {
                p->eventList = amf_malloc(len+1);
                strcpy(p->eventList, json_string_value(value));
            }
        }
        if(strcmp(key, "collectionEntityIpv4Addr") == 0)
        {
            p->collectionEntityIpv4Addr = amf_json_decode_Ipv4Addr_t(value, p->collectionEntityIpv4Addr);
        }
        if(strcmp(key, "collectionEntityIpv6Addr") == 0)
        {
            p->collectionEntityIpv6Addr = amf_json_decode_Ipv6Addr_t(value, p->collectionEntityIpv6Addr);
        }
        if(strcmp(key, "interfaceList") == 0)
        {
            size_t len = json_string_length(value);
            if(len)
            {
                p->interfaceList = amf_malloc(len+1);
                strcpy(p->interfaceList, json_string_value(value));
            }
        }
    }

    return p;
}

NfGroupId_t* amf_json_decode_NfGroupId_t(json_t* obj, NfGroupId_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(NfGroupId_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(NfGroupId_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

CagId_t* amf_json_decode_CagId_t(json_t* obj, CagId_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(CagId_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(CagId_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        fprintf(stdout,"%s\n",json_string_value(obj));
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}

SupportedFeatures_t* amf_json_decode_SupportedFeatures_t(json_t* obj, SupportedFeatures_t* p)
{
    if(p == NULL)
    {
        p = amf_malloc(sizeof(SupportedFeatures_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(SupportedFeatures_t));
    }
    size_t len = json_string_length(obj);
    if(len)
    {
        p->val = amf_malloc(len+1);
        strcpy(p->val, json_string_value(obj));
    }
    return p;
}
AuthenticationInfo_t *amf_json_decode_AuthenticationInfo_t(json_t *obj, AuthenticationInfo_t *p)
{
    const char *key;
    json_t *value;

    if (p == NULL)
    {
        p = amf_malloc(sizeof(AuthenticationInfo_t));
        if (p == NULL)
        {
            if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        }
        memset(p, 0, sizeof(AuthenticationInfo_t));
    }

    json_object_foreach(obj, key, value)
    {
        if (strcmp(key, "supiOrSuci") == 0)
        {
            p->supiOrSuci = amf_json_decode_SupiOrSuci_t(value, p->supiOrSuci);
        }
        if (strcmp(key, "servingNetworkName") == 0)
        {
            p->servingNetworkName = amf_json_decode_ServingNetworkName_t(value, p->servingNetworkName);
        }
        if (strcmp(key, "resynchronizationInfo") == 0)
        {
            p->resynchronizationInfo = amf_json_decode_ResynchronizationInfo_t(value, p->resynchronizationInfo);
        }
        if (strcmp(key, "pei") == 0)
        {
            p->pei = amf_json_decode_Pei_t(value, p->pei);
        }
        if (strcmp(key, "traceData") == 0)
        {
            p->traceData = amf_json_decode_TraceData_t(value, p->traceData);
        }
        if (strcmp(key, "udmGroupId") == 0)
        {
            p->udmGroupId = amf_json_decode_NfGroupId_t(value, p->udmGroupId);
        }
        if (strcmp(key, "routingIndicator") == 0)
        {
            size_t len = json_string_length(value);
            if (len)
            {
                p->routingIndicator = amf_malloc(len + 1);
                strcpy(p->routingIndicator, json_string_value(value));
            }
        }
        if (strcmp(key, "cellCagInfo") == 0)
        {

            size_t len = json_array_size(value);
            int i;
            for(i=0;i<len;i++)
            {

                json_t* val = json_array_get(value,i);
                fprintf(stdout,"%s\n",json_string_value(val));

            }
            p->num_callCagInfo = len;
            if (len)
            {
                p->cellCagInfo = amf_malloc(len * sizeof(CagId_t));
                CagId_t *ignore;
                for (i = 0; i < len; i++)
                {
                    fprintf(stdout,"%s\n",json_string_value(value));
                    json_t* val = json_array_get(value,i);
                    ignore = amf_json_decode_CagId_t(val, &p->cellCagInfo[i]);
                    ignore = ignore;
                }
            }
        }
        if (strcmp(key, "n5gcInd") == 0)
        {
            p->n5gcInd = amf_malloc(1);
            if (p->n5gcInd == NULL)
            {
                if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
            }
            *p->n5gcInd = json_boolean_value(value);
        }
        if (strcmp(key, "supportedFeatures") == 0)
        {
            p->supportedFeatures = amf_json_decode_SupportedFeatures_t(value, p->supportedFeatures);
        }
    }

    return p;
}

json_t *server_load_json(const char *text)
{
    json_t *root;
    json_error_t error;
    root = json_loads(text, 0, &error);
    if (root)
    {
        return root;
    }
    else
    {
        fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
        return (json_t *)0;
    }
}

int main()
{
    FILE *fp;
    char buff[2048];

    fp = fopen("test.json", "r");
    fread(buff, 2048,1, fp);
    fclose(fp);

    AuthenticationInfo_t *p = NULL;
    json_t *root = NULL;
    root = server_load_json(buff);
    if (root == NULL)
    {
        fprintf(stderr, "failed to load json at %s %d\n", __FILE__, __LINE__);
    }
    p = amf_json_decode_AuthenticationInfo_t(root, p);
    
    amf_free(root);    
    if (p != NULL)
    {
        if (p->supiOrSuci->val != NULL)
        {
            fprintf(stdout, "supiOrSuci = %s\n", (char *)p->supiOrSuci->val);
        }
        if (p->servingNetworkName->val != NULL)
        {
            fprintf(stdout, "Serving Network Name = %s\n", p->servingNetworkName->val);
        }
        if (p->pei->val != NULL)
        {
            fprintf(stdout, "pei = %s\n", (char *)p->pei->val);
        }
        if (p->routingIndicator != NULL)
        {
            fprintf(stdout, "routingIndicator = %s\n", (char *)p->routingIndicator);
        }
        int i;
        fprintf(stdout, "num_cellCagId = %d\n", p->num_callCagInfo);
        for (i = 0; i < p->num_callCagInfo; i++)
        {
            fprintf(stdout, "cellCagInfo[%d] = %s\n", i, (char *)p->cellCagInfo[i].val);
        }
    }

   return 0;
}


//curl --http2-prior-knowledge -d '{"suci":"abc","authenticatedInd":true,"supportedFeatures":"for"}' -H "Content-Type: application/json" -X POST -k http://127.0.0.1:80/rg-authentications
