/*
 * queue.c
 *

 */

#include <stdint.h>
#include "queue.h"

void vQueueInitialize(Queue_t *queueptr,uint8_t *buffer,uint8_t maxsize)
{
	queueptr->queuebuffer=buffer;
	queueptr->writeindex=0;
	queueptr->readindex=0;
	queueptr->count=maxsize;

}

uint8_t ucQueueWrite(Queue_t *queueptr,uint8_t writedata) {
	if (ucQueueIsFull(queueptr))
		return 0;

	queueptr->queuebuffer[queueptr->writeindex++] = writedata;
	queueptr->writeindex = queueptr->writeindex % (queueptr->count - 1);
	return 1;
}
uint8_t ucQueueRead(Queue_t *queueptr,uint8_t* readdata){
	if(ucQueueIsEmpty(queueptr))
		return 0;
	*readdata=queueptr->queuebuffer[queueptr->readindex++];
	queueptr->readindex=queueptr->readindex % (queueptr->count -1);
	return 1;

}
uint8_t ucQueueIsFull(Queue_t *queueptr){
	return (queueptr->writeindex + 1 == queueptr->readindex?1:0);
}

uint8_t ucQueueIsEmpty(Queue_t *queueptr){
		return(queueptr->writeindex==queueptr->readindex?1:0);
	}
