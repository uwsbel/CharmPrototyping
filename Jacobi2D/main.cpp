#include "main.h"
#include "jacobi.decl.h"
#include "common.h"

#include <stdlib.h>
#include <time.h>


/* readonly */ CProxy_Main mainProxy;
/* readonly */ int valRows;
/* readonly */ int valCols;
/* readonly */ int chareRows;
/* readonly */ int chareCols;


// Entry point of Charm++ application
Main::Main(CkArgMsg* msg) {

  // Set variables to their default values  
  valRows = DEFAULT_VALUE_ROWS;
  valCols = DEFAULT_VALUE_COLS;
  chareRows = DEFAULT_CHARE_ROWS;
  chareCols = DEFAULT_CHARE_COLS;
  threshold = DEFAULT_THRESHOLD;

  // Process the command line arguements
  switch (msg->argc) {
    case 1:
      break;
    case 3:
      valRows = atoi(msg->argv[1]);
      valCols = atoi(msg->argv[2]);
      break;
    case 5:
      valRows = atoi(msg->argv[1]);
      valCols = atoi(msg->argv[2]);
      chareRows = atoi(msg->argv[3]);
      chareCols = atoi(msg->argv[4]);
      break;
    case 6:
      valRows = atoi(msg->argv[1]);
      valCols = atoi(msg->argv[2]);
      chareRows = atoi(msg->argv[3]);
      chareCols = atoi(msg->argv[4]);
      threshold = atof(msg->argv[5]);
      break;
    default:
      CkPrintf("USAGE: %s [ A B [ C D [ E ] ] ]\n"
               "  where A (integer): value matrix rows per chare\n"
               "        B (integer): value matrix columns per chare\n"
               "        C (integer): chare matrix rows\n"
               "        D (integer): chare matrix columns\n"
               "        E    (real): threshold\n",
               msg->argv[0]
              );
      CkExit();
      break;
  }

  // We are done with msg so delete it.
  delete msg;

  // Display some info about this execution
  //   for the user.
  CkPrintf("Running \"2D Jacobi\" using %d processors.\n"
           "  Value matrix : [ %d x %d ] (per chare)\n"
           "                 [ %d x %d ] (overall)\n"
           "  Chare matrix : [ %d x %d ]\n"
           "  Threshold    : %lf\n",
           CkNumPes(), valRows, valCols,
           valRows * chareRows, valCols * chareCols,
           chareRows, chareCols,
           threshold
          );

  // Set the mainProxy readonly to point to a
  //   proxy for the Main chare object (this
  //   chare object).
  mainProxy = thisProxy;

  // Create the array of Jacobi chare objects.
  jacobiArray = CProxy_Jacobi::ckNew(chareRows, chareCols);

  // Start the first step
  startStep();
}


// Constructor needed for chare object migration (ignore for now)
// NOTE: This constructor does not need to appear in the ".ci" file
Main::Main(CkMigrateMessage* msg) { }


void Main::startStep() {

  // Reset the maximum difference value and checkinCount
  maxDiff = 0.0;
  checkinCount = 0;

  // Broadcast startStep() to the jacobiArray
  jacobiArray.startStep();
}


void Main::stepCheckin(double maxDiffValue) {

  // Compare maxDiffValue to the current maxDiff
  maxDiff = ((maxDiffValue > maxDiff) ? (maxDiffValue) : (maxDiff));

  // Increment the checkinCount and check to see if this is the last
  //   checkin for this particular step
  checkinCount++;
  if (checkinCount >= (chareRows * chareCols)) {

    // Display the global maxDiff value for this iteration
    CkPrintf("Main::stepCheckin() - maxDiff = %lf\n", maxDiff);

    #if DISPLAY_MATRIX != 0
      CkPrintf("------------------------------------------------------------\n");
    #endif

    // Check to see if another iteration is needed.  If so, start it.
    //   Otherwise, exit the program.
    if (maxDiff > threshold)
      startStep();
    else
      CkExit();
  }
}


#include "main.def.h"
