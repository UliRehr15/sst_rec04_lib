
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
// sstRec04TreeKeyIntern.cpp    17.11.15  Re.    20.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//==============================================================================
sstRec04TreeHeaderCls::sstRec04TreeHeaderCls()
{
  dRoot = 0;
  iNodeOfs = 0;
  iOffset = 0;
  iSize = 0;
  eTyp = sstRecTyp_No;

  this->poDataKey = new (sstRec04CargoKeyInternCls );
}
//==============================================================================
