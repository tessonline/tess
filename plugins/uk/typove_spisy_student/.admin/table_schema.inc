<?php


$TABLE_CONFIG["schema"][] = array("field"=>"STUD_ID", "label"=>"ID Studia",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"CISLO_UK", "label"=>"WHOIS",  "width"=>"1%","add"=>"align=center");
$TABLE_CONFIG["schema"][] = array("field"=>"PRIJMENI...' ' ...JMENO", "label"=>"příjmení jméno",  "width"=>"80%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"TITULY_PRED", "label"=>"tituly před",  "width"=>"10%","add"=>"align=left NOWRAP");
$TABLE_CONFIG["schema"][] = array("field"=>"TITULY_ZA", "label"=>"tituly za",  "width"=>"10%","add"=>"align=left");
$TABLE_CONFIG["schema"][] = array("field"=>"DATUM_OD", "label"=>"Studium OD",  "width"=>"40%","add"=>"align=left NOWRAP");


  $TABLE_TOP_MENU["schema"] = array(
    array("label"=>"Založit vybrané",  "url"=>"javascript:RunScript_Send('create.php','".$table_params['tablename']."',0)", "target"=>"send_DS", "title"=>"Načíst"),
    array("label"=>"Založit vše",  "url"=>"javascript:RunScript_Send('create.php','".$table_params['tablename']."', 1)", "target"=>"send_DS", "title"=>"Načíst vše"),
  );
?>
<script>

  function RunScript_Send(name_script, tablename,param){;
    var frm = document.forms['frm_'+tablename];
    frm.method='POST';
//    window.open(name_script,'tisk','height=260,width=470,left=50,top=50,scrollbars,resizable');
    if (frm.REFERENT.value=='' || frm.REFERENT.value==0 || !frm.REFERENT.value) {
      alert('Není vybrán zpracovatel! Vyberte odpovídajícího zpracvovatele');
      return false;
    }
    if (frm.TYPOVY_SPIS.value=='' || frm.TYPOVY_SPIS.value==0 || !frm.TYPOVY_SPIS.value) {
      alert('Není vybrána šablona typového spisu! Vyberte odpovídající šablonu');
      return false;
    }
    if (param == 1) {

    	$( "input[name^='SELECT_ID']" ).each(function(i, obj) {
          if ($(this).val()>0) {
            var input = document.createElement('INPUT');
            input.setAttribute('type', 'hidden');
            input.setAttribute('name', 'SELECT_ID[]');
            input.setAttribute('value', $(this).val());
            frm.appendChild(input);
          }
       });

    	
        
    }
    var act = frm.action;
    var tar = frm.target;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='1';
    frm.action = name_script;
//    frm.target = '_top';
    frm.submit();
    frm.action = act;
    frm.target = tar;
    //if(frm.SELECT_ID_USE_FILTER) frm.SELECT_ID_USE_FILTER.value='0';
  }
</script>
