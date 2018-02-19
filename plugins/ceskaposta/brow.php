<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/oth_funkce_2D.inc"));

If (!(HasRole('spravce')||HasRole('podatelna'))) $where=" and odbor=".VratOdbor();
If ((HasRole('spravce')||HasRole('podatelna'))) $where=" and odbor is null";

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

If (!(HasRole('spravce'))) $GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();

if (HasRole('spravce')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
}
if ($GLOBALS['omez_zarizeni']) $where = " AND superodbor=" . $GLOBALS['omez_zarizeni'];


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


