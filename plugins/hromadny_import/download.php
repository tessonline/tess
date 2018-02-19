<?php 
require('tmapy_config.inc');
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
$filename = $_GET['file'];
$param = $_GET['param'];





$i=0;
while ((!file_exists($filename))&&($i<5)) {
  $i++;
  echo $filename."<br />";
  sleep(1)       ;
}

if (file_exists($filename)) {
  header('Content-Description: File Transfer');
  header('Content-Type: application/octet-stream');
  header("Content-Disposition: attachment; filename*=UTF-8''".urlencode(basename($filename)));
  header('Expires: 0');
  header('Cache-Control: must-revalidate');
  header('Pragma: public');
  header('Content-Length: ' . filesize($filename));
  
  /*if ($_GET['all']==1) {
    foreach (glob(dirname($filename)."/*.zip") as $file) {
      $file = "\"".$file."\"";
      readfile("\"".$file."\"");
    }
    
  } else*/
  
  readfile($filename);
  //smaze docasny adresar vcetne souboru
 /* if (!isset($_GET['redirect_false'])) { 
  $temp = new Temp(dirname($filename), true);
  $temp->delTempDir();
  }*/
}              


if (!isset($_GET['redirect_false'])) { 

?>
<script>
  window.location.href='import2.php?id=<?php echo $param;?>&dalsi_krok=1';
</script>
<?php 
}