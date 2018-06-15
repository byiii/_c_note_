#include <iostream>
#include <cstdint>

using namespace std;

template<int CAP>
struct ArrListData_T {
  static const uint32_t CAPACITY = CAP;
  
  uint16_t p[CAP];
  uint16_t n[CAP];
  int * d[CAP];
};

typedef ArrListData_T<3> ArrListData_3_T;

class ArrList_T {
private:
    ArrList_T();
public:
    ArrList_T(uint16_t cap, uint16_t *p, uint16_t *n, int **d)
      : CAPACITY(cap),
        prev(p),
        next(n),
        data(d)
    {}
    
    ~ArrList_T()
    {}
    
    const uint16_t CAPACITY;
    inline int * pd(uint16_t index) {
        if(index >= CAPACITY)
            return nullptr;
        return (int *)(*(data + (*(prev+index))));
    }
    inline uint16_t pi(uint16_t index) {
        if(index >= CAPACITY)
            return CAPACITY;
        return *(prev + index);
    }
    inline int * gd(uint16_t index) {
        if(index >= CAPACITY)
            return nullptr;
        return (int *)(*(data + index));
    }
private:
    uint16_t * const prev;
    uint16_t * const next;
    int ** const data;
};

int main()
{
   cout << "Hello World" << endl; 
   
   ArrListData_3_T ld;
   ArrList_T al(ld.CAPACITY, ld.p, ld.n, &ld.d[0]);
   
   int array[3] = {1, 2, 3};
   
   ld.p[0] = ld.CAPACITY;
   ld.n[0] = 1;
   ld.d[0] = &array[0];
   ld.p[1] = 0;
   ld.n[1] = 2;
   ld.d[1] = &array[1];
   ld.p[2] = 1;
   ld.n[2] = ld.CAPACITY;
   ld.d[2] = &array[3];
   
   cout << al.gd(0) << endl;
   cout << *(al.gd(0)) << endl;
   cout << (al.pd(1)) << endl;
   cout << al.pi(0) << endl;
   
   return 0;
}