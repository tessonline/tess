<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));

echo '<p>Nastavení slouží pro vytvoření vazby uživatelů mezi loginy z jiného systému a uživatelem v EED</p>';
Table(array("showaccess" => true,"appendwhere"=>$where2));  
require(FileUp2("html_footer.inc"));

