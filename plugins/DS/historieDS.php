<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/isds_.inc"));
require_once(FileUp2("interface/.admin/soap_funkce.inc"));
require_once(FileUp2("html_header_full.inc"));


if (!$_GET['DS_ID']) {
  echo '<h1>Historie datové schránky</h1>
  <div class="form darkest-color"> <div class="form-body"> <div class="form-row">
  <form method="get" action="historieDS.php" onsubmit="return frm_edit_Validator(this)">
  Zadejte identifikátor datové schránky: <input type="text" name="DS_ID" value="" size=15 maxlength=32 class="required">
  <input type="submit" name="sumbit" value="Vypsat informace" class="btn button">
  </form>
  </div></div></div>
  ';

  echo '<h1>Poznámka z dokumentace ISDS</h1><span class="text">
  <p>Leží-li datum stavu (aktuálně neaktivní) schránky, o kterou se OVM zajímá, v minulosti a
  ta je kratší než 3 roky, je jisté, že schránka je pouze znepřístupněná (ve stavu 2, 4 nebo
  6). Pak již dnes lze schránku vyhledat službou vyhledání datové schránky</p>
  <p>Je-li toto datum starší, pak se může stát, že schránka je již zrušená (ve stavu 5). V
  takovém případě se na schránku nelze zeptat pomocí FindDataBox ani nijak jinak
  veřejně. Informace o smazaných schránkách jsou k dispozici pouze pro správce ISDS
  v jeho servisní aplikaci. Proto pokud OVM stojí o tato data, musí se obrátit s požadavkem
  na MV.</p>';

  echo '
  <script language="javascript" type="text/javascript">
  <!--
  function frm_edit_Validator(f) {
    if (f.DS_ID.value.length < 6) {
      alert("Zadejte správný identifikátor datové schránky!");
      f.DS_ID.focus();
      return(false);
    }

  //if (document.frm_edit.__) document.frm_edit.__.disabled = true;
  }
  //-->
  </script>
  ';
} else {
echo '
  <h1>Historie datové schránky '.$_GET['DS_ID'].'</h1>';
if ($GLOBALS[CONFIG_POSTA][DS][ds_cert_id]) $certifikat=VratCestukCertifikatu(0,$GLOBALS[CONFIG_POSTA][DS][ds_cert_id],1); else
  $certifikat='';
  $schranka=new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
  if (!$schranka->ValidLogin) {
  	echo ("<span class='caption'>Nepodařilo se připojit k ISDS.</span><br/><span class='text'>Zkontrolujte uľivatelské jméno a heslo.<br/>".$schranka->ErrorInfo."</span>");
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    require(FileUp2("html_footer.inc"));
  	exit();
  }

  $DSID= str_replace(' ','', $_GET['DS_ID']);

  //echo "$OldPassword,$NewPassword";
  //Die();


  $res=$schranka->GetDataBoxActivityStatus($DSID);
  if ($schranka->StatusCode<>'0000') {
    echo "<script>document.getElementById('upl_wait_message').innerHTML = 'Nepovedlo se změnit heslo!'</script>";Flush();
    echo "Odpověd z ISDS: <font color=red><b>".TxtEncodingFromSoap($schranka->StatusMessage)."</b></font><br/>";
    echo "<input type='button' onclick='document.location.href=\"historieDS.php\";' value='Zpět' class='button btn'>";
    require(FileUp2("html_footer.inc"));
    Die();
  }
  print_r($res);

}

require_once(FileUp2("html_footer.inc"));
