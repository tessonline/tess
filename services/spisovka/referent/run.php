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

if ($_GET['REFERENT_ID']) UNSET($_GET['ODBOR']);

if (is_array($_GET['ODBOR'])) {
  foreach($_GET['ODBOR'] as $odbor) {
    if ($odbor>0) {
      $noveid = ZalozNovyDokument($GLOBALS['POSTA_ID'], 0, 3);
      $so = VratSuperOdbor($odbor);
      if ($odbor<1000) $odbor=0;
      if ($odbor>1000) $odbor = VratOdbor($odbor);
      $sql='update posta set superodbor='.$so.',ODBOR='.$odbor.', referent=0 ';
      $sql.=' where id='.$noveid;
//      echo $sql.'<br/>';
      $q->query($sql);
      NastavStatus($noveid);
    }
  }
}

if (is_array($_GET['REFERENT_ID'])) { 
  foreach($_GET['REFERENT_ID'] as $referent) {
    if ($referent>0) {
      $noveid=ZalozNovyDokument($GLOBALS['POSTA_ID'], 0, 3);
  
      $pole=OdborPrac($referent);
      print_r($pole);
      $sql='update posta set REFERENT='.$referent.',ODBOR='.$pole['odbor'];
      $sql.=' where id='.$noveid;
      echo $sql;
      $q->query($sql);
      NastavStatus($noveid);
    }
  }
}
//Die();
//$sql="update posta set nazev_spisu='".$GLOBALS['NAZEV_SPISU']."' where cislo_spisu1=".$GLOBALS['CISLO_SPISU1']." and cislo_spisu2=".$GLOBALS['CISLO_SPISU2'];

//Run_(array('outputtype'=>3,'to_history'=>true));

require_once(Fileup2('html_footer.inc'));
echo '
<script language="JavaScript" type="text/javascript">
  <!--
    window.opener.document.location.reload();
    window.close();
  //-->
</script>
';
