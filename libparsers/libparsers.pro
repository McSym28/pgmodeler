include(../pgmodeler.pro)

TEMPLATE = lib
TARGET = parsers

!macx {
 # Check if LIBDESTDIR points to another location other than DESTDIR
 # in this case the INSTALLS will be used
 !equals(LIBDESTDIR, $$DESTDIR) {
  target.path = $$LIBDESTDIR
  INSTALLS = target
 }

 windows {
  !isEmpty(_WIN_MSVC) {
   QMAKE_CXXFLAGS+="-DLIBPARSERS_EXPORT"
  }
 }
}

macx:DESTDIR=$$LIBDESTDIR

LIBS += $$DESTDIR/$$LIBUTILS \
	$$XML_LIB

HEADERS += src/schemaparser.h \
	   src/xmlparser.h \
	   src/attribsmap.h \
	   src/parsersattributes.h

SOURCES += src/schemaparser.cpp \
	   src/xmlparser.cpp

