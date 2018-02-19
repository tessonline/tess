<?php
$show_ref = false;
$show_odbor = false;
if ($GLOBALS['REFERENT']) {
  $show_ref = true;
}

if ($GLOBALS['ODBOR']) $show_odbor = true;
if ($GLOBALS['POSTA_ID']>0) {
  $doc = LoadClass('EedDokument', $GLOBALS['POSTA_ID']);
  $odbor = $doc->odbor; 
  //echo ' odbor je ' . $odbor;
  $GLOBALS['ODBOR'] = $doc->VratSpisUzelZOdboru($odbor);
  //echo $GLOBALS['ODBOR'];
  //print_r($doc);
}


if ($show_ref) $GLOBALS['ODBOR']=VratOdbor();

$FORM_CONFIG['schema'][] = array( 'elements' => array(
                   array( 'type' => 'hidden', 'name' => 'POSTA_ID')),
                   'label' => '');

$FORM_CONFIG['schema'][] = array( 'elements' => array(
                   array( 'type' => 'select_spisuzly', 'name' => 'ODBOR[]', 'insertnull' => true, "add"=>'data-multiple-item="true"')),
                   'visible' => $show_odbor,
                   'label' => 'Odbor:');

$FORM_CONFIG['schema'][] = array( 'elements' => array(
                   array( 'type' => 'select_referent', 'name' => 'REFERENT_ID[]', 'insertnull' => true,"add"=>'data-multiple-item="true"')),
                   'visible' => $show_ref,
                   'label' => 'Referent:');

  include(FileUp2('.admin/el/owner_user_date_form_add.inc'));  
?>

<style>
<?php include(FileUp2('/css/autocomplete.css'));?>
</style>
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.1/jquery-ui.min.js"></script>
<script type="text/javascript">
<?php include(FileUp2('/js/jquery.placeholder/jquery.placeholder.js'));
      include(FileUp2('/js/adresat.js'));
      include(FileUp2('/js/multiple_items.js'));
?>
</script>
