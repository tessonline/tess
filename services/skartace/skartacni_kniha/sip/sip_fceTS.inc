<?php


function tSkartacniRezim(&$pole, $data) {
  $spisovna = getDataSpisovna($data['ID']);
  $SkartacniRezim = $pole->addChild('SkartacniRezim');
  $identSkartace = $SkartacniRezim->addChild('Identifikator', $spisovna['ID']);
  $identSkartace->addAttribute('zdroj', 'ERMS');
  $SkartacniRezim->addChild('Nazev', ($data['SKARTACE']));
  $SkartacniRezim->addChild('Oduvodneni', ('podle platného typového skartačního rejstříku'));
  $SkartacniRezim->addChild('SkartacniZnak', $data['SKAR_ZNAK']);
  $SkartacniRezim->addChild('SkartacniLhuta', $data['LHUTA']);
  $SkartacniRezim->addChild('SpousteciUdalost', ('uzavření spisu'));
}

function tDataceVyrazeni(&$pole, $data) {
  $dataceVyrazeni = $pole->addChild('DataceVyrazeni');
  $dataceVyrazeni->addChild('RokSpousteciUdalosti', $data['ROK_PREDANI']);
  $dataceVyrazeni->addChild('RokSkartacniOperace', $data['ROK_SKARTACE']);
}

function tSkartacniRizeni(&$pole, $data) {
  $skartacniRezim = $pole->addChild('SkartacniRizeni');
}


function tPuvodSeskupeni(&$pole, $data) {
  $puvod = $pole->addChild('Puvod');
  $puvod->addChild('DatumVytvoreni', $data['DATUM_OTEVRENI']);
}

function tMaterskaEntitaSoucasti(&$pole, $soucast) {
  $spis = $pole->addChild('Spis');
  getSpisInfo($spis, $data); //predat data o prvotnim dokumentu
}

function tTrideniSoucasti(&$pole, $soucast) {
  $entita = $pole->addChild('MaterskaEntita');
  tMaterskaEntitaSoucasti($entita, $soucast);
}

function tEvidencniUdajeSoucasti(&$pole, $soucast) {
  $EvidencniUdaje = $pole->addChild('EvidencniUdaje');
  tPuvodSeskupeni($EvidencniUdaje, $soucast);
  tTrideniSoucasti($EvidencniUdaje, $soucast);
  tVyrazovani($EvidencniUdaje, $soucast);
  tManipulaceSeskupeni($EvidencniUdaje, $soucast);

}

function tSoucast(&$pole, $soucast) {
  tEvidencniUdajeSoucasti($pole, $soucast);
//  tZaznamOHistorii($pole);
}

function tMaterskaEntitaDilu(&$pole, $dil) {
  $soucast = &$pole->addChild('Soucast');
  tSoucast($soucast, $dil);
}

function tTrideniDilu(&$pole, $dil) {
  $trideni = $pole->addChild('Trideni');
  tMaterskaEntitaDilu($trideni, $dil);
}



function tVyrazovani(&$pole, $dil) {
  $vyrazovani = $pole->addChild('Vyrazovani');
   tSkartacniRezim($vyrazovani, $dil);
   tDataceVyrazeni($vyrazovani, $dil);
   tSkartacniRizeni($vyrazovani, $dil);

}

function tManipulaceSeskupeni(&$pole, $data) {
  $Manipulace = $pole->addChild('Manipulace');
  $Manipulace->addChild('DatumOtevreni', $dil['DATUM_OTEVRENI']); //Otevreni
}



function tEvidencniUdajeDilu(&$pole, $dil) {
   $EvidencniUdaje = $pole->addChild('EvidencniUdaje');
   tPuvodSeskupeni($EvidencniUdaje, $dil);
//   tTrideniDilu($EvidencniUdaje, $dil);
//   tVyrazovani($EvidencniUdaje, $dil);
   tManipulaceSeskupeni($EvidencniUdaje, $dil);


}


function getDilInfo(&$spis, $data) {
  $dil = $spis->AddChild('Dil');
  $Identifikace = $dil->addChild('Identifikace');

  $identifikator = $Identifikace->addChild('Identifikator', $data['JID']);
  $identifikator->addAttribute('zdroj', 'ERMS');
  tEvidencniUdajeDilu($dil, $data);

   $Dokumenty = $dil->addChild('Dokumenty');
   //nacist dokumenty v dilu aprohnat pres
   $cj = LoadClass('EedCj', 0);
   $cjs = $cj->SeznamCJvTypovemSpisu($data['TYPOVY_SPIS_ID'], $data['SOUCAST'], $data['DIL']);
   $xx = new DB_POSTA;
   foreach ($cjs as $cjDoc) {
     $sql = 'select * from posta where id=' . $cjDoc;
     $xx->query($sql); $xx->Next_Record(); $data = $xx->Record;
     getDokument($Dokumenty, $data);
   }
}


function getTypSpisInfo($data, $typovy_spis_id) {
  $cj = LoadClass('EedCj', 0);
  $pole = $cj->getObsahTypSpis($typovy_spis_id);

  foreach($pole['soucast'] as $idSoucast => $soucast) {

    foreach($soucast['dil'] as $idDil => $dil) {
      getDilInfo($data, $dil);
    }

  }
//   print_r($pole);
//   Die();
//<Dil ID="ESS_SPSPISIDENTIFIKATOR" xmlns="nsesss">
//</Dil>


  getDilInfo($data, $dil);

}