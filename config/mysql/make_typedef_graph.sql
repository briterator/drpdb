DROP PROCEDURE IF EXISTS make_typedef_graph;
#then_execute
CREATE PROCEDURE `make_typedef_graph`()
	LANGUAGE SQL
	DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
	COMMENT ''
BEGIN
select typedefs.symbol 'Source', typedefs.type_symbol 'Target' from typedefs;
select typedefs.symbol 'Id', symbols.name 'Label' from symbols inner join typedefs on typedefs.symbol=symbols.symbol
union all
select typedefs.type_symbol 'Id', symbols.name 'Label' from symbols inner join typedefs on typedefs.type_symbol=symbols.symbol;
END