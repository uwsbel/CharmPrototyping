#ifndef __MAIN_H__
#define __MAIN_H__

class Main : public CBase_Main 
{ 
    public:
        Main(CkArgMsg* msg); 
        Main(CkMigrateMessage* msg); 
};

// class Simple : public CBase_Simple
// {
//     public:
        
//         Simple(double pi);
//         void findArea(double radius, bool done);
// };

#endif //__MAIN_H__