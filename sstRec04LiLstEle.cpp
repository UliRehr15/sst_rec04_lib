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
// sstRec04LiLstEle.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

// Complete function description is in headerfile
//-----------------------------------------------------------------------------
sstRec04LiLstEleCls::sstRec04LiLstEleCls()
{
  master = 0;
  ulPrev = 0;    // nachbar[1]
  ulNext = 0;    // nachbar[0]
  ulTarget = 0;  // Element in Target list
}
//=============================================================================
int sstRec04LiLstEleCls::SetMaster(int iKey,  dREC04RECNUMTYP  dTmpMaster)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  master = dTmpMaster;
  return 0;
}
//=============================================================================
int sstRec04LiLstEleCls::SetPrev(int iKey,  dREC04RECNUMTYP  dTmpPrev)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  ulPrev = dTmpPrev;
  return 0;
}
//=============================================================================
int sstRec04LiLstEleCls::SetNext(int iKey,  dREC04RECNUMTYP  dTmpNext)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  ulNext = dTmpNext;
  return 0;
}
//=============================================================================
int sstRec04LiLstEleCls::SetTarget(int iKey,  dREC04RECNUMTYP  dTmpTarget)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  ulTarget = dTmpTarget;
  return 0;
}
//=============================================================================
int sstRec04LiLstEleCls::Set(int           iKey,
                        dREC04RECNUMTYP  dTmpMaster,
                        dREC04RECNUMTYP  dTmpPrev,
                        dREC04RECNUMTYP  dTmpNext)
{
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  master = dTmpMaster;
  ulPrev = dTmpPrev;  // nachbar[1]
  ulNext = dTmpNext;  // nachbar[0]
  return 0;
}
//=============================================================================
 dREC04RECNUMTYP sstRec04LiLstEleCls::GetMaster()
{
  return master;
}
//=============================================================================
 dREC04RECNUMTYP sstRec04LiLstEleCls::GetPrev()
{
  return ulPrev;
}
//=============================================================================
 dREC04RECNUMTYP sstRec04LiLstEleCls::GetNext()
{
  return ulNext;
}
//=============================================================================
 dREC04RECNUMTYP sstRec04LiLstEleCls::GetTarget()
{
  return ulTarget;
}
//=============================================================================

