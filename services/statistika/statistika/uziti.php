<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/nocache.inc"));
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2("html_header.inc"));
?>
    <link href="css/main.css" rel="stylesheet" type="text/css">
    <link href="css/form.css" rel="stylesheet" type="text/css">
    <script src="js/libs/jquery-1.8.3.min.js"></script>
    <script src="js/form.js"></script>
  </head>
<body>
<?
$uziti_array = array(
  1=>array('nazev'=>'Užití spisových znaků', 'table_name'=>'posta_w_statistika_skartace','desc'=>'napříč spisovými plány','ident'=>'SKARTACE'),
  2=>array('nazev'=>'Užití věcné klasifikace', 'table_name'=>'posta_w_statistika_typ_posty','desc'=>'delší select, setrvejte','ident'=>'ODES_TYP'),
  3=>array('nazev'=>'Užití věcné fáze', 'table_name'=>'posta_w_statistika_jine','desc'=>'delší select, setrvejte','ident'=>'JINE'),
  4=>array('nazev'=>'Užití ukládacích značek', 'table_name'=>'posta_w_statistika_ukl_znacka','desc'=>'delší select, setrvejte','ident'=>'UKL_ZNACKA_ID'),
  5=>array('nazev'=>'Užítí dle subjektů', 'table_name'=>'posta_w_statistika_subj','desc'=>'delší select, setrvejte','ident'=>'SUBJEKT'),
  6=>array('nazev'=>'Užití dle způsobu vyřízení', 'table_name'=>'posta_w_statistika_zpus_vyrizeni','desc'=>'delší select, setrvejte','ident'=>'VYRIZENO'),
);


if (count($uziti_array)>0 && !$ident)
{ 
	echo '<div id="links">';
	echo '<ul>';
	foreach($uziti_array as $id => $funkce) echo '<li><a class="stat_link" id='.$id.' href="uziti.php?ident='.$id.'&cacheid=">'.$funkce['nazev'].'</a><br/>'.$funkce['desc'];
	echo '</ul>';
	echo '</div>';
	echo '<div id="select_odbor">';
	/*filtr dle pracoviště a roku*/
	$q=new DB_POSTA;
	$sql="SELECT DISTINCT g.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=0 or g.parent_group_id is null ORDER BY g.id";	
	$res = $q->query($sql);
	echo'<form name="dep" id="dep" action="'.$PHP_SELF.'">';	
	echo'Vyberte pracoviště<br/>';
	echo'<select name="department" id="department">';
	echo'<option value="">-- vše --</option>'; 

	while($q->next_record()) {
	$id = $q->Record["ID"];
	echo'<option value="'.$id.'" '.$selected.'>'.$q->Record["NAME"]."</option>";
	}
	echo'</select><br/>';
	echo 'od ';

	echo '<input type="text" size="4" name="yearfrom" id="yearfrom" value="'.$yearfrom.'">';	
	echo ' do ';
	echo '<input type="text" size="4" name="yearto" id="yearto" value="'.$yearto.'">';	
	echo '</div>';
}

if ($ident)
{
  /*parametry url*/	
  $params='';  
  if (isset($department) && $department!='') {$params .= '&department=' .$department;}
  if (isset($yearfrom) && $yearfrom!='') {$params .= '$yearfrom='.$yearfrom;}
  if (isset($yearto) && $yearto!='') {$params .= '$yearto='.$yearto;}
  $params = '&department=' .$department. '&yearfrom=' . $yearfrom. '&yearto=' .$yearto;
  echo '<a href="uziti.php?ident=' . $ident . '&show=vse'.$params.'">Vše</a>&nbsp;&nbsp;&nbsp;
  <a href="uziti.php?ident=' . $ident . '&show=notnull'.$params.'">Jen použité</a>
  ';   
  $where = '';
  /* filtr */
  $first=true;
  if (isset($department) && $department!='') {$cond .='superodbor='.$department;$first=false;}
  if (isset($yearfrom) && $yearfrom!='') if($first) {$cond .=' rok > '.$yearfrom;$first=false;} else {$cond .=' AND rok > '.$yearfrom;$first=false;}
  if (isset($yearto) && $yearto!='') if($first) {$cond .=' rok < '.$yearto;$first=false;} else {$cond .=' AND rok < '.$yearto;}
  if ($show == 'notnull') if($first) {$cond .= 'pocet_uziti>0 ';} else {$cond .=' AND pocet_uziti>0';}
  if ($cond !='') $where = " WHERE ".$cond;  
  /*sql pro sestavaní výpisu*/	
  $sql = "select * from ".$uziti_array[$ident]['table_name']." " . $where . " order by pocet_uziti desc";
  $caption = $uziti_array[$ident]['nazev'];
  $GLOBALS['COLUMN_IDENT'] = $uziti_array[$ident]['ident']; 
  $count = Table(array(
           "maxnumrows"=>100,
           "caption"=>$caption,
           "sql" => $sql,
           "showdelete"=>false, 
           "showedit"=>false,
           "showinfo"=>false,	 
           "nocaption"=>false,
           "schema_file"=>".admin/table_schema_uziti.inc",
  ));
}
require(FileUp2("html_footer.inc"));