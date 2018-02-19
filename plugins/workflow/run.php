<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

if ($GLOBALS['ID_WORKFLOW']==2) {
  $GLOBALS['PROMENNA'] = $GLOBALS['TYPSCHVALENI'];
  $GLOBALS['HODNOTA'] = $GLOBALS['SCHVALUJICI_ID'];
}

if ($GLOBALS['ID_WORKFLOW']==3) {
  $GLOBALS['PROMENNA'] = $GLOBALS['NOVA_POLOZKA'];
  $GLOBALS['HODNOTA'] = $GLOBALS['DATOVY_TYP'];
}

Run_(array("showaccess"=>true,"outputtype"=>3));

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
//  window.close();
</script>
';

require_once(Fileup2("html_footer.inc"));  