#include <stdio.h>
#include <CrPsDebug.h>

void debugPacket(char* pckt, size_t size)
{
  size_t i;
  DEBUG_PCKT("\n");
  for (i = 0; i < size; i++)
    {
      DEBUG_PCKT(" :");
      DEBUG_PCKT("%02X", (unsigned char)pckt[i]);
    }
  DEBUG_PCKT("\n");
  for (i = 0; i < size; i++)
    {
      if (i > 0) 
        {
          DEBUG_PCKT("-");
        }
      if ((unsigned char)pckt[i]< 10) 
        {
          DEBUG_PCKT(" ");
        }
      if ((unsigned char)pckt[i]< 100) 
        {
          DEBUG_PCKT(" ");
        }
      DEBUG_PCKT("%u", (unsigned char)pckt[i]);
    }
  DEBUG_PCKT("\n");
}



