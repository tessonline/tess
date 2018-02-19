  <?php 
if ($GLOBALS['CONFIG']['WORKFLOW_POLOZKY_FORMULARE']&&($GLOBALS['EDIT_ID'])) {
  $q = new DB_POSTA;
  $sql = "SELECT * FROM POSTA_WORKFLOW_POLE WHERE ID_POSTA =". $GLOBALS['EDIT_ID'];
  $q->query($sql);
  $GLOBALS['polozky_workflow'] = array();
  while ($q->Next_Record()) {
    $GLOBALS['polozky_workflow'][] = $q->Record;

  }
  
  //SELECT * FROM posta_workflow WHERE id_workflow=3
}

/*function nahradValidaci($i_max) {
  ?>
  <script type="text/javascript" name="nahrazeni_validace">
//	$('form[name=frm_edit]',parent.document).attr('onsubmit','return frm_edit_Validator_nahrazeni(this)');
//  function frm_edit_Validator_nahrazeni(f) {
//	  for (var i=0;i<<?php echo $i_max ?>;i++) {
//		  var fName = 'frm_edit_Validator'+i
//		  alert(fName);
//		  try {
//		  frm_edit_Validator1(f);
//		  }
//		  catch (err) {
//			  alert(err);
//		  }
//		  if ($.isFunction(fName)) {
//			  alert(fName);
//			  var ret = window[fName](f);
//			  if (ret==false)
//				  return (false);
//		  }
//	  }
//	  var res = frm_edit_Validator(f);
//	  return res;
//  }
	</script>
	<?php     
}

nahradValidaci(1);*/

?>
