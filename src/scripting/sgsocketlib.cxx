
// TODO: add Nasal wrapper for SGSocket: http://simgear.sourceforge.net/doxygen/classSGSocket.html

#include <cstdlib>
#include <cstdio>
#include <simgear/nasal/nasal.h>
#include <simgear/io/sg_socket.hxx>

static naRef ns;

typedef struct { SGSocket *_s; } SGSocketGhost;

static void SGSocketGhostDestroy(SGSocketGhost *g) 
{
  delete g->_s;
}

static naGhostType SGSocketGhostType = { (void(*)(void*))SGSocketGhostDestroy, "sgsocket" };

naRef naNewSGSocketGhost(naContext ctx, SGSocket *s)
{
  
    SGSocketGhost *g = (SGSocketGhost*) malloc(sizeof(SGSocketGhost));
    g->_s = s;
    return naNewGhost(ctx, &SGSocketGhostType, g);
}

static naRef f_dummy(naContext ctx, naRef me, int argc, naRef* args)
{
    printf("f_dummy()");
    return naNil();
}


static naCFuncItem funcs[] = {
    { "dummy", f_dummy },
    { 0, 0}
};

naRef naInit_sgsocket(naContext ctx) {
    ns = naGenLib(ctx,funcs);
    return ns;
}

