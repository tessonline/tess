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


if ($GLOBALS['zalozeni']==2)
  $NOVEID=ZalozNovyDokument($ID,0,2);
elseif ($GLOBALS['zalozeni']==3)
  $NOVEID=ZalozNovyDokument($ID,0,3);
else
  ZalozNovyDokument($ID);

	
if ($GLOBALS["otoc"]==1)
echo '
<script language="JavaScript" type="text/javascript">
<!--
  alert("soubory zkopírovány");
  window.close();
//-->
</script>
';
elseif ($GLOBALS['zalozeni']==2)
{
echo '
<script language="JavaScript" type="text/javascript">
<!--
  function NewWindowEditevidencepisemnosti(script) {
    if (window.name == \'Edit\') {
      window.location.href = script;
    } else {
      newwindow = window.open(script, \'Edit\',\'height=570,width=790,left=1,top=1,scrollbars,resizable\');
      newwindow.focus();
    }
  }
  function edit_evidencepisemnosti (id) {
    NewWindowEditevidencepisemnosti(\'/ost/posta/edit.php?edit&EDIT_ID=\'+id);
  }
  edit_evidencepisemnosti('.$NOVEID.');
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//-->

</script>
';  
  
} 
else
echo '
<script language="JavaScript" type="text/javascript">
<!--
  document.location.href="brow'.$prefix.'.php";
//-->
</script>
';
