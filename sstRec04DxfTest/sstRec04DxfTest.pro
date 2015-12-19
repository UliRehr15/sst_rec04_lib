TEMPLATE	  = app
CONFIG	 	 += warn_on
CONFIG       -= qt
CONFIG       -= windows

# CONFIG       -= debug  # RELEASE ist aktiv
CONFIG       -= release  # DEBUG ist aktiv

INCLUDEPATH += ../../str_lib/Header
INCLUDEPATH += ../../sst_misc01_lib/Header
INCLUDEPATH += ../../sst_rec04_lib/Header

debug{
  LIBS        += ../../libs/libsst_rec04_lib_d.a
  LIBS        += ../../libs/libsst_misc01_lib_d.a
  LIBS        += ../../libs/libsst_str01_lib_d.a
}
release{
  
  win32-g++:QMAKE_LFLAGS += -static
  win32-g++:QMAKE_LFLAGS -= -mthreads
  win32-g++:QMAKE_LFLAGS_EXCEPTIONS_ON -= -mthreads
  win32-g++:QMAKE_CXXFLAGS_EXCEPTIONS_ON -= -mthreads
  
  
  LIBS        += ../../libs/libsst_rec04_lib_r.a
  LIBS        += ../../libs/libsst_misc01_lib_r.a
  # LIBS        += ../../libs/libsst_str01_lib_r.a
}

HEADERS    += \
    sstRec04DxfTest.h

SOURCES    += \
    sstRec04DxfTest.cpp

TARGET	  	= sstRec04DxfTest
# copy to deployment directory
# DESTDIR     = ../../../local_deploy

