#include<stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef NIL
#define NIL ((NODE *)0)
#endif


typedef struct node {
    struct node *next;      /* Points at the next node in the list */
    struct node *previous;  /* Points at the previous node in the list */
} NODE;


typedef struct{                 /* Header for a linked list. */
    NODE node;              /* Header list node */
    int count;              /* Number of nodes in list */
} DLIST;

void         lstInit (DLIST *pList);
void         lstAdd (DLIST *pList, NODE *pNode);
void         lstConcat (DLIST *pDstList, DLIST *pAddList);
int          lstCount (DLIST *pList);
void         lstDelete (DLIST *pList, NODE *pNode);
void         lstExtract (DLIST *pSrcList, NODE *pStartNode, NODE *pEndNode, DLIST *pDstList);
NODE *       lstFirst (DLIST *pList);
NODE *       lstGet (DLIST *pList);
void         lstInsert (DLIST *pList, NODE *pPrev, NODE *pNode);
NODE *       lstLast (DLIST *pList);
NODE *       lstNext (NODE *pNode);
NODE *       lstNth (DLIST *pList, int nodenum);
NODE *       lstPrevious (NODE *pNode);
NODE *       lstNStep (NODE *pNode, int nStep);
int          lstFind (DLIST *pList, NODE *pNode);
void         lstFree (DLIST *pList);


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

typedef struct advanced_list
{
    NODE __anchor__;
    int a;
    int b;
}list_of_int;

DLIST list;

void add_to_list(int a,int b)
{
    list_of_int* my_node;
    my_node = malloc(sizeof(list_of_int));
    if(my_node == NULL)
    {
        exit(1);
    }
    my_node->a = a;
    my_node->b = b;
    lstAdd(&list, (NODE*)my_node);
}
void print_list()
{

}

void delete_from_list()
{

}
int main()
{
    DLIST list;
    lstInit(&list);
    return 0;
}