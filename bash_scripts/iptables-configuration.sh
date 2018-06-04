#!/bin/bash
# configure iptables


###################################

# tables:
#       raw
#       mangle
#       net
#       filter

# chains:
#       INPUT
#       OUTPUT
#       FORWARD
#       PREROUTING
#       POSTROUTING

# actions:
#       ACCEPT
#       DROP
#       REDIRECT
#       SNAT
#       DNAT
#       MASQUERADE
#       LOG

###################################


# clear existing rules
iptables --flush            # -F : flush       , delete all rules
iptables --delete-chain     # -X : delete-chain, delete all user-defined chains if no chain specified
iptables --zero             # -Z : zerop       , zero counters in chain or all chains


# accept loopback
iptables --append INPUT   --source   127.0.0.1 --destination 127.0.0.1           --jump ACCEPT

# accept established or releated connections
iptables --append INPUT   --match    state     --state       ESTABLISHED,RELATED --jump ACCEPT

# accept all output packages
iptables --append OUTPUT  --jump     ACCEPT

# accept tcp 22
iptables --append INPUT   --protocol tcp       --dport       22                  --jump ACCEPT

# accept tcp 80
iptables --append INPUT   --protocol tcp       --dport       80                  --jump ACCEPT

# accept tcp 21
iptables --append INPUT   --protocol tcp       --dport       21                  --jump ACCEPT

# accept tcp 20
iptables --append INPUT   --protocol tcp       --dport       20                  --jump ACCEPT

# reject all other INPUT connections
iptables --append INPUT   --jump     REJECT

# reject all other FORWARD connections
iptables --append FORWARD --jump     REJECT