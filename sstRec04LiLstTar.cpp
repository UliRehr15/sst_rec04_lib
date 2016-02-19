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
// sstRec04LiLstTar.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//-----------------------------------------------------------------------------
sstRec04LiLstTarCls::sstRec04LiLstTarCls()
{
  this->ulNumEle = 0;
}
//=============================================================================

