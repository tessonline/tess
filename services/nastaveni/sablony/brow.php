<?php
require("tmapy_config.inc");
require(FileUp2(".admin/brow_.inc"));
require(FileUp2("html_header_full.inc"));
require_once(FileUp2(".admin/security_.inc"));
require_once(FileUp2(".admin/security_name.inc"));
require(FileUp2(".admin/config.inc"));

/*$GLOBALS['ZAKAZ_ROZSIRENI_VIDITELNOSTI']=true;
include_once(FileUp2('.admin/brow_access.inc'));
Access();
if (strlen($where)<3) $where.= "(1=1) ";
$where2 = $where;*/

include_once(FileUp2('.admin/brow_access.inc'));


/*$USER_INFO = $GLOBALS["POSTA_SECURITY"]->GetUserInfo();
$EedUser = LoadClass('EedUser', $USER_INFO['ID']);
$unit_id = $EedUser->odbor_id;

if (!HasRole('spravce')&&!HasRole('access_all')) {
  //omezeni superodbor
  $where2.=" AND ID_SUPERODBOR IN (". EedTools::VratSuperOdbor() .") ";
  if (!HasRole('lokalni-spravce')) {
    //omezeni na odbor
    $uzel_id = VratOdbor();
    $where2.=" AND ODBOR IN (". $uzel_id.") ";
    if (!HasRole('spravce-sablony')) {
      //omezeni na referenta
      //$where2.= " AND (referent=" . $USER_INFO['ID'] . " OR (odbor in (" . $uzel_id . ") and referent is null))";
    }
  }
}*/

/*if (HasRole('access_all')) {
  include_once(FileUp2('.admin/brow_superodbor.inc'));
  if ($GLOBALS['omez_zarizeni']) $where2.= " AND id_superodbor=" . $GLOBALS['omez_zarizeni']; else 
    $where2.= " AND id_superodbor is null";
} */


Table(array("showaccess" => true,"appendwhere"=>$where2,"showupload"=>true));  
/*echo "

<span class='caption'>
Nápověda:</span><br/>
<span class='text'>
Níže uvedené tagy vepište do šablony na místa, kde chcete vkládat automatický text. Poté šablonu uložte ve formátu RTF. Posledním krokem je nahrání na server - proveďte přes ikonu uploadu <img src='".FileUp2("images/folder_empty.gif")."' border=0> pomocí funkce <i>Nahrát přílohu</i>. Pokud zde již nějaká šablona je, můžete ji tam nechat - systém sám vybere vždy tu nejnovější.<br/>
Pro otestovaní šablony vepište do editace ID dokumentu, z kterého se vezmou testovací data - ID dokumentu naleznete tak, že najete myší na ikonku tužky u daného dokumentu (nebudete na něj klikat) a ve stavovém řádku naleznete např. <i>edit_(1)</i>, kde číslo v závorce je ID dokumentu
</span><br/>
<span class='caption'>Povolené tagy:</span><br/>
<table class=brow cellspacing=5><tr class=brow>

<td class=browdark>%CAROVY_KOD%</td>
<td class=browdark>%DATUM_PRIJETI%</td>
<td class=browdark>%CISLO_JEDNACI%</td>
<td class=browdark>%CISLO_SPISU%</td>
<td class=browdark>%VEC_DOPISU%</td>
<td class=browdark>%ODBOR_REFERENTA%</td>

</tr><tr class=brow>


<td class=browdark>%ADRESA_ODESILATELE%</td>
<td class=browdark>%ADRESA_OSLOVENI%</td>
<td class=browdark>%ADRESA_JMENO%</td>
<td class=browdark>%ADRESA_ULICE%</td>
<td class=browdark> %ADRESA_MESTO%</td>
<td class=browdark> %ADRESA_ODD%</td>
</tr><tr class=brow>

<td class=browdark> %ADRESA_KONTOSOBA%</td>
<td class=browdark>%UREDNIK_JMENO%</td>
<td class=browdark>%UREDNIK_JEN_PRIJMENI%</td>
<td class=browdark>%UREDNIK_TELEFON%</td>
<td class=browdark>%UREDNIK_EMAIL%</td>
<td class=browdark>%UREDNIK_FAX%</td>

</tr><tr class=brow>

<td class=browdark>%JEJICH_CJ%</td>
<td class=browdark>%JEJICH_CJ_DNE%</td>
<td class=browdark>%SPIS_ZNAK%</td>
<td class=browdark>%ROZDELOVNIK%</td>
<td class=browdark>%DNESNI_DATUM%</td>
<td class=browdark>%CAROVY_KOD%</td>
</tr>
    
<tr class=brow>
<td class=browdark>%DATUM_NAROZENI%</td>
<td class=browdark>%SU_ADRESA%</td>
<td class=browdark>%SU_TELEFON%</td>
<td class=browdark>%SU_MOBIL%</td>
<td class=browdark>%SU_EMAIL%</td>
<td class=browdark>%SU_WEB%</td>
</tr>
</table>

<br/>
<span class='text'>
Vkládáte-li čárový kód do dokumentu DOCX, nepoužívejte proměnnou %CAROVY_KOD%, ale na místo, kde chcete čárový kód, vložte <a href=\"barcode.png\" download>tento obrázek pojmenovaný \"barcode.png\"</a>.
</span><br/>


";*/

echo "
<p>Použití \"tagů\" (zástupných znaků) v šablonách dokumentů:</p>
<p>Níže uvedené tagy jsou určeny pro vložení do šablon dokumentů uložených v prostředí ESS UK (nabídka \"Související aplikace / Nastavení šablon\").<br />
Tagy zajistí, že při vytváření dokumentu prostřednictvím šablony se do tohoto dosadí hodnoty již evidované ve formuláři záznamu ESS (čísla jednacího).</p>
<p>Další postup:<br />
1) vytvořenou šablonu opatřenou tagy uložte jako dokument formátu \"DOCX\".<br />
2) Dokument \"DOCX\" vložte v \"Nastavení šablon\" do přílohy připraveného záznamu šablony (vytvoříte pomocí ikony \"Nová položka\").<br />
3) Pro možnost otestovaní šablony uveďte ve formuláři \" Úprava Nastavení šablon\" do pole \"ID dokumentu pro test\" JID dokumentu, ze kterého se vezmou testovací data (z hodnoty vybraného JID stačí uvést pouze desetimístné číslo, bez úvodního prexifu tvořeného pěti písmeny)<br />
- ve sloupci \"Test\" příslušného záznamu šablony se následně bude zobrazovat ikona \"W\" pomocí které bude možno testovat funkčnost tagů v šabloně.<br />
--------------------------------------------------------------<br />
Vkládání čárových kódů do vytvářených dokumentů lze zajistit taktéž prostřednictvím šablon.<br />
Pro tento účel vložte do šablony obrázek \"barcode.png\" (tento obrázek je ke stažení přímo na stránce \"Nastavení šablon\").<br />
--------------------------------------------------------------</p>

<table class=brow cellspacing=2>

<tr class=brow>
<th class=browdark><b>Popis</b></th>
<th class=browdark><b>Tag</b></th>
</tr>

<tr><td>Adresa spisového uzlu zpracovatele</td><td>%SU_ADRESA%</td></tr>
<tr><td>Číslo jednací</td><td>%CISLO_JEDNACI%</td></tr>
<tr><td>Číslo jednací druhé strany</td><td>%JEJICH_CJ%</td></tr>
<tr><td>Číslo orientační příjemce</td><td>%ODESL_COR%</td></tr>
<tr><td>Číslo osoby dle WhoIS</td><td>%WHOIS_NUMBER%</td></tr>
<tr><td>Číslo popisné příjemce</td><td>%ODESL_CP%</td></tr>
<tr><td>Datová schránka příjemce</td><td>%ODESL_DATSCHRANKA%</td></tr>
<tr><td>Datum doručení</td><td>%DATUM_DORUCENI%</td></tr>
<tr><td>Datum narození</td><td>%ODESL_DATNAR%</td></tr>
<tr><td>Datum právní moci</td><td>%DATUM_PM%</td></tr>
<tr><td>Datum vytvoření (datum a čas)</td><td>%DATUM_PODATELNA_PRIJETI%</td></tr>
<tr><td>Datum vytvoření (pouze datum)</td><td>%DEN_PRIJETI%</td></tr>
<tr><td>Datum vypravení</td><td>%DATUM_VYPRAVENI%</td></tr>
<tr><td>Dnešní datum</td><td>%DNESNI_DATUM%</td></tr>
<tr><td>Druh příloh</td><td>%DRUH_PRILOH%</td></tr>
<tr><td>Email spisového uzlu zpracovatele</td><td>%SU_EMAIL%</td></tr>
<tr><td>Email zpracovatele</td><td>%UREDNIK_EMAIL%</td></tr>
<tr><td>Emailová adresa příjemce</td><td>%ODESL_EMAIL%</td></tr>
<tr><td>IČ příjemce</td><td>%ODESL_ICO%</td></tr>
<tr><td>ID studia příjemce (studenta)</td><td>%WHOIS_IDSTUDIA%</td></tr>
<tr><td>Jiné (zejména zahraniční PSČ)</td><td>%ODESL_JINE%</td></tr>
<tr><td>Jméno příjemce</td><td>%ODESL_JMENO%</td></tr>
<tr><td>Jméno, příjmení a titul zpracovatele</td><td>%UREDNIK_JMENO%</td></tr>
<tr><td>Město/obec příjemce</td><td>%ODESL_POSTA%</td></tr>
<tr><td>Mobil spisového uzlu zpracovatele</td><td>%SU_MOBIL%</td></tr>
<tr><td>Název firmy příjemce</td><td>%ODESL_PRIJMENI_FIRMA%</td></tr>
<tr><td>Obálka (detail způsobu vypravení)</td><td>%DOPORUCENE%</td></tr>
<tr><td>Oddělení příjemce (příjemcem je firma)</td><td>%ODESL_ODD%</td></tr>
<tr><td>Oslovení příjemce</td><td>%ODESL_OSLOVENI%</td></tr>
<tr><td>Osoba příjemce (příjemcem je firma)</td><td>%ODESL_OSOBA%</td></tr>
<tr><td>Počet listů</td><td>%POCET_LISTU%</td></tr>
<tr><td>Počet příloh</td><td>	%POCET_PRILOH%</td></tr>
<tr><td>Poznámka</td><td>	%POZNAMKA%</td></tr>
<tr><td>Příjmení příjemce</td><td>%ODESL_PRIJMENI%</td></tr>
<tr><td>Příjmení uživatele</td><td>%UREDNIK_JEN_PRIJMENI%</td></tr>
<tr><td>PSČ příjemce</td><td>%ODESL_PSC%</td></tr>
<tr><td>Spisový uzel</td><td>%ODBOR%</td></tr>
<tr><td>Stát příjemce</td><td>%ODESL_STAT%</td></tr>
<tr><td>Subjekt emailu</td><td>%ODESL_SUBJ%</td></tr>
<tr><td>Telefon spisového uzlu zpracovatele</td><td>%SU_TELEFON%</td></tr>
<tr><td>Telefon zpracovatele</td><td>%UREDNIK_TELEFON%</td></tr>
<tr><td>Tělo emailu</td><td>%ODESL_BODY%</td></tr>
<tr><td>Titul před (příjemce)</td><td>%ODESL_TITUL%</td></tr>
<tr><td>Titul za (příjemce)</td><td>%ODESL_TITUL_ZA%</td></tr>
<tr><td>Ulice příjemce</td><td>%ODESL_ULICE%</td></tr>
<tr><td>Věc</td><td>%VEC%</td></tr>
<tr><td>Způsob vypravení</td><td>%ZPUSOB_VYPRAVENI%</td></tr>

</table>



";



require(FileUp2("html_footer.inc"));
?>
