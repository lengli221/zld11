#ifndef __LIST_H_
#define __LIST_H_

#if Debug_List == 1
// typedef struct __List_head_{
// 	struct __List_head_ *next,*prev;
// }List_head;

// #define LIST_HEAD_INIT(name) {&(name),&(name)}
// #define LIST_HEAD(name) List_head name = LIST_HEAD_INIT(name)
// //#define LIST_HEAD(name)  List_head name;name.next = &name;name.prev=&name;

struct list_head{
	struct list_head *next,*prev;
};

#define LIST_HEAD_INIT(name) {&(name),&(name)}
/*
** #define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)
** �����޷�ͨ��:expression must have a constant value
*/
#define LIST_HEAD(name) struct list_head name;//name.next = &name;name.prev=&name;

/*
** ������������
*/
#define list_for_each(pos,head)\
	for(pos = (head)->next;pos != (head);\
		pos = pos->next)

/*
** 	��ȡlist����ʼ��ַ
**	(
**		(type*)
**		(
**			(char*)(ptr)-
**			(unsigned long)(&((type*)0)->member)
**		)
**	)
*/
#define list_entry(ptr,type,member)\
	((type*)((char*)(ptr)-(unsigned long)(&((type*)0)->member)))

/*
** ��������
*/
static __INLINE  void __list_add(struct list_head *_new,struct list_head *prev,struct list_head *next){
								  next->prev = _new;
								  _new->next = next;
								  _new->prev = prev;
								  prev->next = _new;
}

/*
** ����ͷ��β���ӽ��--����ָ�������head�������new���
*/
void list_add(struct list_head *_new,struct list_head *head);
/*
** ջ--������ָ�������head���ǰ����new���
*/
/*static*/ void list_add_tail(struct list_head *_new,struct list_head *head);

/*
** ����list
*/
void Debug_ListParam(void);

#endif

#endif

