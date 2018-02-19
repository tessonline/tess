<?php $d = $templateData; ?>

<p>
  
  <?php echo $d['info']; ?>

  <?php if (isset($d['url'])) { ?>

  <a href="<?php echo $d['url']; ?>" target="_blank"><?php echo $d['url']; ?></a>

  <?php } ?>
  
</p>

<input type="button" class="button btn" onclick="window.close(); window.opener.location.reload();" value="Zavřít">