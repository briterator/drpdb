DROP PROCEDURE IF EXISTS make_inheritance_graph;
#then_execute
CREATE PROCEDURE `make_inheritance_graph`()
	LANGUAGE SQL
	DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
	COMMENT ''
BEGIN
select base_classes.child_symbol 'Source', base_classes.parent_symbol 'Target' from base_classes;
select user_types.symbol 'Id', symbols.name 'Label' from symbols inner join user_types on user_types.symbol = symbols.symbol;
END