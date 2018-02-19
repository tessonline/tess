<?php
function UkazSchvalovani($id) {
  global $USER_INFO;
  $res .= '<a href="javascript:newVedouci('.$id.')">'.VratImgKeSchvalovani($id).'</a>';
  if ($GLOBALS['STATUS']<2) $res = '';

  if (!MaPristupKDokumentu_table($GLOBALS['REFERENT'],$GLOBALS['ID'])) {
    if (_JsemNaRade($GLOBALS['ID'], $USER_INFO['ID']))
      echo '';
    else
      $res='&nbsp;';
  }
  return $res;
}

echo "
  <script>
  <!--

  function newVedouci(id) {
    NewWindowAgenda('plugins/schvalovani/edit.php?insert&POSTA_ID='+id);
  }

 //-->
</script>
";


