<?php
include_once('tmapy_config.inc');
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/isds_.inc"));

include_once(FileUp2('interface/.admin/soap_funkce.inc'));
require(FileUp2(".admin/classes/unispis/dokument/dokument.inc"));

class DR_server
{
    protected $class_name    = '';
    protected $authenticated = false;

    public function __construct($class_name)
    {
        $this->class_name = $class_name;
        $this->db = new DB_POSTA;
    }

    public function Security( $header  ){
      $this->Username = trim($header->UsernameToken->Username);
      $this->Password = trim($header->UsernameToken->Password);

      $sql = "select * from posta_plugins_dr_app where server_username='" . $this->Username . "' AND server_passwd='" . $this->Password . "'";
      $this->db->query($sql);
      if ($this->db->Num_Rows()>0) {
        $this->Authenticated = true; // This should be the result of an authenticating method
        $this->db->Next_Record();
        $this->App_ID = $this->db->Record['ID'];
      }

    }

    public function WorkContext( $header  ){
    }

    public function __call($method_name, $arguments)
    {
         if(!method_exists($this->class_name, $method_name))
             throw new Exception('method ' . $method_name . ' not found');

        $this->checkAuth();

        return call_user_func_array(array($this->class_name, $method_name), $arguments);

    }


    public function FindDataBox($params) {

      if (!$this->App_ID) return new SoapFault("1000", "neni identifikovana aplikace");
      $schranka = new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);

      $find = $params->dbOwnerInfo;
      $dbResults = array();
      $dbResults = $schranka->FindDataBox($find);

      $dbStatus = array(
        'dbStatusCode' => $schranka->StatusCode,
        'dbStatusMessage' => $schranka->StatusMessage,
        'dbStatusRefNumber' => NULL
      );

      $result = array(
        'dbResults' => $dbResults,
        'dbStatus' => $dbStatus
      );

      return ($result);
    }


    public function vlozDokument($params) {
      return new SoapFault("1001", "metoda neni povolena");
    }

    public function vlozAOdesliDokument($params) {
       include_once(FileUp2('DS/.admin/funkce.inc'));
       if (!$this->App_ID) return new SoapFault("1000", "neni identifikovana aplikace");

       $schranka = new ISDSbox($GLOBALS[CONFIG_POSTA][DS][ds_user],$GLOBALS[CONFIG_POSTA][DS][ds_passwd],$certifikat);
       $doc = new dokument();

       $doc->setFromObject($params);
       if (!$doc->Dalsi_id_agenda) $doc->Dalsi_id_agenda = uniqid();
       $doc->Dalsi_id_agenda = 'DR-' . $this->App_ID.'-' . $doc->Dalsi_id_agenda;
       $doc->InsertAdresaFromDS();
       $doc->SaveAsOdchozi();
       $zpravaDS = GetPoleProDS($doc->id);
       $DS_id = $schranka->CreateMessage($zpravaDS);
       $sql = 'select * from posta_plugins_dr_app where id='.$this->App_ID;
       $this->db->query($sql);
       $this->db->Next_Record();
       $so = $this->db->Record['SUPERODBOR'] ? $this->db->Record['SUPERODBOR'] : 0;
       if ($schranka->StatusCode<>'0000')   {
         $sql="update posta set vlastnich_rukou=9,superodbor=$so,poznamka='ISDS chyba:".$schranka->StatusMessage."' where id=".$doc->id;
         $this->db->query($sql);
         $id = array('Identifikator'=>array('ZdrojID' =>'ISDS', 'HodnotaID' => 0));
        //$id = array('Identifikator'=>array(0 => array('ZdrojID' =>'DR', 'HodnotaID' => $doc->id),1 => array('ZdrojID' =>'ISDS', 'HodnotaID' => 0), ));
//        $id = array('Identifikator'=>array(array('ZdrojID' =>'DR', 'HodnotaID' => $doc->id), array('ZdrojID' =>'ISDS', 'HodnotaID' => 0)));

         $result = array(
           'Identifikatory' => $id,
           'StatusCode' => $schranka->StatusCode,
           'StatusMessage' => $schranka->StatusMessage
         );

         return $result;
       }
       else  {
         $sql="insert into posta_DS (posta_id,DS_id,odeslana_posta,datum_odeslani,last_date,last_time,last_user_id) VALUES
         ($doc->id,$DS_id,'t','".Date('d.m.Y H:i:s')."','".Date('Y-m-d')."','".Date('H:i:s')."',0)";
         $this->db->query($sql);
         $sql="update posta set vlastnich_rukou=9,superodbor=$so,datum_vypraveni='".Date('Y-m-d H:i:s')."',poznamka='ISDS:Odeslano' where id=".$doc->id;
         $this->db->query($sql);
         NastavStatus($doc->id);

         $text = 'dokument (<b>'.$doc->id.'</b>) byl vypraven Datovou schránkou. ID datové zprávy je ' . $DS_id;
         EedTransakce::ZapisLog($doc->id, $text, 'DOC');
      }


      $id = array('Identifikator'=>array('ZdrojID' =>'ISDS', 'HodnotaID' => $DS_id));
      //$id = array('Identifikator'=>array(0 => array('ZdrojID' =>'DR', 'HodnotaID' => $doc->id),1 => array('ZdrojID' =>'ISDS', 'HodnotaID' => $DS_id), ));

      $result = array(
        'Identifikatory' => $id,
        'StatusCode' => $schranka->StatusCode,
        'StatusMessage' => $schranka->StatusMessage
      );

     return $result;
//      return ($result);
    }


    protected function checkAuth()
    {
        if(!$this->authenticated)
            HTML_Output::error(403);

    }

}

class DebugSoapServer extends SoapServer
{
    public function handle($request = null)
    {
        // check input param
        if ($request === null) {
            $request = file_get_contents('php://input');
        }
        // store the request string
        $requestSignature = md5($request);
        file_put_contents('/tmp/soap_' . $requestSignature . '_request', $request);
        // start output buffering
        ob_start();
        // finaly call SoapServer::handle() - store result
        $result = parent::handle($request);

        // store the response string
        file_put_contents('/tmp/soap_' . $requestSignature . '_response', ob_get_contents());
        // flush buffer
        ob_flush();
        // return stored soap-call result
        return $result;
    }
}

$Service = new DR_server('WebService');

$url = 'http://' . $_SERVER['HTTP_HOST']. '/ost/posta/plugins/DR/server/ws.php';
$Server = new DebugSoapServer($url);

$Server->setObject($Service);

$Server->handle();
