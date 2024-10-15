#!/usr/bin/python3

from scapy.all import *

# Get DST ip addesses via args
inner_ip_addr = sys.argv[1]
outer_ip_addr = sys.argv[2]

# Craft DST inner IP
inner_ip_packet = IP(dst=inner_ip_addr)

# Craft DST outer IP
outer_ip_packet = IP(dst=outer_ip_addr) / inner_ip_packet 

# Send packet
send(outer_ip_packet)