  <script type="text/javascript">
  	function odstranitPole(jmeno) {
      	$('input[name='+jmeno+']').parent().parent().parent().parent().remove();      	
      	$('input[name=VAR_'+jmeno+']').remove();
      	$('input[name=VAR_DT_'+jmeno+']').remove();
  	}
  </script>

<?php 
if (isset($GLOBALS['polozky_workflow']))
foreach ($GLOBALS['polozky_workflow'] as $polozka) {
  if ($polozka['PROMENNA']<>'') {
    $name = "WORKFLOW_".iconv("UTF-8", "us-ascii//TRANSLIT", $polozka['PROMENNA']);
    $name = strtoupper(str_replace(" ", "", $name));
    $GLOBALS[$name] = $polozka['HODNOTA'];
    
    $FORM_CONFIG["schema"][] = array("elements" => array(
      array(
        "type" => $polozka['DATOVY_TYP'],
        "name" => $name,
      ),
    ),
      "label" => $polozka['PROMENNA'].":"
    );
    
    
    $FORM_CONFIG["schema"][] = array("elements" => array(
      array(
        "type" => "hidden",
        "name" => "VAR_".$name,
        "value" => $polozka['PROMENNA']
      ),
    ),
    );
    
    $FORM_CONFIG["schema"][] = array("elements" => array(
      array(
        "type" => "hidden",
        "name" => "VAR_DT_".$name,
        "value" => $polozka['DATOVY_TYP']
      ),
    ),
    );
  }
}

?>