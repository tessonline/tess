<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_title.inc"));
//$run=GetAgendaPath('POSTA',false,true)."/output/pdf/obalka.php";
Form_(array("showaccess"=>true, "caption"=>"Další dokumenty do obálky"));
require(FileUp2("html_footer.inc"));

?>
