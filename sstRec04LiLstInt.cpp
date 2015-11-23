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
// sstRec04LiLstInt.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

// Complete function description is in headerfile
//-----------------------------------------------------------------------------
sstRec04LiLstIntCls::sstRec04LiLstIntCls()
{
  this->poRecMemHed = NULL;
  this->poRecMemEle = NULL;
  this->poRecMemTar = NULL;

  this->poLstHedKey = new(sstRec04CargoKeyInternCls);
  this->poLstEleKey = new(sstRec04CargoKeyInternCls);
  this->poLstTarKey = new(sstRec04CargoKeyInternCls);

  dLiLstEntry2 = 0;
  dLiLstEntry1 = 0;
}
//=============================================================================
sstRec04LiLstIntCls::~sstRec04LiLstIntCls()
{
  this->poRecMemHed = NULL;
  this->poRecMemEle = NULL;
  this->poRecMemTar = NULL;

  delete(this->poLstHedKey);
  delete(this->poLstEleKey);
  delete(this->poLstTarKey);
}

//=============================================================================
int sstRec04LiLstIntCls::Define3(int          iKey,
                               sstRec04Cls *oTmpHedDss1,
                               sstRec04Cls *oTmpEleDss2,
                               sstRec04Cls *oTmpTarDss3)
//-----------------------------------------------------------------------------
{
  int iStat = 0;
  if ( iKey != 0) return -1;

  this->poRecMemHed = (sstRec04InternCls*) oTmpHedDss1->GetInternObjAdr();
  this->poRecMemEle = (sstRec04InternCls*) oTmpEleDss2->GetInternObjAdr();
  this->poRecMemTar = (sstRec04InternCls*) oTmpTarDss3->GetInternObjAdr();

  iStat = this->poRecMemHed->AddCargoSys( 0, sizeof(sstRec04LiLstHedCls), (char*) "LLHE", this->poLstHedKey);
  iStat = this->poRecMemEle->AddCargoSys( 0, sizeof(sstRec04LiLstEleCls), (char*) "LLEL", this->poLstEleKey);
  iStat = this->poRecMemTar->AddCargoSys( 0, sizeof(sstRec04LiLstTarCls), (char*) "LLTA", this->poLstTarKey);

  return iStat;
}
//=============================================================================
int sstRec04LiLstIntCls::Target2List( int              iKey,
                                      dREC04RECNUMTYP  dRecNoTar,
                                      dREC04RECNUMTYP  dRecNoEle)
{
  dREC04RECNUMTYP dSaveLastRecNoEle=0;  // Store last adress
  dREC04RECNUMTYP dNumRec = 0;
  sstRec04LiLstEleCls *poEleRec2=NULL;
  sstRec04LiLstTarCls *poTarRec3=NULL;
  void *vCargoAdr = NULL;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iStat = 0;
  int iRet = 0;

  iStat = this->poRecMemEle->GetCargoAdr( 0, this->poLstEleKey, &vCargoAdr);
  poEleRec2 = (sstRec04LiLstEleCls*) vCargoAdr;

  iStat = this->poRecMemTar->GetCargoAdr( 0, this->poLstTarKey, &vCargoAdr);
  poTarRec3 = (sstRec04LiLstTarCls*) vCargoAdr;

  dNumRec = this->poRecMemEle->count();  // Get number of elements in chain-array

  if ( dNumRec <= 1) /* chain-array is empty */
  {
    // create first set in chain-array
    this->dLiLstEntry2  = dRecNoEle;
    this->dLiLstEntry1 = dRecNoEle;

    iStat = this->poRecMemEle->ReadInt( 0, dNumRec, this->poRecMemEle->GetVectorAdr());

    iStat = poEleRec2->Set(0,0,0,0);
    iStat = poEleRec2->SetTarget(0,dRecNoTar);

    this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dNumRec);
  }
  else                    /* Es liegen bereits Datei-Eintragungen vor. */
  {
    if ( this->dLiLstEntry2 == 0)    /* start new linked list */
    {
      dNumRec = this->poRecMemEle->count();  // Get number of elements in chain-array

      this->dLiLstEntry2  = dRecNoEle;
      this->dLiLstEntry1 = dRecNoEle;

      iStat = this->poRecMemEle->ReadInt( 0, dRecNoEle, this->poRecMemEle->GetVectorAdr());

      iStat = poEleRec2->Set( 0, 0, 0, 0);
      iStat = poEleRec2->SetTarget(0,dRecNoTar);

      this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dRecNoEle);
    }
    else                  /* Extend existing linked list */
    {
      // Store new element for existing chain in field
      iStat = this->poRecMemEle->ReadInt( 0, this->dLiLstEntry2, this->poRecMemEle->GetVectorAdr());

      iStat = poEleRec2->SetNext( 0, dRecNoEle);

      iStat = this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), this->dLiLstEntry2);

      // save int adress
      dSaveLastRecNoEle = this->dLiLstEntry2;
      this->dLiLstEntry2 = poEleRec2->GetNext();

      iStat = this->poRecMemEle->ReadInt( 0, dRecNoEle, this->poRecMemEle->GetVectorAdr());

      iStat = poEleRec2->Set(0, 0, dSaveLastRecNoEle, 0);
      iStat = poEleRec2->SetTarget ( 0, dRecNoTar);

      this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dRecNoEle);
    }
  }

  iStat = this->poRecMemTar->ReadInt( 0, dRecNoTar, this->poRecMemTar->GetVectorAdr());

  poTarRec3->ulNumEle = poTarRec3->ulNumEle + 1;

  iStat = this->poRecMemTar->WritInt( 0, this->poRecMemTar->GetVectorAdr(), dRecNoTar);

  // Reset Data in Vector
  poTarRec3->ulNumEle = 0;
  iStat = poEleRec2->Set(0, 0, 0, 0);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int sstRec04LiLstIntCls::List2Header ( int              iKey,
                                       dREC04RECNUMTYP  dRecNoEle,
                                       dREC04RECNUMTYP  dRecNoHed)
{
  int iDirec;                     /* 0 = Forwards, 1 = Backwards  */
  dREC04RECNUMTYP dMasterEle;     /* Element, dem die Kette zugeordnet werden soll */
  dREC04RECNUMTYP dStartStop[2];  /* Erster u. letzte Adresse der Kette */
  dREC04RECNUMTYP dActEleInList = 0;  // actual element in List
  dREC04RECNUMTYP dHedRecNum=0;  // Amount of records in Head MemRec
  dREC04RECNUMTYP dEleRecNo=0;   // actual record in Ele MemRec
  void *vCargoAdr = NULL;
  sstRec04LiLstHedCls *poHedRec1;
  sstRec04LiLstEleCls *poEleRec2;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iStat = 0;
  int iRet = 0;

  iStat = this->poRecMemHed->GetCargoAdr(0,this->poLstHedKey,&vCargoAdr);
  poHedRec1 = (sstRec04LiLstHedCls*) vCargoAdr;

  iStat = this->poRecMemEle->GetCargoAdr(0,this->poLstEleKey,&vCargoAdr);
  poEleRec2 = (sstRec04LiLstEleCls*) vCargoAdr;

// === Update Node data
  dHedRecNum = this->poRecMemHed->count();  // Get number of elements in chain-array
  dMasterEle = dHedRecNum;

  dEleRecNo = dRecNoEle;
  iStat = this->poRecMemEle->ReadInt( 0, dEleRecNo, this->poRecMemEle->GetVectorAdr());

  iStat = poEleRec2->SetMaster(0,dMasterEle);

  iStat = this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dEleRecNo);

  if ( poEleRec2->GetNext() != 0)
  {
    // Looking forwarts
    iDirec = 0;
    dActEleInList = poEleRec2->GetNext();
  }
  else
  {
    // Looking backwarts
    iDirec = 1;
    dActEleInList = poEleRec2->GetPrev();
  }

  dStartStop[0] = dRecNoEle;
  dStartStop[1] = dRecNoEle;

    while ( dActEleInList != 0)
    {
      dEleRecNo = dActEleInList;
      iStat = this->poRecMemEle->ReadInt( 0, dEleRecNo, this->poRecMemEle->GetVectorAdr());

      iStat = poEleRec2->SetMaster(0, dMasterEle);

      iStat = this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dEleRecNo);

      if (iDirec == 0)  // looking forwarts
      {
        if (poEleRec2->GetNext() == 0) dStartStop[1] = dActEleInList;
        dActEleInList = poEleRec2->GetNext();
      }
      else             // looking backwarts
      {
        if (poEleRec2->GetPrev() == 0) dStartStop[0] = dActEleInList;
        dActEleInList = poEleRec2->GetPrev();
      }
    }

    // === Update Head data
    dEleRecNo = this->poRecMemHed->ReadInt( 0,dRecNoHed, this->poRecMemHed->GetVectorAdr());

    poHedRec1->SetEntry1(0, dStartStop[0]);
    poHedRec1->SetEntry2(0, dStartStop[1]);

    iStat = this->poRecMemHed->WritInt( 0, this->poRecMemHed->GetVectorAdr(),dRecNoHed);

    // Linked list finished, reset all infos
    this->dLiLstEntry2 = 0;
    this->dLiLstEntry1 = 0;

    poHedRec1->SetEntry1(0,0);
    poHedRec1->SetEntry2(0,0);

    poEleRec2->Set(0,0,0,0);

    // Fatal Errors goes to an assert
    if (iRet < 0)
    {
      // Expression (iRet >= 0) has to be fullfilled
      assert(0);
    }

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}
//=============================================================================
int sstRec04LiLstIntCls::GetTarNumUse(int              iKey,
                                      dREC04RECNUMTYP *dNumUse,
                                      dREC04RECNUMTYP  RecNoTar)
{
  sstRec04LiLstTarCls *pTarRec3;
  void *pCargoAdr;
  int iStat = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poRecMemTar->GetCargoAdr( 0, this->poLstTarKey, &pCargoAdr);
  pTarRec3 = (sstRec04LiLstTarCls*) pCargoAdr;

  // Read record to vector
  // iStat = this->oTarDss3->LesAbs( 0, this->oTarDss3->oVector->GetAdr(), RecNoTar);
  iStat = this->poRecMemTar->ReadInt( 0, RecNoTar, this->poRecMemTar->GetVectorAdr());

  *dNumUse = pTarRec3->ulNumEle;

  //  pTarRec3->ulNumEle = dNumUse;

//  // Write vector to record
//  iStat = this->oTarDss3->ShrAbs( 0, this->oTarDss3->oVector->GetAdr(), RecNoTar);

  return iStat;
}
//=============================================================================
int sstRec04LiLstIntCls::SetTarNumUse(int          iKey,
                                  dREC04RECNUMTYP dNumUse,
                                  dREC04RECNUMTYP RecNoTar)
{
  sstRec04LiLstTarCls *pTarRec3;
  void *pCargoAdr;
  int iStat = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poRecMemTar->GetCargoAdr( 0, this->poLstTarKey, &pCargoAdr);
  pTarRec3 = (sstRec04LiLstTarCls*) pCargoAdr;

  // Read record to vector
  // iStat = this->oTarDss3->LesAbs( 0, this->oTarDss3->oVector->GetAdr(), RecNoTar);
  iStat = this->poRecMemTar->ReadInt( 0, RecNoTar, this->poRecMemTar->GetVectorAdr());

  pTarRec3->ulNumEle = dNumUse;

  // Write vector to record
  // iStat = this->oTarDss3->ShrAbs( 0, this->oTarDss3->oVector->GetAdr(), RecNoTar);
  iStat = this->poRecMemTar->WritInt( 0, this->poRecMemTar->GetVectorAdr(), RecNoTar);

  return iStat;
}
//=============================================================================
int sstRec04LiLstIntCls::SetEleAll (int          iKey,
                                dREC04RECNUMTYP dRecNoEle,
                                dREC04RECNUMTYP dTmpMaster,
                                dREC04RECNUMTYP dTmpNext,
                                dREC04RECNUMTYP dTmpPrev,
                                dREC04RECNUMTYP dTmpTarget)
{

  sstRec04LiLstEleCls *pEleRec2;
  void *pCargoAdr;
  int iStat = 0;
  int iRet = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poRecMemEle->GetCargoAdr( 0, this->poLstEleKey, &pCargoAdr);
  pEleRec2 = (sstRec04LiLstEleCls*) pCargoAdr;

  // Read record to vector
  // iStat = this->oEleDss2->LesAbs( 0, this->oEleDss2->oVector->GetAdr(), dRecNoEle);
  iStat = this->poRecMemEle->ReadInt( 0, dRecNoEle, this->poRecMemEle->GetVectorAdr());

  iStat = pEleRec2->Set(0, dTmpMaster, dTmpPrev, dTmpNext);
  iStat = pEleRec2->SetTarget(0,dTmpTarget);

  // Write vector to record
  // iStat = this->oEleDss2->ShrAbs( 0, this->oEleDss2->oVector->GetAdr(), dRecNoEle);
  iStat = this->poRecMemEle->WritInt( 0, this->poRecMemEle->GetVectorAdr(), dRecNoEle);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04LiLstIntCls::ListNodeGetEleAll (int              iKey,
                                            dREC04RECNUMTYP  dRecNoEle,
                                            dREC04RECNUMTYP *dTmpMaster,
                                            dREC04RECNUMTYP *dTmpNext,
                                            dREC04RECNUMTYP *dTmpPrev,
                                            dREC04RECNUMTYP *dTmpTarget)
{

  sstRec04LiLstEleCls *pEleRec2;
  void *pCargoAdr;
  int iStat = 0;
  int iRet = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poRecMemEle->GetCargoAdr( 0, this->poLstEleKey, &pCargoAdr);
  pEleRec2 = (sstRec04LiLstEleCls*) pCargoAdr;

  // Read record to vector
  iStat = this->poRecMemEle->ReadInt( 0, dRecNoEle, this->poRecMemEle->GetVectorAdr());

  // iStat = pEleRec2->Get(0, dTmpMaster, dTmpPrev, dTmpNext);
  *dTmpMaster = pEleRec2->GetMaster();
  *dTmpNext = pEleRec2->GetNext();
  *dTmpPrev = pEleRec2->GetPrev();
  *dTmpTarget = pEleRec2->GetTarget();

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04LiLstIntCls::SetHedAll (int             iKey,
                                    dREC04RECNUMTYP dRecNoHed,
                                    dREC04RECNUMTYP dTmpEntry1,
                                    dREC04RECNUMTYP dTmpEntry2)
{

  sstRec04LiLstHedCls *pHedRec1;
  void *pCargoAdr;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iStat = 0;
  int iRet = 0;

  iStat = this->poRecMemHed->GetCargoAdr( 0, this->poLstHedKey, &pCargoAdr);
  pHedRec1 = (sstRec04LiLstHedCls*) pCargoAdr;

  // Read record to vector
  iStat = this->poRecMemHed->ReadInt( 0, dRecNoHed, this->poRecMemHed->GetVectorAdr());

  iStat = pHedRec1->SetEntry1(0,dTmpEntry1);
  iStat = pHedRec1->SetEntry2(0,dTmpEntry2);

  // Write vector to record
  iStat = this->poRecMemHed->WritInt( 0, this->poRecMemHed->GetVectorAdr(), dRecNoHed);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04LiLstIntCls::getEntriesInLinkList(int               iKey,
                                              dREC04RECNUMTYP  dRecNoHed,
                                              dREC04RECNUMTYP *dTmpEntry1,
                                              dREC04RECNUMTYP *dTmpEntry2)
{
  sstRec04LiLstHedCls *pHedRec1;
  void *pCargoAdr;
  int iStat = 0;

  //-----------------------------------------------------------------------------
  if ( iKey == 0)
  {
    // Get Adress of LiList Header Data in Head RecMem Vector
    this->poRecMemHed->GetCargoAdr( 0, this->poLstHedKey, &pCargoAdr);
    pHedRec1 = (sstRec04LiLstHedCls*) pCargoAdr;

    // Read record to vector
    iStat = this->poRecMemHed->ReadInt( 0, dRecNoHed, this->poRecMemHed->GetVectorAdr());

    *dTmpEntry1 = pHedRec1->GetEntry1();
    *dTmpEntry2 = pHedRec1->GetEntry2();
  }
  return iStat;
}
//=============================================================================
int sstRec04LiLstIntCls::ExtendAtEnd(int             iKey,
                                     dREC04RECNUMTYP dRecNoHead,
                                     dREC04RECNUMTYP dRecNoEle,
                                     dREC04RECNUMTYP dRecNoTarget)
//-----------------------------------------------------------------------------
{
  void *vCargoAdr = NULL;
  sstRec04LiLstHedCls *poHedRec1 = NULL;
  sstRec04LiLstEleCls *poEleRec2 = NULL;

  int iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  if (dRecNoHead <= 0    || dRecNoHead > this->poRecMemHed->count()) return -2;
  if (dRecNoEle <= 0     || dRecNoHead > this->poRecMemEle->count()) return -3;
  if (dRecNoTarget <= 0  || dRecNoHead > this->poRecMemTar->count()) return -4;


  iStat = this->poRecMemHed->GetCargoAdr(0,this->poLstHedKey,&vCargoAdr);
  poHedRec1 = (sstRec04LiLstHedCls*) vCargoAdr;

  iStat = this->poRecMemEle->GetCargoAdr(0,this->poLstEleKey,&vCargoAdr);
  poEleRec2 = (sstRec04LiLstEleCls*) vCargoAdr;

  iStat = this->poRecMemEle->ReadInt( 0,dRecNoEle, this->poRecMemEle->GetVectorAdr());

  // Given List Element should be emtpy
  if (poEleRec2->GetMaster() != 0 || poEleRec2->GetTarget() != 0) return -5;

  // === Update Head data
  iStat = this->poRecMemHed->ReadInt( 0,dRecNoHead, this->poRecMemHed->GetVectorAdr());

  this->dLiLstEntry1 = poHedRec1->GetEntry1();
  this->dLiLstEntry2 = poHedRec1->GetEntry2();

  // Insert new target object to element list
  iStat = this->Target2List( 0, dRecNoEle, dRecNoTarget);

  // Add list object to header object
  if (iStat >= 0) iStat = this->List2Header( 0, dRecNoEle, dRecNoHead);

  return iStat;
}
//=============================================================================

