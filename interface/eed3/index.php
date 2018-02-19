<?php

if (file_exists('server/soap.php'))
  Header('Location: user/index.php');
else
  Die('Konektor není dostupný!');
?>
