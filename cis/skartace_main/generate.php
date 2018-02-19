<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("interface/.admin/soap_funkce.inc"));

$a = new DB_POSTA;
$c = new DB_POSTA;
$d = new DB_POSTA;
$q = new DB_POSTA;

function Text($str) {
  $str = TxtEncoding4Soap($str);
  if (strlen($str) == 0) $str = 'NULL';
  return $str;
}

$xmlstr = <<<XML
<?xml version='1.0'?>
<SpisovyPlan xmlns:nsesss="http://www.mvcr.cz/nsesss/v2" xmlns:dc="http://purl.org/dc/elements/1.1/" xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.mvcr.cz/nsesss/v2 D:\spis_sluzba\spis_plan\nsesss-plan.xsd" >
</SpisovyPlan>

XML;


$doc = @new SimpleXMLElement($xmlstr);



function VratVecneSkupiny($idcko=0,$uroven=0, $plan, $where = array()) {
	$db = new DB_POSTA;
	$db_x = new DB_POSTA;
	if (!$idcko) $idcko="0 or nadrazene_id is null";
	if ($where['main_id']) $append=" AND main_id = " . $where['main_id'];
	if ($idcko == 1) $idcko="0 or nadrazene_id is null";
	$sql="SELECT * from cis_posta_skartace where typ='1' $append AND (nadrazene_id=".$idcko.") order by id asc";
	
	if ($where['jde_o_id']) $sql="SELECT * from cis_posta_skartace where typ='1' $append AND (id=".$idcko.") order by id asc";
	unset($where['jde_o_id']);
	$db->query($sql);
	$uroven++;
	while ($db->Next_Record())	{
	
   	   $skupina = $plan->addChild('PlanVecnaSkupina');
		 $skupina->addAttribute('ID',$db->Record['ID']);
		
		$skupina->addChild('Uroven', $uroven);
		$evidencni = $skupina->addChild('EvidencniUdaje');
		    $ident = $evidencni->addChild('Identifikator', $db->Record['ID']);
		    $ident->addAttribute('zdroj','TMAPESS');
			$popis = $evidencni->addChild('Popis', $db->Record['TEXT']);
			$puvod = $evidencni->addChild('Puvod');
			  $puvod->addChild('DatumVytvoreni', $db->Record['LAST_DATE']);
		    $trideni =  $evidencni->addChild('Trideni');
		      $trideni->addChild('JednoduchySpisovyZnak', $db->Record['KOD']);
		      $trideni->addChild('PlneUrcenySpisovyZnak', $db->Record['KOD']);
		      $counter = 1;
		$sql="SELECT * from cis_posta_skartace where typ='2' AND (nadrazene_id=".$db->Record['ID'].") order by id asc";
		$db_x->query($sql);
		while ($db_x->Next_Record())	{
		  	$znak = $skupina->addChild('PlanVecnaSkupina');
		  	$znak->addAttribute('ID',$db_x->Record['ID']);
		  	 
		  	$evidencni = $znak->addChild('EvidencniUdaje');
			  	$ident = $evidencni->addChild('Identifikator', $db_x->Record['ID']);
				$ident->addAttribute('zdroj','TMAPESS');
				$popis = $evidencni->addChild('Popis', $db_x->Record['TEXT']);
			  	$puvod = $evidencni->addChild('Puvod');
    			  $puvod->addChild('DatumVytvoreni', $db_x->Record['LAST_DATE']);
			  	$trideni =  $evidencni->addChild('Trideni');
			  	  $trideni->addChild('JednoduchySpisovyZnak', $counter);
			  	  $trideni->addChild('PlneUrcenySpisovyZnak', $db_x->Record['KOD']);
			  	$vyrazovani =  $evidencni->addChild('Vyrazovani');
			  	  $SkartacniRezim =  $vyrazovani->addChild('SkartacniRezim');
			  	    $SkartacniRezim->addChild('Identifikator', $db_x->Record['ID']);
			  	    $SkartacniRezim->addChild('Nazev', $db_x->Record['KOD']);
			  	    $SkartacniRezim->addChild('Oduvodneni', 'Dle zákona');
			  	    $SkartacniRezim->addChild('SkartacniZnak', $db_x->Record['SKAR_ZNAK']);
			  	    $SkartacniRezim->addChild('SkartacniLhuta', $db_x->Record['DOBA']);
			  	    $SkartacniRezim->addChild('SpousteciUdalost', 'Vyřízení dokumentu,Uzavření spisu');
			  	    
			 $counter ++;  	
		}		

		$skupina = VratVecneSkupiny($db->Record['ID'], $uroven, $skupina, $where);
 
	}
	return $plan;
}


if ($ID) {
  $doc = VratVecneSkupiny($ID, 0, $doc, array('jde_o_id' => true));
}
else
  $doc = VratVecneSkupiny(0, 0, $doc, array('main_id' => $MAIN_ID));

  
$vysledek = $doc->asXML ();
$content_type = "application/xml";
header("Content-type: $content_type");
header("Content-Disposition: attachment; filename=\"spis_plan.xml\"");

echo html_entity_decode($vysledek, 0, 'UTF-8');

