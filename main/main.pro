include(../pgmodeler.pro)

TEMPLATE = app
TARGET = pgmodeler


windows:RC_FILE=res/windows_ico.qrc
windows:RCC_DIR=src/

windows {
 !isEmpty(_WIN_MSVC) {
  INCLUDEPATH += $$OUT_PWD/../libpgmodeler_ui/src
 }
}

macx:QMAKE_POST_LINK+="cp -r $$PWD/res/Resources $$BASEDIR; \
                       cp $$PWD/res/Info.plist $$BASEDIR; \
                       cp $$PWD/res/PkgInfo $$BASEDIR; \
                       cp $$PWD/res/startapp $$DESTDIR"

!macx {
 # Check if BINDESTDIR points to another location other than DESTDIR
 # in this case the INSTALLS will be used
 !equals(BINDESTDIR, $$DESTDIR) {
  target.path = $$BINDESTDIR
  INSTALLS = target
 }

 LIBS += $$DESTDIR/$$LIBUTILS \
         $$DESTDIR/$$LIBPARSERS \
         $$DESTDIR/$$LIBPGCONNECTOR \
         $$DESTDIR/$$LIBOBJRENDERER \
         $$DESTDIR/$$LIBPGMODELER \
         $$DESTDIR/$$LIBPGMODELERUI
}

macx {
 DESTDIR=$$BINDESTDIR
 LIBS += $$LIBDESTDIR/$$LIBUTILS \
         $$LIBDESTDIR/$$LIBPARSERS \
         $$LIBDESTDIR/$$LIBPGCONNECTOR \
         $$LIBDESTDIR/$$LIBOBJRENDERER \
         $$LIBDESTDIR/$$LIBPGMODELER \
         $$LIBDESTDIR/$$LIBPGMODELERUI
}

HEADERS += src/application.h
SOURCES += src/main.cpp \
    src/application.cpp

