<div id="page">
  <?php if ($logo): ?>
    <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
  <?php endif; ?>
  
  <?php if ($site_name || $site_slogan): ?>
    <?php if ($site_name): ?>
      <h1 id="site-name" class="page-header">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
      </h1>
    <?php endif; ?>

    <?php if ($site_slogan): ?>
      <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
    <?php endif; ?>
  <?php endif; ?>

  <?php print render($page['header']); ?>

  <div id="main" class="row clearfix">

    <?php
      // Default # of columns in a Bootstrap row
      $content_col_span = 12;

      // Render the sidebars to see if there's anything in them.
      $sidebar_first = render($page['sidebar_first']);
      // Narrow main column to make room for sidebar_first
      if ($sidebar_first) $content_col_span -= 3;
      // Narrow main column to make room for sidebar_second
      $sidebar_second = render($page['sidebar_second']);
      if ($sidebar_second) $content_col_span -= 3;
    ?>

    <div id="content" class="span<?php print $content_col_span; ?> pull-right" role="main">
      <?php print render($page['highlighted']); ?>
      <?php print $breadcrumb; ?>
      <a id="main-content"></a>
      <?php print $messages; ?>
      <?php if ($tabs): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php if ($page['help']): ?> 
        <div class="well"><?php print render($page['help']); ?></div>
      <?php endif; ?>
      <?php if ($action_links): ?>
        <ul class="action-links nav nav-pills"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div><!-- /#content -->

    <?php if ($sidebar_first || $sidebar_second): ?>
      <aside class="sidebars pull-left">
        <?php if ($sidebar_first): ?>
          <div class="span3">
            <?php print $sidebar_first; ?>
          </div>
        <?php endif; ?>
        <?php if ($sidebar_second): ?>
          <div class="span3">
            <?php print $sidebar_second; ?>
          </div>
        <?php endif; ?>
      </aside><!-- /.sidebars -->
    <?php endif; ?>
  </div><!-- /#main -->

  <footer>
    <?php print render($page['footer']); ?>
  </footer>

</div><!-- /#page -->

<a href="<?php print $base_path . 'admin'; ?>" class="admin-link"><i class="icon-wrench"></i></a>

<?php print render($page['bottom']); ?>
