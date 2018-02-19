<?php
require('tmapy_config.inc');
$QUERY_STRING = "insert";
include_once FileUp2('.admin/edit_.inc');
include_once($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
include_once(FileUp2('./ost/posta/.admin/javascript.inc'));
include_once(FileUp2('.admin/el/of_select_.inc'));

//echo '<p><span class="caption">'.$GLOBALS['RSTR_IMPORT']['import_nastaveni'].'</span></p>';
$log = 'Rucni nastaveni promennych';
ZapisLog($log);

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();

$GLOBALS['REFERENT'] = $USER_INFO['ID'];

$is_restart = EedImport::isRestart($id);

if ($is_restart)  {
  if (!EedImport::db2glob($id)) {
    $sql =  "select * from posta where id = (select id_posta from posta_hromadny_import_posta where id_import = ".$GLOBALS['id']." limit 1)";
    $q->query($sql);
    $q->Next_Record();
    if ($q->Record['ID']) {
      $GLOBALS['VEC'] = $q->Record['VEC'];
      $GLOBALS['SKARTACE'] = $q->Record['SKARTACE'];
      $GLOBALS['DOPORUCENE'] = $q->Record['DOPORUCENE'];
      $GLOBALS['VLASTNICH_RUKOU'] = $q->Record['VLASTNICH_RUKOU'];
      $GLOBALS['TYP_POSTY'] = $q->Record['TYP_POSTY'];
      $GLOBALS['AGENDA_DOKUMENTU'] = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
      $GLOBALS['OBALKA_NEVRACET'] = $q->Record['OBALKA_NEVRACET'];
      $GLOBALS['OBALKA_10DNI'] = $q->Record['OBALKA_10DNI'];
    }
  } else {
    $GLOBALS['AGENDA_DOKUMENTU'] = VratAgenduDokumentu($GLOBALS['TYP_POSTY']);
  }
}

Form_(array(
  'caption' => '',
  'target' => '',
  'action'=>'import2.php',
  'showaccess' => true,
  'myform_schema' => '.admin/form_schema_params.inc',
  'noshowclose' => true,
));

$sql = 'update ' . $GLOBALS['PROPERTIES']['AGENDA_TABLE'] .' set stav=2,last_date=\''.$LAST_DATE.'\',last_time=\''.$LAST_TIME.'\',last_user_id='.$LAST_USER_ID.' where tid=' . intval($id);
$log = 'SQL: ' . $sql;
ZapisLog($log);
$q->query($sql);

/*if ($is_restart)  {
  echo "<script language=\"JavaScript\" type=\"text/javascript\">
        window.location.href='import2.php?id=".$id."&dalsi_krok=1';
        </script>";
}*/
?>
<script type="text/javascript">
	TypObalky(this,'1');
	var agenda = document.getElementById('AGENDA_DOKUMENTU');
	var typ_posty = "<?php  echo $GLOBALS['TYP_POSTY']; ?>";
	UkazTypPosty(agenda,'TYP_POSTY',typ_posty,'',0,typ_posty);
</script>