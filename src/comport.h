#ifndef _COMPORT_H_
#define _COMPORT_H_
#include "types.h"

//class IComPort
//{
//public:
//  virtual void transChar(char c) = 0;
//  virtual bool isTransEmpty() = 0;
//};

//class ComPort : public IComPort
class ComPort
{
public:
  ComPort(unsigned int baseRegAddr);
  ComPort();
  void initHW();
  void setBaudRate(unsigned int baudRate);
  virtual void transChar(char c);
  virtual BYTE recvChar();
  virtual bool isTransEmpty();
  virtual bool isDataReady();
private:
  unsigned int _baseRegAddr;
  BYTE _lineControl;

  void setBRDL(BYTE b); // Baud Rate Lo (LSB) Register.
  void setBRDH(BYTE b); // Baud Rate Hi (MSB) Register.
  void setLCR(BYTE b); // Line Control Register
  BYTE getLST(); // Line Status Register
  void setTHR(BYTE b); // Transmit Empty Register
  BYTE getRDR(); // Receive Data Register
  void setIER(BYTE b); // Interrupt Enable Register
  BYTE getIID(); // Interrupt ID Register.
  enum LineControlBits
  {
    DLAB = 0x80, // Divisor latch access bit.
    STOP_BIT_1 = 0,
    WORD_LEN_8_BIT = 0x03,
    WORD_LEN_7_BIT = 0x02,
    WORD_LEN_6_BIT = 0x01,
    WORD_LEN_5_BIT = 0,
    PARITY_NONE = 0,
    PARITY_EVEN = 0x18,
    PARITY_ODD = 0x08,
  };
  enum LineStatusBits
  {
    THR_EMPTY = (1 << 5),
    RDR_FULL  = (1 << 0),
  };
};

#endif /* _COMPORT_H_ */
