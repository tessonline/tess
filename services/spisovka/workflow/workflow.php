<?php
$hod=$hodnota;
require("tmapy_config.inc");
require(FileUp2("html_header_full.inc"));
require(FileUp2(".admin/classes/transformace/DatumFiltr.inc"));

?>
<script type="text/javascript">
function removeSelected(element) {
  element.children().each(function() {
		$(this).prop('selected', false);
  });
}
</script>
<?php

function vybranaSablona($typ_posty) {
  if (isset($typ_posty)) {
    $db = new DB_POSTA;
    $sql = "select id from posta_cis_sablony where typ_posty= ".$typ_posty;
    $db->query($sql);
    $db->Next_record();
    return $db->Record['ID'];
  } else 
    return null;
}


function zpracujWorkflow($typ_posty)
{
  $res = array();
  $q=new DB_POSTA;
  $sql="select id_workflow, promenna, hodnota, dokument from posta_workflow where id_typ=".$typ_posty;
  $q->query($sql);
  while ($q->Next_Record()) {
    $res[] =$q->Record;
  }
  return $res;
}

function elementPole($id,$label,$name,$dt) {
  $id_hidden = $id+1000;
  $el = '<div class="form-row">';
  $el.='<div class="form-item" data-id="'.$id.'">';
  $el.='<label class="form-label" for="'.$id.'">';
  $el.=$label;
  $el.='</label>';
  $el.='<div class="form-field-wrapper">';
  $el.='<div class="form-field">';
  $el.='<input name="'.$name.'" value="" type="text" id="'.$id.'">';
  $el.='</div>';
  
 // $el.='<img src="'.FileUpImage('images/remove') .'" border="0" width="25" onclick="odstranitPole(\\\''.$name.'\\\')" title="Odstranit pole">';
  $el.='</div></div></div>';
  $el.='<input type="hidden" name="VAR_'.$name.'" value="'.$label.'" id="'.$id_hidden.'">';
  $el.='<input type="hidden" name="VAR_DT_'.$name.'" value="'.$dt.'" id="'.($id_hidden+1000).'">'; 
  
  return $el;
}

/*function scriptPole($label,$name,$dt,$stav) {
  if ($dt=="text_number") {
  ?>
  <script type="text/javascript">
  function frm_edit_Validator<?php echo $stav;?>(f) {
    if (window.RegExp) {
      var reg = new RegExp("^[0-9\-]*$","g"); 
      if (f.<?php echo $name;?>.type != "hidden") { 
        if (!reg.test(f.<?php echo $name;?>.value)) { 
    			alert("<?php echo $label;?> musí obsahovat číslice!");
        	f.<?php echo $name;?>.focus();
    			return(false);        
    		} 
    	} 
  	}
  }
	</script>
	<?php     
  }
}*/


function scriptPole($label,$name,$dt,$stav) {
  if ($dt=="text_number") {
  //$script = '<script type="text/javascript">';
    $script= 'function frm_edit_Validator'.$stav.'(f) {';
  $script.= '  			alert("ahoj luma");';
//  $script.= '  if (window.RegExp) {';
//  $script.= '    var reg = new RegExp("^[0-9\-]*$","g"); ';
//  $script.= '    if (f.'.$name.'.type != "hidden") { ';
//  $script.= '      if (!reg.test(f.'.$name.'.value)) { ';
//  $script.= '  			alert("'.$label.' musí obsahovat číslice!");';
//  $script.= '      	f.'.$name.'.focus();';
//  $script.= '  			return(false);';        
//  $script.= '  		}'; 
//  $script.= '  	}'; 
//  $script.= '	}';
  $script.= '}';
	//$script.= '</script>';
  }
//  $script = '<div id="ahoj luma"></div>';
  return $script;
}

/*function nahradValidaci($i_max) {
  ?>
  <script type="text/javascript">
	$('form[name=frm_edit]',parent.document).attr('onsubmit','return frm_edit_Validator_nahrazeni(this)');
  function frm_edit_Validator_nahrazeni(f) {
	  for (var i=0;i<<?php echo $i_max ?>;i++) {
		  var fName = 'frm_edit_Validator'+i
		  alert(fName);
		  if ($.isFunction(fName)) {
			  alert(fName);
			  var ret = window[fName](f);
			  if (ret==false)
				  return (false);
		  }
	  }
	  var res = frm_edit_Validator(f);
	  return res;
  }
	</script>
	<?php     
}*/
			  
function nahradValidaci($i_max) {
  
  
 /* $script = '<script type="text/javascript">';
  $script.= 'function frm_edit_Validator_nahrazeni(f) { ';
  $script.='   for (var i=0;i<'.$i_max.';i++) {';
  $script.='   var fName = "frm_edit_Validator"+i';
  $script.='   if ($.isFunction(fName)) {';
  $script.='   alert(fName);';
  $script.='   var ret = window[fName](f);';
  $script.='   if (ret==false)';
  $script.='   return (false);';
  $script.='   }';
  $script.='   }';
  $script.='   var res = frm_edit_Validator(f);';
  $script.='   return res;';
  $script.='   }';
  $script.='   </script>';*/
  ?>
  <script type="text/javascript">
	$('form[name=frm_edit]',parent.document).attr('onsubmit','return frm_edit_Validator_nahrazeni(this)');
	$('form[name=frm_edit]',parent.document).attr('onsubmit','alert(window.testovaci);'); 
  </script>

	<?php
	$script='   window.testovaci = "ahoj luma testovaci";';
//	$script.= 'function frm_edit_Validator_nahrazeni(f) { ';
//	 $script.='   try {';
//	 $script.='   frm_edit_Validator1(f);';
//	 $script.='   } catch(err) { alert(err);}';
//	 $script.='   return(false);';
//	 $script.='   }';
	 
	return $script;
}
			  


function novePoleFormulare($promenna,$hodnota,$stav) {
  $name = "WORKFLOW_".iconv("UTF-8", "us-ascii//TRANSLIT", $promenna);
  $name = strtoupper(str_replace(" ", "", $name));
  $el = elementPole($stav+1000,$promenna,$name,$hodnota);
  $script =  scriptPole($promenna,$name,$hodnota,$stav);
  
  ?>
  <script type="text/javascript">
      //jestli neexistuje najdi element a za nej pripoj vygenerovane html    
      if (!$('input[name=<?php echo $name;?>]',parent.document).length) {
      	var element = $('select[name=TYP_POSTY]',parent.document).parent().parent().parent().parent();
	      element.after('<?php echo $el;?>');
      }
      $('script[name=nahrazeni_validace]',parent.document).parent().prepend($('<script>').attr('type', 'text/javascript').text('<?php echo $script;?>'));
      //$("head",parent.document).prepend('<?php echo $script;?>');

      //$('script[name=nahrazeni_validace]',parent.document).appendTo($('<script>').attr('type', 'text/javascript').text('<?php echo $script;?>'));
      
     // $('<script>')
     // .attr('type', 'text/javascript')
     // .text('<?php echo $script;?>')
     // .prependTo('head',parent.document);

      </script>
      <?php	  		
}

function odstranPoleFormulare($id_posta) {
  if ($id_posta) {
  $x=0;
  ?>
  <script type="text/javascript">
  $('[name^="WORKFLOW_"]',parent.document).each(
  	  function() {
  	  	  var name = $(this).attr('name');
  	  	  var promenna = $('input[name=VAR_'+name+']',parent.document).val();
	  			$.ajax({
  				  url: "smazpole.php",
  				  method: "GET",
  				  url: "smazpole.php",
  				  data: { "promenna": promenna, id_posta: <?php echo $id_posta;?> }
  				}).done(function() {
  				});	  
					$(this).parent().parent().parent().parent().remove();
					$('input[name=VAR_'+name+']',parent.document).remove();
					$('input[name=VAR_DT_'+name+']',parent.document).remove();					
		  });
  </script>
  <?php
  }
  
}


function zmenaDat_select2($promenna,$hodnota,$trigger_change = true) {
  if ($promenna == "ODESL_ODBOR") $promenna = "ORGANIZACNI_VYBOR-1-NEW";
  ?>
  <script type="text/javascript">

      var element2 = $("#<?php echo $promenna; ?>",parent.document);
      removeSelected($('#<?php echo $promenna; ?>',parent.document));
      $('#<?php echo $promenna; ?>',parent.document).val('<?php echo $hodnota ?>');
		  if (<?php echo $trigger_change;?>=="1")
			  $('#<?php echo $promenna; ?>',parent.document).trigger("change");
      var text = $("#<?php echo $promenna; ?> option[value='<?php echo $hodnota ?>']", parent.document).text();
      //$('.select2-selection__rendered', parent.document).prop("title",text);
      //$('.select2-selection__rendered', parent.document).text(text);
      $('#select2-<?php echo $promenna; ?>-container', parent.document).prop("title",text);
      $('#select2-<?php echo $promenna; ?>-container', parent.document).text(text);
      </script>
      <?php	  		  		
  }

function zmenaDat_default($promenna,$hodnota,$trigger_change = true) {
  if ($promenna == "ODESL_PRAC2") $promenna = "ZPRACOVATEL-1-NEW";
  if ($trigger_change == false) $trigger_change = 0;
  $df = new DatumFiltr();
  ?>
  <script type="text/javascript">
  var element = $("[name='<?php echo $promenna; ?>']",parent.document);
  element.attr("disabled",false);
	//alert('<?php echo $promenna; ?>'+element.is(":disabled")+element.parent().is(":disabled"));
	if (element.attr("type")!="hidden") {  
    //pro element SELECT
    if (element.prop('nodeName')=='SELECT') {
	  	removeSelected(element);
  	  element.children().each(function() {
  		  if ($(this).val() == '<?php echo $hodnota ?>') {
 			  try {
  			  $(this).prop('selected', true);
  			  if (<?php echo $trigger_change;?>=="1")
  		 	 		$(this).trigger("change");
  			  } catch (err) {
  				  alert(err);
  			  }
  		  } 
  		  });
    } else {
  	// pro element INPUT  
  	if (element.is("[datetime]")) {
  		  element.val("<?php echo $t_hodnota = $df->transform($hodnota,true); ?>");
  	} else
  	if (element.is(":checkbox")) {
  
  		if ("<?php echo $hodnota;?>"=="1")
  			checked = 1;
  		else
  			checked = 0; 
  		//element.prop( "checked", <?php echo $hodnota;?>);
  		element.prop( "checked", checked);
    } else
  		//alert("<?php echo $t_hodnota = $df->transform($hodnota); ?>");
    element.val("<?php echo $t_hodnota = $df->transform($hodnota); ?>");
    }
	}
  </script>
  <?php
}

function zmenaDat_referent($hodnota) {
  $referent = LoadClass('EedUser', $hodnota);
  ?>
  <script type="text/javascript">  
  	var element_ref = $("[name='REFERENT']",parent.document);
		element_ref.append($('<option>', {
		    value: '<?php echo $hodnota; ?>',
		    text: '<?php echo $referent->cele_jmeno; ?>'
		}));  	
		element_ref.children().last().prop('selected', true);
  </script>
  <?php 
}



function zmenaDat_vyrizeno($hodnota) {
  $h=0;
  ?>
  <script type="text/javascript">
    var element = $("[name='VYRIZENO_COMBO_BOX']",parent.document);
    var nalezeno = false;
  	removeSelected(element);  
  	element.children().each(function() {
  		  
  		  if ($(this).val() == '<?php echo $hodnota ?>') {
  			  nalezeno = true;
  		    $(this).prop('selected', true); 
  		  } 
  	});
  	if (!nalezeno) {
  		element.children().last().prop('selected', true);
  	  element = $("[name='VYRIZENO_TEXT_INPUT']",parent.document);  	  
  	  element.val("<?php echo $hodnota; ?>");
		  element.attr('style', 'display:inline;');			
  	} else {
   	  element = $("[name='VYRIZENO_TEXT_INPUT']",parent.document);  	  
  		element.val("");
		  element.attr('style', 'display:none;');			
  	}
  	element = $("[name='VYRIZENO']",parent.document);
  	element.val("<?php echo $hodnota; ?>");
	</script>
<?php 
}

$GLOBALS['zmena_referent'] = false;

function zmenaDat($promenna, $hodnota, $stav) {
  //zmenaDat_default($promenna,$hodnota);
   switch ($promenna) {
 /*   case "REFERENT": 
      zmenaDat_referent($hodnota);
      $GLOBALS['zmena_referent'] = true;
    break;*/
     
     case "ODBOR":
       $_SESSION['WORKFLOW'] = $GLOBALS['TYP_POSTY'];
       $_SESSION['STAV_WORKFLOW'] = $stav;
       $_SESSION['WORKFLOW_ODCHOZI_POSTA'] = $GLOBALS['ODCHOZI_POSTA'];
       zmenaDat_default($promenna,$hodnota);
       exit(0);
     break;
     
    /* case "ODES_TYP":
       zmenaDat_default($promenna,$hodnota,true);
     break;*/
     
     /*
    case "ODBOR":
      zmenaDat_default($promenna,$hodnota,!$GLOBALS['zmena_referent']);
    break;*/
    case "VYRIZENO":
        zmenaDat_vyrizeno($hodnota);
    break;
    case "ODESL_ODBOR":
      //$_SESSION['WAIT_FOR_CONFIRMATION'] = true;
      $_SESSION['WORKFLOW'] = $GLOBALS['TYP_POSTY'];
      $_SESSION['STAV_WORKFLOW'] = $stav;
      $_SESSION['WORKFLOW_ODCHOZI_POSTA'] = $GLOBALS['ODCHOZI_POSTA'];
      zmenaDat_select2($promenna,$hodnota);
      exit(0);
    break;
    default:
      //zmenaDat_default($promenna,$hodnota,$stav);
      zmenaDat_default($promenna,$hodnota);
      break;
  }
}


$start_from = 0;
if (isset($_SESSION['WORKFLOW'])) {
  $GLOBALS['TYP_POSTY'] = $_SESSION['WORKFLOW'];
  $GLOBALS['ODCHOZI_POSTA'] = $_SESSION['WORKFLOW_ODCHOZI_POSTA'];
  unset($_SESSION['WORKFLOW']);
  $start_from = $_SESSION['STAV_WORKFLOW']+1;
  unset($_SESSION['STAV_WORKFLOW']);
}
else {
  //zacatek zpracovani workflow, odstraneni polí formuláře přidaných předchozím workflow
  odstranPoleFormulare($GLOBALS['ID_POSTA']);
}
$workflow = zpracujWorkflow($GLOBALS['TYP_POSTY']);

$i_max = 0;

for ($i=$start_from;$i<sizeof($workflow);$i++) {
 switch ($workflow[$i]['ID_WORKFLOW']) {
   case 1: //zmena dat
     $doc_pozadovany = $workflow[$i]['DOKUMENT'];
     $odchozi_posta = $GLOBALS['ODCHOZI_POSTA'];
     if (($doc_pozadovany=="")|| (($doc_pozadovany=="O")&&($GLOBALS['ODCHOZI_POSTA']=="t")) || (($doc_pozadovany=="P")&&($GLOBALS['ODCHOZI_POSTA']!="t"))) {
      zmenaDat($workflow[$i]['PROMENNA'],$workflow[$i]['HODNOTA'],$i);
     }
    break;
    case 2: //zaloz schvalovaci proces
      echo "i equals 2";
    break;
    case 3: //nove pole formulare
      novePoleFormulare($workflow[$i]['PROMENNA'],$workflow[$i]['HODNOTA'],$i);
    break;
  }
  $i_max = $i;
}

//$script = nahradValidaci($i_max);
?>
	  <script language="JavaScript" type="text/javascript">
//$('form[name=frm_edit]',parent.document).parent().prepend($('<script>').attr('type', 'text/javascript').text('<?php echo $script;?>'));


</script>
<?php 



//nacteni sablony dle druhu dokumentu
  $sel = vybranaSablona($GLOBALS['TYP_POSTY']); 
  ?>
 	  <script language="JavaScript" type="text/javascript">
 	 		var element = $("[name='sablony']",parent.document);
	 		 element.children().each(function() {
				  $(this).prop('selected',false);
				  //$(this).removeAttr('selected');
	 		 });
	 		 element.children().each(function() {
	 			  if ($(this).val() == '<?php echo $sel; ?>') {
	 				 $(this).prop('selected',true);
	 				  //$(this).attr('selected','selected');
	 			  }
	 		 });
 	  
 	  </script> 
  <?php 

require(FileUp2("html_footer.inc"));
?>

