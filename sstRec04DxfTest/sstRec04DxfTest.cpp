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
// sstRec04DxfTest.cpp    14.12.15 Re.    14.12.15  Re.
//
// Small Analyzing tool for dxf data using sstRec04 linked list functions.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04DxfTest.h"

//=============================================================================
int main (int argc, char *argv [])
//=============================================================================
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------

  sstMisc01AscFilCls oDxfFilIn;
  sstMisc01AscFilCls oDxfFilOut;
  sstMisc01AscRowCls oRowIn;
  sstMisc01AscRowCls oRowOut;
  std::string oDxfRowIn;
  std::string oDxfRowOut;

  sstTDBLetterCls oLetterRec;  // Text Database: Letter
  sstTDBLinkCls oLinkRec;      // Text Database: Letter Links
  sstTDBWordCls oWordRec;      // Text Database: Words

  sstRec04Cls oRM3_Letter(sizeof(oLetterRec));  // RecordMemory for Letter
  sstRec04Cls oRM2_Link(sizeof(oLinkRec));      // RecordMemory for Linked List
  sstRec04Cls oRM1_Word(sizeof(oWordRec));      // RecordMemory for Words

  sstRec04LiLstCls oTDB;

  // Initialize Linked List with Header, List element and target RecMem objects
  iStat = oTDB.Define3( 0, &oRM1_Word, &oRM2_Link, &oRM3_Letter);

  dREC04RECNUMTYP dWordPos;
  dREC04RECNUMTYP dLinkPos;
  dREC04RECNUMTYP dLetterPos;

  // Fill Letter Table
  for (dREC04RECNUMTYP ii=1; ii<=200; ii++)
  {
    oRM3_Letter.WritNew(0,&oLetterRec,&dLetterPos);
  }

  iStat = oDxfFilIn.fopenRd(0,(char*)"test_Was_Schaum.dxf");

  int iStat1 = 0;
  unsigned long ulDxfRowNum=0;
  unsigned long ulDxfRowLen = 0;

  dREC04RECNUMTYP  	dLinkListEntry1 = 0;
  dREC04RECNUMTYP  	dLinkListEntry2 = 0;

  while (iStat1 >= 0)
  {
    // iStat1 = oDxfFilIn.rd_line(0,&oRowIn);
    iStat1 = oDxfFilIn.Rd_StrDS1(0,&oDxfRowIn);
    ulDxfRowNum++;
    if(ulDxfRowNum >= 3) iStat1 = -1;  // Break at row num

    // oDxfRowIn = oRowIn.Txt;

    ulDxfRowLen = oDxfRowIn.length();
    oRM1_Word.WritNew(0,&oWordRec,&dWordPos);

//    dREC04RECNUMTYP  	dLinkListEntry1 = 0;
//    dREC04RECNUMTYP  	dLinkListEntry2 = 0;

    for (unsigned long ll =0; ll < ulDxfRowLen; ll++)
    {
      oRM2_Link.WritNew(0,&oLinkRec,&dLinkPos);

      dLetterPos = oDxfRowIn.at(ll);
      iStat = oTDB.ExtendAtEnd ( 0, dWordPos, dLinkPos, dLetterPos);

      // Get Element Data for Linked list object
      iStat = oTDB.getEntriesInLinkList( 0, dWordPos, &dLinkListEntry1, &dLinkListEntry2);
    }
  }

  oDxfFilIn.fcloseFil(0);
  printf("Read Dxf into Record Memory\n");


  // === Read linked list and write dxf file ===================================

  iStat = oDxfFilOut.fopenWr (0,(char*)"Output.dxf");

  dREC04RECNUMTYP  	dRecNoElePrev = 0;
  dREC04RECNUMTYP  	dRecNoEleNext = 0;

  dLinkListEntry1 = 0;
  dLinkListEntry2 = 0;

  dREC04RECNUMTYP dWordsAmount = oRM1_Word.count();

  for ( dREC04RECNUMTYP ll=1; ll <= dWordsAmount; ll++)
  {
    // Get Element Data for Linked list object
    iStat = oTDB.getEntriesInLinkList( 0, ll, &dLinkListEntry1, &dLinkListEntry2);

    oDxfRowOut.clear();

    while (dLinkListEntry1 > 0)
    {
      // Get all data from element node
      iStat = oTDB.ListNodeGetEleAll ( 0, dLinkListEntry1, &dWordPos, &dRecNoEleNext, &dRecNoElePrev, &dLetterPos);
      dLinkListEntry1 = dRecNoEleNext;

      oDxfRowOut = oDxfRowOut + (char) dLetterPos;
    }

    // memset(oRowOut.Txt,0,dCASC2_TEXTLEN);
    // strncpy( oRowOut.Txt, oDxfRowOut.c_str(), dCASC2_TEXTLEN);

    // iStat = oDxfFilOut.wr_line(0,&oRowOut);
    iStat = oDxfFilOut.Wr_StrDS1(0,&oDxfRowOut);

  }

  oDxfFilOut.fcloseFil(0);
  printf("Write Contence of Record Memory into mirror dxf. \n");

  //=== Read both dxf files and compare rows

  iStat = oDxfFilIn.fopenRd(0,(char*)"test_Was_Schaum.dxf");
  iStat = oDxfFilOut.fopenRd(0,(char*)"Output.dxf");

  iStat1 = 0;

  // iStat = oDxfFilIn.rd_line(0,&oRowIn);
  // iStat1 = oDxfFilOut.rd_line(2,&oRowOut);
  iStat = oDxfFilIn.Rd_StrDS1(0,&oDxfRowIn);
  iStat1 = oDxfFilOut.Rd_StrDS1(2,&oDxfRowOut);

  while (iStat1 >= 0)
  {

//    oDxfRowIn = oRowIn.Txt;
//    oDxfRowOut = oRowOut.Txt;

    iStat = oDxfRowIn.compare(oDxfRowOut);
    assert(oDxfRowIn.compare(oDxfRowOut)==0);

    iStat = oDxfFilIn.rd_line(0,&oRowIn);
    iStat1 = oDxfFilOut.rd_line(2,&oRowOut);

  }


  oDxfFilIn.fcloseFil(0);
  oDxfFilOut.fcloseFil(0);

  printf("Test: Both dxf files are identically. \n");

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
sstTDBLetterCls::sstTDBLetterCls()
{

}
//=============================================================================
sstTDBLinkCls::sstTDBLinkCls()
{

}
//=============================================================================
sstTDBWordCls::sstTDBWordCls()
{

}
//=============================================================================
