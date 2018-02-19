<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));


$id_prislo = $GLOBALS['ID'];
$count = Table(array(
         "appendwhere"=>$where,
         "maxnumrows"=>10,
         "nopaging"=>$nopaging,
         'caption' => 'Seznam aplikací',
//         "tablename"=>"ui_adresa", 
         
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,	 
//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
         "nocaption"=>false,
//         "sql"=>$q, 
         "showself" => true,
         "showaccess"=>true,
  	     "setvars"=>true,
  	     "unsetvars"=>true,
//         "formvars_decode"=>true,
//         "showselect"=>true, 
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));


require(FileUp2("html_footer.inc"));

?>
