# IP2ORG2IP

IP2ORG2IP is an IP to organization name and organization name to IP resolution service. We aim to improve upon current-day IP to Organization attribution services and DNS resolution services such as whois.

### Features

- IP2ORG lookup, allowing a set of IP's at given dates to be input
- ORG2IP lookup, allowing a set of organization names at given dates to be input

These services together provide historic, bulk attribution services, which addresses a key issue of current attribution service


### Importance
IP2ORG and ORG2IP resolution services play a crucial role in the operation of the Internet, providing valuable information regarding domain names, IP addresses, organizations, and autonomous systems. Specifically to networking, these services provide great tools to assist in network troubleshooting, as well as investigations of cyber security incidents

### How address resolution works

- IP resolution works by querying a database that contains IP addresses, along with their corresponding autonomous system number (ASN). The database used is the CAIDA Routeviews Aggregate Dataset, which utilizes information from the University of Oregon's Routeviews Project

- ASN to organization resolution utilizes the CAIDA Inferred AS to ORG Mapping Dataset, using CAIDA's provided API

- Organization name resolution works by querying a database containing every organization names and their associated ASN

- With the associated ASN, we can find the IP address of the company associated with the ASN


## What Are ASN's?
Autonomous Systems (AS) can be most simply described as a group of IP prefixes that follow their own routing policy within said system. These are key at the network layer, with the Internet being viewed as a collection of these systems from a network layer perspective. ASN's are simply the numbers used to manage routing within the network, and exchange information with other autonomous systems. The Internet Assigned Numbers Authority (IANA) allocates these numbers, provided the autonomous system meets the qualifications required by Internet governing bodies

## Procedure

### Client

- Client parses the provided input file
- For each request in the file, format packet accordingly
- Client sends this packet off to the server and awaits a response
- Client receives response, and displays this to the console
- Repeats for each request


### Server 

- When server receives a connection, it will create a thread to receive the packet from the client
- Server will extract the required information from packet
- Dependent on request type, server will either do IP2ORG, or ORG2IP
- Server then sends response back to client with the requested information
- Server waits for any more requests from connection and terminates if none

## More Information
For more information please read the full research paper in the repo: Bulk_Historic_IP2ORG2IP_Attribution.pdf
