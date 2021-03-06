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
\ingroup libparsers
\brief ParserEsquema class definition used to create SQL definition for model objects from schemas files (stored on disk).
\note <strong>Creation date:</strong> 19/06/2008
*/

#ifndef SCHEMA_PARSER_H
#define SCHEMA_PARSER_H

#include "globalattributes.h"
#include "exception.h"
#include <map>
#include <vector>
#include <QDir>
#include <QTextStream>
#include "xmlparser.h"
#include "attribsmap.h"

class LIBPARSERS_API SchemaParser {
	private:
		/*! \brief Indicates that the parser should ignore unknown
		 attributes avoiding raising exceptions */
		bool ignore_unk_atribs;

		/*! \brief Indicates that the parser should ignore empty
		 attributes avoiding raising exceptions */
		bool ignore_empty_atribs;

        static const char CHR_COMMENT;			//! \brief Character that starts a comment
        static const char CHR_LINE_END;			//! \brief Character that indicates end of line
        static const char CHR_SPACE;        //! \brief Character that indicates spacing
        static const char CHR_TABULATION;   //! \brief Character that indicates tabulation
        static const char CHR_INI_ATTRIB;   //! \brief Character that indicates a reference to an attribute
        static const char CHR_MID_ATTRIB;   //! \brief Character that delimits on the left the attribute name
        static const char CHR_END_ATTRIB;   //! \brief Character that delimits on the right the attribute name
        static const char CHR_INI_CONDITIONAL;//! \brief Character that starts a conditional instruction
        static const char CHR_INI_METACHAR;   //! \brief Character that starts a metacharacter
        static const char CHR_INI_PURETEXT;   //! \brief Character that starts a puretext
        static const char CHR_END_PURETEXT;   //! \brief Character that ends a puretext
        static const char CHR_INI_CEXPR;      //!brief Character that starts a comparison expression
        static const char CHR_END_CEXPR;      //!brief Character that ends a comparison expression
        static const char CHR_VAL_DELIM;      //!brief Character that delimiters a value (string)

        //! \brief Tokens related to conditional instructions and operators
        static const QString	TOKEN_IF;  // %if
        static const QString	TOKEN_THEN;// %then
        static const QString	TOKEN_ELSE;// %else
        static const QString	TOKEN_END; // %end
        static const QString	TOKEN_OR;  // %or
        static const QString	TOKEN_NOT; // %not
        static const QString	TOKEN_AND; // %and
        static const QString	TOKEN_DEFINE; //%define


		//! \brief Tokens related to metacharacters
        static const QString	TOKEN_META_SP;// $sp (space)
        static const QString	TOKEN_META_BR;// $br (line break)
        static const QString	TOKEN_META_TB;// $tb (tabulation)
        static const QString	TOKEN_META_OB;// $ob (open bracket '[')
        static const QString	TOKEN_META_CB;// $cb (close bracket ']')

    //! \brief Tokens related to comparison expressions
        static const QString	TOKEN_EQ_OP;// == (equal)
        static const QString	TOKEN_NE_OP;// != (not equal)
        static const QString	TOKEN_GT_OP;// > (greater than)
        static const QString	TOKEN_LT_OP;// < (less than)
        static const QString	TOKEN_GT_EQ_OP;// >= (greater or equal to)
        static const QString	TOKEN_LT_EQ_OP;// <= (less or equal to)


		//! \brief Get an attribute name from the buffer on the current position
		QString getAttribute(void);

		//! \brief Get an conditional instruction from the buffer on the current position
		QString getConditional(void);

		//! \brief Get an metacharacter from the buffer on the current position
		QString getMetaCharacter(void);

		/*! \brief Returns the result (true|false) of conditional expression evaluation.
		The expression is evaluated from the left to the right and not support Polish Notation, so
		as the parser finds an attribute evaluates it and stores the result, when find another one
		evaluates and compare with previous evaluation, and so on. Example:

		Let's suppose a1 and a2 has values and a3 is empty, the following expression
		results will be:

				%if @{a1} %or @{a2} %and {a3} %then --> FALSE
				%if @{a1} %or @{a2} %and %not {a3} %then --> TRUE
				%if @{a1} %or %not @{a3} %then --> TRUE
				%if @{a1} %and @{a3} %then --> FALSE
		*/
		bool evaluateExpression(void);

    /*! \brief Returns the result (true|false) of a comparison expression. A comparison expression
        have the form: ( @{attribute} [operator] "value" ), where:

        (            --> Starts the expression
        @{attribute} --> Is the attribute to be compared to a value
        [operator]   --> A valid comparison operator:
                         == (equal), != (not equal), < (less than), > (greater than)
                         <= (less or equal to), >= (greater or equal to)
        )            --> Closes the expression

        The parenthesis are mandatory otherwise the parser will not recognize the expression
        and raise an exception. Multiple expressions combined with logical operators
        %not %and %or in the same () are not supported. */
    bool evaluateComparisonExpr(void);

    /*! brief Creates a new attribute when finding  %define @{attrib-name} [expr], where [expr]
        can be pure texts, meta chars or other attributes exists overwrite its value */
    void defineAttribute(void);

    //! brief Increments the column counter while blank chars (space and tabs) are found on the line
		void ignoreBlankChars(const QString &line);

    //! brief Translates the meta char token to the real character
    char translateMetaCharacter(const QString &meta);

		/*! \brief Get an word from the buffer on the current position (word is any string that isn't
		 a conditional instruction or comment) */
		QString getWord(void);

		//! \brief Gets a pure text, ignoring elements of the language
		QString getPureText(void);

		/*! \brief Returns whether a character is special i.e. indicators of attributes
		 or conditional instructions */
		bool isSpecialCharacter(char chr);

		//! \brief Filename that was loaded by the parser
		QString filename;

		/*! \brief Vectorial representation of the loaded file. This is the buffer that is
		 analyzed by de parser */
		vector<QString> buffer;

		unsigned line, //! \brief Current line where the parser reading is
						 column, //! \brief Current column where the parser reading is

						/*! \brief Comment line ammout extracted. This attribute is used to make the correct
											reference to the line on file that has syntax errors */
						 comment_count;

		attribs_map attributes;

		//! \brief PostgreSQL version currently used by the parser
		QString pgsql_version;

	public:

		//! \brief Constants used to refernce PostgreSQL versions.
        static const QString PGSQL_VERSION_90;
        static const QString PGSQL_VERSION_91;
        static const QString PGSQL_VERSION_92;
        static const QString PGSQL_VERSION_93;
        static const QString PGSQL_VERSION_94;

		//! \brief Constants used to get a specific object definition
        static const unsigned SQL_DEFINITION=0;
        static const unsigned XML_DEFINITION=1;

		SchemaParser(void);

		/*! \brief Set the version of PostgreSQL to be adopted by the parser in obtaining
		 the definition of the objects. This function should always be called at
		 software startup or when the user wants to change the default version
		 of the database */
		void setPgSQLVersion(const QString &pgsql_ver);

		/*! \brief Returns the complete xml/sql definition for an database object represented by the
		 map 'attributes'. For SQL definition is necessary to indicate the version of PostgreSQL
		 in order to the to correct schema be loaded */
		QString getCodeDefinition(const QString &obj_name, attribs_map &attribs, unsigned def_type);

		/*! \brief Generic method that loads a schema file and for a given map of attributes
		 this method returns the data of the file analyzed and filled with the values ​​of the
		 attributes map */
		QString getCodeDefinition(const QString &filename, attribs_map &attribs);

		/*! \brief Generic method that interprets a pre-specified buffer (see loadBuffer()) and for a given map
		 of attributes this method returns the data of the buffer analyzed and filled with the values ​​of the
		 attributes map */
		QString getCodeDefinition(attribs_map &attribs);

		//! \brief Loads the buffer with a string
		void loadBuffer(const QString &buf);

		//! \brief Loads a schema file and inserts its line into the parser's buffer
		void loadFile(const QString &filename);

		//! \brief Resets the parser in order to do new analysis
		void restartParser(void);

		//! \brief Set if the parser must ignore unknown attributes avoiding expcetion throwing
		void setIgnoreUnkownAttributes(bool ignore);

		//! \brief Set if the parser must ignore empty attributes avoiding expcetion throwing
		void setIgnoreEmptyAttributes(bool ignore);

		//! \brief Retorns the current PostgreSQL version used by the parser
		QString getPgSQLVersion(void);

		//! \brief Returns the PostgreSQL version supported by pgModeler
		static QStringList getPgSQLVersions(void);

		/*! \brief Converts any chars (operators) < > " to the respective XML entities. This method is only
    called when generating XML code and only tag attributes are treated.*/
    static QString convertCharsToXMLEntities(QString buf);
};

#endif
