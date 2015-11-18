/**********************************************************************
 *
 * sst_rec_lib - library for working with data records
 * Hosted on github
 *
 * Copyright (C) 2015 Hans Ulrich Rehr
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstRec04TestRec.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//==============================================================================
sstRec04TestRec1Cls::sstRec04TestRec1Cls()
{
  this->iValue = 0;
  memset(this->cVal,0,sizeof(this->cVal));
}
//=============================================================================
int sstRec04TestRec1Cls::SetAllValues(int iTmpVal, char *cTmpVal)
{
  iValue = iTmpVal;
  strncpy(cVal,cTmpVal,10);
  return 0;
}
//==============================================================================
sstRec04TestRec2Cls::sstRec04TestRec2Cls()
{
  this->iValue = 0;
  this->uiValue = 0;
  this->dValue = 0.0;
  memset(this->cVal,0,sizeof(this->cVal));
}
//==============================================================================
