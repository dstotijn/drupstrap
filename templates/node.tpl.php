<?php if (!empty($pre_object)) print render($pre_object) ?>

<div class="<?php print $classes ?>" <?php print ($attributes) ?>>
  <?php if (!empty($submitted)): ?>
    <div class="submitted"><small><?php print $submitted ?></small></div>
  <?php endif; ?>

  <?php if (!empty($title_prefix)) print render($title_prefix); ?>

  <?php if (!$page && !empty($title)): ?>
    <h2 class="node-title" <?php if (!empty($title_attributes)) print $title_attributes ?>>
      <?php if (!empty($new)): ?><span class="new"><?php print $new ?></span><?php endif; ?>
      <a href="<?php print $node_url ?>"><?php print $title ?></a>
    </h2>
  <?php endif; ?>

  <?php if (!empty($title_suffix)) print render($title_suffix); ?>


  <?php if (!empty($content)): ?>
      <?php print render($content) ?>
  <?php endif; ?>

  <?php if (!empty($links)): ?>
      <?php print render($links) ?>
  <?php endif; ?>

  <?php if (!$page): ?>
    <hr>
  <?php endif; ?>

</div>

<?php if (!empty($post_object)) print render($post_object) ?>
