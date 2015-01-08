include(../pgmodeler.pro)

TEMPLATE = lib
TARGET = objrenderer

!macx {
 # Check if LIBDESTDIR points to another location other than DESTDIR
 # in this case the INSTALLS will be used
 !equals(LIBDESTDIR, $$DESTDIR) {
  target.path = $$LIBDESTDIR
  INSTALLS = target
 }

 windows {
  !isEmpty(_WIN_MSVC) {
   QMAKE_CXXFLAGS+="-DLIBOBJRENDERER_EXPORT"
  }
 }
}

macx:DESTDIR=$$LIBDESTDIR

LIBS += $$DESTDIR/$$LIBUTILS \
	$$DESTDIR/$$LIBPARSERS \
	$$DESTDIR/$$LIBPGMODELER

HEADERS +=  src/baseobjectview.h \
	    src/textboxview.h \
	    src/tableview.h \
	    src/graphicalview.h \
	    src/relationshipview.h \
	    src/tabletitleview.h \
	    src/tableobjectview.h \
	    src/basetableview.h \
	    src/objectsscene.h \
	    src/schemaview.h \
    src/roundedrectitem.h \
    src/styledtextboxview.h

SOURCES +=  src/baseobjectview.cpp \
	    src/textboxview.cpp \
	    src/tableview.cpp \
	    src/graphicalview.cpp \
	    src/relationshipview.cpp \
	    src/tabletitleview.cpp \
	    src/tableobjectview.cpp \
	    src/basetableview.cpp \
	    src/objectsscene.cpp \
	    src/schemaview.cpp \
    src/roundedrectitem.cpp \
    src/styledtextboxview.cpp
