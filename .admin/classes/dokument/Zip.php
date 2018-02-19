<?php

class Zip extends ZipArchive{

  private $zip_name;
  
 // private $zip;

  
  /*
   * Contructor
   * @author luma
   */
  function __construct($zip_name,$op_type = ZipArchive::CREATE) {
    $this->zip_name = $zip_name;
    $this->open($zip_name, $op_type);
  }
    
  public function add($filename,$data) {
    $this->addFromString($filename, $data);
  }
  
  public function create() {
    $this->close();
    return true;
  }
  
  public function getFileName() {
    return $this->zip_name;
  }
  
  public function deleteFromArchive($file_to_delete) {
    $z = $this->zip;
    for($i=0;$i<$z->numFiles;$i++){
      $entry_info = $z->statIndex($i);
      if(substr($entry_info["name"],0,strlen($file_to_delete))==$file_to_delete){
        $z->deleteIndex($i);
      }
    }
    
  }
     
  public function download($param=null,$redirect="") {
    ?>
    
    <script>
    function sleep(milliseconds) {
    	  var start = new Date().getTime();
    	  for (var i = 0; i < 1e7; i++) {
    	    if ((new Date().getTime() - start) > milliseconds){
    	      break;
    	    }
    	  }
    	}
      var a = document.createElement("a");
      document.body.appendChild(a);
      a.target = "_blank";
      a.download = encodeURI("download.php?file=<?php echo $this->zip_name; echo $redirect; ?>&param=<?php echo $param; ?>");
      a.href = encodeURI("download.php?file=<?php echo $this->zip_name; echo $redirect; ?>&param=<?php echo $param; ?>");
      var ua = window.navigator.userAgent;
      var msie = ua.indexOf("MSIE");
      var edge = ua.indexOf("Edge")
      if (msie > 0 || edge > 0 || !!navigator.userAgent.match(/Trident.*rv\:11\./)) {
        //Alert("In");
          a.click();
      } else {
        var clickEvent = new MouseEvent("click", {
            "view": window,
            "bubbles": true,
            "cancelable": false
        });
        a.dispatchEvent(clickEvent);
      }
   sleep(1000);
    
//      window.open("download.php?file=<?php echo $this->zip_name; ?>&param=<?php echo $param; ?>", "_blank", "width=400,height=500")
    	//window.location.href  = "download.php?file=<?php echo $this->zip_name; ?>&param=<?php echo $param; ?>";
//		$.ajax({
//    	  url: "download.php?file=<?php echo $this->zip_name; ?>&param=<?php echo $param; ?>",
//    	  context: document.body
//    	}).done(function() {
//        	alert("done");
//    	});

    	
    </script>
    <?php 
  }
  
    
  private function folderToZip($folder, &$zipFile, $exclusiveLength) {
    $handle = opendir($folder);
    while (false !== $f = readdir($handle)) {
      if ($f != '.' && $f != '..') {
        $filePath = "$folder/$f";
        // Remove prefix from file path before add to zip.
        $localPath = substr($filePath, $exclusiveLength);
        if (is_file($filePath)) {
          $zipFile->addFile($filePath, $localPath);
        } elseif (is_dir($filePath)) {
          // Add sub-directory.
          $zipFile->addEmptyDir($localPath);
          self::folderToZip($filePath, $zipFile, $exclusiveLength);
        }
      }
    }
    closedir($handle);
  }
  
  /*public function zipDir($sourcePath, $outZipPath)
  {
    $pathInfo = pathInfo($sourcePath);
    $parentPath = $pathInfo['dirname'];
    $dirName = $pathInfo['basename'];
  
    $z = new ZipArchive();
    $z->open($outZipPath, ZIPARCHIVE::CREATE);
    $z->addEmptyDir($dirName);
    self::folderToZip($sourcePath, $z, strlen("$parentPath/"));
    $z->close();
  }*/
  
  
  public function upload($id,$agenda) {
    $name = basename($this->zip_name);
     $tmp_file = $this->zip_name;     
     chmod($tmp_file, 0777);
     include_once(FileUp2('.admin/upload_.inc'));
     $u=Upload(array('create_only_objects'=>true,'agenda'=>$agenda,'noshowheader'=>true));
     $ret = $u['table']->SaveFileToAgendaRecord($tmp_file, $id);
     return $ret;
  }  
}

