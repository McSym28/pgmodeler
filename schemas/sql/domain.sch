# SQL definition for domains
# PostgreSQL Version: 9.x
# CAUTION: Do not modify this file unless you know what you are doing.
#          Code generation can be broken if incorrect changes are made.

[-- object: ] @{name} [ | type: ] @{sql-object} [ --] $br

[-- ] @{drop}

 %if @{prepended-sql} %then
   @{prepended-sql}
   $br [-- ddl-end --] $br $br
 %end

[CREATE DOMAIN ] @{name} [ AS ] @{type}

%if (@{pgsql-ver} != "9.0") %and @{collation} %then
 $br $tb [COLLATE ] @{collation}
%end

%if @{default-value} %then
 $br $tb [DEFAULT ] @{default-value}
%end

%if @{not-null} %then
 $br $tb [NOT NULL]
%end

%if @{expression} %then

 $br $tb

 %if @{constraint} %then
   [CONSTRAINT ] @{constraint} $sp
 %end

 [CHECK ] (@{expression})
%end

;$br

# This is a special token that pgModeler recognizes as end of DDL command
# when exporting models directly to DBMS. DO NOT REMOVE THIS TOKEN!
[-- ddl-end --] $br

%if @{owner} %then @{owner} %end
%if @{comment} %then @{comment} %end

%if @{appended-sql} %then
 @{appended-sql}
 $br [-- ddl-end --] $br
%end

$br
