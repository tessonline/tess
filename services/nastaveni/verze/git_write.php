<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2("html_header_title.inc"));

$dir = GetAgendaPath('POSTA', false, false);
$output = array();
chdir($dir);
exec("git log",$output);
$history = array();

$verObj = LoadClass('EedVersion', '');

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
    $commit['ENG_DATE'] = date('Y-m-d H:i:s', strtotime($commit['DATE']));
	}
	else{
		$commit['MESSAGE']  .= $line;
	}

}

foreach ($history as $event)
  $verObj->WriteGitLog($event);
//print_r($commit);

require_once(Fileup2("html_footer.inc"));
