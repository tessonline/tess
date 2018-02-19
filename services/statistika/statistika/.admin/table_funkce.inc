<?php
Function ShowOdkaz($ident,$pocet) {
  $res = '<a href="/ost/posta/services/spisovka/denik/index.php?frame&'.$GLOBALS['COLUMN_IDENT'].'='.$ident.'&POSTA_VYHLEDAVANI=1" target="POSTA_DENIK">'.$pocet.'</a>';
  return $res;
}


