<?php

if (!$doc_id) echo 'chyba predani parametru';
else {
  if (HasRole('spravce')) {
    echo '<h1>Úpravy pro adminy:</h1>';

    echo '<input type="button" name="" value="Pøepoèet stavu" class="btn" onclick="AdminPrepocet('.$doc_id.');"> ';
    echo '&nbsp;&nbsp;&nbsp;';
    echo '<input type="button" name="" value="Vymazání uzavøení spisu" class="btn" onclick="AdminVymaz('.$doc_id.');"> ';
    echo '&nbsp;&nbsp;&nbsp;';
    echo '<input type="button" name="" value="Oprava sekund" class="btn" onclick="AdminSekundy('.$doc_id.');"> ';
    echo '&nbsp;&nbsp;&nbsp;';
    echo '<input type="button" name="" value="Výpis pøístupù k danému èj" class="btn" onclick="AdminPristupy('.$doc_id.');"> ';
    echo '&nbsp;&nbsp;&nbsp;';
    echo '<input type="button" name="" value="Uzavøení spisu bez konverze" class="btn" onclick="AdminUzavreni('.$doc_id.');"> ';
    echo '&nbsp;&nbsp;&nbsp;';
    echo '<input type="button" name="" value="Smazat doruèenky DZ" class="btn" onclick="AdminDelDZ('.$doc_id.');"> ';
    echo "<script>
      function AdminPrepocet(doc_id) {
        NewWindowAgenda('/ost/posta/plugins/admins/prepocet.php?DOC_ID='+doc_id+'&cacheid=');
      }
      function AdminVymaz(doc_id) {
        NewWindowAgenda('/ost/posta/plugins/admins/vymaz.php?DOC_ID='+doc_id+'&cacheid=');
      }
      function AdminSekundy(doc_id) {
        NewWindowAgenda('/ost/posta/plugins/admins/sekundy.php?DOC_ID='+doc_id+'&cacheid=');
      }
      function AdminUzavreni(doc_id) {
        NewWindowAgenda('/ost/posta/plugins/admins/uzavrit.php?DOC_ID='+doc_id+'&cacheid=');
      }
      function AdminPristupy(doc_id) {
        NewWindowAgenda('".GetAgendaPath("POSTA_NASTAVENI_PRISTUPY",false,true)."/brow.php?AGENDA_ID='+doc_id+'&cacheid=');
      }
      function AdminDelDZ(doc_id) {
        NewWindowAgenda('/ost/posta/plugins/admins/delDZ.php?DOC_ID='+doc_id+'&cacheid=');
      }
     //-->
    </script>
    ";
  }
}



