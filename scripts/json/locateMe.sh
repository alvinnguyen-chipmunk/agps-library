#!/bin/bash

API_KEY=AIzaSyBx6LZQwV-73Z_LtJLXvcnpUMJpCIaCR6g
JSON_FILE=${1}

if [ -z ${JSON_FILE} ]; then
	printf "\e[31mERROR: no json file\e[0m\n"
	exit
fi

curl -d @${1} -H "Content-Type: application/json" -i "https://www.googleapis.com/geolocation/v1/geolocate?key=${API_KEY}"
