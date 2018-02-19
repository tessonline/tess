<?php 
$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$EedUser = LoadClass('EedUser', $USER_INFO['ID']);
$unit_id = $EedUser->odbor_id;

if (!HasRole('spravce')&&!HasRole('access_all')) {
  //omezeni superodbor
  $where2.=" AND ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() .") ";
  if (!HasRole('lokalni-spravce')) {
    //omezeni na odbor
    $uzel_id = VratOdbor();
    $where2.=" AND ODBOR IN (". $uzel_id.") ";
    if (!HasRole('spravce-odbor-sablony')) {
      //omezeni na referenta
      //$where2.= " AND (referent=" . $USER_INFO['ID'] . " OR (odbor in (" . $uzel_id . ") and referent is null))";
    }
  }
}

if (HasRole('access_all')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
  if ($GLOBALS['omez_zarizeni']) $where2.= " AND id_superodbor=" . $GLOBALS['omez_zarizeni']; else 
    $where2.= " AND id_superodbor is null";
} 