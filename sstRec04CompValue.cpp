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
// sstRec04CompValue.cpp    17.11.15  Re.    20.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//=============================================================================
sstRec04CompValueCls::sstRec04CompValueCls()
{
  CComp  = NULL;
  IComp  = NULL;
  LComp  = NULL;
  UIComp = NULL;
  ULComp = NULL;
  RComp  = NULL;
  DComp  = NULL;
}
//=============================================================================
