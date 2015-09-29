#include "main.decl.h"

#include "main.h"
#include "hello.decl.h"

/* readonly */ CProxy_Main mainProxy;
/* readonly */ int numElements;

// Entry point of Charm++ application
Main::Main(CkArgMsg* msg) {

  numElements = 5; // Default numElements to 5

  // There should be 0 or 1 command line arguements.
  // If there is one, it is the number of "Hello"
  // chares that should be created.
  if (msg->argc > 1)
    numElements = atoi(msg->argv[1]);

  // We are done with msg so delete it.
  delete msg;

  // Display some info about this execution
  // for the user.
  CkPrintf("Running \"Hello World\" with %d elements "
           "using %d processors.\n",
           numElements, CkNumPes());

  // Set the mainProxy readonly to point to a
  // proxy for the Main chare object (this
  // chare object).
  mainProxy = thisProxy;

  // Create the array of Hello chare objects. NOTE: The
  // 'helloArray' object that is returned by 'ckNew()' is
  // actually a Proxy object to the array.
  CProxy_Hello helloArray = CProxy_Hello::ckNew(numElements);

  // Invoke the "sayHi()" entry method on the first
  // element of the helloArray array of chare objects.
  helloArray[0].sayHi(-1);
}

// Constructor needed for chare object migration (ignore for now)
// NOTE: This constructor does not need to appear in the ".ci" file
Main::Main(CkMigrateMessage* msg) { }

// When called, the "done()" entry method will cause the program
// to exit.
void Main::done() {
  CkExit();
}

#include "main.def.h"