<!DOCTYPE html>
<!--[if IEMobile 7]><html class="iem7" <?php print $html_attributes; ?>><![endif]-->
<!--[if lte IE 6]><html class="lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="lt-ie9 lt-ie8" <?php print $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="lt-ie9" <?php print $html_attributes; ?>><![endif]-->
<!--[if (gte IE 9)|(gt IEMobile 7)]><!--><html <?php print $html_attributes . $rdf_namespaces; ?>><!--<![endif]-->
  <head>
    <?php print $head; ?>
    <title><?php print $head_title; ?></title>
    <?php print $styles; ?>
    <?php print $scripts; ?>
    <?php if ($add_html5_shim and !$add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/html5.js"></script>
      <![endif]-->
    <?php elseif ($add_html5_shim and $add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/html5-respond.js"></script>
      <![endif]-->
    <?php elseif ($add_respond_js): ?>
      <!--[if lt IE 9]>
      <script src="<?php print $base_path . $path_to_zen; ?>/js/respond.js"></script>
      <![endif]-->
    <?php endif; ?>
  </head>
  <body class="<?php print $classes; ?>" <?php print $attributes;?>>
    <?php if ($skip_link_text && $skip_link_anchor): ?>
    <a href="#<?php print $skip_link_anchor; ?>" class="sr-only"><?php print $skip_link_text; ?></a>
    <?php endif; ?>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
  </body>
</html>