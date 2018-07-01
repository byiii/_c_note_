#include <iostream>
#include <cstdint>

#include <memory.h>

struct Node_T {
    uint32_t p;
    uint32_t n;
    int * d;
};

template<int CAP>
struct ArrListData_T {
    static const uint32_t cap = CAP;
    Node_T buf[CAP];
    uint32_t s;
};

class ArrList_T {
private:
    ArrList_T();
    int & operator=(ArrList_T &another);

public:
    ArrList_T(const uint32_t _c, uint32_t * _s, Node_T *_b)
        : cap(_c),
          psize(_s),
          pbuf(_b),
          _nil({_c, _c, nullptr})
    {}
    virtual ~ArrList_T()
    {}

    inline void init() {
        uint32_t i;
        uint32_t end_i = cap - 1;
        Node_T *ptmp;
        memset(pbuf, 0, sizeof(Node_T)*cap);
        for(i=0; i<end_i; ++i) {
            ptmp = pbuf + i;
            ptmp->p = cap;
            ptmp->n = i+1;
            ptmp->d = nullptr;
        }
        (pbuf + end_i)->p = cap;
        (pbuf + end_i)->n = cap;
        (pbuf + end_i)->d = nullptr;

        *psize = 0;
        head_i = cap;
        tail_i = cap;
        free_i = 0;
    }
    inline void clear() {
        init();
    }
    inline uint32_t prev_i(int i) {
        return (pbuf + i)->p;
    }
    inline uint32_t next_i(int i) {
        return (pbuf + i)->n;
    }
    inline int * gdata(int i) {
        return (pbuf + i)->d;
    }
    inline int * prev(int i) {
        return (pbuf + (pbuf + i)->p)->d;
    }
    inline int * next(int i) {
        return (pbuf + (pbuf + i)->n)->d;
    }
    inline uint32_t head() const {
        return head_i;
    }
    inline uint32_t tail() const {
        return tail_i;
    }
    inline uint32_t free_node() const {
        return free_i;
    }
    inline uint32_t size() const {
        return *psize;
    }

    int insert(int pre, int *pd);
    int erase(int i);
    int append(int *pd);
    int swap(int ia, int ib, int mode);
    int check();

private:
    const uint32_t cap;
    uint32_t * const psize;
    Node_T *pbuf;

    uint32_t head_i;
    uint32_t tail_i;

    uint32_t free_i;

    Node_T _nil;
};

/* ------------------------------------------------------------
 */
int ArrList_T::insert(int pre, int *pd) {
    Node_T *cn;
    Node_T *pn;
    Node_T *nn;

    if(*psize >= cap)
        return 1;

    cn = pbuf + free_i;
    free_i = cn->n;

    cn->d = pd;
    if(pre == -1) {
        if(head_i == cap) {
            /* psize must be 0 */
            head_i = 0;
            tail_i = 0;
            *psize = 1;
        } else {
            cn->n = head_i;
            (pbuf + head_i)->p = *psize;
            head_i = *psize;
            *psize += 1;
        }

        return 0;
    }

    cn->p = pre;
    pn = pbuf + pre;
    pn->n = *psize;
    cn->n = pn->n;
    if(pre == (int)tail_i) {
        tail_i = *psize;
        cn->n = cap;
    } else {
        nn = pbuf + pn->n;
        nn->p = *psize;
    }
    *(psize) += 1;

    return 0;
}

/* ------------------------------------------------------------
 */
int ArrList_T::erase(int i) {
    Node_T *pn;
    Node_T *nn;
    Node_T *cn;

    if(i>=(int)cap || i<0)
        return 1;

    /* erase head */
    if(i == (int)head_i) {
        cn = pbuf + head_i;
        nn = pbuf + cn->n;
        head_i = cn->n;
        nn->p = cap;

        cn->p = cap;
        cn->d = nullptr;
        cn->n = free_i;
        free_i = i;

        *psize -= 1;
        return 0;
    }
    /* erase tail */
    if(i == (int)tail_i) {
        cn = pbuf + tail_i;
        pn = pbuf + cn->p;
        tail_i = cn->p;
        pn->n = cap;

        cn->p = cap;
        cn->d = nullptr;
        cn->n = free_i;
        free_i = i;

        *psize -= 1;
        return 0;
    }

    /* erase interval */
    cn = pbuf + i;
    nn = pbuf + cn->n;
    pn = pbuf + cn->p;
    pn->n = cn->n;
    nn->p = cn->p;

    cn->p = cap;
    cn->n = free_i;
    cn->d = nullptr;
    free_i = i;

    *psize -= 1;
    return 0;
}

/* ------------------------------------------------------------
 */
int ArrList_T::append(int *pd) {
    Node_T *cn;

    if((*psize) >= cap)
        return 1;

    cn = pbuf + free_i;
    cn->p = tail_i;
    cn->d = pd;
    (pbuf + tail_i)->n = free_i;
    tail_i = free_i;
    free_i = cn->n;
    cn->n = cap;

    *psize += 1;

    return 0;
}

/* ------------------------------------------------------------
 */
/* TODO: int swap(int ia, int ib)
 */
int ArrList_T::swap(int ia, int ib, int mode) {
    Node_T tmp_node;
    int c_h, c_t;

    if(ia == ib)
        return 0;

    memcpy(&tmp_node, (pbuf+ia), sizeof(Node_T));
    memcpy((pbuf+ia), (pbuf+ib), sizeof(Node_T));
    memcpy((pbuf+ib), &tmp_node, sizeof(Node_T));

    /* originally ib is nil node */
    if(mode) {
        if(ia == tail_i) {
            /* constraint: (pbuf + (pbuf + ib)->p)->n == ia */
            (pbuf + (pbuf + ib)->p)->n = ib;
            tail_i = ib;
            return 0;
        }
        if(ia == head_i) {
            head_i = ib;
            /* constraint: (pbuf + (pbuf + ib)->n)->p == ia */
            (pbuf + (pbuf + ib)->n)->p = ib;
            return 0;
        }

        /* constraint: (pbuf + (pbuf + ib)->p)->n == ia */
        (pbuf + (pbuf + ib)->p)->n = ib;
        /* constraint: (pbuf + (pbuf + ib)->n)->p == ia */
        (pbuf + (pbuf + ib)->n)->p = ib;
        return 0;
    }
    c_h = head_i;
    c_t = tail_i;
    /* ia and ib are normal nodes */
    if(ia == c_h) head_i = ib;
    if(ib == c_h) head_i = ia;
    if(ia == c_t) tail_i = ib;
    if(ib == c_t) tail_i = ia;

    if((pbuf + ib)->n == ib) {
        /* originally ia is predicessor of ib */
        /* constraint: (pbuf + (pbuf + ib)->p)->n == ia */
        if(((pbuf + ib)->p) < cap)
            (pbuf + (pbuf + ib)->p)->n = ib;

        (pbuf + ib)->n = ia;
        (pbuf + ia)->p = ib;

        /* constraint: (pbuf + (pbuf + ia)->n)->p == ib */
        if(((pbuf + ia)->n) < cap)
            (pbuf + (pbuf + ia)->n)->p = ia;

        return 0;
    }
    if((pbuf + ia)->n == ia) {
        /* originally ib is predicessor of ia */
        if(((pbuf + ia)->p) < cap)
            (pbuf + (pbuf + ia)->p)->n = ia;

        (pbuf + ia)->n = ib;
        (pbuf + ib)->p = ia;

        /* constraint: (pbuf + (pbuf + ia)->n)->p == ib */
        if(((pbuf + ib)->n) < cap)
            (pbuf + (pbuf + ib)->n)->p = ib;

        return 0;
    }
    /* constraint: (pbuf + (pbuf + ia)->p)->n == ib */
    if(((pbuf + ia)->p) < cap)
        (pbuf + (pbuf + ia)->p)->n = ia;

    /* constraint: (pbuf + (pbuf + ia)->n)->p == ib */
    if(((pbuf + ia)->n) < cap)
        (pbuf + (pbuf + ia)->n)->p = ia;

    /* constraint: (pbuf + (pbuf + ib)->p)->n == ia */
    if(((pbuf + ib)->p) < cap)
        (pbuf + (pbuf + ib)->p)->n = ib;

    /* constraint: (pbuf + (pbuf + ib)->n)->p == ia */
    if(((pbuf + ib)->n) < cap)
        (pbuf + (pbuf + ib)->n)->p = ib;

    return 0;
}

/* ------------------------------------------------------------
 */
int ArrList_T::check() {
    /* check circle
     */
    Node_T *pt;
    int i = 0;
    int s = *psize;
    for(i=0; i<s; ++i) {
        pt = pbuf + i;
        if(pt->p == pt->n && pt->p < cap)
            return 1;
    }
    return 0;
}

/* ------------------------------------------------------------
 */
void show_arr_list(Node_T *buf, uint32_t cap)
{
    uint32_t i;
    for(i=0; i<cap; ++i) {
        if((buf+i)->d)
            printf("[%u, %d, %u]\n", (buf+i)->p, *((buf+i)->d), (buf+i)->n);
        else
            printf("[%u, nil, %u]\n", (buf+i)->p, (buf+i)->n);
    }
}

/* ------------------------------------------------------------
 */
int main() {
    using namespace std;
    cout << "hello" << endl;

    int arr[] = {13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    const uint32_t CAPACITY = 5;
    ArrListData_T<CAPACITY> ldata;
    ArrList_T al(CAPACITY, &ldata.s, ldata.buf);

    al.init();
    show_arr_list(ldata.buf, CAPACITY);

    ldata.buf[0].p = CAPACITY;
    ldata.buf[0].n = 1;
    ldata.buf[0].d = &arr[0];
    ldata.buf[1].p = 0;
    ldata.buf[1].n = CAPACITY;
    ldata.buf[1].d = &arr[1];

    show_arr_list(ldata.buf, CAPACITY);

    cout << *al.prev(1) << endl;
    cout << al.prev_i(1) << endl;
    cout << *al.next(0) << endl;
    cout << al.next_i(0) << endl;

    cout << "clear" << endl;
    al.clear();

    cout << "insert before head " << endl;
    al.insert(-1, &arr[2]);
    cout << "h.1 " << al.head() << endl;
    cout << "t.1 " << al.tail() << endl;
    cout << "f.1 " << al.free_node() << endl;
    cout << "s.1 " << al.size() << endl;

    cout << "insert before head " << endl;
    al.insert(-1, &arr[1]);
    cout << "h.2 " << al.head() << endl;
    cout << "t.2 " << al.tail() << endl;
    cout << "f.2 " << al.free_node() << endl;
    cout << "s.2 " << al.size() << endl;
    show_arr_list(ldata.buf, CAPACITY);

    cout << "insert after pos 0 " << endl;
    al.insert(0, &arr[3]);
    show_arr_list(ldata.buf, CAPACITY);
    cout << "h.3 " << al.head() << endl;
    cout << "t.3 " << al.tail() << endl;
    cout << "f.3 " << al.free_node() << endl;
    cout << "s.3 " << al.size() << endl;

    cout << "erase head " << endl;
    al.erase(al.head());
    show_arr_list(ldata.buf, CAPACITY);
    cout << "h.4 " << al.head() << endl;
    cout << "t.4 " << al.tail() << endl;
    cout << "f.4 " << al.free_node() << endl;
    cout << "s.4 " << al.size() << endl;

    cout << "append " << endl;
    al.append(&arr[4]);
    show_arr_list(ldata.buf, CAPACITY);
    cout << "h.5 " << al.head() << endl;
    cout << "t.5 " << al.tail() << endl;
    cout << "f.5 " << al.free_node() << endl;
    cout << "s.5 " << al.size() << endl;

    cout << "swap pos 0, 2 " << endl;
    al.swap(0, 2, 0);
    show_arr_list(ldata.buf, CAPACITY);
    cout << "h.6 " << al.head() << endl;
    cout << "t.6 " << al.tail() << endl;
    cout << "f.6 " << al.free_node() << endl;
    cout << "s.6 " << al.size() << endl;

    cout << "append " << endl;
    al.append(&arr[5]);
    al.append(&arr[6]);
    show_arr_list(ldata.buf, CAPACITY);

    cout << "swap pos 0, 2 " << endl;
    al.swap(0, 2, 0);
    show_arr_list(ldata.buf, CAPACITY);
    cout << "h.7 " << al.head() << endl;
    cout << "t.7 " << al.tail() << endl;
    cout << "f.7 " << al.free_node() << endl;
    cout << "s.7 " << al.size() << endl;

    return 0;
}
