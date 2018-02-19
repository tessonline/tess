<?php
session_start();
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/upload_.inc"));
require(FileUp2(".admin/has_access.inc"));
include_once(FileUp2(".admin/security_.inc"));
include_once(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));

$uplobj=Upload(array('create_only_objects'=>true,'noshowheader'=>true));


$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 

$GLOBALS['TYP_POSTY']=$GLOBALS['CONFIG']['REZERVACE_TYP_POSTY'];

//if (HasRole('podatelna'))
//  $GLOBALS['SUPERODBOR']=VratSuperOdbor();
//else
  $GLOBALS['REFERENT']=$rezervace_id;

$GLOBALS["ODESLANA_POSTA"]='t';
$count = Table(array(
         "appendwhere"=>$where,
         "caption"=>"Čísla, která jsou již rezervována",
         "agenda"=>"POSTA",
         "schema_file"=>GetAgendaPath('POSTA_REZERVACE')."/.admin/table_schema.inc",
         "maxnumrows"=>10,
         "nopaging"=>$nopaging,
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
         "showexportall"=>true,
  	     "setvars"=>true,
));

NewWindow(array("fname"=>"", "name"=>"vicereferentu", "header"=>true, "cache"=>false, "window"=>"edit"));
echo "<form name=\"frm_pf_parc\" method=\"GET\">\n";
echo "<input type=\"submit\" class='button' value=\"Přidat čísla do rezervace\" onClick=\"NewWindow('edit.php?insert&REFERENT=".$rezervace_id."');return false;\">\n";
echo "</form>";


require(FileUp2("html_footer.inc"));

?>
