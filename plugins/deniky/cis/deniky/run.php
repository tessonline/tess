<?php
require("tmapy_config.inc");
require(FileUp2(".admin/run2_.inc"));
require_once(Fileup2("html_header_title.inc"));

if (!$GLOBALS['AKTIVNI']) $GLOBALS['AKTIVNI'] = 0;
if (!$GLOBALS['DATUM_VYRIZENI']) $GLOBALS['DATUM_VYRIZENI'] = 0;
if (!$GLOBALS['SPIS_VYRIZEN']) $GLOBALS['SPIS_VYRIZEN'] = 0;

if ($GLOBALS['DELETE_ID']) {
 $sql="
do $$
begin
IF EXISTS (SELECT 0 FROM pg_class where relname = 'drop sequence posta_deniky_".$lastid."_seq' )
THEN
   drop sequence posta_deniky_".$lastid."_seq;
END IF;

end$$;
";
echo $sql;
  $q = new DB_POSTA;
  $q->query($sql);
}

if (!$DELETE_ID && !$EDIT_ID) {$insert = 1;}

$lastid = Run_(array("showaccess"=>true,"outputtype"=>1));


$sql = 'select 1 ' . $insert;
if (($GLOBALS['NOVAHODNOTA'] == 1 || $insert == 1) && !$GLOBALS['DELETE_ID'])
 $sql="
do $$
begin
IF EXISTS (SELECT 0 FROM pg_class where relname = 'drop sequence posta_deniky_".$lastid."_seq' )
THEN
drop sequence posta_deniky_".$lastid."_seq;
END IF;
end$$;
CREATE SEQUENCE posta_deniky_".$lastid."_seq START 1 INCREMENT 1 MAXVALUE 2147483647 MINVALUE 1 CACHE 1;

";

if ($GLOBALS['NOVAHODNOTA'] > 1 && !$GLOBALS['DELETE_ID'])
 $sql="SELECT setval('posta_deniky_".$lastid."_seq', ".$GLOBALS['NOVAHODNOTA']."); COMMIT;";

$q = new DB_POSTA;
echo $sql;
$q->query($sql);

echo '
<script language="JavaScript" type="text/javascript">
  if (window.opener.document) {
    window.opener.document.location.reload();
  }
  window.close();
</script>
';

require_once(Fileup2("html_footer.inc"));  


