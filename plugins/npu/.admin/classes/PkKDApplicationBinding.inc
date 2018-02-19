<?php
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php");
require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));

class PkKDApplicationBinding {
  var $client;
  var $config;
  var $charset = 'UTF-8';
  var $namespaces = array(
    'pkp' => 'http://iispp.npu.cz/PkKDApplicationBinding',
    'ser' => 'http://iispp.npu.cz/ServiceAuth',
  );
  var $debug = false;

  function PkKDApplicationBinding() {
    $this->config = $GLOBALS['CONFIG_NPU']['PK_SERVICE'];
  }

  function connect() {
    $this->client = new TW_SoapClient($this->config['url_KDBind']);
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

  function createBind($spisid, $pk_id, $login) {
    if (!$spisid) return false;
//    if (!$pk_id) return false;
    if (!$login) return false;
    if (!$this->client) {
      $res = $this->connect();
 //     if ($res !== true) return array(false, $res);
    }
    $params = array(
      'uid' => $login, //login zpracovatele
      'appId' => $GLOBALS['CONFIG_NPU']['APP_ID'],
      'appRecordId' => $spisid,
      'pkRecordId' => $pk_id,
    );

    $result = $this->client->call('pkp:createBindingRequest', $params, false, false, false, null, 'rpc', 'literal');
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
    if ($result['idKD']) return $result['idKD'];
    $err = $this->client->getError();
    if ($err) return false;
  }


  function deleteBind($spisid, $pk_id, $login) {
    if (!$spisid) return false;
    if (!$pk_id) return false;
    if (!$login) return false;
    if (!$this->client) {
      $res = $this->connect();
 //     if ($res !== true) return array(false, $res);
    }
    $params = array(
      'uid' => $login, //login zpracovatele
      'appId' => $GLOBALS['CONFIG_NPU']['APP_ID'],
      'appRecordId' => $spisid,
      'pkRecordId' => $pk_id,
    );

    $result = $this->client->call('pkp:deleteBindingRequest', $params, false, false, false, null, 'rpc', 'literal');
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
    if ($result['result'] == 'true') return true;

    $err = $this->client->getError();
    if ($err) return false;
  }
}
