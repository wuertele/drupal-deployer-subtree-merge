<?php

function theme_amazon_item__dvd($item, $style = 'default') {
  $output = '';
  switch ($style) {
    case 'full':
      $output .= '<div class="'. _amazon_item_classes($item) .' amazon-item-full">';
      $output .= theme('image', $item['imagesets']['mediumimage']['url'], t('Cover image'), check_markup($item['title']), NULL, FALSE);
      $output .= '<h3>'. l(check_plain($item['title']), $item['detailpageurl'], array('attributes' => array('rel' => 'nofollow'))) .'</h3>';
      $output .= '</div>';
      break;
    case 'thumbnail':
      $output .= '<div class="'. _amazon_item_classes($item) .' amazon-item-thumbnail">';
      $output .= theme('image', $item['imagesets']['mediumimage']['url'], t('Cover image'), check_markup($item['title']), NULL, FALSE);
      $output .= '</div>';
      break;
    default:
      $output .= '<div class="'. _amazon_item_classes($item) .'">';
      $output .= theme('image', $item['imagesets']['smallimage']['url'], t('Cover image'), check_markup($item['title']), NULL, FALSE);
      $date = split('-', $item['theatricalreleasedate']);
      $output .= '<h3>'. l(check_markup($item['title']), $item['detailpageurl'], array('attributes' => array('rel' => 'nofollow'))) .' ('. check_plain($date[0]) .')</h3>';
      $output .= '<div><strong>'. t('Director') .':</strong> '. implode(', ', $item['director']) .'</div>';
      $output .= '<div><strong>'. t('Rating') .':</strong> '. $item['audiencerating'] .'</div>';
      $output .= '<div><strong>'. t('Running time') .':</strong> '. $item['runningtime'] .' '. t('minutes') .'</div>';
      $output .= '</div>';
      break;
  }
  return $output;
}

function theme_amazon_inline_item_dvd($item) {
  $date = split('-', $item['theatricalreleasedate']);
  $output = '<span class="'. _amazon_item_classes($item) .' amazon-item-inline">';
  $output .= l($item['title'] . ' (' . $date[0] . ')', $item['detailpageurl'], array('attributes' => array('rel' => 'nofollow')));
  $output .= '</span>';
  return $output;
}


function theme_amazon_inline_item_software($item) {
  $output = '<span class="'. _amazon_item_classes($item) .' amazon-item-inline">';
  $output .= l($item['title'] . ' (' . $item['operatingsystem'] . ')', $item['detailpageurl'], array('attributes' => array('rel' => 'nofollow')));
  $output .= '</span>';
  return $output;
}


function theme_amazon_inline_item_video_games($item) {
  $output = '<span class="'. _amazon_item_classes($item) .' amazon-item-inline">';
  $output .= l($item['title'] . ' (' . $item['hardwareplatform'] . ')', $item['detailpageurl'], array('attributes' => array('rel' => 'nofollow')));
  $output .= '</span>';
  return $output;
}
