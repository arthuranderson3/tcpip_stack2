# tcpip_stack2 Design
tcpip stack

## OSI Model
```
|************|
| OSI Model  |
|************|
|Application |
|------------|
|Presentation|
|------------|
|Session     |
|------------|
|Transport   |
|------------|
|Network     |
|------------|
|Data Link   |
|------------|
|Physical    |
|------------|
```

## TCP/IP

```
|************|
|TCP/IP Model|
|************|
|Application |
|------------|
|Transport   |
|------------|
|Network L3  |
|------------|
|Data Link L2|
|------------|
```
## TCP/IP Protocol Suite

```
|**********************************|
| TCP/IP Suite                     |
|**********************************|
| HTTP SMTP Telnet FTP DNS RIP SNMP|
|----------------------------------|
| TCP / UDP                        |
|----------------------------------|
| ARP IP IGMP ICMP                 |
|----------------------------------|
|Ethernet TokenRing ATM FrameRelay |
|----------------------------------|
```


## Network Topology
### Terminology

* Routers - has interfaces / ports - L3 routing
* Switches - has interfaces / ports - L2 routing
* Links - Wires plugged into the interfaces / ports of routers or switches
* Layer 3 - IP Layer IPv4, IPv6
* Interfaces - have Mac Address and optional IP Address
* L2 Routing sends frames from one interface to the next.
* L3 Routing sends packets from one computer to another
* Network ID
* Available Addresses
* Mac is a Manufacture assigned globally unique address
* Neighbor Node - is the owning node that has the intf connected using a cable

### Tools
* Mininet
* ifconfig

### Network Modules
* Node - routers and switches or L3 vs L2 routing
* Intf - interfaces on routers and switches
* Link - wired connection between two interfaces
* IP Address - IPv4 / IPv6
* Mask - represents the size of bits that will be masked 0 - 128
* Mac Address - 6 byte hex
* Topology is a graph of nodes w/ interfaces and links

