<?php
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php");
require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));

class PagisServiceStavInfo {
  var $client;
  var $config;
  var $charset = 'UTF-8';
  var $namespaces = array(
    'pkp' => 'http://iispp.npu.cz/PkPravniStav',
    'ser' => 'http://iispp.npu.cz/ServiceAuth',
  );
  var $debug = false;

  function PagisServiceStavInfo() {
    $this->config = $GLOBALS['CONFIG_NPU']['PK_SERVICE'];
  }

  function connect() {
    $this->client = new TW_SoapClient($this->config['url_StavInfo']);
    $this->client->timeout = 10;
    $this->client->response_timeout = 10;
    foreach ($this->namespaces as $alias => $url) {
      $this->client->namespaces[$alias] = $url;
    }
    $auth = '<ser:AuthToken>'
          . '<ser:username>' . $this->config['login'] . '</ser:username>'
          . '<ser:password>' . $this->config['passwd'] . '</ser:password>'
          . '</ser:AuthToken>';
    $this->client->setHeaders($auth);
    $this->client->soap_defencoding = $this->charset;
    if ($this->charset == 'UTF-8') $this->client->decodeUTF8(false);
    $err = $this->client->getError();
    if ($err) return $err;
    return true;
  }

  function getInfo($id, $login) {
    if (!$id) return array(false, 'Není id');
    if (!$login) return array(false, 'Není login');
    if (!$this->client) {
      $res = $this->connect();
 //     if ($res !== true) return array(false, $res);
    }
    $params = array(
      'uid' => $login, //login zpracovatele
      'prStavId' => $id
    );
    $result = $this->client->call('pkp:getDetailRequest', $params, false, false, false, null, 'rpc', 'literal');
    if ($this->debug) {
      print '<pre>';
      print '<h2>request:</h2>';
      print $this->client->request;
      print '<h2>response:</h2>';
      print $this->client->response;
      print '<h2>debug:</h2>';
      print $this->client->debug_str;
      print '</pre>';
    }
    $err = $this->client->getError();
    if ($err) return false;

    $arr = array(
      'id' => $ret['prvekId'],
      'jmeno' => $result['nazev'],
      'popis' => $result['anotace'],
      'url' => $result['urlInt'],
      'ochrana' => $result['typOchranyNazev'],
      'lokalita' => $result['prvek']['piPrvku']['lokalita'],
      'rejstrikoveCislo' => $result['rejstrikoveCisloUSKP'],
      'typ' => 8,
    );
    while (list($key2,$val2) = each($result['metadata'])) {
      if ($val2['nazev'] == 'katastr') $arr['katastr'] = $val2['hodnota'];
      if ($val2['nazev'] == 'adresa') $arr['adresa'] = $val2['hodnota'];
    }
    return $arr; // nenalezeno;
  }
}
