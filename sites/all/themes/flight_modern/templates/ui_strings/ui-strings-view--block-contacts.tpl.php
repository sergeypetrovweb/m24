<div id="inform">
  <h2><?php print t($settings['title']) ?></h2>
  <ul>
    <?php for ($i = 0; $i < $settings['items']['count_items']; $i++) : ?>
      <li class="<?php print $settings['items'][$i]['icon'] ?>"><?php print t($settings['items'][$i]['text']) ?></li>
    <?php endfor; ?>
  </ul>
</div>