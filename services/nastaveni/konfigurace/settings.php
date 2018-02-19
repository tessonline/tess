<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require(FileUp2(".admin/settings.inc"));
require_once(FileUp2("security/.admin/security_func.inc"));
require_once(FileUp2(".admin/classes/pdf/PDF_Predani.php"));
require_once(FileUp2(".admin/security_name.inc"));
require_once(FileUp2(".admin/status.inc"));
require_once(FileUp2(".admin/config.inc"));
require_once(Fileup2("html_header_title.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$id_user=$USER_INFO["ID"];
$jmeno = $USER_INFO["FNAME"] . " " . $USER_INFO["LNAME"];
$LAST_USER_ID=$id_user;
$OWNER_ID=$id_user;
$LAST_TIME=Date('H:i');
$LAST_DATE=Date('Y-m-d');

$add_info="last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=".$LAST_USER_ID;

if (!$krok) $krok=1;

if (!$id)
{
  echo "<h1>Nastavení databázových hodnot</h1>
  <p><i><b>Upozornění:</B> tyto funkce přímo ovlivňují údaje v databázové struktuře a jsou většinou nevratné. </i></p>
  <ul>";
  while (list($key,$val)=each($settings))
  {
    if (($key!=1)||HasRole('spravce'))
    echo "<li><a class='body' href='settings.php?id=$key'>".$val['name']."</a></li>";
  }
  echo "</ul>";
}
if ($id && $settings[$id]['krok'][$krok])
{
  $q=new DB_POSTA();

  echo "<h1>".$settings[$id]['name']."</h1>
  <form name='prevod_zpracovatele' method=get action='settings.php' onsubmit='return validate()'>
  <input type='hidden' name='id' value='$id'>
  <input type='hidden' name='krok' value='".($krok+1)."'>
  
  ";
  
  eval($settings[$id]['krok'][$krok]);

  if ($settings[$id]['krok'][$krok+1])
    echo "<br/><input type='submit' name='Další' value='  Další  ' class='btn'>";
  else
    echo "<br/><input type='submit' name='Dokončit' value='  Dokončit  ' class='btn'>";

}

if ($id && !$settings[$id]['krok'][$krok])
{
  echo "<script>document.location.href='settings.php';</script>";
}
require_once(Fileup2("html_footer.inc"));  

?>

<script language="javascript" type="text/javascript">
<!--

  function validateDate(elementName) {
    
    var err = false;  
    var textInput = window.document.getElementsByName(elementName)[0];
    if (textInput.value != '') {

      if (window.RegExp) {
        var reg = new RegExp(',', 'g');
        textInput.value = textInput.value.replace(reg, '.');
        var reg = new RegExp("^[0-9]{1,2}[.][0-9]{1,2}[.][0-9]{4}$", "g");
        if (!reg.test(textInput.value)) err = true;
      };

      dt = textInput.value.split('.');
      y = dt[2];
      m = dt[1];
      d = dt[0];

      if (m < 1 || m > 12) err = true;
      if (d < 1 || d > 31) err = true;
      if ((d == 31) && (m == 4 || m == 6 || m == 9 || m == 11)) err = true;
      if ((m == 2) && (d > 29)) err = true;

      } else err = true;


    if (err == true){
      alert("Datum nemá správnou hodnotu nebo formát. Správný formát je 'd.m.yyyy' (p\u0159: 31.12.1999)!");
      textInput.focus();

    }
    return !err;
  }
  
  function validate() {
    return validateDate('datum_od') && validateDate('datum_do');
  }


-->
</script>
