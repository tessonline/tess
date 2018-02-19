<?php

require("tmapy_config.inc");
$GLOBALS["PROPERTIES"]["DEFAULT_LANG"]='cz_utf-8';
require(FileUp2("html_header_full.inc"));
include_once(FileUp2(".admin/properties.inc"));
include_once(FileUp2(".admin/security_name.inc"));

//skript ktery se vola pri zmene dokumentu...

$q = new DB_POSTA;

if (!$DRUH_DOC || $DRUH_DOC == '') return false;
$sql = 'SELECT lhuta, skartace_id FROM cis_posta_typ WHERE id = ' . $DRUH_DOC; //
$q->query($sql);
$q->Next_Record();
$skartaceId = $q->Record['SKARTACE_ID'];
$lhuta = $q->Record['LHUTA'] ? $q->Record['LHUTA'] : 0;

if ($lhuta=='' || $lhuta==0) $lhuta=30; //


echo '
<script>
';

if ($lhuta > 0)
  echo '    parent.document.frm_edit.LHUTA.value=\''.$lhuta.'\';
';

if ($skartaceId > 0)
  echo '    parent.document.frm_edit.SKARTACE.value=\''.$skartaceId.'\';
      var text = $("#SKARTACE option[value=\''. $skartaceId.'\']", parent.document).text();
      $("#select2-SKARTACE-container", parent.document).prop("title",text);
      $("#select2-SKARTACE-container", parent.document).text(text);
			$("#SKARTACE",parent.document).trigger("change");
';
else
  echo '    parent.document.frm_edit.SKARTACE.value=\'\';
';

echo '
</script>
';

