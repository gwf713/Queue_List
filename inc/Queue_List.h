/******************************************************
 *		Queue_List.h
 * @file	Queue_List.h
 * @brief	Head file of list queue module
 * @version	0.0.2
 * @date    09-September-2015
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
	#include "stdio.h"
	/* Maxim items in queue */
	#define	LIMIT_QUEUE	10
	#define Node_Remove_EN
	
	typedef void *ps_Item;
	
	/*type define of node*/ 
	typedef	struct node{
		void *	pItem; /* Item in node */
		struct	node	*pre; /* Previous node's pointer*/
		struct	node	*next;/* Next node's pointer */
	}ts_Node, *ps_Node;

	/*type define of queue*/
	typedef struct {
		ps_Node	Header;
		ps_Node	Tail;
		uint8_t	Count_Node;
		size_t  Size_Item;
	}ts_Queue, *ps_Queue;

	/********** PUBLIC FUNCTION **********/
	extern ps_Queue Create_Queue(size_t Size_Item);
	extern void Delete_Queue(ps_Queue 	pq);
	extern FlagStatus Queue_Is_Full(const ps_Queue	pq);
	extern FlagStatus Queue_Is_Empty(const ps_Queue	pq);
	extern uint8_t	Queue_Count(const ps_Queue	pq);
	extern ErrorStatus Queue_Write(ps_Item pItem, ps_Queue	pq);
	extern ErrorStatus Queue_Read(ps_Item pItem, ps_Queue	pq);
	extern void Empty_Queue(ps_Queue pq);
	#ifdef Node_Remove_EN
		extern ErrorStatus Node_Remove(ps_Node pnode, ps_Item pItem, ps_Queue pq);
	#endif /* Node_Remove_EN */
	extern void Queue_Traverse(ps_Queue	pq,	ErrorStatus (*pfun)(ps_Node pNode, ps_Item Item, ps_Queue pq), ps_Item pItem);

#endif	/*QUEUE_LIST_H*/

