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

  sstMisc01AscFilCls oDxfFilIn;   // Dxf input file object
  sstMisc01AscFilCls oDxfFilOut;  // Dxf output file object

  std::string oDxfRowIn;   // Dxf input string object
  std::string oDxfRowOut;  // Dxf output string object

  sstTDBLetterCls oLetterRec;  // Text Database: Letter
  sstTDBLinkCls oLinkRec;      // Text Database: Letter linked list
  sstTDBWordCls oWordRec;      // Text Database: Word

  sstRec04Cls oRM3_Letter(sizeof(oLetterRec));  // RecordMemory for Letter
  sstRec04Cls oRM2_Link(sizeof(oLinkRec));      // RecordMemory for Linked List
  sstRec04Cls oRM1_Word(sizeof(oWordRec));      // RecordMemory for Words

  sstRec04LiLstCls oTDB;  // Linked list text data base

  // Initialize Linked List with Header, List element and target RecMem objects
  iStat = oTDB.Define3( 0, &oRM1_Word, &oRM2_Link, &oRM3_Letter);

  dREC04RECNUMTYP dWordPos;    // Record position in Word RecMem
  dREC04RECNUMTYP dLinkPos;    // Record position in Link RecMem
  dREC04RECNUMTYP dLetterPos;  // Record position in Letter RecMem

  // Fill Letter Table with 200 Letters
  // ASCII Code Table
  for (dREC04RECNUMTYP ii=1; ii<=200; ii++)
  {
    oRM3_Letter.WritNew(0,&oLetterRec,&dLetterPos);
  }

  //=== read dxf data from file and write into linked list

  iStat = oDxfFilIn.fopenRd(0,(char*)"Test_Input.dxf");
  assert(iStat == 0);

  int iStat1 = 0;
  unsigned long ulDxfRowNum=0;
  unsigned long ulDxfRowLen = 0;

  dREC04RECNUMTYP  	dLinkListEntry1 = 0;
  dREC04RECNUMTYP  	dLinkListEntry2 = 0;

  while (iStat1 >= 0)
  {
    // Read next row from file
    iStat1 = oDxfFilIn.Rd_StrDS1(0,&oDxfRowIn);
    ulDxfRowNum++;
    if(ulDxfRowNum >= 10) iStat1 = -1;  // Break at row num

    // one row is one word
    ulDxfRowLen = oDxfRowIn.length();
    oRM1_Word.WritNew(0,&oWordRec,&dWordPos);

    // loop over all letters in row
    for (unsigned long ll =0; ll < ulDxfRowLen; ll++)
    {
      // write next linked list element
      oRM2_Link.WritNew(0,&oLinkRec,&dLinkPos);

      // Add next element into linked list
      dLetterPos = oDxfRowIn.at(ll);
      iStat = oTDB.ExtendAtEnd ( 0, dWordPos, dLinkPos, dLetterPos);
    }
  }

  oDxfFilIn.fcloseFil(0);
  printf("Read Dxf into Linked list\n");
  printf("Row: ListHead, Use of Letters: ListElement, LetterTable: ListTarget. \n\n");

  // === Get some statistic data =============================================================

  printf("Test: Count use of letters. \n\n");

  dREC04RECNUMTYP  	dNumUse=0;
  // loop from letter "A" to "F"
  for (dREC04RECNUMTYP ll=65;ll <= 70; ll++)
  {
    // Get Number of uses for target record
    iStat = oTDB.GetTarNumUse ( 0, ll, &dNumUse);
    int iVal = (int) ll;
    printf("Char %c Number of uses: %lu \n", iVal, dNumUse);
  }

  printf("\n");
  printf("Test: Calculate row length. \n\n");

  // Get Number of list elements for list header
  dREC04RECNUMTYP  	dListLength=0;
  dWordPos = oRM1_Word.count();

  for (dREC04RECNUMTYP ll=1;ll <= dWordPos; ll++)
  {
    // Get Number of uses for target record
    // iStat = oTDB.GetTarNumUse ( 0, ll, &dNumUse);
    iStat = oTDB.GetHedListLength ( 0, ll, &dListLength);
    printf("Row %lu : Length of row: %lu \n",ll, dListLength);
  }
  // === Read dxf data from linked list and write dxf file ===================================

  iStat = oDxfFilOut.fopenWr (0,(char*)"Test_Output.dxf");

  dREC04RECNUMTYP  	dRecNoElePrev = 0;
  dREC04RECNUMTYP  	dRecNoEleNext = 0;

  dLinkListEntry1 = 0;
  dLinkListEntry2 = 0;

  // how many rows or words are stored?
  dREC04RECNUMTYP dWordsAmount = oRM1_Word.count();

  for ( dREC04RECNUMTYP ll=1; ll <= dWordsAmount; ll++)
  {
    // Get Element Data for Linked list object
    iStat = oTDB.getEntriesInLinkList( 0, ll, &dLinkListEntry1, &dLinkListEntry2);

    oDxfRowOut.clear();

    while (dLinkListEntry1 > 0)
    {
      // Get all data from linked list element node
      iStat = oTDB.ListNodeGetEleAll ( 0, dLinkListEntry1, &dWordPos, &dRecNoEleNext, &dRecNoElePrev, &dLetterPos);

      // next linked list node is actual Entry
      dLinkListEntry1 = dRecNoEleNext;

      // add next letter to dxf row
      oDxfRowOut = oDxfRowOut + (char) dLetterPos;
    }

    // write next row or word to new dxf file
    iStat = oDxfFilOut.Wr_StrDS1(0,&oDxfRowOut);

  }

  oDxfFilOut.fcloseFil(0);
  printf("\n");
  printf("Write Contents of Record Memory into mirror dxf. \n");

  //=== Read both dxf files and compare rows

  iStat = oDxfFilIn.fopenRd(0,(char*)"Test_Input.dxf");
  iStat = oDxfFilOut.fopenRd(0,(char*)"Test_Output.dxf");

  // read first row in both dxf files
  iStat = oDxfFilIn.Rd_StrDS1(0,&oDxfRowIn);
  iStat1 = oDxfFilOut.Rd_StrDS1(2,&oDxfRowOut);

  while (iStat1 >= 0)
  {

    // compare rows
    iStat = oDxfRowIn.compare(oDxfRowOut);
    assert(oDxfRowIn.compare(oDxfRowOut)==0);

    // read next row in both dxf files
    iStat = oDxfFilIn.Rd_StrDS1(0,&oDxfRowIn);
    iStat1 = oDxfFilOut.Rd_StrDS1(2,&oDxfRowOut);

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
