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
// sstRec04Header.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//=============================================================================
sstRec04HeaderCls::sstRec04HeaderCls()
{
  strncpy(cVersionstring,(char*)"sstRec02",10);    /**< Version String, for exampe sstRec02 */
  dRecSize = 0;  /**< Size of every Record */
  memset( cRecChgDateTime, 0, 18);    /**< Write Change Date, for exampe 151012 */
  memset( cRecNewDateTime, 0, 18);    /**< Write New Date, for exampe 151012 */
  bDel = 0;    /**< Delete Flag */
  bMark = 0;   /**< Mark Flag */
}
//=============================================================================
dREC04RECSIZTYP sstRec04HeaderCls::getRecSize() const
{
  return this->dRecSize;
}
//=============================================================================
void sstRec04HeaderCls::setRecSize(const dREC04RECSIZTYP &dTmpValue)
{
  this->dRecSize = dTmpValue;
}
//=============================================================================
char* sstRec04HeaderCls::GetVersStr()
{
  return this->cVersionstring;
}
//=============================================================================
void sstRec04HeaderCls::SetVersStr(char *cTmpNam)
{
  strncpy(this->cVersionstring,cTmpNam,10);
}
//=============================================================================
void sstRec04HeaderCls::SetNewDate()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d.%X", &tstruct);
  strncpy(this->cRecNewDateTime,buf,18);
}
//=============================================================================
void sstRec04HeaderCls::SetChangeDate()
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d.%X", &tstruct);
  strncpy(this->cRecChgDateTime,buf,18);
}
//==============================================================================
void sstRec04HeaderCls::RecSetDeleted()
{
  this->bDel = true;
}
//==============================================================================
void sstRec04HeaderCls::RecSetMarked()
{
  this->bMark = true;
}
//==============================================================================
void sstRec04HeaderCls::RecSetUndeleted()
{
  this->bDel = false;
}
//==============================================================================
void sstRec04HeaderCls::RecSetUnmarked()
{
  this->bMark = false;
}
//==============================================================================
bool sstRec04HeaderCls::RecGetDeleteStatus()
{
  return this->bDel;
}
//==============================================================================
bool sstRec04HeaderCls::RecGetMarkStatus()
{
  return this->bMark;
}
//==============================================================================
