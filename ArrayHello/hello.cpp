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
  int numRows = 200;
  int numCols = 400;
  int sample[numRows][numCols];

  if(thisIndex % 4 == 0)
  {
    //CkPrintf("%d mod 4 == 0\n",thisIndex);
    for(int currRow = 0;currRow < numRows;currRow++)
    {
      for(int currCol = 0;currCol < numCols;currCol++)
      {
        int currIndex = currCol + currRow*numCols;
        sample[currRow][currCol] = currIndex;
      }
    }
    // Have this chare object say hello to the user.
    CkPrintf("\"Hello\" from Hello chare # %d on "
           "processor %d (told by %d). I am divisible by 4 \n",
           thisIndex, CkMyPe(), from);
  }
  else if (thisIndex % 3 == 0)
  {
    //CkPrintf("%d mod 3 == 0\n",thisIndex);

    for(int currCol = 0;currCol < numCols;currCol++)
    {
      for(int currRow = 0;currRow < numRows;currRow++)
      {
        int currIndex = currCol + currRow*numCols;
        sample[currRow][currCol] = currIndex;
      }
    }
    // Have this chare object say hello to the user.
    CkPrintf("\"Hello\" from Hello chare # %d on "
           "processor %d (told by %d). I am divisible by 3 \n",
           thisIndex, CkMyPe(), from);
  }
  else
  {
    CkPrintf("\"Hello\" from Hello chare # %d on "
           "processor %d (told by %d). I am not divisible by 4 or 3 \n",
           thisIndex, CkMyPe(), from);  
  }



  // Tell the next chare object in this array of chare objects
  // to also say hello. If this is the last chare object in
  // the array of chare objects, then tell the main chare
  // object to exit the program.
  // if (thisIndex < (numElements - 1))
  //   thisProxy[thisIndex + 1].sayHi(thisIndex);
  // else
  mainProxy.done();
}

#include "hello.def.h"