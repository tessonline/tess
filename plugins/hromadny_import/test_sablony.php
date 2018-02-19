<?php 
require('tmapy_config.inc');
include_once(FileUp2('.admin/upload_.inc'));
include_once(FileUp2('.admin/classes/dokument/Rtf.php'));
include_once(FileUp2('.admin/classes/dokument/Docx.php'));
include_once(FileUp2('.admin/classes/dokument/Temp.php'));
include_once(FileUp2('.admin/status.inc'));

$uplobj = Upload(array(
  'create_only_objects' => true,
  'agenda' => 'POSTA_HROMADNY_IMPORT',
  'noshowheader' => true,
));

$importFiles = array();
$upload_records = $uplobj['table']->GetRecordsUploadForAgenda($id);
while (list($key, $val) = each($upload_records)) {
  if (strpos($val['NAME'], 'import_log') === false) {
    $importFiles[] = $val;
  }
}

$DOC = "Rtf";


  foreach ($importFiles  as $val) {
    $ext = pathinfo($val['NAME'], PATHINFO_EXTENSION);
    if ($val['TYPEFILE'] == 'text/csv') {
      $datafile = $uplobj['table']->GetUploadFiles($val);
    }
    if ($val['TYPEFILE'] == 'application/rtf') {
      $rtf_template_data = $uplobj['table']->GetUploadFiles($val);
      $rtf_template = $val['NAME'];
    }
    if (strtolower ($ext) == 'docx') {
      $rtf_template_data = $uplobj['table']->GetUploadFiles($val);
      $rtf_template = $val['NAME'];
      $DOC = "Docx";
    }
  }

  $data = explode(chr(10), $datafile);

  $l = 0;
  $var_array = array();
  $data_array = array();
  foreach($data as $line) {
    if ((strlen($line)>1)&&(substr_count($line,';')<(strlen($line)-1))) {
      $l++;
      $var = false;
      if ($l ==1) $var = true;
          foreach (str_getcsv($line,";") as $cell) {
             if ($var) $var_array[] = $cell; 
             else 
                 $data_array[$l][] = iconv('CP1250', 'UTF-8', $cell);
          }
    }
  }
  
  $temp = new Temp($GLOBALS['CONFIG_POSTA']['HLAVNI']['tmp_adresar']);
  $rtf = new $DOC($rtf_template_data,$var_array);
  if ($DOC=="Docx") $rtf->setEncoding("UTF-8");
 // $rtf->setDb(new DB_POSTA);
  $path_parts = pathinfo($rtf_template);
  
  $data_item = $data_array[2];
  $doc_id = 1;
  //nahrazeni promennych v RTF a vytvoreni prislusnych souboru
  $dest = $temp->getTempDir()."/".$doc_id.".".$path_parts['extension'];
 // $rtf->csv_only = true;
  $rtf->process($dest,$data_item,$doc_id);  
  
  $vysledny = file_get_contents($dest);
  $temp->delTempDir();
  $nazev = $rtf_template;
  
  $ext = "msword";
    
  Header("Content-Type: application/".$ext);
  Header("Content-Disposition: attachment;filename=$nazev");
    
  Header("Pragma: cache");
  Header("Cache-Control: public");
        
  echo $vysledny;
  

  
  