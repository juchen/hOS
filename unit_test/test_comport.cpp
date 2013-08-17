#include "comport.h"
#include "stdio.h"
#include "assert.h"

#define ASSERT(x) assert(x)

// need to emulation the hardware to test the queue.

class CharRingBuf
{
private:
  enum {
    RING_SIZE =1024,
  };

public:
  CharRingBuf(); // constructor
  void push(char a);
  char pop();
  bool isEmpty() { return (e <= b); }
  bool isFull() { return (e - b) >= RING_SIZE; }

private:
  char buf[RING_SIZE];
  int b;
  int e;
};

CharRingBuf::CharRingBuf()
  : b(0), e(0)
{
}

void CharRingBuf::push(char a)
{
  if((e - b) < RING_SIZE)
  {
    buf[(e++)%RING_SIZE] = a;
  }
  else
  {
    // Do nothing because of buffer overflow.
  }
}

char CharRingBuf::pop()
{
  char r = buf[(b++)%RING_SIZE];
  if(b >= RING_SIZE)
  {
    int c;
    c = (b / RING_SIZE) * RING_SIZE;
    b -= c;
    e -= c;
  }
  return r;
}

class BufferredComOut
{
public:
  BufferredComOut(CharRingBuf *charRingBuf, IComPort *comPort);
  void putChar(char c);
  void outputChar();
private:
  CharRingBuf *m_charRingBuf;
  IComPort *m_comPort;
  void oneCharToComport(char c)
  {
    m_comPort->transChar(c);
  }

  bool hwTHIsEmpty()
  {
    return m_comPort->isTransEmpty();
  }
#warning Need to implemented these two function when really used in system.
  void comportLock() {}
  void comportUnLock() {}
};

BufferredComOut::BufferredComOut(CharRingBuf *charRingBuf, IComPort *comPort)
  : m_charRingBuf(charRingBuf),
    m_comPort(comPort)
{
}

void BufferredComOut::putChar(char c)
{
  comportLock();
  if(m_charRingBuf->isFull() && hwTHIsEmpty())
  {
    oneCharToComport(m_charRingBuf->pop());
    m_charRingBuf->push(c);
  }
  else if(m_charRingBuf->isFull()) // not hwTHIsEmpty()
  {
    // Do nothing because of overflow.
  }
  else if(hwTHIsEmpty())
  {
    m_charRingBuf->push(c);
    oneCharToComport(m_charRingBuf->pop());
  }
  else
  {
    m_charRingBuf->push(c);
  }
  comportUnLock();
}

void BufferredComOut::outputChar()
{
  if(m_charRingBuf->isEmpty())
  {
    // Do nothing because of underflow.
  }
  else
  {
    comportLock();
    if(hwTHIsEmpty())
    {
      oneCharToComport(m_charRingBuf->pop());
    }
    else
    {
      // Strange! Should be something wrong!
      ASSERT(false);
    }
    comportUnLock();
  }
}

class FakeComPort : public IComPort
{
public:
  FakeComPort()
    : m_TH(0),
      m_THEmpty(true),
      m_bufferredComOut(0)
  {
  }
  virtual void transChar(char c)
  {
    m_TH = c;
    m_THEmpty = false;
  }
  virtual bool isTransEmpty()
  {
    return m_THEmpty;
  }
  bool takeChar(char *c)
  {
    if(m_THEmpty)
    {
      return false;
    }
    else
    {
      m_THEmpty = true;
      *c = m_TH;
      m_bufferredComOut->outputChar();
      return true;
    }
  }
  void setBufferredComOut(BufferredComOut *bco)
  {
    m_bufferredComOut = bco;
  }
private:
  bool m_THEmpty;
  char m_TH;
  BufferredComOut *m_bufferredComOut;
};

bool test_normal()
{
  char *in = "Test input message.";
  char out[2048];
  char *i;
  CharRingBuf *crb = new CharRingBuf;
  FakeComPort *fcp = new FakeComPort;
  BufferredComOut *bco = new BufferredComOut(crb, fcp);
  fcp->setBufferredComOut(bco);
  for(i = in; (*i) !=0; ++i)
  {
    bco->putChar(*i);
  }

  for(i = out; (fcp->takeChar(i) && i < (out + 2048)); ++i)
  {
  }
  *i = 0;

  printf("Input: %s\n", in);
  printf("Result: %s\n", out);
  delete bco;
  delete fcp;
  delete crb;

  return true;
}

int main(int argc, char **argv)
{
  test_normal();
  return 0;
}





