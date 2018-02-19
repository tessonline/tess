<?php

class PDF {

  private $pdf_name;
  private $files = array();
  
  
  /*
   * Contructor
   * @author luma
   */
  function __construct($pdf_name) {
    $this->pdf_name = $pdf_name;
  }

    
  public function add($filename) {
    $this->files[] = $filename;
  }
  
  public function getFileName() {
    return $this->pdf_name;
  }
  
  public function create() {    
    $uplobj = Upload(array(
      'create_only_objects' => true,
      'agenda' => 'POSTA',
      'noshowheader'=>true)
        );
 //   echo "1<br />";
 //   var_dump ($this->files);
//    $pdf_file = $uplobj['table']->stg_obj->mergeFiles($this->files);
  /*  echo "2<br />";
    $i = 0;
    $pdf_unavailable = true;
    var_dump($pdf_file);
    echo "1<br />";*/
    $i=0;
    $pdf_file = false;
    while (!$pdf_file) {

      $pdf_file = $uplobj['table']->stg_obj->mergeFiles($this->files);

     /* if (!$pdf_file) {
        
        if ($i==600) {
          echo '<br />';
          echo 'Požadavek na generování PDF se ukládá do fronty, která je postupně zpracovávána. Z toho důvodu může být výsledné PDF k dispozici až za několik minut.';
        }
        echo '<br />';
        echo 'Další pokus proběhne automaticky za 10 sekund.';
      }*/
      sleep(1);
      $i++;
      if ($i>10) return false;
    }
    file_put_contents($this->pdf_name,$pdf_file);
    return true;
    
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
      a.download = "download.php?file=<?php echo $this->pdf_name; echo $redirect; ?>&param=<?php echo $param; ?>";
      a.href = "download.php?file=<?php echo $this->pdf_name; echo $redirect; ?>&param=<?php echo $param; ?>";
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
  
  
  public function upload($id,$agenda) {
    $name = basename($this->pdf_name);
    $tmp_file = $this->pdf_name;     
     chmod($tmp_file, 0777);
     include_once(FileUp2('.admin/upload_.inc'));
     $u=Upload(array('create_only_objects'=>true,'agenda'=>$agenda,'noshowheader'=>true));
     $ret = $u['table']->SaveFileToAgendaRecord($tmp_file, $id);
     return $ret;
  }  
}

