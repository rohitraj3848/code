#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define Ngap_RAN_UE_NGAP_ID_t unsigned long long
typedef struct OCTET_STRING {
        uint8_t *buf;   /* Buffer with consecutive OCTET_STRING bits */
        size_t size;    /* Size of the buffer */

} OCTET_STRING_t;

typedef struct BIT_STRING_s {
        uint8_t *buf;   /* BIT STRING body */
        size_t size;    /* Size of the above buffer */

        int bits_unused;/* Unused trailing bits in the last octet (0..7) */
} BIT_STRING_t;

typedef OCTET_STRING_t   Ngap_PLMNIdentity_t;
typedef BIT_STRING_t    Ngap_AMFRegionID_t;
typedef BIT_STRING_t    Ngap_AMFSetID_t;
typedef BIT_STRING_t    Ngap_AMFPointer_t;
typedef OCTET_STRING_t  Ngap_AMF_UE_NGAP_ID_t;
typedef BIT_STRING_t    Ngap_SecurityKey_t;
typedef BIT_STRING_t    ENC_ALGO_t;
typedef BIT_STRING_t    INT_ALGO_t;

typedef struct Ngap_GUAMI {
        Ngap_PLMNIdentity_t      pLMNIdentity;
        Ngap_AMFRegionID_t       aMFRegionID;
        Ngap_AMFSetID_t  aMFSetID;
        Ngap_AMFPointer_t        aMFPointer;
}Ngap_GUAMI_t;

typedef struct Ngap_UESecurityCapabilities {
        ENC_ALGO_t enc_algo;
        INT_ALGO_t int_algo;

}Ngap_UESecurityCapabilities_t;

typedef struct Ngap_InitialContextSetupRequestIEs {
        int     id;
        int       criticality;
        struct Ngap_InitialContextSetupRequestIEs__value {
                int present;
                union Ngap_InitialContextSetupRequestIEs__Ngap_value_u {
                        Ngap_AMF_UE_NGAP_ID_t    AMF_UE_NGAP_ID;
                        Ngap_RAN_UE_NGAP_ID_t    RAN_UE_NGAP_ID;
                        Ngap_GUAMI_t     GUAMI;
                        Ngap_UESecurityCapabilities_t    UESecurityCapabilities;
                        Ngap_SecurityKey_t       SecurityKey;
                        
                }choice;
        }value;
}Ngap_InitialContextSetupRequestIEs_t;

void print_guami(Ngap_InitialContextSetupRequestIEs_t* p_ics_ie)
{
        for(int i=0;i<p_ics_ie->value.choice.GUAMI.aMFPointer.size;i++)
        {
            printf("%d\n",p_ics_ie->value.choice.GUAMI.aMFPointer.buf[i]);  
        }
        
}
int main()
{
        /*p_ics_ie = malloc(sizeof(struct Ngap_InitialContextSetupRequestIEs));
        if(p_ics_ie == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        memset(p_ics_ie, 0, sizeof(struct Ngap_InitialContextSetupRequestIEs));
        p_ics_ie->id = 1;
        p_ics_ie->criticality = 2;
        p_ics_ie->value.present = 5;

        
        Ngap_AMF_UE_NGAP_ID_t* ngap_id = &p_ics_ie->value.choice.AMF_UE_NGAP_ID;
        memset(ngap_id, 0, sizeof(OCTET_STRING_t));

        ngap_id->buf = malloc(5*sizeof(char));
        if(ngap_id->buf == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        unsigned int id = 2345678;
        memcpy(ngap_id->buf, &id, 5);
        */
        struct Ngap_InitialContextSetupRequestIEs* p_ics_ie;

        p_ics_ie = malloc(sizeof(struct Ngap_InitialContextSetupRequestIEs));
        if(p_ics_ie == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        memset(p_ics_ie, 0, sizeof(struct Ngap_InitialContextSetupRequestIEs));
        Ngap_GUAMI_t* guami = &p_ics_ie->value.choice.GUAMI;
        if(guami == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        memset(guami, 0, sizeof(Ngap_GUAMI_t));

        OCTET_STRING_t* plmn_id = &guami->pLMNIdentity;
        memset(plmn_id, 0, sizeof(OCTET_STRING_t));
        plmn_id->buf = malloc(3);
        plmn_id->size = 3;
        if(plmn_id->buf == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        memset(plmn_id->buf, 0, 3);
        unsigned char buffer[] = "rohit";
        memcpy(plmn_id->buf, buffer,plmn_id->size);


        BIT_STRING_t* amf_region_id = &guami->aMFRegionID;
        memset(amf_region_id, 0, sizeof(BIT_STRING_t));
        amf_region_id->size = sizeof(unsigned char);
        amf_region_id->buf = malloc(sizeof(unsigned char));
        if(amf_region_id->buf == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        unsigned char id1 = 23;
        memcpy(amf_region_id->buf, (char*)&id1, amf_region_id->size);

        BIT_STRING_t* amf_set_id = &guami->aMFSetID;
        memset(amf_set_id, 0, sizeof(BIT_STRING_t));
        amf_set_id->size = sizeof(unsigned short);
        amf_set_id->buf = malloc(sizeof(unsigned short));
        if(amf_set_id->buf == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        unsigned short setid = 45;
        memcpy(amf_set_id->buf, (char*)&setid, amf_set_id->size);

        BIT_STRING_t* amf_pointer = &guami->aMFPointer;
        memset(amf_pointer, 0, sizeof(BIT_STRING_t));
        amf_pointer->size = sizeof(unsigned char);
        amf_pointer->buf = malloc(sizeof(unsigned char));
        if(amf_pointer->buf == NULL)
        {
                fprintf(stdout,"%s\n", "unable to allocate memory");
                exit(1);
        }
        unsigned char id2 = 89;
        memcpy(amf_pointer->buf, (char*)&id2, amf_pointer->size);
        
        print_guami(p_ics_ie);
        return 0;
}