<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));


$count = Table(array(
         "appendwhere"=>$where,
         "maxnumrows"=>10,
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,	 
//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
         "nocaption"=>false,
//         "sql"=>$q, 
         "showaccess"=>true,
  	     "setvars"=>true, 
));



require(FileUp2("html_footer.inc"));

?>
