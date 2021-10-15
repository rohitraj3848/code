
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
        unsigned char   ngKsi_type; //1
        unsigned char   ngKsi_value; // 1
        unsigned int    nas_count_ul_3gpp; //4
        unsigned int    nas_count_dl_3gpp; //4
        unsigned int    nas_count_ul_non3gpp; //4
        unsigned int    nas_count_dl_non3gpp; //4
        unsigned char   cipher_algo; //1
        unsigned short  cipher_key_length; //2
        unsigned char   cipher_key[16]; //16
        unsigned char   integrity_algo; //1
        unsigned short  integrity_key_length; //2
        unsigned char   integrity_key[16]; //16
}ue_nas_security_ctx_t; // 56

typedef struct
{
        int                     fd; //4  /** the file descriptor of SCTP connection **/
        unsigned char auth_type; //1

}ue_ctx_runtime_t; //5

typedef struct
{
        unsigned long ue_gnb_ngap_id;  //4

}gnb_ctx_t; //4

typedef struct
{
        unsigned char suci[32]; //32 
        unsigned int            state_3gpp;  //4
        unsigned int            state_non3gpp; //4
        ue_nas_security_ctx_t   current_sec_ctx; //56
        ue_nas_security_ctx_t   non_current_sec_ctx; //56
        ue_ctx_runtime_t        rt; //5

}ue_ctx_t; //

typedef struct
{
        ue_ctx_t ue_ctx; //157
        gnb_ctx_t gnb_ctx; // 4
}gnb_ue_ctx_t;


typedef struct 
{
        int a;
        int b;
        char c;
}data_t;

int main()
{
        gnb_ue_ctx_t* gnb_ue = malloc(sizeof(gnb_ue_ctx_t));
        int a = 4;
        char b = 3;
        if(gnb_ue == NULL)
        {
                printf("%s\n", "unable to allocate memory");
        }
        memset(gnb_ue, 0, sizeof(gnb_ue_ctx_t));

        gnb_ue_ctx_t gnb;
        memset(&gnb, 0, sizeof(gnb_ue_ctx_t));

        data_t data;
        memset(&data, 0, sizeof(data_t));

        printf("%ld\n", sizeof(b));
        printf("%ld\n", sizeof(char));
        printf("%ld\n", sizeof(a));
        printf("%ld\n", sizeof(int));
        printf("%ld\n", sizeof(*gnb_ue));
        printf("%ld\n", sizeof(gnb_ue_ctx_t));
        printf("%ld\n", sizeof(gnb));
        printf("%ld\n", sizeof(gnb_ue_ctx_t));
        printf("%ld\n", sizeof(data));
        printf("%ld\n", sizeof(data_t));
        return 0;
}