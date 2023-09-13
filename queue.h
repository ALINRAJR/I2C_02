/*
 * queue.h
 *
 
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct {
	uint8_t *queuebuffer;
	uint32_t writeindex;
	uint32_t readindex;
	uint32_t count;
}Queue_t;
void vQueueInitialize(Queue_t *queueptr, uint8_t *buffer, uint8_t maxsize);
uint8_t ucQueueWrite(Queue_t *queueptr,uint8_t writedata);
uint8_t ucQueueRead(Queue_t *queueptr,uint8_t* readdata);
uint8_t ucQueueIsFull(Queue_t *queueptr);
uint8_t ucQueueIsEmpty(Queue_t *queueptr);

#endif /* QUEUE_H_ */
