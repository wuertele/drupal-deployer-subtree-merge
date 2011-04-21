<div class="<?php print $classes; ?>">
<?php if (!empty($smallimage)) { print $smallimage; } ?>
<div><strong><?php print l($title, $detailpageurl, array('html' => TRUE, 'attributes' => array('rel' => 'nofollow'))); ?></strong> (<?php print $hardwareplatform; ?>)</div>
<div><strong><?php print t('Genre'); ?>:</strong> <?php print $genre; ?></div>
<div><strong><?php print t('Age rating'); ?>:</strong> <?php print $esrbagerating; ?></div>
<div><strong><?php print t('Price'); ?>:</strong> <?php print $listpriceformattedprice; ?></div>
</div>
