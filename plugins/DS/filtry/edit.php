<?php
require('tmapy_config.inc');
require(FileUp2(".config/config.inc"));
require(FileUp2('.admin/edit_.inc'));
require(FileUp2('html_header_title.inc'));

Form_(array(
  'showaccess'=>true
));  
    echo '<script>
newwindow = window.open(\'../../../services/spisovka/oddeleni/get_value_odb.php?ODBOR='.$GLOBALS['ED_ITEM_SUPERODBOR'].'&vysledek=ODBOR&hodnota='.$GLOBALS["ED_ITEM_ODBOR"].'\',\'ifrm_get_value2\',\'\');
newwindow.focus();
</script> 
';
   echo '<script>
newwindow = window.open(\'../../../services/spisovka/oddeleni/get_value_prac.php?ODBOR='.$GLOBALS['ED_ITEM_ODBOR'].'&vysledek=REFERENT&hodnota='.$GLOBALS["ED_ITEM_REFERENT"].'\',\'ifrm_get_value\',\'\');
newwindow.focus();
</script> 
';
require(FileUp2('html_footer.inc'));
