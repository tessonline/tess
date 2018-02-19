<?php

echo "<script>
function insertIds() {    
       var tablename = 'denik';
       var f_t = document.getElementsByName('frm_'+tablename);
        f_t = f_t[0];
        if (f_t != null) {
          var edit_id = '';
          for (var i=f_t.length-1; i>=0; i--) {
            if (unescape(f_t[i].name)=='SELECT_ID'+tablename+'[]' &&
                f_t[i].checked) {
								edit_id = edit_id + ',' + f_t[i].value;
            }
          }
          edit_id = edit_id.substr(1);
          if (edit_id.length>1)
          NewWindowStitek('plugins/uk/stitek_typovy_spis/edit.php?edit&EDIT_ID='+edit_id);
        }
}
</script>
";

//print_r($GLOBALS['omez_stav']);
if ($GLOBALS['omez_stav'] == -7)
$TABLE_TOP_MENU["schema"][] = array(
  'label' => 'Tisknout údaje vybraných typových spisů',
  'url' => 'javascript:insertIds()',
  'target' => '_self',
  'theme_config' => array(
    'square' => array(
      'theme' => array(
        'dropdown' => false,
        'button' => true
      )
    )
  )
);
