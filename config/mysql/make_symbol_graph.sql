DROP PROCEDURE IF EXISTS make_symbol_graph;
#then_execute
CREATE  PROCEDURE `make_symbol_graph`()
	LANGUAGE SQL
	DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
	COMMENT ''
BEGIN
select symbols.symbol 'Source', symbols.parent_symbol 'Target' from symbols where parent_symbol!=0 and (tag='function' or tag='enum' or tag='data' or tag='udt');
select symbols.symbol 'Id', symbols.name 'Label', symbols.tag from symbols where (tag='function' or tag='enum' or tag='data' or tag='udt');
END