<?php
require("tmapy_config.inc");
require_once(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/security_obj.inc"));
require_once(Fileup2("html_header_title.inc"));

$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo(); 
$REFERENT = $USER_INFO["ID"]; 

$path1 = GetAgendaPath('STARA_POSTA',false,true);
$path2 = GetAgendaPath('PREVOD_STARA_POSTA',false,true);
$path3 = GetAgendaPath('POSTA_OKNOUZE_PRACOVNICI',false,true);
$path4 = GetAgendaPath('POSTA_ISRZP_PRACOVNICI',false,true);

echo "<h1>Nastavení</h1>";
echo "<a class='body' href='$path1/index.php?frame' target='_top'>EED - dokumenty v historii</a><br/>";
echo "<a class='body' href='$path2/index.php?frame' target='_top'>EED - převod dokumentů do historie</a><br/>";
echo "<a class='body' href='../reporty/reporty.php'>Reporty</a><br/>";
if (HasRole('spravce') || HasRole('lokalni-spravce')) {
  echo "<a class='body' href='konfigurace/index.php?frame' target='nastaveni'>Konfigurace EED</a><br/>";
//  echo "<a class='body' href='referent/index.php?frame' target='nastaveni'>Zástup zpracovatele</a><br/>";
//  echo "<a class='body' href='certifikaty/index.php?frame' target='nastaveni'>Správce certifikátů</a><br/>";
}
If (HasRole('spravce'))
{
  echo "<br/>";
  echo "<a class='body' href='nastaveni.php'>Ukázat hodnoty nastavení</a><br/>";
  echo "<a class='body' href='git.php'>Ukázat GIT log</a><br/>";
  echo "<a class='body' target='_logy' href='logy/index.php?frame'>Výpis logů externích aplikací</a><br/>";
  if (trim($path3)<>'.')
    echo "<a class='body' href='$path3/index.php?frame' target='_top'>Plug-in OK NOUZE: nastavení zpracovatelů</a><br/>";
  if (trim($path4)<>'.')
    echo "<a class='body' href='$path4/index.php?frame' target='_top'>Plug-in IS RŽP: nastavení zpracovatelů</a><br/>";
}

require(FileUp2("html_footer.inc"));
?>
