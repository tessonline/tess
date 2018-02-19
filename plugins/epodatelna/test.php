<?php
require("tmapy_config.inc");
include('.admin/podpis.inc');
require(FileUp2(".admin/nastaveni.inc"));
require(FileUp2(".admin/funkce.inc"));
require(FileUp2(".admin/soap_funkce.inc"));
OdesliPodepsanyEmail('onma@tmapy.cz','14.12.2008','Podani','CJ/205/2008','Jan Nov8k');
