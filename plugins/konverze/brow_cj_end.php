<?php

if (!$doc_id) echo 'chyba predani parametru';
else {
  echo '<h1>Autorizovaná konverze z moci úřední:</h1>';
  echo '<input type="button" name="" value="Konverze z listinné podoby" class="btn" onclick="KonverzeLE('.$doc_id.');"> ';
  echo '&nbsp;&nbsp;&nbsp;';
  echo '<input type="button" name="" value="Konverze z elektronické podoby" class="btn" onclick="showVyber('.$doc_id.');"> ';


  //NewWindow(array("fname" => "Agenda", "name" => "Agenda", "header" => true, "cache" => false, "window" => "edit"));

  echo "<script>
    function KonverzeLE(doc_id) {
      NewWindowAgenda('/ost/posta/plugins/konverze/index.php?cmd=KonvezeLE&RECORD_ID=&DOC_ID='+doc_id+'&cacheid=');
    }
    function showVyber(doc_id) {
      NewWindowAgenda('/ost/posta/plugins/konverze/select_file.php?DOC_ID='+doc_id+'&cacheid=');
    }
    function KonverzeEL(id,doc_id) {
      NewWindowAgenda('/ost/posta/plugins/konverze/index.php?cmd=KonvezeEL&RECORD_ID='+id+'&DOC_ID='+doc_id+'&cacheid=');
    }
   //-->
  </script>
  ";
}



