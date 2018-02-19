<?php
echo '<div class="form dark-color"> <div class="form-body"> <div class="form-row"><p><strong>Rychlý&nbsp;filtr:&nbsp;&nbsp;&nbsp;</strong>';
$referent_where = "and referent in (" . $USER_INFO['ID'] .")";
$vedouci = false;

$EddSql = LoadClass('EedSql');

if (HasRole('cteni_uzel')) {
    $where_filter .= "and (".$EddSql->WhereOdborAndPrac(VratOdbor()."").")";
}

if (HasRole('cteni_uzel') || HasRole('cteni_vse_pracoviste') || HasRole('cteni_admin')) { $vedouci = true;}

if (!$vedouci) $where = $where_filter . $referent_where;
$referent_param = "&omez_prac=".$USER_INFO['ID'];


if (!HasRole('cteni_admin')) $where_filter .= " AND superodbor in (" . EedTools::VratSuperOdbor() .") ";
//zelena
if (HasRole('cteni_admin')||HasRole('cteni_uzel')||HasRole('cteni_vse_pracoviste')||HasRole('vedouci-odd')) {
  echo "<font style=\"background-color: green; color:white;\"><b>&nbsp;NOVÉ&nbsp;</b></font>&nbsp;(<a href='brow.php?STATUS=2'>" . EedTools::UkazPocetDleStatus(2,$where_filter) . "</a>)&nbsp;&nbsp;&nbsp;";
}

//modra
echo "<font style=\"background-color: blue; color:white;\"><b>&nbsp;NOVÉ&nbsp;</b></font>&nbsp;(";
if ($vedouci) {
  echo "<a href='brow.php?STATUS=3'>" . EedTools::UkazPocetDleStatus(3, $where_filter) . "</a>/";
}
echo "<a href='brow.php?STATUS=3$referent_param'>" . EedTools::UkazPocetDleStatus(3, $where_filter . $referent_where) . "</a>";
echo ")&nbsp;&nbsp;&nbsp;";


//na stole
echo "<font style=\"background-color: black; color:white;\"><b>&nbsp;NA STOLE&nbsp;</b></font>&nbsp;(";
if ($vedouci) {
  echo "<a href='brow.php?STATUS=4'>" . EedTools::UkazPocetDleStatus(4, $where_filter) . "</a>/";
}
echo "<a href='brow.php?STATUS=4$referent_param'>" . EedTools::UkazPocetDleStatus(4, $where_filter . $referent_where) . "</a>";
echo ")&nbsp;&nbsp;&nbsp;";

//nutne
echo "<font style=\"background-color: yellow; color:black;\"><b>&nbsp;NUTNÉ&nbsp;</b></font>&nbsp;(";
if ($vedouci) {
  echo "<a href='brow.php?STATUS=5'>" . EedTools::UkazPocetDleStatus(5, $where_filter) . "</a>/";
}
echo "<a href='brow.php?STATUS=5$referent_param'>" . EedTools::UkazPocetDleStatus(5, $where_filter . $referent_where) . "</a>";
echo ")&nbsp;&nbsp;&nbsp;";

//po terminu
echo "<font style=\"background-color: red; color:white;\"><b>&nbsp;PO&nbsp;TERMÍNU&nbsp;</b></font>&nbsp;(";
if ($vedouci) {
  echo "<a href='brow.php?STATUS=6'>" . EedTools::UkazPocetDleStatus(6, $where_filter) . "</a>/";
}
echo "<a href='brow.php?STATUS=6$referent_param'>" . EedTools::UkazPocetDleStatus(6, $where_filter . $referent_where) . "</a>";
echo ")&nbsp;&nbsp;&nbsp;";

if ($GLOBALS['CONFIG_POSTA']['PLUGINS']['schvalovani']['enabled'] == true) {
  include_once(GetAgendaPath('POSTA_PLUGINS',0,0).'/schvalovani/.admin/schvalovani.inc');
  //k souhlaus
  echo "<font style=\"background-color: black; color:white;\"><b>&nbsp;K SOUHLASU&nbsp;</b></font>&nbsp;(";
  //if ($vedouci) {
  //  echo "<a href='brow.php?STATUS=11'>" . EedTools::UkazPocetDleStatus(11, $where_filter) . "</a>/";
  //}
  $res = SeznamKeSchvaleni($USER_INFO["ID"]);
  echo "<a href='brow.php?STATUS=11'>" . count($res) . "</a>";
  echo ")&nbsp;&nbsp;&nbsp;";

  //k podpisu
  echo "<font style=\"background-color: black; color:white;\"><b>&nbsp;K PODPISU&nbsp;</b></font>&nbsp;(";
  //if ($vedouci) {
  //  echo "<a href='brow.php?STATUS=12'>" . EedTools::UkazPocetDleStatus(12, $where_filter) . "</a>/";
  //}
  $res = SeznamKPodpisu($USER_INFO["ID"]);
  echo "<a href='brow.php?STATUS=11&podpis=1'>" . count($res) . "</a>";
  echo ")&nbsp;&nbsp;&nbsp;";

}

//dorucenkz
echo "<font style=\"background-color: brown; color:white;\"><b>&nbsp;DORUČENKY&nbsp;</b></font>&nbsp;(";
if ($vedouci) {
  echo "<a href='brow.php?STATUS=8'>" . EedTools::UkazPocetDleStatus(8, $where_filter) . "</a>/";
}
echo "<a href='brow.php?STATUS=8$referent_param'>" . EedTools::UkazPocetDleStatus(8, $where_filter . $referent_where) . "</a>";
echo ")&nbsp;&nbsp;&nbsp;";
echo '<p></div> </div> </div>';
