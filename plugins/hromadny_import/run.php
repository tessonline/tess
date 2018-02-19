<?php
require('tmapy_config.inc');
require(FileUp2('.admin/run2_.inc'));
require_once(Fileup2('html_header_title.inc'));
require_once(FileUp2('.admin/oth_funkce_2D.inc'));

$user = LoadClass('EedUser', 0);
$GLOBALS['REFERENT'] = $user->id_user;

$pole = OdborPrac($GLOBALS['REFERENT']);  
$GLOBALS['ODBOR'] = $pole['odbor'];
$GLOBALS['SUPERODBOR'] = $pole['so'];

Run_(array(
  'outputtype' => 3, 
  'no_unsetvars' => true
));

require_once(Fileup2('html_footer.inc'));

?>
<script>
window.opener.document.location.reload();
</script>
<?php 