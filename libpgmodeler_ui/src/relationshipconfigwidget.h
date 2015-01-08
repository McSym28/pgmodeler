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
\class RelationshipConfigWidget
\brief Implements the operations to manage global settings for relationship objects.
*/

#ifndef RELATIONSHIP_CONFIG_WIDGET_H
#define RELATIONSHIP_CONFIG_WIDGET_H

#include "ui_relationshipconfigwidget.h"
#include "baseconfigwidget.h"
#include "pgsqltypes.h"
#include "syntaxhighlighter.h"
#include "relationshipview.h"
#include "hinttextwidget.h"

class LIBPGMODELERUI_API RelationshipConfigWidget: public QWidget, public Ui::RelationshipConfigWidget, public BaseConfigWidget {
	private:
		Q_OBJECT

		map<QString, attribs_map> patterns;

    HintTextWidget *fk_to_pk_ht, *center_pnts_ht;

    void hideEvent(QHideEvent *);

public:
		RelationshipConfigWidget(QWidget * parent=0);

		void saveConfiguration(void);
		void loadConfiguration(void);

	public slots:
		void applyConfiguration(void);
		void restoreDefaults(void);

	private slots:
		void fillNamePatterns(void);
		void updatePattern(void);

};

#endif
