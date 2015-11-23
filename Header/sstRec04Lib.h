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
// sstRec04Lib.h   17.11.15  Re.   16.10.15  Re.
//
// Datastructures and Prototypes for system "sstRec04Lib"
//

#ifndef   _SST_REC04_LIB_HEADER
#define   _SST_REC04_LIB_HEADER

/**
 * @defgroup sstRecord04Lib sstRecord04Lib: cpp sst record library (Version 4)
 *
 * cpp sst record library <BR>
 *
 */

// Defines ---------------------------------------------------------------------

/**
 * @brief Record Number Type
 * @ingroup sstRecord04Lib
 */
// typedef int  dREC04RECNUMTYP;    /**< Record Number Type    */
// typedef unsigned int  dREC04RECNUMTYP;    /**< Record Number Type    */
// typedef long  dREC04RECNUMTYP;    /**< Record Number Type    */
typedef unsigned long  dREC04RECNUMTYP;    /**< Record Number Type: Int, Unsigned, Long, Unsigned Long   */

/**
 * @brief Record Size Type
 * @ingroup sstRecord04Lib
 */
// typedef int  dREC04RECNUMTYP;    /**< Record Number Type    */
// typedef unsigned int  dREC04RECNUMTYP;    /**< Record Number Type    */
// typedef long  dREC04RECNUMTYP;    /**< Record Number Type    */
typedef unsigned long  dREC04RECSIZTYP;    /**< Record Size Type: Int, Unsigned, Long, Unsigned Long  */


// forward declaration ---------------------------------------------------------

class sstRec04InternCls;
class sstRec04CargoKeyInternCls;
class sstRec04LiLstIntCls;

//------------------------------------------------------------------------------


//==============================================================================
/**
* @brief Definition Enum CompTyp_enum
*
* All possible compare types
*
* Changed: 30.10.15  Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 30.10.15
*/
// ----------------------------------------------------------------------------
enum _sstRec04CompTyp_enum
{ sstRecTyp_No,     /**< No Sorttyp              */
  sstRecTyp_I2,     /**< Signed Short Integer    */
  sstRecTyp_I4,     /**< Signed Long Integer     */
  sstRecTyp_UI,     /**< Unsigned Short Integer  */
  sstRecTyp_UL,     /**< Unsigned Long Integer   */
  sstRecTyp_R4,     /**< Real                    */
  sstRecTyp_D8,     /**< Double                  */
  sstRecTyp_CC      /**< Character String        */
     };
typedef enum _sstRec04CompTyp_enum sstRec04CompTyp_enum;
//==============================================================================
/**
* @brief Identification Key for cargo packets
*
* Changed: 16.10.15  Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 16.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04CargoKeyCls
{
  public:   // Public functions
     sstRec04CargoKeyCls();  // Constructor
    ~sstRec04CargoKeyCls();  // Destructor

     sstRec04CargoKeyInternCls *poCargoKeyIntern;   /**< Pointer to intern object */

};
//==============================================================================
/**
* @brief Identification key of tree object
*
* More Comment
*
* Changed: 27.10.15  Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 27.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04TreeKeyCls
{
public:
  sstRec04TreeKeyCls();
  // ~sstRec04TreeKeyCls();
  int iTriNo;  /**< Internal Number of Tree-Object */
};
//==============================================================================
/**
* @brief sst Record Memory Vers. 4
*
* record storage <BR>
*
* Changed: 04.08.15  Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 09.07.15
*/
// ----------------------------------------------------------------------------
class sstRec04Cls {
public:
    //==============================================================================
    /**
    * @brief sstRec constructor with size of one record
    *
    * @param Size [in] Size of one record
    */
    // ----------------------------------------------------------------------------
  sstRec04Cls(dREC04RECSIZTYP Size);
  ~sstRec04Cls();
  //==============================================================================
  /**
  * @brief Get number of stored records
  *
  * @return number of elements in stash memory
  */
  // ----------------------------------------------------------------------------
  dREC04RECNUMTYP count();
  //==============================================================================
  /**
  * @brief // Write new record into sstRec memory <BR>
  * iStat = oRecMem.WritNew(iKey, *vRecAdr, *dPosition);
  *
  * @param iKey      [in]  For the moment 0
  * @param vRecAdr   [in]  adress of Record to store
  * @param dPosition [out] New Positon of new Record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int WritNew(int iKey, void* vRecAdr, dREC04RECNUMTYP *dPosition);
  //==============================================================================
  /**
  * @brief // Write Record at postion in sstRec Memory <BR>
  * iStat = oRecMem.Writ( iKey, *vRecAdr, dPosition);
  *
  * @param iKey      [in] For the moment 0
  * @param vRecAdr   [in] Adress of record
  * @param dPosition [in] target position to write record
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Wrong Record positon
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Writ(int iKey, void* vRecAdr, dREC04RECNUMTYP dPosition);
  //==============================================================================
  /**
  * @brief // Read record from sstRec memory with Record number <BR>
  * iStat = oRecMem.Read( iKey, dPosition, *vRecAdr);
  *
  * @param iKey      [in]  For the moment 0
  * @param dPosition [in]  record number to read
  * @param vRecAdr   [out] read Record to record adress
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Wrong Record positon
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int Read(int iKey, dREC04RECNUMTYP dPosition, void *vRecAdr);
  //==============================================================================
  /**
  * @brief open file with name or create new file
  *
  * @param iKey    [in]  For the moment 0
  * @param cSysNam [in]  File Name
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: File already open
  * @retval   = -3: Filename empty
  * @retval   = -4: sstRec not empty
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int OpenFile(int   iKey,
               char *cSysNam);
  //==============================================================================
  /**
  * @brief open new file
  *
  * @param iKey    [in]  For the moment 0
  * @param cSysNam [in]  File Name
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: File already open
  * @retval   = -3: Filename empty
  * @retval   = -4: sstRec not empty
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int NewFile(int   iKey,
              char *cSysNam);
  //==============================================================================
  /**
  * @brief Set file data store
  *
  * @param iKey  [in]  For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int SetStoreFile(int iKey);
  //=============================================================================
  /**
  * @brief // Add cargo system to sstRec memory and get new identification key <BR>
  * iStat = oRecMem.AddCargoSys( iKey, uiSize, *cCargoNam, *oCargoKey);
  *
  * @param iKey      [in]  For the moment 0
  * @param uiSize    [in]  Size of cargo record
  * @param cCargoNam [in]  Name of cargo system (3 Letters)
  * @param oCargoKey [out] key of new cargo object
  *
  * @return Errorstate
  *
  * @retval   =   0: OK
  * @retval   =  -1: Wrong Key
  * @retval   =  -2: Cargo Packet must not be empty
  * @retval   =  -3: Cargo Name has to be length 3
  * @retval   =  -4: Cargo Key should be empty
  * @retval   =  -5: Cargo Name should be unique
  * @retval   = -10: sstRecMem is not empty
  * @retval   <   0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int AddCargoSys( int                  iKey,
                   unsigned int         uiSize,
                   char                *cCargoNam,
                   sstRec04CargoKeyCls *oCargoKey);
  //=============================================================================
  /**
  * @brief // write cargo packet to vector Memory <BR>
  * iStat = oRecMem.WrtCargo ( iKey, *oCargoKey, *vCargoAdr);
  *
  * @param iKey       [in]  For the moment 0
  * @param oCargoKey  [in]  identification key of cargo packet
  * @param vCargoAdr  [in]  adress of cargo packet
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Cargo key not OK for RecMem object
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int WrtCargo ( int                  iKey,
                 sstRec04CargoKeyCls *oCargoKey,
                 void                *vCargoAdr);
  //=============================================================================
  /**
  * @brief // Read cargo packet from vector memory  <BR>
  * iStat = oRecMem.RedCargo ( iKey, *oCargoKey, *vCargoAdr);
  *
  * @param iKey       [in]   For the moment 0
  * @param oCargoKey  [in]   identification key of cargo packet
  * @param vCargoAdr  [out]  Adress of cargo packet
  *
  * @return Errorstate
  *
  * @retval   =  0: OK
  * @retval   = -1: Wrong Key
  * @retval   = -2: Cargo key not OK for RecMem object
  * @retval   <  0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int RedCargo ( int                  iKey,
                 sstRec04CargoKeyCls *oCargoKey,
                 void                *vCargoAdr);
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
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
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
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
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
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
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
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
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
  * @retval   = true:  Record is deleted
  * @retval   = false: Record is undeleted
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
  * @retval   = true : Record is marked
  * @retval   = false: Record is unmarked
  */
  // ----------------------------------------------------------------------------
  bool RecGetMarkStatus( int               iKey,
                         dREC04RECNUMTYP   dRecNo);
  //=============================================================================
  /**
  * @brief // Init new Tree sorting object for RecMem object  <BR>
  * iStat = oRecMem.TreIni ( iKey, *vDsAdr, *vCompAdr, iCompSiz, eCompTyp, *poTre);
  *
  * @param iKey     [in]  For the moment 0
  * @param vDsAdr   [in]  Adress of record
  * @param vCompAdr [in]  Adress of compare value in record
  * @param iCompSiz [in]  Size of compare value
  * @param eCompTyp [in]  Type of compare value
  * @param poTre    [out] New Tree system
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreIni ( int                iKey,
               void              *vDsAdr,
               void              *vCompAdr,
               int                iCompSiz,
               sstRec04CompTyp_enum   eCompTyp,
               sstRec04TreeKeyCls     *poTre);
  //=============================================================================
  /**
  * @brief // Rebuild Tree system  <BR>
  * iStat = oRecMem.TreBld ( iKey, *poTre);
  *
  * @param iKey  [in]     For the moment 0
  * @param poTre [in out] Tree to rebuild
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreBld ( int                   iKey,
               sstRec04TreeKeyCls   *poTre);
  //=============================================================================
  /**
  * @brief // Find record with exact search value  <BR>
  * iStat = oRecMem.TreSeaEQ  ( iKey, poTreKey, *vSearchVal, *dRecNo);
  *
  * @param iKey       [in]  at the moment 0
  * @param poTreKey   [in]  tree key object
  * @param vSearchVal [in]  search value
  * @param dRecNo     [out] Value found at record number
  *
  * @return errorstate
  *
  * @retval   =0 Nothing found
  * @retval   =1 Exact value found at dRecNo
  * @retval   <0 Unspecified Error
  */
  //-----------------------------------------------------------------------------
  int TreSeaEQ  ( int                   iKey,
                  sstRec04TreeKeyCls   *poTreKey,
                  void                 *vSearchVal,
                  dREC04RECNUMTYP      *dRecNo);
  //=============================================================================
  /**
  * @brief Get next greater or equal <BR>
  * iStat = iRecMem.TreReadNxtGE ( iKey, *poTre, *vRecAdr, *dRecNo);
  *
  * @param iKey     [in]     For the moment 0
  * @param poTre    [in]     Tree key
  * @param vRecAdr  [in out] return record at given adress
  * @param dRecNo   [in out] Return next greater or equal
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreReadNxtGE (int               iKey,
                    sstRec04TreeKeyCls    *poTre,
                    void             *vRecAdr,
                    dREC04RECNUMTYP  *dRecNo);
  //=============================================================================
  /**
  * @brief // Return first record number <BR>
  * iStat = oRecMem.TreSeaFrst ( iKey, *poTre, *dRecNo);
  *
  * @param iKey    [in]     For the moment 0
  * @param poTre   [in out] Tree system
  * @param dRecNo  [out]    Return record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreSeaFrst ( int               iKey,
                   sstRec04TreeKeyCls    *poTre,
                   dREC04RECNUMTYP  *dRecNo);

  //=============================================================================
  /**
  * @brief // Seach next greater / equal  <BR>
  * iStat = oRecMem.TreSeaNxtGE ( iKey, *poTre, dRecNo1, *dRecNo2);
  *
  * @param iKey    [in]     For the moment 0
  * @param poTre   [in out] Tree system
  * @param dRecNo1 [in]     actual record number
  * @param dRecNo2 [out]    next record number
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreSeaNxtGE ( int                iKey,
                    sstRec04TreeKeyCls     *poTre,
                    dREC04RECNUMTYP    dRecNo1,
                    dREC04RECNUMTYP   *dRecNo2);
  //=============================================================================
  /**
  * @brief // Write new record into record memory and update all trees  <BR>
  * iStat = oRecMem.TreWriteNew ( iKey,  *vRecAdr, *dRecNo);
  *
  * @param iKey     [in]  Vorerst immer 0
  * @param vRecAdr  [in]  Adresse des Datensatzes
  * @param dRecNo   [out] new record written at number
  *
  * @return Fehlerstatus
  *
  * @retval   =0 = OK
  * @retval   <0 = allgemeiner Fehler
  */
  //-----------------------------------------------------------------------------
  int TreWriteNew ( int              iKey,
                    void            *vRecAdr,
                    dREC04RECNUMTYP *dRecNo);
  //=============================================================================
  /**
  * @brief // Write record at position and update tree(s) <BR>
  * iStat = oRecMem.TreWritAtPos ( iKey, vRecAdr, dRecNo);
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
  int TreWritAtPos ( int               iKey,
                     void             *vRecAdr,
                     dREC04RECNUMTYP   dRecNo);
  //==============================================================================
  /**
  * @brief // Delete next record with given value from tree   <BR>
  * iStat = oRecMem.TreDelValue ( iKey, *oTreKey, *vSearchValue, *dRecNo);
  *
  * @param iKey         [in] For the moment 0
  * @param oTreKey      [in] Tree object
  * @param vSearchValue [in] Seach Value
  * @param dRecNo       [out] Return deleted record number
  *
  * @return Errorstate
  *
  * @retval   = 1: Record with value found and deleted from tree(s)
  * @retval   = 0: Value not found in RecMem
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreDelValue ( int                   iKey,
                    sstRec04TreeKeyCls   *oTreKey,
                    void                 *vSearchValue,
                    dREC04RECNUMTYP      *dRecNo);
  //==============================================================================
  /**
  * @brief // Delete record with record number from all defined trees   <BR>
  * iStat = oRecMem.TreDelNumber ( iKey, dRecNo);
  *
  * @param iKey         [in] For the moment 0
  * @param dRecNo       [in] record number to delete
  *
  * @return Errorstate
  *
  * @retval   = 1: Record with Value found and deleted from tree(s)
  * @retval   = 0: Value not found
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
  int TreDelNumber ( int                      iKey,
                     dREC04RECNUMTYP          dRecNo);
  //==============================================================================
  /**
  * @brief Get Adress of intern object
  *
  * @retval   Return adress of intern object
  */
  // ----------------------------------------------------------------------------
  sstRec04InternCls* GetInternObjAdr();
  //=============================================================================

private:
  sstRec04InternCls *poRec01Intern;   /**< Pointer to intern object */

};

//==============================================================================
/**
* @brief Small test record class
*
* Changed: 16.10.15 Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 16.10
*/
// ----------------------------------------------------------------------------
class sstRec04TestRec1Cls
{
  public:   // Public functions
     sstRec04TestRec1Cls();  // Constructor
     //==============================================================================
     /**
     * @brief // Set all Values for test record 1 <BR>
     * oTestRecord1.SetAllValues(iTstValue,cTstValue)
     *
     * @param iTstVal [in] Set Integer Test Value
     * @param cTstVal [in] Set Character Test Value
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetAllValues(int iTstVal, char *cTstVal);

     int iValue;        /**< Test Integer Value */
     char cVal[5];     /**< Test Character Value */

};
//==============================================================================
/**
* @brief Full test record class
*
* Changed: 16.10.15 Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 16.10.15
*/
// ----------------------------------------------------------------------------
class sstRec04TestRec2Cls
{
  public:   // Public functions
    sstRec04TestRec2Cls();  // Constructor
    int    iValue;          /**< Test Integer Value */
    unsigned int uiValue;   /**< Test Unsigned Value */
    double dValue;          /**< Test Double Value */
    char cVal[10];         /**< Test Character Value */
};
//==============================================================================
/**
* @brief Linked List object for 3 MemRec objects
*
* Changed: 19.11.15  Re.
*
* @ingroup sstRecord04Lib
*
* @author Re.
*
* @date 19.11.15
*/
// ----------------------------------------------------------------------------
class sstRec04LiLstCls
{
  public:   // Öffentliche Funktionen
     sstRec04LiLstCls();  // Konstruktor
     ~sstRec04LiLstCls();  // Destruktor

     // ----------------------------------------------------------------------------
     /**
     * @brief // Initialize Linked List with Header, List element and target RecMem objects  <BR>
     * iStat = oLiList.Define3( iKey, *oRecMem1Hed, *oRecMem2Ele, *oRecMem3Tar);
     *
     * @param iKey [in] For the moment 0
     * @param oRecMem1Hed [in out] Store linked list header data in RecMem1
     * @param oRecMem2Ele [in out] Store linked list list element data in RecMem2
     * @param oRecMem3Tar [in out] Store linked list target data in RecMem3
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int Define3(int          iKey,
                 sstRec04Cls *oRecMem1Hed,
                 sstRec04Cls *oRecMem2Ele,
                 sstRec04Cls *oRecMem3Tar);
     //==============================================================================
     /**
     * @brief // Get entry Data for Linked list object  <BR>
     *  oLinkList.getEntriesInLinkList(int iKey, dRecNoHed, *dEntry1, *dEntry2);
     *
     * @param iKey      [in] For the moment 0
     * @param dRecNoHed [in] Number of Linked List Header object
     * @param dEntry1   [out] Return entry 1 in LinkList
     * @param dEntry2   [out] Return entry 2 in LinkList
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int getEntriesInLinkList(int              iKey,
                              dREC04RECNUMTYP  dRecNoHed,
                              dREC04RECNUMTYP *dEntry1,
                              dREC04RECNUMTYP *dEntry2);
     //==============================================================================
     /**
     * @brief // Get all data from element node  <BR>
     * iStat = oLinkList.ListNodeGetEleAll ( iKey, dRecNoEle, *dMaster, *dNext, *dPrev, *dTarget);
     *
     * @param iKey       [in] For the moment 0
     * @param dRecNoEle  [in] node number in list
     * @param dMaster    [out] Master object of linked list
     * @param dNext      [out] Next node in linked list
     * @param dPrev      [out] Previous node in linked list
     * @param dTarget    [out] Target object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
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
     * @brief // Extend Linked List at end  <BR>
     * iStat = oLinkList.ExtendAtEnd ( iKey, dRecNoHead, dRecNoEle, dRecNoTarget);
     *
     * @param iKey          [in] For the moment 0
     * @param dRecNoHead    [in] Extend Linked List named by dRecNoHead
     * @param dRecNoEle     [in] Extend Linked List named by dRecNoHead
     * @param dRecNoTarget  [in] Extend with Target object
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int ExtendAtEnd(int             iKey,
                     dREC04RECNUMTYP dRecNoHead,
                     dREC04RECNUMTYP dRecNoEle,
                     dREC04RECNUMTYP dRecNoTarget);
     //==============================================================================
private:  // Private Funktionen
     sstRec04LiLstIntCls *poRec04LiLstInt;   /**< Pointer to intern object */

};
//==============================================================================

// Do some intern Tests
int sstRec04_DoSomeInternTests (int iKey);

#endif // SST_REC01_LIB
