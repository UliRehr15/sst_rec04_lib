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
// sstRec04quicksort.cpp    11.06.21  Re.    09.11.12  Re.
//
// Quicksort functions
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//=============================================================================
//void sst_QSort_IniIntArray(int *test_array, unsigned long ulTArrayDim)
//{
//  int i, j;
//  for(i = ulTArrayDim,j=0; i > 0; i--,j++)
//  test_array[j] = i;
//}
//=============================================================================
//void sst_QSort_IniDblArray(double *test_array, unsigned long ulTArrayDim)
//{
//  int i;
//  int j;
//  for(i = ulTArrayDim,j=0; i > 0; i--,j++)
//  {
//    test_array[j] = (double) i;
//    test_array[j] = test_array[j] + 0.1;
//  }
//}
//=============================================================================
//void sst_QSort_IniStrArray(QSortStr_stru *sst_test_array)
//{
//  strcpy(sst_test_array[0].myStr,"s4");
//  strcpy(sst_test_array[1].myStr,"s3");
//  strcpy(sst_test_array[2].myStr,"s5");
//  strcpy(sst_test_array[3].myStr,"s2");
//  strcpy(sst_test_array[4].myStr,"s1");
//}
//=============================================================================
void sst_QSort_PrintIntArray(int *test_array, unsigned long ulTArrayDim)
{
  unsigned long i;
  for(i=0; i<ulTArrayDim; i++)    printf("%d ", test_array[i]);
  printf("\n");
}

//=============================================================================
void sst_QSort_PrintDblArray(double *test_array, unsigned long ulTArrayDim)
{
  unsigned long i;
  for(i=0; i<ulTArrayDim; i++)    printf("%lf ", test_array[i]);
  printf("\n");
}

//=============================================================================
void sst_QSort_PrintStrArray(sstRec04QSortStr_stru *sst_test_array, unsigned long ulStrArrayDim)
{
  unsigned long i;
  for(i=0; i<ulStrArrayDim; i++)    printf("%s ",sst_test_array[i].myStr);
  printf("\n");
}
//=============================================================================
void sst_QSort_IntSwap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

//=============================================================================
void sst_QSort_StrSwap(sstRec04QSortStr_stru *a, sstRec04QSortStr_stru *b)
{
  sstRec04QSortStr_stru tmp = *a;
  *a = *b;
  *b = tmp;
}

//=============================================================================
void sst_QSort_IntQSort(int *begin, int *end)
{
  int *ptr;
  int *split;
  if (end - begin <= 1)  return;

  ptr = begin;
  split = begin + 1;

  while (++ptr != end)
  {
    if (*ptr < *begin)
    {
      sst_QSort_IntSwap(ptr, split);
      ++split;
    }
  }
  sst_QSort_IntSwap(begin, split - 1);
  sst_QSort_IntQSort(begin, split - 1);
  sst_QSort_IntQSort(split, end);
}

//=============================================================================
void sst_QSort_StrQSort(sstRec04QSortStr_stru *begin, sstRec04QSortStr_stru *end, unsigned long sst_size)
{
  sstRec04QSortStr_stru *ptr;
  sstRec04QSortStr_stru *split;
  if (end - begin <= 1)  return;

  ptr = begin;
  split = begin + 1;

  while (++ptr != end)
  {
    int iStat = strcmp(ptr->myStr,begin->myStr);
    if (iStat < 0)
    {
      sst_QSort_StrSwap(ptr, split);
      ++split;
    }
  }
  sst_QSort_StrSwap(begin, split - 1);
  sst_QSort_StrQSort(begin, split - 1, sst_size);
  sst_QSort_StrQSort(split, end, sst_size);
}
//=============================================================================
void sst_QSort_StrQSortPrgBar(sstRec04QSortStr_stru      *begin,
                              sstRec04QSortStr_stru      *end,
                              sstMisc01ConPrgBarCls *sPrgBar)
//-----------------------------------------------------------------------------
{
  // int iStat=0;
  sstRec04QSortStr_stru *ptr;
  sstRec04QSortStr_stru *split;
  //-----------------------------------------------------------------------------
  if (end - begin <= 1)  return;

  ptr = begin;
  split = begin + 1;

  // Progress Bar: Tick Calls are one Point.
  sPrgBar->Tick();

  while (++ptr != end)
  {
    if ((strcmp(ptr->myStr,begin->myStr)) < 0)
    {
      sst_QSort_StrSwap(ptr, split);
      ++split;
    }
  }
  sst_QSort_StrSwap(begin, split - 1);
  sst_QSort_StrQSortPrgBar(begin, split - 1, sPrgBar);
  sst_QSort_StrQSortPrgBar(split, end, sPrgBar);
}
//=============================================================================
int sst_StrSSortPrgBar (int                 iKey,
                        sstRec04QSortStr_stru      *QSortStr,
                        unsigned long       ulArraySize,
                        sstMisc01ConPrgBarCls *sPrgBar)
//-----------------------------------------------------------------------------
{
  unsigned long kk;
  unsigned long ll;
  unsigned long llRunSum=0;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  for (kk=0; kk< ulArraySize; kk++)
  {
    for (ll=0; ll< ulArraySize-1; ll++)
    {
      int iStat = strcmp(QSortStr[ll].myStr,QSortStr[ll+1].myStr);
      if (iStat > 0)
      {
        sst_QSort_StrSwap(&QSortStr[ll],&QSortStr[ll+1]);
        llRunSum++;
      }
    }
    // Progress Bar: Tick Calls are one Point.
    sPrgBar->Tick();

    if (llRunSum == 0) break;
    llRunSum = 0;

  }

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
long sstIntPartition(int a[],
                     int l,    // c array lower range
                     int r,    // c array upper range
                     int max)  // c array max range
{
  int v;
  int i, j;
  int t;

  v = a[r];    // save upper value in array
  i = l-1;     // save lower value of range
  j = r;       // save upper value of range

  // printf("Start i= %i ,j= %i\n",i,j);

  for (;;)
  {
    while( (i<= max) && (a[++i] < v));  // protect range of array

    while( (j>0) && (a[--j] > v));  // protect range of array

    if(i >= j) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
  }
  t = a[i]; a[i] = a[r]; a[r] = t;
  return i;
}
//=============================================================================
long sstSrtStrPartition(sstRec04QSortStr_stru a[], long l, long r, long max)
{
  sstRec04QSortStr_stru v;
  long i, j;
  sstRec04QSortStr_stru t;

  v = a[r];
  i = l-1;
  j = r;

  for (;;)
  {
    // while(strcmp(a[++i].myStr,v.myStr)<0);
    while((i<max) && (strcmp(a[++i].myStr,v.myStr)<0));  // protect range of array

    // while(strcmp(a[--j].myStr,v.myStr)>0);
    while((j>0)&&(strcmp(a[--j].myStr,v.myStr)>0));  // protect range of array

    if(i >= j) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
  }
  t = a[i]; a[i] = a[r]; a[r] = t;
  return i;
}
//=============================================================================
void sstIntQSort( int                 a[],
                  int                 lArrayDim,
                  sstMisc01ConPrgBarCls *sConPrgBar)
{
  int i,l,r;
  sstLiFoIntCls oLiFoInt;  // LiFo Storage for signed integer
  l=0;
  r = lArrayDim - 1;

  oLiFoInt.stackinit();

  for(;;)
  {
    // Progress Bar: Tick Calls are one Point.
    sConPrgBar->Tick();

    while(r>l)
    {
      i = sstIntPartition(a,l,r,lArrayDim-1);
      if(i-l > r-i)
      {
        oLiFoInt.push(l);
        oLiFoInt.push(i-1);
        l=i+1;
      }
      else
      {
        oLiFoInt.push(i+1);
        oLiFoInt.push(r);
        r=i-1;
      }
    }
    if(oLiFoInt.stackempty()) break;
    r = oLiFoInt.pop();
    l = oLiFoInt.pop();
  }
}
//=============================================================================
void sstRec04SrtStrQSort( sstRec04QSortStr_stru       a[],
                     long                lArrayDim,
                     sstMisc01ConPrgBarCls *sConPrgBar)
{
  long i,l,r;
  sstLiFoLongCls oLiFoLong;  // LiFo Storage for long integer
  l=0;
  r = lArrayDim - 1;

  oLiFoLong.stackinit();

  for(;;)
  {
    // Progress Bar: Tick Calls are one Point.
    sConPrgBar->Tick();

    while(r>l)
    {
      i = sstSrtStrPartition(a,l,r, lArrayDim-1);
      if(i-l > r-i)
      {
        oLiFoLong.push(l);
        oLiFoLong.push(i-1);
        l=i+1;
      }
      else
      {
        oLiFoLong.push(i+1);
        oLiFoLong.push(r);
        r=i-1;
      }
    }
    if(oLiFoLong.stackempty()) break;
    r = oLiFoLong.pop();
    l = oLiFoLong.pop();
  }
}
//=============================================================================

