<?php
  unlink($del_path);
  $dname = dirname($del_path);
  rmdir($dname);