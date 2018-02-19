<?php

function getHref($id, $nazev, $script = '') {
  return '<a href="' . ($script ? 'javascript:' . $script . '(\'' : '') . '/ost/posta/edit.php?insert&MAIN_DOC=' . $id . '&cacheid=' . ($script ? $script . '\')' : '') . '">' . $nazev . '</a>';
}
