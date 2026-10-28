#include "freeList.h"

freeList::freeList( long int*inRAM, int size ) {
  head = inRAM;
  head[0] = size - 2;
  head[1] = 0;
}

long int*
freeList::reserve_space( int size ) {
  long int* chunk = head;
  long int oldSize = head[0];
  long int oldNext = head[1];

  chunk[0] = size;
  chunk[1] = 0;

  head = chunk + size + 2;
  head[0] = oldSize - size - 2;
  head[1] = oldNext;
  long int* loc = chunk + 2;

  return loc;
}

void
freeList::free_space( long int* location ) {
  long int* chunk = location - 2;
  chunk[1] = (long int)head;
  head = chunk;
}

void
freeList::coalesce_forward() {
  long int* curr = head;

  while( curr != NULL && curr[1] != 0 ) {
    long int* next = (long int*)curr[1];

    if( curr + curr[0] + 2 == next ) {
      curr[0] += next[0] + 2;
      curr[1] = next[1];
    } else {
      curr = next;
    }
  }
}

// print() is given to you. It traverses the free list and prints out what is there.
void freeList::print() {
  long int * printHead = head;
  
  while( printHead != NULL ) {
    cout << "at " << printHead << "("<< dec <<printHead[0] << " : 0x" << hex << printHead[1] <<  ")\n";
    printHead = (long int *)printHead[1];
  }
}
