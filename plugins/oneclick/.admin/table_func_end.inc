<?php
include_once(FileUp2('plugins/oneclick/.admin/classes/EedDocument.inc'));

function createOneClickLink($documentId, $referent) {

  static $agendaPath;

  if ($referent<1) return '';

  if (!$agendaPath) {
    $agendaPath = getAgendaPath('POSTA_PLUGINS', true, false) . '/oneclick';
  }

  $script = '/one_click.php?DOKUMENT_ID=' . $documentId;

  if (EedDocument::hasTask(intval($documentId))) {
    $src = $agendaPath  . '/images/cervena';
    $title = 'Otevřít úkol v aplikaci 1click';
    $target = '_blank';
    $href = $agendaPath . $script;
    $onclick = '';
  }
  else {
    $src = $agendaPath  . '/images/ukol_cerna.gif';
    $title = 'Vytvořit nový úkol v aplikaci 1click';
    $target = '';
    $href = '#';
    $onclick = "if (confirm('Chcete skutečně vytvořit nový úkol?')) {
window.open('$agendaPath$script', '1click', 'width=400, height=400, top=200, left=200');} return false;";
  }
  $src = FileUpImage('images/link');
  $img = '<img src="' . $src . '"  border=0>';
  $a = '<a title="' . $title . '" href="' . $href . '" target="' . $target . '" onclick="' . $onclick . '">' . $img . '</a>';

  return $a;
}

