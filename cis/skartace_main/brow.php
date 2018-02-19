<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
IF ($GLOBALS["TEXT"]) {$GLOBALS["TEXT"]="*".$GLOBALS["TEXT"]."*";}

$filterWhere = "";
if ($GLOBALS['SKARTACE_NAZEV']) $filterWhere.= " and text like '%".$GLOBALS['SKARTACE_NAZEV']."%'";
if ($GLOBALS['SKARTACE_SKUPINA']) $filterWhere.= " and nadrazene_id = '".$GLOBALS['SKARTACE_SKUPINA']."'";
if ($GLOBALS['SKARTACE_AKTIVNI']) $filterWhere.= " and aktivni>0";
if ($GLOBALS['SKARTACE_NEAKTIVNI']) $filterWhere.= " and (aktivni=0 or aktivni is null)";
if ($GLOBALS['SKARTACE_ZNAK']) $filterWhere.= " and SKAR_ZNAK like '".$GLOBALS['SKARTACE_ZNAK']."%' AND SKAR_ZNAK!='' AND SKAR_ZNAK IS NOT NULL";
if ($GLOBALS['SKARTACE_LHUTA']) $filterWhere.= " and DOBA = '".$GLOBALS['SKARTACE_LHUTA']."'";
// var_dump($filterWhere, strlen($filterWhere));
if(strlen($filterWhere)<1) {
  $count=Table(array("showaccess" => true,"setvars"=>true,"showself"=>true, "tablename"=>"skartace_plan","unsetvars"=>array("except"=>array('ID'))));
}
function VratVecneSkupiny($idcko=0,$uroven=0,$pole=array(), $where = array()) {
	$db = new DB_POSTA;
	$append = "";
	if ($where['jen_viditelne']) $append = " and show_vs=1 ";
	if ($where['main_id']) $append = " and main_id= " . $where['main_id'];
	if ($where['jid']) $append = " and id=".$where['jid'];
	if (!$idcko) $idcko="AND (nadrazene_id=0 or nadrazene_id is null)";
	else $idcko = " AND nadrazene_id=".$idcko;
	if ($where['filter']) {
	  $append = $where['filter'];
	  $idcko = "";
	}
	$sql="SELECT * from cis_posta_skartace where 1=1 $append $idcko
	 order by priorita, id asc";
	$db->query($sql);
	$uroven++;
	while ($db->Next_Record())	{
		$idcko = $db->Record['ID'];
		$name = $db->Record['KOD'] . ' ' . $db->Record['TEXT'];
		for ($a=1; $a<$uroven; $a++)
//			$pole[$idcko].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
			$pole[$idcko]['TEXT'].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';

      $pole[$idcko]['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'VS' . $idcko;
			$pole[$idcko]['ID'].=$idcko;
			$pole[$idcko]['KOD'].= $db->Record['KOD'];
			$pole[$idcko]['TYP'].= $db->Record['TYP'];
			$pole[$idcko]['SKAR_ZNAK'].= $db->Record['SKAR_ZNAK'];
			$pole[$idcko]['DOBA'].= $db->Record['DOBA'];
			$pole[$idcko]['NADRAZENE_ID'].= $db->Record['NADRAZENE_ID'];
			$pole[$idcko]['TEXT'].=$name;
			if(!$where['filter']) {
			  $pole=VratVecneSkupiny($db->Record['ID'], $uroven,$pole, $where);
			}
	}
	return $pole;
}


If (($count==1 && $GLOBALS['ID']) || strlen($filterWhere)>1)
{
  echo "<hr>\n";
  
  $where='AND MAIN_ID='.$GLOBALS["ID"];
  
  //$params = array("agenda"=>"ZP_ARCHIV_PARCELA", "setvars"=>true, "tablename"=>"PARCELY","caption"=>"Dotčené parcely", "tablename"=>"ZP_ARCHIV_PARCELA", "nopaging"=>true, "showdelete"=>true, "showedit"=>true,"appendwhere"=>$where,  "mapsupport"=>true,"showmap"=>true
  //);
  $main_id=$GLOBALS['ID'];
  unset($GLOBALS["ID"]);
//  $sql='select * from cis_posta_skartace where main_id='.$GLOBALS['ID'];

$data = VratVecneSkupiny(0, 0, array(), array('main_id' => $main_id, 'jid' => $GLOBALS["JID"], 'filter' => $filterWhere));

include_once $GLOBALS["TMAPY_LIB"]."/db/db_array.inc";
$db_arr = new DB_Sql_Array;
$db_arr->Data = $data;

  if($SHOWALL) {
    echo '<a class="btn" href="index.php?frame&ID='.$main_id.'" target="_top">Normální režim zobrazení</a>';
  }
  
	$count2 = Table(
			array(
					"db_connector" => &$db_arr,
					"showaccess" => true,
          "tablename" => "znaky",
					"caption" => "Načtené údaje",
					"agenda"=>'POSTA_CIS_SKARTACE',
					"showedit"=>true,
					"showdelete"=>true,
					"setvars" => true,
					"showinfo"=>false,
					"showcount"=>false,
			    "page_size"=>($SHOWALL == 1 ? 1000 : 25),
			    "showself"=>true,
			    "showselfurl"=>GetAgendaPath("POSTA", 0, 1).'/index.php?frame&VYHLEDAVANI=1&ID_X=\'...JID',
          "showselftitle" => "Zobrazit dokumenty v EED",
			    "showselftarget"=>"EED",
					//    "schema_file"=>".admin/table_schema_certifikat.inc"
			)
			);
	if($count2 == 1) {
	  
	}

  echo "<form name=\"frm_pf_parc\" method=\"GET\">\n";
  echo "<input type=\"submit\" class='btn' value=\"Nový záznam\" onClick=\"javascript:NewWindow('".GetAgendaPath("POSTA_CIS_SKARTACE",false,true)."/edit.php?insert&MAIN_ID=".$main_id."');return false;\">\n";
  if($SHOWALL) {
    echo '<a class="btn" href="index.php?frame&ID='.$main_id.'" target="_top">Normální režim zobrazení</a>';
  }
  else {
    echo '<a class="btn" href="index.php?frame&ID='.$main_id.'&SHOWALL=1" target="_top">Zobrazit všechny záznamy</a>';
  }
  echo "</form>";          
}


  
require(FileUp2("html_footer.inc"));
?>
