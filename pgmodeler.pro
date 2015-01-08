############################################################
# XML / PostgreSQL variables configuration                 #
#                                                          #
# PGSQL_LIB -> Full path to libpq.(so | dll | dylib)       #
# PGSQL_INC -> Root path where PgSQL includes can be found #
#                                                          #
# XML_LIB   -> Full path to libxml2.(so | dll | dylib)     #
# XML_INC   -> Root path where XML2 includes can be found  #
############################################################
#cache()

unix {
 !macx:CONFIG += link_pkgconfig
 !macx:PKGCONFIG = libpq libxml-2.0
 !macx:PGSQL_LIB = -lpq
 !macx:XML_LIB = -lxml2
}

macx {
 PGSQL_LIB = /Library/PostgreSQL/9.3/lib/libpq.dylib
 PGSQL_INC = /Library/PostgreSQL/9.3/include
 XML_INC = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/include/libxml2
 XML_LIB = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.9.sdk/usr/lib/libxml2.dylib
}

windows {
 QMAKE_CXXFLAGS+="-DHAVE_STRUCT_TIMESPEC"

 contains(QMAKE_TARGET.arch, x86_64) {
  _WIN64 = 1
 }
 win*-msvc* {
  _WIN_MSVC = 1
  QMAKE_CXXFLAGS+="-D__PRETTY_FUNCTION__=__FUNCSIG__"
 }

 isEmpty(_WIN64) {
  PGSQL_DIR = E:\Database\PostgreSQL\9.3_32
  XML_DIR = E:\CXX\third_party\parser\xml\libxml2\libxml2-2.9.2-win32-x86
 } else {
  PGSQL_DIR = E:\Database\PostgreSQL\9.3
  XML_DIR = E:\CXX\third_party\parser\xml\libxml2\libxml2-2.9.2-win32-x86_64
 }

 PGSQL_INC = $$PGSQL_DIR\include
 XML_INC = $$XML_DIR\include
 isEmpty(_WIN_MSVC) {
  PGSQL_LIB = $$PGSQL_DIR\bin\libpq.dll
  XML_LIB = $$XML_DIR\bin\libxml2-2.dll
 } else {
  PGSQL_LIB = $$PGSQL_DIR\lib\libpq.lib
  XML_LIB = $$XML_DIR\lib\libxml2.dll.a
 }
}

macx | windows {
  !exists($$PGSQL_LIB) {
    PKG_ERROR = "PostgreSQL libraries"
    VARIABLE = "PGSQL_LIB"
    VALUE = $$PGSQL_LIB
  }
}

macx | windows {
  !exists($$PGSQL_INC/libpq-fe.h) {
    PKG_ERROR = "PostgreSQL headers"
    VARIABLE = "PGSQL_INC"
    VALUE = $$PGSQL_INC
  }
}

macx | windows {
 !exists($$XML_LIB) {
    PKG_ERROR = "XML2 libraries"
    VARIABLE = "XML_LIB"
    VALUE = $$XML_LIB
 }
}

macx | windows {
 !exists($$XML_INC) {
   PKG_ERROR = "XML2 headers"
   VARIABLE = "XML_INC"
   VALUE = $$XML_INC
 }
}


macx | windows {
 !isEmpty(PKG_ERROR) {
    warning("$$PKG_ERROR were not found at \"$$VALUE\"!")
    warning("Please correct the value of $$VARIABLE and try again!")
    error("pgModeler compilation aborted.")
 }
}

###########################
# Main variables settings #
###########################
CONFIG += ordered qt stl rtti exceptions warn_on c++11

#Additional configs on unix / windows
unix:CONFIG += x11
windows:CONFIG += windows

macx:CONFIG-=app_bundle

#Libraries extension and preffix for each platform
unix:LIB_PREFIX = lib
unix:LIB_EXT = so
windows {
 isEmpty(_WIN_MSVC) {
  LIB_EXT = dll
 } else {
  LIB_EXT = lib
 }
}
macx:LIB_EXT = dylib

SUBDIRS = libutils \
          libparsers \
          libpgmodeler \
          libpgconnector \
          libobjrenderer \
          libpgmodeler_ui \
          crashhandler \
          main-cli \
          main \
          plugins/dummy \
          plugins/xml2object

#Include the tests subproject only on debug mode
CONFIG(debug, debug|release):SUBDIRS+=tests

QT += core widgets printsupport network
TEMPLATE = subdirs
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = src

macx {
 BASEDIR = $$PWD/build/pgmodeler.app/Contents
 DESTDIR = $$BASEDIR/MacOS #Where the compiled executables are stored
 BINDESTDIR = $$DESTDIR
 DOCDESTDIR = $$DESTDIR
 LIBDESTDIR = $$BASEDIR/Frameworks #Where the compiled libs are stored
 RESDESTDIR = $$DESTDIR
}

# User can pass additional config params to specify custom output directory as follow:
#
# BINDIR = where any generated binary will be installed.
# LIBDIR = where any generated library will be installed.
# RESDIR = where resource files like conf, lang, samples and schema directories will be installed.
# DOCDIR = where doc files will be installed.
#
# By default, when not specifying any of above options, the compilation will generate files
# under ./build.
#
linux|windows {
 DESTDIR = $$PWD/build

 BINDESTDIR = $$DESTDIR
 defined(BINDIR, var): BINDESTDIR=$$BINDIR

 #On Linux and Windows the compiled libs resides on the same executable's dir (by default)
 LIBDESTDIR = $$DESTDIR
 defined(LIBDIR, var): LIBDESTDIR=$$LIBDIR

 #On Linux and Windows the resource files (conf, schemas, etc) resides on the same executable's dir (by default)
 RESDESTDIR = $$DESTDIR
 defined(RESDIR, var): RESDESTDIR=$$RESDIR
 
 DOCDESTDIR = $$DESTDIR
 defined(DOCDIR, var): DOCDESTDIR=$$DOCDIR
}

#Creating the project's libraries names based upon the running OS
LIBUTILS=$${LIB_PREFIX}utils.$${LIB_EXT}
LIBPARSERS=$${LIB_PREFIX}parsers.$${LIB_EXT}
LIBPGCONNECTOR=$${LIB_PREFIX}pgconnector.$${LIB_EXT}
LIBPGMODELER=$${LIB_PREFIX}pgmodeler.$${LIB_EXT}
LIBOBJRENDERER=$${LIB_PREFIX}objrenderer.$${LIB_EXT}
LIBPGMODELERUI=$${LIB_PREFIX}pgmodeler_ui.$${LIB_EXT}

#Setting up the flag passed to compiler to build the demo version
defined(DEMO_VERSION, var): QMAKE_CXXFLAGS+="-DDEMO_VERSION"

INCLUDEPATH += $$XML_INC \
               $$PGSQL_INC \
               $$PWD/libutils/src \
               $$PWD/libpgconnector/src \
               $$PWD/libparsers/src \
               $$PWD/libpgmodeler/src \
               $$PWD/libobjrenderer/src \
               $$PWD/libpgmodeler_ui/src \
               $$PWD/main/src


#Deployment configurations
pgmodeler_data.files = samples schemas lang conf
pgmodeler_data.path = $$RESDESTDIR

pgmodeler_doc.files = README.md CHANGELOG.md LICENSE RELEASENOTES.md
pgmodeler_doc.path = $$DOCDESTDIR

unix {
!macx:pgmodeler_data.files += pgmodeler.vars
linux:pgmodeler_data.files += start-pgmodeler.sh
}

INSTALLS += pgmodeler_data pgmodeler_doc
