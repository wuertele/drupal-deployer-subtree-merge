;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Measured Value Field module.
;; $Id$
;;
;; Started as fork of Money CCK field (http://drupal.org/project/money)
;;
;; Credit goes to Money CCK module maintainers:
;;   markus_petrux (http://drupal.org/user/39593)
;;   Wim Leers (original author) (http://drupal.org/user/99777)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

OVERVIEW
========

Most values in our life are not simple numbers, but numbers with units. Many 
CCK fields have mechanics to display units together with values via "suffix" 
and "prefix" settings. There is problem with that: these settings are 
configured once at field level and don't change. Also, user can't choose the 
unit together with value, which sometimes is a problem too. 
Measured Value Field module tries to overcome these problems. MVF 
implements value that has number and unit of measurement. 
MVF supports both single values, and value ranges, which means each range is 
pair of values that is treated like single value of field.
MVF module uses the Units module API, to get a list of units to work with. 
Thanks to this flexibility MVF can be used to setup: distances, weghts, 
currencies, percentages, speeds, calories... list is endless. It only depends
on what units you make available to Units module. 

DETAILS
=======

The form element for values is reused from the Formatted Number CCK module.
Decimal points and thousands separators are formatted using the Format Number
API module, where these options are configured from site and/or user settings.

Single values are stored as pairs too: just their "To" value is equal to the 
"From" one.
For ranges there are also advanced Views filters: you can filter using range 
overlap, and "in between" filter operator
 
Since MVF is using Units module, every unit available in Units also becomes 
available as part of Measured Value field. 


REQUIREMENTS
============

- CCK (http://drupal.org/project/cck)
- Format Number API (http://drupal.org/project/format_number)
- Formatted Number CCK (http://drupal.org/project/formatted_number)
- Units module (http://drupal.org/project/units)
- One or more Units integration modules enabled:
  Units module itself doesn't provide units, only API. So one needs to have 
  another module using it's API to provide units. For example, Currency Units 
  module, that is bundled together with Units, provides Currencies implemented 
  in Currency Exchange module.


INSTALLATION
============

- Please, make sure all required modules are installed first.

- Copy all contents of this package to your modules directory preserving
  subdirectory structure.

- Goto Administer > Site building > Modules to install this module.

- For maximum comfort, goto Administer > Content management  > Units and setup 
  site-wide list of enabled units. This will save you lot of time, because
  each MVF instance will use globally enabled units as a base.

- Create or edit content types and start adding Measured Value Fields.
  Note, that you need to have some units provided by the Units module for
  this module to work.
