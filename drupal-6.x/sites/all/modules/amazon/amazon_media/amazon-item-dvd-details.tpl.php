<div class="<?php print $classes; ?>">
<?php if (!empty($smallimage)) { print $smallimage; } ?>
<div><strong><?php print l($title, $detailpageurl, array('html' => TRUE, 'attributes' => array('rel' => 'nofollow'))); ?></strong> (<?php print $theatricalreleaseyear; ?>)</div>
<div><strong><?php print t('Director'); ?>:</strong> <?php print $director; ?></div>
<div><strong><?php print t('Starring'); ?>:</strong> <?php print $actor; ?></div>
<div><strong><?php print t('Rating'); ?>:</strong> <?php print $audiencerating; ?></div>
</div>
