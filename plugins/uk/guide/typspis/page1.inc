<?php

echo '<h1>Zařazení do typového spisu</h1>';

if ($_GET['SELECT_IDedit']) {
  $vybrana_soucast = array();
  $vybrana_soucast['ID'] = $_GET['SELECT_IDedit'];
  $typovy_spis_id = $_GET['typovy_spis_id'];
}
else {

  $idStudia = $_GET['IDstudia'];
  $whois = $_GET['Ident'];
  $skartace = $_GET['skartace'];
  $typ = $_GET['typ'];

  if ($typ == 'C') {
    $nazev = 'S' . $whois . '/'.$idStudia;
  }


  if ($skartace>0) {
    $skartace_pole = EedTools::Skartace_Pole($skartace);
    $znak = $skartace_pole['znak'];
  }


  $nazev = '%' . $nazev .'%';
  if (!$ids = EedTools::VratTypovySpisZNazvu($nazev)) Die('Chyba - není založen odpovídající typový spis. ');
  if (count($ids)>1) Die('Chyba - nalezeno více typových spisů. ');
  else
    $typovy_spis_id = $ids[0];

  $vhodna_soucast = array(); //soucast, ktera splnuje zadani;


  $vhodna_soucast = EedTools::VratSoucastDleSkartaceTypovehoSpisu($typovy_spis_id, $znak);

  if (count($vhodna_soucast) == 0) $vhodna_soucast = EedTools::GetSoucastiTypovehoSpisu($typovy_spis_id);;

  if (count($vhodna_soucast) == 1) $vybrana_soucast = $vhodna_soucast[0];

  if (count($vhodna_soucast)>1) {
  	$caption = 'Vyberte součást, do které bude dokument vložen';

    $GLOBALS['GUIDE_DIRECTION'] = 1;

  	UNSET($SPIS_ID);
  	$where = ' AND typovy_spis_id=' . $typovy_spis_id . ' and dalsi_spis_id=-1 and dil=1 and datum_uzavreni is NULL';
  	unset($ID);
  	$count = Table(array(
  			"agenda" => "POSTA_TYP_SPIS_SOUCASTIADILY",
        "tablename" => "edit",
  			"showselect"=>true,
  			"showedit"=>false,
  			"appendwhere"=>$where,
  			multipleselect=>false,
  			"formvars"=>array('GUIDE_DIRECTION', 'typovy_spis_id'),
  			'caption'=>$caption,
  			"showinfo"=>false,
  			"showdelete"=>false,
  			'setvars'=>true
  	));
  }

}
if ($vybrana_soucast['ID']>0) {
  $doc = LoadClass('EedCj', $typovy_spis_id);
  $nazev_spisu = $doc->nazev;
  $soucast_id = $vybrana_soucast['ID'];
  $sql  = 'select * from cis_posta_spisy where id=' . $soucast_id;
  $a = new DB_POSTA;
  $a->query($sql);
  $a->Next_Record();
  $soucast = $a->Record['SOUCAST'];
  $nazev_soucasti = $a->Record['NAZEV_SPISU'];
echo '
<script language="JavaScript" type="text/javascript">
  window.opener.document.frm_edit.WHOIS_TYPOVYSPISID.value = "'.$typovy_spis_id.'";
  window.opener.document.frm_edit.WHOIS_TYPOVYSPISSOUCAST.value = "'.$soucast.'";


  window.opener.$( "input[name=\'SHOW_WHOIS_TYPOVYSPIS\']" ).attr(\'value\', "'.$typovy_spis_id.'");
  window.opener.$( "input[name=\'SHOW_WHOIS_TYPOVYSPIS\']" ).css( "display", "block" );
  window.opener.$( "input[name=\'SHOW_WHOIS_TYPOVYSPIS\']" ).focus();

//  parent.$.fancybox.close();

</script>
';


}
