DROP PROCEDURE IF EXISTS make_call_graph;
#then_execute
CREATE PROCEDURE `make_call_graph`()
	LANGUAGE SQL
	DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
	COMMENT ''
BEGIN
select target_symbol 'Target', symbol 'Source' from calls;
select target_symbol 'Id', name 'Label' from calls inner join symbols on calls.target_symbol=symbols.symbol
union all
select calls.symbol 'Id', name 'Label' from calls inner join symbols on calls.symbol=symbols.symbol;
END