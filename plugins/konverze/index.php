<?php
include('tmapy_config.inc');
include(FileUp2('html_header_full.inc'));

if ($cmd == 'KonvezeLE') {
  $odkaz = "RunKonverze('LE', ".$DOC_ID.")";
  $nadpis = 'z listinné do elektronické podoby';
//  $src = GetAgendaPath('POSTA_PLUGINS',0,1).'/konverze/generuj.php?type=EL&ID=' . $RECORD_ID;
}
if ($cmd == 'KonvezeEL') {
  $odkaz = "RunKonverze('EL', ".$RECORD_ID.")";
  $nadpis = 'z elektronické do listinné podoby';
//  $src = GetAgendaPath('POSTA_PLUGINS',0,1).'/konverze/generuj.php?type=LE&ID=' . $DOC_ID;
}

echo '<h1>Autorizovaná konverze z moci úřední '.$nadpis.'</h2>';
echo '<p>Konverzi zahájíte kliknutím na odkaz Vygenerovat soubor - systém vygeneruje soubor pro autorizovanou konverzi. Tento soubor otevřete pomocí FormFilleru a pokračujte dle instrukcí ve formuláři.
</p>';


echo '<p><input type="button" class="btn" name="GenButton" onclick="'.$odkaz.';" value="Vygenerovat soubor" >&nbsp;&nbsp;&nbsp;<input type="button" class="btn" onclick="parent.$.fancybox.close();" value="Zavřít okno">';

echo '<script>
function RunKonverze(typ, ID) {
  $( "input[name=\'GenButton\']" ).attr(\'value\' ,\'generuje se...\');
  $( "input[name=\'GenButton\']" ).attr(\'disabled\' ,\'true\');
  newwindow =   window.open(\''.GetAgendaPath('POSTA_PLUGINS',0,1).'/konverze/generuj.php?type=\'+typ+\'&ID=\'+ID,   \'generovani\', \'\');
  newwindow.focus();
}
</script>
';
//Výsledná konverze bude uložena pod JID <b>'.$DOC_ID.'</b>
include(FileUp2('html_footer.inc'));
echo '<iframe src="" name="generovani" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>';
