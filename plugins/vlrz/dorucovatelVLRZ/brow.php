<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));

If (!(HasRole('spravce')||HasRole('podatelna'))) $where=" and odbor=".VratOdbor();

$GLOBALS['SUPERODBOR']=VratSuperOdbor();
echo "<input type='button' class='button btn' value='Založit nový protokol' onclick=\"window.open('edit.php?insert&cacheid=', 'xertex', 'height=500px,width=700px,left=0,top=0,scrollbars,resizable');\">";
$count = Table(array(
         "appendwhere"=>$where,
         "maxnumrows"=>10,
         "nopaging"=>$nopaging,
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,
         "showself"=>false,	 
         "nocaption"=>false,
         "showaccess"=>true,
  	     "setvars"=>true, 
));



require(FileUp2("html_footer.inc"));

?>
