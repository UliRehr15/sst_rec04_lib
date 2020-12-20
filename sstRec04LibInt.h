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
// sstRec04LibInt.h   17.11.15  Re.   17.10.15  Re.
//
// Intern Datastructures and Prototypes for system "sstRec04Lib"
//

#ifndef   _SST_REC04_LIB_INT_HEADER
#define   _SST_REC04_LIB_INT_HEADER

#include <string>

#include "sstStr01Lib.h"
#include "sstRec04Lib.h"

/**
 * @defgroup sstRecord04InternLib sstRecord04InternLib: Intern cpp sst record library
 *
 * Intern cpp sst record library <BR>
 *
 */


// Defines ---------------------------------------------------------------------

/**
 * @brief Maximal File Name Length
 * @ingroup sstRecord04InternLib
 */
#define dREC04FILNAMMAXLEN 260

/**
 * @brief Maximal Cargo Sys Name Length
 * @ingroup sstRecord04InternLib
 */
#define dREC04CARGONAMMAXLEN 4


// Structures and Classes ------------------------------------------------------

//==============================================================================
/**
* @brief Adress array for all definied sort types
*
* More Comment
*
* Changed: 27.10.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 27.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04CompValueCls
{
  public:   // Public functions
     sstRec04CompValueCls();   // Constructor
    // ~X();   // Destructor
// ----------------------------------------------------------------------------
     char          *CComp;   /**< Character */
     int           *IComp;   /**< Integer */
     long          *LComp;   /**< Long integer */
     unsigned int  *UIComp;  /**< Unsigned integer */
     unsigned long *ULComp;  /**< Unsigned long integer */
     float         *RComp;   /**< float */
     double        *DComp;   /**< long float */
  private:  // Private functions
};
//==============================================================================
/**
* @brief sstRecMem Internal Header Class with System Data for every record <BR>
*
* With Delete Flag, Mark Flag, Version String, New Date and so on. <BR>
* Stored as cargo class inside record.
*
* Changed: 12.10.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 12.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04HeaderCls
{
  public:   // Public functions
     sstRec04HeaderCls();  // Constructor
     //==============================================================================
     /**
     * @brief // Get Size of full record size with all cargo packets <BR>
     * dRecordSize = oRemMemHeader.getRecSize();
     *
     * @retval  Record Size
     */
     // ----------------------------------------------------------------------------
     dREC04RECSIZTYP getRecSize() const;
     //==============================================================================
     /**
     * @brief // Set Size of full Record with all cargo packets <BR>
     * oRecMem.setRecSize( dRecSize);
     *
     * @param dRecSize [in] Record Size
     *
     */
     // ----------------------------------------------------------------------------
     void setRecSize(const dREC04RECSIZTYP &dRecSize);
     //==============================================================================
     /**
     * @brief return adress of version string
     *
     * @return adress of version string
     */
     // ----------------------------------------------------------------------------
     char* GetVersStr();
     //==============================================================================
     /**
     * @brief set version string
     *
     * @param cNam [in] adress of version string
     */
     // ----------------------------------------------------------------------------
     void SetVersStr(char *cNam);
     //==============================================================================
     /**
     * @brief set version string
     */
     // ----------------------------------------------------------------------------
     void SetNewDate();
     //==============================================================================
     /**
     * @brief set version string
     */
     // ----------------------------------------------------------------------------
     void SetChangeDate();
     //==============================================================================
     /**
     * @brief set record deleted status
     */
     // ----------------------------------------------------------------------------
     void RecSetDeleted();
     //==============================================================================
     /**
     * @brief set record marked status
     */
     // ----------------------------------------------------------------------------
     void RecSetMarked();
     //==============================================================================
     /**
     * @brief set record undeleted status
     */
     // ----------------------------------------------------------------------------
     void RecSetUndeleted();
     //==============================================================================
     /**
     * @brief set record unmarked status
     */
     // ----------------------------------------------------------------------------
     void RecSetUnmarked();
     //==============================================================================
     /**
     * @brief get record Delete Status
     */
     // ----------------------------------------------------------------------------
     bool RecGetDeleteStatus();
     //==============================================================================
     /**
     * @brief get record Mark Status
     */
     // ----------------------------------------------------------------------------
     bool RecGetMarkStatus();


private:  // Private functions
     char cVersionstring[10];    /**< Version String, for exampe sstRec02 */
     dREC04RECSIZTYP dRecSize;  /**< Size of every Record */
     char cRecChgDateTime[18];    /**< Write Change Date, for exampe 151012 */
     char cRecNewDateTime[18];    /**< Write New Date, for exampe 151012 */
     bool bDel;    /**< Delete Flag */
     bool bMark;   /**< Mark Flag */
};
//==============================================================================
/**
* @brief System data for every cargo packet
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstRec04CargoMemCls
{
  public:   // Öffentliche Funktionen
     sstRec04CargoMemCls();  // Konstruktor
     ~sstRec04CargoMemCls();  // Destruktor
     //==============================================================================
     /**
     * @brief return Offset
     *
     * @return Offset
     */
     // ----------------------------------------------------------------------------
     int GetOffset();
     //==============================================================================
     /**
     * @brief Set Offset
     *
     * @param iOffset [in] Offset
     */
     // ----------------------------------------------------------------------------
     void SetOffset(int iOffset);
     //==============================================================================
     /**
     * @brief return Cargo Size
     *
     * @return Cargo Size
     */
     // ----------------------------------------------------------------------------
     int GetCargoSize();
     //==============================================================================
     /**
     * @brief Set Cargo Size
     *
     * @param iSize [in] Cargo Size
     */
     // ----------------------------------------------------------------------------
     void SetCargoSize(int iSize);
     //==============================================================================
     /**
     * @brief return adress of cargo name char
     *
     * @return adress of cargo name char
     */
     // ----------------------------------------------------------------------------
     char* GetCargoSysNam();
     //==============================================================================
     /**
     * @brief set cargo name
     *
     * @param cNam [in] adress of cargo name char
     */
     // ----------------------------------------------------------------------------
     void SetCargoSysNam(char *cNam);
     //==============================================================================
     /**
     * @brief get cargo adress
     *
     * @return cargo adress
     */
     // ----------------------------------------------------------------------------
     void* GetCargoAdr();
     //==============================================================================
     /**
     * @brief set cargo adress
     *
     * @param vCargoAdr [in] adress of cargo
     */
     // ----------------------------------------------------------------------------
     void SetCargoAdr(void *vCargoAdr);
     //==============================================================================
  private:  // Private Funktionen
     int iOffset;           /**< Offset from Start of vector */
     int iSize;             /**< Size of cargo sys*/
     char cNam[4];          /**< Name of cargo sys */
     void *vCargoAdr;        /**< Adress in vector memory */
};


//==============================================================================
/**
* @brief vector storage with all defined cargo packets
*
* More Comment
*
* Changed: 01.10.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 01.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04VectSysCls
{
  public:   // Öffentliche Funktionen
    //=============================================================================
    /**
    * @brief constructor for vector memory
    *
    * @return Errorstate
    *
    * @retval   =0: OK
    * @retval   <0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
     sstRec04VectSysCls();
     ~sstRec04VectSysCls();
     //=============================================================================
     /**
     * @brief // Add cargo system to vector memory and get new identification key <BR>
     * iStat = oVector.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
     *
     * @param iKey      [in]  For the moment 0
     * @param uiSize    [in]  Size of cargo record
     * @param cCargoNam [in]  Name of cargo system (4 Letters)
     * @param oCargoKey [out] key of new cargo object
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Cargo Packet must not be empty
     * @retval   =-3: Cargo Name has to be length 3
     * @retval   =-4: Cargo Key should be empty
     * @retval   =-5: Cargo Name should be unique
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int AddCargoSys( int             iKey,
                      unsigned int    uiSize,
                      char           *cCargoNam,
                      sstRec04CargoKeyInternCls *oCargoKey);
     //=============================================================================
     /**
     * @brief write record to vector Memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  adress of cargo record
     * @param vCargoAdr [in]  adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Cargo key not OK for RecMem object
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtCargo ( int              iKey,
                    sstRec04CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);

     //=============================================================================
     /**
     * @brief Read record from vector memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  Adress of cargo record
     * @param vCargoAdr [in]  Adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Cargo key not OK for RecMem object
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RedCargo ( int              iKey,
                    sstRec04CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);

     //=============================================================================
     /**
     * @brief Calculate new position in memory
     *
     * @param BasPtr [in]  Basis pointer
     * @param IdxPtr [out] Result pointer = Basis + offset
     * @param Offs   [in]  Offset
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void CalcSetPos ( void   *BasPtr,
                       void  **IdxPtr,
                       long    Offs);

     //=============================================================================
     /**
     * @brief Get size of vector
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     unsigned long GetSize() const;

     //=============================================================================
     /**
     * @brief Get adress of vector
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void* GetAdr() const;
     //=============================================================================
     /**
     * @brief Get Adress of cargo system
     *
     * @param iKey      [in]     For the moment 0
     * @param oDataKey  [in out] Key of cargo object
     * @param vCargoAdr [out]    Adress of cargo system
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetCargoAdr (int               iKey,
                      sstRec04CargoKeyInternCls  *oDataKey,
                      void            **vCargoAdr);
     //=============================================================================
     /**
     * @brief // Get Record size of named cargo system <BR>
     * iStat = oMemVector.GetCargoSize ( iKey, &oDataKey, &ulRecSize);
     *
     * @param iKey      [in]   For the moment 0
     * @param oDataKey  [in]   Key of cargo object
     * @param ulRecSize [out]  Record Size of cargo system
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetCargoSize (int                         iKey,
                       sstRec04CargoKeyInternCls  *oDataKey,
                       unsigned long              *ulRecSize);
     //=============================================================================
     /**
     * @brief Get offset of cargo system
     *
     * @param iKey     [in]     For the moment 0
     * @param oDataKey [in out] Key of cargo object
     * @param iOffset  [out]    offset of cargo object
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetOffset (int                iKey,
                    sstRec04CargoKeyInternCls   *oDataKey,
                    int               *iOffset);
     //=============================================================================
     /**
     * @brief reset memory of vector
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void ResetMem(int iKey);

  private:
    unsigned int              uiNumCargoSys;  /**< Number of Cargo Systems */
    sstRec04CargoMemCls *poMemAdr;        /**< Field of of Cargo Systems */
    void            *vVectorAdr;     /**< main memory vector with all cargo values */
    dREC04RECSIZTYP    dVectorSize;  /**< size of main memory vector */
};
//==============================================================================
/**
* @brief Intern key object for cargo packet
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 19.02.10
*/
//==============================================================================
class sstRec04CargoKeyInternCls
{
  public:   // Öffentliche Funktionen
     sstRec04CargoKeyInternCls();  // Konstruktor
     ~sstRec04CargoKeyInternCls();  // Destruktor
     int  iKey;           /**< Key of cargo sys */
     char cNam[dREC04CARGONAMMAXLEN+1];        /**< Name of cargo sys*/
     sstRec04VectSysCls *poCargoAdr;  /**< Adress of cargo object  */
  private:  // Private Funktionen
     // int iDummy;
};
//==============================================================================
/**
* @brief Tree node data are stored inside record
*
* More Comment
*
* Changed: 27.10.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 27.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04TreeNodeCls
{
  public:
    sstRec04TreeNodeCls();
    dREC04RECNUMTYP dLeft_LT;   /**< left branch smaller */
    dREC04RECNUMTYP dRight_GE;  /**< right branch greater/equal */
  private:  // Private functions
};
//==============================================================================
/**
* @brief All internal data for tree object
*
* Are stored in array inside RecMem object
*
* Changed: 27.10.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 27.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04TreeHeaderCls
{
public:
  sstRec04TreeHeaderCls();
  // ~sstRec04TreeHeaderCls();
  dREC04RECNUMTYP    dRoot;             /**< Base record of actual tree */
  int                iNodeOfs;          /**< Offset of Tree Node data from start of full record */
  int                iOffset;           /**< Offset of sort value from start of user record */
  int                iSize;             /**< Size of sort value */
  sstRec04CompTyp_enum   eTyp;          /**< Type of sort value */
  sstRec04CargoKeyInternCls *poDataKey;  /**< Cargo key object */
private:  // Private functions
};
//==============================================================================
/**
* @brief intern sstRecMem class
*
* Intern class for sstRecordLib <BR>
*
* Changed: 04.08.15  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 09.07.15
*/
// ----------------------------------------------------------------------------
class sstRec04InternCls
{
  public:   // Public functions
    //==============================================================================
    /**
    * @brief constructor with size of one record
    *
    * @param Size [in] Size of one record
    */
    // ----------------------------------------------------------------------------
     sstRec04InternCls(dREC04RECSIZTYP Size);  // Constructor
    ~sstRec04InternCls();  // Destructor
     //==============================================================================
     /**
     * @brief // Write new record into intern sstRec memory <BR>
     * iStat = oRecMem.WritNewInt( iKey, vRecAdr, dRecNo);
     *
     * @param iKey    [in]  For the moment 0
     * @param vRecAdr [in]  Record to store
     * @param dRecNo  [out] New index number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritNewInt(int iKey, void* vRecAdr, dREC04RECNUMTYP *dRecNo);
     //==============================================================================
     /**
     * @brief // Write new record with sstRec vector <BR>
     * iStat = oRecMem.WritNewVector( iKey, vRecAdr, dRecNo);
     *
     * @param iKey    [in]  For the moment 0
     * @param vRecAdr [in]  Record to store
     * @param dRecNo  [out] New index number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritNewVector(int iKey, void* vRecAdr, dREC04RECNUMTYP *dRecNo);
     //==============================================================================
     /**
     * @brief // Write Record at position in intern sstRec Memory  <BR>
     * iStat = oRecMem.WritInt( iKey, *vRecAdr,  dRecNo);
     *
     * @param iKey    [in] For the moment 0
     * @param vRecAdr [in] Adress of record
     * @param dRecNo  [in] target position to write record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Wrong Record positon
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritInt(int iKey, void* vRecAdr, dREC04RECNUMTYP dRecNo);
     //==============================================================================
     /**
     * @brief // Write Record at position with sstRec vector  <BR>
     * iStat = oRecMem.WritVector( iKey, *vRecAdr, dRecNo);
     *
     * @param iKey    [in] For the moment 0
     * @param vRecAdr [in] Adress of record
     * @param dRecNo  [in] target position to write record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Wrong Record positon
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WritVector(int iKey, void* vRecAdr, dREC04RECNUMTYP dRecNo);
     //==============================================================================
     /**
     * @brief // Read record from sstRec memory with Record number <BR>
     * iStat = oRecMem.ReadInt( iKey, dRecNo, *vRecAdr);
     *
     * @param iKey    [in] For the moment 0
     * @param dRecNo  [in] record number to read
     * @param vRecAdr [out read record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Wrong Record positon
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadInt(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);
     //==============================================================================
     /**
     * @brief // Read record from sstRec memory with Record number and vector <BR>
     * iStat = oRecMem.ReadVector( iKey, dRecNo, *vRecAdr);
     *
     * @param iKey    [in] For the moment 0
     * @param dRecNo  [in] record number to read
     * @param vRecAdr [out read record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Wrong Record positon
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ReadVector(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);
     //==============================================================================
     /**
     * @brief return number of stored records in sstRec memory
     *
     * @return number of records, which are stored
     */
     // ----------------------------------------------------------------------------
     dREC04RECNUMTYP count();
     //==============================================================================
     /**
     * @brief Open existing or new file of record storing
     *
     * @param iKey    [in]  For the moment 0
     * @param cSysNam [in]  File Name
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: File already open
     * @retval   =-3: Filename empty
     * @retval   =-4: sstRec not empty
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int OpenFile(int   iKey,
                  char *cSysNam);
     //==============================================================================
     /**
     * @brief Open new file of record storing
     *
     * @param iKey    [in]  For the moment 0
     * @param cSysNam [in]  File Name
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: File already open
     * @retval   =-3: Filename empty
     * @retval   =-4: sstRec not empty
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int NewFile(int   iKey,
                 char *cSysNam);
     //==============================================================================
     /**
     * @brief Store record data in file
     *
     * @param iKey  [in]  For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: No File open
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetStoreFile(int iKey);
     //==============================================================================
     /**
     * @brief // Add cargo system to sstRec memory and get new identification key <BR>
     * iStat = oRecMem.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
     *
     * @param iKey      [in]  For the moment 0
     * @param uiSize    [in]  Size of cargo record
     * @param cCargoNam [in]  Name of cargo system (4 Letters)
     * @param oCargoKey [out] key of new cargo object
     *
     * @return Errorstate
     *
     * @retval   =0:   OK
     * @retval   =-1:  Wrong Key
     * @retval   =-2:  Cargo Packet must not be empty
     * @retval   =-3:  Cargo Name has to be length 3
     * @retval   =-4:  Cargo Key should be empty
     * @retval   =-5:  Cargo Name should be unique
     * @retval   =-10: sstRecMem is not empty
     * @retval   <0:   Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int AddCargoSys( int                  iKey,
                      unsigned int         uiSize,
                      char                *cCargoNam,
                      sstRec04CargoKeyInternCls *oCargoKey);
     //=============================================================================
     /**
     * @brief write record to vector Memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  adress of cargo record
     * @param vCargoAdr [in]  adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Cargo key not OK for RecMem object
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int WrtCargo ( int              iKey,
                    sstRec04CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);
     //=============================================================================
     /**
     * @brief Read record from vector memory
     *
     * @param iKey      [in]  For the moment 0
     * @param oDataKey  [in]  Identification Key
     * @param vCargoAdr [in]  Adress of cargo record
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong Key
     * @retval   =-2: Cargo key not OK for RecMem object
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RedCargo ( int              iKey,
                    sstRec04CargoKeyInternCls *oDataKey,
                    void            *vCargoAdr);
     //=============================================================================
     /**
     * @brief Get adress of vector
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     void* GetVectorAdr() const;
     //=============================================================================
     /**
     * @brief Get Adress of cargo system
     *
     * @param iKey      [in]     For the moment 0
     * @param oDataKey  [in out] Key of cargo object
     * @param vCargoAdr [out]    Adress of cargo system
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetCargoAdr (int               iKey,
                      sstRec04CargoKeyInternCls  *oDataKey,
                      void            **vCargoAdr);
     //==============================================================================
     /**
     * @brief set date/time in new string of header object
     */
     // ----------------------------------------------------------------------------
     void SetNewDate();
     //==============================================================================
     /**
     * @brief set date/time in change string of header object
     */
     // ----------------------------------------------------------------------------
     void SetChangeDate();
     //==============================================================================
     /**
     * @brief // Set record state as deleted  for record dRecNo in RecMem  <BR>
     * iStat = oRecMem.RecSetDeleted ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RecSetDeleted ( int               iKey,
                         dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Set record state as marked  for record dRecNo in RecMem  <BR>
     * iStat = oRecMem.RecSetMarked ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RecSetMarked( int               iKey,
                        dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Set record state as undeleted  for record dRecNo in RecMem  <BR>
     * iStat = oRecMem.RecSetUndeleted ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RecSetUndeleted( int               iKey,
                           dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Set record state as unmarked for record dRecNo in RecMem  <BR>
     * iStat = oRecMem.RecSetUnmarked ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int RecSetUnmarked( int               iKey,
                          dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Get delete state of record dRecNo  <BR>
     * iStat = oRecMem.RecGetDeleteState ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Delete State
     *
     * @retval   =true:  Record is deleted
     * @retval   =false: Record is undeleted
     */
     // ----------------------------------------------------------------------------
     bool RecGetDeleteStatus( int               iKey,
                              dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Get mark state of record dRecNo <BR>
     * iStat = oRecMem.RecGetMarkState ( iKey,  RecNo);
     *
     * @param iKey   [in]  For the moment 0
     * @param dRecNo [in]  record number
     *
     * @return Mark State
     *
     * @retval   =true : Record is marked
     * @retval   =false: Record is unmarked
     */
     // ----------------------------------------------------------------------------
     bool RecGetMarkStatus( int               iKey,
                            dREC04RECNUMTYP   dRecNo);
     //=============================================================================
     /**
     * @brief Init new Tree System
     *
     * @param iKey    [in] For the moment 0
     * @param DsAdr   [in] Adress of record
     * @param CompAdr [in] Adress of compare value in record
     * @param CompSiz [in] Size of compare value
     * @param CompTyp [in] Type of compare value
     * @param oTre    [in] New Tree system
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreIni ( int              iKey,
                  void            *DsAdr,
                  void            *CompAdr,
                  int              CompSiz,
                  sstRec04CompTyp_enum     CompTyp,
                  sstRec04TreeKeyCls   *oTre);
     //=============================================================================
     /**
     * @brief Clean Tree Data and Rebuild Tree system
     *
     * iStat = oDss.TreBld ( iKey, *oTre);
     *
     * @param iKey [in]     For the moment 0
     * @param oTre [in out] Tree to rebuild
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreBld ( int              iKey,
                  sstRec04TreeKeyCls   *oTre);
     //=============================================================================
     /**
     * @brief find record with exact search value
     *
     * iStat = oDs2.TreSeaEQ  ( iKey, oTre, *Val, *SNr);
     *
     * @param iKey   [in]  at the moment 0
     * @param oTre   [in]  tree object
     * @param Val    [in]  search value
     * @param dRecNo [out] Value found at record number
     *
     * @return errorstate
     *
     * @retval   =0 Nothing found
     * @retval   =1 Exact value found at dRecNo
     * @retval   <0 Unspecified Error
     */
     //-----------------------------------------------------------------------------
     int TreSeaEQ  ( int              iKey,
                     sstRec04TreeKeyCls   *oTre,
                     void            *Val,
                     dREC04RECNUMTYP   *dRecNo);
     //==============================================================================
     /**
     * @brief // Insert new record in tree with root record  <BR>
     * iStat = oRecMem.DSiTreInsert (iKey, *oTre, dRecNoOld, dRecNoNew, *vRecAdr)
     *
     * @param iKey      [in] For the moment 0
     * @param oTre      [in] Tree object
     * @param dRecNoOld [in] Root or base record
     * @param dRecNoNew [in] record to insert in tree
     * @param vRecAdr   [in] adress of compare value for record new
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     dREC04RECNUMTYP DSiTreInsert ( int                    iKey,
                                    sstRec04TreeHeaderCls *oTre,
                                    dREC04RECNUMTYP        dRecNoOld,
                                    dREC04RECNUMTYP        dRecNoNew,
                                    void                  *vRecAdr);
     //=============================================================================
     /**
     * @brief Get next greater or equal
     *
     * @param iKey  [in]     For the moment 0
     * @param oTre  [in out] Tree system
     * @param DSatz [in]     actual dataset
     * @param SNr   [out]    Return next greater or equal
     *
     * @return Errorstate
     *
     * @retval   =0:  OK
     * @retval   =-1: Wrong key
     * @retval   =-2: nothing found
     * @retval   <0:  Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreReadNxtGE (int              iKey,
                      sstRec04TreeKeyCls   *oTre,
                      void            *DSatz,
                      dREC04RECNUMTYP    *SNr);
     //=============================================================================
     /**
     * @brief Return first record number
     *
     * @param iKey [in]     For the moment 0
     * @param oTre [in out] Tree system
     * @param SNr  [out]    Return record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreSeaFrst ( int            iKey,
                      sstRec04TreeKeyCls *oTre,
                      dREC04RECNUMTYP  *SNr);
     //=============================================================================
     /**
     * @brief Seach next greater
     *
     * @param iKey [in]     For the moment 0
     * @param oTre [in out] Tree system
     * @param SNr1 [in]     actual record number
     * @param SNr2 [out]    next record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreSeaNxtGE ( int             iKey,
                       sstRec04TreeKeyCls  *oTre,
                       dREC04RECNUMTYP    SNr1,
                       dREC04RECNUMTYP   *SNr2);
     //=============================================================================
     /**
     * @brief Seach next equal
     *
     * @param iKey       [in]     For the moment 0
     * @param oTre       [in out] Tree system
     * @param vSearchMin [in]     Min of search
     * @param vSearchMax [in]     Max of search
     * @param SNr        [in out] old adn new record number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreSeaNxtEQ ( int                   iKey,
                       sstRec04TreeKeyCls   *oTre,
                       void                 *vSearchMin,
                       void                 *vSearchMax,
                       dREC04RECNUMTYP      *SNr);
     //==============================================================================
     /**
     * @brief TreSeaGE
     *
     * @param iKey [in] For the moment 0
     * @param oTre [in]
     * @param Val  [in]
     * @param SNr  [in]
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreSeaGE ( int              iKey,
                    sstRec04TreeKeyCls   *oTre,
                    void            *Val,
                    dREC04RECNUMTYP    *SNr);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is equal than AdrNew  <BR>
     * iStat = oRecMem.DSiCompEQ ( iKey, *oTre, *vAdr1, *vCompAdr);
     *
     * @param iKey     [in] For the moment 0
     * @param oTre     [in] For the moment 0
     * @param vAdr1    [in] For the moment 0
     * @param vCompAdr [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiCompEQ ( int                     iKey,
                         sstRec04TreeHeaderCls  *oTre,
                         void                   *vAdr1,
                         void                   *vCompAdr);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is not equal than AdrNew  <BR>
     * iStat = oRecMem.DSiCompNE ( iKey, *oTre, *vAdr1, *vCompAdr);
     *
     * @param iKey     [in] For the moment 0
     * @param oTre     [in] For the moment 0
     * @param vAdr1    [in] For the moment 0
     * @param vCompAdr [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiCompNE ( int                     iKey,
                           sstRec04TreeHeaderCls  *oTre,
                           void                   *vAdr1,
                           void                   *vCompAdr);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is smaller than AdrNew  <BR>
     * iStat = oRecMem.DSiCompLT ( iKey, *oTre, *vAdr1, *vCompAdr);
     *
     * @param iKey     [in] For the moment 0
     * @param oTre     [in] For the moment 0
     * @param vAdr1    [in] For the moment 0
     * @param vCompAdr [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiCompLT ( int                     iKey,
                          sstRec04TreeHeaderCls  *oTre,
                          void                   *vAdr1,
                          void                   *vCompAdr);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is greater/equal than AdrNew  <BR>
     * iStat = oRecMem.DSiCompGE ( iKey, *oTre, *vAdr1, *vCompAdr);
     *
     * @param iKey     [in] For the moment 0
     * @param oTre     [in] For the moment 0
     * @param vAdr1    [in] For the moment 0
     * @param vCompAdr [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiCompGE ( int                     iKey,
                          sstRec04TreeHeaderCls  *oTre,
                          void                   *vAdr1,
                          void                   *vCompAdr);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is greater than AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompGT(iKey,eType,vAdrOld,vAdrNew)
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] For the moment 0
     * @param vAdrOld [in] For the moment 0
     * @param vAdrNew [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompGT (int                   iKey,
                       sstRec04CompTyp_enum *eType,
                       void                 *vAdrOld,
                       void                 *vAdrNew);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is greater/equal than AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompGE ( iKey, eType, vAdrOld, vAdrNew);
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] For the moment 0
     * @param vAdrOld [in] For the moment 0
     * @param vAdrNew [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompGE (int iKey, sstRec04CompTyp_enum *eType, void *vAdrOld, void *vAdrNew);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is smaller than AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompLT ( iKey, eType, vAdrOld, vAdrNew);
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] For the moment 0
     * @param vAdrOld [in] For the moment 0
     * @param vAdrNew [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompLT (int iKey, sstRec04CompTyp_enum *eType, void *vAdrOld, void *vAdrNew);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is smaller/equal than AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompLE ( iKey, eType, vAdrOld, vAdrNew);
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] For the moment 0
     * @param vAdrOld [in] For the moment 0
     * @param vAdrNew [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompLE (int iKey, sstRec04CompTyp_enum *eType, void *vAdrOld, void *vAdrNew);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is equal AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompEQ ( iKey, eType, vAdrOld, vAdrNew)
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] For the moment 0
     * @param vAdrOld [in] For the moment 0
     * @param vAdrNew [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompEQ (int iKey, sstRec04CompTyp_enum *eType, void *vAdrOld, void *vAdrNew);
     //==============================================================================
     /**
     * @brief // Is true, if Compare Value AdrOld is not equal AdrNew  <BR>
     * iStat = oRecMem.DSiVarCompNE ( iKey, eType, vAdrOld, vAdrNew)
     *
     * @param iKey    [in] For the moment 0
     * @param eType   [in] value type
     * @param vAdrOld [in] old value
     * @param vAdrNew [in] new (compare) value
     *
     * @return Errorstate
     *
     * @retval   =1: true: values are not equal
     * @retval   =0: false: values are equal
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiVarCompNE (int iKey, sstRec04CompTyp_enum *eType, void *vAdrOld, void *vAdrNew);
     //==============================================================================
     /**
     * @brief // Set type and adress for compare value in ValSet <BR>
     * iStat = oRecMem.DSiCompValue(iKey,vValueAdr,eCompTyp,poCompValue);
     *
     * @param iKey        [in]  For the moment 0
     * @param vValueAdr   [in]  Adress of Compare Value
     * @param eCompTyp    [in]  Type of compare value
     * @param poCompValue [out] return object for comparing
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiCompValue (int                    iKey,
                       void                  *vValueAdr,
                       sstRec04CompTyp_enum  *eCompTyp,
                       sstRec04CompValueCls  *poCompValue);
     //==============================================================================
     /**
     * @brief // In Tree oTre seach Value and return record number <BR>
     * iStat = oRecMem.DSiTreSearch( iKey, oTre, Val, xx_SNr);
     *
     * @param iKey     [in]  0
     * @param oTre     [in]  Tree object
     * @param Val      [in]  Seach Value
     * @param xx_SNr   [out] Result Record Number
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiTreSeach ( int                  iKey,
                       sstRec04TreeKeyCls  *oTre,
                       void                *Val,
                       dREC04RECNUMTYP     *xx_SNr);
     //==============================================================================
     /**
     * @brief // In Tree oTre for Record 1 seach next greater Record 2 <BR>
     * iStat = oRecMem.DSiTreSeaNxtGT(iKey,oTre,dRecNo,dRecNo1,*dRecNo2);
     *
     * @param iKey     [in]  0,1, or 2
     * @param oTre     [in]  Tree object
     * @param dRecNo   [in]  Record Number base
     * @param dRecNo1  [in]  Record Number 1
     * @param pdRecNo2 [out] Result Record Number 2
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiTreSeaNxtGT ( int              *iKey,
                          sstRec04TreeKeyCls    *oTre,
                          dREC04RECNUMTYP   dRecNo,
                          dREC04RECNUMTYP   dRecNo1,
                          dREC04RECNUMTYP  *pdRecNo2);
     //=============================================================================
     /**
     * @brief // Read record dRecNo into vRecAdc Memory and return tree node data of tree oTre <BR>
     * iStat = oRecMem.DSiTreDatGet(iKey,*poTre,dRecNo,*vRecAdr,*poTreData);
     *
     * @param iKey      [in] For the moment 0
     * @param poTreHead [in] Tree Header
     * @param dRecNo    [in] Record number
     * @param vRecAdr   [in] adress of temporary record memory
     * @param poTreData [out] Return Tree node data
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiTreDatGet ( int                 iKey,
                        sstRec04TreeHeaderCls      *poTreHead,
                        dREC04RECNUMTYP     dRecNo,
                        void               *vRecAdr,
                        sstRec04TreeNodeCls    *poTreData);
     //==============================================================================
     /**
     * @brief Write Tree Data into vector and write vector into RecMem
     *
     * Was used by delete record functions
     *
     * @param iKey       [in] For the moment 0
     * @param oTreHead   [in] Actual Tree Header
     * @param SNr    [in]
     * @param DSatz  [in]
     * @param TreDat [in]
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     //=============================================================================
     int DSiTreDatSet ( int             iKey,
                        sstRec04TreeHeaderCls  *oTreHead,
                        dREC04RECNUMTYP    SNr,
                        void           *DSatz,
                        sstRec04TreeNodeCls    *TreDat);
     //=============================================================================
     /**
     * @brief // Return adress of tree data in record vActDs <BR>
     * iStat= oRecMem.DSiTreAdrGet( iKey, poTreHead, vActRec, poNodeData)
     *
     * @param iKey        [in]  For the moment 0
     * @param poTreHead   [in]  Tree Header
     * @param vActRec     [in]  Record vector
     * @param poNodeData  [out] adress of tree data in record
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiTreAdrGet ( int                      iKey,
                        sstRec04TreeHeaderCls   *poTreHead,
                        void                    *vActRec,
                        sstRec04TreeNodeCls     *poNodeData);
     //==============================================================================
     /**
     * @brief // Write Tree Data into record vector
     * iStat = oRecMem.DSiTreAdrSet ( iKey,  *poTreeHead, *vRecAdr, *poNodeData);
     *
     * @param iKey        [in] For the moment 0
     * @param poTreeHead  [in] Tree Header
     * @param vRecAdr     [in] Record vector
     * @param poNodeData  [in] Tree Node Data
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int DSiTreAdrSet ( int                      iKey,
                        sstRec04TreeHeaderCls   *poTreeHead,
                        void                    *vRecAdr,
                        sstRec04TreeNodeCls     *poNodeData);
     //=============================================================================
     /**
     * @brief // Write new record into record memory and update all trees  <BR>
     * iStat = oRecMem.TreWriteNew ( iKey,  *vRecAdr, *dRecNo);
     *
     * @param iKey     [in]  For the moment 0
     * @param vRecAdr  [in]  Adress of new record to be written
     * @param dRecNo   [out] New Record written at number
     *
     * @return Fehlerstatus
     *
     * @retval   =0 = OK
     * @retval   <0 = Unspecified Error
     */
     //-----------------------------------------------------------------------------
     int TreWriteNew ( int              iKey,
                       void            *vRecAdr,
                       dREC04RECNUMTYP *dRecNo);
     //=============================================================================
     /**
     * @brief // Datensatz an absoluter Position schreiben <BR>
     * iStat = DS1_TreShrAbs ( Key, *DsVerw, *DSatz, SNr);
     *
     * @param iKey    [in]  For the moment 0
     * @param vRecAdr [in] record adress
     * @param dRecNo  [in] Write record at position
     *
     * @return Fehlerstatus
     *
     * @retval   =0 = OK
     * @retval   <0 = allgemeiner Fehler
     *
     * @date 07.11.15
     */
     //-----------------------------------------------------------------------------
     int TreWritVector ( int               iKey,
                         void             *vRecAdr,
                         dREC04RECNUMTYP   dRecNo);
     //==============================================================================
     /**
     * @brief // Delete record with value from tree   <BR>
     * iStat = oRecMem.TreDelValue ( iKey, *oTre, *v, *dRecNo);
     *
     * @param iKey         [in] For the moment 0
     * @param oTre         [in] Tree object
     * @param vSearchValue [in] Seach Value
     * @param dRecNo       [out] return deleted record number
     *
     * @return Errorstate
     *
     * @retval   =1: Record with Value found and deleted from tree(s)
     * @retval   =0: Value not found
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreDelValue ( int                   iKey,
                       sstRec04TreeKeyCls   *oTre,
                       void                 *vSearchValue,
                       dREC04RECNUMTYP      *dRecNo);
     //==============================================================================
     /**
     * @brief // Delete record with record number from all trees   <BR>
     * iStat = oRecMem.TreDelNumber ( iKey, *oTreHead, dRecNo);
     *
     * @param iKey         [in] For the moment 0
     * @param dRecNo       [in] record number to delete
     *
     * @return Errorstate
     *
     * @retval   =1: Record with Value found and deleted from tree(s)
     * @retval   =0: Value not found
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreDelNumber ( int                      iKey,
                        dREC04RECNUMTYP          dRecNo);
     //==============================================================================
     /**
     * @brief // Delete record with record number from given tree   <BR>
     * iStat = oRecMem.TreDelIntern ( iKey, *oTreHead, dRecNo);
     *
     * @param iKey         [in] For the moment 0
     * @param oTreHead     [in] Tree object
     * @param dRecNo       [in] record number to delete
     *
     * @return Errorstate
     *
     * @retval   =1: Record with Value found and deleted from tree(s)
     * @retval   =0: Value not found
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreDelIntern ( int                      iKey,
                        sstRec04TreeHeaderCls   *oTreHead,
                        dREC04RECNUMTYP          dRecNo);
     //==============================================================================
     /**
     * @brief // Get Size of user data record <BR>
     * dUserRecSize = oRecMem.GetUserRecordSize();
     *
     * @return User Record size
     */
     // ----------------------------------------------------------------------------
     dREC04RECNUMTYP GetUserRecordSize();
     //==============================================================================
     /**
     * @brief // Log Tree sorting into file <BR>
     * iStat = oRecMem.TreeLog( iKey, oTre, cLogFilNam);
     *
     * @param iKey       [in] For the moment 0
     * @param oTre       [in] Tree for logging
     * @param cLogFilNam [in] Target file name for logging output
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int TreeLog(int                   iKey,
                 sstRec04TreeKeyCls   *oTre,
                 char                 *cLogFilNam);
     //==============================================================================


  private:  // Private functions
     //==============================================================================
     /**
     * @brief Shortstory
     *
     * @param iKey [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
    void inflate(int increase);
    //=============================================================================
    void CalcSetPos ( void   *BasPtr,
                      void  **IdxPtr,
                      long    Offs) const;
    //==============================================================================
    /**
    * @brief Reset User record
    *
    * @param iKey [in]     For the moment 0
    * @param iKey [in out] Adress of user record
    *
    * @return Errorstate
    *
    * @retval   =0: OK
    * @retval   <0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int resetRecord(int iKey, void *vRecAdr);
    //=============================================================================

    // dREC04RECSIZTYP dUsrSize;     /**< Size of each user record */
    dREC04RECNUMTYP dQuantity;     /**< Number of storage spaces */
    dREC04RECNUMTYP dActStored;   /**< Number of stored records */
    unsigned char* ucStorage;       /**< Dynamically allocated array of bytes */
    FILE*          pFilHdl;        /**< File Handle: If not NULL, store in file   */
    bool           bFileNotDelete;  /**< Do File not delete   */
    char cDatnam[dREC04FILNAMMAXLEN]; /**< Filename for storing record data   */
    sstRec04HeaderCls *poHeader;  /**< Intern Header            */
    sstRec04VectSysCls *poVector;  /**< Intern memory space for vector            */
    sstRec04CargoKeyInternCls *poRecMemUsrKey;   /**< Identification Key for Header Cargo */
    sstRec04CargoKeyInternCls *poRecMemSysKey;   /**< Identification Kea for User Data Cargo */
    sstRec04TreeHeaderCls     *poTre;            /**< Array with all tree header data    */
    int           iTriAnz;    /**< Number of all defined trees            */
};
//==============================================================================
/**
* @brief Root or head object with entry infos for linked list
*
* Changed: 20.06.14  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 20.06.14
*/
// ----------------------------------------------------------------------------
class sstRec04LiLstHedCls
{
  public:   // Öffentliche Funktionen
     sstRec04LiLstHedCls();  // Konstruktor
     //==============================================================================
     /**
     * @brief Set Entry 1: Beginn of linked list
     *
     * @param iKey    [in] For the moment 0
     * @param dEntry1 [in] Entry 1
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetEntry1(int iKey,  dREC04RECNUMTYP dEntry1);
     //==============================================================================
     /**
     * @brief Set Entry 2: Exit / End of linked list
     *
     * @param iKey    [in] For the moment 0
     * @param dEntry2 [in] Entry 2
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetEntry2(int iKey,  dREC04RECNUMTYP dEntry2);
     //==============================================================================
     /**
     * @brief Get Entry 1
     *
     * @return Entry1
     */
     // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetEntry1();
      //==============================================================================
      /**
      * @brief Get Entry 2
      *
      * @return Entry 2
      */
      // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetEntry2();
      //==============================================================================
      /**
      * @brief AddElement
      */
      // ----------------------------------------------------------------------------
      void AddElement();
      //==============================================================================
      /**
      * @brief ReduceElement
      */
      // ----------------------------------------------------------------------------
      void ReduceElement();
      //==============================================================================
      /**
      * @brief GetNumListElements
      *
      * @return NumListElements
      */
      // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetNumListElements();
      //==============================================================================
  private:  // Private Funktionen
      dREC04RECNUMTYP chain_loc[2];      /**< Entry and exit in linked list */
      dREC04RECNUMTYP dNumListElements;  /**< Number of List elements */
};
//==============================================================================
/**
* @brief List Node Element class of Linked List
*
* List Element for Linked List
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstRec04LiLstEleCls
{
  public:   // Öffentliche Funktionen
     sstRec04LiLstEleCls();  // Konstruktor
     //==============================================================================
     /**
     * @brief Set Head or master object for linked list
     *
     * @param iKey    [in] For the moment 0
     * @param dMaster [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetMaster(int iKey,  dREC04RECNUMTYP  dMaster);
     //==============================================================================
     /**
     * @brief Set previous element for linked list object
     *
     * @param iKey  [in] For the moment 0
     * @param dPrev [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetPrev(int iKey,  dREC04RECNUMTYP  dPrev);
     //==============================================================================
     /**
     * @brief Set Next element for linked list object
     *
     * @param iKey  [in] For the moment 0
     * @param dNext [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetNext(int iKey,  dREC04RECNUMTYP  dNext);
     //==============================================================================
     /**
     * @brief Set Next element for linked list object
     *
     * @param iKey    [in] For the moment 0
     * @param dTarget [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetTarget(int iKey,  dREC04RECNUMTYP  dTarget);
     //==============================================================================
     /**
     * @brief set all parameter for linked list object
     *
     * iStat = Set( iKey, dMaster, dPrev, dNext);
     *
     * @param iKey    [in] For the moment 0
     * @param dMaster [in] Head or Master object
     * @param dPrev   [in] Previous in linked list
     * @param dNext   [in] Next in linked list
     * @param dTarget [in] Set Link to Target
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Set(int              iKey,
             dREC04RECNUMTYP  dMaster,
             dREC04RECNUMTYP  dPrev,
             dREC04RECNUMTYP  dNext,
             dREC04RECNUMTYP  dTarget);
     //==============================================================================
     /**
     * @brief Get Master
     *
     * @return dMaster
     */
     // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetMaster();
     //==============================================================================
     /**
     * @brief Get Previous
     *
     * @return dPrev
     */
     // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetPrev();
     //==============================================================================
     /**
     * @brief Get Next
     *
     * @return dNext
     */
     // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetNext();
     //==============================================================================
     /**
     * @brief Get Next
     *
     * @return dNext
     */
     // ----------------------------------------------------------------------------
      dREC04RECNUMTYP GetTarget();

  private:  // Private Funktionen
      dREC04RECNUMTYP master;    /**< Master or root object of list */
      dREC04RECNUMTYP ulPrev;    /**< Previous element in list */
      dREC04RECNUMTYP ulNext;    /**< Next element in list */
      dREC04RECNUMTYP ulTarget;  /**< Element in Target list */

};
//==============================================================================
/**
* @brief target element class of linked list
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstRec04LiLstTarCls
{
  public:   // Öffentliche Funktionen
     sstRec04LiLstTarCls();  // Konstruktor
     unsigned long ulNumEle;        /**< Number of linked elements */
  private:  // Private Funktionen
};
//==============================================================================
/**
* @brief Definition Klasse sstRec04LiLstIntCls
*
* Linked List Class for Dss2 Library
*
* Changed: 19.02.10  Re.
*
* @ingroup sstRecord04InternLib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstRec04LiLstIntCls
{
  public:   // Öffentliche Funktionen
     sstRec04LiLstIntCls();  // Konstruktor
     ~sstRec04LiLstIntCls();  // Destruktor

     // ----------------------------------------------------------------------------
     /**
     * @brief Initialize Linked List
     *
     * @param iKey [in] For the moment 0
     * @param Dss1 [in out] Target Dss
     * @param Dss2 [in out] List Element Dss
     * @param Dss3 [in out] Header Dss
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
//     int Define3(int                iKey,
//                    sstRec04InternCls *Dss1,
//                    sstRec04InternCls *Dss2,
//                    sstRec04InternCls *Dss3);
     int Define3(int          iKey,
                    sstRec04Cls *Dss1,
                    sstRec04Cls *Dss2,
                    sstRec04Cls *Dss3);
     // ----------------------------------------------------------------------------
     /**
     * @brief Add list object to header object
     *
     * @param iKey     [in] For the moment 0
     * @param RecNoEle [in] ID of List
     * @param RecNoHed [in] ID of Header
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int List2Header( int          iKey,
                       dREC04RECNUMTYP RecNoEle,
                       dREC04RECNUMTYP RecNoHed);
//                      char         name[],
//                      unsigned int iname);

     // ----------------------------------------------------------------------------
     /**
     * @brief Insert new target object to element list
     *
     * @param iKey     [in] For the moment 0
     * @param RecNoEle [in] ID of list element
     * @param RecNoTar [in] ID of target element
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Target2List( int          iKey,
                       dREC04RECNUMTYP RecNoEle,
                       dREC04RECNUMTYP RecNoTar);

     //==============================================================================
     /**
     * @brief Get Number of uses for target record
     *
     * @param iKey      [in]  For the moment 0
     * @param dRecNoTar [in]  Record number of target
     * @param dNumUse   [out] Number of uses
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetTarNumUse (int              iKey,
                       dREC04RECNUMTYP  dRecNoTar,
                       dREC04RECNUMTYP *dNumUse);
     //==============================================================================
     /**
     * @brief Set Number of uses for target record
     *
     * @param iKey      [in] For the moment 0
     * @param dNumUse   [in] Number of uses
     * @param dRecNoTar [in] Record number of target
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetTarNumUse(int          iKey,
                       dREC04RECNUMTYP dNumUse,
                       dREC04RECNUMTYP dRecNoTar);
     //==============================================================================
     /**
     * @brief Set all attributes for element record
     *
     * iStat = oLinkedList.SetEleAll ( iKey, dRecNoEle, dMaster, dNext, dPrev, dTarget);
     *
     * @param iKey      [in] For the moment 0
     * @param dRecNoEle [in] record number of element
     * @param dMaster   [in] Master of list
     * @param dNext     [in] Next element
     * @param dPrev     [in] Previous element
     * @param dTarget   [in] Previous element
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetEleAll (int          iKey,
                     dREC04RECNUMTYP dRecNoEle,
                     dREC04RECNUMTYP dMaster,
                     dREC04RECNUMTYP dNext,
                     dREC04RECNUMTYP dPrev,
                     dREC04RECNUMTYP dTarget);

     //==============================================================================
     /**
     * @brief Shortstory
     *
     * @param iKey       [in] For the moment 0
     * @param dRecNoEle  [in] For the moment 0
     * @param dMaster    [out] For the moment 0
     * @param dNext      [out] For the moment 0
     * @param dPrev      [out] For the moment 0
     * @param dTarget    [out] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ListNodeGetEleAll (int              iKey,
                    dREC04RECNUMTYP  dRecNoEle,
                    dREC04RECNUMTYP *dMaster,
                    dREC04RECNUMTYP *dNext,
                    dREC04RECNUMTYP *dPrev,
                    dREC04RECNUMTYP *dTarget);
     //==============================================================================
     /**
     * @brief Set all attributes for element record
     *
     * @param iKey       [in] For the moment 0
     * @param dRecNoHed  [in] Master of list
     * @param dEntry1    [in] Start / Begin of linked list
     * @param dEntry2    [in] Exit / End of linked list
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetHedAll (int          iKey,
                     dREC04RECNUMTYP dRecNoHed,
                     dREC04RECNUMTYP dEntry1,
                     dREC04RECNUMTYP dEntry2);
     //==============================================================================
     /**
     * @brief Get Number of list elements for list header
     *
     * @param iKey        [in]  For the moment 0
     * @param dRecNoHed   [in]  Record number of list heaser
     * @param dListLength [out] Number of list elements
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int GetHedListLength (int              iKey,
                           dREC04RECNUMTYP  dRecNoHed,
                           dREC04RECNUMTYP *dListLength);
     //==============================================================================
     /**
     * @brief Shortstory
     *
     * @param iKey      [in] For the moment 0
     * @param dRecNoHed [in] For the moment 0
     * @param dEntry1   [out] For the moment 0
     * @param dEntry2   [out] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int getEntriesInLinkList ( int              iKey,
                                dREC04RECNUMTYP  dRecNoHed,
                                dREC04RECNUMTYP *dEntry1,
                                dREC04RECNUMTYP *dEntry2);
     //==============================================================================
     /**
     * @brief // Extend Linked List at end  <BR>
     * iStat = oLinkList.ExtendAtEnd ( iKey, dRecNoHead, dRecNoEle, dRecNoTarget);
     *
     * @param iKey          [in] For the moment 0
     * @param dRecNoHead    [in] Extend Linked List named by dRecNoHead
     * @param dRecNoEle     [in] Linked List node in insert
     * @param dRecNoTarget  [in] Extend with Target object
     *
     * @return Errorstate
     *
     * @retval   =0: OK
     * @retval   <0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ExtendAtEnd(int             iKey,
                     dREC04RECNUMTYP dRecNoHead,
                     dREC04RECNUMTYP dRecNoEle,
                     dREC04RECNUMTYP dRecNoTarget);
     //==============================================================================

private:  // Private Member
     dREC04RECNUMTYP dLiLstEntry2;  /**< Second entry in linked list */
     dREC04RECNUMTYP dLiLstEntry1;  /**< First Entry in linked list */

     sstRec04CargoKeyInternCls *poLstTarKey;  /**< Cargo Linked List target LLTA   */
     sstRec04CargoKeyInternCls *poLstEleKey;  /**< Cargo Linked List element LLEL  */
     sstRec04CargoKeyInternCls *poLstHedKey;  /**< Cargo Linked List Head LLHE     */

     sstRec04InternCls *poRecMemHed; /**<  RecMem for Target elements      */
     sstRec04InternCls *poRecMemEle; /**<  RecMem for Target list elements */
     sstRec04InternCls *poRecMemTar; /**<  RecMem for Header elements      */
};
//==============================================================================
// iStat = Test_VectorSys_Stack ( iKey);
int Test_VectorSys_Stack (int iKey);

// iStat = Test_VectorSys_Heap ( iKey);
int Test_VectorSys_Heap (int iKey);

// Test Compare functions
int Test_CompareFunctions (int iKey);

//==============================================================================

#endif

// --------------------------------------------------------------- File End ----

