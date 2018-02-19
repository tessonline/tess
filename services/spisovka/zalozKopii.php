<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2('.admin/upload_fce_.inc'));
require_once(FileUp2(".admin/oth_funkce.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/zaloz.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
@include_once(FileUp2('.admin/db/db_upload.inc'));
include_once(FileUp2("/interface/.admin/soap_funkce.inc"));
require_once(FileUp2("/interface/.admin/upload_funkce.inc"));

EedTools::MaPristupKDokumentu($ID, 'vytvoreni kopie');
if ($GLOBALS['zalozeni']==2)
  $NOVEID=ZalozNovyDokument($ID,0,2);
elseif ($GLOBALS['zalozeni']==3)
  $NOVEID=ZalozNovyDokument($ID,0,3);
elseif ($GLOBALS['zalozeni']==4)
  $NOVEID=ZalozNovyDokument($ID,0,4);
else
  ZalozNovyDokument($ID);

$GLOBALS['ID'] = $ID;
$GLOBALS['noveID'] = $NOVEID;
reset ($GLOBALS["CONFIG_POSTA"]["PLUGINS"]);
foreach($GLOBALS["CONFIG_POSTA"]["PLUGINS"] as $plug_name => $plug) {
  if ($plug['enabled']){
    $file = FileUp2('plugins/'.$plug['dir'].'/services/spisovka/zalozKopii_end.php');
		if (File_Exists($file)) include($file);
  }
}


echo '
<script language="JavaScript" type="text/javascript">
  window.parent.location.reload();
  window.close();
//  window.close();
</script>
';
