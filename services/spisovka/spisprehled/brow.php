<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

if ($CISLO_SPISU1 &&$CISLO_SPISU2 ) $cislospisu = $CISLO_SPISU1.'/'.$CISLO_SPISU2;
$count = Table(array(
   "appendwhere"=>$where,
   "maxnumrows"=>25,
   "nopaging"=>$nopaging,
//         "tablename"=>"ui_adresa", 
   
   "showdelete"=>true, 
   "showedit"=>true,
   "showinfo"=>true,	 
//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
   "nocaption"=>false,
//         "sql"=>$q, 
   "showaccess"=>true,
   "setvars"=>true, 
//         "formvars_decode"=>true, 
//         "showselect"=>true, 
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));



require(FileUp2("html_footer.inc"));

?>
