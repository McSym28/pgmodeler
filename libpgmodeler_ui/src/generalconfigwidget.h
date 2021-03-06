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
\class GeneralConfigWidget
\brief Implements the operations to manage general configurations.
*/

#ifndef GENERAL_CONFIG_WIDGET_H
#define GENERAL_CONFIG_WIDGET_H

#include "ui_generalconfigwidget.h"
#include "baseconfigwidget.h"
#include "messagebox.h"
#include "hinttextwidget.h"

class LIBPGMODELERUI_API GeneralConfigWidget: public QWidget, public Ui::GeneralConfigWidget, public BaseConfigWidget {
	private:
		Q_OBJECT

        static const unsigned UNIT_MILIMETERS=0;
        static const unsigned UNIT_POINT=1;
        static const unsigned UNIT_INCHS=2;
        static const unsigned UNIT_CENTIMETERS=3;

    HintTextWidget *simp_obj_creation_ht, *confirm_validation_ht, *corner_move_ht,
    *save_last_pos_ht, *invert_pan_range_ht, *disable_smooth_ht,
    *hide_ext_attribs_ht, *hide_table_tags_ht, *hide_rel_name_ht;

    void hideEvent(QHideEvent *);


	public:
		GeneralConfigWidget(QWidget * parent=0);

		void saveConfiguration(void);
		void loadConfiguration(void);

	public slots:
		void applyConfiguration(void);
		void restoreDefaults(void);
		void updateFileAssociation(void);
		void selectPaperSize(void);

	private slots:
		void convertMarginUnity(void);
};

#endif
