<?php
include_once(FileUp2('.admin/db/db_prirustkove_body.inc'));

function ShowName($typ, $id) {
  if ($typ == 'PRIR') {
//     global $bod;
//     if (!$bod) $bod = new DB_PRIRUSTKOVE_BODY;
//     $sql = 'select nazev from prirustkove_body where OBJECTID='.$id;
//     $bod->query($sql);
//     $data = $bod->Record;  
  }
  if ($typ == 'PAGIS') {
  }
  
  return $data['NAZEV'];
}  
Function ShowOdkazGIS($typ,$id) {
  if ($typ == 'PRIR') {
    global $img_prir;
    if (!$img) $img=FileUp2('images/globe.gif');
    $href="http://gis.up.npu.cz/tms/npu_uz/index.php?client_type=map_resize&Project=TMS_NPU_UZIDENT&interface=tmv&Values=".$id."&Theme=pagis&Field=IDREG&Command=SelByFld&MinScale=2000&Zoom=ToExtent&client_lang=cz_win";
    $url="<a href='".$href."' target='okno_$typ'><img src='".$img."' border=0></a>";
  }
  if ($typ == 'PAGIS') {
    global $img_pagis;
    if (!$img) $img=FileUp2('images/globe.gif');
    $href="http://gis.up.npu.cz/tms/npu_uz/index.php?client_type=map_resize&Project=TMS_NPU_UZIDENT&interface=tmv&Values=".$id."&Theme=pagis&Field=IDOB_PG&Command=SelByFld&MinScale=2000&Zoom=ToExtent&client_lang=cz_win";
    $url="<a href='".$href."' target='okno_$typ'><img src='".$img."' border=0></a>";
  }
  return $url;
}

