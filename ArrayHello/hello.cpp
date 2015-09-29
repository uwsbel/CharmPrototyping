#include "hello.decl.h"

#include "hello.h"
#include "main.decl.h"

extern /* readonly */ CProxy_Main mainProxy;
extern /* readonly */ int numElements;

Hello::Hello() {
  // Nothing to do when the Hello chare object is created.
  // This is where member variables would be initialized
  // just like in a C++ class constructor.
}

// Constructor needed for chare object migration (ignore for now)
// NOTE: This constructor does not need to appear in the ".ci" file
Hello::Hello(CkMigrateMessage *msg) { }

void Hello::sayHi(int from) {

  // Have this chare object say hello to the user.
  CkPrintf("\"Hello\" from Hello chare # %d on "
           "processor %d (told by %d).\n",
           thisIndex, CkMyPe(), from);

  // Tell the next chare object in this array of chare objects
  // to also say hello. If this is the last chare object in
  // the array of chare objects, then tell the main chare
  // object to exit the program.
  if (thisIndex < (numElements - 1))
    thisProxy[thisIndex + 1].sayHi(thisIndex);
  else
    mainProxy.done();
}

#include "hello.def.h"