<?php
$is_filter_all = true;

    
If (($is_filter_all) && (HasRole('spravce')||HasRole('podatelna')))
  {
    echo "<br/>";
    If ($GLOBALS["CONFIG"]["NEOPOST"]) echo "<input type='button' class='button btn' value='Generovat soubor pro NEOPOST'   onclick=\"window.open('".GetAgendaPath('POSTA_NEOPOST',false,true)."/edit.php?insert&cacheid=', 'neopost', 'height=200px,width=700px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["XERTEC"]) echo "<input type='button' class='button btn' value='Vážit na XERTECu'   onclick=\"window.open('".GetAgendaPath('POSTA_XERTEC',false,true)."/edit.php?insert&cacheid=', 'xertex', 'height=500px,width=700px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["XERTEC"]) echo "<input type='button' class='button btn' value='Načíst soubor z XERTECu'   onclick=\"window.open('".GetAgendaPath('POSTA_XERTEC',false,true)."/xertec.php', 'xertex', 'height=500px,width=700px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["EVROFIN"]) echo "<input type='button' class='button btn' value='Generovat soubor pro EVROFIN'   onclick=\"window.open('".GetAgendaPath('POSTA_EVROFIN',false,true)."/edit.php?insert&cacheid=', 'evrofin', 'height=200px,width=700px,left=0,top=0,scrollbars,resizable');\">";    
    echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Vnitřní dokument' onclick='document.location.href=\"brow_vnitrni.php\"'>";
    echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Roční kniha dokumentů'   onclick=\"window.open('services/spisovka/protokoly/edit.php?insert&kniha=1&cacheid=', 'neopost', 'height=200px,width=700px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["TISK_RAZITKA"]) echo "<br/><input type='button' class='button btn' value='Tisk podacích razítek'   onclick=\"window.open('services/barcode/razitko/edit.php?insert', 'podaci', 'height=500px,width=500px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Převzetí zásilek na odbor' onclick=\"window.open('services/barcode/prevzeti/edit.php?insert&smer=1', 'podaci2', 'height=500px,width=4400px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["PREDANI_PRES_CK"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Převzetí zásilek na podatelnu' onclick=\"window.open('services/barcode/prevzeti/edit.php?insert&smer=2', 'podaci2', 'height=500px,width=400px,left=0,top=0,scrollbars,resizable');\">";

    If ($GLOBALS["CONFIG"]["CPOST"]) echo "<br/><input type='button' class='button btn' value='Předávací protokol pro Českou poštu'   onclick=\"document.location.href='".GetAgendaPath('POSTA_CPOST',false,true)."/brow.php?cacheid=';\">";
    If ($GLOBALS["CONFIG"]["CPOST"]) echo "&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Měsíční výkaz pro Českou poštu'   onclick=\"window.open('".GetAgendaPath('POSTA_CPOST',false,true)."/edit_mesic.php?edit&MESICNI_VYKAZ=1&cacheid=', 'xertec', 'height=500px,width=700px,left=0,top=0,scrollbars,resizable');\">";
    echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Předávací protokol pro doručovatele'   onclick=\"document.location.href='".GetAgendaPath('POSTA_DORUCOVATEL',false,true)."/brow.php?cacheid=';\"><br/>";

    If ($GLOBALS["CONFIG"]["JE_ISRZP"] && $GLOBALS["ODBOR"]!=$GLOBALS["CONFIG"]["ZIVNOSTENSKY_ODBOR"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Načíst data z IS RŽP' onclick=\"document.location.href='interface/rzp/receive.php'\">";
    If ($GLOBALS["CONFIG"]["UPLOAD_ELO"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Vytvoření ELO záznamu' onclick=\"window.open('services/dms/elo/edit.php?insert', 'podaci3', 'height=500px,width=400px,left=0,top=0,scrollbars,resizable');\">";
    If ($GLOBALS["CONFIG"]["SKENOVACI_LINKA"]) echo "<br/><input type='button' class='button btn' value='Načtení ze scanneru' onclick=\"window.open('interface/scanner/nacist.php?insert', 'podaci3', 'height=500px,width=400px,left=0,top=0,scrollbars,resizable');\">";
    
   
    $PRACOVNICI_PODATELNY=$GLOBALS["POSTA_SECURITY"]->GetUsersForGroup('posta-podatelna-ruid',1);
    $PRACOVNICI_POD_ID=array();
    If (is_array($PRACOVNICI_PODATELNY))
    {
      while (list($key,$val)=each($PRACOVNICI_PODATELNY))
       $PRACOVNICI_POD_ID[]=$val["ID"];
    }
//    echo "ONMA ".print_r($PRACOVNICI_POD_ID)." onma";
    $PRACOVNICI_PODATELNA=implode(',',$PRACOVNICI_POD_ID);    
    echo "<br/><input type='button' class='button btn' value='Předávací protokol příchozích dokumentů'   onclick=\"window.open('services/spisovka/protokoly/edit.php?insert&cacheid=&smer=prichozi&podatelna_id=$PRACOVNICI_PODATELNA', 'neopost', 'height=300px,width=700px,left=0,top=0,scrollbars,resizable');\">  ";
  }

  If ($is_filter_all && HasRole('podatelna-odbor'))
  {
    $odbor=VratOdbor();
    echo "<br/><input type='button' class='button btn' value='Předávací protokol příchozích dokumentů'   onclick=\"window.open('services/spisovka/protokoly/edit.php?insert&cacheid=&smer=prichozi&podatelna_id=$REFERENT&odbor=$odbor', 'neopost', 'height=300px,width=700px,left=0,top=0,scrollbars,resizable');\">  ";
    If ($GLOBALS["CONFIG"]["CPOST"] && $GLOBALS["CONFIG"]["PODATELNA_ODBOR_PROTOKOL"]) echo "<br/><input type='button' class='button btn' value='Předávací protokol pro Českou poštu'   onclick=\"document.location.href='".GetAgendaPath('POSTA_CPOST',false,true)."/brow.php?cacheid=';\">";
    If ($GLOBALS["CONFIG"]["PODATELNA_ODBOR_PROTOKOL"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Předávací protokol pro doručovatele'   onclick=\"document.location.href='".GetAgendaPath('POSTA_DORUCOVATEL',false,true)."/brow.php?cacheid=';\">";
  }


  If (($is_filter_all) && (HasRole('spravce')||HasRole('vedouci-odbor')||HasRole('vedouci-odd')))
  {
    $odbor=$GLOBALS["ODBOR"];
    //u vedouciho odboru musime nastavit odbor, abychom dostali spravne oddeleni
     if (HasRole('vedouci-odbor')||HasRole('vedouci-odd') ) {$GLOBALS["ODBOR"]=$odbor; $GLOBALS["ODDELENI"]='';}
     else
     {
       //u posta-spravce a access_all
       $GLOBALS["ODBOR"]='';
       $GLOBALS["ODDELENI"]='';
     }
  }
  if ($is_filter_all)  echo "&nbsp;<input type='button' class='button btn' value='Předávací protokol odchozích dokumentů'   onclick=\"window.open('services/spisovka/protokoly/edit.php?insert&cacheid=&smer=odchozi&referent=$REFERENT', 'neopost', 'height=300px,width=700px,left=0,top=0,scrollbars,  resizable');\">";

  If ($is_filter_all) {
    $odbor=VratOdbor();
    echo "<br/><input type='button' class='button btn' value='Tisk obálek'   onclick=\"window.open('services/spisovka/obalky/edit.php?insert&cacheid=', 'obalky', 'height=300px,width=700px,left=0,top=0,scrollbars,resizable');\"> 
    &nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Načtení doručenek'   onclick=\"window.open('services/barcode/dorucenka/edit.php?insert&cacheid=', 'podaci2', 'height=500px,width=400px,left=0,top=0,scrollbars,resizable');\"><br/>";
    If (in_array(VratOdbor(),$GLOBALS[CONFIG][ODBOR_BCLOGIA_TLACITKO])&&$is_filter_all)  echo "<br/><input type='button' class='button btn' value='Připrav dokumenty do BCLOGIE'   onclick=\" window.open('./interface/bclogia/dosle_pisemnosti.php?ZAVRI=1', 'BCLOGIA', 'height=1px,width=1px,left=0,top=0');\">  ";
    If ($GLOBALS["CONFIG"]["JE_OKNOUZE"] && $odbor==$GLOBALS["CONFIG"]["SOCIALNI_ODBOR"]) echo "<input type='button' class='button btn' value='Vytvoření souboru pro OKnouzi' onclick=\"window.open('interface/oknouze/send.php', 'podaci3', 'height=500px,width=400px,left=0,top=0,scrollbars,resizable');\">&nbsp;&nbsp;&nbsp;";
    If ($GLOBALS["CONFIG"]["JE_OKNOUZE"] && $odbor==$GLOBALS["CONFIG"]["SOCIALNI_ODBOR"]) echo "<input type='button' class='button btn' value='Načtení souboru z OKnouze' onclick=\"document.location.href='interface/oknouze/receive.php'\">";
    If ($GLOBALS["CONFIG"]["JE_ISRZP"] && $odbor==$GLOBALS["CONFIG"]["ZIVNOSTENSKY_ODBOR"]) echo "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type='button' class='button btn' value='Načíst data z IS RŽP' onclick=\"document.location.href='interface/rzp/receive.php'\">";
    If ($GLOBALS["CONFIG"]["REZERVACE_CJ"]) echo "<input type='button' class='button btn' value='Rezervace jednacích čísel' onclick=\"document.location.href='".GetAgendaPath('POSTA_REZERVACE',false,true)."/brow.php?rezervace_id=$REFERENT'\">";
    unset($odbor);
  }
  
