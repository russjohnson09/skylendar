#!/usr/bin/perl
my $a, $p;
foreach $i (@INC)
{
 $p = ($^O =~ /MSWin/) ? "lib" : "vendor_perl";
 $a = $i if($i =~ /$p/);
}
$a = $INC[$#INC - 1] if($a eq "");
print "$a\n";
