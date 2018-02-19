<?php
function callbackJID($buffer) {
  return (str_replace("JID", "PID", $buffer));
}

ob_start("callbackJID");