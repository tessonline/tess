<?php

require("tmapy_config.inc");
require_once(FileUp2(".admin/nocache.inc"));
require_once(FileUp2(".admin/brow_.inc"));
require_once(FileUp2(".admin/statistiky.inc"));
require_once(FileUp2("html_header.inc"));

?>

    <link href="css/main.css" rel="stylesheet" type="text/css">
    <link href="css/jquery-ui-1.8.18.custom.css" rel="stylesheet" type="text/css">

  </head>
<body>

<?php

$nadpis = array();
$mesice_text = array(1 =>'leden','únor','březen','duben','květen','červen','červenec','srpen','září','říjen','listopad','prosinec');
$sql = 'select id from posta';
$sql_where = array();
$q = new DB_POSTA;

$sql_where[]="AND odes_typ<>'X'";
$sql_where[]="AND odes_typ<>'S'";

if ($GLOBALS["HISTORIE"]) {$nadpis[]="včetně archívu"; }
if ($GLOBALS["STORNOVANE"]) {$nadpis[]="včetně stornovaných";} else {$sql_where[]=$STATISTIKA['BEZ_STORNA'];}

//If ($GLOBALS["MESIC"]=="") {$GLOBALS["MESIC"]='%';}
If ($GLOBALS["ROK"]) {$sql_where[]="AND ROK IN (".$GLOBALS['ROK'].")"; $nadpis[]="rok: ".$GLOBALS['ROK'];};

If ($GLOBALS["MESIC"]) {
  if (!$GLOBALS['ROK']) $sql_where[]="AND ROK IN (".Date('Y').")"; $nadpis[]="rok: ".Date('Y'); 
  {$sql_where[]="AND datum_podatelna_prijeti like '%.".$GLOBALS['MESIC'].".".$GLOBALS['ROK']."%'"; $nadpis[]="měsíc: ".$mesice_text[$GLOBALS['MESIC']];};
}
if ($GLOBALS['ODBOR'] && !$GLOBALS['PRAVA']) 
{
  $sql_where[]=" AND ODBOR IN (".$GLOBALS['ODBOR'].")";
  $nadpis[]="spis.uzel: ".UkazOdbor($GLOBALS['ODBOR']);
  $file_schema = ".admin/statistika_detail.inc";
}
elseif ($GLOBALS['PRAVA']=="podatelna")
{
  if ($GLOBALS['ODBOR'])
    $sql_where[]=" AND ODBOR IN (".$GLOBALS['ODBOR'].")";
  $nadpis[]="spis.uzel: ".UkazOdbor($GLOBALS['ODBOR']);

  $file_schema = ".admin/statistika_role_podatelna.inc";
}
else
  $file_schema = ".admin/statistika_zaklad.inc";

$graf = "http://".$_SERVER['SERVER_NAME']."/cgi-bin/owtchart?type=Pie&PieRadius=75"; //&BGColor=F0F6F2

include_once($file_schema);

$nl=chr(10);

echo "<div class='nadpis'><h1>".$nl."</h1>";
echo "  <h1 class='caption'>Statistika Evidence dokumentů";
if (count($nadpis)>0) echo ", ".implode(', ',$nadpis);
echo "</h1>".$nl;
echo "</div>".$nl;

echo "<div id='accordion'>".$nl;

while (list($key,$blok)=each($celek)) {
  //ukazeme cely blok
  echo "  <h3><a href='#'>".$blok['NAME']."</a></h3>".$nl;
  echo "<div>".$nl; 
  
  //koukneme, jestli je k dispozici nejaka tabulka
  if (is_array($blok['tabulka']))
  while (list($id_tab,$tab)=each($blok['tabulka']))
  {
    //vypiseme tabulku 
    echo "  <div class='blok'>".$nl;
    echo "      <table class='brow' cellspacing='0'>".$nl;
    //a vypiseme jednotlivy radky tabulky
    $hodnoty = array(); $soucet = 0;
    if (count($tab['radky'])>0) {
      echo "        <tr class='brow'><th class='brow'>".$tab['NAME']."</th><th class='brow'>Počet</th></tr>".$nl;
      $sudyRadek = FALSE;
      foreach($tab['radky'] as $vlevo => $vpravo) {
        $hodnoty[] = $vpravo;
        $soucet = $soucet+$vpravo;
        $class = $sudyRadek ? 'browdark' : 'brow';
        echo "        <tr><td class='$class leftCell'>".$vlevo."</td><td class='$class rightCell'>".$vpravo."</td></tr>".$nl;
        $sudyRadek = !$sudyRadek;
      }
    }
    echo "      </table>".$nl;
    //ukazeme graf
    $vals = "&vals=".implode('!',$hodnoty)."&NumPts=".count($hodnoty);
    if ($soucet>0)
      echo "      <img src='".$graf.$vals."'>".$nl;    
    echo "  </div>".$nl; 
  }   
  
  echo "</div>";
}

echo "</div>".$nl;


require(FileUp2('html_footer.inc'));

if (!$GLOBALS['PRIRAVIT_PRO_TISK'])
echo '
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
<script src="js/libs/jquery-ui-1.8.17.custom.min.js"></script>
<script type="text/javascript">
  
	$(function() {
    
    $( "#accordion" ).accordion({
			autoHeight: false,
			navigation: true,
			collapsible: true
		});
    
	});
  
</script>

';
