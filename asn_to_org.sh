#!/bin/bash

curl -s -X GET "https://api.data.caida.org/as2org/v1/asns/$1?dateStart=1970-01-01&dateEnd=$2-$3-$4" -H "accept: application/json" | jq -r '.data' | grep orgName | head -n 1 | sed 's/"orgName": //'  | sed 's/"//g; s/,//g'| sed 's/^[ \t]*//' > output.txt

rm -f tmp.txt
