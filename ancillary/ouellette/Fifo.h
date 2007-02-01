/************************************************/
// Fifo.h
// Public header file containing Definitions
// and function prototypes.

#ifndef _FIFO_H_
#define _FIFO_H_

// FIFO_SIZE Must be a power of 2 (2, 4, 8, 16, 32, 64, or 128).
#define FIFO_SIZE   32

// FifoPut Return values.
#define FIFO_ADD_OK 0  // Indicates that FifoPut Succeeded
#define FIFO_FULL   1  // Indicates that FifoPut Failed
                      //  (no room for more entries).

// FifoGet Return Value.
#define FIFO_EMPTY  -1 // Indicates that FifoGet Failed
                      //  (Fifo is empty).

// Function Prototypes
void FifoInit(void);
bit FifoPut(unsigned char);
int FifoGet(void);

#endif
