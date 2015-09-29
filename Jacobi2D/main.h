#ifndef __MAIN_H__
#define __MAIN_H__

#include "main.decl.h"
#include "jacobi.decl.h"


class Main : public CBase_Main {

 private:

  /// Member Variables (Object State) ///
  double threshold;     // Threshold value to end calculation
  int checkinCount;     // Number of chare objects that have finished the current step
  double maxDiff;       // Global maxDiff value for the current step
  CProxy_Jacobi jacobiArray;  // Prefix array proxy

  /// Private Member Functions ///
  void startStep();

 public:

  /// Constructors ///
  Main(CkArgMsg* msg);
  Main(CkMigrateMessage* msg);

  /// Entry Methods ///
  void stepCheckin(double maxDiffValue);
};


#endif //__MAIN_H__
