<div id="simple_ads">

  <div class="title"><h2><?php print $node->title;?></h2></div>
  <div class="body"> <?php print $node->body['und'][0]['value'] ?></div>
  <div class="picture">   <img width="480px" src="/sites/default/files/<?php print $node->field_ads_image['und'][0]['filename']?>" /> </div>
</div>
