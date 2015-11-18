TEMPLATE	= lib
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows

# CONFIG    -= debug  # RELEASE is active
CONFIG    -= release  # DEBUG is active

CONFIG    += staticlib

INCLUDEPATH = ./Header

HEADERS		+=  ./Header/sstRec04Lib.h
HEADERS		+= sstRec04LibInt.h

SOURCES		+=  sstRec04.cpp \
    sstRec04TestIntern.cpp \
    sstRec04TestRec.cpp \
    sstRec04Header.cpp \
    sstRec04CargoMem.cpp \
    sstRec04CompValue.cpp \
    sstRec04Tree.cpp \
    sstRec04TreeKeyIntern.cpp \
    sstRec04TreeKey.cpp
    #sstRec02Cargo.cpp
SOURCES		+=  sstRec04CargoKey.cpp
SOURCES		+=  sstRec04CargoKeyInt.cpp
SOURCES		+=  sstRec04Int.cpp
SOURCES		+=  sstRec04Vector.cpp

OTHER_FILES += README.md

debug{
  TARGET		= sst_rec04_lib_d
}
release{
  TARGET		= sst_rec04_lib_r
}

DESTDIR     = ../libs

