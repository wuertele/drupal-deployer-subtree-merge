<?php
if (!empty($detail) && !empty($$detail)) {
  print $$detail;
} else {
  print "$detail not found for $asin";
}
?>