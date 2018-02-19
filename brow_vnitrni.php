<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/config.inc"));
require(FileUp2("html_header_full.inc"));

echo '<div class="form darkest-color"> <div class="form-body"> <div class="form-row">';
echo '<form method="get" action="brow_vnitrni.php"><span class="text">Vyhledat JID:
<input type="text" name="podaci_cislo" size=15">&nbsp;<input class="button btn" type="submit" value="vyhledat"></form></span>';
echo '</div> </div> </div>';

If ($GLOBALS["podaci_cislo"])
{
  $id = PrevedCPnaID($GLOBALS["podaci_cislo"]);
  $where2="and id in (".$id.")";
}

//If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) $where2.=" AND datum_predani_ven is not null ";

$where="and odeslana_posta='t' and odesl_ico='".$GLOBALS["CONFIG"]["ICO"]."' ".$where2." and dalsi_id_agenda IS NULL and status=12 ";
$caption='Označit tuto odchozí poštu jako příchozí poštu';

$GLOBALS['SHOW_ZALOZ_VNITRNI'] = true; //zapneme ikonu pro predani
$GLOBALS['SHOW_BARCODE'] = true;
$count = Table(array(
  "tablename"=>"evidencepisemnostivnitrni",
//  "schema_file"=>"./.admin/table_schema_simple.inc",
  "schema_file"=>"./.admin/table_schema_guide.inc",
  "caption"=>$caption,
  "showpagging"=>true,
  "modaldialogs"=>false,
  "setvars"=>true,
  "showhistory"=>false,
  "showinfo"=>true,
  "showedit"=>false,
  "showdelete"=>false,
  "appendwhere"=>$where,
  "page_size"=>"25",
  ));

require(FileUp2("html_footer.inc"));
 
?>
