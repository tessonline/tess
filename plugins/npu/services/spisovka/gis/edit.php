<?php
require("tmapy_config.inc");
session_start();
$site = 'http://npu-gis.matej5.tmapserver.cz';
$url = '/tms/npu_uz/index.php?client_type=map_resize&Project=TMS_NPU_UZIDENT&client_lang=cz_win&strange_opener=0&interface=tmv&Theme=clear_sel';

UNSET($_SESSION['gis_spis_id']);
$_SESSION['gis_spis_id'] = $GLOBALS['DOKUMENT_ID'];

Header("Location: $site.$url");
