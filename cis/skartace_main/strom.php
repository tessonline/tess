<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require(FileUp2('.admin/config.inc'));
require(FileUp2('html_header_full.inc'));

NewWindow(array("fname" => "AgendaSpis", "name" => "AgendaSpis", "header" => true, "cache" => false, "window" => "edit"));

echo "
<script type=\"text/javascript\">
<!--
  function edit_ (id) {
    NewWindowAgendaSpis('../skartace/edit.php?edit&EDIT_ID='+id);
  }
  function insert_ (id) {
    NewWindowAgendaSpis('../skartace/edit.php?insert&NADRAZENE_ID='+id);
  }
//-->
</script>
<p>
</p>
";

$main_id = $GLOBALS['ID'];

function ShowStromVS($idcko = 0, $uroven = 0, $main_id)
{
  $barvy = array(
    '',
    '#000000',
    '#0000FF',
    '#FF0000',
    '#11BB11',
    '#000000'
  );
  $org_obj = LoadClass('EedUser',0);

  $db = new DB_POSTA;
  $q = new DB_POSTA;
  if (!$idcko) $idcko="0 or nadrazene_id is null";
  $sql="SELECT id,kod || ' ' || text as NAME
        FROM cis_posta_skartace where typ='1'
        AND nadrazene_id=".$idcko .' order by id asc';
  $db->query($sql);
	$uroven++;
	while ($db->Next_Record())
	{
    $id = $db->Record['ID'];
		$name=$db->Record['NAME'];
		for ($a=1; $a<$uroven; $a++) 
      echo '<img src="'.FileUpURL('images/editor/tree_vertline.gif').'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	  echo '<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';

      echo '<a href="javascript:edit_('.$db->Record['ID'].')"><font face=verdana size=2 color="'.$barvy[$uroven].'"><b>'.$name.'</b></font></a><BR />';
      unset($GLOBALS['ID']);
      
      for ($a=1; $a<$uroven; $a++)
      	echo '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<table width="90%" align=center><tr><td>';
      
      
      $count=Table( 
      	array(
      		"showaccess" => true,
      			"setvars"=>true,
      			'nocaption' => true,
      			'showcount' => false,
      			'emptyoutput' => true,
      			"agenda"=>'POSTA_CIS_SKARTACE',
      			'appendwhere' => 'and nadrazene_id=' . $db->Record['ID'].' and typ=2',
      			"tablename"=>"skartace_plan",
      			"unsetvars"=>true));
      	echo '</td></tr></table>';
      	ShowStromVS($db->Record['ID'], $uroven, $main_id);
	}
}
$count=Table(array("showaccess" => true,"setvars"=>true,"showself"=>true, "tablename"=>"skartace_plan","unsetvars"=>array("except"=>array('ID'))));


ShowStromVS(0, 0, $main_id);
NewWindow(array("fname"=>"", "name"=>"pf_parc_new", "header"=>true, "cache"=>false, "window"=>"edit"));

echo "<form name=\"frm_pf_parc\" method=\"GET\">\n";
echo "<input type=\"submit\" class='btn' value=\"Nový záznam\" onClick=\"javascript:NewWindow('".GetAgendaPath("POSTA_CIS_SKARTACE",false,true)."/edit.php?insert&MAIN_ID=".$main_id."');return false;\">\n";


require(FileUp2('html_footer.inc'));
