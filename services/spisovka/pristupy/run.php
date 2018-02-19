<?php
require('tmapy_config.inc');
require_once(FileUp2('.admin/run2_.inc'));
require_once(FileUp2('.admin/oth_funkce.inc'));
require_once(FileUp2('.admin/status.inc'));
require_once(FileUp2('.admin/zaloz.inc'));
include_once(FileUp2('/interface/.admin/soap_funkce.inc'));
require_once(FileUp2('/interface/.admin/upload_funkce.inc'));
require_once(Fileup2('html_header_title.inc'));
$q=new DB_POSTA;

if (!$DELETE_ID) {


  $sql = "delete from posta_pristupy where spis_id=(SELECT spis_id from posta_pristupy where id=".$GLOBALS['EDIT_ID'].")";

//$sql = "delete from posta_pristupy where access='$GLOBALS[ACCESS]'  and odbor=$GLOBALS[ODBOR] and posta_id in ($pid)";
if ($GLOBALS[PREV_REFERENT]!="")
  $sql.= " and referent=$GLOBALS[PREV_REFERENT]";
  else
    $sql.= " and odbor=$GLOBALS[PREV_ODBOR] and referent is null";
  
  //  if (($GLOBALS['EDIT_ID']>0)&&($GLOBALS['RANGE'] !="V")) $sql.= " AND id!=".$GLOBALS['EDIT_ID'];
    
    
if ($GLOBALS['EDIT_ID']>0 || $GLOBALS['DELETE_ID'])
$q->query($sql);
    

    
  
  $cj_obj = LoadClass('EedCj',$GLOBALS['POSTA_ID']);
  $pid_arr = $cj_obj->GetDocsInCj($GLOBALS['POSTA_ID']);
  $pid = implode(',',$pid_arr);
  $GLOBALS['SPIS_ID'] = $GLOBALS['POSTA_ID'];
      
  if ($GLOBALS['RANGE'] =="V") {
    foreach ($GLOBALS['SELECT_IDvybrane'] as $id) {
      if ($GLOBALS['REFERENT']=="") $GLOBALS['REFERENT'] = "null";
      //$referent = $GLOBALS['REFERENT'];
      unset($GLOBALS['ID']);
      unset($GLOBALS['EDIT_ID']);
      $GLOBALS['POSTA_ID'] = $id;
      $GLOBALS['SPIS'] = 0;
      $edit_id = Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
      
    /*  $sql = "INSERT INTO posta_pristupy (posta_id, access, spis, odbor, referent) VALUES ($id,'$GLOBALS[ACCESS]',0,$GLOBALS[ODBOR],$referent)";
      $q->query($sql);*/
    }
  }
  else 
  {
    $GLOBALS['SPIS'] = 1;
    unset($GLOBALS['ID']);
    unset($GLOBALS['EDIT_ID']);
    $edit_id = Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
    
   /* 
    if ($GLOBALS['REFERENT']>0) {
      $user = LoadClass('EedUser', $GLOBALS['REFERENT']);
      $uzel =  $user->VratSpisovyUzelPracovnika($GLOBALS['REFERENT']);
      if ($uzel>0) $GLOBALS['ODBOR'] = $uzel;
    }
    if ($GLOBALS['EDIT_ID']) {
      $q->query('select * from posta_pristupy where id=' . $GLOBALS['EDIT_ID']);
      $q->Next_Record();
      $data = $q->Record;
    }
    if ($GLOBALS['DELETE_ID']) {
      $q->query('select * from posta_pristupy where id=' . $GLOBALS['DELETE_ID']);
      $q->Next_Record();
      $data = $q->Record;
    }
    if (!$data['POSTA_ID']) $data['POSTA_ID'] = $GLOBALS['POSTA_ID'];
    
    
    if ($GLOBALS['DELETE_ID']) {
      $opravneni = '<b>'.$GLOBALS['ACCESS'].'</b> pro spis.uzel <b>'.UkazOdbor($data['ODBOR']).'</b> ('.$data['ODBOR'].'), zpracovatel <b>'.UkazUsera($data['REFERENT']).'</b> ('.$data['REFERENT'].')';
      $q->query('select * from posta_pristupy where id=' . $GLOBALS['DELETE_ID']);
      $q->Next_Record();
      $data = $q->Record;
      Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
    
      $cj_obj = LoadClass('EedCj', $data['POSTA_ID']);
      $cj_info = $cj_obj->GetCjInfo($data['POSTA_ID']);
      $text = $cj_info['CELY_NAZEV'] . ' - bylo odebráno oprávnění: ' . $opravneni;
      EedTransakce::ZapisLog($data['POSTA_ID'], $text, 'DOC');
      EedTransakce::ZapisLog($data['POSTA_ID'], $text, 'SPIS');
    }
    
    else {
      $cj_obj = LoadClass('EedCj', $data['POSTA_ID']);
      $cj_info = $cj_obj->GetCjInfo($data['POSTA_ID']);
      $opravneni = '<b>'.$GLOBALS['ACCESS'].'</b> pro spis.uzel <b>'.UkazOdbor($GLOBALS['ODBOR']).'</b> ('.$GLOBALS['ODBOR'].'), zpracovatel <b>'.UkazUsera($GLOBALS['REFERENT']).'</b> ('.$GLOBALS['REFERENT'].')';
      if ($GLOBALS['EDIT_ID'])
        $text = $cj_info['CELY_NAZEV'] . ' - bylo upraveno oprávnění: ' . $opravneni;
      else
        $text = $cj_info['CELY_NAZEV'] . ' - bylo přidáno oprávnění: ' . $opravneni;
        if ($GLOBALS['EDIT_ID']>0) {
          $GLOBALS['SPIS'] = 1;
          $GLOBALS['POSTA_ID'] = $cj_info['SPIS_ID'];
        }
      $edit_id = Run_(array("showaccess"=>true,"outputtype"=>1,"no_unsetvars"=>true));
    
      EedTransakce::ZapisLog($data['POSTA_ID'], $text, 'DOC');
      EedTransakce::ZapisLog($data['POSTA_ID'], $text, 'SPIS');
    */
  }
    
} else {
  $sql = "delete from posta_pristupy where spis_id=(SELECT spis_id from posta_pristupy where id=".$GLOBALS['DELETE_ID'].") and referent = (SELECT referent from posta_pristupy where id=".$GLOBALS['DELETE_ID'].") and odbor = (SELECT odbor from posta_pristupy where id=".$GLOBALS['DELETE_ID'].")";
  $q->query($sql);
}
require_once(Fileup2('html_footer.inc'));
echo '
<script language="JavaScript" type="text/javascript">
  <!--
    window.opener.document.location.reload();
    window.close();
  //-->
</script>
';
