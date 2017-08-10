DROP PROCEDURE IF EXISTS make_include_graph;
#then_execute
CREATE PROCEDURE `make_include_graph`()
	LANGUAGE SQL
	NOT DETERMINISTIC
	CONTAINS SQL
	SQL SECURITY DEFINER
	COMMENT ''
BEGIN
select compiland_symbol 'Source', source_id 'Target' from included;
select src_files.path 'Label',src_files.source_id 'Id',  1 'type' from src_files
union all
select symbols.name 'Label', compilands.symbol 'Id', 0 'type' from compilands inner join symbols on symbols.symbol=compilands.symbol;
END