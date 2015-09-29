#ifndef __JACOBI_H__
#define __JACOBI_H__

#include "jacobi.decl.h"

#include "common.h"


// NOTE: Contents of the Local Values Matrix
//   The values member variable points to the local
//   portion of the global values matrix.  There are
//   two extra rows and two extra columns to hold
//   "ghost" information.  Since the calculation
//   is to take an average of the element's value and
//   the element's four neighbor's values, for the chare
//   object to perform the calculation on its last
//   column (for example) it must have the first
//   column of the chare object to its east (x+1).
//   So, before a chare object can perform the calculation
//   it must first recieve some values from each of
//   its neighbors.  These peices of data are refered
//   to as "ghosts" or "ghost data".  They are exact
//   copies of the data in the other chare objects
//   which are used by this chare object to perform
//   the calculation localy (and are read-only in
//   this case).  The layout of the matrix pointed
//   to by values is visually presented below:
//
//   Key:
//     DDD : Local data (local portion of the values matrix)
//     NNN : North ghost data (last DDD row from y-1)
//     SSS : South ghost data (first DDD row from y+1)
//     EEE : East ghost data (first DDD column from x+1)
//     WWW : West ghost data (last DDD column from x-1)
//     --- : Don't care
//
//     <---- (valCols+2) ---->
//         <-- valCols -->
//
//     --- NNN NNN ... NNN ---            /\
//     WWW DDD DDD ... DDD EEE   /\        |
//     WWW DDD DDD ... DDD EEE    |        |
//     ... ... ... ... ... ...    valRows  (valRows+2)
//     WWW DDD DDD ... DDD EEE   \/        |
//     --- SSS SSS ... SSS ---            \/


class Jacobi : public CBase_Jacobi {

 private:

  /// Member Variables (Object State) ///
  double* values;              // Values matrix for this chare object
  double* tmpBuffer;           // General working buffer (used to send messages and do local portion of jacobi calculation)
  int calcCounterTarget;       // Number of events that need to occure before this chare is ready to start the calculation for this step (1 for sending ghosts, +1 for each ghost expected)
  int calcCounter;             // Number of events that have already occured this step (triggers calculation when it reaches the target value)

  #if DISPLAY_MATRIX != 0
    char* displayBuffer;
  #endif

  /// Member Functions (private) ///
  void attemptCalculation();
  double doStep();

 public:

  /// Constructors ///
  Jacobi();
  Jacobi(CkMigrateMessage *msg);
  ~Jacobi();

  /// Entry Methods ///
  void startStep();
  void eastGhost(int len, double* vals);
  void westGhost(int len, double* vals);
  void southGhost(int len, double* vals);
  void northGhost(int len, double* vals);

};


#endif //__JACOBI_H__
