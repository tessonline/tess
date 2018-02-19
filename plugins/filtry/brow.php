<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
//require(FileUp2(".admin/security_.inc"));
require(FileUp2(".admin/security_name.inc"));
require(FileUp2("html_header_full.inc"));
NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

if (!HasRole('spravce')) {
    $USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
    $where = 'AND owner_id IN (' . $USER_INFO['ID'] . ')';
}
//$GLOBALS['SUPERODBOR'] = EedTools::VratSuperOdbor();
echo "<a  class=\"btn btn-loading\" href=\"#\" onClick=\"javascript:NewWindowAgendaSpis('edit.php?insert&cacheid=')\">Založit nový filtr</a>";
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
