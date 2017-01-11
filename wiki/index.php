<?php
// Uncomment the following line to turn errors on
//ini_set("display_errors","on");

// This is needed to allow secure ldap authentication
putenv('LDAPTLS_REQCERT=never');

include('/nfs/ca/info/www_secure/wiki/pmwiki/pmwiki.php');
