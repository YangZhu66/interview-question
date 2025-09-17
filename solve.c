#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <math.h>
typedef char element_t;
typedef struct sequence
{
    element_t data;
    struct sequence *pre;
    struct sequence *next;
}sequence_t;
typedef struct list
{
    sequence_t *head;
    sequence_t *tail;
    int size;
}list_t;
list_t *create_queue(void)
{
    list_t *manager=(list_t *)malloc(sizeof(list_t));
    if(manager==NULL)
    {
        printf("malloc error\n");
        return NULL;
    }
    manager->head=manager->tail=NULL;
    manager->size=0;
    return manager;
}
//头插
bool push_head(list_t *manager,element_t inputdata)
{
    sequence_t *new=(sequence_t *)malloc(sizeof(sequence_t));
    if(new==NULL)
    {
        printf("malloc error\n");
        return false;
    }
    new->data=inputdata;
    new->next=NULL;
    new->pre=NULL;
    if(manager->size==0)//第一次
    {
        manager->head=manager->tail=new;
        new->pre=new;
        new->next=new;
    }
    else
    {
        manager->head->pre=new;
        manager->tail->next=new;
        new->pre=manager->tail;
        new->next=manager->head;
        manager->head=new;
    }
    manager->size++;
}
//尾插
bool push_tail(list_t *manager,element_t inputdata)
{
    sequence_t *new=(sequence_t *)malloc(sizeof(sequence_t));
    if(new==NULL)
    {
        printf("malloc error\n");
        return false;
    }
    new->data=inputdata;
    new->next=NULL;
    new->pre=NULL;
    if(manager->size==0)//第一次
    {
        manager->head=manager->tail=new;
        new->pre=new;
        new->next=new;
    }
    else
    {
        manager->head->pre=new;
        manager->tail->next=new;
        new->pre=manager->tail;
        new->next=manager->head;
        manager->tail=new;
    }
    manager->size++;
}
//头删
bool pop_head(list_t *manager)
{
    
    if(manager->size==0)//不存在
    {
        printf("the sequence is empty\n");
        return true;
    }
    sequence_t *del_data=manager->head;
    if(manager->size!=1)
    {
        manager->head=manager->head->next;
        manager->head->pre=manager->tail;
        manager->tail->next=manager->head;
    }
    else
    {
        manager->head = manager->tail = NULL;
    }
    free(del_data);
    manager->size--;
}
//尾删
bool pop_tail(list_t *manager)
{
    
    if(manager->size==0)//不存在
    {
        printf("the sequence is empty\n");
        return true;
    }
    sequence_t *del_data=manager->tail;
    if(manager->size!=1)
    {
        manager->tail=manager->tail->pre;
        manager->tail->next=manager->head;
        manager->head->pre=manager->tail;
    }
    else
    {
        manager->head = manager->tail = NULL;
    }
    free(del_data);
    manager->size--;
}
//取头
element_t get_head(list_t *manager)
{
    return (manager->head->data);
}
//取尾
element_t get_tail(list_t *manager)
{
    return (manager->tail->data);
}
//判断是否为空
bool isEmpty(list_t *manager)
{
    return (manager->size==0);
}
//qingkong
void destroy_all(list_t *manager)
{
    if(manager->size==0)
    {
        printf("is empty\n");
        return;
    }
    sequence_t *p=manager->head;
    for(int i = 0; i < manager->size; i++) 
    { 
        sequence_t *temp = p;
        p = p->next;
        free(temp);
    }
    free(manager);
}
//show all
void show_all(list_t *manager)
{
    
    if(manager->size==0)
    {
        printf("is empty\n");
        return;
    }
    sequence_t *p=manager->head;
    do 
    {
        printf("%c->", p->data);
        p = p->next;
    } 
    while(p != manager->head);
    printf("\n");
}
//find [
sequence_t *find_first(list_t *manager)
{
    
    if(manager->size==0)
    {
        printf("is empty\n");
        return NULL;
    }
    sequence_t *p=manager->head;
    sequence_t *q=NULL;
    do 
    {
        if(p->data=='[')
        {
            q=p;
        }
        p = p->next;
    } 
    while(p != manager->head);
    return q;
}
//find ]
sequence_t *find_end(list_t *manager,sequence_t *find_first)
{
    
    if(manager->size==0)
    {
        printf("is empty\n");
        return NULL;
    }
    sequence_t *p=find_first;
    sequence_t *q=NULL;
    do 
    {
        if(p->data==']')
        {
            q=p;
            break;
        }
        p = p->next;
    } 
    while(p != find_first);
    return q;
}
//find number
int find_num(list_t *manager,sequence_t *find_first)
{
    
    if(manager->size==0)
    {
        printf("is empty\n");
        return -1;
    }
    sequence_t *p=find_first;
    sequence_t *q=NULL;
    int count=0;
    int num=0;
    do 
    {
        if(p->data<='9'&&p->data>='0')
        {
            num=num+(p->data-'0')*pow(10,count);
            count++;
            q=p;
        }
        p = p->pre;
        if(p->data<'0'||p->data>'9') break;
    } 
    while(1);
    if(count==0) num=1;
    return num;
}
//find zuishang
sequence_t *find_start(list_t *manager,sequence_t *find_first)
{
    
    if(manager->size==0)
    {
        printf("is empty\n");
        return NULL;
    }
    sequence_t *p=find_first;
    do 
    {
        p = p->pre;
        if(p->data<'0'||p->data>'9') return p;
    } 
    while(1);
    return NULL;
}
void main()
{
    list_t *manager=create_queue();
    char s[100]={0};
    printf("please input s:\n");
    scanf("%s",s);
    for(int i=0;i<strlen(s);i++)
    {
        push_tail(manager,s[i]);
    }

    while(1)
    {
        sequence_t *first=find_first(manager); // 找到最后一个[
        if(first==NULL) break;
        sequence_t *end=find_end(manager,first); // 找到匹配的]，后一个
        if(end==NULL) break;
        sequence_t *start=find_start(manager,first); // 找到数字前的非数字节点
        int num=find_num(manager,first); // 获取重复次数

        list_t *content=create_queue();
        sequence_t *current=first->next;
        while(current!=end)
        {
            push_tail(content,current->data);
            current=current->next;
        }
        
        // 创建
        list_t *expanded=create_queue();
        for(int i=0;i<num;i++)
        {
            sequence_t *content_node=content->head;
            for(int j=0;j<content->size;j++)
            {
                push_tail(expanded, content_node->data);
                content_node=content_node->next;
            }
        }
        
        // 删除原括号和数字部分
        sequence_t *delete_start=start->next;
        sequence_t *delete_end=end;
        // 调整链表连接
        start->next=expanded->head;
        expanded->head->pre=start;      
        expanded->tail->next=end->next;
        end->next->pre=expanded->tail;
        // 更新头尾指针防止丢失
        if(delete_start==manager->head)
            manager->head=expanded->head;
        if(delete_end==manager->tail)
            manager->tail=expanded->tail;
        
        // 释放被删除节点
        current=delete_start;
        int count_delete=0;
        while(current!=delete_end)
        {
            sequence_t *next_node=current->next;
            free(current);
            current=next_node;
            count_delete++;
        }
        free(delete_end);
        count_delete++;
        // 更新大小
        manager->size=manager->size-count_delete+expanded->size;
        // 释放临时链表
        destroy_all(content);
        //释放结构体
        free(expanded); 

    }
    show_all(manager);
    destroy_all(manager);
}