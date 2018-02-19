<?php
require("tmapy_config.inc");
include(FileUp2(".admin/brow_.inc"));

    $q=new DB_POSTA;
    $q->query ("update POSTA SET CISLO_SPISU1='$CISLO_SPISU1' where id=$ID");
    $q->query ("update POSTA SET CISLO_SPISU2='$CISLO_SPISU2' where id=$ID");
    $q->query ("update POSTA SET PODCISLO_SPISU='0' where id=$ID");
    echo "      <script language=\"JavaScript\" type=\"text/javascript\">
           window.close();
         
      //-->
      </script>
";
?>
