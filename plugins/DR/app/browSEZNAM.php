<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2(".admin/table_func_DR.inc"));
require(FileUp2("html_header_full.inc"));

$id_prislo = $GLOBALS['ID'];

if (!$id_prislo && $GLOBALS['VYBRANE_ID']>0) { $id_prislo = $GLOBALS['VYBRANE_ID']; $GLOBALS['ID'] = $GLOBALS['VYBRANE_ID'];}

$GLOBALS['VYBRANE_ID'] = $id_prislo;


$count = Table(array(
         "appendwhere"=>$where,
         "maxnumrows"=>10,
         "nopaging"=>$nopaging,
         'caption' => 'Seznam aplikací',
         "tablename"=>"seznam",
         
         "showdelete"=>true, 
         "showedit"=>true,
         "showinfo"=>false,	 
//         "showinfo"=>$USER_INFO["LOGIN"]!="anonymous",
         "nocaption"=>false,
         "showselfurl" => "browSEZNAM.php",
//         "sql"=>$q, 
         "showself" => true,
         "showaccess"=>true,
  	     "setvars"=>true,
  	     "unsetvars"=>true,
         "formvars"=>array('VYBRANE_ID'),
//         "showselect"=>true, 
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));

if ($count==1 && $id_prislo>0) {

  $GLOBALS['VYBRANE_ID'] = $id_prislo;
  $where = "AND stav=".(1001+($id_prislo*10))." and odeslana_posta='f'";
$count = Table(array(
         "agenda" => "POSTA",
         "schema_file"=>"plugins/DR/app/.admin/table_schema_prichozi.inc",
         "appendwhere"=>$where,
         "tablename"=>"prichozi",
         "showdelete"=>false,
         "showedit"=>false,
         "showinfo"=>false,
         "caption" => "Příchozí dokumenty k předaní do aplikace",
         "nocaption"=>false,
//         "sql"=>$q,
         "showaccess"=>true,
  	     "setvars"=>true,
  	     "unsetvars"=>true,
         "formvars"=>array('VYBRANE_ID'),
//         "showselect"=>true,
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));

  $GLOBALS['VYBRANE_ID'] = $id_prislo;
  $where = "AND DALSI_ID_AGENDA LIKE 'DR-" . $id_prislo ."-%' and odeslana_posta='t'";
  $count = Table(array(
         "agenda" => "POSTA",
         "schema_file"=>"plugins/DR/app/.admin/table_schema_dorucenky.inc",
         "tablename"=>"odchozi",
         "appendwhere"=>$where,
         "showdelete"=>false,
         "showedit"=>false,
         "showinfo"=>false,
         "caption" => "Odchozí dokumenty z aplikace",
         "nocaption"=>false,
//         "sql"=>$q,
         "showaccess"=>true,
  	     "setvars"=>true,
  	     "unsetvars"=>true,
         "formvars"=>array('VYBRANE_ID'),
//         "formvars_decode"=>true,
//         "showselect"=>true,
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));


  $GLOBALS['VYBRANE_ID'] = $id_prislo;
  $where = "AND stav=".(1002+($id_prislo*10))." and odeslana_posta='f'";
$count = Table(array(
         "agenda" => "POSTA",
         "schema_file"=>"plugins/DR/app/.admin/table_schema_prichozi.inc",
         "appendwhere"=>$where,
         "tablename"=>"prichozi2",
         "showdelete"=>false,
         "showedit"=>false,
         "showinfo"=>false,
         "caption" => "Příchozí dokumenty jíž předané do aplikace",
         "nocaption"=>false,
//         "sql"=>$q,
         "showaccess"=>true,
  	     "setvars"=>true,
  	     "unsetvars"=>true,
         "formvars"=>array('VYBRANE_ID'),
//         "showselect"=>true,
//         "multipleselect" => true,
//         "multipleselectsupport" => true,
));


}

require(FileUp2("html_footer.inc"));

?>
