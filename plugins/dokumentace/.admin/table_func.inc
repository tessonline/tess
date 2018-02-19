<?php
require_once(FileUp2('.admin/upload_.inc'));

function zobrazDokumentace($id) {
  $upload = Upload(array('create_only_objects' => true, 'agenda' => $PROPERTIES['AGENDA_IDENT'], 'noshowheader' => true));
  $upload_records = $upload['table']->GetRecordsUploadForAgenda($id);
  $highest_id = 0;
  if (count($upload_records) < 1) {
    return '';
  }
  $html = '';
  foreach ($upload_records as $record) {
    if ($record['ANONYM'] == 't' || $record['ANONYM'] == 'y' || $record['ANONYM'] == '1') {
      $html .= '<a href="ug_file.php?DOWNLOAD='.$record['ID'].'&ID='.$id.'" target="_blank">'.$record['NAME'].'</a><br />';
    }
  }
  return $html;
}

function ShowNazev($nazev, $text, $id) {
  if (!$text || strlen($text)<2) return $nazev;
  else {
    $href = '<a href="show.php?ID=' . $id . '" title="Zobrazit text" target="dokumentace">' . $nazev . '</a>';
    return $href;
  }
}

