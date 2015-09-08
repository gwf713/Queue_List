/******************************************************
 *		Queue_List.h
 * @file	Queue_List.h
 * @brief	Head file of list queue module
 * @version	0.0.1
 * @author	Gwf
 *
 * Copyright(c) 2015, Gwf
 * All rights reserved
 *
 *******************************************************/
#ifndef	QUEUE_LIST_H
#define	QUEUE_LIST_H
	/* Type define for platform */
	#include "stm32f0xx.h"
	
	/* Maxim items in queue */
	#define	LIMIT_QUEUE	10
	#define Node_Remove_EN
	
	/********** typedef **********/
	typedef	CanRxMsg ts_Item;//type declare for item
	typedef ts_Item *ps_Item;

	/*type define of node*/ 
	typedef	struct	node{
		ts_Item		item; /* Item in node */
		struct	node	*pre; /* Previous node's pointer*/
		struct	node	*next;/* Next node's pointer */
	}ts_Node, *ps_Node;

	/*type define of queue*/
	typedef struct {
		ps_Node	Header;
		ps_Node	Tail;
		uint8_t	Count_Node;
	}ts_Queue, *ps_Queue;

	/********** PUBLIC FUNCTION **********/
	extern ps_Queue Create_Queue(void);
	extern void Delete_Queue(ps_Queue 	pq);
	extern FlagStatus Queue_Is_Full(const ps_Queue	pq);
	extern FlagStatus Queue_Is_Empty(const ps_Queue	pq);
	extern uint8_t	Queue_Count(const ps_Queue	pq);
	extern ErrorStatus Queue_Write(ts_Item item, ps_Queue	pq);
	extern ErrorStatus Queue_Read(ps_Item pitem, ps_Queue	pq);
	extern void Empty_Queue(ps_Queue pq);
	#ifdef Node_Remove_EN
		extern ErrorStatus Node_Remove(ps_Node pnode, ts_Item item);
	#endif /* Node_Remove_EN */
	extern void Queue_Traverse(ps_Queue	pq,	ErrorStatus (*pfun)(ps_Node pNode, ts_Item Item), ts_Item item);

#endif	/*QUEUE_LIST_H*/

