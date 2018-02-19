<?php
Function DecinKopieDokumentu($id) {
  If ((HasRole('podatelna')||HasRole('spravce')) && $GLOBALS["ODESLANA_POSTA"]=="f" && $GLOBALS["ODES_TYP"]<>"X") $res.='<a href="javascript:newZaloz(\''.$id.'\',\'2\')"><img src="' .  FileUpImage('images/add') . '" border="0" title="Zkopírovat dokument"></a>';
  IF ($GLOBALS['STATUS']<2) $res = '&nbsp;';
  if (!MaPristupKDokumentu_old($GLOBALS['REFERENT'],$GLOBALS['ID'])) $res='&nbsp;';
  return $res;
}