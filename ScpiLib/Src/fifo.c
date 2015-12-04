
#include "fifo.h"

void fifo_init(fifo_t * fifo) {
    fifo->wr = 0;
    fifo->rd = 0;
    fifo->size = FIFO_SIZE;
}

void fifo_clear(fifo_t * fifo) {
    fifo->wr = 0;
    fifo->rd = 0;
}

boolean fifo_add(fifo_t * fifo, INT16 value) {
    /* FIFO full? */
    if (fifo->wr == ((fifo->rd + fifo->size) % (fifo->size + 1))) {
        fifo_remove(fifo, NULL);
    }

    fifo->data[fifo->wr] = value;
    fifo->wr = (fifo->wr + 1) % (fifo->size + 1);

    return TRUE;
}

boolean fifo_remove(fifo_t * fifo, INT16 * value) {
    /* FIFO empty? */
    if (fifo->wr == fifo->rd) {
        return FALSE;
    }

    if(value) {
        *value = fifo->data[fifo->rd];
    }

    fifo->rd = (fifo->rd + 1) % (fifo->size + 1);

    return TRUE;
}

boolean fifo_count(fifo_t * fifo, INT16 * value) {
    *value = fifo->wr - fifo->rd;
    if (*value < 0) {
        *value += (fifo->size + 1);
    }
    return TRUE;
}