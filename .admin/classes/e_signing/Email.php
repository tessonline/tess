<?php

include_once('ISignedDocument.php');
include_once('Utils.php');

/**
 * Description of Email
 * @author mier
 */
class Email implements ISignedDocument {
  
  private $id;
  private $messageId;
  private $from;
  private $name;
  private $subject;
  private $date;
  private $attachments;
  private $text;
  private $size;
  
  private $signature;
  
  /**
   * Konstruktor
   * @param array $emailArray Pole s informacemi o emailu
   * @param Signature $signature El. podpis emailu
   */
  public function __construct($emailArray, Signature $signature) {
    
    $this->id           = $emailArray['id'];
    $this->messageId    = $emailArray['message_id'];
    $this->from         = $emailArray['from'];
    $this->name         = $emailArray['name'];
    $this->subject      = $emailArray['vec'];
    $this->date         = $emailArray['datum'];
    $this->attachments  = $emailArray['soubor'];
    $this->text         = $emailArray['vlastni_text'];
    $this->size         = $emailArray['size'];
    
    $this->signature    = $signature;
  }
  
  /**
   * Viz interface ISignedDocument
   */
  public function verify() {
    
    return $this->signature->isValid();
  }
  
  /**
   * Viz interface ISignedDocument
   */
  public function createProtocolContent($protocolType) {
    
    $protocolType = strtoupper($protocolType);    
    $data = $this->prepareProtocolData();
    
    switch ($protocolType) {
      case 'PDF':
        return $this->createPdfProtocol($data);
      default:
        return '';
    }    
  }
  
  /**
   * Funkce pripravi pole, ktere obsahuje data potrebna pro vytvoreni protokolu.
   * @return array Data o e-mailu.
   */
  private function prepareProtocolData() {
    
    $data = array();
    $time = date('j.n.Y H:i:s');
    $certificate = $this->signature->certificate;
    
    $data['styles'] = FileUp2('.admin/classes/e_signing/templates/styles.css');
    
    $data['title'] = 'Protokol o přijetí e-mailu';
    
    $data['id']['label'] = strtoupper('E-mail ID');
    $data['id']['value'] = htmlentities($this->messageId);
    
    
   
    $data['blocks'][0]['label'] = strtoupper('Informace o e-mailu');
    
    $data['blocks'][0]['items'][0]['label'] = 'Odesílatel';
    $data['blocks'][0]['items'][0]['value'] = $this->name;
    
    $data['blocks'][0]['items'][1]['label'] = 'Věc';
    $data['blocks'][0]['items'][1]['value'] = $this->subject;
    
    $data['blocks'][0]['items'][2]['label'] = 'Čas odeslání';
    $data['blocks'][0]['items'][2]['value'] = $this->date;
    
//    $data['blocks'][0]['items'][3]['label'] = 'Čas doručení';
//    $data['blocks'][0]['items'][3]['value'] = '?';
    
    $data['blocks'][0]['items'][4]['label'] = 'Čas ověření';
    $data['blocks'][0]['items'][4]['value'] = $time;
    
    $data['blocks'][0]['items'][5]['label'] = 'Čas přijetí';
    $data['blocks'][0]['items'][5]['value'] = $time;
    
    
   
    $data['blocks'][1]['label'] = strtoupper('Informace o elektronickém podpisu');
    
    $data['blocks'][1]['items'][0]['label'] = 'Předmět';
    $subject  = 'C: '             . $certificate->subject['C']            . '<br>';
    $subject .= 'CN: '            . $certificate->subject['CN']           . '<br>';
    $subject .= 'O: '             . $certificate->subject['O']            . '<br>';
    $subject .= 'L: '             . $certificate->subject['L']            . '<br>';
    $subject .= 'ST: '            . $certificate->subject['ST']           . '<br>';
    $subject .= 'Serial number: ' . $certificate->subject['serialNumber'];
    $data['blocks'][1]['items'][0]['value'] = $subject;
    
    $data['blocks'][1]['items'][1]['label'] = 'Sériové číslo certifikátu';
    $data['blocks'][1]['items'][1]['value'] = $certificate->serialNumber; 
    
    $data['blocks'][1]['items'][2]['label'] = 'Verze certifikátu';
    $data['blocks'][1]['items'][2]['value'] = $certificate->version;  
    
    $data['blocks'][1]['items'][3]['label'] = 'Platnost certifikátu';
    $validity  = 'od: ' . date('j.n.Y g:i:s', $certificate->validFrom)  . '<br>';
    $validity .= 'do: ' . date('j.n.Y g:i:s', $certificate->validTo);
    $data['blocks'][1]['items'][3]['value'] = $validity;
    
    $data['blocks'][1]['items'][4]['label'] = 'Vydavatel certifikátu';
    $issuer  = 'OU: ' . $certificate->issuer['OU']  . '<br>';
    $issuer .= 'O: '  . $certificate->issuer['O']   . '<br>';
    $issuer .= 'CN: ' . $certificate->issuer['CN']  . '<br>';
    $issuer .= 'C: '  . $certificate->issuer['C'];
    $data['blocks'][1]['items'][4]['value'] = $issuer;
    
    $data['blocks'][1]['items'][5]['label'] = 'Ověření el. podpisu';    
    if ($this->signature->isValid()) {
      $verifyMessage = 'Elektronický podpis je platný.';
    }
    else {
      $verifyMessage = 'ELEKTRONICKÝ PODPIS NENÍ PLATNÝ NEBO SE HO NEPODAŘILO OVĚŘIT.';
    }
    $data['blocks'][1]['items'][5]['value'] = $verifyMessage;
    
    $i = 0;
    $data['attachments']['label'] = strtoupper('Informace o přílohách e-mailu');

    if (count($this->attachments)>0) {
      foreach ($this->attachments as $attachment) {

        if (!preg_match('/\.p7s$/', $attachment['FILE_NAME'])) {
          $i++;
          $size = strlen(base64_decode($attachment['FILE_DATA']));
          $data['attachments']['items'][] = ' Soubor č. ' . $i . ': ' . $attachment['FILE_NAME'] . ' (' . $size . ' Bytes)';
        }
      }
    }
    else {
      $data['attachments']['items'][] = 'přílohy neuvedeny.';
    }

    return $data;
  }  
  
  /**
   * Funkce vygeneruje obsah PDF protokolu na zaklade predpripravenych dat
   * @param array $data Pole hodnot pro naplneni HTML sablony templates/pdfProtocol.inc
   * @return string PDF content 
   */
  private function createPdfProtocol($data) {
    
    ob_start();
    include('templates/pdfProtocol.inc');
    $html = iconv('ISO_8859-2', 'UTF-8', ob_get_clean());
    
    require_once(FileUp2('lib/tcpdf/tcpdf.php'));

    $pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);

    $pdf->SetCreator('ePodatelna');
    $pdf->SetAuthor('T-WIST EED');
    $pdf->SetTitle('Protokol el. podpisu');
    $pdf->SetSubject('el.podpis');
    $pdf->SetKeywords('el.podpis');

    // remove default header/footer
    $pdf->setPrintHeader(false);
    $pdf->setPrintFooter(false);

    // set default header data
    //$pdf->SetHeaderData(PDF_HEADER_LOGO, PDF_HEADER_LOGO_WIDTH, PDF_HEADER_TITLE, PDF_HEADER_STRING);

    // set header and footer fonts
    //$pdf->setHeaderFont(Array(PDF_FONT_NAME_MAIN, '', PDF_FONT_SIZE_MAIN));
    //$pdf->setFooterFont(Array(PDF_FONT_NAME_DATA, '', PDF_FONT_SIZE_DATA));

    // set default monospaced font
    $pdf->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);

    //set margins
    $pdf->SetMargins(PDF_MARGIN_LEFT, 10, PDF_MARGIN_RIGHT);
    //$pdf->SetHeaderMargin(PDF_MARGIN_HEADER);
    //$pdf->SetFooterMargin(PDF_MARGIN_FOOTER);

    //set auto page breaks
    $pdf->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

    //set image scale factor
    $pdf->setImageScale(PDF_IMAGE_SCALE_RATIO);

    //set some language-dependent strings
    $pdf->setLanguageArray($l);
    
    $pdf->SetFont('freesans', '', 12);
    $pdf->setFontSubsetting(TRUE);

    $pdf->AddPage();

    $tagvs = array(
      'p' => array(
        0 => array('h' => 0, 'n' => 0),
        1 => array('h' => 2, 'n' => 1)
      ), 
      'div' => array(
        0 => array('h' => 0, 'n' => 0),
        1 => array('h' => 0, 'n' => 0)
      ), 
    );

    $pdf->setHtmlVSpace($tagvs);
    $pdf->SetCellPadding(1.5);
    $pdf->writeHTML($html, true, false, true, false, '');
    $pdf->lastPage();
    
    return $pdf->Output('', 'S');
  }
}

?>
