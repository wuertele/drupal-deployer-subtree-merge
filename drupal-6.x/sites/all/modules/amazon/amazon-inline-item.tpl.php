<?php
$alt_theme = 'amazon_inline_item_' . _amazon_clean_type($item['producttypename']);
if ($output = theme($alt_theme, $item)) {
  print $output;
}
else {
?>
<span class="<?php print _amazon_item_classes($item) ?> amazon-item-inline">
  <?php print l($item['title'], $item['detailpageurl'], array('html' => TRUE, 'attributes' => array('rel' => 'nofollow'))); ?>
</span>
<?php } ?>
