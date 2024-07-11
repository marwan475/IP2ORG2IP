#!/bin/bash

if compgen -G "database/routeviews-*-$1$2$3-*.pfx2as" > tmp.txt; then
		echo "file found in database"
else
	wget -q -P database https://publicdata.caida.org/datasets/routing/routeviews-prefix2as/$1/$2/

	OUTPUT=$(cat database/index.html | grep href | grep $1$2$3 | grep -o '"[^"]*"' | tr -d '"')

	touch tmp.txt

	echo "database/" | tr -d "\n" > tmp.txt
	cat database/index.html | grep href | grep $1$2$3 | grep -o '"[^"]*"' | tr -d '"' | sed 's/\.gz$//' >> tmp.txt

	rm -f database/index.html

	echo "${OUTPUT}"

	wget -q -P database https://publicdata.caida.org/datasets/routing/routeviews-prefix2as/$1/$2/$OUTPUT

	gzip -d -f database/$OUTPUT

fi

