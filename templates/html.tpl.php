<!doctype html>
<html<?php print $html_attributes; ?>>
<head>
<?php print $head; ?>
<title><?php print $head_title; ?></title>
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
<?php print $styles; ?>
<!--[if lt IE 9]>
<script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
<![endif]-->
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
  <?php print $scripts; ?>
</body>
</html>
