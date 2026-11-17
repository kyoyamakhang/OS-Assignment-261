#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
;
        if (q == NULL || proc == NULL)
                return;
        if (q->size < MAX_QUEUE_SIZE) {
                q->proc[q->size++] = proc;
        }
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (empty(q))
                return NULL;

        int idx = 0;
#ifdef MLQ_SCHED
        uint32_t min_prio = q->proc[0]->prio;
        for (int i = 1; i < q->size; i++) {
                if (q->proc[i]->prio < min_prio) {
                        min_prio = q->proc[i]->prio;
                        idx = i;
                }
        }
#else
        uint32_t min_prio = q->proc[0]->priority;
        for (int i = 1; i < q->size; i++) {
                if (q->proc[i]->priority < min_prio) {
                        min_prio = q->proc[i]->priority;
                        idx = i;
                }
        }
#endif
        struct pcb_t *proc = q->proc[idx];
        for (int i = idx; i < q->size - 1; i++) {
                q->proc[i] = q->proc[i + 1];
        }
        q->size--;
        return proc;
}

struct pcb_t *purgequeue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: remove a specific item from queue
         * */
        if (empty(q) || proc == NULL)
                return NULL;

        for (int i = 0; i < q->size; i++) {
                if (q->proc[i] == proc) {
                        for (int j = i; j < q->size - 1; j++) {
                                q->proc[j] = q->proc[j + 1];
                        }
                        q->size--;
                        return proc;
                }
        }
        return NULL;
}