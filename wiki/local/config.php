<?php if (!defined('PmWiki')) exit();

## Produce a unique cookie prefix for this site.
$CookiePrefix = substr($tmp = md5(__FILE__), 0, 5).'_';

##  $WikiTitle is the name that appears in the browser's title bar.
$WikiTitle = 'praterj Wiki';

$ScriptUrl = 'https://web.engr.oregonstate.edu/~praterj/wiki';
$PubDirUrl = 'https://web.engr.oregonstate.edu/~praterj/wiki/pub';

##  If you want to use URLs of the form .../pmwiki.php/Group/PageName instead of .../pmwiki.php?p=Group.PageName. Doesn't work in all
# environments,
$EnablePathInfo = 1;

# get rid of "Main." from Urls
$PagePathFmt = array(
           '{$Group}.$1',           # page in current group
           '{$DefaultGroup}.$1',    # page in default group (Main)
           '$1.$1',                 # group home page
           '$1.{$DefaultName}',     # group home page
    );

   SDV($DefaultPage, 'Main.HomePage');
   $pagename = MakePageName($DefaultPage, $pagename);

    $FmtPV['$PageUrl'] = 'PUE(($group==$GLOBALS["DefaultGroup"])
                                 ? "$ScriptUrl/$name"
                                   : "$ScriptUrl/$group/$name")';
######################################

#$PageLogoUrl = "coe_custom.png";

## If you want to have a custom skin
#$Skin = 'monobook';


$EnableGUIButtons = 1;

$EnableUpload = 1;


if ($action == 'refcount') include_once('$FarmD/scripts/refcount.php');

##  The feeds.php script enables ?action=rss
if ($action == 'rss') include_once('$FarmD/scripts/feeds.php');   # RSS 2.0

include_once("$FarmD/cookbook/pmwiki2pdf/pmwiki2pdf.php");

$EnableRelativePageVars = 1;

session_name('praterjWikiSESSID');

//add non-ldap users here
//$AuthUser['me'] = crypt('test');

// LDAP Authentication

// If you want group support, uncomment these next lines and put in
// an array of groups

//$ldapc['filter_base_dn'] = "ou=group,dc=engr,dc=oregonstate,dc=edu";
//$ldapc['filter_user_attr'] = "memberuid";
//$ldapc['filter'] = array (
//   "(cn=group)",
//);

// AuthUser should be the string to authenticate the user
$AuthUser['ldap'] = 'ldaps://ldap.engr.oregonstate.edu/ou=people,dc=engr,dc=oregonstate,dc=edu?uid?one';

// If you want individual users to have access, add them in a comma
// separated list. By default, only the user has access to read or
// write to the wiki.  If you want anyone to be able to read the wiki
// comment out the ['read'] line.  Set it to 'id:*' if you want anyone
// with an ENGR account to be able to read (or anyone in an ldap group
// defined above)

$DefaultPasswords['admin'] = 'id:praterj';
$DefaultPasswords['upload'] = 'id:praterj';
$DefaultPasswords['edit'] = 'id:praterj';
// $DefaultPasswords['read'] = 'id:praterj';

include_once("$FarmD/scripts/authuser.php");
