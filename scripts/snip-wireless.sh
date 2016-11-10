#!/bin/bash

WIFI_RAW=./raw_wifi
WIFI_FILTERED=./filtered_wifi
WIFI_INTERFACE=wlan0

function main()
{
	RUN_MODE=${1}
	TEST_FILE=${2}
	CreateRawInput ${RUN_MODE} ${TEST_FILE}
	FilterData
	ExportData
	Cleanup
}

function CreateRawInput()
{
	if [[ ${1} = "test" ]]; then
		GetInput="cat ${2}"
	else
		GetInput="iwlist ${WIFI_INTERFACE} scan"
	fi

	${GetInput} | \
	grep -i \
		-e "Signal" \
		-e "address" \
		-e "channel" | \
		grep -i -v "frequency" \
		> ${WIFI_RAW}
}

function FilterData()
{
	cat ${WIFI_RAW} | \
	sed 's/Cell [0-9][0-9] - Address: //g' | \
    sed 's/Channel:/ /g' | \
    sed 's/Quality=[0-9][0-9]\/[0-9][0-9]//g' | \
    sed 's/Signal level=//g' | \
    sed 's/dBm//g' | \
    sed 's/Quality:[0-9]\/[0-9]//g' | \
    sed 's/Signal level://g' | \
    sed 's/Noise level:-[0-9][0-9]//g' | \
    sed 's/\n/ /g' \
    > ${WIFI_FILTERED}
}

function ExportData()
{
	declare -i LINE=0
	declare -i SIGNAL=0
	# declare -i CHANNEl=0
	declare FIRST_LINE="no"
	declare ADDRESS
	declare -i NUMBER_PROPERTIES=2

	# Openning
	printf "{\n"

	OpenJsonNode "wifi"

	for each in $(cat ${WIFI_FILTERED}); do
		if [[ ${LINE} = ${NUMBER_PROPERTIES} ]]; then
			printf ",\n"
			LINE=0
		fi
		LINE=$((LINE+1))

		if [[ ${LINE} = 1 ]]; then
			ADDRESS=$each
		elif [[ ${LINE} = ${NUMBER_PROPERTIES} ]]; then
			SIGNAL=$each
			CreateJsonNode ${ADDRESS} ${SIGNAL} 0
		fi
	done

	printf "\n"

	CloseJsonNode "wifi"

	# Closing
	printf "}\n"
}

function CreateJsonNode()
{
	ADDRESS=${1}
	SIGNAL=${2}
	AGE=${3}
	# CHANNEL=${4}

	# Openning
	printf "  { "

	# Conten
	printf "\"macAddress\": \"%s\"" ${ADDRESS}
	printf ", "
	printf "\"signalStrength\": %d" ${SIGNAL}
	printf ", "
	printf "\"age\": %d" ${AGE}
	# printf ", "
	# printf "\"channel\": %d" ${CHANNEL}

	# Closing
	printf " }"

}

function OpenJsonNode()
{
	NODE_TYPE=${1}

	printf " "
	if [[ ${NODE_TYPE} = "wifi" ]]; then
		printf "\"wifiAccessPoints\":"
	elif [[ ${NODE_TYPE} = "3g" ]]; then
		printf "\"cellTowers\":"
	fi
	printf " \n [\n"
}

function CloseJsonNode()
{
	NODE_TYPE=${1}

	if [[ ${NODE_TYPE} = "wifi" ]]; then
		printf " ]\n"
	elif [[ ${NODE_TYPE} = "3g" ]]; then
		printf " ]\n"
	fi
}

function Cleanup()
{
	rm ${WIFI_RAW} ${WIFI_FILTERED}
}

main ${1} ${2}
