# sst_rec04_lib

sstRec04Lib - Library for working with records

This lib based on idea "STASH" from bruce eckels book "thinking in c++".

I take this idea as base for small record management system.

This Library is created with QtCreator 4.5.2 and gcc 7.3.0.

Structure of coding projects should be:

.. [libs] <BR>
   [sstMath01Lib] <BR>
   [sstStr01Lib] <BR>
   [sstMisc01Lib] <BR>
   [sstRec04Lib] <BR>
   [Doxygen_Output] <BR>

August 2016, Hanover, Germany, Uli Rehr

Versions <BR>
20151117: 4.0 Fork from sstRec03 <BR>
20151123: 4.1 Add doubly linked list with 3 RemMem objects (Head, List Element, Target) <BR>
20151219: 4.2 Small corrections. Test linked list functions while dxf analyzing. <BR>
20151220: 4.3 Small corrections. More comments for dxf analyzing. <BR>
20151225: 4.4 Extend dxf analyzing: count letters, calculate row length. <BR>
20160212: 4.5 Error in Heap Management corrected. <BR>
20160219: 4.6 Test functions extended. sst_rec04_lib now based on sst_str01_lib and sst_misc01_lib. <BR>
20160311: Vers. 4.7: New Tree Log function, patched error in tree reading / writing.  <BR>
20160428: Vers. 4.8: Doxygen commends extented.  <BR>
20160807: Vers. 4.9: Corrections working with test records 1 and 2.  <BR>
20170217: Vers. 4.10: New class function "Search next record with equal value in sort tree".  <BR>
20170811: Vers. 4.11: Small corrections in testing. <BR>
20180126: Vers. 4.12: Fix problem in reading TestRec Data. <BR>
20180502: Vers. 4.13: Small corrections for sst_str01_lib Version 1.25. <BR>
20180611: Vers. 4.14: Fix problem in tree traversing. <BR>
20180914: Vers. 4.15: Update to QtCreator 4.5.2 and gcc 7.3.0. <BR>
20181101: Vers. 4.16: More Tests for Test Record 1 and 2. <BR>
20190125: Vers. 4.17: Small Changes in working with TestRec objects. <BR>
20190222: Vers. 4.18: Repeat call of TreeBuild should be possible now. <BR>
20200724: Vers. 4.19: Set pointer to NULL after -delete- for class sstRec04InternCls. <BR>
20201220: Vers. 4.20: Fixed some Doxygen warnings. <BR>
