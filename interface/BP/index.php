<?php
include_once('tmapy_config.inc');
require(FileUp2(".admin/config.inc"));
require(FileUp2(".admin/isds_.inc"));
require(FileUp2(".admin/upload_.inc"));

include_once('eed/.admin/fce.inc');

include('eed/server/sps_Response.inc');
//Message
require('eed/server/sps_Message.inc');

include_once(FileUp2('.admin/soap_funkce.inc'));
require(FileUp2(".admin/status.inc"));

class DR_server
{
    protected $class_name    = '';
    protected $authenticated = false;
    protected $ZdrojID;
    protected $CilID;

    public function __construct($class_name)
    {
        $this->class_name = $class_name;
        $this->db = new DB_POSTA;
    }

    public function Security( $header  ){
      $this->Username = trim($header->UsernameToken->Username);
      $this->Password = trim($header->UsernameToken->Password);

      $sql = "select * from posta_interface_bp_app where username='" . $this->Username . "' AND password='" . $this->Password . "'";
      $this->db->query($sql);
      if ($this->db->Num_Rows()>0) {
        $this->Authenticated = true; // This should be the result of an authenticating method
        $this->db->Next_Record();
        $this->App_ID = $this->db->Record['ID'];
        $this->CilID = $this->db->Record['ZDROJ_ID'];
        $this->ZdrojID = $this->db->Record['EXT_ZDROJ_ID'];
      }

    }

    protected function checkAuth()
    {
        if(!$this->authenticated)
            HTML_Output::error(403);

    }

    public function __call($method_name, $arguments)
    {
        if(!method_exists($this->class_name, $method_name))
           return new SoapFault("9999", 'Metoda ' . $method_name . ' neni dostupna');

        $this->checkAuth();

        return call_user_func_array(array($this->class_name, $method_name), $arguments);

    }

    public function WorkContext( $header  ){
    // pouze zamezeni chybam...
    }



    //jednotlive metody z WSDL

    //sync metody - nektere chybi

    //CiselnikZadost

    public function DavkaZadost($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      $Davka = (array) $params->Davka;
      include('eed/server/sps_DavkaZadost.inc');
      $res = DavkaZadost($this->App_ID, $Davka);

      return $res;
    }


    public function DavkySeznam($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      include('eed/server/sps_DavkySeznam.inc');
      $res = DavkySeznam($this->App_ID);

      return $res;
    }

    //DokumentPostoupeniZadost

    public function DokumentZalozeni($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      include('eed/server/sps_DokumentZalozeni.inc');
      $Autorizace = array_merge((array) $params->Autorizace, (array) $params->DoplnujiciData);
      $dokument = json_decode(json_encode($params->ProfilDokumentu), true);
      $res = DokumentZalozeniRequest($UdalostiPredchazejici, $dokument, $Autorizace);
      return $res;
    }

    //FunkcniMista

    public function ProfilDokumentuZadost($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      include('eed/server/sps_ProfilDokumentuZadost.inc');
      $IdDokument = (array) $params->IdDokument;
      $Autorizace = (array) $params->Autorizace;
      $dokument = json_decode(json_encode($params->IdDokument), true);

      $res = ProfilDokumentuZadostRequest($UdalostiPredchazejici, $dokument, $Autorizace);

      return $res;
    }

    //ProfilSpisuZadost

    public function SouborZadost($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      include('eed/server/sps_SouborZadost.inc');
      $Autorizace = (array) $params->Autorizace;
      $dokument = json_decode(json_encode($params->Soubor), true);
      $res = SouborZadostRequest($UdalostiPredchazejici, $dokument, $Autorizace);

      return $res;
    }

    public function Udalosti($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      $Udalosti = BPobjectToArray($params->Udalosti);
      include('eed/server/sps_Udalosti.inc');
      include('eed/server/sps_Asyn_func.inc');

      $res = UdalostiRequest($Udalosti);
      return $res;
    }

    //async udalosti

    public function ermsAsyn($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");
      if ($this->ZdrojID <> $params->Zdroj) return new SoapFault("9003", "Nenalezen odpovidajici Zdroj");
      if ($this->CilID <> $params->Cil) return new SoapFault("9004", "Nenalezen odpovidajici Cil");

      $Udalosti = BPobjectToArray($params->Udalosti);
      include('eed/server/sps_ErmsAsyn.inc');
      $res = BPermsAsyn($Udalosti, $this->Poradi, $this->App_ID);
      return $res;
    }

    public function WsTest($params) {
      if (!$this->App_ID) return new SoapFault("9001", "neni identifikovana aplikace");

      $Udalosti = $params->WsTestId;
      $Autorizace = (array) $params->Autorizace;
      include('eed/server/sps_wstest.inc');
      $res = WsTestRequest($Udalosti, $Autorizace);
      return $res;
    }

    //


}

class DebugSoapServer extends SoapServer
{
/*
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
*/
}

$Service = new DR_server('WebService');

$url = 'http://' . $_SERVER['HTTP_HOST']. '/ost/posta/interface/BP/ws.php';
$Server = new DebugSoapServer($url);

$Server->setObject($Service);

$Server->handle();
