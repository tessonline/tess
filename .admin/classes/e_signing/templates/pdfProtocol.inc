<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
  
  <head>
    
    <meta charset="utf-8">
    
    <title>PDF Protocol</title>
    
    <link rel="stylesheet" type="text/css" href="<?php echo $data['styles']; ?>">
    
  </head>
  
  <body>
    
    <div class="header">  
      
      <p></p>
      
      <table>
        <tr>
          <td class="first"> <?php echo $data['title']; ?></td>
          <td class="second"></td>
          <td class="third"></td>
        </tr>
      </table>
      
    </div>
    
    <div class="block">
      
      <p><?php echo $data['id']['label']; ?></p>
      <p><span> <?php echo $data['id']['value']; ?> </span></p> 
      
    </div>
    
    <?php foreach ($data['blocks'] as $block) { ?>
    
    <div class="block">
      
      <p><?php echo $block['label']; ?></p>

      <table>

        <?php foreach ($block['items'] as $item) { ?>
        
        <tr>
          <td class="label"><?php echo $item['label']; ?></td>
          <td class="value"><?php echo $item['value']; ?></td>
        </tr>
    
        <?php } ?>

      </table>
      
    </div>
    
    <?php } ?>
    
    <?php if (isset($data['attachments'])) { ?>
    
    <div class="block">
      
      <p><?php echo $data['attachments']['label']; ?></p>

        <?php if (is_array($data['attachments']['items'])) foreach ($data['attachments']['items'] as $items) { ?>
        
      		<p><?php echo $items['title']; ?></p>
      		
      		<table>
      				
        	<?php  if (is_array($items)) foreach ($items as $item) { ?>
        	
        		<tr>
          		<td class="label"><?php echo $item['label']; ?></td>
          		<td class="value"><?php echo $item['value']; ?></td>
        		</tr>
        		
        	<?php } ?>
        		
      		</table>
      		
        <?php } ?>
        
    </div>
    
    <?php } ?>
    
  </body>
  
  <script>
  </script>
  
</html>
