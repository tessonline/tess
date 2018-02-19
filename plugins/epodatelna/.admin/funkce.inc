<?php

//function TxtEncoding4Soap($txt){
//  $from = $GLOBALS["TMAPY_SECURITY"]->Security->configuration['charset'];
//  return iconv($from, 'UTF-8', $txt);
//}

function VratEmailPole($mbox, $mid, $prilohy=1) {
    // input $mbox = IMAP stream,  $mid = message id
    // output all the following:
    global $htmlmsg, $plainmsg, $charset, $attachments;
    // the message may in $htmlmsg,  $plainmsg,  or both
    $htmlmsg = $plainmsg = $charset = '';
    $attachments = array();


     //onma
    $header = imap_header($mbox,  $mid);
    $from = $header->from[0];
    $adresa = $from->mailbox."@".$from->host;
    $to = $header->to[0];
    $adresat = $to->mailbox."@".$to->host;
    $message['udate'] = $header->udate;
    $message['size'] = $header->size;
    $hlavicky = imap_rfc822_parse_headers(imap_fetchheader($mbox, $mid));

//    mb_internal_encoding("ISO-8859-2");
    mb_internal_encoding("UTF-8");
    $vec =  mb_decode_mimeheader($hlavicky->subject);
    $vec = str_replace('_', ' ', $vec);
    
    if (strpos($vec, '?Q?')) {
      $vec = imap_mime_header_decode ($vec);
      if (!eregi('UTF-8', $vec[0]->charset))
      {
        $vec = iconv($vec[0]->charset, 'UTF-8', $vec[0]->text);
        $vec .= iconv($vec[1]->charset, 'UTF-8', $vec[1]->text);
        $vec .= iconv($vec[2]->charset, 'UTF-8', $vec[2]->text);
        $vec .= iconv($vec[3]->charset, 'UTF-8', $vec[3]->text);
        $vec .= iconv($vec[4]->charset, 'UTF-8', $vec[4]->text);
        $vec .= iconv($vec[5]->charset, 'UTF-8', $vec[5]->text);
      }
    }
    
    $from = imap_mime_header_decode($header->fromaddress);
    $from = $from[0]->text;
    // zistíme,  či mail obsahuje aj prílohy
    $structure = imap_fetchstructure($mbox,  $mid);
  
    $parts = $structure->parts;
    $num_parts = sizeof($parts);
    $email['id']=$header->Msgno;
    $email['message_id']=$header->message_id;
    $email['from']=$adresa;
    $email['to']=$adresat;
    $email['name']=$from;
    $email['vec']=$vec;
    $email['datum']=date("j.n.Y H:i:s", $message['udate']);
    $email['prilohy']=$num_parts;
    $email['size']=$size;
  
    if ($prilohy==1) {
      // HEADER
      $h = imap_header($mbox, $mid);
      // add code here to get date,  from,  to,  cc,  subject...
  
      // BODY
      $s = imap_fetchstructure($mbox, $mid);
      if (!$s->parts)  // not multipart
          getpart($mbox, $mid, $s, 0);  // no part-number,  so pass 0
      else {  // multipart: iterate through each part
          foreach ($s->parts as $partno0=>$p)
              getpart($mbox, $mid, $p, $partno0+1);
      }
    }
    //else
    //      $charset='utf-8';
    $a=0;
    
    //echo "Charset je ".$charset;
//   echo "DEBUG: Mail od ".$adresa." má charset - ".$charset;
    if (!eregi('UTF-8', $charset))
    {
//      echo " - konvertuji tedy do ISO-8859-2 (".$email['vec'].")";
      $email['from']=iconv($charset, 'UTF-8', $email['from']);
//      $email['vec']=iconv($charset, 'ISO-8859-2', $email['vec']);
//      echo " - (".$email['vec'].")";
    }
    if (strlen($htmlmsg)>0 && $prilohy==1)
    {
      $email['soubor'][$a]['FILE_NAME']='mail_v_html.html';
      $email['soubor'][$a]['FILE_DATA']=base64_encode($htmlmsg);
      $a++;
    }
    if (strlen($plainmsg)>0 && $prilohy==1)
    {
      $email['vlastni_text']=$plainmsg;
    }
    if (strlen($email['vlastni_text'])<10) $email['vlastni_text']='Celý text emailu - viz. příloha';
    //if (strlen($email['vlastni_text'])>50) 
    	$email['vlastni_text']='Celý text emailu - viz. příloha';
    $email['vec'] = substr($email['vec'], 0, 101);
    if (count($attachments) && $prilohy==1)
    {
      while (list($key, $val)=each($attachments))
      {
//        if (eregi('.p7s', $key)) 
//        {
//          echo "rady";
//          ParsujCertifikatp7s($val);
//        }
//        else
        {
           mb_internal_encoding("UTF-8");
          $nazev=mb_decode_mimeheader($key);
          if (strtolower($nazev) == 'winmail.dat') {
             //soubory jsou v debilnim formatu..
             $tmp = $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["tmp_adresar"].'/EED_mail_'.$mid.'/';
             @mkdir ($tmp);
             $fp = fopen($tmp.'winmail.dat', 'w');
             fwrite($fp, $val);
             fclose($fp);
             $cmd = 'tnef -f ' . $tmp . 'winmail.dat -C ' . $tmp;
             exec($cmd, $output);
             if ($handle = opendir($tmp)) {
             while (false !== ($entry = readdir($handle))) {
               if ($entry != "." && $entry != ".." && $entry != "winmail.dat")
               {
                     $email['soubor'][$a]['FILE_NAME']=iconv('WINDOWS-1250','UTF-8', $entry);
                     $email['soubor'][$a]['FILE_DATA']=base64_encode(file_get_contents($tmp.$entry));
                     $a ++;
               }
             }
             closedir($handle);
            }
          } else {
            $email['soubor'][$a]['FILE_NAME']=TxtEncoding4Soap($nazev);
            $email['soubor'][$a]['FILE_DATA']=base64_encode($val);
          }
        }
        
        $a++;
      }    
    }
    return $email;
//print_r($attachments);

}

function getpart($mbox, $mid, $p, $partno) {
    // $partno = '1',  '2',  '2.1',  '2.1.3',  etc if multipart,  0 if not multipart
    global $htmlmsg, $plainmsg, $charset, $attachments;


    // DECODE DATA
    $data = ($partno)?
        imap_fetchbody($mbox, $mid, $partno):  // multipart
        imap_body($mbox, $mid);  // not multipart
    // Any part may be encoded,  even plain text messages,  so check everything.
    
    if ($p->encoding==4)
        $data = quoted_printable_decode($data);
    elseif ($p->encoding==3)
        $data = base64_decode($data);
    // no need to decode 7-bit,  8-bit,  or binary

    // PARAMETERS
    // get all parameters,  like charset,  filenames of attachments,  etc.
    $params = array();
    if ($p->parameters)
        foreach ($p->parameters as $x)
            $params[ strtolower( $x->attribute ) ] = $x->value;
    if ($p->dparameters)
        foreach ($p->dparameters as $x)
            $params[ strtolower( $x->attribute ) ] = $x->value;

    // ATTACHMENT
    // Any part with a filename is an attachment, 
    // so an attached text file (type 0) is not mistaken as the message.
    if ($params['filename'] || $params['name']) {
        // filename may be given as 'Filename' or 'Name' or both
        $filename = ($params['filename'])? $params['filename'] : $params['name'];
        // filename may be encoded,  so see imap_mime_header_decode()
        $attachments[$filename] = $data;  // this is a problem if two files have same name
    }

    // TEXT
    elseif ($p->type==0 && $data) {
        // Messages may be split in different parts because of inline attachments, 
        // so append parts together with blank row.
        if (strtolower($p->subtype)=='plain')
            $plainmsg .= trim($data) ."\n\n";
        else
            $htmlmsg .= $data ."<br><br>";
        $charset = $params['charset'];  // assume all parts are same charset
    }

    // EMBEDDED MESSAGE
    // Many bounce notifications embed the original message as type 2, 
    // but AOL uses type 1 (multipart),  which is not handled here.
    // There are no PHP functions to parse embedded messages, 
    // so this just appends the raw source to the main message.
    elseif ($p->type==2 && $data) {
        $plainmsg .= trim($data) ."\n\n";
    }

    // SUBPART RECURSION
    if ($p->parts) {
        foreach ($p->parts as $partno0=>$p2)
            getpart($mbox, $mid, $p2, $partno.'.'.($partno0+1));  // 1.2,  1.2.1,  etc.
    }

}


function UlozitMail($bbb, $sess, $superodbor) {
  global $mbox_eed,$client, $a;

  $USER_INFO = $GLOBALS["TMAPY_SECURITY"]->GetUserInfo();
  $id_user=$USER_INFO["ID"];
  $jmeno_uzivatele=$USER_INFO["FNAME"]." ".$USER_INFO["LNAME"];
  $LAST_USER_ID=$id_user?$id_user:9;
  $LAST_TIME=Date('H:i:s');
  $LAST_DATE=Date('Y-m-d');

  $q = new DB_POSTA;
  $status = 7;
  $email = VratEmailPole($mbox_eed,$bbb, 1);
  $header = imap_fetchheader($mbox_eed,$bbb);
  $content=imap_body($mbox_eed,$bbb);
  $mail_cely=$header.$content;
  $dorucenka=false;
  if (eregi('disposition-notification',$mail_cely))
  {
    eregi("Original-Message-ID: <(.+)\>",$mail_cely,$parts);
    $id=substr($parts[0],strpos($parts[0],'<')+1,(strpos($parts[0],'>')-strpos($parts[0],'<'))-1);
//    echo "ID je ".$id."<br/>";

    $sql="select dokument_id from posta_epodatelna where record_uid like '%".$id."%'";
//    echo $sql."<br/>";
    $q->query($sql);
    $q->Next_Record(); $dokument_id=$q->Record['DOKUMENT_ID'];

//    print_r($dokument_id);
    if ($dokument_id<1 || $id<1)
    {
      //nenasel jsem, k cemu je dorucenka, uloyime to jako samostatny email
      $dorucenka=false;
    }
    else
    {
      echo "Ukládám doručenku... <br/>"; Flush();
      $dorucenka=true;
      $sql="update posta set datum_doruceni='".$email['datum']."',last_date='$LAST_DATE',last_time='$LAST_TIME',last_user_id=$LAST_USER_ID where id=".$dokument_id;
  //echo $sql;
      $q->query($sql);
      $soubor[0]['FILE_NAME']="potvrzeni_doruceni.eml";
    }



  }
  if (!$dorucenka)
  {
    $dorucenka=false;
    $vytvorit_cj=1;
    if ($vytvorit_cj) {
      $EedSql = LoadClass('EedSql');
      $dokument_id = $EedSql->createCJ();
/*
      $result = $client->call('get_cj', array(
          'session_id'=>$session_id,
        )
      );
      if ($result['return']['RESULT']<>'OK') Die('nebylo vytvoreno CJ!!!');
      $dokument_id=$result['dokument_id'];
      $cislo_jednani=$result['cislo_jednaci'];
*/
    }
    else {
      $odeslani='01.01.2100 12:00';
      $rok=Date('Y');
      $odbor=0; $zpracovatel=0; $smer='f'; $odd=0;
      $sql="insert into posta (cislo_jednaci1,ev_cislo,stav,rok,odes_typ,odesl_prijmeni,odesl_posta,datum_podatelna_prijeti,odeslana_posta,odbor,oddeleni,referent,last_date,last_time,last_user_id) values (1,0,132,'$rok','P','".$jmeno."','".$vec."','".$odeslani."','".$smer."',".$odbor.",'".$odd."',".$zpracovatel.",'".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.")";
  //  echo "Jsem tu".$sql;
      $q->query($sql);
      $dokument_id=$q->getlastid("posta", "ID");

    }
    if (strpos($email[name],'@'))
      $emailova_adresa=$email[name];
    else
      $emailova_adresa=$email[from];

    echo "Zpracovávám email od ".htmlentities(TxtEncodingFromSoap($email[name]))."</pre><br/>"; Flush();

    $sql = "select * from security_user where email ilike '".$email['to']."'";
    $q->query($sql);
    $q->Next_Record();



    $sql="update posta set ";
    $sql.="vec='".$email['vec']."', ";
    $sql.="datum_podatelna_prijeti='".$email['datum']."', ";
    $sql.="odesl_email='".$emailova_adresa."', ";
    $sql.="odesl_subj='".$email['vec']."', ";
    $sql.="odesl_body='".$email['vlastni_text']."', ";
    $sql.="zpusob_podani='9', ";
    $sql.="druh_priloh='elektronické', ";
    $sql.="pocet_priloh='".$email['prilohy']."', ";

    if ($q->Record['ID']) {

      $pracovnik=OdborPrac($q->Record['ID']);
      $sql.="referent=".$q->Record['ID'].", ";
      $sql.="odbor='".($pracovnik['odbor']?$pracovnik['odbor']:0)."', ";

      if ($superodbor>0) $sql.="superodbor='".$superodbor."', ";
      else
        $sql.="superodbor='".($pracovnik['so']?$pracovnik['so']:0)."', ";

      $status = 3;
    }
    else {
      if ($superodbor>0) $sql.="superodbor='".$superodbor."', ";
      $sql.="poznamka='Adresát: ".$email['to']."', ";
    }


    $sql.="odes_typ='M', ";

    If ($GLOBALS["KONEKTOR"]["EPODATELNA"]["ZALOZIT_SPIS"])
  {
    $nazev_spisu=$GLOBALS["KONEKTOR"]["EPODATELNA"]["NAZEV_SPISU"]?$GLOBALS["KONEKTOR"]["EPODATELNA"]["NAZEV_SPISU"]:'';
    $sql.="
  cislo_spisu1=cislo_jednaci1,
  cislo_spisu2=cislo_jednaci2,
  nazev_spisu='".$nazev_spisu."',
  ";
  }


    $sql.="stav=0, lhuta=30, typ_dokumentu='D',  ";
    $sql.="status=$status ";

    $sql.="where id=".$dokument_id;
    //   echo $sql."
    //   ";
    $q->query($sql);

echo $sql;

    unset($soubor);
    $soubor = array();

    if (count($email['soubor'])>0)  $soubor = $email['soubor'];

    while (list($key, $val) = each($soubor)) {

      if (eregi('.p7s', $val[FILE_NAME])) {

        try {

          $signature = new SMimeFile($mail_cely);
          $emailObj = new Email($email, $signature);
          $valid = $emailObj->verify();
          $protocol = $emailObj->createProtocolContent('PDF');

          if (!$valid) {
            echo '<span style="color: red; font-weight: bold;">';
            echo 'Elektronický podpis není platný nebo se ho nepodařilo ověřit.';
            echo '</span><br />';
          }
        }
        catch (Exception $e) {
          echo '<span style="color: red; font-weight: bold;">';
          echo $e->getMessage();
          echo '</span><br />';
        }

        //konec MIER
//         $soubor[$key][FILE_NAME]='kontrola_podpisu.pdf';
//         $soubor[$key][FILE_DESC]=TxtEncoding4Soap('<i>protokol o přijetí emailu a kontrole el. podpisu</i>');
//         $soubor[$key][FILE_DATA]=base64_encode($protocol);
      }
    }

//    Die();
    $dalsi=count($soubor);
    //$dalsi=0;
    $soubor[$dalsi]['FILE_NAME']="prichozi_email.eml";
    $soubor[$dalsi]['FILE_DATA']=base64_encode($mail_cely);
    $soubor[$dalsi]['BIND_TYPE']='message/rfc822';
    $soubor[$dalsi]['FILE_DESC']=TxtEncoding4Soap('<i>celý email ve formátu .eml</i>');
    //$soubor[1]['FILE_DATA']=base64_encode($fdata);

//print_r($soubor);
//echo $GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"];
    if (strlen($GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"])>2) {
      include_once($GLOBALS['TMAPY_LIB'].'/upload/functions/SOAP_602_print2pdf.php');
      //pod stejnzm souborem ulozi
      $a=new SOAP_602_print2pdf($SERVER_CONFIG["UPLOAD_CONFIG"]["MODULES"]["table"]["STORAGE"]["Print2PDF_SERVICE"]);
      try {

        list($fname,$fdata)=$a->ConvertStream('prichozi_email.eml',$mail_cely,$GLOBALS["CONFIG_POSTA"]["HLAVNI"]["Print2PDF_TS_PROFIL"]);
        $dalsi++;
        $soubor[$dalsi]['FILE_NAME']="prichozi_email.pdf";
        $soubor[$dalsi]['FILE_DATA']=base64_encode($fdata);
        $soubor[$dalsi]['BIND_TYPE']='aplication/pdf';
        $soubor[$dalsi]['FILE_DESC']=TxtEncoding4Soap('<i>celý email ve formátu pdf opatřený časovým razítkem</i>');
      }
      catch (Exception $e) {
        echo '<span style="color: red; font-weight: bold;">';
        echo $e->getMessage();
        echo '</span><br />';
      }

    }

  }
//  print_r($soubor);
  echo "Ukládám přílohy... <br/>"; Flush();
  //echo "data jsou ".$soubor['FILE_DATA'];
  $adr = $GLOBALS[CONFIG_POSTA][HLAVNI][tmp_adresar] . 'epodatelna/';
  $virus = false;
  if (!is_dir($adr)) mkdir($adr);
  foreach($soubor as $file) {
    $uplobj=Upload(array('create_only_objects'=>true,'agenda'=>'POSTA','noshowheader'=>true,'skip_access'=>true));
    UNSET($GLOBALS['EDIT_ID']); //blbne pri ukladani, nesmi byt hodnota EDIT_ID
    $tmp_soubor = $adr . $file['FILE_NAME'];
    if (is_file($tmp_soubor)) unlink($tmp_soubor);

    $GLOBALS['DESCRIPTION'] = TxtEncodingFromSoap($val[FILE_DESC]);
    if (!$fp=fopen($tmp_soubor,'w')) echo '<font color=red>Chyba pri ulozeni tmp souboru '.$tmp_soubor.'</font><br/>';
    fwrite($fp, base64_decode($file['FILE_DATA']));
    fclose($fp);
$zavirovane_soubory = array();
    if (function_exists('cl_scanfile')) {
      $retcode = cl_scanfile($tmp_soubor, $virusname);
      if ($retcode == CL_VIRUS) {
//      if (1 == 1) {
//        $virusname = 'NAZEV VIRU';
          echo "<font color=red><b>Antivirová kontrola - soubor " . basename($tmp_soubor) . "- nalezen vir!: </b></font> - Virus $virusname <br/>"; Flush();
          echo "<font color=black><b>Příloha neuložena!</b> <br/>"; Flush();
          $virus = true;
          $zavirovane_soubory[basename($tmp_soubor)] = $virusname;
  //        echo "File path : ".$file."Return code : ".cl_pretcode($retcode)."Virus found name : ".$virusname;
      } else {
        echo "Antivirová kontrola v pořádku... <br/>"; Flush();
        $ret = $uplobj['table']->SaveFileToAgendaRecord(TxtEncodingFromSoap($tmp_soubor), $dokument_id);
        if (strlen($ret[err_msg])>5) echo '<font color=red>Chyba pri ulozeni souboru '.$val["FILE_NAME"].': '.$ret[err_msg].'</font><br/>';
      }
    }
    else {
      $ret = $uplobj['table']->SaveFileToAgendaRecord(TxtEncodingFromSoap($tmp_soubor), $dokument_id);
      if (strlen($ret[err_msg])>5) echo '<font color=red>Chyba pri ulozeni souboru '.$val["FILE_NAME"].': '.$ret[err_msg].'</font><br/>';
    }
    if (is_file($tmp_soubor)) unlink($tmp_soubor);
    unset($plobj);

  }
  echo 'Přílohy uloženy ... <br/>'; Flush();


  //odesleme potvrzeni o doruceni, pouze pokud je vyplnena polozka text_emailu
  if (strlen($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu"])>2 && !$dorucenka && $status<10 && !$virus) {
    echo "Odesílám potvrzení o přečtení... <br/>"; Flush();
    OdesliPodepsanyEmail($emailova_adresa,$email['datum'],$email['vec'],$cislo_jednani,$jmeno_uzivatele);
    $text = 'dokument (<b>'.$dokument_id.'</b>) byl založen načtením z ePodatelny';
    EedTransakce::ZapisLog($dokument_id, $text, 'DOC');
  }
  //odesleme potvrzeni o doruceni, pouze pokud je vyplnena polozka text_emailu
  if (strlen($GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["text_emailu_vir"])>2 && !$dorucenka && $status<10 && $virus) {
    echo "Odesílám informaci o zavirovaném podání... <br/>"; Flush();
    OdesliPodepsanyEmailVir($emailova_adresa,$email['datum'],$email['vec'],$cislo_jednani,$jmeno_uzivatele,$zavirovane_soubory);
//    $sql="update posta set stornovano='Zavirované přílohy', status=-1 where id=".$dokument_id;
//    $q->query($sql);
    $text = 'dokument (<b>'.$dokument_id.'</b>) byl založen načtením z ePodatelny, ale některé přílohy byly zavirovené';
    EedTransakce::ZapisLog($dokument_id, $text, 'DOC');
    EedTransakce::ZapisLog(0, $text, 'SECURITY');
    echo "Ukládám email do složky karanteny... <br/>"; Flush();
    imap_mail_move($mbox_eed,$bbb, $GLOBALS["CONFIG_POSTA"]["EPODATELNA"]["eed_karantena"] );
  }

  echo "Ukládám informaci o načtení emailu... <br/>"; Flush();
  $sql="insert into posta_epodatelna (mailbox,smer,uid,record_uid,dokument_id,last_date,last_time,last_user_id)
  VALUES ('".$name_of_eed_folder."','f',".$email[id].",'".$email[message_id]."',$dokument_id,'".$LAST_DATE."','".$LAST_TIME."',".$LAST_USER_ID.");
  ";
  //echo $sql;
  $q->query($sql);

  echo "Hotovo.<br/>"; Flush();
}