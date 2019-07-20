#!/usr/bin/perl
#
# skif version 1.8 (C)opyright Christophe Gros 2017
#

use Carp;
use skif;
use Getopt::Long;

my $version, $help, $verbose, $pw, $host, $port, $plcnt, $output, $tzp;
my ($db, $user) = ("skylendar", $ENV{USER});

sub fi
{
    my ($file) = @_;
		$output =~ s/"//g if($output);
		die("The output file must be a skif or aaf file!") if($output ne undef && $output !~ /\.(aaf|AAF|skif|SKIF)$/);
    foreach $f (< $file >)
		{
			$f =~ s/"//g;
    	if($f =~ /\.aaf$/i)
    	{
					DATASET::LoadCode($db, $user, $host, $port, $pw);
					my $s = new SKIF;
					$s->ReadAAF($f);
					$f =~ s/\.aaf$/.skif/i;
					open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
					print "write $f\n" if($verbose);
					print FILE $s->WriteSKIF;
					close FILE;
    	}
    	elsif($f =~ /\.skif$/i)
    	{
					DATASET::LoadCode($db, $user, $host, $port, $pw);
					my $s = new SKIF;
					$s->ReadSKIF($f);
					$f =~ s/\.skif$/.aaf/i;
					open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
					print "write $f\n" if($verbose);
					print FILE $s->WriteAAF;
					close FILE;
    	}
    	elsif($f =~/(\.kst$)|(\.dat$)/i)
    	{
					DATASET::LoadCode($db, $user, $host, $port, $pw) if($plcnt);
					my $s = new SKIF;
					$s->ReadKst($f, $plcnt);
					$f =~ /\.kst$/ ? $f =~ s/\.kst$/.skif/i : $f =~ s/\.dat$/.skif/i;
					open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
					print "write $f\n" if($verbose);
					print FILE $s->WriteSKIF;
					close FILE;	
    	}
			elsif($f =~ /\.mtx$/i)
			{
					my $s = new SKIF;
					$s->ReadMaitreya($f);
					$f =~ s/\.mtx$/.skif/i;
					open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
					print "write $f\n" if($verbose);
					print FILE $s->WriteSKIF;
					close FILE;
			}
			elsif($f =~ /\.zbs$/i)
			{
				my $s = new SKIF;
				$s->ReadZet8($f);
				$f =~ s/\.zbs$/.skif/i;
				open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
				print "write $f\n" if($verbose);
				print FILE $s->WriteSKIF;
				close FILE;
			}
			elsif($f =~ /\.qck$/i)
			{
				my $s = new SKIF;
				my $dbh = DATASET::OpenDB($db, $user, $host, $port, $pw);
				$s->ReadQuickChart($f, $dbh);
				$f =~ s/\.qck$/.skif/i;
				open FILE, ($output ne undef) ? ">$output" : ">$f" || croak "Can't open $f !\n";
				print "write $f\n" if($verbose);
				print FILE $s->WriteSKIF;
				close FILE;
				DATASET::CloseDB($dbh);
			}
    	else
    	{
				croak "Unknown file type '$f'!\n";
    	}
		}
}

GetOptions("version" => \$version, "db=s" => \$db, "user=s" => \$user, "host=s" => \$host, "port=i" => \$port, "pw=s" => \$pw, "help" => \$help,
"verbose" => \$verbose,  "out=s" => \$output, "tzp=s" => \$tzp, "plcnt" => \$plcnt, '<>' => \&fi);
print "skif version $SKIF::version\n" if($version);
print "skif [--help] [--version] [--db=database] [--user=username] [--host=hostname] [--port=port] [--pw=password] [--out=file] [--tzp=timezone path] [--plcnt] [--verbose] [FILE...]\n" if($help);

