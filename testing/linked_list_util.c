#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sp_fmwk.h>

// these structures need to go in header file 
typedef struct
{
        unsigned char   ngKsi_type; 
        unsigned char   ngKsi_value; 
        unsigned int    nas_count_ul_3gpp; 
        unsigned int    nas_count_dl_3gpp; 
        unsigned int    nas_count_ul_non3gpp; 
        unsigned int    nas_count_dl_non3gpp; 
        unsigned char   cipher_algo; 
        unsigned short  cipher_key_length; 
        unsigned char   cipher_key[16]; 
        unsigned char   integrity_algo; 
        unsigned short  integrity_key_length; 
        unsigned char   integrity_key[16]; 
}ue_nas_security_ctx_t; 


typedef struct
{
        unsigned long long ue_gnb_ngap_id;  
        unsigned char kgnb[32];

}gnb_ctx_t; 

typedef struct
{
        unsigned char suci[32];
        unsigned long long amf_ue_ngap_id; 
        unsigned int            state_3gpp; 
        unsigned int            state_non3gpp;
        ue_nas_security_ctx_t   current_sec_ctx; 
        ue_nas_security_ctx_t   non_current_sec_ctx; 
}ue_ctx_t; 

typedef struct
{
        NODE    __anchor__;
        int fd;
        ue_ctx_t ue_ctx; 
        gnb_ctx_t gnb_ctx;
}gnb_ue_ctx_t;


//these functions and global declarations need to go in gnb_ue.c 

DLIST attached_ue_list;
static int num_ue = 0;

void add_to_list(unsigned long long id, unsigned char* suci)
{

        gnb_ue_ctx_t* mynode = malloc(sizeof(gnb_ue_ctx_t));
        if(mynode == NULL)
        {
                fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
                exit(1);
        }
        mynode->gnb_ctx.ue_gnb_ngap_id = id;
        memcpy(mynode->ue_ctx.suci, suci, sizeof(suci));
        lstAdd(&attached_ue_list, (NODE*)mynode);

        num_ue ++;

}

 

void display_list()
{
        NODE* scan;
        gnb_ue_ctx_t* mynode;
        scan = lstFirst(&attached_ue_list);
        int i = 1;
        while(scan != NULL)
        {
                mynode = (gnb_ue_ctx_t*)scan;
                printf("ue[%d] -------------- context-----data\n", i);
                printf("ran_ue_ngap_id : %lld\n",mynode->gnb_ctx.ue_gnb_ngap_id);
                printf("suci : %s\n", mynode->ue_ctx.suci);
                scan = lstNext(scan);
                printf("****************************************\n");
                i++;
        }

}

 

void delete_from_list(unsigned long long id)
{
        NODE* scan;
        gnb_ue_ctx_t* mynode;
        scan = lstFirst(&attached_ue_list);
        while(scan != NULL)
        {
                mynode = (gnb_ue_ctx_t*)scan;
                scan = lstNext(scan);
                if(mynode->gnb_ctx.ue_gnb_ngap_id == id)
                {
                        lstDelete(&attached_ue_list, (NODE*)mynode);
                        num_ue --;
                }
        }
}

int main()
{
        //id generation function need to be written 
        //also handle the argument sent during attach command (ie. the number of ues to attach and add ues to the list after id generation)
        //also generate unique suci to each ue with proper format as given in the spec which is to be sent during attach procedure

        unsigned long long id1= 34;
        unsigned char suci1[] = "7748973";
        unsigned long long id2 =33;
        unsigned char suci2[] = "7488098";
        unsigned long long id3 = 45;
        unsigned char suci3[] = "7837529";
        unsigned long long id4 = 56;
        unsigned char suci4[] = "7843000";

        add_to_list(id1, suci1);
        add_to_list(id2, suci2);
        add_to_list(id3, suci3);
        add_to_list(id4, suci4);

        display_list();
        printf("%s\n", "after deleting ue[3]");
        delete_from_list(45);

        display_list();

        return 0;
}

/*OUTPUT OF THE ABOVE PROGRAM 

ue[1] -------------- context-----data
ran_ue_ngap_id : 34
suci : 7748973
****************************************
ue[2] -------------- context-----data
ran_ue_ngap_id : 33
suci : 7488098
****************************************
ue[3] -------------- context-----data
ran_ue_ngap_id : 45
suci : 7837529
****************************************
ue[4] -------------- context-----data
ran_ue_ngap_id : 56
suci : 7843000
****************************************
after deleting ue[3]
ue[1] -------------- context-----data
ran_ue_ngap_id : 34
suci : 7748973
****************************************
ue[2] -------------- context-----data
ran_ue_ngap_id : 33
suci : 7488098
****************************************
ue[3] -------------- context-----data
ran_ue_ngap_id : 56
suci : 7843000
****************************************



*/ 