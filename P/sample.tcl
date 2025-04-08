set ns [new Simulator]
set nr [open trac.tr w]
set nm [open n.nam w]

$ns trace-all $nr
$ns namtrace-all $nm

proc finish {} {
	global nm nr ns
	$ns flush-trace
	close $nr
	close $nm
	exec nam n.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail


set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n1 $sink0

$ns connect $tcp0 $sink0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set udp0 [new Agent/UDP]
$ns attach-agent $n2 $udp0

set null0 [new Agent/Null]
$ns attach-agent $n3 $null0

$ns connect $udp0 $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

$ns at 1 "$ftp0 start"
$ns at 2 "$cbr0 start"
$ns at 8 "$ftp0 stop"
$ns at 9 "$cbr0 stop"
$ns at 10 "finish"

$ns run
