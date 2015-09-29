#include "main.decl.h" 
#include "main.h"

// Entry point of Charm++ application
Main::Main(CkArgMsg* msg) 
{
    // Print a message for the user
    CkPrintf("Hello World!\n");
    // Exit the application --> This is needed. It does not work like normal C/C++ that just returning will do the job.
   
    CkExit();
}

// Simple::Simple(double pi)
// {
//     //CkPrintf("From chare on %d Area of a circle radius %d is %g\n", CkMyPe(), x, y*x*x);
//     CkExit();
// }
// void Simple::findArea(double radius, bool done)
// {

// }

// Constructor needed for chare object migration (ignore
// for now) NOTE: This constructor does not need to
// appear in the ".ci" file
Main::Main(CkMigrateMessage* msg) { }

#include    "main.def.h"   

