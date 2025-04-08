 set ns [new Simulator]

           #
           # Create two nodes
           #
           set n0 [$ns node]
           set n1 [$ns node]

           #
           # Create a trace and arrange for all the trace events of the
           # links subsequently created to be dumped to "out.tr"
           #
           set f [open out.tr w]
           $ns trace-all $f

           #
           # Connect the two nodes with a 1.5Mb link with a transmission
           # delay of 10ms using FIFO drop-tail queuing
           #
           $ns duplex-link $n0 $n1 1.5Mb 10ms DropTail

           #
           # Set up BSD Tahoe TCP connections in opposite directions.
           #
           set tcp_src1 [new Agent/TCP]
           set tcp_snk1 [new Agent/TCPSink]
           set tcp_src2 [new Agent/TCP]
           set tcp_snk2 [new Agent/TCPSink]
           $ns attach-agent $n0 $tcp_src1
           $ns attach-agent $n1 $tcp_snk1
           $ns attach-agent $n1 $tcp_src2
           $ns attach-agent $n0 $tcp_snk2
           $ns connect $tcp_src1 $tcp_snk1
           $ns connect $tcp_src2 $tcp_snk2

           #
           # Create ftp sources at the each node
           #
           set ftp1 [$tcp_src1 attach-source FTP]
           set ftp2 [$tcp_src2 attach-source FTP]

           #
           # Start up the first ftp at the time 0 and
           # the second ftp staggered 1 second later
           #

           $ns at 0.0 "$ftp1 start"
           $ns at 1.0 "$ftp2 start"

           #
           # run the simulation for 10 simulated seconds
           #
           $ns at 10.0 "exit 0"
           $ns runs
