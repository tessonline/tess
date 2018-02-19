<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2("html_header_title.inc"));

// Author: Ngo Minh Nam
$dir = GetAgendaPath('POSTA', false, false);
$output = array();
chdir($dir);
exec("git log",$output);
$history = array();

foreach($output as $line){
	if(strpos($line, 'commit')===0){
		if(!empty($commit)){
			array_push($history, $commit);
			unset($commit);
		}
		$commit['HASH']   = substr($line, strlen('commit'));
	}
	else if(strpos($line, 'Author')===0){
		$commit['AUTHOR'] = substr($line, strlen('Author:'));
	}
	else if(strpos($line, 'Date')===0){
		$commit['DATE']   = substr($line, strlen('Date:'));
	}
	else{
		$commit['MESSAGE']  .= $line;
	}
}

include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data = $history;

$table = array(
  array( field=>"HASH", "label"=>"ID", width=>"10%"),
  array( field=>"AUTHOR", "label"=>"Autor", width=>"30%"),
  array( field=>"DATE", "label"=>"Datum", width=>"20%","add"=>"NOWRAP"),
  array( field=>"MESSAGE", "label"=>"Popis", width=>"50%","add"=>"NOWRAP"),
);

Table(
		array(
				"db_connector" => &$db_arr,
				"table_schema" => $table,
				"showaccess" => true,
				"caption" => "GIT log",
				"showedit"=>false,
				"showdelete"=>false,
				"setvars" => true,
				"showinfo"=>false,
				"showhistory"=>false,

				"showcount"=>false,
		)
		);


require_once(Fileup2("html_footer.inc"));
