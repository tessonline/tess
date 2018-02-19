<?php
require("tmapy_config.inc");
require(FileUp2(".admin/edit_.inc"));
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/javascript.inc"));


$GLOBALS['spis'] = 1;

if (isset($GLOBALS['EDIT_ID'])) {
  $q = new DB_POSTA;
  $sql="select posta_id,spis, spis_id, odbor, access, referent from posta_pristupy where id =".$GLOBALS['EDIT_ID'];
  $q->query($sql);
  $q->next_record();
  $GLOBALS['REFERENT'] = $q->Record["REFERENT"];
  $GLOBALS['ODBOR'] = $q->Record["ODBOR"];
  $GLOBALS['SPIS_ID'] = $q->Record["SPIS_ID"];
  $GLOBALS['POSTA_ID'] = $q->Record["POSTA_ID"];
  //  $GLOBALS['ACCESS'] = $q->Record["ACCESS"];
  $GLOBALS['spis'] = $q->Record["SPIS"];
}
//else {



if ((isset($GLOBALS['EDIT_ID'])&&($GLOBALS['spis']==1))) {
  $GLOBALS['RANGE'] = 'C';
  $range = $GLOBALS['RANGE'];
}



Form_(array(
  "showaccess"=>true, 
  "nocaption"=>false,
));


$posta_id = ($GLOBALS['SPIS_ID'] ? $GLOBALS['SPIS_ID'] : $GLOBALS['POSTA_ID']);
$cj_obj = LoadClass('EedCj',$posta_id);
$GLOBALS['ID'] = $cj_obj->GetDocsInCj($posta_id);



unset ($GLOBALS['ODBOR']);
unset ($GLOBALS['REFERENT']);
unset ($GLOBALS['LAST_DATE']);
unset ($GLOBALS['LAST_TIME']);
unset ($GLOBALS['LAST_USER_ID']);
unset ($GLOBALS['OWNER_ID']);


echo "<br />";
$count = Table(array(
  "agenda" => "POSTA",
  "tablename" => "vybrane",
  "showselect"=>true,
  "showedit"=>false,
  "multipleselect"=>true,
  "multipleselectsupport"=>true,
  "schema_file" => '.admin/table_schema_simple.inc',
  "nocaption" => true,
  "showdelete"=>false,
  "nopaging"=>true,
  "showinfo"=>FALSE,
  "setvars"=>true,
  "showhistory"=>false  
));



require(FileUp2("html_footer.inc"));


?>
<script type="text/javascript">
	JenVybrane({value:'<?php echo $range; ?>'});
	pristupyZmena();	
	document.querySelector('[name="frm_edit"]')
		.addEventListener('submit',
         function () {
    			formPristupyPromenne();
    			}
		);
		
</script>