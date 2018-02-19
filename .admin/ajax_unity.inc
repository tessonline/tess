<?php
include_once ($GLOBALS['TMAPY_LIB'] . '/oohforms.inc');
require_once (FileUp2('.admin/el/of_select_.inc'));
$odbory = getSelectDataEed(new of_select_vsechny_spisuzly(array()));

$unit_exists = false;
$subzak = '';
foreach ($odbory as $key => $val) {
  if ($GLOBALS['omez_uzel']==$key) $unit_exists = true;
   if ((HasRole('zpracovatel') || HasRole('vedouci-odbor')) && $GLOBALS['ODBOR'] == $key) {$disabled='';  $GLOBALS['omez_uzel'] = $key;}
     else $disabled = 'DISABLED';
  if (HasRole('spravce') || HasRole('lokalni-spravce') || HasRole('podatelna')) $disabled = '';
  $subzak .= '<option value="'.$key.'" '.($GLOBALS['omez_uzel']==$key?'SELECTED':'').' '.$disabled.'>'.$val.'</option>';
}
?>
    <script language="JavaScript" type="text/javascript">
       //if ($('select[name=\'omez_uzel\']', window.parent.document))
       {
         var typ_dokumentu = $('select[name=omez_uzel]');
          typ_dokumentu.empty();
          typ_dokumentu.append('<?php echo $subzak; ?>');
         document.frm_change.isLoadedUnit.value =1 ;
       }
    </script>