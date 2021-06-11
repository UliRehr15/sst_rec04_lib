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
// sstRec04LifoStore.cpp    11.06.21  Re.    16.11.12  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sstStr01Lib.h>
#include <sstMath01Lib.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

sstLiFoLongCls::sstLiFoLongCls()
{
  key = 0;       /**< Transport information */
  next = NULL;   /**< pointer to next element */
  zz = NULL;     /**< pointer to next element */
  tt = NULL;     /**< pointer to next element */
}

void sstLiFoLongCls::stackinit()
{
  void *ptr;
  ptr = malloc(sizeof *head);
  assert(ptr);
  head = (ul_node*) ptr;

  ptr = malloc(sizeof *zz);
  assert(ptr);
  zz = (ul_node*) ptr;

  head->next = zz; head->key =0;
  zz->next = zz;
}

void sstLiFoLongCls::push( long v)
{
  void *ptr;
  ptr =  malloc(sizeof *tt);
  assert(ptr);
  tt = (ul_node*) ptr;

  tt->key = v; tt->next = head->next;
  head->next = tt;
}

long sstLiFoLongCls::pop()
{
  long xx;
  tt = head->next; head->next = tt->next;
  xx = tt->key;
  free(tt);
  return xx;
}

int sstLiFoLongCls::stackempty()
{
  return head->next == zz;
}
sstLiFoIntCls::sstLiFoIntCls()
{
  key = 0;       /**< Transport information */
  next = NULL;   /**< pointer to next element */
  zz = NULL;     /**< pointer to next element */
  tt = NULL;     /**< pointer to next element */
}

void sstLiFoIntCls::stackinit()
{
  void *ptr;
  ptr = malloc(sizeof *head);
  assert(ptr);
  head = (ul_node*) ptr;

  ptr = malloc(sizeof *zz);
  assert(ptr);
  zz = (ul_node*) ptr;

  head->next = zz; head->key =0;
  zz->next = zz;
}

void sstLiFoIntCls::push( long v)
{
  void *ptr;
  ptr =  malloc(sizeof *tt);
  assert(ptr);
  tt = (ul_node*) ptr;

  tt->key = v; tt->next = head->next;
  head->next = tt;
}

long sstLiFoIntCls::pop()
{
  long xx;
  tt = head->next; head->next = tt->next;
  xx = tt->key;
  free(tt);
  return xx;
}

int sstLiFoIntCls::stackempty()
{
  return head->next == zz;
}

