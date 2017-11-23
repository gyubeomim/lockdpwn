#!/usr/bin/perl
=pod
    perl ==> 해킹침투코딩 p148, SNMP 프로토콜을 스캐닝해본 펄 코드
=cut
use Net::Ping;
use Net::SNMP;

@log = 0;
$time = localtime;
push (@log,"\n\n##### $time ######\n\n");

# variable for ping
$ip1 = @ARGV[0];
$ip2 = @ARGV[1];
$rawip1 = get_raw_address($ip1);
$rawip2 = get_raw_address($ip2);

# variable for SNMP
$mibName = "1.2.6.1.2.1.1.5.0"; # system name
$mibDescr = "1.3.6.1.2.1.1.1.0"; # system description
$mibHardwareType = "1.3.6.1.2.1.25.3.2.1.2.1";
$port = 161;
$community = "public";
$retries = 1;

# main loop
for ($counter = $rawip1; $counter <= $rawip2; $counter++)
{
    $host = get_ip_address($counter);
    $pinger = Net::Ping->new("icmp",1,64);

    if ($pinger->ping($host))
    {
        print "\n$host is up \n";
        push (@log, "\n$host is up\n");
        &init_snmp;
        &get_snmp_info;
        $session->close;
        &write_log;
    }
    else
    {
        print "\n$host is down\n";
        push (@log, "\n$host is up\n");
        &write_log;
    }
}

# get the raw version of an IP
sub get_raw_address
{
    my $ipaddress;
    my $oct1;
    my $oct2;
    my $oct3;
    my $oct4;
    my $retval;

    $ipaddress = shift;
    ($oct1, $oct2, $oct3, $oct4) = split /\./, $ipaddress;

    $retval = $oct4 + ($oct3 * 2**8) + ($oct2 * 2**16) + ($oct1 * 2**24);
    return $retval;
}

sub get_ip_address
{
    my $rawaddress;
    my $retval;
    my $oct;
    my $counter;

    $rawaddress = shift;
    while ($counter < 4)
    {
        $oct = $rawaddress % 2**8;
        $retval = $oct . "." . $retval;
        $rawaddress = int($rawaddress / 2 ** 8);
        $counter++;
    }
    chop $retval;

    if ($retval =~ m/\.(255 | 0)$/)
    {
        return 0;
    }
    return $retval;
}

sub init_snmp
{
    ($session, $error) = Net::SNMP->session(
        Hostname => $host,
        Community => $community,
        Port => $port,
        Retries => $retries
        );

    if (!defined($session))
    {
        die "couldn't setup SNMP session\n\n";
    }

    $session->timeout($timeout);
}

sub get_snmp_info
{
    $name = &get_request($mibName);

    if ($name =~ /no response/)
    {
        print "no SNMP response from ", $host, "\n";
        return;
    }
    print "name = ", $name, "\n";
    push (@log, "name = $name");

    $description = &get_request($mibDescr);
    print "description = ", $description, "\n";
    push (@log, "description = $description");

    $hardware = &get_request($mibHardwareType);

    if ($hardware =~ /1.3.6.1.2.1.25.3.1.5/)
    {
        $hardware = "Printer";
    }
    if ($hardware =~ /1.3.6.1.2.1.25.3.1.3/)
    {
        $hardware = "Processor";
    }
    if ($hardware =~ /1.3.6.1.2.1.25.3.1.4/)
    {
        $hardware = "Network";
    }
    if ($hardware =~ /1.3.6.1.2.1.25.3.1.6/)
    {
        $hardware = "Disk Storage";
    }
    if ($hardware =~ //)
    {
        $hardware = "Unknown";
    }
    else
    {
        $hardware = "Unknown"
    }

    print "hardware = ", $hardware, "\n";
    push (@log, "hardware = $hardware");
}

sub get_request
{
    my $response;
    my $return;

    if (!defined($response = $session->get_request($_[0])))
    {
        return "no response";
    }

    $return = $response->{$_[0]};
    return $return;
}

sub write_log
{
    open (LOG, ">> snmp.log") || print "Error Opening snmplog.log: $!\n";
    print LOG join("\n", @log), "\n";
    close(LOG) or die "Error Closing snmplog.log : $!\n";

    @log = (); # clear the log array
}
