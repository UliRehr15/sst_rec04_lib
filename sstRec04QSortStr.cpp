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
// sstRec04QSortStr.cpp    11.06.21  Re.    09.11.12  Re.
//
// Quicksort functions for strings
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

//#include <kern.h>
//#include <mathem.h>
//#include <str_lib.h>
//#include <sstlib.h>     // sstlib-Header

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>
#include <sstMisc01Lib.h>

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
//void sst_QSort_IniStrArray(QSortStrCls *sst_test_array)
//{
//  strcpy(sst_test_array[0].myStr,"s4");
//  strcpy(sst_test_array[1].myStr,"s3");
//  strcpy(sst_test_array[2].myStr,"s5");
//  strcpy(sst_test_array[3].myStr,"s2");
//  strcpy(sst_test_array[4].myStr,"s1");
//}
//=============================================================================
void sst_QSort2_PrintIntArray(int *test_array, unsigned long ulTArrayDim)
{
  unsigned long i;
  for(i=0; i<ulTArrayDim; i++)    printf("%d ", test_array[i]);
  printf("\n");
}

//=============================================================================
void sst_QSort2_PrintDblArray(double *test_array, unsigned long ulTArrayDim)
{
  unsigned long i;
  for(i=0; i<ulTArrayDim; i++)    printf("%lf ", test_array[i]);
  printf("\n");
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
// void sst_print_test_array(void)
void sst_QSort2_PrintStrArray(sstRec04QSortStrCls *sst_test_array, unsigned long ulStrArrayDim)
{
  unsigned long i;
  for(i=0; i<ulStrArrayDim; i++)    printf("%s ",sst_test_array[i].getStr().c_str());
  printf("\n");
}


//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
void sst_QSort2_IntSwap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
void sst_QSort2_StrSwap(sstRec04QSortStrCls *a, sstRec04QSortStrCls *b)
{
  sstRec04QSortStrCls tmp = *a;
  *a = *b;
  *b = tmp;
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
void sst_QSort2_IntQSort(int *begin, int *end)
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
      sst_QSort2_IntSwap(ptr, split);
      ++split;
    }
  }
  sst_QSort2_IntSwap(begin, split - 1);
  sst_QSort2_IntQSort(begin, split - 1);
  sst_QSort2_IntQSort(split, end);
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
void sst_QSort2_StrQSort(sstRec04QSortStrCls *begin, sstRec04QSortStrCls *end, unsigned long sst_size)
{
  sstRec04QSortStrCls *ptr;
  sstRec04QSortStrCls *split;
  if (end - begin <= 1)  return;

  ptr = begin;
  split = begin + 1;
  // split = begin + sst_size;

  while (++ptr != end)
  // while ((ptr+sst_size) != end)
  {
    // if (*ptr < *begin)
    int iStat = strcmp(ptr->getStr().c_str(),begin->getStr().c_str());
    if (iStat < 0)
    {
      sst_QSort2_StrSwap(ptr, split);
      ++split;
      // split = split + sst_size;
    }
  }
  sst_QSort2_StrSwap(begin, split - 1);
  sst_QSort2_StrQSort(begin, split - 1, sst_size);
  sst_QSort2_StrQSort(split, end, sst_size);
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
void sst_QSort2_StrQSortPrgBar(sstRec04QSortStrCls      *begin,
                              sstRec04QSortStrCls      *end,
                              sstMisc01ConPrgBarCls *sPrgBar)
//-----------------------------------------------------------------------------
{
  // int iStat=0;
  sstRec04QSortStrCls *ptr;
  sstRec04QSortStrCls *split;
  //-----------------------------------------------------------------------------
  if (end - begin <= 1)  return;

  ptr = begin;
  split = begin + 1;
  // split = begin + sst_size;

  // Progress Bar: Tick Calls are one Point.
  // sst_consoleProgress1Tick ( sPrgBar);
  sPrgBar->Tick();

  while (++ptr != end)
  // while ((ptr+sst_size) != end)
  {
    // if (*ptr < *begin)
    // int iStat = strcmp(ptr->myStr,begin->myStr);
    if ((strcmp(ptr->getStr().c_str(),begin->getStr().c_str())) < 0)
    {
      sst_QSort2_StrSwap(ptr, split);
      ++split;
      // split = split + sst_size;
    }
  }
  sst_QSort2_StrSwap(begin, split - 1);
  sst_QSort2_StrQSortPrgBar(begin, split - 1, sPrgBar);
  sst_QSort2_StrQSortPrgBar(split, end, sPrgBar);
}
//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
int sst_StrSSortPrgBar (int                 iKey,
                        sstRec04QSortStrCls      *QSortStr,
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
      int iStat = strcmp(QSortStr[ll].getStr().c_str(),QSortStr[ll+1].getStr().c_str());
      if (iStat > 0)
      {
        sst_QSort2_StrSwap(&QSortStr[ll],&QSortStr[ll+1]);
        llRunSum++;
      }
    }
    // Progress Bar: Tick Calls are one Point.
    // sst_consoleProgress1Tick ( sPrgBar);
    sPrgBar->Tick();

    // printf(" %ld %ld \n" ,kk+1, llRunSum);
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
long sstIntPartition2(int a[],
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
    // while(a[++i] < v);
    while( (i<= max) && (a[++i] < v));  // protect range of array

    // while(a[--j] > v);
    while( (j>0) && (a[--j] > v));  // protect range of array

    // printf("v= %i ,i= %i ,j= %i\n",v,i,j);

    if(i >= j) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
  }
  t = a[i]; a[i] = a[r]; a[r] = t;
  return i;
}
//=============================================================================
long sstSrtStrPartition2(sstRec04QSortStrCls a[], long l, long r, long max)
{
  sstRec04QSortStrCls v;
  long i, j;
  sstRec04QSortStrCls t;

  v = a[r];
  i = l-1;
  j = r;

  for (;;)
  {
    while((i<max) && (strcmp(a[++i].getStr().c_str(),v.getStr().c_str())<0));  // protect range of array

    while((j>0)&&(strcmp(a[--j].getStr().c_str(),v.getStr().c_str())>0));      // protect range of array

    if(i >= j) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
  }
  t = a[i]; a[i] = a[r]; a[r] = t;
  return i;
}
//=============================================================================
void sstIntQSort2( int                 a[],
                  int                 lArrayDim,
                  sstMisc01ConPrgBarCls *sConPrgBar)
{
  int i,l,r;
  sstLiFoIntCls oLiFoInt;  // LiFo Storage for signed integer
  l=0;
  r = lArrayDim - 1;

  oLiFoInt.stackinit();
  // ul_stackinit();

  for(;;)
  {
    // Progress Bar: Tick Calls are one Point.
    // sst_consoleProgress1Tick ( sConPrgBar);
    sConPrgBar->Tick();

    while(r>l)
    {
      i = sstIntPartition2(a,l,r,lArrayDim-1);
      if(i-l > r-i)
      {
        oLiFoInt.push(l);
        oLiFoInt.push(i-1);
        // ul_push(l);
        // ul_push(i-1);
        l=i+1;
      }
      else
      {
        oLiFoInt.push(i+1);
        oLiFoInt.push(r);
        // ul_push(i+1);
        // ul_push(r);
        r=i-1;
      }
    }
    if(oLiFoInt.stackempty()) break;
    r = oLiFoInt.pop();
    l = oLiFoInt.pop();
    // if(ul_stackempty()) break;
    // r = ul_pop();
    // l = ul_pop();
  }
}
//=============================================================================
void sstRec04SrtStrQSort2( sstRec04QSortStrCls           a[],
                     long                   lArrayDim,
                     sstMisc01ConPrgBarCls *sConPrgBar)
{
  long i,l,r;
  sstLiFoLongCls oLiFoLong;  // LiFo Storage for long integer
  l=0;
  r = lArrayDim - 1;

  oLiFoLong.stackinit();
  // ul_stackinit();

  for(;;)
  {
    // Progress Bar: Tick Calls are one Point.
    // sst_consoleProgress1Tick ( sConPrgBar);
    sConPrgBar->Tick();

    while(r>l)
    {
      i = sstSrtStrPartition2(a,l,r, lArrayDim-1);
      if(i-l > r-i)
      {
        oLiFoLong.push(l);
        oLiFoLong.push(i-1);
        // ul_push(l);
        // ul_push(i-1);
        l=i+1;
      }
      else
      {
        oLiFoLong.push(i+1);
        oLiFoLong.push(r);
        // ul_push(i+1);
        // ul_push(r);
        r=i-1;
      }
    }
    if(oLiFoLong.stackempty()) break;
    r = oLiFoLong.pop();
    l = oLiFoLong.pop();
    // if(ul_stackempty()) break;
    // r = ul_pop();
    // l = ul_pop();
  }
}
//=============================================================================
sstRec04QSortStrCls::sstRec04QSortStrCls()
{
  memset( this->myStr, 0, dQSORT_TEXTLEN);
  this->ulMyLongInt = 0;
}
//=============================================================================
std::string sstRec04QSortStrCls::getStr()
{
  std::string oTmpStr;
  oTmpStr = this->myStr;
  return oTmpStr;
}
//=============================================================================
unsigned long int sstRec04QSortStrCls::getLong()
{
  return this->ulMyLongInt;
}
//=============================================================================
void sstRec04QSortStrCls::setString(const std::string oStr)
{
  strncpy(this->myStr,oStr.c_str(),dQSORT_TEXTLEN-1);
}
//=============================================================================
void sstRec04QSortStrCls::setLong(const unsigned long int ulVal)
{
  this->ulMyLongInt = ulVal;
}
//=============================================================================
void sstRec04QSortStrCls::set(const std::string oStr, const unsigned long int ulVal)
{
  strncpy(this->myStr,oStr.c_str(),dQSORT_TEXTLEN-1);
  this->ulMyLongInt = ulVal;
}
//=============================================================================
