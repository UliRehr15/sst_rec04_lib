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
// sstRec04TestRec.cpp    17.11.15  Re.    17.10.15  Re.
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>

#include "sstRec04Lib.h"
#include "sstRec04LibInt.h"

//=============================================================================
sstRec04TestRec1Cls::sstRec04TestRec1Cls()
{
  // dVal = 0.0;         /**< Test value Double  */
  iVal = 0;         /**< Test value Integer  */
  memset(cVal,0,10);  /**< Test value Char/Text */

}
//=============================================================================
int sstRec04TestRec1Cls::SetAll(int iTmpVal, char *cTmpVal)
{
  iVal = iTmpVal;
  strncpy(cVal,cTmpVal,251);
  return 0;
}
//=============================================================================
// Csv Read Function
int sstRec04TestRec1Cls::Csv_Read(int iKey, std::string *sTestSys_Str)
{
  int iStat = 0;
  // char cDelimit[2]=";";
//  Bloc Function1 Start
//  std::string sErrTxt;
  sstStr01Cls oCsvStr;
  // long TPos = 0;
  int iRet  = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  if (iStat >= 0)
    iStat = oCsvStr.CsvString2_Int2( 0, sTestSys_Str, &this->iVal);
  if (iStat >= 0)
    iStat = oCsvStr.CsvString2_Char( 0, sTestSys_Str, this->cVal,11);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function1 End
  return iStat;
}

//=============================================================================
// Csv Write Function
int sstRec04TestRec1Cls::Csv_Write(int iKey, std::string *sTestSys_Str)
{
  int iStat = 0;
  sstStr01Cls oCsvStr;

//  Bloc Function Write Start
  int iRet  = 0;
  if ( iKey != 0) return -1;

  if (iStat >= 0)
    iStat = oCsvStr.Csv_Int2_2String( 0, this->iVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = oCsvStr.Csv_Char_2String( 0, this->cVal, sTestSys_Str);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function Write End
  return iStat;
}
//=============================================================================
// Constructor
sstRec04TestRec1FncCls::sstRec04TestRec1FncCls()
{
  this->oFrmtTyp.SetBoolTyp(0,2);
  this->dActRecNo = 0;
  this->poTestRec1Table = new sstRec04Cls(sizeof(sstRec04TestRec1Cls));
  this->sErrStr.clear();
}
//=============================================================================
// Destructor
sstRec04TestRec1FncCls::~sstRec04TestRec1FncCls()
{
  delete(this->poTestRec1Table);
}
//=============================================================================
// Csv Read Function
int sstRec04TestRec1FncCls::Csv_Read(int iKey, std::string *sTestSys_Str, sstRec04TestRec1Cls *oTestSysTypTestRecCls)
{
  int iStat = 0;
  sstStr01Cls oCsvStr;
  int iRet  = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  this->oFrmtTyp.SetReadPositon(0,0);

  if (iStat >= 0)
    iStat = oCsvStr.CsvString2_Int2( 0, sTestSys_Str, &oTestSysTypTestRecCls->iVal);
  if (iStat >= 0)
    iStat = oCsvStr.CsvString2_Char( 0, sTestSys_Str, oTestSysTypTestRecCls->cVal,11);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function1 End
  return iStat;
}

//=============================================================================
// Csv Write Function
int sstRec04TestRec1FncCls::Csv_Write(int iKey, sstRec04TestRec1Cls *oTestSysTypTestRecCls, std::string *sTestSys_Str)
{
  sstStr01Cls oCsvStr;
  int iStat = 0;
  char cFrmtStrDbl[20];
  char cFrmtStrFlt[20];

  strncpy(cFrmtStrFlt,"%# 06.2f",20);
  strncpy(cFrmtStrDbl,"%# 015.4f",20);

//  Bloc Function Write Start
  int iRet  = 0;
  if ( iKey != 0) return -1;

  this->oFrmtTyp.SetReadPositon(0,0);

  if (iStat >= 0)
    iStat = oCsvStr.Csv_Int2_2String( 0, oTestSysTypTestRecCls->iVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = oCsvStr.Csv_Char_2String( 0, oTestSysTypTestRecCls->cVal, sTestSys_Str);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function Write End
  return iStat;
}

//=============================================================================
int sstRec04TestRec1FncCls::OpenReadCsvFile(int iKey, char *cCsvFilNam)
{

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iStat = 0;
  int iStat1 = 0;

  sstMisc01AscRowCls oImpRow;
  sstMisc01AscFilCls oImpFil;

  sstRec04TestRec1Cls oTestRec1;
  std::string sRecStr;

  dREC04RECNUMTYP dRecNo = 0;

  //-----------------------------------------------------------------------------

  iStat = oImpFil.fopenRd ( 0, cCsvFilNam);

  if (iStat < 0) return -2;

  // iStat = this->poRecDss-> ->Open(0,sizeof(sstRec04TestRec1Cls),100,(char*)"RecDss");
  // if (iStat < 0) return -3;

  // Eine Zeile aus Ascii-Datei lesen.
  iStat1 = oImpFil.rd_line( 0, &oImpRow);

  while (iStat1 >= 0)
  {
    // iStat = Str1Cpy( 0, &sRecStr, oImpRow.Txt);
    iStat = oImpRow.Line_toStr1(0,&sRecStr);

    iStat = this->Csv_Read(0,&sRecStr,&oTestRec1);
    assert(iStat == 0);

    iStat = this->poTestRec1Table->WritNew(0,&oTestRec1,&dRecNo);

    // Eine Zeile aus Ascii-Datei lesen.
    iStat1 = oImpFil.rd_line( 0, &oImpRow);
  }

  // CascObjekt beenden und zugehörige Datei schließen.
  iStat = oImpFil.fcloseFil(0);

  return 0;
}
//=============================================================================
int sstRec04TestRec1FncCls::ReadRecPos(int iKey,dREC04RECNUMTYP dRecNo, sstRec04TestRec1Cls *oTestRec1) const
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  // dActRecNo++;
  iStat = this->poTestRec1Table->Read( 0, dRecNo, oTestRec1);

  return iStat;
}
//=============================================================================
int sstRec04TestRec1FncCls::ReadRecNext(int iKey,dREC04RECNUMTYP *dRecNo, sstRec04TestRec1Cls *oTestRec1)
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  dActRecNo++;
  iStat = this->poTestRec1Table->Read( 0, dActRecNo, oTestRec1);

  *dRecNo = dActRecNo;

  return iStat;
}
//=============================================================================
int sstRec04TestRec1FncCls::WriteNew(int iKey,dREC04RECNUMTYP *dRecNo, sstRec04TestRec1Cls *oTestRec1)
{
  int iStat = 0;
  // dREC04RECNUMTYP dRecNo = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poTestRec1Table->WritNew( 0, oTestRec1, dRecNo);

  return iStat;
}
//=============================================================================
int sstRec04TestRec1FncCls::WriteRecPos(int iKey,dREC04RECNUMTYP dRecNo, sstRec04TestRec1Cls *oTestRec1)
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poTestRec1Table->Writ( 0,oTestRec1,dRecNo);

  return iStat;
}
//=============================================================================
int sstRec04TestRec1FncCls::DeleteRecPos(int            iKey,
                                 dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;

  int iStat = this->poTestRec1Table->RecSetDeleted(0,dRecNo);

  return iStat;
}
//=============================================================================
dREC04RECNUMTYP sstRec04TestRec1FncCls::RecordCount() const
{
  dREC04RECNUMTYP dRecNo = 0;
  dRecNo = this->poTestRec1Table->count();

  return dRecNo;
}
//=============================================================================
int sstRec04TestRec1FncCls::CloseCsvFile(int iKey, char *cCsvFilNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  dREC04RECNUMTYP dRecNo = 0;
  sstRec04TestRec1Cls oTestRec;
  std::string sOutStr;
  std::string sErrStr;

  // CascObjekt öffnen zum Lesen.
  sstMisc01AscFilCls oExpFil;
  sstMisc01AscRowCls oExpRow;

  dRecNo = this->poTestRec1Table->count();
  iStat = oExpFil.fopenWr ( 0, cCsvFilNam);
  if(iStat < 0)
  {
    // delete (this->poTestRec1Table);
    return -2;
  }

  for (dREC04RECNUMTYP ll = 1; ll <= dRecNo; ll++)
  {
    iStat = this->poTestRec1Table->Read( 0, ll, &oTestRec);
    if (iStat >= 0)
    {  // if no read error and not marked deleted
      // iStat = Str1_Init(0,&sOutStr);
      sOutStr.clear();
      this->Csv_Write( 0, &oTestRec, &sOutStr);
      oExpRow.Str1_toLine(0,&sOutStr);
      oExpFil.wr_line( 0, &oExpRow);
    }
  }
  // iStat = thisoRecDss.Close(0);
  // delete (this->poTestRec1Table);
  iStat = oExpFil.fcloseFil(0);

  return iStat;
}
//=============================================================================
sstRec04TestRec2Cls::sstRec04TestRec2Cls()
{
  iVal = 0;           /**< Test value Integer */
  uiVal = 333;        /**< Test value Unsigned Integer */
  lVal = 0;           /**< Test value Long Integer */
  ulVal = 0;          /**< Test value Unsigned Long Integer */
  fVal = 0.0;         /**< Test value Float  */
  dVal = 0.0;         /**< Test value Double  */
  bVal = 0;           /**< Test value Bool */
  memset(cVal,0,10);  /**< Test value Char/Text */
}
//=============================================================================
int sstRec04TestRec2Cls::SetAll(int iTmpVal,
                        unsigned int uiTmpVal,
                        long lTmpVal,
                        unsigned long ulTmpVal,
                        float fTmpVal,
                        double dTmpVal,
                        bool bTmpVal,
                        char *cTmpVal)
//-----------------------------------------------------------------------------
{
  iVal = iTmpVal;
  uiVal = uiTmpVal;
  lVal = lTmpVal;
  ulVal = ulTmpVal;
  fVal = fTmpVal;
  dVal = dTmpVal;
  bVal = bTmpVal;
  strncpy(cVal,cTmpVal,10);
  return 0;
}
//=============================================================================
// Constructor
sstRec04TestRec2FncCls::sstRec04TestRec2FncCls()
{
  oFrmtTyp.SetBoolTyp(0,2);
  dActRecNo = 0;
  this->poTestRec2Table = new sstRec04Cls(sizeof(sstRec04TestRec2Cls));
  this->sErrStr.clear();
}
//=============================================================================
// Destructor
sstRec04TestRec2FncCls::~sstRec04TestRec2FncCls()
{
  delete(this->poTestRec2Table);
}
//=============================================================================
// Csv Read Function
int sstRec04TestRec2FncCls::Csv_Read(int iKey, std::string *sTestSys_Str, sstRec04TestRec2Cls *oTestSysTypTestRecCls)
{
  int iStat = 0;
  int iRet  = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  this->oFrmtTyp.SetReadPositon(0,0);

  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_Int2( 0, sTestSys_Str, &oTestSysTypTestRecCls->iVal);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_UInt2( 0, sTestSys_Str, &oTestSysTypTestRecCls->uiVal);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_Int4( 0, sTestSys_Str, &oTestSysTypTestRecCls->lVal);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_UInt4( 0, sTestSys_Str, &oTestSysTypTestRecCls->ulVal);
  if (iStat >= 0)
  {
    iStat = this->oFrmtTyp.CsvString2_Flt( 0, sTestSys_Str, &oTestSysTypTestRecCls->fVal);
//    iStat = this->oFrmtTyp.CsvString2_Dbl( 0, sTestSys_Str, &dVal);
//    oTestSysTypTestRecCls->fVal = (float) dVal;
  }
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_Dbl( 0, sTestSys_Str, &oTestSysTypTestRecCls->dVal);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_Bool( 0, sTestSys_Str, &oTestSysTypTestRecCls->bVal);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.CsvString2_Char( 0, sTestSys_Str, oTestSysTypTestRecCls->cVal,11);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function1 End
  return iStat;
}

//=============================================================================
// Complete function description is in headerfile
//-----------------------------------------------------------------------------
// Csv Write Function
int sstRec04TestRec2FncCls::Csv_Write(int iKey, sstRec04TestRec2Cls *oTestSysTypTestRecCls, std::string *sTestSys_Str)
{
  int iStat = 0;
  char cFrmtStrDbl[20];
  char cFrmtStrFlt[20];

  strncpy(cFrmtStrFlt,"%# 6.2f",20);
  strncpy(cFrmtStrDbl,"%# 015.4f",20);

//  Bloc Function Write Start
  int iRet  = 0;
  if ( iKey != 0) return -1;

  this->oFrmtTyp.SetReadPositon(0,0);

  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Int2_2String( 0, oTestSysTypTestRecCls->iVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_UInt2_2String ( 0, oTestSysTypTestRecCls->uiVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Int4_2String ( 0, oTestSysTypTestRecCls->lVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_UInt4_2String ( 0, oTestSysTypTestRecCls->ulVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Real_2String ( 0, oTestSysTypTestRecCls->fVal, sTestSys_Str);
  // iStat = this->oFrmtTyp.Csv_Real_2String ( 0, cFrmtStrFlt, oTestSysTypTestRecCls->fVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Dbl_2String ( 0, oTestSysTypTestRecCls->dVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Bool_2String ( 0, oTestSysTypTestRecCls->bVal, sTestSys_Str);
  if (iStat >= 0)
    iStat = this->oFrmtTyp.Csv_Char_2String ( 0, oTestSysTypTestRecCls->cVal, sTestSys_Str);

  // Fatal Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  // Small Errors will given back
  iRet = iStat;

//  Bloc Function Write End
  return iStat;
}

//=============================================================================
int sstRec04TestRec2FncCls::OpenReadCsvFile(int iKey, char *cCsvFilNam)
{

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  int iStat = 0;
  int iStat1 = 0;

  sstMisc01AscRowCls oImpRow;
  sstMisc01AscFilCls oImpFil;

  sstRec04TestRec2Cls oTestRec2;
  std::string sRecStr;

  dREC04RECNUMTYP dRecNo = 0;

  //-----------------------------------------------------------------------------

  iStat = oImpFil.fopenRd ( 0, cCsvFilNam);

  if (iStat < 0) return -2;

  // iStat = this->oRecDss.Open(0,sizeof(sstRec04TestRec2Cls),100,(char*)"RecDss");
  // if (iStat < 0) return -3;

  // Eine Zeile aus Ascii-Datei lesen.
  iStat1 = oImpFil.rd_line( 0, &oImpRow);

  while (iStat1 >= 0)
  {
    // iStat = Str1Cpy( 0, &sRecStr, oImpRow.Txt);
    oImpRow.Line_toStr1(0,&sRecStr);

    iStat = this->Csv_Read(0,&sRecStr,&oTestRec2);
    assert(iStat == 0);

    iStat = this->poTestRec2Table->WritNew( 0, &oTestRec2, &dRecNo);

    // Eine Zeile aus Ascii-Datei lesen.
    iStat1 = oImpFil.rd_line( 0, &oImpRow);
  }

  // CascObjekt beenden und zugehörige Datei schließen.
  iStat = oImpFil.fcloseFil(0);

  return 0;
}
//=============================================================================
int sstRec04TestRec2FncCls::ReadRecPos(int iKey,dREC04RECNUMTYP dRecNo, sstRec04TestRec2Cls *oTestRec1) const
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  // dActRecNo++;
  iStat = this->poTestRec2Table->Read( 0, dRecNo, oTestRec1);

  return iStat;
}
//=============================================================================
int sstRec04TestRec2FncCls::ReadRecNext(int iKey,dREC04RECNUMTYP *dRecNo, sstRec04TestRec2Cls *oTestRec1)
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  dActRecNo++;
  iStat = this->poTestRec2Table->Read( 0, dActRecNo, oTestRec1);

  *dRecNo = dActRecNo;

  return iStat;
}
//=============================================================================
int sstRec04TestRec2FncCls::WriteNew(int iKey,dREC04RECNUMTYP *dRecNo, sstRec04TestRec2Cls *oTestRec1)
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  iStat = this->poTestRec2Table->WritNew( 0, oTestRec1, dRecNo);

  return iStat;
}
//=============================================================================
int sstRec04TestRec2FncCls::WriteRecPos(int iKey,dREC04RECNUMTYP dRecNo, sstRec04TestRec2Cls *oTestRec1)
{
  int iStat = 0;

  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

  iStat = this->poTestRec2Table->Writ( 0, oTestRec1, dRecNo);

  return iStat;
}
//=============================================================================
int sstRec04TestRec2FncCls::DeleteRecPos(int            iKey,
                                 dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;

  int iStat = this->poTestRec2Table->RecSetDeleted(0,dRecNo);
  // delete(this->poRecDss);

  return iStat;
}
//=============================================================================
dREC04RECNUMTYP sstRec04TestRec2FncCls::RecordCount() const
{
  dREC04RECNUMTYP dRecNo = 0;
  dRecNo = this->poTestRec2Table->count();

  return dRecNo;
}
//=============================================================================
int sstRec04TestRec2FncCls::CloseCsvFile(int iKey, char *cCsvFilNam)
{
  if ( iKey != 0) return -1;

  int iStat = 0;
  dREC04RECNUMTYP dRecNo = 0;
  sstRec04TestRec2Cls oTestRec;
  std::string sOutStr;
  std::string sErrStr;

  // CascObjekt öffnen zum Lesen.
  sstMisc01AscFilCls oExpFil;
  sstMisc01AscRowCls oExpRow;

  dRecNo = this->poTestRec2Table->count();
  iStat = oExpFil.fopenWr ( 0, cCsvFilNam);
  if(iStat < 0)
  {
    // iStat = oRecDss.Close(0);
    // delete (this->poTestRec2Table);
    return -2;
  }

  // Loop over all records in table
  for (dREC04RECNUMTYP ll = 1; ll <= dRecNo; ll++)
  {
    iStat = this->poTestRec2Table->Read( 0, ll, &oTestRec);
    if (iStat >= 0)
    {  // if no read error and not marked deleted
      // iStat = Str1_Init(0,&sOutStr);
      sOutStr.clear();
      this->Csv_Write( 0, &oTestRec, &sOutStr);
      oExpRow.Str1_toLine(0,&sOutStr);
      oExpFil.wr_line( 0, &oExpRow);
    }
  }
  // iStat = oRecDss.Close(0);
  // delete (this->poTestRec2Table);
  iStat = oExpFil.fcloseFil(0);

  return iStat;
}
//=============================================================================
int TestRec1Dss_WritNewCsv (int           iKey,
                            char         *cExpFilNam,
                            sstRec04Cls   *oTestRec1Dss)
//-----------------------------------------------------------------------------
{
  // CascObjekt open to write
  sstMisc01AscFilCls oExpFil;
  sstMisc01AscRowCls oExpRow;
  std::string sTestRecStr;
  std::string sErrStr;

  dREC04RECNUMTYP lAnzDs = 0;
  sstRec04TestRec1Cls  oTstChar;
  sstStr01Cls oFrmtTyp;

  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  iStat = sizeof(oTstChar);
  if (sizeof(oTstChar) != oTestRec1Dss->GetUserRecordSize()) return -2;

  // Get Number of stored dataset
  lAnzDs = oTestRec1Dss->count();

  if (lAnzDs <= 0) return -3;

  // open file
  iStat = oExpFil.fopenWr( 0, cExpFilNam);

  // Write Title Row to Csv File
  // iStat = Str1Cpy(0,&sTestRecStr, (char*)"Test_Double;Test_String");
  sTestRecStr = "Test_Double;Test_String";
  iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
  iStat = oExpFil.wr_line( 0, &oExpRow);

  for(dREC04RECNUMTYP ll=1;ll<=lAnzDs;ll++)
  {
    // Read next Record from Dss
    iStat = oTestRec1Dss->Read( 0, ll, &oTstChar);

    // iStat = Str1_Init(0,&sTestRecStr);
    sTestRecStr.clear();

    // Write TestRec1 to row
    iStat = oTstChar.Csv_Write( 0, &sTestRecStr);

    // Write to export row and to file
    iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
    iStat = oExpFil.wr_line( 0, &oExpRow);
  }


  // CascObjekt beenden und zugehörige Datei schließen.
  iStat = oExpFil.fcloseFil(0);

  // Open Fil
  // Loop Dss
  // Write Record to File
  // Close Fil

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
int TestRec1Dss_WritNewLog (int          iKey,
                            char        *cExpFilNam,
                            sstRec04Cls  *oTestRec1Dss)
//-----------------------------------------------------------------------------
{
  // CascObjekt open to write
  sstMisc01AscFilCls oExpFil;
  sstMisc01AscRowCls oExpRow;
  std::string sTestRecStr;
  std::string sErrStr;

  dREC04RECNUMTYP lAnzDs = 0;
  sstRec04TestRec1Cls  oTstChar;
  sstStr01Cls oFrmtTyp;

  dREC04RECNUMTYP SNr1;
  sstRec04TreeKeyCls oTre;


  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  iStat = sizeof(oTstChar);
  if (sizeof(oTstChar) != oTestRec1Dss->GetUserRecordSize()) return -2;

  // Get Number of stored dataset
  lAnzDs = oTestRec1Dss->count();
  if (lAnzDs <= 0) return -3;

  oTre.iTriNo = 1;

  // open file
  iStat = oExpFil.fopenWr( 0, cExpFilNam);

  // Write Title Row to Csv File
  // iStat = Str1Cpy(0,&sTestRecStr, (char*)"Test_Double;Test_String");
  sTestRecStr = "Test_Double;Test_String";
  iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
  iStat = oExpFil.wr_line( 0, &oExpRow);

  for(dREC04RECNUMTYP ll=1;ll<=lAnzDs;ll++)
  {
    // Read next Record from Dss
    iStat = oTestRec1Dss->Read( 0, ll, &oTstChar);

    // iStat = Str1_Init(0,&sTestRecStr);
    sTestRecStr.clear();

    // Write TestRec1 to row
    iStat = oTstChar.Csv_Write( 0, &sTestRecStr);

    // Write to export row and to file
    iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
    iStat = oExpFil.wr_line( 0, &oExpRow);
  }


  // iStat = Str1Cpy(0,&sTestRecStr, (char*)"Tree 1");
  sTestRecStr = "Tree 1";
  iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
  iStat = oExpFil.wr_line( 0, &oExpRow);

  // Write Title Row of tree to log File
  // iStat = Str1Cpy(0,&sTestRecStr, (char*)"Record No;Test_Double;Test_String");
  sTestRecStr = "Record No;Test_Double;Test_String";
  iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
  iStat = oExpFil.wr_line( 0, &oExpRow);

  // Zu einer gebenen Satznummer den nächst größeren Satz im Baum zurückgeben (Traversieren).
  // int TreNr = 1;
  SNr1 = 0;
  // iStat = oTestRec1Dss->TreLesNxtGE( 0, &oTre, &oTstChar, &SNr1);  // Result 4
  iStat = oTestRec1Dss->TreReadNxtGE( 0, &oTre, &oTstChar, &SNr1);  // Result 4

  while (SNr1 > 0)
  {
    // Read next Record from Dss
    iStat = oTestRec1Dss->Read( 0, SNr1, &oTstChar);

    // iStat = Str1_Init(0,&sTestRecStr);
    sTestRecStr.clear();

    if (iStat >= 0)
      iStat = oFrmtTyp.Csv_UInt4_2String( 0, SNr1, &sTestRecStr);

    // Write TestRec1 to row
    iStat = oTstChar.Csv_Write( 0, &sTestRecStr);

    // Write to export row and to file
    iStat = oExpRow.Str1_toLine(0,&sTestRecStr);
    iStat = oExpFil.wr_line( 0, &oExpRow);

    iStat = oTestRec1Dss->TreReadNxtGE( 0, &oTre, &oTstChar, &SNr1);  // Result 4
  }
  // CascObjekt beenden und zugehörige Datei schließen.
  iStat = oExpFil.fcloseFil(0);

  // Open Fil
  // Loop Dss
  // Write Record to File
  // Close Fil

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
