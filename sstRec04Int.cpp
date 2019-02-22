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
// sstRec04Int.cpp    22.02.19  Re.    17.10.15  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>

#include "sstRec04LibInt.h"

//=============================================================================
sstRec04InternCls::sstRec04InternCls(dREC04RECSIZTYP dRecSize)
{
    int iStat = 0;
    dQuantity = 0;
    ucStorage = 0;
    dActStored = 0;
    pFilHdl = NULL;
    bFileNotDelete = 0;  // Default: File will be deleted
    this->iTriAnz = 0; // Number of defined trees is zero
    this->poTre = NULL;

    this->poRecMemSysKey = new (sstRec04CargoKeyInternCls);
    this->poRecMemUsrKey = new (sstRec04CargoKeyInternCls);
    this->poVector = new sstRec04VectSysCls();
    this->poHeader = new sstRec04HeaderCls();

    iStat = this->AddCargoSys( 0, sizeof(sstRec04HeaderCls), (char*) "SYST", this->poRecMemSysKey);
    iStat = this->AddCargoSys( 0, dRecSize, (char*) "USER", this->poRecMemUsrKey);
    assert(iStat >= 0);

}
//=============================================================================
sstRec04InternCls::~sstRec04InternCls()
{

  // First delete all defined intern tree key
  for (int ii=1;ii<=this->iTriAnz;ii++)
  {
     delete this->poTre[ii-1].poDataKey;
  }
  // next free tree array in heap
  free(this->poTre);

  delete (this->poHeader);
  delete (this->poVector);
  delete (this->poRecMemUsrKey);
  delete (this->poRecMemSysKey);

    if(ucStorage)
    {
      // puts("freeing storage");
      free(ucStorage);
    }

    if (this->pFilHdl != 0)
    {
        // Close File
        int iStat= fclose( this->pFilHdl);
        assert(iStat >= 0);

        if(!this->bFileNotDelete)
        {
            // Remove file from disk
            iStat = remove ( this->cDatnam);
            assert(iStat >= 0);
        }
    }
}
//=============================================================================
int sstRec04InternCls::WritNewInt(int iKey, void* element, dREC04RECNUMTYP *index)
{

  if ( iKey != 0) return -1;

  if(this->pFilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->pFilHdl, (this->dActStored) * this->poVector->GetSize(), SEEK_SET);
    fwrite (element, this->poVector->GetSize(), 1, this->pFilHdl);

  }
  else
  {
      if(dActStored >= dQuantity) // Enough space left?
        inflate(100);
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(ucStorage[dActStored * this->poVector->GetSize()]),
              element,
              this->poVector->GetSize());
  }

  dActStored++;
  *index = dActStored;

  return 0;
}
//=============================================================================
int sstRec04InternCls::WritNewVector(int iKey, void* vRecAdr, dREC04RECNUMTYP *dRecNo)
{
  int iStat = 0;

  // Set actual date into DateNew field
  this->poHeader->SetNewDate();
  this->poHeader->SetChangeDate();

  // Reset full intern vector with all cargo packets
  // no good idea, some user cargo data are stored in vector
  // this->poVector->ResetMem(0);

  // write record into vector memory
  iStat = this->poVector->WrtCargo( 0, this->poRecMemSysKey, this->poHeader);

  // write record into vector memory
  iStat = this->poVector->WrtCargo( 0, this->poRecMemUsrKey, vRecAdr);

  // Reset all trees cargos in vector
  sstRec04TreeNodeCls oTreeNode;
  for(int iTreNo=1; iTreNo <= this->iTriAnz; iTreNo++)
  {
     iStat = this->poVector->WrtCargo( 0, this->poTre[iTreNo-1].poDataKey, &oTreeNode);
  }

  // Write new record into intern sstRec memory
  iStat = this->WritNewInt( iKey, this->poVector->GetAdr(), dRecNo);
  return iStat;
}

//=============================================================================
int sstRec04InternCls::WritInt(int iKey, void* vRecAdr, dREC04RECNUMTYP index)
{
  if ( iKey != 0) return -1;
  if (index <= 0 || index > dActStored) return -2;

  if(this->pFilHdl != NULL)
  {
    // Jump to end of file and write record
    fseek  (this->pFilHdl, index * this->poVector->GetSize(), SEEK_SET);
    fwrite (vRecAdr, this->poVector->GetSize(), 1, this->pFilHdl);

  }
  else
  {
      // Copy element into storage,
      // starting at next empty space:
      memcpy(&(ucStorage[(index-1) * this->poVector->GetSize()]), vRecAdr, this->poVector->GetSize());
  }

  return 0;
}
//=============================================================================
int sstRec04InternCls::WritVector(int iKey, void* vRecAdr, dREC04RECNUMTYP dRecNo)
{

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number into vector
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());
  if (iStat < 0) return iStat;

  // show header cargo of vector data
  iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  // Write Change Data in Header Cargo of vector
  poLocHeader->SetChangeDate();

  // write user record into vector memory
  iStat = this->poVector->WrtCargo( 0, this->poRecMemUsrKey, vRecAdr);

  // Write vector Record at position in intern sstRec Memory
  iStat = this->WritInt( iKey, this->poVector->GetAdr(), dRecNo);
  return iStat;
}
//=============================================================================
int sstRec04InternCls::ReadInt(int iKey, dREC04RECNUMTYP index, void *vAdr)
{
    if ( iKey != 0) return -1;
    if(index <= 0 || index > dActStored) return -2;

  if(this->pFilHdl != 0)
  {
    fseek (this->pFilHdl, (index-1) * this->poVector->GetSize(), SEEK_SET);
    fread (vAdr, this->poVector->GetSize(), 1, this->pFilHdl);
  }
  else
  {
      void *vLocAdr = NULL;

      // if(index >= next || index < 0)
      if(index > dActStored)
        return -2;  // Not out of bounds?

      // Produce pointer to desired element:
      vLocAdr = (void*) &(ucStorage[(index-1) * this->poVector->GetSize()]);

      // copy one record data to given record adress
      memcpy( vAdr, vLocAdr, this->poVector->GetSize());
  }

  return 0;
}
//=============================================================================
int sstRec04InternCls::ReadVector(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr)
{
  if ( iKey != 0) return -1;

  // Read record from sstRec memory with Record number
    int iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());
    if (iStat < 0) return -2;

    sstRec04HeaderCls *poLocHeader = NULL;
    iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

    if (poLocHeader->RecGetDeleteStatus())
    {
      this->poVector->ResetMem(0);
      // Read record from vector memory
      iStat = this->poVector->RedCargo( 0, this->poRecMemUsrKey, vRecAdr);
      return -3;
    }

    // Read record from vector memory
    iStat = this->poVector->RedCargo( 0, this->poRecMemUsrKey, vRecAdr);

    // Read Header Data from vector and test
    sstRec04HeaderCls oHeaderData;
    if (iStat >= 0) iStat = this->poVector->RedCargo( 0, this->poRecMemSysKey, &oHeaderData);
    iStat = strncmp((char*)"sstRec02", oHeaderData.GetVersStr(), 10);
    assert(iStat==0);
    assert(oHeaderData.getRecSize() == this->poVector->GetSize());

    return iStat;
}
//=============================================================================
dREC04RECNUMTYP sstRec04InternCls::count() {
  return dActStored; // Number of actual stored records
}
//==============================================================================
int sstRec04InternCls::OpenFile(int   iKey,
                                char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->pFilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC04FILNAMMAXLEN) <= 0) return -3;
  if (this->dActStored > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC04FILNAMMAXLEN);
  strncat(cDatnam, ".rec", dREC04FILNAMMAXLEN);

  // Reoopen existing or open new file for binary Reading/Writing
  this->pFilHdl = fopen( cDatnam, "a+b");
  assert( this->pFilHdl != NULL);

  fseek (this->pFilHdl, 0, SEEK_END);
  long lSize = ftell(this->pFilHdl);

  // Calculate number of existing records in file
  this->dActStored = lSize / this->poVector->GetSize();

  return 0;
}
//==============================================================================
int sstRec04InternCls::NewFile(int   iKey,
                               char *cSysNam)
{
  if ( iKey != 0) return -1;
  if (this->pFilHdl != NULL) return -2;
  if (strnlen(cSysNam,dREC04FILNAMMAXLEN) <= 0) return -3;
  if (this->dActStored > 0) return -4;

  strncpy(cDatnam, cSysNam, dREC04FILNAMMAXLEN);
  strncat(cDatnam, ".rec", dREC04FILNAMMAXLEN);

  // Open new file for binary Reading/Writing
  this->pFilHdl = fopen( cDatnam, "w+b");
  assert( this->pFilHdl != NULL);

  return 0;
}
//==============================================================================
int sstRec04InternCls::SetStoreFile(int iKey)
{
  if ( iKey != 0) return -1;
  this->bFileNotDelete = 1;
  return 0;
}
//=============================================================================
void sstRec04InternCls::inflate(int increase) {
  void* v = realloc(ucStorage, (dQuantity+increase) * this->poVector->GetSize());
  assert(v);  // Was it successful?
  ucStorage = (unsigned char*)v;
  dQuantity += increase;
}
//=============================================================================
int sstRec04InternCls::AddCargoSys( int                  iKey,
                              unsigned int         uiSize,
                              char                *cCargoNam,
                              sstRec04CargoKeyInternCls *oCargoKey)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    if (this->count()!= 0) return -10;

    iStat = this->poVector->AddCargoSys(iKey,uiSize,cCargoNam,oCargoKey);

    this->poHeader->setRecSize(this->poVector->GetSize());

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}

//==============================================================================
int sstRec04InternCls::WrtCargo ( int              iKey,
                            sstRec04CargoKeyInternCls *oDataKey,
                            void            *vCargoAdr)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    iStat = this->poVector->WrtCargo(0,oDataKey,vCargoAdr);

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}
//==============================================================================
int sstRec04InternCls::RedCargo ( int              iKey,
                            sstRec04CargoKeyInternCls *oDataKey,
                            void            *vCargoAdr)
{
    int iRet  = 0;
    int iStat = 0;
  //-----------------------------------------------------------------------------
    if ( iKey != 0) return -1;

    iStat = this->poVector->RedCargo(0,oDataKey,vCargoAdr);

    assert(iRet >= 0);

    // Small Errors will given back
    iRet = iStat;

    return iRet;
}
//==============================================================================
void* sstRec04InternCls::GetVectorAdr() const
{
  // return this->GetAdr();
  return this->poVector->GetAdr();
}
//==============================================================================
int sstRec04InternCls::GetCargoAdr (int                         iKey,
                                    sstRec04CargoKeyInternCls  *oDataKey,
                                    void                      **vCargoAdr)
{
  return this->poVector->GetCargoAdr( iKey, oDataKey, vCargoAdr);
}
//==============================================================================
void sstRec04InternCls::SetNewDate()
{
  this->poHeader->SetNewDate();
}
//==============================================================================
void sstRec04InternCls::SetChangeDate()
{
  this->poHeader->SetChangeDate();
}
//==============================================================================
int sstRec04InternCls::RecSetDeleted( int               iKey,
                                       dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return -2;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  if (iStat >= 0) poLocHeader->RecSetDeleted();

  // Write record from vector to sstRec memory with Record number
  if (iStat >= 0) iStat = this->WritInt( iKey, this->poVector->GetAdr(),dRecNo);

  return iStat;
}
//==============================================================================
int sstRec04InternCls::RecSetMarked( int               iKey,
                                      dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return -2;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  if (iStat >= 0) poLocHeader->RecSetMarked();

  // Write record from vector to sstRec memory with Record number
  if (iStat >= 0) iStat = this->WritInt( iKey, this->poVector->GetAdr(),dRecNo);

  return 0;
}
//==============================================================================
int sstRec04InternCls::RecSetUndeleted( int               iKey,
                                         dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return -2;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  if (iStat >= 0) poLocHeader->RecSetUndeleted();

  // Write record from vector to sstRec memory with Record number
  if (iStat >= 0) iStat = this->WritInt( iKey, this->poVector->GetAdr(),dRecNo);

  return 0;
}
//==============================================================================
int sstRec04InternCls::RecSetUnmarked( int               iKey,
                                        dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return -2;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  if (iStat >= 0) poLocHeader->RecSetUnmarked();

  // Write record from vector to sstRec memory with Record number
  if (iStat >= 0) iStat = this->WritInt( iKey, this->poVector->GetAdr(),dRecNo);

  return 0;
}
//==============================================================================
bool sstRec04InternCls::RecGetDeleteStatus( int               iKey,
                                            dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return 0;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  return poLocHeader->RecGetDeleteStatus();
}
//==============================================================================
bool sstRec04InternCls::RecGetMarkStatus( int               iKey,
                                          dREC04RECNUMTYP   dRecNo)
{
  if ( iKey != 0) return -1;
  if (dRecNo < 1 || dRecNo > this->dActStored) return 0;

  sstRec04HeaderCls *poLocHeader = NULL;
  int iStat = 0;

  // Read record from sstRec memory with Record number
  iStat = this->ReadInt( iKey, dRecNo, this->poVector->GetAdr());

  if (iStat >= 0) iStat = this->poVector->GetCargoAdr(0,this->poRecMemSysKey,(void**) &poLocHeader);

  return poLocHeader->RecGetMarkStatus();
}
//=============================================================================
int sstRec04InternCls::TreIni ( int                iKey,
                                void              *DsAdr,
                                void              *CompAdr,
                                int                CompSiz,
                                sstRec04CompTyp_enum   CompTyp,
                                sstRec04TreeKeyCls     *oTre)
//-----------------------------------------------------------------------------
{
  int iStat = 0;
  sstRec04TreeNodeCls oBaum;
  void *Adr = NULL;

//.............................................................................
  if (iKey != 0) return -1;

  // this->Tre = new (sstRec04TreeHeaderCls);

  this->iTriAnz++;

  // === Handle cargo array memory
  if (this->iTriAnz == 1)  // first cargo
  {
    iStat = sizeof(sstRec04TreeHeaderCls);
    Adr = calloc( iStat,1);
    if (Adr == NULL) assert(0);
    this->poTre = (sstRec04TreeHeaderCls*) Adr;
    // this->poMemAdr[this->uiNumCargoSys-1].SetOffset(0);
  }
  else
  {  // next cargo memory
    iStat = this->iTriAnz * sizeof(sstRec04TreeHeaderCls);
    Adr = realloc(this->poTre , iStat);
    if (Adr == NULL) assert(0);
    this->poTre = (sstRec04TreeHeaderCls*) Adr;
    // this->poMemAdr[this->uiNumCargoSys-1].SetOffset(this->dVectorSize);
  }




  oTre->iTriNo = this->iTriAnz;  // Set extern tree identification key

  // Old Size of Vector is offset to Tre Stru
  this->poTre[this->iTriAnz-1].iNodeOfs = this->poVector->GetSize();

  // find next Tree name for Cargo System: TR01, TR02 ...
  char cLocTreeCargoName[dREC04CARGONAMMAXLEN+1];
  char cLocStr[3];
  strncpy(cLocTreeCargoName,(char*)"TR",dREC04CARGONAMMAXLEN+1);
  int n;
  n = sprintf (cLocStr, "%02d", this->iTriAnz);
  assert(n==2);
  strncat(cLocTreeCargoName,cLocStr,dREC04CARGONAMMAXLEN+1);

  this->poTre[this->iTriAnz-1].poDataKey = new(sstRec04CargoKeyInternCls);

  // define cargo system for new tree
  iStat = this->AddCargoSys( 0, sizeof(sstRec04TreeNodeCls), cLocTreeCargoName, this->poTre[this->iTriAnz-1].poDataKey);
  assert(iStat == 0);

  oBaum.dLeft_LT = 0;
  oBaum.dRight_GE = 0;
  iStat = poVector->WrtCargo(0,this->poTre[this->iTriAnz-1].poDataKey,&oBaum);

  // Default is entry of tree at record 1
  this->poTre[this->iTriAnz-1].dRoot = 1;

  // Offset of compare value from start of record
  this->poTre[this->iTriAnz-1].iOffset = (char*)CompAdr - (char*)DsAdr;

  // Size of compare value
  this->poTre[this->iTriAnz-1].iSize = CompSiz;

  // Type of compare value
  this->poTre[this->iTriAnz-1].eTyp  = CompTyp;

  return iStat;
}
//=============================================================================
int sstRec04InternCls::TreBld ( int              iKey,
                                sstRec04TreeKeyCls   *oTre)
//.............................................................................
{
  void *Adr1 = NULL;        // adress of compare value in vector
  dREC04RECNUMTYP  Root = 0;

  dREC04RECNUMTYP  ii = 0;
  int   iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;

  Root = 0;

  sstRec04TreeNodeCls oNode;

  // Clean all Tree Node Data in actual Tree
  for( ii=1; ii<=this->dActStored; ii++)
  {
    // Read Record from Record memory into intern vector
    iStat = this->ReadInt(  0, ii, this->poVector->GetAdr());
    // Write empty node record into vector
    iStat = this->DSiTreAdrSet(0, &this->poTre[oTre->iTriNo-1], this->poVector->GetAdr(), &oNode);
    // Rewrite vector into memory
    iStat = this->WritInt( 0, this->poVector->GetAdr(), ii);
  }

  for( ii=1; ii<=this->dActStored; ii++)
  {
    // record record from RecMem into vector
    iStat = this->ReadInt(  0, ii, this->poVector->GetAdr());

    // Get adress of user data
    void *vUsrAdr = NULL;
    iStat = this->poVector->GetCargoAdr(0,this->poRecMemUsrKey,&vUsrAdr);
    // Get Adress of compare value in user data
    this->poVector->CalcSetPos( vUsrAdr, &Adr1, this->poTre[oTre->iTriNo-1].iOffset);

    // Insert new record ii in tree otre with root record
    Root = DSiTreInsert( 0, &this->poTre[oTre->iTriNo-1], Root , ii, Adr1);
  }
  return iStat;
}
//=============================================================================
int sstRec04InternCls::TreSeaEQ  (int                 iKey,
                                  sstRec04TreeKeyCls *oTre,
                                  void               *Val,
                                  dREC04RECNUMTYP    *SNr)
//.............................................................................
{
  // int iRet;
  int iStat;
//.............................................................................
  if (iKey != 0) return -1;
  // if (oTre->iTriNo <= 0 || oTre->iTriNo >= CINT2_MAX) return -2;
  if (oTre->iTriNo <= 0) return -2;
  if (oTre->iTriNo > this->iTriAnz) return -2;
  // iRet = 0;
  iStat = 0;


  if ( this->dActStored > 0)
  {
    iStat = this->TreSeaGE ( 0, oTre, Val, SNr);
  }

  if (iStat < 0)
  {
    assert (iStat >= 0);
  }

  if (iStat == 2)
  {
    iStat = 1;    // exact value found
  }
  else
  {
    iStat = 0;    // nothing found
    *SNr  = 0;    // reset result
  }

  return iStat;
}
//=============================================================================
dREC04RECNUMTYP sstRec04InternCls::DSiTreInsert( int                     iKey,
                                                 sstRec04TreeHeaderCls  *oTre,
                                                 dREC04RECNUMTYP         DsNrAlt,
                                                 dREC04RECNUMTYP         DsNrNeu,
                                                 void                   *Adr1)
//.............................................................................
{

  void        *LocDs = NULL;       // adress of local data memory
  sstRec04TreeNodeCls *Baum2;      // Tree node data in record 2
  void        *Adr2 = NULL;        // Compare value 2
  int          AltGroesser = 0;

  int   iStat = 0;
//.............................................................................

  if (iKey != 0) return -1;

  if ( DsNrAlt == 0)  // exist no stored record
  {
    DsNrAlt = DsNrNeu;
  }
  else
  {

    // LocDs = malloc ( this->oVector->GetSize());
    LocDs = calloc ( this->poVector->GetSize(),1);
    assert(LocDs);

    // Read record from RecMem into local memory
    iStat = this->ReadInt( 0, DsNrAlt, LocDs);

    // Adressen der Baumstrukturen in den Zwischenspeichern ermitteln
    // Get Adress from tree node data in local memory
    // TreVerw = (sstRec04TreeHeaderCls*) this->Tre;
    this->poVector->CalcSetPos(LocDs, &Adr2, oTre->iNodeOfs);
    Baum2 = (sstRec04TreeNodeCls*) Adr2;

    // Get Adress of compare value in local memory
    int iUsrOfs = 0;
    this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
    this->poVector->CalcSetPos(LocDs, &Adr2, (iUsrOfs + oTre->iOffset));

    // Is true, if Compare Value Adr2 is greater than Adr1
    AltGroesser = DSiVarCompGT ( 0, &oTre->eTyp, Adr2, Adr1);

    if ( AltGroesser)
    {
      Baum2->dLeft_LT = DSiTreInsert ( 0, oTre, Baum2->dLeft_LT , DsNrNeu, Adr1);
    }
    else
    {
      Baum2->dRight_GE = DSiTreInsert ( 0, oTre, Baum2->dRight_GE, DsNrNeu, Adr1);
    }

    // Write record in local memory back to RecMem
    iStat = this->WritInt( 0, LocDs, DsNrAlt);

    free ( LocDs);

  }
  // Fatal Errors goes to an assert
  if (iStat < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }

  return DsNrAlt;
}
//=============================================================================
int sstRec04InternCls::TreReadNxtGE (int              iKey,
                                    sstRec04TreeKeyCls   *oTre,
                                    void            *DSatz,
                                    dREC04RECNUMTYP *SNr)
//-----------------------------------------------------------------------------
{
  dREC04RECNUMTYP SNr1 = 0;
  dREC04RECNUMTYP SNr2 = 0;
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  SNr1 = *SNr;

  if (SNr1 == 0)
  {
    // Get record with smallest value from tree oTre
    iStat = TreSeaFrst ( 0, oTre, &SNr2);
  }
  else
  {
    // Get for record SNr1 next greater record number in tree oTre
    iStat = TreSeaNxtGE ( 0, oTre, SNr1, &SNr2);
  }

  *SNr = SNr2;

  if (SNr2 > 0)
  {
    // Read record SNr from RecMem
   iStat = this->ReadVector(0,*SNr,DSatz);
  }
  else
  {
    // no record found, reset record memory
    iStat = this->resetRecord(0,DSatz);
    iStat = -2;
  }

// Heavy Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert("Error in function: xxx");
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04InternCls::TreSeaFrst ( int        iKey,
                             sstRec04TreeKeyCls    *oTre,
                             dREC04RECNUMTYP  *SNr)
//-----------------------------------------------------------------------------
{
  dREC04RECNUMTYP      IntSNr = 0;        // Local Record number
  void         *IntSAdr;                  // Local record memory
  sstRec04TreeNodeCls     SBaum;              // Local tree node object
  sstRec04TreeHeaderCls *poTreHead;

  int iRet;
  int iStat;
//.............................................................................
  if (iKey != 0) return -1;
  iRet = 0;

  poTreHead = (sstRec04TreeHeaderCls*) &this->poTre[oTre->iTriNo-1];
  // iStat = 0;

  // Is RecMem empty, no Record number is result: Error
  if (this->dActStored <= 0)
  {
    *SNr = 0;
    return -2;
  }

  // Is only one record in RecMem, this is result
  if (this->dActStored == 1)
  {
    *SNr = 1;
    return 0;
  }

  // Get Entry record number in Tree oTre
  // This is first result number
  IntSNr = this->poTre->dRoot;

  // Start local record memory
  IntSAdr = malloc(this->poVector->GetSize());
  assert(IntSAdr);

  SBaum.dLeft_LT = IntSNr;

  while ( SBaum.dLeft_LT > 0)
  {
    IntSNr = SBaum.dLeft_LT;
    *SNr   = IntSNr;
    // Return tree node data for record IntSNr of tree oTre
    iStat = DSiTreDatGet ( 0, poTreHead, IntSNr, IntSAdr,  &SBaum);
  }

  free (IntSAdr);

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
int sstRec04InternCls::TreSeaNxtGE ( int               eKey,
                                     sstRec04TreeKeyCls    *oTre,
                                     dREC04RECNUMTYP   SNr1,
                                     dREC04RECNUMTYP  *SNr2)
{
  dREC04RECNUMTYP  SNr = 0;

  int iKey;
  int iStat;
//.............................................................................
  if ( eKey != 0) return -1;
  if ( SNr1 == 0) return -2;

  // Get Base of Tree
  SNr = this->poTre[oTre->iTriNo-1].dRoot;

  *SNr2 = 0;  // Default is Result empty

  // In Tree oTre for Record 1 seach next greater Record 2
  iKey  = 0;
  iStat = DSiTreSeaNxtGT ( &iKey, oTre, SNr, SNr1, SNr2);

  return iStat;
}
//=============================================================================
int sstRec04InternCls::TreSeaNxtEQ ( int                   iKey,
                                     sstRec04TreeKeyCls   *oTre,
                                     void                 *vSearchMin,
                                     void                 *vSearchMax,
                                     dREC04RECNUMTYP      *SNr)
{
  dREC04RECNUMTYP  SeachNr2 = 0;
  void *Satz2Adr;
  sstRec04TreeHeaderCls *poTreHead;
  int iKey2 = 0;

  int iRet  = 0;
  int iStat = 0;
//.............................................................................
  if ( iKey != 0) return -1;

  poTreHead = (sstRec04TreeHeaderCls*) &this->poTre[oTre->iTriNo-1];

  if (*SNr == 0)
  {
    // Den ersten Satz suchen
    // iStat = DS1_TreSeaGE ( 0, WorkDss, TreNr, vValMin, SNr);
    iStat = TreSeaGE ( 0, oTre, vSearchMin, SNr);
  }
  else
  {
    // Den nächsten Satz suchen
    Satz2Adr = malloc ( this->poVector->GetSize());
    assert(Satz2Adr);

    // In Baum TreNr für Datensatz SNr1 den nächst Größeren suchen.
    // iStat = DS1_TreSeaNxtGT ( 0, WorkDss, TreNr, *SNr, &SeachNr2);
    iStat = this->DSiTreSeaNxtGT( &iKey2, oTre, 1, *SNr, &SeachNr2);

    if(SeachNr2 <= 0)
    {
      iStat = 0;
      *SNr = 0;
    }
    else
    {
      // Datensatz an absoluter Position lesen.
      // iStat = DS1_DsLesAbs ( 0, WorkDss, Satz2Adr, SeachNr2);
      iStat = this->ReadInt( 0, SeachNr2, Satz2Adr);
      assert(iStat >= 0);

      // Vergleich -Kleiner Gleich- der Sortiervariablen
      // True wenn Alt Kleiner gleich
      // True wenn Alt Größer gleich: Fund ist kleiner Max-Wert
      // iStat = DSi_CompGE ( 0, oTre, vSearchMax, Satz2Adr);
      iStat = this->DSiCompGE ( 0, poTreHead, vSearchMax, Satz2Adr);
      if (iStat == 1) *SNr = SeachNr2;
      else *SNr = 0;  // Nix mehr gefunden
    }


    free(Satz2Adr);
  }


  // Heavy Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert("Error in function: xxx");
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04InternCls::TreSeaGE ( int                  iKey,
                                  sstRec04TreeKeyCls  *oTre,
                                  void                *Val,
                                  dREC04RECNUMTYP     *SNr)
//-----------------------------------------------------------------------------
{
  // int iRet = 0;
  int iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;
  // if (TreNr <= 0 || TreNr >= CINT2_MAX) return -2;
  // if (TreNr > DsVerw->TrAnz) return -2;

  // In Baum TreNr den Datensatz mit Wert Val oder nächst größeren suchen
  // iStat = DSi_TreSeach ( iKey, DsVerw, TreNr, Val, SNr);
  iStat = this->DSiTreSeach ( iKey, oTre, Val, SNr);

  return iStat;
}
//=============================================================================
int sstRec04InternCls::DSiVarCompGT (int               iKey,
                                     sstRec04CompTyp_enum *cTyp,
                                     void             *AdrAlt,
                                     void             *AdrNeu)
//-----------------------------------------------------------------------------
{
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltGroesser;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Set type and adress for compare value in ValSet
  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  // Set type and adress for compare value in CompValSet
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

    AltGroesser = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) > 0 ) AltGroesser = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp > *CompValSet.IComp) AltGroesser = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp > *CompValSet.LComp) AltGroesser = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp > *CompValSet.UIComp) AltGroesser = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp > *CompValSet.ULComp) AltGroesser = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp > *CompValSet.RComp) AltGroesser = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp > *CompValSet.DComp) AltGroesser = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltGroesser;
}
//=============================================================================
/**
* @brief Vergleicht zwei Variablen
*/
//-----------------------------------------------------------------------------
int sstRec04InternCls::DSiVarCompGE (int iKey, sstRec04CompTyp_enum *cTyp, void *AdrAlt, void *AdrNeu)
//-----------------------------------------------------------------------------
{
  // CompValue_stru ValSet;
  // CompValue_stru CompValSet;
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltGroesserGleich;
  // int iRet  = 0;
  // int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // DSi_CompValue ( 0, AdrAlt, cTyp, &ValSet);
  // DSi_CompValue ( 0, AdrNeu, cTyp, &CompValSet);
  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

    AltGroesserGleich = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) >= 0 ) AltGroesserGleich = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp >= *CompValSet.IComp) AltGroesserGleich = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp >= *CompValSet.LComp) AltGroesserGleich = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp >= *CompValSet.UIComp) AltGroesserGleich = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp >= *CompValSet.ULComp) AltGroesserGleich = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp >= *CompValSet.RComp) AltGroesserGleich = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp >= *CompValSet.DComp) AltGroesserGleich = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltGroesserGleich;
}
//=============================================================================
/**
* @brief Vergleicht zwei Variablen
*/
//-----------------------------------------------------------------------------
int sstRec04InternCls::DSiVarCompLT (int iKey, sstRec04CompTyp_enum *cTyp, void *AdrAlt, void *AdrNeu)
//-----------------------------------------------------------------------------
{
  // CompValue_stru ValSet;
  // CompValue_stru CompValSet;
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltKleiner;
  // int iRet  = 0;
  // int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

//  DSi_CompValue ( 0, AdrAlt, cTyp, &ValSet);
//  DSi_CompValue ( 0, AdrNeu, cTyp, &CompValSet);
  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

    AltKleiner = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) < 0 ) AltKleiner = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp < *CompValSet.IComp) AltKleiner = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp < *CompValSet.LComp) AltKleiner = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp < *CompValSet.UIComp) AltKleiner = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp < *CompValSet.ULComp) AltKleiner = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp < *CompValSet.RComp) AltKleiner = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp < *CompValSet.DComp) AltKleiner = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltKleiner;
}
//=============================================================================
/**
* @brief Vergleicht zwei Variablen
*/
//-----------------------------------------------------------------------------
int sstRec04InternCls::DSiVarCompLE (int iKey, sstRec04CompTyp_enum *cTyp, void *AdrAlt, void *AdrNeu)
//-----------------------------------------------------------------------------
{
  // CompValue_stru ValSet;
  // CompValue_stru CompValSet;
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltKleinerGleich;
  // int iRet  = 0;
  // int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

//  DSi_CompValue ( 0, AdrAlt, cTyp, &ValSet);
//  DSi_CompValue ( 0, AdrNeu, cTyp, &CompValSet);
  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

    AltKleinerGleich = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) <= 0 ) AltKleinerGleich = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp <= *CompValSet.IComp) AltKleinerGleich = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp <= *CompValSet.LComp) AltKleinerGleich = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp <= *CompValSet.UIComp) AltKleinerGleich = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp <= *CompValSet.ULComp) AltKleinerGleich = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp <= *CompValSet.RComp) AltKleinerGleich = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp <= *CompValSet.DComp) AltKleinerGleich = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltKleinerGleich;
}
//=============================================================================
/**
* @brief Vergleicht zwei Variablen
*/
//-----------------------------------------------------------------------------
int sstRec04InternCls::DSiVarCompEQ (int iKey, sstRec04CompTyp_enum *cTyp, void *AdrAlt, void *AdrNeu)
//-----------------------------------------------------------------------------
{
  // CompValue_stru ValSet;
  // CompValue_stru CompValSet;
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltGleich;
  // int iRet  = 0;
  // int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

//  DSi_CompValue ( 0, AdrAlt, cTyp, &ValSet);
//  DSi_CompValue ( 0, AdrNeu, cTyp, &CompValSet);
  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

    AltGleich = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) == 0 ) AltGleich = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp == *CompValSet.IComp) AltGleich = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp == *CompValSet.LComp) AltGleich = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp == *CompValSet.UIComp) AltGleich = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp == *CompValSet.ULComp) AltGleich = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp == *CompValSet.RComp) AltGleich = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp == *CompValSet.DComp) AltGleich = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltGleich;
}
//=============================================================================
int sstRec04InternCls::DSiVarCompNE (int                   iKey,
                                     sstRec04CompTyp_enum *cTyp,
                                     void                 *AdrAlt,
                                     void                 *AdrNeu)
//-----------------------------------------------------------------------------
{
  sstRec04CompValueCls ValSet;
  sstRec04CompValueCls CompValSet;

  int AltUngleich;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  DSiCompValue ( 0, AdrAlt, cTyp, &ValSet);
  DSiCompValue ( 0, AdrNeu, cTyp, &CompValSet);

  // if value1 is not equal value2 return true = 1
  // if value1 is equal value2 return false = 0

  AltUngleich = 0;
    switch (*cTyp)
    {
      // Comp2 ist größer Comp1
      case sstRecTyp_CC:  // Char
        if ( strcmp( ValSet.CComp, CompValSet.CComp) != 0 ) AltUngleich = 1;
        break;
      case sstRecTyp_I2:  // Int
        if ( *ValSet.IComp != *CompValSet.IComp) AltUngleich = 1;
        break;
      case sstRecTyp_I4:  // Long Int
        if ( *ValSet.LComp != *CompValSet.LComp) AltUngleich = 1;
        break;
      case sstRecTyp_UI:  // Unsigned Int
        if ( *ValSet.UIComp != *CompValSet.UIComp) AltUngleich = 1;
        break;
      case sstRecTyp_UL:  // Unsigned Long Int
        if ( *ValSet.ULComp != *CompValSet.ULComp) AltUngleich = 1;
        break;
      case sstRecTyp_R4:  // float
        if ( *ValSet.RComp != *CompValSet.RComp) AltUngleich = 1;
        break;
      case sstRecTyp_D8:  // Double
        if ( *ValSet.DComp != *CompValSet.DComp) AltUngleich = 1;
        break;
      default:
        assert(0);
        break;
    }

  return AltUngleich;
}
//=============================================================================
int sstRec04InternCls::DSiCompValue (int                 iKey,
                                     void               *ValueAdr,
                                     sstRec04CompTyp_enum   *CompTyp,
                                     sstRec04CompValueCls       *CompValue)
//-----------------------------------------------------------------------------
{
  int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // reset all compare type values
  memset(CompValue,0,sizeof(sstRec04CompValueCls));

  switch (*CompTyp)
  {
    case sstRecTyp_CC:  // Char
      CompValue->CComp = (char*) ValueAdr;
      break;
    case sstRecTyp_I2:  // Int
      CompValue->IComp = (int*) ValueAdr;
      break;
    case sstRecTyp_I4:   // Long Int
      CompValue->LComp = (long*) ValueAdr;
      break;
    case sstRecTyp_UI:  // Unsigned Int
      CompValue->UIComp = (unsigned int*) ValueAdr;
      break;
    case sstRecTyp_UL:   // Unsigned Long Int
      CompValue->ULComp = (unsigned long*) ValueAdr;
      break;
    case sstRecTyp_R4:   // Float
      CompValue->RComp = (float*) ValueAdr;
      break;
    case sstRecTyp_D8:   // Double
      CompValue->DComp = (double*) ValueAdr;
      break;
    default:
      iRet = -1;
      break;
  }
    // Heavy Errors goes to an assert
  if (iRet < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert("Error in DSi_CompValue: Cast-Error");
  }

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
int sstRec04InternCls::DSiTreSeach ( int                   iKey,
                                     sstRec04TreeKeyCls   *oTre,
                                     void                 *vSearchVal,
                                     dREC04RECNUMTYP      *xx_SNr)
{
  sstRec04TreeHeaderCls  *TreVerw;

  dREC04RECNUMTYP     SNr;          // Record number
  void       *SAdr;                 // Local record in heap
  sstRec04TreeNodeCls   SBaum;      // Tree Node data

  int iRet;
  int iStat;
//.............................................................................
  if (iKey != 0) return -1;
  iRet = 0;

  // Adresse der Baumstruktur im Datensatz ermitteln
  TreVerw = (sstRec04TreeHeaderCls*) &this->poTre[oTre->iTriNo-1];

  // Zwischenspeicher im Heap für Datensatz anfordern
  SAdr = malloc ( this->poVector->GetSize());
  assert(SAdr);


  // Einstiegsdatensatz für Baum TreNr ermitteln
  // SNr = TreVerw[oTre->iTriNo-1].dRoot;
  if (*xx_SNr == 0)
    // SNr = TreVerw[oTre->iTriNo-1].dRoot;
    SNr = TreVerw->dRoot;
  else
    SNr = *xx_SNr;

  // read record data into local heap record
  iStat = this->ReadInt(  0, SNr, SAdr);

  // Baumdaten in Baum TreNr für Datensatz SNr zurückliefern
  iStat = DSiTreDatGet ( 0, TreVerw, SNr, SAdr,  &SBaum);

  if (iStat < 0)
  {
    free(SAdr);
    return -1;
  }

  *xx_SNr = 0;  // Rückgabedatensatz initialisieren

  // Vergleich der Sortiervariablen
  while (DSiCompNE( 0, TreVerw, vSearchVal, SAdr)  && (SNr != 0)  )
  {

    // Vergleich der Sortiervariablen
    if ( DSiCompLT( 0, TreVerw, vSearchVal, SAdr)  )
    {

      // Gefundener Satz hat größeren Wert
      // Damit erfüllt er erst einmal die Anforderungen
      // Weitersuchen...
      *xx_SNr = SNr;            // Zwischenergebnis
      SNr     =  SBaum.dLeft_LT;   // In nächster Ebene weitersuchen
    }
    else
    {
      // Gefundener Satz hat kleineren Wert
      SNr =  SBaum.dRight_GE;      // In nächster Ebene weitersuchen
    }

    // Baumdaten in Baum TreNr für Datensatz SNr zurückliefern
    if (SNr > 0)
    {
      iStat = DSiTreDatGet ( 0, TreVerw, SNr, SAdr,  &SBaum);
    }

  }

  if (SNr > 0)
  {
    *xx_SNr = SNr;  // Suchwert genau gefunden
    iRet = 2;
  }
  else if (SNr == 0)
  {
    if ( *xx_SNr > 0)
    {
      iRet = 1;    // Überhaupt etwas gefunden
    }
    else
    {
      iRet = 0;    // Nichts gefunden
    }
  }
  else
  {
    iRet = -1;    // Irgendein Fehler
  }

  iStat = 0;
  // iStat = MemFree ( SAdr);
  free ( SAdr);

  return iRet;
}
//=============================================================================
int sstRec04InternCls::DSiTreSeaNxtGT ( int                *iKey,
                                        sstRec04TreeKeyCls      *oTre,
                                        dREC04RECNUMTYP     SNr,
                                        dREC04RECNUMTYP     SNr1,
                                        dREC04RECNUMTYP    *SNr2)
{
  void       *SNr_Adr;      // Local record in heap
  sstRec04TreeNodeCls   SBaum;  // local tree node object

  sstRec04TreeHeaderCls *poTreHead;

  int iRet = 0;
  int iStat = 0;
//.............................................................................
  if ( *iKey < 0 || *iKey > 2) return -1;
  if ( *iKey == 2) return 0;

  poTreHead = (sstRec04TreeHeaderCls*) &this->poTre[oTre->iTriNo-1];

  if ( SNr != 0)  // if not empty
  {
    // Get heap memory for compare record
    SNr_Adr = malloc ( this->poVector->GetSize());
    assert(SNr_Adr);

    // Read record dRecNo into SNr_Adr Memory and return tree node data of tree oTre
    iStat = DSiTreDatGet ( 0, poTreHead, SNr, SNr_Adr,  &SBaum);

    // Traverse in Tree oTre to next greater record
    iStat = DSiTreSeaNxtGT ( iKey, oTre,  SBaum.dLeft_LT, SNr1, SNr2);

    // Action !!
    // the later action first, so this does not run immedialety
    if ( *iKey == 1)
    {
      *SNr2 = SNr;
      *iKey = 2;
    }

    if ( SNr == SNr1)
    {
      *iKey = 1;
    }

    // Traverse in Tree oTre to next greater record
    iStat = DSiTreSeaNxtGT ( iKey, oTre,  SBaum.dRight_GE, SNr1, SNr2);

    // free heap for local record
    free ( SNr_Adr);
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
int sstRec04InternCls::DSiTreDatGet ( int                iKey,
                                      sstRec04TreeHeaderCls     *oTreHead,
                                      dREC04RECNUMTYP    SNr,
                                      void              *DSatz,
                                      sstRec04TreeNodeCls   *TreDat)
//.............................................................................
{
  int iRet = 0;
  int iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;

  // istat = 0;
  if (SNr <= 0) return -1;
  if (SNr > this->dActStored) return -1;

  // Read record from RecMem into given memory
  iStat = this->ReadInt(0,SNr,DSatz);

  // Get Tree node data from read record
  iStat = DSiTreAdrGet ( 0 , oTreHead, DSatz, TreDat);

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
int sstRec04InternCls::DSiTreDatSet ( int                     iKey,
                                      sstRec04TreeHeaderCls  *oTreHead,
                                      dREC04RECNUMTYP         SNr,
                                      void                   *DSatz,
                                      sstRec04TreeNodeCls    *oNodeData)
{
  int iRet = 0;
  int iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;

  if (SNr <= 0) return -1;
  if (SNr > this->dActStored) return -1;

  // Write tree node data into given record
  iStat = DSiTreAdrSet ( 0 , oTreHead, DSatz, oNodeData);

  // Write given record into RecMem at position
  iStat = this->WritInt(0,DSatz,SNr);

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
int sstRec04InternCls::DSiTreAdrGet ( int                     iKey,
                                      sstRec04TreeHeaderCls  *poTreHead,
                                      void                   *vRecAdr,
                                      sstRec04TreeNodeCls    *poTreNode)
//.............................................................................
{
  sstRec04TreeNodeCls    *poRecTreNode;
  void               *vTreeNodeAdr;

  int iret;
  // int istat;
//.............................................................................
  if (iKey != 0) return -1;
  iret = 0;

  CalcSetPos ( vRecAdr, &vTreeNodeAdr, poTreHead->iNodeOfs);

  // Adr are tree node data
  poRecTreNode = (sstRec04TreeNodeCls*) vTreeNodeAdr;

  // Copy Tree Data from vector to tree data
  *poTreNode = *poRecTreNode;

  return iret;

}
//=============================================================================
int sstRec04InternCls::DSiTreAdrSet ( int                     iKey,
                                      sstRec04TreeHeaderCls  *oTreeHead,
                                      void                   *vRecAdr,
                                      sstRec04TreeNodeCls    *oNodeData)
{
  sstRec04TreeNodeCls    *poRecNodeData;
  void *vTreeNodeAdr = 0;

  int iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;

  CalcSetPos ( vRecAdr, &vTreeNodeAdr, oTreeHead->iNodeOfs);

  // Adr are tree node data
  poRecNodeData = (sstRec04TreeNodeCls*) vTreeNodeAdr;

  // Copy Tree Node Data to local vector
  *poRecNodeData = *oNodeData;

  return iStat;
}
//=============================================================================
void sstRec04InternCls::CalcSetPos ( void   *BasPtr,
                                     void  **IdxPtr,
                                     long    Offs) const
//-----------------------------------------------------------------------------
{
  unsigned char *xxx;  // smallest possible type

//.............................................................................
  // Calculate pointer offset
  xxx = (unsigned char*) BasPtr;
  xxx = xxx + Offs;
  (*IdxPtr) = (void*) xxx;
}
//=============================================================================
int sstRec04InternCls::TreWriteNew ( int              iKey,
                                     void            *vRecAdr,
                                     dREC04RECNUMTYP *dRecNo)
//.............................................................................
{
  dREC04RECNUMTYP   DsNr;
  void             *vCompValueAdr;
  int               iTreNo;
  dREC04RECNUMTYP   dRoot;

  int iStat = 0;
//.............................................................................
  if (iKey != 0) return -1;

  // write new record into record memory thru vector buffer
  iStat = this->WritNewVector( 0, vRecAdr, &DsNr);

  assert(DsNr > 0);
  assert(iStat >= 0);

  // Get Adress of user data in vector buffer
  void *vUsrRecAdr = NULL;
  iStat = this->poVector->GetCargoAdr( 0, this->poRecMemUsrKey, &vUsrRecAdr);

  // Update new record in all trees
  for(iTreNo=1; iTreNo <= this->iTriAnz; iTreNo++)
  {
    if (DsNr == 1) dRoot = 0;
    else dRoot = 1;

    // Get Adress of compare value in user data of vector
    this->poVector->CalcSetPos( vUsrRecAdr, &vCompValueAdr, this->poTre[iTreNo-1].iOffset);

    // Insert new record in tree
    dRoot = this->DSiTreInsert( 0, &this->poTre[iTreNo-1], dRoot , DsNr, vCompValueAdr);
  }

  *dRecNo = this->dActStored;

  return iStat;
}
//=============================================================================
int sstRec04InternCls::TreWritVector ( int               Key,
                                       void             *SatzAdr,
                                       dREC04RECNUMTYP   SNr)
//.............................................................................
{
  void         *Adr1;   // erste Vergleichsvariable  (Typenlos)
  int        TreNr;   // Der zu füllende Baum
  dREC04RECNUMTYP    Root;

  int iStat = 0;
  int iRet = 0;
//.............................................................................
  if (Key != 0) return -1;

  if (this->dActStored > 1)
  {
    // Baum kann nur ermittelt werden, wenn mehr als ein Datensatz vorhanden

    // record is in intern vector memory
    iStat = this->ReadInt(0,SNr,this->poVector->GetAdr());
    assert(iStat >= 0);


    // Die Sortierung aller Bäume aktualisieren
    for( TreNr=1; TreNr <= this->iTriAnz; TreNr++)
    {

      // Knoten aus Baum löschen
      // Die Verweise  auf SNr in den anderen Datensätzen müssen auch gelöscht werden.
      iStat = this->TreDelIntern ( 0, &this->poTre[TreNr-1],  SNr);

    }

    // Datensatz an absoluter Position schreiben
    // Die Baumdaten werden neu initialisiert
    iStat = this->WritVector ( 0, SatzAdr, SNr);

    // Die Sortierung aller Bäume aktualisieren
    for( TreNr=1; TreNr <= this->iTriAnz; TreNr++)
    {


      // Get Adress of compare value in local memory
      int iUsrOfs = 0;
      this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
      this->poVector->CalcSetPos(this->poVector->GetAdr(), &Adr1, (iUsrOfs + this->poTre[TreNr-1].iOffset));


      // Datensatz in Baum eintragen
      Root = this->poTre[TreNr-1].dRoot;
      Root = this->DSiTreInsert( 0, &this->poTre[TreNr-1], Root , SNr, Adr1);
    }
  }

  return iRet;
}
//=============================================================================
int sstRec04InternCls::TreDelValue ( int                   iKey,
                                     sstRec04TreeKeyCls   *oTre,
                                     void                 *vSearchValue,
                                     dREC04RECNUMTYP      *dRecNo)
//-----------------------------------------------------------------------------
{
  void *v_cc, *v_pp, *v_xx, *v_tt, *v_tr, *v_cl; // 6 local records in heap
  sstRec04TreeNodeCls   oTreNode_xx;       // Tree Node Data from record xx
  sstRec04TreeNodeCls   oTreNode_pp;       // Tree Node Data from record pp
  sstRec04TreeNodeCls   oTreNode_tt;       // Tree Node Data from record tt
  sstRec04TreeNodeCls   oTreNode_tr;       // Tree Node Data from record tr
  sstRec04TreeNodeCls   oTreNode_cc;       // Tree Node Data from record cc
  sstRec04TreeNodeCls   oTreNode_cl;       // Tree Node Data from record cl
  dREC04RECNUMTYP    dRecNo_tt = 0;       // Record Number from tt
  dREC04RECNUMTYP    dRecNo_xx = 0;       // Record Number from xx
  dREC04RECNUMTYP    dRecNo_pp = 0;       // Record Number from pp
  dREC04RECNUMTYP    dRecNo_cc = 0;       // Record Number from cc
  sstRec04TreeHeaderCls *poTreHead;
  // int iRet  = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;
  *dRecNo = 0;

  poTreHead = (sstRec04TreeHeaderCls*) &this->poTre[oTre->iTriNo-1];

  v_cc = malloc ( this->poVector->GetSize());
  assert(v_cc);
  v_pp = malloc (  this->poVector->GetSize());
  assert(v_pp);
  v_xx = malloc ( this->poVector->GetSize());
  assert(v_xx);
  v_tt = malloc ( this->poVector->GetSize());
  assert(v_tt);
  v_tr = malloc ( this->poVector->GetSize());
  assert(v_tr);
  v_cl = malloc ( this->poVector->GetSize());
  assert(v_cl);

  // Datensatz intern lesen
  // -head- dürfte der Einstieg in den Baum sein, in DSS also SNr = 1
  // p = head;
  dRecNo_pp = 0;


  // DS xx ist der rechte Nachfolger vom Root-Datensatz
  // Datensatz xx lesen
  // x = head->r;
  // Baumdaten in Baum TreNr für Datensatz SNr zurückliefern
  dRecNo_xx = this->poTre[oTre->iTriNo-1].dRoot;

  iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  // Fatal Errors goes to an assert
  if (iStat < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }


  // Vergleich der Sortiervariablen
  while (DSiCompNE ( 0, &this->poTre[oTre->iTriNo-1], vSearchValue, v_xx) )
  //  while (v != x->Key)
  {
    // p = x;
    memcpy( v_pp, v_xx, this->poVector->GetSize());
    dRecNo_pp = dRecNo_xx;
    oTreNode_pp = oTreNode_xx;

    // x = (v < x->key) ? x->l : x->r;
    // Vergleich der Sortiervariablen

    if ( DSiCompLT ( 0, &this->poTre[oTre->iTriNo-1], vSearchValue, v_xx)  )
    {

      // Datensatz xx lesen
      // x = x->l;
      dRecNo_xx =  oTreNode_xx.dLeft_LT;
    }
    else
    {
      // Datensatz xx lesen
      // x = x->r;
      dRecNo_xx =  oTreNode_xx.dRight_GE;
    }

    // Für Datensatz -pp- die Nachfolger-Adressen im Baum -TreNr- liefern
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

  }

  // t = x;
  memcpy( v_tt, v_xx, this->poVector->GetSize());
  dRecNo_tt = dRecNo_xx;
  oTreNode_tt = oTreNode_xx;

  // Für Datensatz -tt- die Nachfolger-Adressen im Baum -TreNr- liefern
  // Datensatz tr lesen
  iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_tt.dRight_GE, v_tr, &oTreNode_tr);

  // if (t->r == z)
  if (oTreNode_tt.dRight_GE == 0)
  {
    // x = x->l;
    // Datensatz xx lesen
    dRecNo_xx =  oTreNode_xx.dLeft_LT;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);


  }
  // else if (t->r->l == z)
  else if (oTreNode_tr.dLeft_LT == 0)
  {
    // x = x->r;
    // Datensatz xx lesen
    dRecNo_xx =  oTreNode_xx.dRight_GE;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

    // x->l = t->l;
    oTreNode_xx.dLeft_LT = oTreNode_tt.dLeft_LT;
    // Für Datensatz -xx- die Nachfolger-Adressen im Baum -TreNr- setzen
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  }
  else
  {
    // c = x->r;
    // Datensatz xx lesen
    dRecNo_cc = oTreNode_xx.dRight_GE;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

    // Datensatz cl lesen
    iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_cc.dLeft_LT, v_cl, &oTreNode_cl);


    // while (c->l->l != z)
    while (oTreNode_cl.dLeft_LT != 0)
    {
      // c = c->l;
      // Datensatz cc lesen
      dRecNo_cc = oTreNode_cc.dLeft_LT;
      iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

      // Datensatz cl lesen
      iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_cc.dLeft_LT, v_cl, &oTreNode_cl);

    }
    // x = c->l;
    // Datensatz xx lesen
    dRecNo_xx = oTreNode_cc.dLeft_LT;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

    // Datensatz intern schreiben
    // c->l = x->r;
    oTreNode_cc.dLeft_LT = oTreNode_xx.dRight_GE;
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

    // x->l = t->l;
    oTreNode_xx.dLeft_LT = oTreNode_tt.dLeft_LT;

    // x->r = t->r;
    oTreNode_xx.dRight_GE = oTreNode_tt.dRight_GE;
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  }

  oTreNode_tt.dRight_GE = 0;
  oTreNode_tt.dLeft_LT  = 0;
  iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_tt, v_tt, &oTreNode_tt);


  if (dRecNo_pp != 0)
  {
    // if (v < p->Key)
    if ( DSiCompLT ( 0, &this->poTre[oTre->iTriNo-1], vSearchValue, v_pp)  )
    {
      // p->l = x;
      oTreNode_pp.dLeft_LT = dRecNo_xx;
    }
    else
    {
      // p->r = x;
      oTreNode_pp.dRight_GE = dRecNo_xx;
    }
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_pp, v_pp, &oTreNode_pp);
  }
  else
  {
    // Der aktuelle Baum bekommt einen neuen Einstiegs-Datensatz
    this->poTre[oTre->iTriNo-1].dRoot = dRecNo_xx;
  }

  free ( v_cl);
  free ( v_tr);
  free ( v_tt);
  free ( v_xx);
  free ( v_pp);
  free ( v_cc);

  *dRecNo = dRecNo_tt;
  if(dRecNo_tt > 0) return 1;
  else return 0;
}
//=============================================================================
int sstRec04InternCls::TreDelNumber ( int                   iKey,
                                      dREC04RECNUMTYP      dRecNo)
//-----------------------------------------------------------------------------
{
  int        TreNr = 0;
  int        iStat = 0;
  //-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Loop over all defined trees
  for( TreNr=1; TreNr <= this->iTriAnz; TreNr++)
  {

    // Delete record with number from given tree
    iStat = this->TreDelIntern ( 0, &this->poTre[TreNr-1],  dRecNo);

  }
  return iStat;
}
//=============================================================================
int sstRec04InternCls::TreDelIntern ( int                   iKey,
                                      sstRec04TreeHeaderCls   *poTreHead,
                                      dREC04RECNUMTYP      dRecNo)
//-----------------------------------------------------------------------------
  {
  void *v_cc, *v_pp, *v_xx, *v_tt, *v_tr, *v_cl; // 6 local records in heap
  void *vSearchValue = NULL;
  sstRec04TreeNodeCls   oTreNode_xx;       // Tree Node Data from record xx
  sstRec04TreeNodeCls   oTreNode_pp;       // Tree Node Data from record pp
  sstRec04TreeNodeCls   oTreNode_tt;       // Tree Node Data from record tt
  sstRec04TreeNodeCls   oTreNode_tr;       // Tree Node Data from record tr
  sstRec04TreeNodeCls   oTreNode_cc;       // Tree Node Data from record cc
  sstRec04TreeNodeCls   oTreNode_cl;       // Tree Node Data from record cl
  dREC04RECNUMTYP    dRecNo_tt = 0;       // Record Number from tt
  dREC04RECNUMTYP    dRecNo_xx = 0;       // Record Number from xx
  dREC04RECNUMTYP    dRecNo_pp = 0;       // Record Number from pp
  dREC04RECNUMTYP    dRecNo_cc = 0;       // Record Number from cc
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // Get Adress of compare value in local memory
  int iUsrOfs = 0;
  this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
  this->poVector->CalcSetPos(this->poVector->GetAdr(), &vSearchValue, (iUsrOfs + poTreHead->iOffset));

  v_cc = malloc ( this->poVector->GetSize());
  assert(v_cc);
  v_pp = malloc (  this->poVector->GetSize());
  assert(v_pp);
  v_xx = malloc ( this->poVector->GetSize());
  assert(v_xx);
  v_tt = malloc ( this->poVector->GetSize());
  assert(v_tt);
  v_tr = malloc ( this->poVector->GetSize());
  assert(v_tr);
  v_cl = malloc ( this->poVector->GetSize());
  assert(v_cl);

  // Datensatz intern lesen
  // -head- dürfte der Einstieg in den Baum sein, in DSS also SNr = 1
  // p = head;
  dRecNo_pp = poTreHead->dRoot;


  // DS xx ist der rechte Nachfolger vom Root-Datensatz
  // Datensatz xx lesen
  // x = head->r;
  // Baumdaten in Baum TreNr für Datensatz SNr zurückliefern
  // dRecNo_xx = this->poTre[oTre->iTriNo-1].dRoot;
  dRecNo_xx = poTreHead->dRoot;

  iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  // Fatal Errors goes to an assert
  if (iStat < 0)
  {
    // Expression (iRet >= 0) has to be fullfilled
    assert(0);
  }


  // do loop while true
  // Vergleich der Sortiervariablen
  while ( !(DSiCompEQ ( 0, poTreHead, vSearchValue, v_xx) && dRecNo_xx==dRecNo))
  {
    // p = x;
    memcpy( v_pp, v_xx, this->poVector->GetSize());
    dRecNo_pp = dRecNo_xx;
    oTreNode_pp = oTreNode_xx;

    // x = (v < x->key) ? x->l : x->r;
    // Vergleich der Sortiervariablen

    if ( DSiCompLT ( 0, poTreHead, vSearchValue, v_xx)  )
    {

      // Datensatz xx lesen
      // x = x->l;
      dRecNo_xx =  oTreNode_xx.dLeft_LT;
    }
    else
    {
      // Datensatz xx lesen
      // x = x->r;
      dRecNo_xx =  oTreNode_xx.dRight_GE;
    }

    // Für Datensatz -pp- die Nachfolger-Adressen im Baum -TreNr- liefern
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

  //    }
    }  // end while is not equal

  // t = x;
  memcpy( v_tt, v_xx, this->poVector->GetSize());
  dRecNo_tt = dRecNo_xx;
  oTreNode_tt = oTreNode_xx;

  // Für Datensatz -tt- die Nachfolger-Adressen im Baum -TreNr- liefern
  // Datensatz tr lesen
  iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_tt.dRight_GE, v_tr, &oTreNode_tr);

  // if (t->r == z)
  if (oTreNode_tt.dRight_GE == 0)
  {
    // x = x->l;
    // Datensatz xx lesen
    dRecNo_xx =  oTreNode_xx.dLeft_LT;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);


  }
  // else if (t->r->l == z)
  else if (oTreNode_tr.dLeft_LT == 0)
  {
    // x = x->r;
    // Datensatz xx lesen
    dRecNo_xx =  oTreNode_xx.dRight_GE;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

    // x->l = t->l;
    oTreNode_xx.dLeft_LT = oTreNode_tt.dLeft_LT;
    // Für Datensatz -xx- die Nachfolger-Adressen im Baum -TreNr- setzen
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  }
  else
  {
    // c = x->r;
    // Datensatz xx lesen
    dRecNo_cc = oTreNode_xx.dRight_GE;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

    // Datensatz cl lesen
    iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_cc.dLeft_LT, v_cl, &oTreNode_cl);


    // while (c->l->l != z)
    while (oTreNode_cl.dLeft_LT != 0)
    {
      // c = c->l;
      // Datensatz cc lesen
      dRecNo_cc = oTreNode_cc.dLeft_LT;
      iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

      // Datensatz cl lesen
      iStat = DSiTreDatGet ( 0, poTreHead, oTreNode_cc.dLeft_LT, v_cl, &oTreNode_cl);

    }
    // x = c->l;
    // Datensatz xx lesen
    dRecNo_xx = oTreNode_cc.dLeft_LT;
    iStat = DSiTreDatGet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);

    // Datensatz intern schreiben
    // c->l = x->r;
    oTreNode_cc.dLeft_LT = oTreNode_xx.dRight_GE;
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_cc, v_cc, &oTreNode_cc);

    // x->l = t->l;
    oTreNode_xx.dLeft_LT = oTreNode_tt.dLeft_LT;

    // x->r = t->r;
    oTreNode_xx.dRight_GE = oTreNode_tt.dRight_GE;
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_xx, v_xx, &oTreNode_xx);
  }

  oTreNode_tt.dRight_GE = 0;
  oTreNode_tt.dLeft_LT  = 0;
  iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_tt, v_tt, &oTreNode_tt);


  if (dRecNo_pp != 0)
  {
    // if (v < p->Key)
    if ( DSiCompLT ( 0, poTreHead, vSearchValue, v_pp)  )
    {
      // p->l = x;
      oTreNode_pp.dLeft_LT = dRecNo_xx;
    }
    else
    {
      // p->r = x;
      oTreNode_pp.dRight_GE = dRecNo_xx;
    }
    iStat = DSiTreDatSet ( 0, poTreHead, dRecNo_pp, v_pp, &oTreNode_pp);
  }
  else
  {
    // Der aktuelle Baum bekommt einen neuen Einstiegs-Datensatz
    poTreHead->dRoot = dRecNo_xx;
  }

  free ( v_cl);
  free ( v_tr);
  free ( v_tt);
  free ( v_xx);
  free ( v_pp);
  free ( v_cc);

  if(dRecNo_tt > 0) return 1;
  else return 0;
}
//=============================================================================
int sstRec04InternCls::DSiCompEQ ( int                     Key,
                                       sstRec04TreeHeaderCls  *oTre,
                                       void                   *Adr1,
                                       void                   *CompDs)
//.............................................................................
{
  void         *Adr2;        // zweite Vergleichsvariable (Typenlos)
  int        iUsrOfs;   // offset of user data in full record

  int iRet;
//.............................................................................
  if (Key != 0) return -1;
  iRet = 0;

  // Adresse der Vergleichsvariablen in den Zwischenspeichern
  this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
  this->poVector->CalcSetPos(CompDs, &Adr2, (iUsrOfs + oTre->iOffset));

  // Vergleicht zwei Variablen ( AdrAlt EQ AdrNeu).
  iRet = DSiVarCompEQ ( 0, &oTre->eTyp, Adr1, Adr2);

  return iRet;
}
//=============================================================================
int sstRec04InternCls::DSiCompNE ( int                    Key,
                                         sstRec04TreeHeaderCls *oTre,
                                         void                  *Adr1,
                                         void                  *CompDs)
//.............................................................................
{
  void        *Adr2;    //   <-> Vergleichsvariable
  int        iUsrOfs;   // offset of user data in full record

  int iRet=0;
//.............................................................................
  if (Key != 0) return -1;

  // Adresse der Vergleichsvariablen in den Zwischenspeichern
  this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
  this->poVector->CalcSetPos(CompDs, &Adr2, (iUsrOfs + oTre->iOffset));

  // Vergleicht zwei Variablen ( AdrAlt NE AdrNeu).
  iRet = this->DSiVarCompNE ( 0, &oTre->eTyp, Adr1, Adr2);

  return iRet;
}
//=============================================================================
int sstRec04InternCls::DSiCompLT ( int                     iKey,
                                        sstRec04TreeHeaderCls  *oTre,
                                        void                   *Adr1,
                                        void                   *CompDs)
//.............................................................................
{
  void        *Adr2;    //   <-> Vergleichsvariable
  int        iUsrOfs;   // offset of user data in full record

  int iRet = 0;
//.............................................................................
  if (iKey != 0) return -1;

  // Adresse der Vergleichsvariablen in den Zwischenspeichern
  this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
  this->poVector->CalcSetPos(CompDs, &Adr2, (iUsrOfs + oTre->iOffset));

  // Vergleicht zwei Variablen ( AdrAlt LT AdrNeu).
  iRet = this->DSiVarCompLT ( 0, &oTre->eTyp, Adr1, Adr2);

  return iRet;
}
//=============================================================================
int sstRec04InternCls::DSiCompGE ( int                     iKey,
                                        sstRec04TreeHeaderCls  *oTre,
                                        void                   *Adr1,
                                        void                   *CompDs)
//.............................................................................
{
  void        *Adr2;    //   <-> Vergleichsvariable
  int        iUsrOfs;   // offset of user data in full record

  int iRet = 0;
//.............................................................................
  if (iKey != 0) return -1;

  // Adresse der Vergleichsvariablen in den Zwischenspeichern
  this->poVector->GetOffset(0,this->poRecMemUsrKey,&iUsrOfs);
  this->poVector->CalcSetPos(CompDs, &Adr2, (iUsrOfs + oTre->iOffset));

  // Vergleicht zwei Variablen ( AdrAlt LT AdrNeu).
  iRet = this->DSiVarCompGE ( 0, &oTre->eTyp, Adr1, Adr2);

  return iRet;
}
//=============================================================================
int sstRec04InternCls::resetRecord(int iKey, void *vRecAdr)
{
  if ( iKey != 0) return -1;

  unsigned long ulSize = 0;
  int iStat = this->poVector->GetCargoSize(0,this->poRecMemUsrKey,&ulSize);
  // memset(vRecAdr,0,this->poVector->GetSize());
  memset( vRecAdr, 0, ulSize);
  // unsigned long ulSize = this->poMemAdr[oDataKey->iKey-1].GetCargoSize();
  return iStat;
}
//=============================================================================
dREC04RECNUMTYP sstRec04InternCls::GetUserRecordSize()
{
  unsigned long ulSize = 0;
  this->poVector->GetCargoSize(0,this->poRecMemUsrKey,&ulSize);
  return ulSize;
}
//=============================================================================
int sstRec04InternCls::TreeLog(int                   iKey,
                               sstRec04TreeKeyCls   *oTre,
                               char                 *cLogFilNam)
{
  void *Adr1 = NULL;        // adress of compare value in vector
  // dREC04RECNUMTYP  Root = 0;
  sstRec04TreeNodeCls *oTreeNode;
  sstMisc01AscFilCls oAscFil;
  std::string oFilRow;
  sstStr01Cls oCsvConvert;

  dREC04RECNUMTYP  ii = 0;
  dREC04RECNUMTYP  dRecNo1 = 0;
  dREC04RECNUMTYP  dRecNo2 = 0;
  dREC04RECNUMTYP  dLoops = 0;
  int   iStat = 0;
//.............................................................................
  if ( iKey != 0) return -1;

  // Open Asc File for Writing
  iStat = oAscFil.fopenWr ( 0, cLogFilNam);
  assert(iStat==0);

  // Root = 0;

  for( ii=1; ii<=this->dActStored; ii++)
  {
    // record record from RecMem into vector
    iStat = this->ReadInt(  0, ii, this->poVector->GetAdr());

    // Get adress of user data
    void *vUsrAdr = NULL;
    iStat = this->poVector->GetCargoAdr(0,this->poRecMemUsrKey,&vUsrAdr);
    // Get Adress of compare value in user data
    this->poVector->CalcSetPos( vUsrAdr, &Adr1, this->poTre[oTre->iTriNo-1].iOffset);
    char* pcCompValue;
    pcCompValue = (char*) Adr1;

    // Get adress of Tree data
    void *vTreAdr = NULL;
    iStat = this->poVector->GetCargoAdr(0, this->poTre[oTre->iTriNo-1].poDataKey,&vTreAdr);
    oTreeNode = (sstRec04TreeNodeCls*) vTreAdr;
    // Get Adress of compare value in user data
    // this->poVector->CalcSetPos( vUsrAdr, &Adr1, this->poTre[oTre->iTriNo-1].iOffset);

    // Insert new record ii in tree otre with root record
    // Root = DSiTreInsert( 0, &this->poTre[oTre->iTriNo-1], Root , ii, Adr1);

    // convert long int to csv-formatted string and append to string
    oFilRow.clear();
    iStat = oCsvConvert.Csv_Int4_2String ( 0, ii, &oFilRow);
    iStat = oCsvConvert.Csv_Int4_2String ( 0, oTreeNode->dLeft_LT, &oFilRow);
    iStat = oCsvConvert.Csv_Int4_2String ( 0, oTreeNode->dRight_GE, &oFilRow);
    iStat = oCsvConvert.Csv_Char_2String( 0, pcCompValue, &oFilRow);

    // Write Str1 structure to file
    iStat = oAscFil.Wr_StrDS1 ( 0, &oFilRow);

  }

  // Write empty row
  oFilRow.clear();
  iStat = oAscFil.Wr_StrDS1 ( 0, &oFilRow);

  dRecNo1 = 0;
  // return record number for smallest value for tree oTriKey_CC
  iStat = this->TreSeaFrst ( 0, oTre, &dRecNo1);

  while (dRecNo1 > 0)
  {
    // record record from RecMem into vector
    iStat = this->ReadInt(  0, dRecNo1, this->poVector->GetAdr());

    // Get adress of user data
    void *vUsrAdr = NULL;
    iStat = this->poVector->GetCargoAdr(0,this->poRecMemUsrKey,&vUsrAdr);
    // Get Adress of compare value in user data
    this->poVector->CalcSetPos( vUsrAdr, &Adr1, this->poTre[oTre->iTriNo-1].iOffset);
    char* pcCompValue;
    pcCompValue = (char*) Adr1;

    // Get adress of Tree data
    void *vTreAdr = NULL;
    iStat = this->poVector->GetCargoAdr(0, this->poTre[oTre->iTriNo-1].poDataKey,&vTreAdr);
    oTreeNode = (sstRec04TreeNodeCls*) vTreAdr;

    // convert long int to csv-formatted string and append to string
    oFilRow.clear();
    iStat = oCsvConvert.Csv_Int4_2String ( 0, dRecNo1, &oFilRow);
    iStat = oCsvConvert.Csv_Int4_2String ( 0, oTreeNode->dLeft_LT, &oFilRow);
    iStat = oCsvConvert.Csv_Int4_2String ( 0, oTreeNode->dRight_GE, &oFilRow);
    iStat = oCsvConvert.Csv_Char_2String( 0, pcCompValue, &oFilRow);

    // Write Str1 structure to file
    iStat = oAscFil.Wr_StrDS1 ( 0, &oFilRow);

    // Return record number for next greater/equal value
    iStat = this->TreSeaNxtGE ( 0, oTre, dRecNo1, &dRecNo2);

    dRecNo1 = dRecNo2;
    dLoops++;
    if(dLoops > this->dActStored)
    {
      dRecNo1 = 0;
      oFilRow = "ERROR: Hard break!";
      iStat = oAscFil.Wr_StrDS1 ( 0, &oFilRow);
    }

  }

  // Close file
  iStat = oAscFil.fcloseFil ( 0);

  return 0;
}
//=============================================================================
