<?php
require('tmapy_config.inc');
require(FileUp2('.admin/brow_.inc'));
require_once('.admin/classes/OneClickConnectorFactory.inc');
require_once('.admin/classes/EedConnectorFactory.inc');
require_once('.admin/classes/Task.inc');
require_once('.admin/classes/Utils.inc');

try {
  
  $templateData = array();
  $errorInfo = 'Úkol nebyl správně zapsán.';
  
  $eedConnector = EedConnectorFactory::getEedConnector();
  $eedConnector->login();
  $eedDocument = $eedConnector->getDocument(intval($DOKUMENT_ID));
  $eedDocument->files = $eedConnector->getFiles($eedDocument->id);
  $eedConnector->logout();
  
  // Ukol uz existuje - presmerovani na dany ukol na webu 1clicku.
  if (EedDocument::hasTask($eedDocument->id)) {

    $taskId = $eedDocument->getTaskId();
    $taskUrl = Task::getUrl($taskId);
    header('Location: ' . $taskUrl);
    die();
  } 
  // Ukol nebyl jeste vytvoren - vytvoreni ukolu.
  else {
  
    require_once(Fileup2('html_header_full.inc'));
    
    $userInfo = $GLOBALS['TMAPY_SECURITY']->GetUserInfo();

    $oneClickConnector = OneClickConnectorFactory::getOneClickConnector();
    $oneClickUsers = $oneClickConnector->getAllUsers();

    // Zadavatel
    $zadavatel = Utils::getOneClickId($oneClickUsers, $userInfo['LOGIN']);
    // Dle specifikace rozhrani: Pokud neexistuje uzivatel 1click,
    // zadavatel bude nastaven na uzivatele, pod kterym se prihlasil klient k webove sluzbe.
    if (!$zadavatel) {
      $login = $CONFIG['POSTA_INTERFACE_ONE_CLICK']['ONE_CLICK']['LOGIN'];
      $zadavatel = Utils::getOneClickId($oneClickUsers, $login);
    }

    $resitel = Utils::getOneClickId($oneClickUsers, Utils::getTwistLogin($eedDocument->zpracovatelId));
    $predmet = $eedDocument->vec;
    $zadani = $eedDocument->cisloJednaci;
    $prilohy = $eedDocument->files;

    $task = new Task(0, $resitel, $predmet, $zadani, $prilohy, $zadavatel);
    $result = $task->save($oneClickConnector, $eedDocument->id);    

    if ($result) {
      $templateData['info'] = 'Úkol byl správně zaloen do sluby 1click. Lze ho zobrazit na této adrese: ';
      $templateData['url'] = Task::getUrl($task->id);
    }
    else {
      $templateData['info'] = $errorInfo;
    }
  }      
}
catch (Exception $e) {
  $templateData['info'] = utf8_decode($e->getMessage()) . ' ' . $errorInfo;
}

$templateData = Utils::convertEncoding('Windows-1250', 'ISO-8859-2', $templateData);
include_once('.admin/templates/result.inc');

require_once(Fileup2('html_footer.inc'));
