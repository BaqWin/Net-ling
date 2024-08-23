from scapy.all import get_if_list, IP, UDP, Raw, send
import random

interface = "lo0"
packets = []

for _ in range(30):
    src_ip = "127.0.0.1"
    dst_ip = "127.0.0.1"

    ip = IP(src=src_ip, dst=dst_ip)
    udp = UDP(sport=random.randint(1024, 65535), dport=random.randint(1024, 65535))
    packet = ip / udp / Raw(load="This is a test packet!")

    packets.append(packet)

send(packets, iface=interface)
