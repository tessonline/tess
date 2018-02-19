<?php
include_once(FileUp2('.admin/oth_funkce.inc'));


function UkazRucne($ID) {
  global $qAdr;
  $sqlZZ = "SELECT * FROM posta_adresati where
  odesl_prijmeni like '" . $GLOBALS['ODESL_PRIJMENI'] . "' AND
  odes_typ like '" . $GLOBALS['ODES_TYP'] . "' ";
  if ($GLOBALS['ODESL_JMENO']) $sqlZZ .= " AND odesl_jmeno like '%" . $GLOBALS['ODESL_JMENO'] . "%'"; else $sqlZZ.=" AND odesl_jmeno is null";
  if ($GLOBALS['ODESL_ULICE']) $sqlZZ .= " AND odesl_ulice like '%" . $GLOBALS['ODESL_ULICE'] . "%'"; else $sqlZZ.=" AND odesl_ulice is null";
  if ($GLOBALS['ODESL_CP']) $sqlZZ .= " AND odesl_cp like '%" . $GLOBALS['ODESL_CP'] . "%'"; else $sqlZZ.=" AND odesl_cp is null";
  if ($GLOBALS['ODESL_POSTA']) $sqlZZ .= " AND odesl_posta like '%" . $GLOBALS['ODESL_POSTA'] . "%'"; else $sqlZZ.=" AND odesl_posta is null";
  if (!$qAdr) $qAdr = new DB_POSTA;
  $qAdr->query($sqlZZ);
   if ($qAdr->Num_Rows()>0) {
    $qAdr->Next_Record();
//    $res .= '<br/><b>'.$qAdr->Record['ODESL_PRIJMENI'].' '.$qAdr->Record['ODESL_JMENO'];
    $res .= '<br/><b>'.UkazAdresu($qAdr->Record['ID'],', ', 'posta_adresati');
    $res .= '</b>';
    return $res;
  }
  else return '';
}
