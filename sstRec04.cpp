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
// sstRec04.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <string>

#include "sstStr01Lib.h"
#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//==============================================================================
sstRec04Cls::sstRec04Cls(dREC04RECSIZTYP Size) {
  poRec01Intern = new sstRec04InternCls(Size);
}
//==============================================================================
sstRec04Cls::~sstRec04Cls() {
    delete(poRec01Intern);
}
//==============================================================================
int sstRec04Cls::WritNew(int iKey, void* vRecAdr, dREC04RECNUMTYP *pdRecNo) {

    return poRec01Intern->WritNewVector( iKey, vRecAdr, pdRecNo);
}
//==============================================================================
int sstRec04Cls::Writ(int iKey, void* vRecAdr, dREC04RECNUMTYP dRecNo)
{
  return poRec01Intern->WritVector( iKey, vRecAdr, dRecNo);
}

//==============================================================================
int sstRec04Cls::Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr) {
    int iStat = poRec01Intern->ReadVector( iKey, dRecNo, vRecAdr);
    return iStat;
}
//==============================================================================
dREC04RECNUMTYP sstRec04Cls::count() {
    return poRec01Intern->count();
}
//==============================================================================
int sstRec04Cls::OpenFile(int   iKey,
                    char *cSysNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  iStat = this->poRec01Intern->OpenFile(iKey,cSysNam);
  return iStat;
}
//==============================================================================
int sstRec04Cls::NewFile(int   iKey,
                   char *cSysNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  iStat = this->poRec01Intern->NewFile(iKey,cSysNam);
  return iStat;
}
//==============================================================================
int sstRec04Cls::SetStoreFile(int iKey)
{
  if ( iKey != 0) return -1;
  int iStat = this->poRec01Intern->SetStoreFile(iKey);
  return iStat;
}
//==============================================================================
int sstRec04Cls::AddCargoSys( int                  iKey,
                              unsigned int         uiSize,
                              char                *cCargoNam,
                              sstRec04CargoKeyCls *oCargoKey)
//-----------------------------------------------------------------------------
{
    int iRet  = 0;
    int iStat = 0;
    //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    iStat = this->poRec01Intern->AddCargoSys(iKey,uiSize,cCargoNam, oCargoKey->poCargoKeyIntern);

    // Fatal Errors goes to an assert
    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}

//==============================================================================
int sstRec04Cls::WrtCargo ( int              iKey,
                            sstRec04CargoKeyCls *oDataKey,
                            void            *vCargoAdr)
//------------------------------------------------------------------------------
{
  return this->poRec01Intern->WrtCargo(iKey,oDataKey->poCargoKeyIntern,vCargoAdr);
}
//==============================================================================
int sstRec04Cls::RedCargo ( int              iKey,
                            sstRec04CargoKeyCls *oDataKey,
                            void            *vCargoAdr)
//-----------------------------------------------------------------------------
{
    return this->poRec01Intern->RedCargo( iKey, oDataKey->poCargoKeyIntern, vCargoAdr);
}
//==============================================================================
int sstRec04Cls::RecSetDeleted ( int               iKey,
                                 dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecSetDeleted( iKey, dRecNo);
}
//==============================================================================
int sstRec04Cls::RecSetMarked( int               iKey,
                                dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecSetMarked( iKey, dRecNo);
}
//==============================================================================
int sstRec04Cls::RecSetUndeleted( int               iKey,
                                   dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecSetUndeleted( iKey, dRecNo);
}
//==============================================================================
int sstRec04Cls::RecSetUnmarked( int               iKey,
                                  dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecSetUnmarked( iKey, dRecNo);
}
//==============================================================================
bool sstRec04Cls::RecGetDeleteStatus( int               iKey,
                                      dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecGetDeleteStatus( iKey, dRecNo);
}
//==============================================================================
bool sstRec04Cls::RecGetMarkStatus( int               iKey,
                                    dREC04RECNUMTYP   dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->RecGetMarkStatus( iKey, dRecNo);
}
//==============================================================================
int sstRec04Cls::TreIni ( int              iKey,
                          void            *DsAdr,
                          void            *CompAdr,
                          int              CompSiz,
                          sstRec04CompTyp_enum     CompTyp,
                          sstRec04TreeKeyCls   *oTre)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreIni(iKey,DsAdr,CompAdr,CompSiz,CompTyp,oTre);
}
//==============================================================================
int sstRec04Cls::TreBld ( int                   iKey,
                          sstRec04TreeKeyCls   *oTre)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreBld(iKey,oTre);
}

//==============================================================================
int sstRec04Cls::TreSeaEQ  ( int                   iKey,
                             sstRec04TreeKeyCls   *oTre,
                             void                 *Val,
                             dREC04RECNUMTYP      *dRecNo)
{
  return this->poRec01Intern->TreSeaEQ ( iKey, oTre, Val, dRecNo);

}

//==============================================================================
int sstRec04Cls::TreReadNxtGE (int                   iKey,
                               sstRec04TreeKeyCls   *oTre,
                               void                 *DSatz,
                               dREC04RECNUMTYP      *SNr)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreReadNxtGE(iKey,oTre,DSatz,SNr);
}
//==============================================================================
int sstRec04Cls::TreSeaFrst ( int            iKey,
                 sstRec04TreeKeyCls *oTre,
                 dREC04RECNUMTYP  *SNr)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreSeaFrst(iKey,oTre,SNr);
}
//==============================================================================
int sstRec04Cls::TreSeaLast ( int            iKey,
                 sstRec04TreeKeyCls *oTre,
                 dREC04RECNUMTYP  *SNr)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreSeaLast(iKey,oTre,SNr);
}
//==============================================================================
int sstRec04Cls::TreSeaNxtGE ( int             iKey,
                  sstRec04TreeKeyCls  *oTre,
                  dREC04RECNUMTYP    SNr1,
                  dREC04RECNUMTYP   *SNr2)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreSeaNxtGE(iKey,oTre,SNr1,SNr2);
}
//==============================================================================
int sstRec04Cls::TreSeaNxtEQ ( int                   iKey,
                               sstRec04TreeKeyCls   *oTre,
                               void                 *vSearchMin,
                               void                 *vSearchMax,
                               dREC04RECNUMTYP      *SNr)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreSeaNxtEQ(iKey,oTre,vSearchMin,vSearchMax,SNr);
}
//==============================================================================
int sstRec04Cls::TreWriteNew( int               iKey,
                            void            *vRecAdr,
                            dREC04RECNUMTYP *dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreWriteNew( iKey, vRecAdr, dRecNo);
}
//==============================================================================
int sstRec04Cls::TreWritAtPos ( int               iKey,
                                void             *vRecAdr,
                                dREC04RECNUMTYP   dRecNo)
{
  return this->poRec01Intern->TreWritVector( iKey, vRecAdr, dRecNo);

}
//==============================================================================
int sstRec04Cls::TreDelValue ( int                   iKey,
                               sstRec04TreeKeyCls   *oTre,
                               void                 *vSearchValue,
                               dREC04RECNUMTYP      *dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreDelValue ( iKey, oTre, vSearchValue, dRecNo);
}
//==============================================================================
int sstRec04Cls::TreDelNumber ( int                      iKey,
                                dREC04RECNUMTYP          dRecNo)
//-----------------------------------------------------------------------------
{
  return this->poRec01Intern->TreDelNumber( iKey, dRecNo);
}
//==============================================================================
sstRec04InternCls* sstRec04Cls::GetInternObjAdr()
{
  return this->poRec01Intern;
}
//==============================================================================
dREC04RECNUMTYP sstRec04Cls::GetUserRecordSize()
{
  return this->poRec01Intern->GetUserRecordSize();
}
//==============================================================================
int sstRec04Cls::TreeLog(int                   iKey,
                         sstRec04TreeKeyCls   *oTre,
                         char                 *cLogFilNam)
{
  return this->poRec01Intern->TreeLog(iKey, oTre, cLogFilNam);
}
//=============================================================================

