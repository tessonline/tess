<?php 
require("tmapy_config.inc");
require(FileUp2(".admin/classes/PoradiSpisovyZnak.php"));
$q = new DB_POSTA();
$insert = new DB_POSTA();
$psz = new PoradiSpisovyZnak();
$sql = 'select id,kod from cis_posta_skartace';
$q->query($sql);
$i = 0;
	while($q->Next_Record()) {
	  $i++;
		$kod = $q->Record['KOD'];
		$poradi = $psz->zjistiPoradi($kod);
		$sql = 'update cis_posta_skartace set priorita='.$psz->zjistiPoradi($kod).' where id='.$q->Record['ID'];
		$insert->query($sql);
	}
echo 'Updatovano '.$i.' zaznamu';



