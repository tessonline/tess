<?php

//$GLOBALS['PROPERTIES_DEBUG']['SHOW_SQL'] = true;
//$GLOBALS['PROPERTIES_DEBUG']['SHOW_ACCESS'] = true; 

//include_once(FileUp2('.admin/db/db_default.inc'));

global $config;

$config['POSTA_DS_FILTRY']['DB_NAME'] = 'DB_DEFAULT';
$config['POSTA_DS_FILTRY']['DEFAULT_LANG'] = 'cz_utf-8';


$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmID']['label'] = 'ID datové zprávy';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dbIDSender']['label'] = 'ID datové schránky odesílatele';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSender']['label'] = 'Odesílatel slovně';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderAddress']['label'] = 'Poštovní adresa odesílatele';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderType']['label'] = 'Hrubý typ schránky odesílatele';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipient']['label'] = 'Příjemce slovně';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipientAddress']['label'] = 'Poštovní adresa příjemce';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderOrgUnit']['label'] = 'Organizační jednotka odesílatele slovně';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderOrgUnitNum']['label'] = 'Organizační jednotka odesílatele hodnotou z číselníku';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dbIDRecipient']['label'] = 'ID datové schránky příjemce';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipientOrgUnit']['label'] = 'Organizační jednotka příjemce slovně';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipientOrgUnitNum']['label'] = 'Organizační jednotka příjemce hodnotou z číselníku';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmToHands']['label'] = 'K rukám - pomocný údaj';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmAnnotation']['label'] = 'Textová poznámka (věc)';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipientRefNumber']['label'] = 'Číslo jednací za strany příjemce';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderRefNumber']['label'] = 'Číslo jednací za strany odesílatele';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmRecipientIdent']['label'] = 'Spisová značka ze strany příjemce';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmSenderIdent']['label'] = 'Spisová značka a strany odesílatele';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmLegalTitleLaw']['label'] = 'Zmocnění - číslo zákona';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmLegalTitleYear']['label'] = 'Zmocnění - rok vydání zákona';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmLegalTitleSect']['label'] = 'Zmocnění - paragraf v zákoně';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmLegalTitlePar']['label'] = 'Zmocnění - odstavec v paragrafu';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmLegalTitlePoint']['label'] = 'Zmocnění - písmeno v odstavci';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmPersonalDelivery']['label'] = 'Příznak Do vlastních rukou';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmAllowSubstDelivery']['label'] = 'Náhradní doručení povoleno/nepovoleno';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmMessageStatus']['label'] = 'Stav DZ';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmAttachmentSize']['label'] = 'Velikost přílohy v kilobajtech';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmDeliveryTime']['label'] = 'Čas dodání do DS';
$config['POSTA_DS_FILTRY']['DM_ITEMS']['dmAcceptanceTime']['label'] = 'Čas doručení';

$config['POSTA_DS_FILTRY']['ED_ITEMS']['superodbor']['label'] = 'Pracoviště';
$config['POSTA_DS_FILTRY']['ED_ITEMS']['odbor']['label'] = 'odbor';
$config['POSTA_DS_FILTRY']['ED_ITEMS']['referent']['label'] = 'zpracovatel';
