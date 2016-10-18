<div id="ourteam">
  <h2><?php print t($settings['title']) ?></h2>
  <ul>
    <?php for ($i = 0; $i < $settings['items']['count_items']; $i++) : ?>
      <li>
        <div class="photowrap">
          <?php
          $img = file_load($settings['items'][$i]['photo']);
          print theme('image_style',array('path' => $img->uri,'style_name' => 'hotels_thumbnails143x134',));
          ?>
        </div>
        <div class="info">
          <h3><?php print t($settings['items'][$i]['name']) ?></h3>
          <h4><?php print t($settings['items'][$i]['role']) ?></h4>
          <a href="mailto:<?php print t($settings['items'][$i]['mail']) ?>" class="glyphicon glyphicon-envelope"></a>
        </div>
      </li>
    <?php endfor; ?>
  </ul>
</div>