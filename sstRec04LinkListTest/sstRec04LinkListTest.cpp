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
// sst_rec04_lib_test.cpp    13.09.15  Re.    13.09.15  Re.
//
// test frame for sstRec04Lib linked list fuctions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sstRec04Lib.h>

#include "sstRec04LinkListTest.h"

// #define BUFSIZE 100

int main()
{

//=============================================================================
  int iStat = 0;
  {
    // ======== linked List test ==============================================

    // Define 3 RecMem Objects
    dREC04RECNUMTYP  	dRecNoHed=0;
    int iTestVal=0;
    sstRec04Cls oRecMem1(sizeof(iTestVal));

    dREC04RECNUMTYP  	dRecNoEle=0;
    unsigned long ulTestVal=0;
    sstRec04Cls oRecMem2(sizeof(ulTestVal));

    dREC04RECNUMTYP  	dRecNoTar=0;
    double dTestVal=0.0;
    sstRec04Cls oRecMem3(sizeof(dTestVal));

    sstRec04LiLstCls oLinkList;

    // Initialize Linked List with Header, List element and target RecMem objects
    // All 3 RecMem has to be emtpy
    iStat = oLinkList.Define3(0, &oRecMem1, &oRecMem2, &oRecMem3);
    assert(iStat == 0);

    // === Fill linked list =====================================================

    // Get Element Data for Linked list object
    dREC04RECNUMTYP  	dLinkListEntry1 = 0;
    dREC04RECNUMTYP  	dLinkListEntry2 = 0;
    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);
    assert(iStat == -2);  // should be error, because head RecMem is empty

    // Write some data into this 3 RecMem objects
    iStat = oRecMem2.WritNew(0,&ulTestVal,&dRecNoEle);
    // iStat = oRecMem2.WritNew(0,&ulTestVal,&dRecNoEle);

    iStat = oRecMem3.WritNew(0,&dTestVal,&dRecNoTar);
    // iStat = oRecMem3.WritNew(0,&dTestVal,&dRecNoTar);

    iStat = oRecMem1.WritNew(0,&iTestVal,&dRecNoHed);
    assert(iStat == 0);

    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);
    // no linked list of dRecNoHed

    // === Create new linked list
    // Extend Linked List at end
    iStat = oLinkList.ExtendAtEnd ( 0, 1, 1, 1);
    assert(iStat == 0);

    // Get Element Data for Linked list object
    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);

    assert(iStat == 0);
    assert(dLinkListEntry1 == 1);
    assert(dLinkListEntry2 == 1);

    // Get Number of uses for target record
    dREC04RECNUMTYP  	dNumUse=0;
    iStat = oLinkList.GetTarNumUse ( 0, dRecNoTar, &dNumUse);
    assert(dNumUse == 1);  // Target Element is one time used by link List

    iStat = oRecMem3.WritNew(0,&dTestVal,&dRecNoTar);
    iStat = oRecMem2.WritNew(0,&ulTestVal,&dRecNoEle);

    iStat = oLinkList.ExtendAtEnd ( 0, 1, 2, 2);
    assert(iStat == 0);

    // Get Element Data for Linked list object
    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);
    assert(iStat == 0);
    assert(dLinkListEntry1 == 1);
    assert(dLinkListEntry2 == 2);

    // === fill second header list ============================================

    // Write some data into this 3 RecMem objects
    iStat = oRecMem2.WritNew(0,&ulTestVal,&dRecNoEle);
    iStat = oRecMem3.WritNew(0,&dTestVal,&dRecNoTar);
    iStat = oRecMem1.WritNew(0,&iTestVal,&dRecNoHed);
    assert(iStat == 0);

    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);
    // no linked list of dRecNoHed

    // === Create new linked list
    // Extend Linked List at end
    iStat = oLinkList.ExtendAtEnd ( 0, dRecNoHed, dRecNoEle, dRecNoTar);
    assert(iStat == 0);

    // Get Element Data for Linked list object
    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);

    assert(iStat == 0);
    assert(dLinkListEntry1 == 3);
    assert(dLinkListEntry2 == 3);

    iStat = oRecMem3.WritNew(0,&dTestVal,&dRecNoTar);
    iStat = oRecMem2.WritNew(0,&ulTestVal,&dRecNoEle);

    iStat = oLinkList.ExtendAtEnd ( 0, dRecNoHed, dRecNoEle, dRecNoTar);
    assert(iStat == 0);

    // Get Element Data for Linked list object
    iStat = oLinkList.getEntriesInLinkList( 0, dRecNoHed, &dLinkListEntry1, &dLinkListEntry2);
    assert(iStat == 0);
    assert(dLinkListEntry1 == 3);
    assert(dLinkListEntry2 == 4);

    // === Read linked list =====================================================

    // Get entry Data for Linked list object
    iStat = oLinkList.getEntriesInLinkList( 0, 1, &dLinkListEntry1, &dLinkListEntry2);

    dREC04RECNUMTYP  	dRecNoElePrev = 0;
    dREC04RECNUMTYP  	dRecNoEleNext = 0;

    // Get all data from element node
    iStat = oLinkList.ListNodeGetEleAll ( 0, dLinkListEntry1, &dRecNoHed, &dRecNoEleNext, &dRecNoElePrev, &dRecNoTar);
    assert(iStat == 0);
    assert(dRecNoEleNext == 2);
    assert(dRecNoTar == 1);
    dLinkListEntry1 = dRecNoEleNext;

    // Get all data from element node
    iStat = oLinkList.ListNodeGetEleAll ( 0, dLinkListEntry1, &dRecNoHed, &dRecNoEleNext, &dRecNoElePrev, &dRecNoTar);
    assert(iStat == 0);
    assert(dRecNoEleNext == 0);
    assert(dRecNoTar == 2);
  }

  return 0;
}
//=============================================================================
