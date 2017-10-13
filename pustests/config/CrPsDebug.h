#include <stdio.h>

#define COLOR_RED        "\033[31m"
#define COLOR_STANDARD   "\033[0m"
#define COLOR_BLUE       "\033[34m"
#define COLOR_GREEN      "\033[32m"
#define COLOR_YELLOW     "\033[33m"
#define COLOR_MAGENTA    "\033[35m"
#define COLOR_CYAN       "\033[36m"




/* Service 1 Printouts*/
#define DEBUGP_1(...)      //printf(COLOR_BLUE); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Service 17 Printouts*/
#define DEBUGP_17(...)     //printf(COLOR_MAGENTA); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Service 3 Printouts*/
#define DEBUGP_3(...)      printf(COLOR_STANDARD); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Service 5 Printouts*/
#define DEBUGP_5(...)      printf(COLOR_STANDARD); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)


/* TestSuite for Service 1 Printouts*/
#define DEBUGP_TS1(...)    //printf(COLOR_YELLOW); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* TestSuite for Service 17 Printouts*/
#define DEBUGP_TS17(...)   //printf(COLOR_CYAN); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD) 
 

/* TestSuite for Service 3 Printouts*/
#define DEBUGP_TS3(...)    printf(COLOR_STANDARD); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* TestSuite for Service 5 COLOR_STANDARD*/
#define DEBUGP_TS5(...)    printf(COLOR_CYAN); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Testsuite DataPool Printouts*/
#define DEBUGP_TSDP(...)   printf(COLOR_YELLOW); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD) 

/* Testsuite Getter and Setter Printouts*/
#define DEBUGP_TSGS(...)   printf(COLOR_BLUE); printf("%s %d - ", __FILE__, __LINE__); printf(__VA_ARGS__); printf(COLOR_STANDARD)


/* Red Text */
#define DEBUGP_RED(...)    printf(COLOR_RED); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Blue Text */
#define DEBUGP_BLUE(...)    printf(COLOR_BLUE); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Magenta Text (violet) */
#define DEBUGP_MAGENTA(...)    printf(COLOR_MAGENTA); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Cyan Text */
#define DEBUGP_CYAN(...)    printf(COLOR_CYAN); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Green Text */
#define DEBUGP_GREEN(...)  printf(COLOR_GREEN); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Yellow Text */
#define DEBUGP_YELLOW(...)  printf(COLOR_YELLOW); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* Text Text */
#define DEBUGP(...)        printf(COLOR_STANDARD); printf(__VA_ARGS__); printf(COLOR_STANDARD)

/* debugPacket printouts*/
#define DEBUG_PCKT(...)    printf(COLOR_STANDARD); printf(__VA_ARGS__); printf(COLOR_STANDARD)


void debugPacket(char* pckt, size_t size);






