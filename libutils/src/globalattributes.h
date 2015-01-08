/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2014 - Raphael Araújo e Silva <raphael@pgmodeler.com.br>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

/**
\ingroup libutils
\namespace GlobalAttributes
\brief Definition of GlobalAttributes namespace wich stores a series of static strings constants used
 to reference the global configuration attributes of the software.
\note <strong>Creation date:</strong> 14/05/2010
*/

#ifndef GLOBAL_ATTRIBUTES_H
#define GLOBAL_ATTRIBUTES_H

#include <QString>
#include <QDir>
#include <QDate>
#include "dllapi.h"

LIBUTILS_API QString _getenv_safe(QString varName, QString defValue);

namespace GlobalAttributes {
	static const QString
  PGMODELER_VERSION="0.8.0-beta",
	PGMODELER_VER_CODENAME="Faithful Elephant",
  PGMODELER_BUILD_NUMBER=QDate::fromString(QString(__DATE__).simplified(), "MMM d yyyy").toString("yyyyMMdd"),
  PGMODELER_SITE="http://www.pgmodeler.com.br",
  PGMODELER_WIKI=QString("%1/wiki").arg(PGMODELER_SITE),
  PGMODELER_SRC_URL="https://github.com/pgmodeler/pgmodeler/releases",
  PGMODELER_BIN_URL=QString("%1/purchase.php").arg(PGMODELER_SITE),
  PGMODELER_UPD_CHECK_URL=QString("%1/checkupdate.php?current_ver=").arg(PGMODELER_SITE),

	CRASH_REPORT_EMAIL="bug@pgmodeler.com.br",
	CRASH_REPORT_FILE="pgmodeler%1.crash",
	STACKTRACE_FILE=".stacktrace",
	MACOS_STARTUP_SCRIPT="startapp",

	DIR_SEPARATOR="/",
	DEFAULT_CONFS_DIR="defaults", //! \brief Directory name which holds the default pgModeler configuration
	SCHEMAS_DIR="schemas", //! \brief Default name for the schemas directory
	SQL_SCHEMA_DIR="sql", //! \brief Default name for the sql schemas directory
	XML_SCHEMA_DIR="xml", //! \brief Default name for the xml schemas directory
  ALTER_SCHEMA_DIR="alter", //! \brief Default name for the alter schemas directory
	SCHEMA_EXT=".sch", //! \brief Default extension for schema files
	OBJECT_DTD_DIR="dtd", //! \brief Default directory for dtd files
	OBJECT_DTD_EXT=".dtd", //! \brief Default extension for dtd files
	ROOT_DTD="dbmodel", //! \brief Root DTD of model xml files
	CONFIGURATION_EXT=".conf", //! \brief Default extension for configuration files
	HIGHLIGHT_FILE_SUF="-highlight", //! \brief Suffix of language highlight configuration files

	CODE_HIGHLIGHT_CONF="source-code-highlight", //! \brief Default name for the language highlight dtd
	OBJECTS_STYLE_CONF="objects-style", //! \brief Default name for the object style configuration file
	GENERAL_CONF="pgmodeler", //! \brief Default name for the general pgModeler configuration
	CONNECTIONS_CONF="connections", //! \brief Default name for the DBMS connection configuration file
	RELATIONSHIPS_CONF="relationships",//! \brief Default name for the relationships configuration file

	SQL_HIGHLIGHT_CONF="sql-highlight", //! \brief Configuration file for SQL language highlight
	XML_HIGHLIGHT_CONF="xml-highlight", //! \brief Configuration file for XML language highlight
	PATTERN_HIGHLIGHT_CONF="pattern-highlight", //! \brief Configuration file for name patterns highlight (relationship editing form)

	EXAMPLE_MODEL="example.dbm", //! \brief Default name for the sample model loaded on appearence configuration form
	UI_STYLE_CONF="ui-style", //! \brief Configuration file ui style

	/*! \brief Fusion is the default widget style for pgModeler. User can change this by calling
	the executable using -style option. This same style is applied to crash handler. */
	DEFAULT_QT_STYLE="Fusion",
	UI_STYLE_OPT="-style";


	/*! \brief Variables used to reference the pgModeler directories.
	 By default, it searches the directories conf/, schemas/, lang/, plugins/, tmp/ and samples/ on
	 the working dir. But these values ​​can be overwritten using the
	 environment variables:

		 PGMODELER_SCHEMAS_DIR
		 PGMODELER_CONF_DIR
		 PGMODELER_LANG_DIR
		 PGMODELER_PLUGINS_DIR
		 PGMODELER_TMP_DIR
		 PGMODELER_SAMPLES_DIR*/

	static const QString
	/*! \brief According to the libxml documentation , the paths used by the parser are
		 in URI format (eg file://a/b/c) then, in Windows, the paths are shaped
		 C:\a\b\c, this caused the error in the parser that could not find
		 the DTD's. The solution to this problem is to replace the '\' by the way '/' */

	/*! \brief If the variable is not specified, pgModeler searches the required folder in the current directory "." */
    SCHEMAS_ROOT_DIR=_getenv_safe("PGMODELER_SCHEMAS_DIR", "./schemas").replace("\\","/"),
    CONFIGURATIONS_DIR=_getenv_safe("PGMODELER_CONF_DIR", "./conf").replace("\\","/"),
    LANGUAGES_DIR=_getenv_safe("PGMODELER_LANG_DIR", "./lang").replace("\\","/"),
    PLUGINS_DIR=_getenv_safe("PGMODELER_PLUGINS_DIR", "./plugins").replace("\\","/"),
    TEMPORARY_DIR=_getenv_safe("PGMODELER_TMP_DIR", "./tmp").replace("\\","/"),
    SAMPLES_DIR=_getenv_safe("PGMODELER_SAMPLES_DIR", "./samples").replace("\\","/"),

	/*! \brief Crash handler executable path configuration, the user can use the below envvar to set a
	different location for pgmodeler-ch */
	#ifndef Q_OS_MAC
        CRASH_HANDLER_PATH=_getenv_safe("PGMODELER_CHANDLER_PATH",
            #ifdef Q_OS_LINUX
                "./pgmodeler-ch"
            #else
                ".\\pgmodeler-ch.exe"
            #endif
            );
	#else
		//For MacOSX the crash handler path is fixed (inside bundle)
		CRASH_HANDLER_PATH=MACOS_STARTUP_SCRIPT + " pgmodeler-ch";
	#endif

	#ifdef DEMO_VERSION
	 //Maximum object creation counter for demo version
   static const unsigned MAX_OBJECT_COUNT=8;
	#endif
}

#endif
