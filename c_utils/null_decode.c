#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>


typedef struct
{
	char* val;
}name_t;

void json_free(name_t* p)
{
	if(p ==  NULL) return;
	free(p->val);
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

name_t* json_decode_to_struct(name_t* p, json_t* obj)
{
	const char *key;
	json_t *value;

	if(p == NULL)
    {
        p = malloc(sizeof(name_t));
        if(p == NULL) {fprintf(stdout,"%s\n","error: amf_malloc");}
        memset(p, 0, sizeof(name_t));
    }
    json_object_foreach(obj, key, value)
    {
    	if (strcmp(key, "name") == 0)
  		{
  			size_t len = json_string_length(value);
  			fprintf(stdout,"%d\n", (int)len);
    		if(len)
    		{
        		p->val = malloc(len+1);
        		strcpy(p->val, json_string_value(value));
    		}
    		if(json_is_null(value))
    		{
    			p->val = (char*)~0;
    		}
  		}
    }
    return p;
}
int main()
{
	FILE *fp;
    char buff[2048];

    fp = fopen("test.json", "r");
    fread(buff, 2048,1, fp);
    fclose(fp);
    name_t* name = NULL;
    json_t *root = NULL;
    root = server_load_json(buff);
    if (root == NULL)
    {
        fprintf(stderr, "failed to load json at %s %d\n", __FILE__, __LINE__);
    }
    
    name = json_decode_to_struct(name, root);
    printf("%s\n", "decoded the data");
    if(name->val != NULL)
    {
    	if(name->val == (char*)~0)
    	{
    		printf("%s\n", "value is null");
    	}
    	else
    	{
    		printf("%s\n", name->val);
    	}
    	
    }
    
}