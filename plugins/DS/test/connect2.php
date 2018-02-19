<?php
require("tmapy_config.inc");
include(FileUp2(".admin/run2_.inc"));
include(FileUp2("nastaveni.inc"));
require_once(FileUp2(".admin/db/db_posta.inc"));
require_once(FileUp2(".admin/oth_funkce.inc"));
include(FileUp2(".admin/isds_.inc"));
//inicializace NuSOAP

/*
// def. datovych typu

$obalka = array(
	'dmSenderOrgUnit' => $SenderOrgUnit,  //nepovinne
	'dmSenderOrgUnitNum' => $SenderOrgUnitNum,  //nepovinne
	'dbIDRecipient' => $IDRecipient, //ID datove schranky!
	'dmRecipientOrgUnit' => $RecipientOrgUnit,  //nepovinne
	'dmRecipientOrgUnitNum' => $RecipientOrgUnitNum, //nepovinne
	'dmToHands' => $ToHands, //nepovinne, textove komu je urceno
	'dmAnnotation' => $Annotation, //vec
	'dmRecipientRefNumber' => $RecipientRefNumber, //jejich spis
	'dmSenderRefNumber' => $SenderRefNumber, //nas spis
	'dmRecipientIdent' => $RecipientIdent,  //jejich cj
	'dmSenderIdent' => $SenderIdent, //nas spis
	'dmLegalTitleLaw' => $LegalTitleLaw, //zmocneni zakon
	'dmLegalTitleYear' => $LegalTitleYear, //zmocneni rok
	'dmLegalTitleSect' => $LegalTitleSect, //zmocneni paragraf
	'dmLegalTitlePar' => $LegalTitlePar, //zmocneni odstavec
	'dmLegalTitlePoint' => $LegalTitlePoint, //zmocneni pismeno 
	'dmPersonalDelivery' => $PersonalDelivery, //zasilka do vlastnich rukou
	'dmAllowSubstDelivery' => $AllowSubstDelivery //nahradni doruceni (durceni fikci)
);

$soubor=array(
	'dmMimeType'=>$MimeType, //mimetype, nevyuziva se
	'dmFileMetaType'=>$MetaType, //druh pisemnosti, prvni musi byt typ main!
	'dmFileGuid'=>$Guid, //interni oznaceni dokumentu, nepouziva se v DS
	'dmUpFileGuid'=>$UpFileGuid, //interni oznaceni dokumentu, nepouziva se v DS
	'dmFileDescr'=>$FileDescr, //popis souboru
	'dmFormat'=>$Format, //nepovinne, 
	'dmEncodedContent'=>$file
	);

$MessageCreateInput = array(
	'dmEnvelope' => $obalka,
	'dmFiles' => $soubor
);	
*/

$schranka=new ISDSbox($username,$password,'');
if (!$schranka->ValidLogin)
{
	echo ("Nepodarilo se pripojit k ISDS. ErrorInfo: ".$schranka->ErrorInfo);
	exit();
}
/*
$dbOwnerInfo=array('dbID' => 'm3raaxi1');
if (!$schranka->CheckDataBox($dbOwnerInfo)) Die('Chyba: '.$schranka->StatusMessage);
*/
/*

//Vyhledani DS
$dbOwnerInfo=array('dbType'=>'OVM','ic'=>'8181181');
$hodnoty=$schranka->FindDataBox($dbOwnerInfo);


//Test DS, zda existuje
$dbOwnerInfo=array('dbID' => 'm3raaxi1');
if (!$schranka->CheckDataBox($dbOwnerInfo)) Die('Chyba: '.$schranka->StatusMessage);

//Seznam dorucenych zprav
$dnes='2009-05-18T00:00:00';	
$zitra='2009-05-19T00:00:00';
if (!$hodnoty=$schranka->GetListOfReceivedMessages($dnes,$zitra,0)) Die('Chyba: '.$schranka->StatusMessage);
print_r($hodnoty);

//Seznam odeslanych zprav
$dnes='2009-05-18T00:00:00';	
$zitra='2009-05-19T00:00:00';
if (!$hodnoty=$schranka->GetListOfSentMessages($dnes,$zitra)) Die('Chyba: '.$schranka->StatusMessage);

//Ukaz info o doruceni dokumentu
$message=1;
if (!$hodnoty=$schranka->GetDeliveryInfo($message)) Die('Chyba: '.$schranka->StatusMessage);

//Ukaz podepsane info o doruceni dokumentu
$message=1;
if (!$hodnoty=$schranka->GetSignedDeliveryInfo($message)) Die('Chyba: '.$schranka->StatusMessage);

//Oznaceni zpravy jako Prectena
$message=1;
if (!$hodnoty=$schranka->MarkMessageAsDownloaded($message)) Die('Chyba: '.$schranka->StatusMessage);

//Nacteni obalky k dane zprave
$message=1;
if (!$hodnoty=$schranka->MessageEnvelopeDownload($message)) Die('Chyba: '.$schranka->StatusMessage);

//stazeni hashe zpravy (pro kontrolu zpravy)
$message=1;
if (!$hodnoty=$schranka->VerifyMessage($message)) Die('Chyba: '.$schranka->StatusMessage);

//odeslani dokumentu
if (!$hodnoty=$schranka->CreateMessage($MessageCreateInput)) Die('Chyba: '.$schranka->StatusMessage);

//stazeni dane zpravy
$message=1;
if (!$hodnoty=$schranka->MessageDownload($message)) Die('Chyba: '.$schranka->StatusMessage);

//stazeni dane zpravy s podpisem MV
$message=1;
if (!$hodnoty=$schranka->SignedMessageDownload($message)) Die('Chyba: '.$schranka->StatusMessage);


//stazeni odeslane zpravy s podpisem MV
$message=1;
if (!$hodnoty=$schranka->SignedSentMessageDownload($message)) Die('Chyba: '.$schranka->StatusMessage);

*/

//$message=5231;
//$hodnoty=$schranka->VerifyMessage($message);

$message=1;
if (!$hodnoty=$schranka->MarkMessageAsDownloaded($message)) Die('Chyba: '.$schranka->StatusMessage);

print_r($hodnoty);
