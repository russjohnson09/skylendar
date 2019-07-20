#
# Perl package SKIF, version 1.8, (C)opyright Christophe Gros 2017
#
use POSIX;

sub DegToDec($)
{
		my $d = $_[0];
		my $si = $d < 0.0 ? -1.0 : 1.0;
		$d = fabs($d);
		my $t = fmod($d, 1.0) * 100.0 + 1e-10;
		my $j = int($t);
		$t = fmod($t, 1.0) * 100.0 + 1e-10;
		return $si * (int($d) + $j / 60.0 + $t / 3600.0);
}

sub DecToDeg($)
{
		my $d = $_[0];
		my $si = $d < 0.0 ? -1.0 : 1.0;
		$d = fabs($d);
		my $h = int($d), $m, $s;
		$d = fabs($d);
		$d -= fabs($h);
		$d *= 60;
		$m = int($d);
		$d -= $m;
		$d *= 60;
		$s = int($d);
		$s++ if($d - $s > 0.5);
		if($s == 60)
		{
				$s = 0;
				$m++;
				if($m == 60)
				{
						$m = 0;
						$h++;
				}
		}
	return $si * ($h + $m / 100.0 + $s / 10000.0);
}

sub Trim($)
{
		$_[0] =~ s/^ +//;
		$_[0] =~ s/ +$//;
		return $_[0];
}

package DATASET;
use Carp;
use Encode;
use Encode 'from_to';
use XML::DOM;
use PerlIO::encoding;

n:

my @month = ("jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep",
	     "oct", "nov", "dec" );

my %codelist, %src = (
		"0" => "Direct",
		"1*"=> "Register",
		"1F"=> "Fambook",
		"1" => "Astrologer",
		"2M"=> "Mother",
		"2F"=> "Father",
		"2P"=> "Personal",
		"2B"=> "Biography",
		"2R"=> "Partner",
		"3" => "Possibility",
		"4" => "Speculative"
),
		%StateCodes = (
"AL" => "Alabama",
"AK" => "Alaska",
"AS" => "American Samoa",
"AZ" => "Arizona",
"AR" => "Arkansas",
"CA" => "California",
"CO" => "Colorado",
"CT" => "Connecticut",
"DE" => "Delaware",
"DC" => "Dist. of Columbia",
"FL" => "Florida",
"GA" => "Georgia",
"GU" => "Guam",
"HI" => "Hawaii",
"ID" => "Idaho",
"IL" => "Illinois",
"IN" => "Indiana",
"IA" => "Iowa",
"KS" => "Kansas",
"KY" => "Kentucky",
"LA" => "Louisiana La",
"ME" => "Maine",
"MD" => "Maryland",
"MH" => "Marshall",
"MA" => "Massachusetts",
"MI" => "Michigan",
"FM" => "Micronesia",
"MN" => "Minnesota",
"MS" => "Mississippi",
"MO" => "Missouri",
"MT" => "Montana",
"NE" => "Nebraska",
"NV" => "Nevada",
"NH" => "New Hampshire",
"NJ" => "New Jersey",
"NM" => "New Mexico",
"NY" => "New York",
"NC" => "North Carolina",
"ND" => "North Dakota",
"MP" => "Northern Marianas",
"OH" => "Ohio",
"OK" => "Oklahoma",
"OR" => "Oregon",
"PW" => "Palau",
"PA" => "Pennsylvania",
"PR" => "Puerto Rico",
"RI" => "Rhode Island",
"SC" => "South Carolina",
"SD" => "South Dakota",
"TN" => "Tennessee",
"TX" => "Texas",
"UT" => "Utah",
"VT" => "Vermont",
"VA" => "Virginia",
"VI" => "Virgin Islands",
"WA" => "Washington",
"WV" => "West Virginia",
"WI" => "Wisconsin",
"WY" => "Wyoming"
);

sub OpenDB($$$$$)
{
		my ($db, $user, $host, $port , $pw) = @_;
		die("db '$db' or user '$user' not found.") if(!$db || !$user);
		my $prefix, $f, $d, $ds, $dbh;
		foreach $prefix (@INC)
		{
				if(-f "$prefix/DBD/PgPP.pm") { $d = "DBI:PgPP"; last; }
				if(-f "$prefix/DBD/Pg.pm")   { $d = "DBI:Pg"; last; }
		}
		croak("No postgres DBD found !\n") if($d eq "");
		use DBI;
		$ds="$d:db=$db";
		$ds .= ";host=$host" if($host ne undef);
		$ds .= ";port=$port" if($port ne undef);
		$dbh = DBI->connect($ds, $user, $pw) or die;
		return $dbh;
}

sub CloseDB($)
{
		my $dbh = shift;
		$dbh->disconnect;
}

sub FetchTZ($$)
{
		my($country, $dbh) = @_;
		my $tzs = $dbh->selectall_arrayref("SELECT tzfile FROM Country WHERE name = \'" . $country . "\'", {Slice => {}});
		return $$tzs[0]->{tzfile};
}

sub FetchState($$)
{
	my($state, $dbh) = @_;
		my $tzs = $dbh->selectall_arrayref("SELECT name, tzfile FROM Country WHERE name like \'%" . $state . "%\'", {Slice => {}});
		return ($$tzs[0]->{name}, $$tzs[0]->{tzfile});	
}

sub LoadCode($$$$$)
{
		return if(scalar keys %codelist > 0);
		my ($db, $user, $host, $port , $pw) = @_;
		my $dbh = OpenDB($db, $user, $host, $port , $pw);
		my $codes = $dbh->selectall_arrayref("SELECT name AS country, code FROM Country WHERE Code <> \'\'",
				{Slice => {}});
		foreach my $code (@$codes)
		{
				$codelist{$code->{country}} = ::Trim(uc $code->{code});
		}
		CloseDB($dbh);
}

sub FetchCountry($)
{
    my ($self, $code) = @_;
		my $key, $value;
    $code = uc $code;
		while(($key, $value) = each %codelist)
		{
				return $key if($value eq $code);
		}
    return undef;
}

sub FetchCode($)
{
    my ($self, $country) = @_;
		return exists $codelist{$country} ? $codelist{$country} : "*";
}

sub new
{
    my $self = {};
    $self->{Zpath} = $::tzp ? $::tzp : "/usr/share/zoneinfo/";
    bless $self;
    $self->reset;
    return $self;
}

sub reset
{
    my ($self) = @_;
    $self->{Name}         = undef;
    $self->{Gender}       = "N";
    $self->{Type}         = "Birth/Beginning";
    $self->{Day}          = 1;
    $self->{Month}        = 1;
    $self->{Year}         = 2000;
    $self->{Hm}           = "0:0";
    $self->{Accuracy}     = "0";
    $self->{Timezone}     = "0:0";
    $self->{Daylight}     = "0:0";
    $self->{Julday}       = "0.0";
    $self->{Latitude}     = "0:0";
    $self->{Longitude}    = "0:0";
    $self->{Place}        = undef;
    $self->{ZoneInfoFile} = "GMT";
    $self->{Country}      = "Default Country";
    $self->{Keywords}     = "";
    $self->{Comment}      = "";
}

sub GetContent($)
{
    my ($self, $node) = @_;
    return encode("utf-8", $node->getFirstChild->getNodeValue) if($node->hasChildNodes);
    return undef;
}

sub GetMonth($)
{
    my ($self, $mon) = @_;
    my $i;
		$mon = lc $mon;
		foreach $i (0 ... 11)
    {
      return($i + 1) if($month[$i] eq $mon)
    }
    return $mon if($mon >= 1 && $mon <= 12);
    return 0;
}

sub GetTime
{
    my ($self, $time) = @_;
    my ($h, $m, $s) = split /\:/, $time;
    if($m =~ /pm$/)
    {
      $h += 12;
      $m =~ s/pm$//;
    }
		if($s && $s =~ /pm$/)
		{
      $h += 12;
      $s =~ s/pm$//;
    }
    $m =~ s/am$// if($m =~ /am$/);
		$s =~ s/am$// if($s && $s =~ /am$/);
		return ($h, $m, $s) if($s);
    return ($h, $m); 
}

sub ReadKst($*$)
{
	my $self = shift;
	local *FILE = shift;
	my $plcnt = shift;
  if(<FILE> !~ /^\@0102/)
  {
    croak "Not a .dat or .kst file\n";
    close FILE;
    return;
  }     
  while(!eof FILE)
  {
      my $l = <FILE>;
      chomp $l;
      if($l =~ /^(-|\/)qb/)
      {
        my @line = split " ", $l;
        $self->{Month}     = $self->GetMonth($line[1]);
        $self->{Day}       = $line[2];
        $self->{Year}      = $line[3];
        my @hm = $self->GetTime($line[4]);
        $self->{Hm}        = "$hm[0]:$hm[1]";
        $self->{Daylight}  = ($line[5] eq "DT") ? "1:00" : "0:00";
        if($line[6] =~ /^-/)
        {
          $line[6] =~ s/^-//;
        }
        elsif($line[6] =~ /^\+/)
        {
          $line[6] =~ s/^\+/-/;
        }
        else
        {
          $line[6] = "-" . $line[6];
        }
        $self->{Timezone}  = $line[6];
        $self->{Longitude} = $line[7];
        $self->{Latitude}  = $line[8];
      }
      elsif($l =~ /^(-|\/)zi/)
      {
        $l =~ s/^(-|\/)zi +//;
        my ($na, $pl) = split /\" +\"/, $l;
        $na =~ s/\"//;
        $pl =~s/\"//;
				$pl =~ s/\x0d//;
        from_to($na, "iso-8859-1", "utf-8");
        $self->{Name}  = $na;
        from_to($pl, "iso-8859-1", "utf-8");
        if($plcnt)
				{
					my ($p, $c) = split /,/, $pl;
					$self->{Place} = ::Trim($p);
					my $cnt = $self->FetchCountry(::Trim($c));
					$self->{Country} = ($cnt eq undef) ? "Unknown Country Code '$c'" : $cnt;
				}
        else
				{
        	$self->{Place} = $pl;
				}
      }
      elsif($l =~ /^(-|\/)zf/)
      {
        my (@zif) = split /\//, $l;
        my $z1 = "$zif[$#zif -1]/$zif[$#zif]";
        $self->{ZoneInfoFile} = $z1 if(-r $self->{Zpath} . "/" . $z1);
        $z1 = $zif[$#zif];
        $self->{ZoneInfoFile} = $z1 if(-r $self->{Zpath} . "/" . $z1);
      }
      elsif($l =~ /^;/)
      {
        $l =~ s/^;//;
        from_to($l, "iso-8859-1", "utf-8");
        $self->{Comment} .= "$l\n" if($l ne "");
      }
  }
}

sub ReadDATASET($)
{
    my ($self, $ds) = @_;
    my @n = $ds->getElementsByTagName("*");
    foreach my $elem (@n)
    {
			my $name = $elem->getTagName;
			if($name eq "NAME")
			{
				$self->{Name} = $self->GetContent($elem);
			}
			elsif($name eq "TYPE")
			{
				$self->{Gender} = $elem->getAttribute("Gender");
			}
			elsif($name eq "DATE")
			{
				$self->{Day}      = $elem->getAttribute("Day");
				$self->{Month}    = $elem->getAttribute("Month");
				$self->{Year}     = $elem->getAttribute("Year");
				$self->{Hm}       = $elem->getAttribute("Hm");
				$self->{Timezone} = $elem->getAttribute("Timezone");
				$self->{Daylight} = $elem->getAttribute("Daylight");
				$self->{Accuracy} = $elem->getAttribute("Accuracy");
				$self->{Julday}   = $elem->getAttribute("Julday");
			}
			elsif($name eq "PLACE")
			{
				$self->{Latitude}  = $elem->getAttribute("Latitude");
				$self->{Longitude} = $elem->getAttribute("Longitude");
				$self->{Place}     = $self->GetContent($elem);
			}
			elsif($name eq "COUNTRY")
			{
				$self->{ZoneInfoFile} = $elem->getAttribute("ZoneInfoFile");
				$self->{Country}      = $self->GetContent($elem); 
			}
			elsif($name eq "KEYWORDS")
			{
				$self->{Keywords}     = $self->GetContent($elem);
			}
			elsif($name eq "COMMENT")
			{
				$self->{Comment}      = $self->GetContent($elem); 
			}
    }
}

sub WriteDATASET($)
{
    my ($self, $doc, $skif) = @_;
    my $ds = $doc->createElement("DATASET");

    my $elem = $doc->createElement("NAME");
    my $text = $doc->createTextNode($self->{Name});
    $elem->appendChild($text);
    $ds->appendChild($elem);
    
    $elem = $doc->createElement("TYPE");
    $elem->setAttribute("Gender", $self->{Gender});
    $text = $doc->createTextNode($self->{Type});
    $elem->appendChild($text);
    $ds->appendChild($elem);

    $elem = $doc->createElement("DATE");
    $elem->setAttribute("Day", $self->{Day});
    $elem->setAttribute("Month", $self->{Month});
    $elem->setAttribute("Year", $self->{Year});
    $elem->setAttribute("Hm", $self->{Hm});
    $elem->setAttribute("Accuracy", $self->{Accuracy});
    $elem->setAttribute("Julday",   $self->{Julday});
    $elem->setAttribute("Timezone", $self->{Timezone});
    $elem->setAttribute("Daylight", $self->{Daylight});
    $ds->appendChild($elem);

    $elem = $doc->createElement("PLACE");
    $elem->setAttribute("Latitude", $self->{Latitude});
    $elem->setAttribute("Longitude", $self->{Longitude});
    $text = $doc->createTextNode($self->{Place});
    $elem->appendChild($text);
    $ds->appendChild($elem);

    $elem = $doc->createElement("COUNTRY");
    $elem->setAttribute("ZoneInfoFile", $self->{ZoneInfoFile});
    $text = $doc->createTextNode($self->{Country});
    $elem->appendChild($text);
    $ds->appendChild($elem);

    $elem = $doc->createElement("KEYWORDS");
    $text = $doc->createTextNode($self->{Keywords});
    $elem->appendChild($text);
    $ds->appendChild($elem);

    $elem = $doc->createElement("COMMENT");
    $text = $doc->createTextNode($self->{Comment});
    $elem->appendChild($text);
    $ds->appendChild($elem);

    $skif->appendChild($ds);
}

sub DMS($$)
{
    my ($self, $dms) = @_;
    $dms = uc $dms;
    my ($h, $m, $s) = split /:|HE|HW|E|W|N|S/, $dms;
    $dms =~ /.*(HE|HW|E|W|N|S).*/;
    return ($h, $m, $1);
}

sub ReadAAFSeg($$*)
{
    my $self = shift;
    my $l = shift;
    local *FILE = shift;
    do
    {
			$l =~ s/(\r|\n)//g;
			if($l =~ /.*\#A93:/)
			{
	    $l =~ s/.*\#A93\://;
	    my ($name, $fname, $gen, $date, $time, $place, $code) = split /,/, $l;
      $gen = uc $gen;
	    $fname = "" if($fname =~ /.*\*.*/ || $gen eq "L" || $gen eq "O");
	    $self->{Name} = $fname eq "" ? $name : "$fname $name";
	    from_to($self->{Name}, "iso-8859-1", "utf-8");
	    if($gen eq "M")
	    {
				$self->{Gender} = "M";
	    }
	    elsif($gen eq "F" || $gen eq "W")
	    {
				$self->{Gender} = "F";
	    }
	    else
	    {
				$self->{Gender} = "N";
				$self->{Type} = "Country" if($gen eq "L");
				$self->{Type} = "Organization" if($gen eq "O");
	    }
	    my ($day, $mon, $yea) = split(/\./, $date);
	    $self->{Day}   = $day;
	    $self->{Month} = $mon;
	    $self->{Year}  = $yea;
	    $time = uc $time;
	    $time =~ s/H/:/ if($time =~ /H/);
	    $time =~ s/M/:/ if($time =~ /M/);
	    if($time =~ /.*\*.*/)
	    {
				$self->{Accuracy} = "-1";
				$self->{Hm} = "";
	    }
	    else
	    {
				$self->{Accuracy} = "0";
				my ($h, $m, $s) = split(/\:/, $time);
				$self->{Hm} = "$h:$m";
	    }
	    $self->{Place} = $place;
	    from_to($self->{Place}, "iso-8859-1", "utf-8");
	    my $coun = $self->FetchCountry($code);
	    $self->{Country} = ($coun eq undef) ? "Unknown Country code $code" : $coun;
	    from_to($self->{Country}, "iso-8859-1", "utf-8");
	}
	elsif($l =~ /\#B93:/)
	{
	  $l =~ s/.*\#B93\://;
	  my ($jul, $lat, $long, $tz, $dl) = split(/,/, $l);
	  $self->{Julday} = $jul eq "*" ? "0.0" : $jul;
	  my ($h, $m, $t) = $self->DMS($lat);
	  $t = ($t eq "S") ? "S" : "N";
	  $self->{Latitude}  = "$h:$m$t";
	  ($h, $m, $t) = $self->DMS($long);
	  $t = ($t =~ /E|O/) ? "E" : "W";	  
	  $self->{Longitude} = "$h:$m$t";
	  ($h, $m, $t) = $self->DMS($tz);
	  $t = ($t =~ /HW/) ? "-" : "";
	  $self->{Timezone}  = "$t$h:$m";
	  if($dl =~ /0|1|2/)
	  {
			$self->{Daylight} = $dl . ":00";
		}
		elsif($dl eq uc "H")
		{
			$self->{Daylight} = "0:30";
		}
		else
		{
			$self->{Daylight} = "0:00";
		}
	}
	elsif($l =~ /\#COM:/)
	{
	    $l =~ s/.*\#COM://;
	    $self->{Comment} = $l;
	    from_to($self->{Comment}, "iso-8859-1", "utf-8");
	}
	elsif($l =~ /\#ZNAM:/)
	{
	   $l =~ s/.*\#ZNAM://;
	   $self->{ZoneInfoFile} = $l;
	}
	elsif($l =~/\#CWORD:/)
	{
	  $l =~ s/.*\#CWORD://;
	  $self->{Keywords} .= "$l, ";
  }
	elsif($l =~ /\#ATTRB:/)
	{
	    $l =~ s/.*\#ATTRB://;
	    my @a = split(/,/, $l);
	    foreach my $i (@a)
	    {
				$i =~ s/ *//;
				my ($c, $d) = split(/=/, $i);
				$c = uc $c;
				if($c =~ /^B/)
				{
					$self->{Keywords} .= "Prof=$d, ";
				}
				elsif($c =~ /^K/)
				{
					$self->{Keywords} .= "Chln=$d, ";
				}
				elsif($c =~ /^N/)
				{
					$self->{Keywords} .= "Nat=$d, ";
				}
	    }
	}
	elsif($l =~ /\#GZQ:/)
	{
	    $l =~ s/.*\#GZQ://;
	    my ($ta, $code, $com) = split(/,/, $l);
	    $code = uc $code;
	    $code =~ s/ *//;
      $self->{Keywords} .= "Orig=$src{$code}, " if(exists $src{$code});
	    $self->{Keywords} .= "Cqu=$com, " if($com ne "");
	}
	elsif($l =~ /\#SRC:/)
	{
	    $l =~ s/.*\#SRC://;
	    $l =~ s/,/;/;
	    $self->{Keywords} .= "Src=$l, ";
	}
	elsif($l =~ /\#VIA:/)
	{
	    $l =~ s/.*\#VIA://;
	    $l =~ s/,/;/;
	    $self->{Keywords} .= "Via=$l, ";
	}
	if(eof FILE)
	{
		$self->{Keywords} =~ s/, $//;
		from_to($self->{Keywords}, "iso-8859-1", "utf-8");
		return $l;
	}
	$l = <FILE>;
 }
 while($l !~ /.*\#A93\:/);
 from_to($self->{Keywords}, "iso-8859-1", "utf-8");
 return $l;
}

sub WriteAAFSeg($)
{
    my ($self) = @_;
    my $l = " \#A93:";
    my $name, $fname, $gen, $date, $time, $place, $code, $b, $c = "\x0d\x0a";
    if($self->{Gender} eq "M" || $self->{Gender} eq "F")
    {
				my @na= split /[, -]+/, $self->{Name};
				$name  = pop @na;
				$fname = ($#na < 0) ? "*": join " ", @na;
				$gen = $self->{Gender};
    }
    else
    {
			$name = $self->{Name}; $fname = "*";
			$gen = "L" if($self->{Type} eq "Country");
			$gen = "O" if($self->{Type} eq "Organization"); 	
    }
    $date = "$self->{Day}\.$self->{Month}\.$self->{Year}";
    my ($h, $m) = split(/:/, $self->{Hm});
    $time = "$h:$m";
    $place = $self->{Place};
    $code = $self->FetchCode($self->{Country});
    $l .= "$name,$fname,$gen,$date,$time,$place,$code$c";
    $l .= " #B93:";
    my $jul, $lat, $long, $tz, $dl;
    $jul = $self->{Julday} ne "0.0" ? $self->{Julday} : "*";
    $lat = $self->{Latitude};
    $lat =~ /.*(N|S)$/;
    $b = lc $1;
    $lat =~ s/(N|S)$//;
    $lat =~ s/:/$b/;
    $long = $self->{Longitude};
    $long =~ /.*(E|W)$/;
    $b = lc $1;
    $long =~ s/(E|W)$//;
    $long =~ s/:/$b/;    
    $tz = $self->{Timezone};
    $b = ($tz =~ /^-/) ? "hw" : "he";
    $tz =~ s/-//;
    $tz =~ s/:/$b/;
    if($self->{Daylight} =~ /(0|1|2)\:00/ || $self->{Daylight} =~ /(0|1)/)
    {
			$dl = "$1";
		}
		elsif($self->{Daylight} eq "0:30")
		{
			$dl = "h";
		}
		else
		{
			$sl = "0";
		}
    $l .= "$jul,$lat,$long,$tz,$dl$c";
    $l .= " \#ZNAM:$self->{ZoneInfoFile}$c";
    my $kw = $self->{Keywords};
    my @k = split /, */, $kw;
    my $cw, $att = undef, $via, $source, $gzq;
    foreach my $i (@k)
    {
			if($i =~ /^(\w*)=(.*)/)
			{
				my $tag = $1, $dat = $2;
				$tag = uc $tag;
				$via = $dat if($tag eq "VIA");
				$source = $dat if($tag eq "SRC");
				if($tag eq "ORIG")
				{
						my $key, $val;
						while(($key, $val) = each %src)
						{
								if(uc $val eq uc $dat)
								{
										$gzq .= "$key,";
										goto CONT;
								}
						}
					CONT:
				}
				$gzq  .= $dat if($tag eq "CQU");
				$att .= "B=$dat, " if($tag eq "PROF");
				$att .= "K=$dat, " if($tag eq "CHLN");
				$att .= "N=$dat, " if($tag eq "NAT");
        }
        else
        {
					$cw .= "$i, ";
				}
    }
    $cw =~ s/, $//;
    $att =~ s/, $//;
    $l .= " \#CWORD:$cw$c" if($cw ne undef);
    $l .= " \#ATTRB:$att$c" if($att ne undef);
    $l .= " \#VIA:$via$c" if($via ne undef);
    $l .= " \#GZQ:TA,$gzq$c" if($gzq ne undef);
    $l .= " \#SRC:$source$c" if($src ne undef);
    my $com = $self->{Comment};
    $l .= " \#COM:$com$c" if($com ne undef);
		from_to($l, 'utf-8', 'iso-8859-1');
    return $l;
}

sub ReadMaitreya($*)
{
		my $self = shift;
		local *FILE = shift;
		my $l;
		die "Not a Maitreya file\n" if(<FILE> !~ /^\#Maitreya 3\.0/);
		$l = <FILE>;
		chomp $l;
		$self->{Name} = $l;
		$l = <FILE>;
		chomp $l;
		$self->{Day} = $l;
		$l = <FILE>;
		chomp $l;
		$self->{Month} = $l;
		$l = <FILE>;
		chomp $l;
		$self->{Year} = $l;
		$l = <FILE>;
		chomp $l;
		$self->{Hm} = ::DecToDeg($l);
		$l = <FILE>;
		chomp $l;
		$self->{Timezone} = ::DecToDeg($l);
		$l = <FILE>;
		chomp $l;
		$self->{Daylight} = ::DecToDeg($l);
		$l = <FILE>;
		chomp $l;
		$self->{Place} = $l;
		$l = <FILE>;
		chomp $l;
		$self->{Longitude} = ::DecToDeg($l);
		$l = <FILE>;
		chomp $l;
		$self->{Latitude} = ::DecToDeg($l);
		while($l = <FILE>)
		{
				$self->{Comment} .= $l;
		}
}

sub ConvertLatLong($)
{
		$l = shift;
		$l =~ s/\'/:/;
		$l =~ s/°/:/;
		$l =~s/\"//;
		return $l;
}

sub ReadZet8Seg($$*)
{
		my $self = shift;
    my $l = shift;
    local *FILE = shift;
		my @a = split(/; +/, $l), @d = split(/\./, $a[1]);
		from_to($a[0], "iso-8859-1", "utf-8");
		$self->{Name} = $a[0];
		$self->{Day} = $d[0];
		$self->{Month} = $d[1];
		$self->{Year} = $d[2];
		$self->{Hm} = $a[2];
		$a[3] =~ s/ +//;
		$self->{Timezone} = $a[3];
		from_to($a[4], "iso-8859-1", "utf-8");
		$self->{Place} = $a[4];
		$self->{Latitude} = ConvertLatLong($a[5]);
		$self->{Longitude} = ConvertLatLong($a[6]);
		$self->{Gender} = $a[7];
		from_to($a[8], "iso-8859-1", "utf-8");
		my @c = split(/\|/, $a[8]);
		$self->{Keywords} = "Orig=" . $c[0] . ", Prof=" . $c[2];
		$self->{Comment} = $c[3];
}

sub ReadQCSeg($$$)
{
		my $self = shift;
		my $l = shift;
		my $dbh = shift;
		my($name, $mon, $day, $year, $hour, $min, $sec, $ap, $zone, $long, $lat, $place) = unpack("A23A3xA2xxA4A2xA2xA2xA2xA9A10A9A*", $l);
		my($city, $state) = split /, +/, $place;
		$self->{Name} = $name;
		$self->{Day}  = $day;
		$self->{Month} = $self->GetMonth($mon);
		my @hm = $self->GetTime("$hour:$min:$sec:" . lc $ap);
		$self->{Hm}    = "$hm[0]:$hm[1]:$hm[2]";
		$self->{Year} = $year;
		$self->{Place} = $city;
		$self->{Longitude} = $long;
		$self->{Latitude}  = $lat;
		my $tz = FetchTZ($state, $dbh);
		if($tz)
		{
				$self->{Country} = $state;
				$self->{ZoneInfoFile} = $tz;
		}
		else
		{
				my $usstate = $StateCodes{$state};
				if($usstate)
				{
						($state, $tz) = FetchState($usstate, $dbh);
						$self->{Country} = $state;
						$self->{ZoneInfoFile} = $tz;
				}
		}
}
1;

package SKIF;
use Sys::Hostname;
use Time::localtime;
use Encode 'from_to';
use XML::DOM;

$version = "1.8";

sub new
{
    my $self = [];
    bless $self;
    return $self;
}

sub ReadKst
{
    my ($self, $file, $plcnt) = @_;
    goto CONT if(-r $file && open(FILE, "<$file"));
    return;
CONT:
    $self->[0] = new DATASET;
    $self->[0]->ReadKst(*FILE, $plcnt);
    close FILE;
}

sub ReadSKIF($)
{
    my ($self, $file) = @_;
    my $parser = new XML::DOM::Parser;
    my $doc = $parser->parsefile ($file);
    my $nodes = $doc->getDocumentElement;
    my @ds = $nodes->getElementsByTagName("DATASET");
    my $i = 0;
    foreach my $x (@ds)
    {
			$self->[$i] = new DATASET;
			$self->[$i]->ReadDATASET($x);
			$i++;
    }
    $doc->dispose;
}

sub WriteSKIF($)
{
    my ($self) = @_;
    my $doc = new XML::DOM::Document;
    my $xml = new XML::DOM::XMLDecl;
    $xml->setVersion("1.0");
    $xml->setEncoding("UTF-8");
    $doc->setXMLDecl($xml);
    my $type = new XML::DOM::DocumentType("SKIF", "SKIF", "http://skylendar.kde.org/dtd/skif.dtd", "-//KDE//DTD skif 1.1//EN");
    {
			local $XML::DOM::IgnoreReadOnly = 1;
			local $XML::DOM::SafeMode = 0;  
			$doc->setDoctype($type);
    }
    my $login = $ENV{USER}, $host = hostname, $time = ctime;
    my $comm = $doc->createComment(" Created by skif $version, Author:$login\@$host, Date:$time ");
    $doc->appendChild($comm);
    my $skif = $doc->createElement("SKIF");
    $skif->setAttribute("Version", $version);
    $doc->appendChild($skif);
    my $i = 0;
    while($self->[$i] ne undef)
    {
			$self->[$i]->WriteDATASET($doc, $skif);
			$i++;
    }
    my $s = $doc->toString;
    return $s;
}


sub ReadAAF()
{
    my ($self, $file) = @_;
    open FILE, "<$file" || die "Can't open $file\n";
    my $i = 0;
    my $l = undef;
    while(!eof FILE)
    {
			$l = <FILE> if($l !~ /.*\#A93\:/);
			if($l =~ /.*\#A93:/)
			{
				$self->[$i] = new DATASET;
				$l = $self->[$i]->ReadAAFSeg($l, *FILE);
				$i++;
			}
    }
    close FILE;
}

sub WriteAAF()
{
    my ($self) = @_;
    my $login = $ENV{USER}, $host = hostname, $time = ctime, $c = "\x0d\x0a";
    my $com = "\#:Created by skif $version, Author:$login\@$host, Date:$time$c$c";
    my $i = 0;
    while($self->[$i] ne undef)
    {
			$com .= "#: -----------------$c";
			$com .= $self->[$i]->WriteAAFSeg;
			$i++;
    }
    return $com;
}

sub ReadMaitreya($$)
{
		my ($self, $file) = @_;
		goto CONT if(-r $file && open(FILE, "<$file"));
		return;
CONT:
    $self->[0] = new DATASET;
    $self->[0]->ReadMaitreya(*FILE);
    close FILE;
}

sub ReadZet8()
{
    my ($self, $file) = @_;
    open FILE, "<$file" || die "Can't open $file\n";
    my $i = 0;
    my $l = undef;
    while(!eof FILE)
    {
				$l = <FILE>;
				$self->[$i] = new DATASET;
				$l = $self->[$i]->ReadZet8Seg($l, *FILE);
				$i++;
		}
    close FILE;
}

sub ReadQuickChart()
{
	my ($self, $file, $dbh) = @_;
	open(FILE, "<:encoding(iso-8859-1)", $file) || die "Can't open $file\n";
	my $i = 0;
	my $l = undef;
	while(!eof FILE)
  {
			$l = <FILE>;
			$self->[$i] = new DATASET;
			$l = $self->[$i]->ReadQCSeg($l, $dbh);
			$i++;
	}
	close FILE;
}

1;
