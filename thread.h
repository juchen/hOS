#ifndef _THREAD_H_
#define _THREAD_H_

struct Context
{
  DWORD _gs;
  DWORD _fs;
  DWORD _es;
  DWORD _ds;
  DWORD _edi;
  DWORD _esi;
  DWORD _edx;
  DWORD _ecx;
  DWORD _ebx;
  DWORD _eax;
  DWORD _eip;
  DWORD _cs;
  DWORD _eflags;
  DWORD _esp;
  DWORD _ss;
};

class Thread;

extern "C"{
unsigned int threadEntry(Thread *thread);
}

class Thread
{
private:
  Thread *_next;
  Context _context;
  BYTE *_stack;
  unsigned int _stackByteCnt;

  Thread(); // hide default constructor

protected:
public:
  Thread(BYTE *stack, unsigned int stackByteCnt);
  Thread *next() {return _next};
  virtual unsigned int threadProc();
  void setNext(Thread *next) { _next = next; };
  void 
};


class ThreadList
{
private:
  Thread *_head;
  Thread *_tail;
public:
  ThreadList():_head(0), _tail(0) {};
  void addToHead(Thead *t)
  {
    t->setNext(_head);
    _head = t;
    if(t->next() == 0)
    {
      _tail = t;
    }
  }
  Thread *popFromHead()
  {
    Thread *r = _head;
    if(_head != 0)
    {
      _head = _head->next();
      r->setNext(0);
    }
    if(_head == 0)
    {
      _tail = 0;
    }
    return r;
  }
  void addToTail(Thread *t)
  {
    if(_tail == 0)
    {
      ASSERT(_head == 0);
      _head = t;
      _tail = t;
    }
    else
    {
      _tail->setNext(t);
      _tail = t;
    }
    _tail->setNext(0);
  }
  Thread *popFromTail()
  {
    Thread *r = _tail;
    for(Thread *t = _head; t->next() != _tail; t = t->next())
    {
    }
    t->setNext(0);
    _tail = t;
    return r;
  }
};

#endif // _THREAD_H_
