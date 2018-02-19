<?php

$client = new soapclient($url_, false);
$client->soap_defencoding='UTF-8';
$client->decodeUTF8(false);
$err = $client->getError();
if ($err) {
    echo "<script>document.getElementById('upl_wait_message').style.display = 'none'</script>";
    echo $button_back;
    Die('DS systém není dostupný');
}
echo '';
Flush();
//Nakonekteno, jdeme odeslat emaily:
