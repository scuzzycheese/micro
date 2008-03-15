#ifndef CONFIGH
#define CONFIGH
#ifdef __cplusplus
extern "C" {
#endif

//I want to forward declair this puppy
struct web_state;

typedef int (*pageFunc)(int argc, char **argv, struct web_state *ws);

//This is for libhash
#define ptType pageFunc


#ifdef __cplusplus
}
#endif
#endif
