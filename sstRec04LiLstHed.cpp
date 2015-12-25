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
// sstRec04LiLstHed.cpp    22.12.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//=============================================================================
sstRec04LiLstHedCls::sstRec04LiLstHedCls()
{
  this->chain_loc[0] = 0;
  this->chain_loc[1] = 0;
  this->dNumListElements = 0;
}
//=============================================================================
int sstRec04LiLstHedCls::SetEntry1(int iKey,  dREC04RECNUMTYP dTmpEntry1)
{
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  this->chain_loc[0] = dTmpEntry1;
  return 0;
}
//=============================================================================
int sstRec04LiLstHedCls::SetEntry2(int iKey,  dREC04RECNUMTYP dTmpEntry2)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  this->chain_loc[1] = dTmpEntry2;
  return 0;
}
//=============================================================================
dREC04RECNUMTYP sstRec04LiLstHedCls::GetEntry1()
{
  return this->chain_loc[0];
}
//=============================================================================
dREC04RECNUMTYP sstRec04LiLstHedCls::GetEntry2()
{
  return this->chain_loc[1];
}
//=============================================================================
void sstRec04LiLstHedCls::AddElement()
{
  this->dNumListElements++;
}
//=============================================================================
void sstRec04LiLstHedCls::ReduceElement()
{
  this->dNumListElements--;
}
//=============================================================================
dREC04RECNUMTYP sstRec04LiLstHedCls::GetNumListElements()
{
  return this->dNumListElements;
}
//=============================================================================

