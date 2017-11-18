#include "stdafx.h"

#include "Checksum.h"

/****************************************************************************
*                                  checksum::add
* Inputs:
*        DWORD d: word to add
* Result: void
* 
* Effect: 
*        Adds the bytes of the DWORD to the checksum
****************************************************************************/

void checksum::add(DWORD value)
{
 union { DWORD value; BYTE bytes[4]; } data;
 data.value = value;
 for(UINT i = 0; i < sizeof(data.bytes); i++)
    add(data.bytes[i]);
} // checksum::add(DWORD)

/****************************************************************************
*                                 checksum::add
* Inputs:
*        WORD value:
* Result: void
* 
* Effect: 
*        Adds the bytes of the WORD value to the checksum
****************************************************************************/

void checksum::add(WORD value)
{
 union { DWORD value; BYTE bytes[2]; } data;
 data.value = value;
 for(UINT i = 0; i < sizeof(data.bytes); i++)
   add(data.bytes[i]);
} // checksum::add(WORD)

/****************************************************************************
*                                 checksum::add
* Inputs:
*        BYTE value:
* Result: void
* 
* Effect: 
*        Adds the byte to the checksum
****************************************************************************/

void checksum::add(BYTE value)
{
 BYTE cipher = (value ^ (r >> 8));
 r = (cipher + r) * c1 + c2;
 sum += cipher;
} // checksum::add(BYTE)

/****************************************************************************
*                                 checksum::add
* Inputs:
*        const CString & s: String to add
* Result: void
* 
* Effect: 
*        Adds each character of the string to the checksum
****************************************************************************/

void checksum::add(const CString & s)
{
 for(int i = 0; i < s.GetLength(); i++)
    add((BYTE)s.GetAt(i));
} // checksum::add(CString)

/****************************************************************************
*                                 checksum::add
* Inputs:
*        LPBYTE b: pointer to byte array
*        UINT length: count
* Result: void
* 
* Effect: 
*        Adds the bytes to the checksum
****************************************************************************/

void checksum::add(LPBYTE b, UINT length)
{
for(UINT i = 0; i < length; i++)
   add(b[i]);
} // checksum::add(LPBYTE, UINT)