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
// sstRec04LiLst.cpp    19.11.15  Re.    18.11.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"


//=============================================================================
sstRec04LiLstCls::sstRec04LiLstCls()
{
  poRec04LiLstInt = new sstRec04LiLstIntCls();
}
//==============================================================================
sstRec04LiLstCls::~sstRec04LiLstCls() {
    delete(poRec04LiLstInt);
}
//==============================================================================
int sstRec04LiLstCls::Define3(int                iKey,
                                 sstRec04Cls *Dss1,
                                 sstRec04Cls *Dss2,
                                 sstRec04Cls *Dss3)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->Define3(iKey,Dss1,Dss2,Dss3);
}
//==============================================================================
int sstRec04LiLstCls::getEntriesInLinkList ( int              iKey,
                                             dREC04RECNUMTYP  dRecNoHed,
                                             dREC04RECNUMTYP *dEntry1,
                                             dREC04RECNUMTYP *dEntry2)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->getEntriesInLinkList(iKey,dRecNoHed,dEntry1,dEntry2);
}
//==============================================================================
int sstRec04LiLstCls::ListNodeGetEleAll (int              iKey,
                                         dREC04RECNUMTYP  dRecNoEle,
                                         dREC04RECNUMTYP *dMaster,
                                         dREC04RECNUMTYP *dNext,
                                         dREC04RECNUMTYP *dPrev,
                                         dREC04RECNUMTYP *dTarget)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->ListNodeGetEleAll(iKey,dRecNoEle,dMaster,dNext,dPrev,dTarget);
}
//=============================================================================
int sstRec04LiLstCls::ExtendAtEnd(int             iKey,
                                  dREC04RECNUMTYP dRecNoHead,
                                  dREC04RECNUMTYP dRecNoEle,
                                  dREC04RECNUMTYP dRecNoTarget)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->ExtendAtEnd( iKey,  dRecNoHead, dRecNoEle, dRecNoTarget);
}
//=============================================================================
int sstRec04LiLstCls::GetHedListLength (int              iKey,
                                        dREC04RECNUMTYP  dRecNoHed,
                                        dREC04RECNUMTYP *dListLength)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->GetHedListLength ( iKey, dRecNoHed, dListLength);
}
//=============================================================================
int sstRec04LiLstCls::GetTarNumUse (int              iKey,
                                    dREC04RECNUMTYP  dRecNoTar,
                                    dREC04RECNUMTYP *dNumUse)
//-----------------------------------------------------------------------------
{
  return this->poRec04LiLstInt->GetTarNumUse(iKey,dRecNoTar,dNumUse);
}
//=============================================================================
