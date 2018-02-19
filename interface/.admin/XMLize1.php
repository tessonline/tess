<?php
function GetChildren($vals, &$i) {
   $children = array(); // Contains node data
   if (isset($vals[$i]['value'])){
      $children['VALUE'] = $vals[$i]['value'];
   }

   while (++$i < count($vals)){
      switch ($vals[$i]['type']){

      case 'cdata':
         if (isset($children['VALUE'])){
            $children['VALUE'] .= $vals[$i]['value'];
         } else {
            $children['VALUE'] = $vals[$i]['value'];
         }
      break;

      case 'complete':
         if (isset($vals[$i]['attributes'])) {
            $children[$vals[$i]['tag']][]['ATTRIBUTES'] = $vals[$i]['attributes'];
            $index = count($children[$vals[$i]['tag']])-1;

            if (isset($vals[$i]['value'])){
               $children[$vals[$i]['tag']][$index]['VALUE'] = $vals[$i]['value'];
            } else {
               $children[$vals[$i]['tag']][$index]['VALUE'] = '';
            }
         } else {
            if (isset($vals[$i]['value'])){
               $children[$vals[$i]['tag']][]['VALUE'] = $vals[$i]['value'];
            } else {
               $children[$vals[$i]['tag']][]['VALUE'] = '';
            }
         }
      break;

      case 'open':
         if (isset($vals[$i]['attributes'])) {
            $children[$vals[$i]['tag']][]['ATTRIBUTES'] = $vals[$i]['attributes'];
            $index = count($children[$vals[$i]['tag']])-1;
            $children[$vals[$i]['tag']][$index] = array_merge($children[$vals[$i]['tag']][$index],GetChildren($vals, $i));
         } else {
            $children[$vals[$i]['tag']][] = GetChildren($vals, $i);
         }
      break;

      case 'close':
         return $children;
   }
}
}

function xmlize($xmlloc,$convert=true){
   if (file_exists($xmlloc)){
      $data = implode('', file($xmlloc));
   } else {
      $fp = fopen($xmlloc,'r');
      while(!feof($fp)){
         $data = $data . fread($fp, 1024);
      }
      fclose($fp);
   }

/*$fp = fopen($xmlloc,'r');
   $filesize=filesize($xmlloc);
   $data=fread($fp,$filesize);
*/
   if ($convert)
     $data= iconv("UTF-8", "ISO-8859-2", $data);
   $parser = xml_parser_create('ISO-8859-1');
   xml_parser_set_option($parser, XML_OPTION_SKIP_WHITE, 1);
   xml_parse_into_struct($parser, $data, $vals, $index);
   xml_parser_free($parser);

   $tree = array();
   $i = 0;

   if (isset($vals[$i]['attributes'])) {
      $tree[$vals[$i]['tag']][]['ATTRIBUTES'] = $vals[$i]['attributes'];
      $index = count($tree[$vals[$i]['tag']])-1;
      $tree[$vals[$i]['tag']][$index] =  array_merge($tree[$vals[$i]['tag']][$index], GetChildren($vals, $i));
   } else {
      $tree[$vals[$i]['tag']][] = GetChildren($vals, $i);
   }
return $tree;
}

?>

