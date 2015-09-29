#ifndef __HELLO_H__
#define __HELLO_H__

class Hello : public CBase_Hello {

 public:

  /// Constructors ///
  Hello();
  Hello(CkMigrateMessage *msg);

  /// Entry Methods ///
  void sayHi(int from);
};

#endif //__HELLO_H__