
/** The maximum size in number of bytes of a packet */
#define LPTSIZE 4000

/**
 * The array holding the packets.
 * Packets are stored in this array in blocks of size LPTSIZE.
 */
static char memArray[LPTSIZE];


void initmemArray()
{
  unsigned int i;
  unsigned char a, b;

  a=0;
  b=0;

  for (i=0;i<LPTSIZE;i+=2)
  {
    memArray[i] = a;
    memArray[i+1] = b;
    b++;
    if (b==255)
    {
      b=0;
      a++;
    }
  }
}


unsigned int* getLptMemStartAddr(unsigned int LptBuffer) /* Adaptation Point */
{
  (void)LptBuffer;

  return (unsigned int*)memArray;
}

unsigned int getLptMemSize(unsigned int LptBuffer) /* Adaptation Point */
{
  (void)LptBuffer;

  return (unsigned int)LPTSIZE;
}
