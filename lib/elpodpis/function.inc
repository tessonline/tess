<?php

require(FileUp2('lib/pdf/pdf.php'));

/**
 * Vytvori soubor, ktery obsahuje el. podpis ve formatu PKCS7, z retece v base64
 * (Je mozne nahradit linuxovym prikazem: openssl smime -pk7out -in test.eml -out test.pkcs7.)
 *
 * @param string $file_data Base64 retezec (bez mezer a enteru) vytazeny ze souboru s/mime
 * @return string $pkcs7_filepath Cesta k PKCS7 souboru
 */

function createPkcs7File($file_data) {

  $data_length = strlen($file_data);		
  $line_length = 72;
  $content = '';
  
  // Obsah souboru musi mit dlouhe radky maximalne 72 znaku
  for ($i = 0; $i < $data_length; $i += $line_length) {
    $content .= substr($file_data, $i, $line_length) . "\n";
  }
      
  $header_line = '-----BEGIN PKCS7-----';
  $footer_line = '-----END PKCS7-----';
  $pkcs7_format = $header_line . "\n" . $content . $footer_line . "\n";
  
  // Vytvoreni docasneho souboru ve slozce /tmp
  $dir = '/tmp/';
  if (is_dir($dir)) {
  
    $pkcs7_filepath = $dir . 'e_signature_' . uniqid() . '.p7s';
    $pkcs7_file = fopen($pkcs7_filepath, 'w+');
    
    if ($pkcs7_file) {
    
      fwrite($pkcs7_file, $pkcs7_format);
      fclose($pkcs7_file);
      
      return $pkcs7_filepath;
    }
    else {
      throw new Exception('Soubor PKCS7 se nepodařilo vytvořit.');
    }
  }
  else {
    throw new Exception("Adresář ($dir) pro uložení souboru PKCS7 neexistuje.");
  }    
}

/**
 * Vytvori soubor obsahujici el. podpis ve formatu PEM, ze souboru, ktery odpovida formatu PKCS7
 *
 * @param string $pkcs7_filepath Cesta k PKCS7 souboru
 * @return string $pem_filepath Cesta k PEM souboru
 */

function createPemFile($pkcs7_filepath) {
  
  if (file_exists($pkcs7_filepath)) {
   
    $dir = '/tmp/';
    if (is_dir($dir)) {
    
      $info = pathinfo($pkcs7_filepath);
      $pkcs7_filename =  basename($pkcs7_filepath, '.' . $info['extension']);
      $pem_filepath = $dir . $pkcs7_filename . '.pem';
      
      if (file_exists($pem_filepath)) {
        unlink($pem_filepath);
      }
      
      $openssl_shell_cmd = "openssl pkcs7 -print_certs -in $pkcs7_filepath -out $pem_filepath";
      exec($openssl_shell_cmd);        
      
      if (file_exists($pem_filepath)) {
        return $pem_filepath;
      }
      else {
        throw new Exception('Soubor PEM se nepodařilo vytvořit.');
      }
    }
    else {
      throw new Exception("Adresář ($dir) pro uložení souboru PEM neexistuje.");
    }
  }
  else {
    throw new Exception("Soubor ($pkcs7_filepath) pro vytvoření souboru PEM neexistuje.");
  }   
}

/**
 * Overi platnost certifikatu
 *
 * @param string $pem_filepath Cesta k certifikatu, ktery je ve formatu PEM
 * @param string $output_msg
 * @param string $ca_dirpath
 * @return bool $is_valid Kdyz je certifikat platny pak true, jinak false
 */

function verifyCertificate($pem_filepath, &$output_msg, $ca_dirpath = '') {
  
  $is_valid = false;
  $output_msg = '';
  
  if (file_exists($pem_filepath)) {
    
    $ca_path_options = '';
    
    if (!empty($ca_dirpath)) {  
      if (is_dir($ca_dirpath)) {
        $ca_path_options = "-CApath $ca_dirpath";
      }
      else {
        throw new Exception("Adresář ($ca_dirpath) s důvěryhodnými certifikáty neexistuje.");
      }
    }
    
    $openssl_shell_cmd = "openssl verify $ca_path_options $pem_filepath";
    $output = array();
    exec($openssl_shell_cmd, $output);
    
    if (count($output) == 1) {
      $output_msg = 'Certifikát subjektu, který podepsal email, je platný.';
    }
    else {
      $output_msg = "Certifikát subjektu, který podepsal email, se nepodařilo ověřit. ";
      $output_msg .= "Důvod: {$output[count($output) - 1]}";
    }
  }
  else {
    throw new Exception("Soubor ($pem_filepath) obsahujici certifikat ve formatu PEM neexistuje.");
  }   
  
  return $is_valid;
}

/**
 * Vytvori obsah txt souboru, ktery slouzi jako protokol o prijeti emailu
 *
 * @param array $email Polozky emailu
 * @param array $e_signature El. podpis
 * @param string $verify_output_msg Zprava o verifikaci certifikatu subjektu,
 *  ktery email elektronicky podepsal
 * @return string $txt_content Obsah txt souboru
 */

function getProtocolAsTxt(array $email, array $e_signature) {
  
  $time = date('j.n.Y g:i:s');
  
  $txt_content = '';
  
  $txt_content .= "Protokol o přijetí e-mailu " . $email['message_id'] . "\n\n";
  
  $txt_content .= " Odesílatel: " . $email['name'] . " &lt;" . $email['from'] . "&gt;\n";
  $txt_content .= " Věc: " . $email['vec'] . "\n";
  $txt_content .= " Čas odeslání emailu: " . $email['datum'] . "\n";
  $txt_content .= " Čas doručení emailu: " . '?' . "\n";
  $txt_content .= " Čas ověření el. podpisu: " . $time . "\n";
  $txt_content .= " Čas přijetí emailu: " . $time . "\n";
  $txt_content .= " Přílohy:\n";
  $i = 0;
  foreach ($email['soubor'] as $attachment) {
    if (!preg_match('/\.p7s$/', $attachment['FILE_NAME'])) {
      $i++;
      $size = strlen(base64_decode($attachment['FILE_DATA']));
      $txt_content .= "  Soubor č. $i: " . $attachment['FILE_NAME'] . " ($size Bytes)\n";
    }    
  }
  $txt_content .= "\n";
  
  $txt_content .= "Digitální podpis:\n\n";
  
  $txt_content .= "Předmět: \n";
  $txt_content .= " C: " . encde_text($e_signature['subject']['C']) . "\n";
  $txt_content .= " CN: " . encde_text($e_signature['subject']['CN']) . "\n";
  $txt_content .= " O: " . encde_text($e_signature['subject']['O']) . "\n";
  $txt_content .= " L: " . encde_text($e_signature['subject']['L']) . "\n";
  $txt_content .= " ST: " . encde_text($e_signature['subject']['ST']) . "\n";
  $txt_content .= " Serial number: " . encde_text($e_signature['subject']['serialNumber']) . "\n";
  
  $txt_content .= "Verze certifikátu: " . encde_text($e_signature['version']) . "\n";
  
  $txt_content .= "Sériové číslo certifikátu: " . encde_text($e_signature['serialNumber']) . "\n";
  
  $txt_content .= "Platnost od: " . date('j.n.Y g:i:s', $e_signature['validFrom_time_t']) . "\n";  
  $txt_content .= "Platnost do: " . date('j.n.Y g:i:s', $e_signature['validTo_time_t']) . "\n";
  
  $txt_content .= "Vydavatel: \n";
  $txt_content .= " OU: " . encde_text($e_signature['issuer']['OU']) . "\n";
  $txt_content .= " O: " . encde_text($e_signature['issuer']['O']) . "\n";
  $txt_content .= " CN: " . encde_text($e_signature['issuer']['CN']) . "\n";
  $txt_content .= " C: " . encde_text($e_signature['issuer']['C']) . "\n\n";
  
  return $txt_content;
}

/**
 * Vytvori obsah pdf souboru, ktery slouzi jako protokol o prijeti emailu
 *
 * @param array $email Polozky emailu
 * @param array $e_signature El. podpis
 * @param string $verify_output_msg Zprava o verifikaci certifikatu subjektu,
 *  ktery email elektronicky podepsal
 * @return string $txt_content Obsah pdf souboru
 */

function getProtocolAsPdf(array $email, array $e_signature, $verify_output_msg) {
  
  $time = date('j.n.Y g:i:s'); 
  $space = '    '; 
  
  $pdf = new PDF();
  $pdf->AddFont('arial', '', 'arial.php');
  $pdf->AddFont('arial', 'B', 'arialb.php');
  $pdf->AliasNbPages();
  $pdf->SetMargins(35, 0);
  $pdf->SetLineWidth(0.3);

  // uvodni stranka, tiskneme pouze tehdy, pokud se tiskne cela kniha;
  $pdf->AddPage();

  // header
  $pdf->SetFont('Arial','B',18);
  $pdf->SetTextColor(255);

  $pdf->SetXY(10, 10);
  $pdf->SetFillColor(125);
  $pdf->Cell(140, 20, $space . 'Protokol o přijetí e-mailu', 0, 0, L, 1);
  $pdf->SetFillColor(160);
  $pdf->Cell(40, 20, '', 0, 0, L, 1);
  $pdf->SetFillColor(215);
  $pdf->Cell(10, 20, '', 0, 0, L, 1);

  // email id
  $pdf->SetTextColor(0);

  $pdf->SetFont('Arial','B', 16);
  $email_id = $email['message_id'];
  $w = $pdf->GetStringWidth($email_id) + 6;

  $pdf->SetXY(-10, 39);
  $pdf->Cell(-$w, 9, $email_id, 0, 0, C, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(-10 - $w, 35);
  $pdf->Cell(40, 4, 'E-mail ID:', 0, 0, L); 


  // informace o emailu

  $top_email = 55;

  // ramecek
  $pdf->SetXY(10, $top_email);
  $pdf->Cell(190, 61, '', 1, 1, L); 
  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetFillColor(255);
  $pdf->SetXY(20, $top_email - 2);
  $pdf->Cell(35, 4, 'Informace o e-mailu', 0, 1, L, 1); 
  $pdf->SetFillColor(225);

  // data 
  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_email + 7);
  $pdf->Cell(40, 4, 'Odesílatel:', 0, 0, L); 
  $pdf->SetXY(15, $top_email + 16);
  $pdf->Cell(40, 4, 'Věc:', 0, 0, L); 
  $pdf->SetXY(15, $top_email + 25);
  $pdf->Cell(40, 4, 'Čas odeslání e-mailu:', 0, 0, L);
  $pdf->SetXY(15, $top_email + 34);
  $pdf->Cell(40, 4, 'Čas doručení e-mailu:', 0, 0, L);
  $pdf->SetXY(15, $top_email + 43);
  $pdf->Cell(40, 4, 'Čas ověření el. podpisu:', 0, 0, L);
  $pdf->SetXY(15, $top_email + 52);
  $pdf->Cell(40, 4, 'Čas přijetí e-mailu:', 0, 0, L);

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_email + 5);
  $pdf->MultiCell(130, 6, $email['name'], 0, 'L', 1);
  $pdf->SetXY(60, $top_email + 14);
  $pdf->MultiCell(130, 6, $email['vec'], 0, 'L', 1);
  $pdf->SetXY(60, $top_email + 23);
  $pdf->MultiCell(130, 6, $email['datum'], 0, 'L', 1);
  $pdf->SetXY(60, $top_email + 32);
  $pdf->MultiCell(130, 6, '?', 0, 'L', 1);
  $pdf->SetXY(60, $top_email + 41);
  $pdf->MultiCell(130, 6, $time, 0, 'L', 1);
  $pdf->SetXY(60, $top_email + 50);
  $pdf->MultiCell(130, 6, $time, 0, 'L', 1); 


  // informace o el. podpisu

  $top_signature = 123;

  // ramecek
  $pdf->SetXY(10, $top_signature);
  $pdf->Cell(190, 122, '', 1, 1, L); 
  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetFillColor(255);
  $pdf->SetXY(20, $top_signature - 2);
  $pdf->Cell(62, 4, 'Informace o elektronickém podpisu', 0, 1, L, 1); 
  $pdf->SetFillColor(225);

  // data 
  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 8);
  $pdf->Cell(40, 4, 'Předmět:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 6);
  $subject = '';
  $subject .= "C: " . encde_text($e_signature['subject']['C']) . "\n";
  $subject .= "CN: " . encde_text($e_signature['subject']['CN']) . "\n";
  $subject .= "O: " . encde_text($e_signature['subject']['O']) . "\n";
  $subject .= "L: " . encde_text($e_signature['subject']['L']) . "\n";
  $subject .= "ST: " . encde_text($e_signature['subject']['ST']) . "\n";
  $subject .= "Serial number: " . encde_text($e_signature['subject']['serialNumber']) . "\n";
  $pdf->MultiCell(130, 6, $subject, 0, L, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 47);
  $pdf->Cell(40, 4, 'Sériové číslo certifikátu:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 45);
  $pdf->MultiCell(130, 6, encde_text($e_signature['serialNumber']), 0, L, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 55);
  $pdf->Cell(40, 4, 'Verze certifikátu:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 54);
  $pdf->MultiCell(130, 6, encde_text($e_signature['version']), 0, L, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 65);
  $pdf->Cell(40, 4, 'Platnost certifikátu:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 63);
  $validity = '';
  $validity .= "od: " . date('j.n.Y g:i:s', $e_signature['validFrom_time_t']) . "\n";
  $validity .= "do: " . date('j.n.Y g:i:s', $e_signature['validTo_time_t']) . "\n";
  $pdf->MultiCell(130, 6, $validity, 0, L, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 80);
  $pdf->Cell(40, 4, 'Vydavatel certifikátu:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 78);
  $issuer = '';
  $issuer .= "OU: " . encde_text($e_signature['issuer']['OU']) . "\n";
  $issuer .= "O: " . encde_text($e_signature['issuer']['O']) . "\n";
  $issuer .= "CN: " . encde_text($e_signature['issuer']['CN']) . "\n";
  $issuer .= "C: " . encde_text($e_signature['issuer']['C']) . "\n";
  $pdf->MultiCell(130, 6, $issuer, 0, L, 1);

  $pdf->SetFont('Arial', '', 10);
  $pdf->SetXY(15, $top_signature + 107);
  $pdf->Cell(40, 4, 'Ověření certifikátu:', 0, 0, L); 

  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetXY(60, $top_signature + 105);
  $pdf->MultiCell(130, 6, $verify_output_msg, 0, L, 1);
  
  $pdf->AddPage();
  

  // informace o prilohach emailu

  $top_attachments = 15;

  // ramecek
  $pdf->SetXY(10, $top_attachments);
  $pdf->Cell(190, 39, '', 1, 1, L); 
  $pdf->SetFont('Arial', 'B', 10);
  $pdf->SetFillColor(255);
  $pdf->SetXY(20, $top_attachments - 2);
  $pdf->Cell(52, 4, 'Informace o přílohách e-mailu', 0, 1, L, 1); 
  $pdf->SetFillColor(225);

  // data 
  $pdf->SetFont('Arial', '', 10);
  $i = 0;
  $page_order = 1;
  $line_height = 6;
  $attachment_content = '';

  foreach ($email['soubor'] as $attachment) {

    if (!preg_match('/\.p7s$/', $attachment['FILE_NAME'])) {
      $i++;
      $page_order++;
      $size = strlen(base64_decode($attachment['FILE_DATA']));
  //    $attachment_content .= "Soubor č. $i: " . $attachment['FILE_NAME'] . " ($size Bytes)\n";
      $pdf->Text(15, $top_attachments - 3 + $line_height * $page_order ,
                  " Soubor č. $i: " . $attachment['FILE_NAME'] . " ($size Bytes)");
    }
  }

  //$pdf->SetXY(15, $top_attachments + 5);
  //$pdf->MultiCell(150, $line_height, $attachment_content, 0, L);

  // ramecek
  if ($pdf->PageNo > 1) {
    $pdf->SetXY(10, 15);
    $pdf->Cell(190, $page_order * $line_height + 2, '', 1, 1, L); 
    $pdf->SetFont('Arial', 'B', 10);
    $pdf->SetFillColor(255);
    $pdf->SetXY(20, $top_attachments - 2);
    $pdf->Cell(52, 4, 'Inforamce o přílohách e-mailu', 0, 1, L, 1); 
    $pdf->SetFillColor(225);
    $pdf->SetFont('Arial', '', 10);
  }
  
  return $pdf->Output('', S);
}

function encde_text($input_string) {
  return iconv('UTF-8', 'ISO-8859-2', $input_string);
}

function Footer() {
  //Position at 1.0 cm from bottom
  $this->SetY(-6);
  //Arial italic 8
  $this->SetFont('Arial','',6);
  //Page number
  $datum=Date("d.m.Y H:m");
  $this->Cell(0,3,'vytištěno v programu Evidence dokumentů, (c) T-MAPY spol. s r.o., www.tmapy.cz',0,0,'L');
  $this->Cell(0,3,'Stránka '.$this->PageNo().'/{nb}, tisk dne '.$datum,0,0,'R');
}
