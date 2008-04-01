#ifndef CONFIGH
#define CONFIGH
#ifdef __cplusplus
extern "C" {
#endif

//I want to forward declair this puppy
struct web_state;

typedef int (*pageFunc)(char **argv, struct web_state *ws);

//This is for libhash
#define ptType pageFunc


#ifdef X86
//my linux box's MAC address
//00:11:D8:BB:6C:45
#define ETHADDR0 0x00
#define ETHADDR1 0x11
#define ETHADDR2 0xD8
#define ETHADDR3 0xBB
#define ETHADDR4 0x6C
#define ETHADDR5 0x45
#endif

#ifdef __cplusplus
}
#endif
#endif
