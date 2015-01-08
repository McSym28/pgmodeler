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
\ingroup libpgmodeler_ui
\class DatabaseExplorerWidge
\brief Implements the operations to browse and manipulate database instances
*/

#ifndef DATABASE_EXPLORER_WIDGET_H
#define DATABASE_EXPLORER_WIDGET_H

#include "ui_databaseexplorerwidget.h"
#include "databaseimporthelper.h"
#include "schemaparser.h"

class LIBPGMODELERUI_API DatabaseExplorerWidget: public QWidget, public Ui::DatabaseExplorerWidget {
	private:
		Q_OBJECT

    /*! brief Connection used to handle objects on database. This connection is copied
        whenever a new operation must be performed on database */
    Connection connection;

    //! brief Database import helper used to list objects from current connection
    DatabaseImportHelper import_helper;

    SchemaParser schparser;

    //! brief Stores the actions to drop and show object's data
    QMenu handle_menu;

    QAction *copy_action, *drop_action, *drop_cascade_action,
            *show_data_action, *refresh_action;

    void configureImportHelper(void);

    //! brief Drops the object represented by the specified item
    void dropObject(QTreeWidgetItem *item, bool cascade);

    bool eventFilter(QObject *object, QEvent *event);

  public:
    DatabaseExplorerWidget(QWidget * parent = 0);

    //! brief Configures the connection used to retrieve and manipulate objects on database
    void setConnection(Connection conn);

    //! brief Returns a copy of the connection used by this explorer instance
    Connection getConnection(void);

  public slots:
    //! brief Lists all objects for the current selected database
    void listObjects(void);

  private slots:
    //! brief Shows the menu to drop/show data
    void handleObject(QTreeWidgetItem *item, int);

    //! brief Updates on the tree under the current selected object
    void updateCurrentItem(void);

  signals:
    //! brief This signal is emmited to indicate that the data manipulation dialog need to be opened
    void s_dataGridOpenRequested(QString schema, QString table, bool hide_views);
};

#endif
