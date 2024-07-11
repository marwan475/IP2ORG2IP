#!/bin/bash

curl -s -X GET "https://api.data.caida.org/as2org/v1/search/?name=$1" -H "accept: application/json" | jq -r '.data'| grep asn | head -n 1| sed 's/"asn": //' | sed 's/"//g; s/,//g'| sed 's/^[ \t]*//' > tmp1.txt
