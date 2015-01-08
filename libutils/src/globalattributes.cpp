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
#include "globalattributes.h"

#include <cstdlib>

QString _getenv_safe(QString varName, QString defValue) {
    QString varValue;
#if _MSC_VER >= 1500
    // http://msdn.microsoft.com/ru-ru/library/ms175774.aspx
    char* buf = 0;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, varName.toStdString().c_str())) {
        return defValue;
    }
    varValue = QString(buf);
    free(buf);
#else
    char *buf = getenv(varName);
    if (!buf) {
        return defValue;
    }
    varValue = QString(buf);
#endif
    if (varValue.isEmpty()) {
        return defValue;
    }
    return varValue;
}
