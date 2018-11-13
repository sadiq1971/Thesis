
Mac/Simple set bandwidth_ 1Mb

set MESSAGE_PORT 42
set BROADCAST_ADDR -1


# variables which control the number of nodes and how they're grouped
# (see topology creation code below)

set num_nodes 7


set val(chan)           Channel/WirelessChannel    ;#Channel Type
set val(prop)           Propagation/TwoRayGround   ;# radio-propagation model
set val(netif)          Phy/WirelessPhy            ;# network interface type



set val(mac)            Mac/802_11                 ;# MAC type
#set val(mac)            Mac                 ;# MAC type
#set val(mac)                  Mac/Simple


set val(ifq)            Queue/DropTail/PriQueue    ;# interface queue type
set val(ll)             LL                         ;# link layer type
set val(ant)            Antenna/OmniAntenna        ;# antenna model
set val(ifqlen)         50                         ;# max packet in ifq


# DumbAgent, AODV, and DSDV work.  DSR is broken
#set val(rp) DumbAgent
#set val(rp)             DSDV
#set val(rp)             DSR
set val(rp)              AODV


# size of the topography
set val(x)              1000
set val(y)              1000

set val(sc)             "scenario"
set val(cp)             "cbr" 

set ns [new Simulator]

set f [open wireless-flooding.tr w]
$ns trace-all $f
set nf [open wireless-flooding.nam w]
$ns namtrace-all-wireless $nf $val(x) $val(y)

$ns use-newtrace

# set up topography object
set topo       [new Topography]

$topo load_flatgrid $val(x) $val(y)

#
# Create God
#
set god_ [create-god $num_nodes]



#set chan_1_ [new $val(chan)]

$ns node-config -adhocRouting $val(rp) \
                 -llType $val(ll) \
                 -macType $val(mac) \
                 -ifqType $val(ifq) \
                 -ifqLen $val(ifqlen) \
                 -antType $val(ant) \
                 -propType $val(prop) \
                 -phyType $val(netif) \
                 -channelType $val(chan) \
		 		 -topoInstance $topo \
		 		 -agentTrace ON \
                 -routerTrace ON \
                 -macTrace OFF


# subclass Agent/MessagePassing to make it do flooding

Class Agent/MessagePassing/Flooding -superclass Agent/MessagePassing

Agent/MessagePassing/Flooding instproc recv {source sport size data} {
    $self instvar messages_seen node_
    global ns BROADCAST_ADDR

    # extract message ID from message
    set message_id [lindex [split $data ":"] 0]
    puts "\nNode [$node_ node-addr] got message $message_id\n"

    if {[lsearch $messages_seen $message_id] == -1} {
          lappend messages_seen $message_id
        $ns trace-annotate "[$node_ node-addr] received {$data} from $source"
        $ns trace-annotate "[$node_ node-addr] sending message $message_id"
          $self sendto $size $data $BROADCAST_ADDR $sport
    } else {
        $ns trace-annotate "[$node_ node-addr] received redundant message $message_id from $source"
    }
}

Agent/MessagePassing/Flooding instproc send_message {size message_id data port} {
    $self instvar messages_seen node_
    global ns MESSAGE_PORT BROADCAST_ADDR

    lappend messages_seen $message_id
    $ns trace-annotate "[$node_ node-addr] sending message $message_id"
    $self sendto $size "$message_id:$data" $BROADCAST_ADDR $port
}



# create a bunch of nodes
for {set i 0} {$i < $num_nodes} {incr i} {
    set node_($i) [$ns node]
    #$n($i) set Y_ [expr 230*floor($i/$group_size) + 160*(($i%$group_size)>=($group_size/2))]
    #$n($i) set X_ [expr (90*$group_size)*($i/$group_size%2) + 200*($i%($group_size/2))]
    #$n($i) set Z_ 0.0
    $ns initial_node_pos $node_($i) 20
}

puts "Loading scenario file..."
source $val(sc)
source $val(cp)


# attach a new Agent/MessagePassing/Flooding to each node on port $MESSAGE_PORT
# for {set i 0} {$i < $num_nodes} {incr i} {
#     set a($i) [new Agent/MessagePassing/Flooding]
#     $node_($i) attach  $a($i) $MESSAGE_PORT
#     $a($i) set messages_seen {}
# }


# now set up some events
$ns at 0.2 "$a(2) send_message 200 3 {first message}  $MESSAGE_PORT"
# $ns at 0.4 "$a(1) send_message 600 2 {some big message} $MESSAGE_PORT"
# $ns at 0.6 "$a(2) send_message 200 3 {another one} $MESSAGE_PORT"

$ns at 3.0 "finish"

proc finish {} {
        global ns f nf val
        $ns flush-trace
        close $f
        close $nf

        #puts "running nam..."
        #exec nam wireless-flooding.nam &
        exit 0
}

$ns run
