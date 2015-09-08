/******************************************************
 *		Queue_List.c
 * @file	Queue_List.c
 * @brief	Source file of list queue module
 * @version	0.0.1
 * @author	Gwf
 *
 * Copyright(c) 2015, Gwf
 * All rights reserved
 *******************************************************/
#include	"stdio.h"
#include	"stdlib.h"
#include  "string.h"
#include	"Queue_List.h"
 
/********** PRIVATE FUNCTION **********/
static void Copy_To_Node(ts_Item item, ps_Node pNode);
static void Copy_To_Item(ps_Node pNode, ps_Item pItem);
static void Init_Queue(ps_Queue	pq);

/********** PUBLIC FUNCTION **********/
/**
 * @brief  Creat new queue
 * @param  None
 * @retval pnew(ps_Queue)
 */
ps_Queue Create_Queue(void)
{
	ps_Queue pnew;

	pnew = (ps_Queue)malloc(sizeof(ts_Queue));

	if(pnew != NULL)
	{
		Init_Queue(pnew);
	}

	return(pnew);
}

/**
 * @brief  Delete the queue
 * @param  pq(ps_Queue)
 * @retval None
 */
void Delete_Queue(ps_Queue 	pq)
{
	Empty_Queue(pq);

	free(pq);
}

/**
 * @brief  Check if the queue is full
 * @param  pq(ps_Queue)
 * @retval (Bool)
 */
FlagStatus Queue_Is_Full(const ps_Queue	pq)
{
	return((pq ->Count_Node >= LIMIT_QUEUE) ? SET : RESET);
}

/**
 * @brief  check if the queue is empty
 * @param  pq(ps_queue)
 * @retval (bool)
 */
FlagStatus Queue_Is_Empty(const ps_Queue	pq)
{
	return((pq ->Count_Node == 0) ? SET : RESET);
}

/**
 * @brief  Count the number in the queue
 * @param  pq(ps_queue)
 * @retval (uint8_t): Number of nodes in the queue
 */
uint8_t	Queue_Count(const ps_Queue	pq)
{
	return(pq ->Count_Node);
}

/**
 * @brief  Add a new item to the queue
 * @param  pq(ps_queue)
 * @param  item(ts_Item)
 * @retval (ErrorStatus)
 */
ErrorStatus Queue_Write(ts_Item item, ps_Queue	pq)
{
	ps_Node pnew;
	
	/* If the queue is full, then return false. */
	if(Queue_Is_Full(pq))
		return ERROR;

	/* Allocate memory for new node. If no memory is available for node, return false. */
	pnew = (ps_Node)malloc(sizeof(ts_Node));
	
	if(pnew == NULL)
	{
		return	ERROR;
	}
	
	/* Copy item to node. */
	Copy_To_Node(item, pnew);
	
	/* Insert new node to the queue. */
	pnew ->pre = NULL;

	if(Queue_Is_Empty(pq))
	{
		pq ->Tail = pnew;
		pnew ->next = NULL;
	}
	else
	{
		pq ->Header ->pre = pnew;
		pnew ->next = pq ->Header;
	}
	
	pq ->Header = pnew;
	pq ->Count_Node++;
	
	return SUCCESS;
}

/**
 * @brief  Read a item from a queue
 * @param  pq(ps_queue)
 * @param  pitem(ps_Item): Where the item will be moved to.
 * @retval (bool)
 */
ErrorStatus Queue_Read(ps_Item pitem, ps_Queue pq)
{
	ps_Node pt;
	
	/* Check if queue is empty. Return false, if Empty. */
	if(Queue_Is_Empty(pq))
		return ERROR;

	/* Copy item to the destination item. */
	Copy_To_Item(pq ->Tail, pitem);
	
	/* The pre node is the new tail node, and free the read node memory. */
	pt = pq ->Tail;
	free(pt);
	
	pq ->Tail = pq ->Tail ->pre;
	if((pq ->Tail) != NULL)
		pq ->Tail ->next = NULL;/* If the pq ->Tail is Null, what will happen? */
	
	/* Reduce the count of nodes. */
	pq ->Count_Node--;
	
	/* If the count of nodes, then clear the header pointer of the queue. */
	if(pq ->Count_Node == 0)
		pq ->Header = NULL;
	
	return SUCCESS;
}

/**
 * @brief  Empty the queue's nodes
 * @param  pq(ps_queue)
 * @retval None
 */
void Empty_Queue(ps_Queue pq)
{
	ts_Item dummy;
	/*Clear the nodes with functions "Queue_Read()"*/
	while(!Queue_Is_Empty(pq))
		Queue_Read(&dummy, pq);
}

#ifdef Node_Remove_EN
	/**
	 * @brief  Remove the node with item as same as parameter of item
	 * @param  pq(ps_queue)
	 * @param  item(ts_Item)
	 * @retval None
	 */
	ErrorStatus Node_Remove(ps_Node pnode, ts_Item item)
	{
		if(memcmp(&item, &(pnode ->item), sizeof(ts_Item)) == 0)
		{
			/*Delete the node from queue*/
			if(pnode ->pre != NULL)
				pnode ->pre ->next = pnode ->next;/* If there is no previous node, what will happen? */
			if(pnode ->next != NULL)
				pnode ->next ->pre = pnode ->pre;/* If there is no next node, what will happen? */
			
			free(pnode);
			
			return(SUCCESS);
		}
		
		return(ERROR);
	}
#endif /* Node_Remove_EN */

/**
 * @brief  Traverse the whole queue
 * @param  pq(ps_queue)
 * @param  pfun: the function's pointer this function will call
 * @retval None
 */
void Queue_Traverse(ps_Queue	pq,	ErrorStatus (*pfun)(ps_Node pNode, ts_Item Item), ts_Item item)
{
	ps_Node pnode = pq ->Header;
	ErrorStatus Result_Function = ERROR;
	
	while(pnode ->next != NULL)
	{
		Result_Function = (* pfun)(pnode, item);
		Result_Function = Result_Function;
		pnode = pnode ->next;
	}
}

/****************	PRIVATE FUNCTION	********************/ 
/**
 * @brief  Initialize the queue
 * @param  pq(ps_Queue)
 * @retval None
 */
static void Init_Queue(ps_Queue	pq)
{
	pq ->Header = pq	->Tail = NULL;
	pq ->Count_Node = 0;
}

/**
 * @brief  Copy the item to the node
 * @param  item(ts_Item)
 * @param  pNode(ps_Node): Node's pointer
 * @retval None
 */
static void Copy_To_Node(ts_Item item, ps_Node pNode)
{
	pNode ->item = item;
}

/**
 * @brief  Copy the node's item to the item
 * @param  pItem(ps_Item): Item's pointer
 * @param  pNode(ps_Node): Node's pointer
 * @retval None
 */
static void Copy_To_Item(ps_Node pNode, ps_Item pItem)
{
	*pItem = pNode ->item;
}
