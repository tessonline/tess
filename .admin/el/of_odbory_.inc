<?php
function VratMultiOdbory($idcko=0,$uroven=0,$pole=array())
{
  $db = new DB_POSTA;
  if (!$idcko) $idcko=0;
  $sql="SELECT o.id as idcko,g.id,g.name
        FROM cis_posta_odbory o LEFT JOIN security_group g  ON g.id=o.id_odbor
        WHERE g.type_group<>3 AND g.public_group='1' AND g.parent_group_id=".$idcko;

  //oprava onma, 2011-09-29
  $sql="SELECT g.id,g.name FROM security_group g  WHERE g.type_group<>3 AND g.public_group='1' AND g.parent_group_id=".$idcko;

//  echo $sql;
//"SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".VratSuperOdbor()."ORDER BY g.name"
  $db->query($sql);
	$uroven++;
	while ($db->Next_Record())
	{
    $id = $db->Record['ID'];
//    $idcko = $db->Record['IDCKO'];
    $idcko = $db->Record['ID'];
		$name=$db->Record['NAME'];
		for ($a=1; $a<$uroven; $a++) 
      $pole[$idcko].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
//	  $pole[$id].='<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';
	  $pole[$idcko].=$name;
		$pole=VratMultiOdbory($db->Record['ID'], $uroven,$pole);
	} 
	return $pole;
}

function nbspPrefix($depth) {
  $prefix = "";
  for ($i=0;$i<$depth;$i++) {
    $prefix.="&nbsp;&nbsp;&nbsp;&nbsp;&nbsp";
  }
  return $prefix;
}

function addItemToList($polex,$item) {
  $depth = $item['DEPTH'];

  $parent_id = $item['ID2'];
  $item['DESCRIPTION'] = nbspPrefix($depth).$item['DESCRIPTION'];
  $item['NAME'] = nbspPrefix($depth).$item['NAME'];
  $item['NAZEV'] = nbspPrefix($depth).$item['NAZEV'];
//    $item['DESCRIPTION'] = $this->nbspPrefix($depth).$item['DESCRIPTION'];
  $depth++;
  $GLOBALS['SPIS_UZLY'][] = $item;
  foreach ($polex as $item) {
    if (($item['DEPTH'] == $depth)&&($item['PARENT_GROUP_ID']==$parent_id)) {
      addItemToList($polex,$item);
    }
  }
}


function VratSpisUzly($parent_group_id=0,$uroven=0,$pole=array(),$add_abbr=false)
{
  $db = new DB_POSTA;
  if (!$parent_group_id) $parent_group_id=0;

  $sql = "WITH RECURSIVE t AS (SELECT id,parent_group_id, description, name, pracoviste, 0 depth, 0 FROM security_group WHERE  parent_group_id = ".$parent_group_id." and type_group = 1"
      ." UNION ALL SELECT g.id,g.parent_group_id,g.description, g.name, g.pracoviste, t.depth+1,0 FROM security_group g"
      ." JOIN t    ON g.parent_group_id = t.id)"
      ." SELECT cpo.id, cpo2.zkratka, tt.description,tt.name,cpo.aktivni,tt.depth,tt.id as id2,tt.parent_group_id,cpo.id_odbor  FROM t tt"
      ." LEFT JOIN cis_posta_odbory cpo ON tt.id=cpo.id_odbor"
      ." LEFT JOIN cis_posta_odbory cpo2 ON tt.pracoviste=cpo2.id_odbor"              
      ." WHERE cpo.id is not null and tt.description is not null and tt.description != '' ORDER BY cpo.poradi,tt.id";

  $db->query($sql);
  $polex = array();
  while ($db->Next_Record()) {
    $polex[] = $db->Record;
  }
  $GLOBALS['SPIS_UZLY'] = array();
  foreach ($polex as $item) {
    if ($item['DEPTH'] == 0)
    addItemToList($polex,$item);
  }
  $polex = array();
  foreach ($GLOBALS['SPIS_UZLY'] as $val) {
    $idcko = $val['ID'];
    $polex[$idcko] = ($add_abbr&&$val['ZKRATKA']!="") ? $val['NAME']." (".$val['ZKRATKA'].")" : $val['NAME'];
    $GLOBALS['AKTIVNI_SPISUZLY'][$idcko] = $val['AKTIVNI'];
//      $GLOBALS['MAP_ODBOR'][$val['ID_ODBOR']] = $idcko;
    $GLOBALS['MAP_ODBOR'][$idcko] = $val['ID_ODBOR'];

  }
	return $polex;
}

function VratNadrizeneOdbory($idcko=0,$uroven=0,$pole=array()) {
  $db = new DB_POSTA;
  if (!$idcko) $idcko=0;
  $sql="SELECT g.id,g.name,g.parent_group_id
        FROM security_group g  WHERE g.type_group<>3 AND g.public_group='1' AND g.id=".$idcko;
//"SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".VratSuperOdbor()."ORDER BY g.name"
//  echo $sql.'<br/>';
  $db->query($sql);
	$uroven++;
	if ($db->Num_Rows()==0) return $pole;
	while ($db->Next_Record())
	{
    $id = $db->Record['ID'];
    $idcko = $db->Record['ID'];
		$name=$db->Record['NAME'];
		for ($a=1; $a<$uroven; $a++) 
      $pole[$idcko].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
//	  $pole[$id].='<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';
	  $pole[$idcko].=$name;
		$pole=VratNadrizeneOdbory($db->Record['PARENT_GROUP_ID'], $uroven,$pole);
	} 
	return $pole;
}

function VratVecneSkupiny($idcko=0,$uroven=0,$pole=array(), $where = array()) {
	$db = new DB_POSTA;
	if ($where['jen_viditelne']) $append = " and show_vs=1 ";
	if ($where['jen_vs']) $append .= " and typ='1' ";
	if ($where['jen_kody']) $append .= " and typ='2' ";
	if ($where['jen_aktivni']) $append .= " and aktivni=1 ";
	if ($where['jen_main_id']) $append .= " and main_id=" . $where['jen_main_id'];
	if (!$idcko) $idcko="0 or nadrazene_id is null";
	$sql="SELECT * from cis_posta_skartace where 1=1  $append
        AND (nadrazene_id=".$idcko.") order by priorita, id asc";
	$db->query($sql);
	$uroven++;
	while ($db->Next_Record())	{
	    $uroven_text = '';
		$idcko = $db->Record['ID'];
		if ($db->Record['NAZEV']) $name = $db->Record['KOD'] . ' ' . $db->Record['NAZEV'];
		if ($db->Record['TEXT']) $name = $db->Record['KOD'] . ' ' . $db->Record['TEXT'];
		for ($a=1; $a<$uroven; $a++)
			$uroven_text.='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';

//			$pole[$idcko].=$name;
        $pole[$idcko]['ID'] = $idcko;
        $pole[$idcko]['JID'] = $GLOBALS['CONFIG']['ID_PREFIX'] . 'VS' . $idcko;
        $pole[$idcko]['KOD'] = $db->Record['KOD'];
        $pole[$idcko]['TYP'] = $db->Record['TYP'];
        $pole[$idcko]['CELY_NAZEV'] = $uroven_text . $name;
        $pole[$idcko]['TEXT'] = $db->Record['TEXT'];
        $pole[$idcko]['SKAR_ZNAK'] = $db->Record['SKAR_ZNAK'];
        $pole[$idcko]['DOBA'] = $db->Record['DOBA'];
        $pole = VratVecneSkupiny($db->Record['ID'], $uroven,$pole, $where);
	}
	return $pole;
}

function VratSpisUzly2($idcko=0,$uroven=0,$pole=array())
{
  $db = new DB_POSTA;
  if (!$idcko) $idcko=0;
  $sql="SELECT o.id as idcko,g.id,g.name, o.zkratka, g.parent_group_id,o.aktivni
        FROM cis_posta_odbory o LEFT JOIN security_group g  ON g.id=o.id_odbor
        WHERE g.type_group<>3 AND g.public_group='1' AND g.parent_group_id=".$idcko." order by o.poradi,g.id";
//"SELECT DISTINCT o.id,g.name FROM cis_posta_odbory o LEFT JOIN security_group g ON g.id=o.id_odbor WHERE g.parent_group_id=".VratSuperOdbor()."ORDER BY g.name"
  $db->query($sql);
	$uroven++;
	while ($db->Next_Record())
	{
//    $idcko = $db->Record['IDCKO'];
    $idcko = $db->Record['ID'];
//     if ($db->Record['PARENT_GROUP_ID']==0)
//   		$name = "<b>".$db->Record['ZKRATKA']." - ".$db->Record['NAME']."</b>";
//     else
  		$name = $db->Record['NAME'];
    if ($uroven == 1) $pole[] = '<optgroup label="'. $name .'">';

		for ($a=1; $a<$uroven; $a++)
      $pole[$idcko].='&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
//	  $pole[$id].='<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';
    $pole[$idcko].=$name;
//    $pole[$idcko]=$db->Record['AKTIVNI'];
    $GLOBALS['AKTIVNI_SPISUZLY'][$idcko] = $db->Record['AKTIVNI'];
		$pole=VratSpisUzly2($db->Record['ID'], $uroven,$pole);
    if ($uroven == 1) $pole[] = '</optgroup>';

	}
	return $pole;
}
