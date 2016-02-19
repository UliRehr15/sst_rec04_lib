/**********************************************************************
 *
 * sst_rec_lib - library for working with data records
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
// sstRec04TestIntern.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include "sstStr01Lib.h"
#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int sstRec04_DoSomeInternTests (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Test writ cargo systems into vector
  iStat = Test_VectorSys_Stack ( 0);

  // Test writ cargo systems into vector
  iStat = Test_VectorSys_Heap ( 0);

  // Fatal Errors goes to an assert
  assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int Test_VectorSys_Stack (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

    sstRec04VectSysCls oDssDataSys;

    sstRec04CargoKeyInternCls oDssDataKey1;
    sstRec04CargoKeyInternCls oDssDataKey2;

    sstRec04TestRec1Cls oCargoData11;
    sstRec04TestRec1Cls oCargoData12;
    sstRec04TestRec2Cls oCargoData21;
    sstRec04TestRec2Cls oCargoData22;

    iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData11), (char*) "XXXX", &oDssDataKey1);

  if(iStat != 0)  {    assert(0);  }

  oCargoData11.iVal = 55;
  strncpy(oCargoData11.cVal,"abc", 5);

  iStat = oDssDataSys.WrtCargo ( 0, &oDssDataKey1, &oCargoData11);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);
  if(oCargoData11.iVal != oCargoData12.iVal) assert(0);

  iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData21), (char*) "YYYY", &oDssDataKey2);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);
  if(oCargoData11.iVal != oCargoData12.iVal) assert(0);

  iStat = oDssDataSys.AddCargoSys( 0, sizeof(oCargoData21), (char*) "ZZZ", &oDssDataKey2);

  oCargoData21.dVal = 55.5;
  strncpy(oCargoData21.cVal,"dcba", 10);

  iStat = oDssDataSys.WrtCargo ( 0, &oDssDataKey2, &oCargoData21);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey1, &oCargoData12);

  if(oCargoData11.iVal != oCargoData12.iVal) assert(0);

  iStat = oDssDataSys.RedCargo ( 0, &oDssDataKey2, &oCargoData22);

  if(oCargoData21.dVal != oCargoData22.dVal) assert(0);

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
int Test_VectorSys_Heap (int iKey) // v  -> For the moment 0
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

    sstRec04VectSysCls *oDssDataSys;

    sstRec04CargoKeyInternCls *oDssDataKey1;
    sstRec04CargoKeyInternCls *oDssDataKey2;

    sstRec04TestRec1Cls oCargoData11;
    sstRec04TestRec1Cls oCargoData12;
    sstRec04TestRec2Cls oCargoData21;
    sstRec04TestRec2Cls oCargoData22;

    oDssDataSys = new (sstRec04VectSysCls);

    oDssDataKey1 = new (sstRec04CargoKeyInternCls);
    oDssDataKey2 = new (sstRec04CargoKeyInternCls);

    iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData11), (char*) "XXXX", oDssDataKey1);

  if(iStat != 0)  {    assert(0);  }

  oCargoData11.iVal = 55;
  strncpy(oCargoData11.cVal,"abc", 5);

  iStat = oDssDataSys->WrtCargo ( 0, oDssDataKey1, &oCargoData11);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey1, &oCargoData12);

  if(oCargoData11.iVal != oCargoData12.iVal) assert(0);

  iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData21), (char*) "YYYY", oDssDataKey2);

  iStat = oDssDataSys->AddCargoSys( 0, sizeof(oCargoData21), (char*) "ZZZ", oDssDataKey2);

  oCargoData21.dVal = 55.5;
  strncpy(oCargoData21.cVal,"dcba", 10);

  iStat = oDssDataSys->WrtCargo ( 0, oDssDataKey2, &oCargoData21);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey1, &oCargoData12);

  if(oCargoData11.iVal != oCargoData12.iVal) assert(0);

  iStat = oDssDataSys->RedCargo ( 0, oDssDataKey2, &oCargoData22);

  if(oCargoData21.dVal != oCargoData22.dVal) assert(0);

  delete(oDssDataKey2);
  delete(oDssDataKey1);

  delete(oDssDataSys);

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
