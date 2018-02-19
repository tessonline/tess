<?php

include_once('ISignedDocument.php');
include_once('Utils.php');
include_once('PDFSignature.php');

/**
 * Description of DatovaZprava *
 * @author mier
 */
class DatovaZprava implements ISignedDocument {
  
  /** @var ISDSbox Rozhrani pro komunikaci s datovou schrankou */
  private $datovaSchranka;
  
  /** @var ID datové zprávy, řetězec délky max. 20, unikátní pro celé ISDS v čase i prostoru */
  private $id;
  
  /** @var ID datové schránky odesílatele */
  private $idSender;
  
  /** @var Jmeno nebo nazev odesilatel */
  private $sender;
  
  /** @var Slozena adresa odesilatele */
  private $senderAddress;
  
  /** @var Jmeno nebo nazev prijemce */
  private $recipient;
  
  /** @var Slozena adresa prijemce */
  private $recipientAddress;
  
  /** @var Datum a cas dodani */
  private $deliveryTime;
  
  /** @var Datum a cas doruceni */
  private $acceptanceTime;
  
  /** @var Popis datove zpravy */
  private $annotation;
  
  /** @var Prilohy */
  private $files;
  
  /** @var Elektronikcy podpis datove zpravy */
  private $signature;
  
  /**
   * Konstruktor
   * @param array $datovaZpravaArray Pole s hodnotami datove zpravy
   * @param Signature $signature Elektronicky podpis datove zpravy
   * @param ISDSbox $datovaSchranka Rozhrani pro komunikaci s datovou schrankou
   */
  public function __construct($datovaZpravaArray, Signature $signature, $datovaSchranka) {
    
    $this->datovaSchranka   = $datovaSchranka;


    $this->id          = $datovaZpravaArray['dmDm']['dmID'];
    $this->idSender         = $datovaZpravaArray['dmDm']['dbIDSender'];
    $this->sender           = $datovaZpravaArray['dmDm']['dmSender'];
    $this->senderAddress    = $datovaZpravaArray['dmDm']['dmSenderAddress'];
    $this->recipient        = $datovaZpravaArray['dmDm']['dmRecipient'];
    $this->recipientAddress = $datovaZpravaArray['dmDm']['dmRecipientAddress'];
    $this->deliveryTime     = $datovaZpravaArray['dmDeliveryTime'];
    $this->acceptanceTime   = $datovaZpravaArray['dmAcceptanceTime'];
    $this->annotation       = $datovaZpravaArray['dmDm']['dmAnnotation'];

    if (is_array($datovaZpravaArray['dmDm']['dmFiles'])) {
      foreach($datovaZpravaArray['dmDm']['dmFiles'] as $key => $val) {

       if ($val[0]) {
         foreach($val as $key1 => $val1) {
            $this->files[$key][$key1] =$val1;
            $this->files[$key][$key1][!dmFileDescr] = @$va1[!dmFileDescr];
         }
       }
        else {
          $this->files[dmFile][0] =$val;
          $this->files[dmFile][0][!dmFileDescr] = @$val[!dmFileDescr];
        }
      }
    }
    $this->signature        = $signature;
  }

  /**
   * Viz interface ISignedDocument
   */
  public function verify() {

    return $this->datovaSchranka->AuthenticateMessage($this->signature->content) === 'true';
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
   * Funkce pripravi pole, ktere obsahuje data potrebna pro vytvoreni protokolu
   * @return array Data o datove zprave
   */
  private function prepareProtocolData() {
    
    $data = array();
    $certificate = $this->signature->certificate;
    
    $data['styles'] = FileUp2('.admin/classes/e_signing/templates/styles.css');
    
    $data['title'] = '&nbsp;<br/>Protokol o přijetí datové zprávy<br/>';
    
    $data['id']['label'] = strtoupper('ID DZ');
    $data['id']['value'] = htmlentities($this->id);
    
    
   
    $data['blocks'][0]['label'] = ('Informace o datové zprávě');
    
    $data['blocks'][0]['items'][0]['label'] = 'Věc';
    $data['blocks'][0]['items'][0]['value'] = $this->annotation;
    
    $data['blocks'][0]['items'][0]['label'] = 'Odesílatel';
    $data['blocks'][0]['items'][0]['value'] = $this->sender;
    
    $data['blocks'][0]['items'][1]['label'] = 'Adresa odesílatele';
    $data['blocks'][0]['items'][1]['value'] = $this->senderAddress;
    
    $data['blocks'][0]['items'][2]['label'] = 'Příjemce';
    $data['blocks'][0]['items'][2]['value'] = $this->recipient;
    
    $data['blocks'][0]['items'][3]['label'] = 'Adresa příjemce';
    $data['blocks'][0]['items'][3]['value'] = $this->recipientAddress;
    
    $data['blocks'][0]['items'][4]['label'] = 'Čas dodání';
    $data['blocks'][0]['items'][4]['value'] = $this->deliveryTime;
    
    $data['blocks'][0]['items'][5]['label'] = 'Čas doručení';
    $data['blocks'][0]['items'][5]['value'] = $this->acceptanceTime;
    
    
   
    $data['blocks'][1]['label'] = ('Informace o elektronickém podpisu DZ');
    
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
    
    $data['blocks'][1]['items'][5]['label'] = 'Ověření e. podpisu';    
    if ($this->verify()) {
      $verifyMessage = 'Elektronický podpis je platný.';
    }
    else {
      $verifyMessage = 'Elektronický podpis není platný nebo se ho nepodařilo ověřit.';
    }
    $data['blocks'][1]['items'][5]['value'] = $verifyMessage;
    
    
   
    $data['attachments']['label'] = ('Informace o souborech datové zprávy');    

    $i = 0;
    foreach ($this->files['dmFile'] as $file) {
      
      $i++;
      $size = strlen(base64_decode($file['dmEncodedContent']));
      $data['attachments']['items'][$i]['title'] = ' Soubor č. ' . $i . ': ' . $file['!dmFileDescr'] . ' (' . $size . ' Bytes)';
      
      // informace o podpisu pdf priloh
       if (pathinfo($file['!dmFileDescr'], PATHINFO_EXTENSION)=='pdf'){

         $TMP_DIR = $_SERVER['DOCUMENT_ROOT']."data/";
         $r = new PDFSignature($TMP_DIR);

         try {
            $verifyMessage = 'Elektronický podpis není platný nebo se ho nepodařilo ověřit.';
            $cert = $r->verifyString(base64_decode($file['dmEncodedContent']));
            //var_dump($cert);
            if ($cert["result"]) {   
              $data['attachments']['items'][$i][0]['label'] = '  Předmět';
              $subject  = 'C: '             . $cert['subject']['c']            . '<br>';
              $subject .= 'CN: '            . $cert['subject']['cn']           . '<br>';
              $subject .= 'O: '             . $cert['subject']['o']            . '<br>';
              $subject .= 'L: '             . $cert['subject']['l']            . '<br>';
              $subject .= 'ST: '            . $cert['subject']['st']           . '<br>';
              $subject .= 'Serial number: ' . $cert['subject']['serial']       . '<br>';
              $data['attachments']['items'][$i][0]['value'] = $subject;
              
              $data['attachments']['items'][$i][1]['label'] = '  Sériové číslo certifikátu';
              $data['attachments']['items'][$i][1]['value'] = $cert['serial'];
              
              $data['attachments']['items'][$i][2]['label'] = '  Verze certifikátu';
              $data['attachments']['items'][$i][2]['value'] = $cert['version'];
              
              $data['attachments']['items'][$i][3]['label'] = '  Platnost certifikátu';
              $validity  = 'od: ' . $cert['valid_from']  . '<br>';
              $validity .= 'do: ' . $cert['valid_to'];
              $data['attachments']['items'][$i][3]['value'] = $validity;
              
              $data['attachments']['items'][$i][4]['label'] = '  Vydavatel certifikátu';
              $issuer  = 'OU: ' . $cert['issuer']['ou']  . '<br>';
              $issuer .= 'O: '  . $cert['issuer']['o']   . '<br>';
              $issuer .= 'CN: ' . $cert['issuer']['cn']  . '<br>';
              $issuer .= 'C: '  . $cert['issuer']['c'];
              $data['attachments']['items'][$i][4]['value'] = $issuer;
              
              $verifyMessage = 'Elektronický podpis je platný.';          
            }      
         } catch (Exception $e) { 
           //var_dump($e);
         }
         $data['attachments']['items'][$i][5]['label'] = '  Ověření e. podpisu';
         $data['attachments']['items'][$i][5]['value'] = $verifyMessage. '<br>';
       } 
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
    $html = iconv('UTF-8', 'UTF-8', ob_get_clean());
    
//    require_once(FileUp2('lib/tcpdf/config/lang/ces.php'));
    require_once(FileUp2('lib/tcpdf/tcpdf.php'));

    $pdf = new TCPDF(PDF_PAGE_ORIENTATION, PDF_UNIT, PDF_PAGE_FORMAT, true, 'UTF-8', false);

    $pdf->SetCreator('');
    $pdf->SetAuthor('');
    $pdf->SetTitle('');
    $pdf->SetSubject('');
    $pdf->SetKeywords('');

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
