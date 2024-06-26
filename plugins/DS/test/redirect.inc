<?php
function curl_redir_exec($ch,$cookie=array())
{
  static $curl_loops = 0;
  static $curl_max_loops = 20;
  if ($curl_loops++ >= $curl_max_loops)
  {
      $curl_loops = 0;
      return FALSE;
  }
  curl_setopt($ch, CURLOPT_HEADER, true);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  $data = curl_exec($ch);
  list($header, $data) = explode("\n\n", $data, 2);
  $http_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
//         echo "Nalezeno>".$http_code;
  if ($http_code == 301 || $http_code == 302)
  {
      $matches = array();
      preg_match('/Location:(.*?)\n/', $header, $matches);
      $url = @parse_url(trim(array_pop($matches)));
      if (!$url)
      {
          //couldn't process the url to redirect to
          $curl_loops = 0;
          return $data;
      }
      $last_url = parse_url(curl_getinfo($ch, CURLINFO_EFFECTIVE_URL));
      if (!$url['scheme'])
          $url['scheme'] = $last_url['scheme'];
      if (!$url['host'])
          $url['host'] = $last_url['host'];
      if (!$url['path'])
          $url['path'] = $last_url['path'];
      $new_url = $url['scheme'] . '://' . $url['host'] . $url['path'] . ($url['query']?'?'.$url['query']:'');
      curl_setopt($ch, CURLOPT_URL, $new_url);
      if (!strpos($cookie[0],"PCZ"))
      {
        $x=strpos($header,"IPCZ",strpos($header,"Cookie:"));
        $y=strpos($header,"\n",$x);		
        $cookie=split("=",substr($header,$x,$y-$x-1));
//               echo "<br/>Nastavime susu na";
//               print_r($cookie);
      }
//             echo "<br/>";
//             echo('Redirecting to'.$new_url."<br/>");Flush();
      return curl_redir_exec($ch,$cookie);
  } else {
      $curl_loops=0;
      return $cookie;
  }
}
