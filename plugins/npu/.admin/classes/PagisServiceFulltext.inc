<?php
require_once($GLOBALS["TMAPY_LIB"]."/lib/nusoap/lib/nusoap.php");
require_once(FileUp2('plugins/npu/.config/config_pam_katalog.inc'));
require_once(FileUp2('plugins/npu/.admin/classes/PKident.inc'));

class PagisServiceFulltext {
  var $client;
  var $config;
  var $charset = 'UTF-8';
  var $namespaces = array(
    'ful' => 'http://iispp.npu.cz/FulltextSearch',
    'ser' => 'http://iispp.npu.cz/ServiceAuth',
  );
  var $debug = false;

  function PagisServiceFulltext() {
    $this->config = $GLOBALS['CONFIG_NPU']['PK_SERVICE'];
  }

  function connect() {
    $this->client = new TW_SoapClient($this->config['url']);
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

  function fulltext($vyraz, $login) {

    if (!$login) return array(false, 'Není uzivatel');
    if (!$vyraz) return array(false, 'Není vyraz');
    if (!$this->client) {
      $res = $this->connect();
 //     if ($res !== true) return array(false, $res);
    }
    $params = array(
      'uid' => $login, //login zpracovatele
      'dotaz' => $vyraz,
      'maxVysledku' => 100,
      'jazyk' => 'cs'
    );
    $result = $this->client->call('ful:fulltextSearchRequest', $params, false, false, false, null, 'rpc', 'literal');
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
    if ($result['id']) {
      $temp = $result;
      $result = array();
      $result[] = $temp;
    }
    if (is_array($result)) {
      $res = array();
      while (list($key, $val) = each($result)) {
        while (list($key2,$val2) = each($val['metadata'])) {
          if ($val2['nazev'] == 'typOchrany') $val['ochrana'] = $val2['hodnota'];
          if ($val2['nazev'] == 'typEntity') $val['typ'] = $val2['codebookValue'];
          if ($val2['nazev'] == 'rejstrikoveCislo') $val['rejstrikoveCislo'] = $val2['hodnota'];
          if ($val2['nazev'] == 'lokalita') $val['lokalita'] = $val2['hodnota'];
          if ($val2['nazev'] == 'katastr') $val['katastr'] = $val2['hodnota'];
          if ($val2['nazev'] == 'adresa') $val['adresa'] = $val2['hodnota'];
          if ($val2['nazev'] == 'kategoriePrvku') $val['kategoriePrvku'] = $val2['hodnota'];
//          if ($val2['nazev'] == 'thumbnailUrl' && $val2['typ'] == 'imageurl') $val['nahled'] = $val2['hodnota'];
          if ($val2['nazev'] == 'previewUrl' && $val2['typ'] == 'imageurl') $val['nahled'] = $val2['hodnota'];

        }
        $res[] = new PKIdent($val);
      }
      return $res;
    }
    return false; // nenalezeno;
  }
}
