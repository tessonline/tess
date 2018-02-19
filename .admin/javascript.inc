<iframe id="ifrm_get_value" name="ifrm_get_value" style="position:absolute;z-index:0;left:10;top:10;visibility:hidden"></iframe>
<iframe id="ifrm_get_value2" name="ifrm_get_value2" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<iframe id="ifrm_get_value3" name="ifrm_get_value3" style="position:absolute;z-index:0;left:0;top:0;visibility:hidden"></iframe>
<script language="JavaScript" type="text/javascript">
<!--
var vall;

function DruhAdresata(val) {
  PovolOdesilani();
<?php if (HasRole('edit-datum-vypraveni'))  echo 'if (document.frm_edit.DATUM_VYPRAVENI)	 document.frm_edit.DATUM_VYPRAVENI.disabled=false;'; ?>

  if (document.getElementById('JEJICH_CJ')) {
    if (val=="U") {
      document.getElementById('JEJICH_CJ').style.backgroundColor='#f1aca8';
    }
    else {
      document.getElementById('JEJICH_CJ').style.backgroundColor='white';
    }
  }

  if (document.forms[0].ODESL_POSTA.value == 'přiřazení čj.') document.forms[0].ODESL_POSTA.value = '';
  if (document.forms[0].ODESL_PRIJMENI.value == 'EPODATELNA') document.forms[0].ODESL_PRIJMENI.value = '';

  //prav.osoba, urad
  if(val=="P" || val=="U")   {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );
  }
  //podnikatel //advokat //exekutor //notar //patent.zastupce//danovy poradce
  if(val=="F" || val=="N" || val=="B" || val=="E" || val=="T" || val=="D") {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //soukr.osoba
  if(val=="O") {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //anonym
  if(val=="A")  {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "anonym" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  }
  //verejnost
  if(val=="V") {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "veřejnost" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  }
  //vlastní záznam
  if(val=="Z")  {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "vlastní záznam" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

    if (document.frm_edit.VLASTNICH_RUKOU) {
      var typobalky = document.frm_edit.VLASTNICH_RUKOU;
//      typobalky.value = <?php echo $GLOBALS[CONFIG][POSTA_NEDORUCUJE]?>;


      TypObalky(typobalky,1);
      ZakazOdesilaniKrome('<?php echo $GLOBALS[CONFIG][POSTA_NEDORUCUJE2]?>');
      document.frm_edit.DOPORUCENE.options[9].selected=true;
    }
  }
  //email
  if(val=="M") {
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

    document.forms[0].TYP_DOKUMENTU.value = 'D';

    if (document.frm_edit.VLASTNICH_RUKOU) {
      var typobalky = document.frm_edit.VLASTNICH_RUKOU;
      typobalky.value = <?php echo $GLOBALS[CONFIG][POSTA_EMAIL]?>;

      TypObalky(typobalky,1);
      ZakazOdesilaniKrome(<?php echo $GLOBALS[CONFIG][POSTA_EMAIL]-1?>);
      document.frm_edit.DOPORUCENE.options[6].selected=true;
    }
  }
  //statnisprava samosprava
  if(val=="S") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    document.forms[0].TYP_DOKUMENTU.value = 'D';
//    document.frm_edit.DATUM_VYPRAVENI.value = '';
<?php if (!HasRole('spravce')) {
   echo ' if (document.frm_edit.DATUM_VYPRAVENI)	 document.frm_edit.DATUM_VYPRAVENI.disabled=true;
';
}
?>
    if (document.frm_edit.VLASTNICH_RUKOU) {
      var typobalky = document.frm_edit.VLASTNICH_RUKOU;
      typobalky.value = <?php echo $GLOBALS[CONFIG][INTERNI_POSTA]?>;

      TypObalky(typobalky,1);
      ZakazOdesilaniKrome(<?php echo $GLOBALS[CONFIG][INTERNI_POSTA]-1?>);
    }
  }
}

function DruhAdresataFilter(val) {
  //prav.osoba, urad
  if(val=="")   {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //prav.osoba, urad
  if(val=="P" || val=="U")   {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //podnikatel //advokat //exekutor //notar //patent.zastupce//danovy poradce
  if(val=="F" || val=="N" || val=="B" || val=="E" || val=="T" || val=="D") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //soukr.osoba
  if(val=="O") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).removeAttr('disabled');
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }
  //anonym
  if(val=="A")  {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "anonym" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  }
  //verejnost
  if(val=="V") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "veřejnost" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  }
  //vlastní záznam
  if(val=="Z")  {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).val( "vlastní záznam" );
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).prop('disabled', true);

    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

  }
  //email
  if(val=="M") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

  }
  //statnisprava samosprava
  if(val=="S") {
    $( "select[name='ODESL_OSLOVENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI_FIRMA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_PRIJMENI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ICO']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_ULICE']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_POSTA']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_EMAIL']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "input[name='ODESL_SUBJ']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "textarea[name='ODESL_BODY']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
    $( "select[name='ODESL_ODBOR']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='ODESL_STAT']" ).closest( "div[class='form-row']" ).css( "display", "none" );;

  }
}

//    document.getElementById('FRM_EMAIL').style.display='none';


function PovolOdesilani() {
  if (document.frm_edit.VLASTNICH_RUKOU) {
    node=document.frm_edit.VLASTNICH_RUKOU;
    if (node.options) {
<?php
      if ($GLOBALS["ODESLANA_POSTA"]=='t') {
        $pocet_doruceni=count($GLOBALS[CONFIG]["DRUH_ODESLANI"]);
        for($a=0; $a<$pocet_doruceni; $a++)  {
           echo '    node.options['.$a.'].disabled=false;';
        }
      }
?>
    }
  }
}

function ZakazOdesilaniKrome(t)
{
  var pomocne = String(t);
  var pole = pomocne.split(",");
  if (document.frm_edit.VLASTNICH_RUKOU) {
    node=document.frm_edit.VLASTNICH_RUKOU;
    if (node.options) {
<?php
      if ($GLOBALS["ODESLANA_POSTA"]=='t') {
        $pocet_doruceni=count($GLOBALS[CONFIG]["DRUH_ODESLANI"]);
        for($a=0; $a<$pocet_doruceni; $a++) {
           echo '    node.options['.$a.'].disabled=true; ';
        }
       echo '
          for(var ii = 0; ii < pole.length; ii++) {
                node.options[pole[ii]].disabled=false;
          }
           ';
      }
?>
    }
  }
}

function UirAdr(okres) {
  newwindow =   window.open('guide.php?G_NAME=posta_adresy&okrkod='+okres+'&ULICE='+document.forms[0].ODESL_ULICE.value+'&cp='+document.forms[0].ODESL_CP.value+'&co='+document.forms[0].ODESL_COR.value+'&psc='+document.forms[0].ODESL_PSC.value+'&mesto='+document.forms[0].ODESL_POSTA.value+'',   'guide', 'height=600px,width=600px,left=0,top=0,scrollbars,resizable');
  newwindow.focus();
}

function JMENO() {
    if (document.forms[0].ODESL_PRIJMENI.value && document.forms[0].ODES_TYP.value == 'O'){
      NewWindowGuide('guide.php?G_NAME=posta_firmy&jmeno='+document.forms[0].ODESL_PRIJMENI.value+'&odes_typ='+document.forms[0].ODES_TYP.value);
    }
    else {
      if (document.forms[0].ODESL_PRIJMENI_FIRMA.value) {
        NewWindowGuide('guide.php?G_NAME=posta_firmy&jmeno='+document.forms[0].ODESL_PRIJMENI_FIRMA.value+'&odes_typ='+document.forms[0].ODES_TYP.value);
      }
      else {
      if (document.forms[0].ODESL_EMAIL.value) {
        var email = document.forms[0].ODESL_EMAIL.value;
        var result = email.match(/\S+@\S+\.\S+/);
        NewWindowGuide('guide.php?G_NAME=posta_firmy&email='+encodeURIComponent(result)+'&odes_typ=M');

      }
      else {
        alert("Musí být zadán výraz pro vyhledávání !")
     }
   }
  }
}

function Jmeno2() {
	JMENO();
}

function Iszr() {
  var d = new Date();
  if (document.forms[0].ODESL_ICO.value){
    NewWindowGuide("/ost/posta/guide.php?G_NAME=posta_iszr&TYP=PO&ICO="+document.forms[0].ODESL_ICO.value+"&UCEL="+document.forms[0].VEC.value+"&"+d.getTime());
  }
  else {
    if (document.forms[0].ODESL_PRIJMENI.value && document.forms[0].ODESL_JMENO.value && document.forms[0].ODESL_DATNAR.value){
      NewWindowGuide("/ost/posta/guide.php?G_NAME=posta_iszr&TYP=FO&PRIJMENI="+document.forms[0].ODESL_PRIJMENI.value+"&JMENO="+document.forms[0].ODESL_JMENO.value+"&DATNAR="+document.forms[0].ODESL_DATNAR.value+"&UCEL="+document.forms[0].VEC.value+"&"+d.getTime());
    }else
      alert("Musí být zadáno jméno, příjmení a datum narození obyvatele nebo IČ organizace!");
  }
}

function ARES() {
  if (document.forms[0].ODESL_ICO.value){
    var d = new Date();
    NewWindowGuide("./ares.php?ICO="+document.forms[0].ODESL_ICO.value+"&typ="+document.forms[0].ODES_TYP.value+"&"+d.getTime());
  }else
    alert("Musí být zadáno IČO !")
}


function Firma() {
  if (document.forms[0].ODESL_PRIJMENI_FIRMA.value){
  newwindow = window.open('guide.php?G_NAME=posta_firmy&jmeno='+document.forms[0].ODESL_PRIJMENI_FIRMA.value+'&odes_typ='+document.forms[0].ODES_TYP.value, 'guide', 'height=600px,width=600px,left=1,top=1,  scrollbars,resizable');
  newwindow.focus();
  }else 
    alert("Musí být zadán výraz pro vyhledávání !")
}


function Rob() {
  if (document.forms[0].ODESL_PRIJMENI.value){
  newwindow =   window.open('guide.php?G_NAME=obyvatele&prijmeni='+document.forms[0].ODESL_PRIJMENI.value+'&jmeno='+document.forms[0].ODESL_JMENO.value+'&typ='+document.forms[0].ODES_TYP.value,   'guide', 'height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
  }else 
    alert("Musí být zadán výraz pro vyhledávání !")
}

function Obalka(ID) {
  if (document.forms[0].obalka.value){
    newwindow =   window.open('output/pdf/obalka.php?ID='+ID+'&ODESLAT='+document.forms[0].DOPORUCENE.value+'&OBALKA='+document.forms[0].obalka.value+'','InsertOdpoved','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
    newwindow.focus();   
  }else 
    alert("Musíte vybrat vhodnou obálku!")
}

function Datovka() {
  var f=document.forms[0];
    url = 'G_NAME=posta_DS&DS='+f.ODESL_DATSCHRANKA.value+'&odes_typ='+f.ODES_TYP.value+'&firma='+encodeURIComponent(f.ODESL_PRIJMENI_FIRMA.value)+'&prijmeni='+encodeURIComponent(f.ODESL_PRIJMENI.value)+'&jmeno='+encodeURIComponent(f.ODESL_JMENO.value)+'&ico='+f.ODESL_ICO.value+'&datnar='+f.ODESL_DATNAR.value+'&mesto='+encodeURIComponent(f.ODESL_POSTA.value);
    NewWindowGuide('/ost/posta/guide.php?'+url);
}
function DoSbernehoArchu(ID) {
  var f=document.forms[0];
    url = 'G_NAME=posta_spisy&arch=1&IDPspis='+ID;
    NewWindowGuide('/ost/posta/guide.php?'+url);
}

function DoSpisu(ID) {
  var f=document.forms[0];
    url = 'G_NAME=posta_spisy&arch=0&spis=1&IDPspis='+ID;
    NewWindowGuide('/ost/posta/guide.php?'+url);
}

function ZalozitSpis(ID) {
  var f=document.forms[0].DOSPISU;
  f.value = -1;
  $( "input[name='SpisCreateButton']" ).attr('value' ,'');
  $( "input[name='SpisCreateButton']" ).attr('placeholder' ,'Zadejte název spisu');
  $( "input[name='SpisCreateButton']" ).attr('type' ,'text');
  $( "input[name='SpisCreateButton']" ).attr('size' ,'40');
  $( "input[name='SpisCreateButton']" ).attr('class' ,'');
  $( "input[name='SpisButton']" ).css( "display", "none" );
//  $( "input[name='NAZEV_SPISU']" ).css( "display", "block" );

}

function JenVybrane(el) {
	if (el.value=="C") {
		  $( ".brow-main" ).hide();		
	} else
		$( ".brow-main" ).show();		
}

function formPristupyPromenne() {
	var fp = document.getElementsByName('frm_edit');
	fp  = fp[0];
   var tablename = 'vybrane';
   var f_t = document.getElementsByName('frm_'+tablename);
    f_t = f_t[0];
    if (f_t != null) {
      for (var i=f_t.length-1; i>=0; i--) {
        if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
            f_t[i].checked) {
            var input = document.createElement('INPUT');
            input.setAttribute('type', 'hidden');
            input.setAttribute('name', 'SELECT_ID'+tablename+'[]');
            input.setAttribute('value', f_t[i].value);
            fp.appendChild(input);
        }
      }
    }
   
	//fp.submit();
}


function pristupyZmena() {
		var pristup = $("[name='ACCESS']").val(); 
		var uzel = $("[name='ODBOR']").val();
		var zpracovatel = $("[name='REFERENT']").val();
	  newwindow =   window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/pristupy/get_pristupne_dokumenty.php?pristup='+pristup+'&uzel='+uzel+'&zpracovatel='+zpracovatel,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
	  newwindow.focus();
}


function Sablona_Nove(ID) {
  if (document.forms[0].sablony.value){
    newwindow =   window.open('output/doc/send_to_word.php?ID='+ID+'&sablona=odpoved&id_sablony='+document.forms[0].sablony.value+'&cislo_spisu1='+document.forms[0].CISLO_SPISU1.value+'&cislo_spisu2='+document.forms[0].CISLO_SPISU2.value+'&save_to_upload=1'+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
    newwindow.focus();
  }else 
    alert("Musíte vybrat vhodnou ąablonu!")
  
}

function Sablona_Smazat(ID) {
  if (confirm('POZOR: Chcete skutečně smazat již vytvořený soubor?')) {
    newwindow =   window.open('output/doc/send_to_word.php?ID='+ID+'&sablona=delete_file&id_sablony='+document.forms[0].sablony.value+'&cislo_spisu1='+document.forms[0].CISLO_SPISU1.value+'&cislo_spisu2='+document.forms[0].CISLO_SPISU2.value+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
    newwindow.focus();
  }
  
}


function Sablona(filename) {
  newwindow =   window.open('output/doc/send_to_word.php?ID='+ID+'&sablona=odpoved&filename='+filename+'&cislo_spisu1='+document.forms[0].CISLO_SPISU1.value+'&cislo_spisu2='+document.forms[0].CISLO_SPISU2.value+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function Sablona2(filename) {
  newwindow =   window.open('output/doc/send_to_word.php?ID=<?echo $GLOBALS["EDIT_ID"]?>&sablona=odpoved2&filename='+filename+'&cislo_spisu1='+document.forms[0].CISLO_SPISU1.value+'&cislo_spisu2='+document.forms[0].CISLO_SPISU2.value+'','nove_okno','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function UkazOdbor(SODBOR,vysledek) {
  newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_odb.php?ODBOR='+SODBOR.value+'&vysledek='+vysledek+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function AgendaFiltr(SODBOR,vysledek) {
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_agenda.php?SODBOR='+SODBOR.value+'&vysledek='+vysledek+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}


function UkazSoucastTypovehoSpisu(spis) {
  newwindow =   window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_typspis.php?SPIS_ID='+spis.value+'','ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function ZmenaTypuDokumentu(typ) {
	//  if (document.frm_edit.SKARTACE.value <= 1) {
  newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/druh_doc.php?DRUH_DOC='+typ.value+'','ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function UkazPracovnika(ODBOR,vysledek,hodnota,hideall) {
	var selectedValues = $('[name="'+ODBOR.name+'"]').val();		
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_prac.php?ODBOR='+selectedValues+'&vysledek='+vysledek+'&hodnota='+hodnota+'&hideall='+hideall+'','ifrm_get_value3','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function UkazTypPosty(AGENDA,vysledek,hodnota,blank,rem_blank,TYP_POSTY,zmenatypposty,smerdokumentu) {
	
	//alert(smerdokumentu);
	var selectedValues = $('[name="'+AGENDA.name+'"]').val();
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/get_value_typ_posty.php?AGENDA='+selectedValues+'&TYP_POSTY='+TYP_POSTY+'&BLANK='+blank+'&REM_BLANK='+rem_blank+'&vysledek='+vysledek+'&hodnota='+hodnota+'&zmenatypposty='+zmenatypposty+'&smer_dokumentu='+smerdokumentu,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function UkazKonfiguraceHodnota(AGENDA) {
	var selectedValues = $('[name="'+AGENDA.name+'"]').val();
	newwindow = window.open('<?php echo GetAgendaPath('POSTA_KONFIGURACE_ODBORY',false,true);?>/get_parametr.php?kategorie='+selectedValues,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function multipleName(pattern,ITEM) {
	var pn = pattern.name;
	var pos = pn.indexOf("-");
	if (pos>0) {
		return ITEM+pn.substr(pos,pn.length-1);
	}
}

function zmenaLokace(lokace) {
	
  var id = lokace.value;
  var name = lokace.name;
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/skartace/skartacni_kniha/get_podrizene_lokace.php?ID='+id+'&NAME='+name,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function AgendaDok(t,sel,seltp,frozen,zmenatypposty,smer) {
	$("[name='"+t.name+"']").val(sel).attr("selected", "selected");
	var text = $("[name='"+t.name+"'] option[value='"+sel+"']").text();
	$('.select2-selection__rendered').prop("title",text);
	$('.select2-selection__rendered').text(text);
	UkazTypPosty(t,'TYP_POSTY',seltp,'',0,seltp,zmenatypposty,smer);
//	$("[name='"+ttp.name+"']").val(seltp).attr("selected", "selected");
  if (frozen==true) {
	  $("[name='"+t.name+"']").attr('disabled','disabled');
	  $("[name='TYP_POSTY']").attr('disabled','disabled');
  }
}

function getAgenda(TYP_POSTY, vysledek) {
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/get_value_agenda_dokumentu.php?TYP_POSTY='+TYP_POSTY.value+'&vysledek='+vysledek,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
	newwindow.focus();
}

function AgendaDocOnChange(TYP_POSTY, vysledek,odchozi_posta,id_posta)
{
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/get_value_agenda_dokumentu.php?TYP_POSTY='+TYP_POSTY.value+'&vysledek='+vysledek,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();

	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/workflow/workflow.php?TYP_POSTY='+TYP_POSTY.value+'&vysledek='+vysledek+'&ODCHOZI_POSTA='+odchozi_posta+'&ID_POSTA='+id_posta,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
	newwindow.focus();  

    
	//	$("[name='"+name+"']").val(sel).attr("selected", "selected");
}

function TypPosty() {
	if (document.forms[0].TYP_POSTY.value!="")
	 NewWindowGuide('guide.php?G_NAME=posta_typ&typ_posty='+document.forms[0].TYP_POSTY.value); else
		 alert("Nejdříve prosím vyberte druh dokumentu.");
}

function ZmenSkartace(skartace) {
  newwindow =   window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/oddeleni/get_value_skar.php?skartace='+skartace.value,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
}

function Zakony() {
  newwindow = window.open('http://portal.gov.cz/wps/portal/_s.155/701/_s.155/701','zakony');
  newwindow.focus();
}
function PSC() {
  newwindow = window.open('/ost/posta/guide.php?G_NAME=posta_psc&PSC='+document.forms[0].ODESL_PSC.value+'&MESTO='+document.forms[0].ODESL_POSTA.value, 'ifrm_get_value','height=400,width=500,scrollbars=1,resizable=0,  toolbar=0,status=0,menubar=0,titlebar=0');
}

function Prijemci(agenda) {
  if (!document.forms[0].DALSI_PRIJEMCI.value) {document.forms[0].DALSI_PRIJEMCI.value=',';}

   newwindow=window.open('guide.php?G_NAME='+agenda+'&prijemci='+document.forms[0].DALSI_PRIJEMCI.value+'&obalka_zadano='+document.forms[0].DOPORUCENE.value+'&doruceni_zadano='+document.forms[0].VLASTNICH_RUKOU.value, 'guideXXX', 'height=600px,width=600px,left=0,  top=0,scrollbars,resizable=1');
}

function DelPrijemci(id,zpusob) {
   newwindow=window.open('./services/spisovka/prijemci/del_adr.php?prijemci='+document.forms[0].DALSI_PRIJEMCI.value+'&DEL_ID='+id+'&zpusob='+zpusob, 'ifrm_get_value',   'height=10px,width=10px,scrollbars,resizable=0');
}

function AddDay2StartDate(val,den,mesic,rok){
  num = new Number(val);
//  todaysdate = new Date(rok,mesic,den,0,0,0,0);
  date_end = new Date(rok,mesic-1,den,0,0,0,0);
  date_end.setTime(date_end.getTime()+((num)*24*60*60*1000));
  str_dat = date_end.getDate()+'.'+(date_end.getMonth()+1)+'.'+date_end.getFullYear()+' 10:00:00';
  document.forms[0].DATUM_PODATELNA_PRIJETI.value=str_dat;
}


function InsertMesto(obj){
var town = '<?php echo $GLOBALS[CONFIG][MESTO] ?>';
   if (obj.value == '') obj.value = town
   else if(obj.value == town) obj.value = ''
        else obj.value = '';
}

function Predani() {
  var obj = document.frm_edit.VLASTNICH_RUKOU.value;
  var povolene = [<?php echo $GLOBALS[CONFIG][POVOLENE_DATUM_VYPRAVENI] ? $GLOBALS[CONFIG][POVOLENE_DATUM_VYPRAVENI] :'"3"' ?>];
  var existuje = povolene.indexOf(obj);
  if (existuje>-1) {
   document.frm_edit.DATUM_VYPRAVENI.disabled=false;
	 document.frm_edit.DATUM_VYPRAVENI.style.backgroundColor = 'white';
  }
  else {
 	 document.frm_edit.DATUM_VYPRAVENI.disabled=true;
	 document.frm_edit.DATUM_VYPRAVENI.style.backgroundColor = 'transparent';
  }
}

function TypObalky(t,zmen) {
  if (document.frm_edit.DOPORUCENE)  {
    node=document.frm_edit.DOPORUCENE;
//    if (!t) t.value=0;
    if (node.options) {

<?php
  $pocet_obalek=count($GLOBALS[CONFIG]["TYP_ODESLANI"]);
  while (list($key,$dorucovatel)=each($GLOBALS[CONFIG]["DRUH_ODESLANI"])) {
    $vybrano=false;
    $vybrano_hodnota=0;
    echo '  if (t.value==\''.$dorucovatel[VALUE].'\') { ';
    for($a=0; $a<$pocet_obalek; $a++) {
      echo '    node.options['.$a.'].disabled=';
      if (in_array($a,$dorucovatel[OBALKY]))
      {echo 'false;
      ';
         if (!$vybrano){ $selected=$a; $vybrano=true; }
      }
      else {echo 'true;'; }
    }
    echo ' if (zmen=="1")
    {
      document.frm_edit.DOPORUCENE.options['.$selected.'].selected=true;
    }
        ';
      
    echo '
    }
   ';    
  }
  ?>
    }
  }

  $( "input[name='OBALKA_NEVRACET']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  $( "input[name='HromObalka']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
  if (document.frm_edit.VLASTNICH_RUKOU.value == 1)  {
    $( "input[name='OBALKA_NEVRACET']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
    $( "input[name='HromObalka']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
  }

}

function Vypnout_PM(){
 var obj = document.frm_edit.DATUM_VYPRAVENI.value;
	if (obj == '' ) {
 		 document.frm_edit.DATUM_PM.disabled=true;
		 document.frm_edit.DATUM_PM.style.backgroundColor = 'transparent';
	}
	else {
 		 document.frm_edit.DATUM_PM.disabled=false;
		 document.frm_edit.DATUM_PM.style.backgroundColor = 'white';
	}
}

function EditShowAtt(e,id,target){
  var script = '/ost/posta/ug_file.php?upload_modul=table&_set_sess_cache_limit_=1';
  if (e.ctrlKey){
    script = script + '&edit&show_typ=1&EDIT_ID='+id;
    var param = 'height=430,width=580,'
    target = 'FileAtt';
  }else{
    script = script + '&FILE_ID='+id;
    var param = 'menubar,status,titlebar,toolbar,';
  }
  var d = new Date();
  newwindow = window.open(script+'&cacheid='+d.getTime(),target,param+'left=100,top=50,scrollbars,resizable');
  newwindow.focus();
  e.cancelBubble=true;
  return false;
}

function UlozVyber(a,id,hodnota) {
  newwindow = window.open('guide/posta_adresati/save_session.php?ID='+id+'&typ='+a+'&hodnota_set='+hodnota.value,'ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();
//  alert(id);
}

function ZSbernehoArchu(cislo) {
	  document.frm_edit.CISLO_JEDNACI1.value=0;   
	  document.frm_edit.PODCISLO_SPISU.value=0;
	  document.frm_edit.EXEMPLAR.value=0;
	  document.frm_edit.DOSBERNEHOARCHU.value=-9;
	  $( "input[name='SbernyArchVyjmuti']" ).attr('value', 'ČJ bude přiděleno při uložení.');
	}

function PridatVnitrnihoAdresata(cislo) {
  newwindow =   window.open('services/spisovka/prijemci/vnitrni_adresat.php?cislo='+cislo,'ifrm_get_value','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  newwindow.focus();

}

function SuperodborChange(vysledek) {
	var superodbor = $("[name='SUPERODBOR']").val();
	newwindow = window.open('<?php echo GetAgendaPath('POSTA',false,true);?>/services/spisovka/get_spisuzly.php?SUPERODBOR='+superodbor+'&vysledek='+vysledek,'ifrm_get_value2','height=600px,width=600px,left=1,top=1,scrollbars,resizable');
  	newwindow.focus();
}

function ReplaceIDSpan() {
  document.getElementById('ID_span').innerHTML='<textarea name=\"ID_pole\" rows=5 cols=10></textarea>';
  document.frm_edit.ID_pole.focus();
  return false;
}

function VymazOdbor(so) {
  //pridame prazdny retezec
  if (document.all) {
    var arg1=document.frm_edit.ODBOR.length
    var arg2=0
  }else{
    var arg1=null
    var arg2="document.formular.seznam.options[0]"
  }
  var no = new Option();
  no.value = ''
  no.text = ""
  document.frm_edit.ODBOR.add(no,arg1);


  document.frm_edit.ODBOR.value = '';
// document.frm_edit.ODDELENI.value = '';
  document.frm_edit.REFERENT.value = '';
  document.frm_edit.DATUM_REFERENT_PRIJETI.value = '';
  document.frm_edit.DATUM_VYRIZENI.value = '';
  document.frm_edit.VYRIZENO.value = '';
  if (so.value == document.frm_edit.SUPERODBOR_PUVODNI.value) {
 		document.frm_edit.ODBOR.disabled=false;
 		document.frm_edit.REFERENT.disabled=false;
 		document.frm_edit.ODBOR_PUVODNI.value=0;
  }
  else {
    document.frm_edit.ODBOR.disabled=true;
    document.frm_edit.REFERENT.disabled=true;
 		document.frm_edit.ODBOR_PUVODNI.value=-1;
  }
  
  return false;
}

function REFERENT_ON() {
 document.frm_edit.DATUM_REFERENT_PRIJETI.value = '';
  return false;
}

function ConvertDate(date) {

  var dt = date.split(" ");
  var date = dt[0];
  var time = dt[1];
  if (!time) time = '23:59:0';

  var dateArray = date.split(".");
  dateArray[0] = parseInt(dateArray[0]);
  dateArray[1] = parseInt(dateArray[1]) - 1;
  dateArray[2] = parseInt(dateArray[2]);

  var timeArray = time.split(":");
  timeArray[0] = parseInt(timeArray[0]);
  timeArray[1] = parseInt(timeArray[1]);
  timeArray[2] = parseInt(timeArray[2]);

  var datum = new Date(dateArray[2],dateArray[1],dateArray[0],timeArray[0],timeArray[1],timeArray[2],0);
  return datum;
}

<?php

if (($is_edit || $is_new || $is_insert)&& $GLOBALS['ODESLANA_POSTA']<>'t')
  include_once(GetAgendaPath('POSTA',false,false).'/js/lhuta_pro_vyrizeni.js');

?>

function Smazat() {
  document.frm_edit.ODESL_PRIJMENI_FIRMA.value = '';
  document.frm_edit.ODESL_PRIJMENI.value = '';
  document.frm_edit.ODESL_OSLOVENI.value = '';
  document.frm_edit.ODESL_EMAIL.value = '';
  document.frm_edit.ODESL_DATNAR.value = '';
  document.frm_edit.ODESL_JMENO.value = '';
  document.frm_edit.ODESL_TITUL.value = '';
  document.frm_edit.ODESL_TITUL_ZA.value = '';
  document.frm_edit.ODESL_ICO.value = '';
  document.frm_edit.ODESL_ODD.value = '';
  document.frm_edit.ODESL_OSOBA.value = '';
  document.frm_edit.ODESL_ULICE.value = '';
  document.frm_edit.ODESL_CP.value = '';
  document.frm_edit.ODESL_COR.value = '';
  document.frm_edit.ODESL_POSTA.value = '';
  document.frm_edit.ODESL_PSC.value = '';
  document.frm_edit.ODESL_DATSCHRANKA.value = '';
  document.frm_edit.ODESL_STAT.value = '';
  document.frm_edit.ODESL_JINE.value = '';

  if (document.frm_edit.WHOIS_NUMBER) document.frm_edit.WHOIS_NUMBER.value = '';
  if (document.frm_edit.WHOIS_IDSTUDIA) document.frm_edit.WHOIS_IDSTUDIA.value = '';

}

function PrepocitejDobu() {
  var rok = document.frm_edit.ROK_PREDANI.value;
  var lhuta = document.frm_edit.LHUTA.value;
  if (rok>0 && lhuta>0 && !document.frm_edit.ROK_SKARTACE.value) {
    var skartace = parseInt(rok) + parseInt(lhuta) + 1;
    document.frm_edit.ROK_SKARTACE.value = skartace;
  }
}

function DatumVypraveni(a) {
  if (document.frm_edit.VLASTNICH_RUKOU.value == 1 && a.value != 1) {
    document.frm_edit.DATUM_VYPRAVENI.value = '';
  }
}


function DruhSkartaceFilter(val) {
	  if(val=="1")   {
	    $( "select[name='SKAR_ZNAK']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
	    $( "checkbox[name='SHOW_WS']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
	    $( "checkbox[name='AKTIVNI']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
	  }
	  else {
	    $( "select[name='SKAR_ZNAK']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
	    $( "checkbox[name='SHOW_WS']" ).closest( "div[class='form-row']" ).css( "display", "none" );;
	    $( "checkbox[name='AKTIVNI']" ).closest( "div[class='form-row']" ).css( "display", "block" );;
	  }
}	  

//-->
</script>
