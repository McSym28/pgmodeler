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
\class PluginsConfigWidget
\brief Implements the operations to manage plugins.
*/

#ifndef PLUGINS_CONFIG_WIDGET_H
#define PLUGINS_CONFIG_WIDGET_H

#include "baseconfigwidget.h"
#include "ui_pluginsconfigwidget.h"
#include "objecttablewidget.h"
#include "pgmodelerplugin.h"

class LIBPGMODELERUI_API PluginsConfigWidget: public QWidget, public Ui::PluginsConfigWidget, public BaseConfigWidget {
	private:
		Q_OBJECT

		//! \brief Loaded plugins
		vector<PgModelerPlugin *> plugins;

		//! \brief Stores the actions assigned for each plugin
		vector<QAction *> plugins_actions;

		//! \brief Table used to show the loaded plugins
		ObjectTableWidget *plugins_tab;

		void applyConfiguration(void){}

	public:
		PluginsConfigWidget(QWidget *parent = 0);
		~PluginsConfigWidget(void);

		void loadPlugins(void);

		/*! \brief Install the created actions on menu and toolbars. Additionally the user must specify the
		 receiver object and slot executed when the actions is activated */
		void installPluginsActions(QToolBar *toolbar, QMenu *menu, QObject *recv, const char *slot);

	private slots:
		void showPluginInfo(int idx);
		void openRootPluginDiretory(void);
};

#endif
