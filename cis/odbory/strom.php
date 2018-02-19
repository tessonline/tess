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
    NewWindowAgendaSpis('./edit.php?edit&EDIT_ID='+id);
  }
  function insert_ (id) {
    NewWindowAgendaSpis('./edit.php?insert&ID_ODBOR='+id);
  }
//-->
</script>
<p>
<span class='text'>Pozn: šedivě je uvedena org. struktura, která není vedena jako spisový uzel. Barevně jsou uvedeny unity, které jsou již jako spisové uzly uvedeny.
Kliknutím na název založíte nový spisový uzel nebo opravíte stávající.<br/>U stávajícího lze opravit zkratku unity případně lze nastavit, které spisové znaky daná unita uvidí.
</span></p>
";

function ShowStrom($idcko = 0, $uroven = 0)
{
  $barvy = array(
    '',
    '#00AAAA',
    '#0000FF',
    '#FF0000',
    '#11BB11',
    '#000000'
  );
  $org_obj = LoadClass('EedUser',0);

  $db = new DB_DEFAULT;
  $q = new DB_POSTA;
  $sql="SELECT id,name
        FROM security_group 
        WHERE type_group<>3 AND public_group='1' AND parent_group_id=".$idcko;
  $db->query($sql);
	$uroven++;
	while ($db->Next_Record())
	{
    $id = $db->Record['ID'];
		$name=$db->Record['NAME'];
		for ($a=1; $a<$uroven; $a++) 
      echo '<img src="'.FileUpURL('images/editor/tree_vertline.gif').'">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	  echo '<img src="'.FileUpURL('images/editor/tree_split.gif').'">&nbsp;';

    $sqla="SELECT * FROM cis_posta_odbory where id_odbor=".$id;
    $q->query($sqla);
    if ($q->Num_Rows()>0)
    {
      $q->Next_Record();
      echo '<a href="javascript:edit_('.$q->Record['ID'].')"><font face=verdana size=2 color="'.$barvy[$uroven].'"><b>'.$q->Record['ZKRATKA'].' - '.$name.'</b></font></a><BR />';
    }
    else
      echo '<a href="javascript:insert_('.$id.')"><font face=verdana size=2 color="#CCCCCC"><b>'.$name.'</b></font></a><BR />';
 		ShowStrom($db->Record['ID'], $uroven);
	}
}


$pracoviste = 0;
if (HasRole('lokalni-spravce')) {
  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
  $pracoviste = $USER_INFO['PRACOVISTE']; 
  
}

ShowStrom($pracoviste);

require(FileUp2('html_footer.inc'));
