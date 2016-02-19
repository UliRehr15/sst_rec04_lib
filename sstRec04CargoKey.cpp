/**********************************************************************
 *
 * sstRec02Lib - cpp template library for sst
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
// sstRec04CargoKey.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//=============================================================================
sstRec04CargoKeyCls::sstRec04CargoKeyCls()
{
    this->poCargoKeyIntern = new(sstRec04CargoKeyInternCls);
}
//=============================================================================
sstRec04CargoKeyCls::~sstRec04CargoKeyCls()
{
    delete(this->poCargoKeyIntern);
}
//=============================================================================
