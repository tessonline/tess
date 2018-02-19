<?php
function Code39Pic_bin($code){

  $xpos=10;
  $ypos=5;
  $baseline=4;
  $height=30;
	$wide = $baseline;
	$narrow = $baseline / 2 ; 
	$gap = $narrow;

	$barChar['0'] = 'nnnwwnwnn';
	$barChar['1'] = 'wnnwnnnnw';
	$barChar['2'] = 'nnwwnnnnw';
	$barChar['3'] = 'wnwwnnnnn';
	$barChar['4'] = 'nnnwwnnnw';
	$barChar['5'] = 'wnnwwnnnn';
	$barChar['6'] = 'nnwwwnnnn';
	$barChar['7'] = 'nnnwnnwnw';
	$barChar['8'] = 'wnnwnnwnn';
	$barChar['9'] = 'nnwwnnwnn';
	$barChar['A'] = 'wnnnnwnnw';
	$barChar['B'] = 'nnwnnwnnw';
	$barChar['C'] = 'wnwnnwnnn';
	$barChar['D'] = 'nnnnwwnnw';
	$barChar['E'] = 'wnnnwwnnn';
	$barChar['F'] = 'nnwnwwnnn';
	$barChar['G'] = 'nnnnnwwnw';
	$barChar['H'] = 'wnnnnwwnn';
	$barChar['I'] = 'nnwnnwwnn';
	$barChar['J'] = 'nnnnwwwnn';
	$barChar['K'] = 'wnnnnnnww';
	$barChar['L'] = 'nnwnnnnww';
	$barChar['M'] = 'wnwnnnnwn';
	$barChar['N'] = 'nnnnwnnww';
	$barChar['O'] = 'wnnnwnnwn'; 
	$barChar['P'] = 'nnwnwnnwn';
	$barChar['Q'] = 'nnnnnnwww';
	$barChar['R'] = 'wnnnnnwwn';
	$barChar['S'] = 'nnwnnnwwn';
	$barChar['T'] = 'nnnnwnwwn';
	$barChar['U'] = 'wwnnnnnnw';
	$barChar['V'] = 'nwwnnnnnw';
	$barChar['W'] = 'wwwnnnnnn';
	$barChar['X'] = 'nwnnwnnnw';
	$barChar['Y'] = 'wwnnwnnnn';
	$barChar['Z'] = 'nwwnwnnnn';
	$barChar['-'] = 'nwnnnnwnw';
	$barChar['.'] = 'wwnnnnwnn';
	$barChar[' '] = 'nwwnnnwnn';
	$barChar['*'] = 'nwnnwnwnn';
	$barChar['$'] = 'nwnwnwnnn';
	$barChar['/'] = 'nwnwnnnwn';
	$barChar['+'] = 'nwnnnwnwn';
	$barChar['%'] = 'nnnwnwnwn';

  //otestujeme delku retezce
  $img=imagecreate(400,50);
  $bila = imagecolorallocate($img, 255, 255, 255);
  $cerna = imagecolorallocate($img, 0, 0, 0);
  imagefill($img,0,0,$bila);

  imagestring($img, 3, 10, 38, $code, $cerna); 
	$code = '*'.strtoupper($code).'*';
	for($i=0; $i<strlen($code); $i++){
		$char = $code{$i};
		if(!isset($barChar[$char])){
			Die('Invalid character in barcode: '.$char);
		}
		$seq = $barChar[$char];
		for($bar=0; $bar<9; $bar++){
			if($seq{$bar} == 'n'){
				$lineWidth = $narrow;
			}else{
				$lineWidth = $wide;
			}
			if($bar % 2 == 0){
        imagefilledrectangle($img,$xpos,$ypos,$xpos+$lineWidth,$ypos+$height,$cerna);
        //imagefilledrectangle($img,$xpos,$ypos,$lineWidth,$height,$cerna);
			}
			$xpos += $lineWidth;
		}
		$xpos += $gap;
	}

  $file='/tmp/'.md5(Date('dmYhms')).'.png';
  ImagePNG($img,$file);
  $fp=fopen($file,'r');
  fseek($fp,0);
  $soubor="";
  while (!feof ($fp)) {
      $buffer = fgets($fp, 4096);
      $soubor.=$buffer;
  }
  ImageDestroy($img);
  fclose($fp);
  @unlink($file);
  return $soubor;
}


function Code39Pic($code) {
  $soubor = Code39Pic_bin($code);
  return bin2hex($soubor);
}



/*
$text=Code39Pic('101168/2008');
/*
for($a=0; $a<strlen($text);$a++)
{
//  echo $text[$a];
//  echo hex($text[$a]);
}
$text2=bin2hex($text);
echo $text;
*/
