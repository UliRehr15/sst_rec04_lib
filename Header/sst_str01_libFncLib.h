//  sst_str01_libFncLib.h   21.03.18  Re.   21.03.18  Re.
//
//  Definitions of class "sst_str01_libFnc"
//
  
#ifndef   _SST_sst_str01_lib_Fnc_HEADER
#define   _SST_sst_str01_lib_Fnc_HEADER

#include <string>
#include "sstStr01Lib.h"
#include "sstMisc01Lib.h"
#include "sstRec04Lib.h"
  
/**
 * @defgroup sst_str01_libLib sst_str01_libLib
 *
 * Description: sst_str01_libLib
 *
 */
 
//==============================================================================
/**
* @brief Fnc Class sst_str01_libFncBaseCls
*
* More Comment
*
* Used Type Definitions
* sstRec04Cls *poRecTab;;0;0;;;sst Record Table
*
* Changed:   Re.
*
* @ingroup sst_str01_libLib
*
* @author Re.
*
* @date 
*/
// ----------------------------------------------------------------------------
class sst_str01_libFncBaseCls
{
  public:  // Public functions
    //==============================================================================
    /**
    * @brief // Constructor sst_str01_libFncBaseCls <BR>
    */
    // -----------------------------------------------------------------------------
    sst_str01_libFncBaseCls();// Constructor
     sstRec04Cls *poRecTab;  /**< sst Record Table */
  private:
};
 
//==============================================================================
/**
* @brief Fnc Class sst_str01_libFncTst1ClsCls
*
* More Comment
*
* Changed:   Re.
*
* @ingroup sst_str01_libLib
*
* @author Re.
*
* @date 
*/
// ----------------------------------------------------------------------------
class sst_str01_libFncTst1ClsCls : public sst_str01_libFncBaseCls
{
  public:  // Public functions
    //==============================================================================
    /**
    * @brief // Constructor sst_str01_libFncTst1ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    sst_str01_libFncTst1ClsCls();// Constructor
    //==============================================================================
    /**
    * @brief // Destructor ~sst_str01_libFncTst1ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    ~sst_str01_libFncTst1ClsCls();// Destructor
    //==============================================================================
    /**
    * @brief // Load all records from csv file into datatable LoadTabFromCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int LoadTabFromCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Load all records from csv file into datatable
    //==============================================================================
    /**
    * @brief // Save all records from datatable into Csv file SaveTabToCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int SaveTabToCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Save all records from datatable into Csv file
    //==============================================================================
    /**
    * @brief // Count all records in table Count <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP Count();// Count all records in table
    //==============================================================================
    /**
    * @brief // Read data record from table with record number Read <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read data record from table with record number
    //==============================================================================
    /**
    * @brief // Write data record to table with record number or new with numer = 0 Write <BR>
    * @param iKey
    * @param *dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Write(int iKey, dREC04RECNUMTYP *dRecNo, void *vRecAdr);// Write data record to table with record number or new with numer = 0
  private:
};
 
//==============================================================================
/**
* @brief Fnc Class sst_str01_libFncTst2ClsCls
*
* More Comment
*
* Changed:   Re.
*
* @ingroup sst_str01_libLib
*
* @author Re.
*
* @date 
*/
// ----------------------------------------------------------------------------
class sst_str01_libFncTst2ClsCls : public sst_str01_libFncBaseCls
{
  public:  // Public functions
    //==============================================================================
    /**
    * @brief // Constructor sst_str01_libFncTst2ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    sst_str01_libFncTst2ClsCls();// Constructor
    //==============================================================================
    /**
    * @brief // Destructor ~sst_str01_libFncTst2ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    ~sst_str01_libFncTst2ClsCls();// Destructor
    //==============================================================================
    /**
    * @brief // Load all records from csv file into datatable LoadTabFromCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int LoadTabFromCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Load all records from csv file into datatable
    //==============================================================================
    /**
    * @brief // Save all records from datatable into Csv file SaveTabToCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int SaveTabToCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Save all records from datatable into Csv file
    //==============================================================================
    /**
    * @brief // Count all records in table Count <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP Count();// Count all records in table
    //==============================================================================
    /**
    * @brief // Read data record from table with record number Read <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read data record from table with record number
    //==============================================================================
    /**
    * @brief // Write data record to table with record number or new with numer = 0 Write <BR>
    * @param iKey
    * @param *dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Write(int iKey, dREC04RECNUMTYP *dRecNo, void *vRecAdr);// Write data record to table with record number or new with numer = 0
  private:
};
 
//==============================================================================
/**
* @brief Fnc Class sst_str01_libFncTst3ClsCls
*
* More Comment
*
* Changed:   Re.
*
* @ingroup sst_str01_libLib
*
* @author Re.
*
* @date 
*/
// ----------------------------------------------------------------------------
class sst_str01_libFncTst3ClsCls : public sst_str01_libFncBaseCls
{
  public:  // Public functions
    //==============================================================================
    /**
    * @brief // Constructor sst_str01_libFncTst3ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    sst_str01_libFncTst3ClsCls();// Constructor
    //==============================================================================
    /**
    * @brief // Destructor ~sst_str01_libFncTst3ClsCls <BR>
    */
    // -----------------------------------------------------------------------------
    ~sst_str01_libFncTst3ClsCls();// Destructor
    //==============================================================================
    /**
    * @brief // Load all records from csv file into datatable LoadTabFromCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int LoadTabFromCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Load all records from csv file into datatable
    //==============================================================================
    /**
    * @brief // Save all records from datatable into Csv file SaveTabToCsv <BR>
    * @param iKey
    * @param std::string
    * @param *sErrTxt
    */
    // -----------------------------------------------------------------------------
    int SaveTabToCsv(int iKey, const std::string oCsvFilNam, std::string *sErrTxt);// Save all records from datatable into Csv file
    //==============================================================================
    /**
    * @brief // Count all records in table Count <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP Count();// Count all records in table
    //==============================================================================
    /**
    * @brief // Read data record from table with record number Read <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Read(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read data record from table with record number
    //==============================================================================
    /**
    * @brief // Write data record to table with record number or new with numer = 0 Write <BR>
    * @param iKey
    * @param *dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int Write(int iKey, dREC04RECNUMTYP *dRecNo, void *vRecAdr);// Write data record to table with record number or new with numer = 0
  private:
};
 
//==============================================================================
/**
* @brief Fnc Class sst_str01_libFncTest 2 ClassCls
*
* More Comment
*
* Used Type Definitions
* sst_str01_lib;Database;sst_str01_libFncTst1ClsCls *poT;;0;0;sst Str01_Lib;Test 1 Class;oTabTst1Cls
* sst_str01_lib;Database;sst_str01_libFncTst2ClsCls *poT;;0;0;sst Str01_Lib;Test 2 Class;oTabTst2Cls
* sst_str01_lib;Database;sst_str01_libFncTst3ClsCls *poT;;0;0;sst Str01_Lib;Test 3 Class;oTabTst3Cls
* sst_str01_lib;;sst_str01_libFncTst3ClsCls oTab;;0;0;;Database class for type records;
*
* Changed: 21.03.18  Re.
*
* @ingroup sst_str01_libLib
*
* @author Re.
*
* @date 21.03.18
*/
// ----------------------------------------------------------------------------
class sst_str01_libFncDatabaseCls
{
  public:  // Public functions
    //==============================================================================
    /**
    * @brief // Constructor sst_str01_libFncDatabaseCls <BR>
    */
    // -----------------------------------------------------------------------------
    sst_str01_libFncDatabaseCls();// Constructor
    //==============================================================================
    /**
    * @brief // Destructor ~sst_str01_libFncDatabaseCls <BR>
    */
    // -----------------------------------------------------------------------------
    ~sst_str01_libFncDatabaseCls();// Destructor
    //==============================================================================
    /**
    * @brief // Read Record from Db Table ReadDbTst1Cls <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int ReadDbTst1Cls(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read Record from Db Table
    //==============================================================================
    /**
    * @brief // Write Record to Db Tab WriteDbTst1Cls <BR>
    * @param iKey
    * @param *vRecAdr
    * @param *pdRecNo
    */
    // -----------------------------------------------------------------------------
    int WriteDbTst1Cls(int iKey, void *vRecAdr, dREC04RECNUMTYP *pdRecNo);// Write Record to Db Tab
    //==============================================================================
    /**
    * @brief // Count Records from Db Tab CountDbTst1Cls <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP CountDbTst1Cls();// Count Records from Db Tab
    //==============================================================================
    /**
    * @brief // Read Record from Db Table ReadDbTst2Cls <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int ReadDbTst2Cls(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read Record from Db Table
    //==============================================================================
    /**
    * @brief // Write Record to Db Tab WriteDbTst2Cls <BR>
    * @param iKey
    * @param *vRecAdr
    * @param *pdRecNo
    */
    // -----------------------------------------------------------------------------
    int WriteDbTst2Cls(int iKey, void *vRecAdr, dREC04RECNUMTYP *pdRecNo);// Write Record to Db Tab
    //==============================================================================
    /**
    * @brief // Count Records from Db Tab CountDbTst2Cls <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP CountDbTst2Cls();// Count Records from Db Tab
    //==============================================================================
    /**
    * @brief // Read Record from Db Table ReadDbTst3Cls <BR>
    * @param iKey
    * @param dRecNo
    * @param *vRecAdr
    */
    // -----------------------------------------------------------------------------
    int ReadDbTst3Cls(int iKey, dREC04RECNUMTYP dRecNo, void *vRecAdr);// Read Record from Db Table
    //==============================================================================
    /**
    * @brief // Write Record to Db Tab WriteDbTst3Cls <BR>
    * @param iKey
    * @param *vRecAdr
    * @param *pdRecNo
    */
    // -----------------------------------------------------------------------------
    int WriteDbTst3Cls(int iKey, void *vRecAdr, dREC04RECNUMTYP *pdRecNo);// Write Record to Db Tab
    //==============================================================================
    /**
    * @brief // Count Records from Db Tab CountDbTst3Cls <BR>
    */
    // -----------------------------------------------------------------------------
    dREC04RECNUMTYP CountDbTst3Cls();// Count Records from Db Tab
    //==============================================================================
    /**
    * @brief // Read Database from Csv Files LoadFromCsvFiles <BR>
    * @param *poPrt
    * @param std::string
    */
    // -----------------------------------------------------------------------------
    int LoadFromCsvFiles(sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam);// Read Database from Csv Files
    //==============================================================================
    /**
    * @brief // Write Database to Csv Files SaveToCsvFiles <BR>
    * @param *poPrt
    * @param std::string
    */
    // -----------------------------------------------------------------------------
    int SaveToCsvFiles(sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam);// Write Database to Csv Files
    //==============================================================================
    /**
    * @brief // Read Database from format main file LoadAllFromMainFile <BR>
    * @param *poPrt
    * @param std::string
    */
    // -----------------------------------------------------------------------------
    int LoadAllFromMainFile(sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam);// Read Database from format main file
    //==============================================================================
    /**
    * @brief // Write Database to format main file SaveAllToMainFile <BR>
    * @param *poPrt
    * @param std::string
    */
    // -----------------------------------------------------------------------------
    int SaveAllToMainFile(sstMisc01PrtFilCls *poPrt, const std::string oPtsFilNam);// Write Database to format main file
     sst_str01_libFncTst1ClsCls *poT1;  /**< oTabTst1Cls */
     sst_str01_libFncTst2ClsCls *poT2;  /**< oTabTst2Cls */
     sst_str01_libFncTst3ClsCls *poT3;  /**< oTabTst3Cls */
     sst_str01_libFncTst3ClsCls oTab;
  private:
};
 
#endif
//
// --------------------------------------------------------------- File End ----
