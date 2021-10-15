#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char content_type[256];
	char content_id[256];
	unsigned char data[65536];
	unsigned int size;
}fw_boundary_token_t;

void fw_boundary_process_collected_data(unsigned char* collected, unsigned int collected_size, fw_boundary_token_t* t)
{
	fprintf(stdout, "%s\n", "inside fw_boundary_process_collected_data");
	char* scan;

	scan = (char*)collected;
	collected[collected_size] = '\0';

	strcpy(t->content_type, "");
	strcpy(t->content_id, "");
	strcpy((char*)t->data, "");
	t->size = 0;
	scan = strstr(scan, "Content-Type: application/json");
	if(scan != NULL)
	{
		strcpy(t->content_type, "application/json");
		scan += strlen("Content-Type: application/json");
		scan = strstr(scan, "{");
		if(scan != NULL)
		{
			strcpy((char*)t->data, scan);
			t->size = strlen((char*)t->data);
			return;
		}
	}

	scan = (char*)collected;
	scan = strstr(scan, "Content-Type: application/vnd.3gpp.ngap");
	if(scan != NULL)
	{
		strcpy(t->content_type, "application/vnd.3gpp.ngap");
		scan += strlen("Content-Type: application/vnd.3gpp.ngap");
		scan = strstr(scan, "Content-Id: ");
		if(scan != NULL)
		{
			scan += strlen("Content-Id: ");
			int count = 0;
			while((*scan != '\n') && (*scan != '\r'))
			{
				t->content_id[count] = *scan;
				scan++;
				count++;
			}
			t->content_id[count] = '\0';
			scan = strstr(scan, "{");
			if(scan != NULL)
			{
				scan ++;
				unsigned char* start = (unsigned char*)scan;

				unsigned char* end = collected + collected_size;
				while(*end != '}') end--;
				if(end > start)
				{
					memcpy(t->data, start, end - start);
					t->size = end - start;
					return;
				}
			}
		}
	}
	scan = (char*)collected;
	scan = strstr(scan, "Content-Type: application/vnd.3gpp.5gnas");
	if(scan != NULL)
	{
		strcpy(t->content_type, "application/vnd.3gpp.5gnas");
		scan += strlen("Content-Type: application/vnd.3gpp.5gnas");
		scan = strstr(scan, "Content-Id: ");
		if(scan != NULL)
		{
			scan += strlen("Content-Id: ");
			int count = 0;
			while((*scan != '\n') && (*scan != '\r'))
			{
				t->content_id[count] = *scan;
				scan++;
				count++;
			}
			t->content_id[count] = '\0';
			scan = strstr(scan, "{");
			if(scan != NULL)
			{
				scan ++;
				unsigned char* start = (unsigned char*)scan;

				unsigned char* end = collected + collected_size;
				while(*end != '}') end--;
				if(end > start)
				{
					memcpy(t->data, start, end - start);
					t->size = end - start;
					return;
				}
			}
		}
	}
	
}

unsigned int fw_boundary_parse(void* input, unsigned int length_input, char* boundary, fw_boundary_token_t* t)
{
	fprintf(stdout, "%s\n", "inside fw_boundary_parse");
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
	end_boundary[begin_boundary_length+1] = '-';
	
	end_boundary_length = begin_boundary_length+2;

	
	void* scan = input;
	int first_boundary = 1;

	collected_size = 0;
	num_collected = 0;

	while(remaining_length > end_boundary_length)
	{
		if(memcmp(scan, end_boundary, end_boundary_length) == 0)
		{
			if(!first_boundary)
			{
				fw_boundary_process_collected_data(collected, collected_size, &t[num_collected]);
				collected_size = 0;
				num_collected++;
			}
			break;
		}
		
		if(memcmp(scan, begin_boundary, begin_boundary_length) == 0)
		{
			scan += begin_boundary_length;
			remaining_length -= begin_boundary_length;

			if(first_boundary)
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

		scan++; remaining_length--;
	}

	return num_collected;
}

int main(int argc, char** argv)
{
	char *req_payload = NULL;
	int len_req_payload = 1;

	req_payload = realloc(req_payload, len_req_payload+strlen("----Boundary"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcpy(req_payload, "----Boundary");
	len_req_payload += strlen("----Boundary");

	req_payload = realloc(req_payload, len_req_payload+strlen("Content-Type: application/json"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, "Content-Type: application/json");
	len_req_payload += strlen("Content-Type: application/json");

	
	char* res = "{plmnId : {mcc : 012, mnc : 342}}";
	int size = strlen(res);
	req_payload = realloc(req_payload, len_req_payload+size);
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}

	strcat(req_payload, res);
	len_req_payload += size;


	req_payload = realloc(req_payload, len_req_payload+strlen("----Boundary"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, "----Boundary");
	len_req_payload += strlen("----Boundary");

	req_payload = realloc(req_payload, len_req_payload+strlen("Content-Type: application/vnd.3gpp.5gnas"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, "Content-Type: application/vnd.3gpp.5gnas");
	len_req_payload += strlen("Content-Type: application/vnd.3gpp.5gnas");


	req_payload = realloc(req_payload, len_req_payload+strlen("Content-Id: n1msg\r\n {"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, "Content-Id: n1msg\r\n {");
	len_req_payload += strlen("Content-Id: n1msg\r\n {");

	char* sm_data = "hjhklasmgksma;l,vlvmkkldnjgnlkngkmv,x.cv nsjnkkhkjalkajdl}\r\n";
	int len_sm = strlen(sm_data);
	req_payload = realloc(req_payload, len_req_payload+len_sm);
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, sm_data);
	len_req_payload += len_sm;

	req_payload = realloc(req_payload, len_req_payload+strlen("----Boundary--"));
	if (req_payload == NULL)
	{
		fprintf(stderr, "failed to allocate memory at %s %d\n", __FILE__, __LINE__);
		exit(1);
	}
	strcat(req_payload, "----Boundary--");
	len_req_payload += strlen("----Boundary--");

	printf("%s\n", req_payload);
	fw_boundary_token_t t[10];
	memset(t, 0, 10*sizeof(fw_boundary_token_t));
	int ret = fw_boundary_parse((char*)req_payload, len_req_payload, "--Boundary", t);
	printf("ret: %d\n", ret);
	int i;
	for(i=0; i<ret; i++)
	{
		printf("item: %d\n", i+1);
		fw_boundary_token_t* tok = &t[i];
		printf("content_type: <%s>\n", tok->content_type);
		printf("content_id: <%s>\n", tok->content_id);
		printf("data_length: <%d>\n", tok->size);
		tok->data[tok->size] = '\0';
		printf("data = %s\n", tok->data);
	}

	return 0;
}
	
