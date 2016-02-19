/**********************************************************************
 *
 * sstTemplateLib - cpp template library for sst
 * Hosted on github
 *
 * Copyright (C) 2015 Uli Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstRec04CargoMem.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//=============================================================================
sstRec04CargoMemCls::sstRec04CargoMemCls()
{
  memset( &(*this), 0, sizeof((*this)));
}
//=============================================================================
sstRec04CargoMemCls::~sstRec04CargoMemCls()
{

}
//=============================================================================
int sstRec04CargoMemCls::GetOffset()
{
  return this->iOffset;
}
//=============================================================================
void sstRec04CargoMemCls::SetOffset(int iTmpOffset)
{
  this->iOffset = iTmpOffset;
}
//=============================================================================
int sstRec04CargoMemCls::GetCargoSize()
{
  return this->iSize;
}
//=============================================================================
void sstRec04CargoMemCls::SetCargoSize(int iTmpSize)
{
  this->iSize = iTmpSize;
}
//=============================================================================
char* sstRec04CargoMemCls::GetCargoSysNam()
{
  return this->cNam;
}
//=============================================================================
void sstRec04CargoMemCls::SetCargoSysNam(char *cTmpNam)
{
  strncpy(this->cNam,cTmpNam,dREC04CARGONAMMAXLEN);
}
//=============================================================================
void* sstRec04CargoMemCls::GetCargoAdr()
{
  return this->vCargoAdr;
}
//=============================================================================
void sstRec04CargoMemCls::SetCargoAdr(void *vTmpCargoAdr)
{
  this->vCargoAdr = vTmpCargoAdr;
}
//=============================================================================



