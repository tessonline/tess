<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));

If (!(HasRole('spravce')||HasRole('podatelna'))) $where=" and odbor=".VratOdbor();

If (!(HasRole('spravce'))) $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

//$GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();
echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('edit.php?insert&cacheid=')\">Založit nový protokol</a>";
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
