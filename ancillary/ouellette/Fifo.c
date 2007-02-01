/***************************************************/
// Fifo.c
// Source level module

#include "FIFO.H"

// Macro to calculate the current number of entries in
// Fifo, saving the overhead of function call.
#define FifoLength   ((unsigned char)(FifoHead - FifoTail))

// Private, Module Level Variables
unsigned char FifoBuffer[FIFO_SIZE];
unsigned char FifoHead = 0;
unsigned char FifoTail = 0;

// Function to flush the Fifo
void FifoInit(void)
{
  FifoHead = 0;
  FifoTail = 0;
}

// Function to add an entry to Fifo
// If Fifo if full then function returns FIFO_FULL
// else function adds entry to FifoBuffer, increments
// FifoHead and returns FIFO_ADD_OK.
int FifoPut(unsigned char Entry)
{
 if (FifoLength >= FIFO_SIZE)
 {
    return FIFO_FULL;
 }
  FifoBuffer[FifoHead++ & (FIFO_SIZE - 1)] = Entry;
 return FIFO_ADD_OK;
}

// Function to get an entry from Fifo
// If Fifo is empty then function returns FIFO_EMPTY
// else function returns oldest entry in FifoBuffer
// and increments FifoTail.
int FifoGet(void)
{
 if (FifoLength == 0)
 {
    return FIFO_EMPTY;
 }
 return (FifoBuffer[FifoTail++ & (FIFO_SIZE - 1)]);
}
