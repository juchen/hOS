#include "comport.h"
#include "x86functions.h"

ComPort::ComPort(unsigned int baseRegAddr)
  : _baseRegAddr(baseRegAddr),
  _lineControl(PARITY_NONE + WORD_LEN_8_BIT + STOP_BIT_1)
{
  initHW();
}

ComPort::ComPort()
  : _baseRegAddr(0x3f8),
  _lineControl(PARITY_NONE + WORD_LEN_8_BIT + STOP_BIT_1)
{
  initHW();
}

void ComPort::initHW()
{
  setLCR(_lineControl);
  setBaudRate(115200);
}

void ComPort::setBaudRate(unsigned int baudRate)
{
  int divisor = 115200/baudRate;
  if(divisor < 1) divisor = 1;
  if(divisor > 12) divisor = 12;
  setBRDL(divisor & 0xFF);
  setBRDH((divisor >> 8) & 0xFF);
}

void ComPort::setLCR(BYTE b)
{
  outb(_baseRegAddr + 3, b);
}

void ComPort::setBRDL(BYTE b)
{
  setLCR(_lineControl | DLAB); // set DLAB.
  outb(_baseRegAddr, b);
  setLCR(_lineControl & (~DLAB)); // clear DLAB.
}

void ComPort::setBRDH(BYTE b)
{
  setLCR(_lineControl | DLAB); // set DLAB.
  outb(_baseRegAddr + 1, b);
  setLCR(_lineControl & (~DLAB)); // clear DLAB.
}


BYTE ComPort::getLST()
{
  return inb(_baseRegAddr + 5);
}

void ComPort::setTHR(BYTE b)
{
  outb(_baseRegAddr, b);
}

BYTE ComPort::getRDR()
{
  return inb(_baseRegAddr);
}

void ComPort::setIER(BYTE b)
{
  outb(_baseRegAddr, b);
}

BYTE ComPort::getIID()
{
  return inb(_baseRegAddr);
}

void ComPort::transChar(char c)
{
  while(!isTransEmpty())
  {
    // just wait.
  }
  setTHR(c);
}

BYTE ComPort::recvChar()
{
    while(!isDataReady()) {
        // just wait.
    }
    return getRDR();
}

bool ComPort::isTransEmpty()
{
  unsigned int st = getLST();
  return (THR_EMPTY == (THR_EMPTY & st));
}

bool ComPort::isDataReady()
{
  unsigned int st = getLST();
  return (RDR_FULL == (RDR_FULL & st));
}

