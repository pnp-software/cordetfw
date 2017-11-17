#include <stdio.h>
#include <CrPsDebug.h>
#include <CrFwConstants.h>
#include <Pckt/CrFwPckt.h>
#include <Services/General/CrPsPktServHk.h>
#include <Services/General/CrPsPktServHkSupp.h>


void print31(char* pckt)
{
  uint32_t i, j, n1, nfa, n2;
  n1 = getHkCreateCmdN1(pckt);
  for (i=1;i<=n1;i++)
  {
    if (i>10)
    {
      printf(" %d    |", i);
    }
    else
    {
      printf(" %d     |", i);
    }
    if (i>100) 
      {
        break;
      }
  }
  printf(" NFA           |");
  nfa = getHkCreateCmdNFA(pckt);
  for (i=1;i<=nfa;i++)
  {
    printf(" SCSrepnr      | N2            |");
    n2 = getHkCreateCmdN2(pckt, i);
    for (j=1;j<=n2;j++)
    {
      if (j>10)
      {
        printf(" %d    |", j);
      }
      else
      {
        printf(" %d     |", j);
      }
      if (j>100) 
      {
        break;
      }
    }
    if (i>100) 
      {
        break;
      }
  }
  printf("EOP");
}

void print310(char* pckt)
{
  uint32_t i, j, n1, nfa, n2;
  n1 = getHkRepStructRepN1(pckt);
  for (i=1;i<=n1;i++)
  {
    if (i>10)
    {
      printf(" %d    |", i);
    }
    else
    {
      printf(" %d     |", i);
    }
    if (i>100) 
      {
        break;
      }
  }
  printf(" NFA           |");
  nfa = getHkRepStructRepNFA(pckt);
  for (i=1;i<=nfa;i++)
  {
    printf(" SCSrepnr      | N2            |");
    n2 = getHkRepStructRepN2(pckt, i);
    for (j=1;j<=n2;j++)
    {
      if (j>10)
      {
        printf(" %d    |", j);
      }
      else
      {
        printf(" %d     |", j);
      }
      if (j>100) 
      {
        break;
      }
    }
    if (i>100) 
      {
        break;
      }
  }
  printf("EOP");
}

void debugPacket(char* pckt, size_t size)
{
  size_t i;
  DEBUG_PCKT("\n");
  /*Prim and Sec Headers*/
  if (CrFwPcktGetCmdRepType(pckt) == crRepType)
    {
      printf("Primary Header           | Sec Header                            |");        
    }
  else
    {
      printf("Primary Header           | Sec Header    |");
    }

  if(CrFwPcktGetServType(pckt) == 3 && (CrFwPcktGetServSubType(pckt) == 1 || CrFwPcktGetServSubType(pckt) == 2))
  {
    /*enhanced 3.1 Header*/
    printf("*  |collinterval   |N1             |");
    print31(pckt);
  }
  if(CrFwPcktGetServType(pckt) == 3 && (CrFwPcktGetServSubType(pckt) == 10 || CrFwPcktGetServSubType(pckt) == 12))
  {
   /*enhanced 3.1 Header*/
    printf("*  |*  |collinterval   |N1             |");
    print310(pckt); 
  }
  printf("\n");
  printf(COLOR_GREEN);
  for (i = 0; i < size; i++)
    {
      if (i==6)
      {
        printf(COLOR_YELLOW);
      }
      if ((CrFwPcktGetCmdRepType(pckt) == crRepType) && (i==16))
      {
        printf(COLOR_STANDARD);
      }
      if ((CrFwPcktGetCmdRepType(pckt) == crCmdType) && (i==10))
      {
        printf(COLOR_STANDARD);
      }      
      DEBUG_PCKT(" :");
      DEBUG_PCKT("%02X", (unsigned char)pckt[i]);
    }
  DEBUG_PCKT("\n ");
  printf(COLOR_GREEN);
  for (i = 0; i < size; i++)
    {
      if (i==6)
      {
        printf(COLOR_YELLOW);
      }
      if ((CrFwPcktGetCmdRepType(pckt) == crRepType) && (i==16))
      {
        printf(COLOR_STANDARD);
      }
      if ((CrFwPcktGetCmdRepType(pckt) == crCmdType) && (i==10))
      {
        printf(COLOR_STANDARD);
      } 
      DEBUG_PCKT("-");
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
  printf(COLOR_STANDARD);
}


void clearPacket(char* pckt, size_t size)
{
  size_t i;
  for (i=0;i<size;i++)
  {
    pckt[i]=0;
  }

}




