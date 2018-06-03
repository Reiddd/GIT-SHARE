#!/bin/bash
# system monitor


# -i : install
# -v : version
# -h : help
while getopts ivh name; do
	case "$name" in
		"i") iopt=1;;
		"v") vopt=1;;
		"h") hopt=1;;
		*)   echo "Invalid arg";exit 1;;
	esac
done


# -i : install
if [[ ! -z $iopt ]]; then # -z : the length of the string == 0
	wd=$(pwd)

	# echo $(basename /path/to/file)  ->  file
	# echo $(readlink linkToorigin)   ->  origin
	# -------
	# [ -L "$0" ] && readlink "$0" || echo "$0"
	# -L : link
	# if [ -L "$0" ]; then readlink "$0"; else echo "$0"; fi
	# -------
	# temporary file stored in /tmp
	basename $([[ -L "$0" ]] && readlink "$0" || echo "$0") > /tmp/scriptname

	# scriptname = currentdir + basename
	scriptname=$(echo -ne "$wd"/ && cat /tmp/scriptname)

	# -c : command
	cp $scriptname /usr/bin/smonitor && echo "script installed." || echo "script installation failed."
fi


# -v : version
if [ ! -z $vopt ]; then
	echo -e "system montior version 0.1\n"
fi


# -h : help
if [ ! -z $hopt ]; then
	echo -e "-i 		Install the script into your system."
	echo -e "-v 		Check the version."
	echo -e "-h 		Get help."
fi


# exit if we run this script with arguments
if [[ ! $# -eq 0 ]]; then
	exit 0
fi


# clear the screen
clear


# those are variables we will use after, double check by `unset` them
unset tecreset os architecture kernelrelease internalip externalip nameserver loadaverage


# tput sgr0
tecreset=$(tput sgr0)


# check for internet connection
# '\E[32m' set printed message to green
ping -c 1 www.reidblog.cn &> /dev/null && echo -e '\E[32m'"Internet: $tecreset Connected" || echo -e '\E[32m'"Internet: $tecreset Disconnected"


# check for system information
os=$(uname -o)		# operating-system : GNU/Linux 
echo -e '\E[32m'"Operating System Type :" $tecreset $os
OS=`uname -s`		# kernel-name      : linux
REV=`uname -r`      # kernel-release   : 4.15.0-22-generic
MACH=`uname -m`     # machine          : x86_64


function GetVersionFromFile()
{
    VERSION=`cat $1 | tr "\n" ' ' | sed s/.VERSION.*=\ // `
}



# kernel-name
if [[ "${OS}" -eq "SunOS" ]]; then
    OS=Solaris
    ARCH=`uname -p`
    OSSTR="${OS} ${REV}(${ARCH} `uname -v`)"

elif [[ "${OS}" -eq "AIX" ]]; then
    OSSTR="${OS} `oslevel` (`oslevel -r`)"

elif [[ "${OS}" -eq "Linux" ]]; then
    KERNEL=`uname -r`
    if [[ -f /etc/redhat-release ]]; then
        DIST='RedHat'
        PSUEDONAME=`cat /etc/redhat-release | sed s/.*\(// | sed s/\)//`
        REV=`cat /etc/redhat-release | sed s/.*release\ // | sed s/\ .*//`

    elif [[ -f /etc/SuSE-release ]]; then
        DIST=`cat /etc/SuSE-release | tr "\n" ' ' | sed s/VERSION.*//`
        REV=`cat /etc/SuSE-release | tr "\n" ' ' | sed s/.*=\ //`

    elif [[ -f /etc/mandrake-release ]]; then
        DIST='Mandrake'
        PSUEDONAME=`cat /etc/mandrake-release | sed s/.*\(// | sed s/\)//`
        REV=`cat /etc/mandrake-release | sed s/.*release\ // | sed s/\ .*//`

    elif [[ -f /etc/debian_version ]]; then
        DIST="Debian `cat /etc/debian_version`"
        REV=""
    fi

    if ${OSSTR} [ -f /etc/UnitedLinux-release ]; then
        DIST="${DIST}[`cat /etc/UnitedLinux-release | tr "\n" ' ' | sed s/VERSION.*//`]"
    fi

    OSSTR="${OS} ${DIST} ${REV}(${PSUEDONAME} ${KERNEL} ${MACH})"
fi


echo -e '\E[32m'"OS Version :" $tecreset $OSSTR

# uname -m : machine, x86_64
architecture=$(uname -m)
echo -e '\E[32m'"Architecture :" $tecreset $architecture

# uname -r : release, 4.15.0-22-generic
kernelrelease=$(uname -r)
echo -e '\E[32m'"Kernel Release :" $tecreset $kernelrelease

echo -e '\E[32m'"Hostname :" $tecreset $HOSTNAME

internalip=$(hostname -I)
echo -e '\E[32m'"Internal IP :" $tecreset $internalip

externalip=$(curl -s ipecho.net/plain;echo)
echo -e '\E[32m'"External IP : $tecreset "$externalip

nameservers=$(cat /etc/resolv.conf | sed '1 d' | awk '{print $2}')
echo -e '\E[32m'"Name Servers :" $tecreset $nameservers 

who>/tmp/who
echo -e '\E[32m'"Logged In users :" $tecreset && cat /tmp/who 

# free
free -h | grep -v + > /tmp/ramcache
echo -e '\E[32m'"Ram Usages :" $tecreset
cat /tmp/ramcache | grep -v "Swap"
echo -e '\E[32m'"Swap Usages :" $tecreset
cat /tmp/ramcache | grep -v "Mem"

# df
df -h| grep 'Filesystem\|/dev/sda*' > /tmp/diskusage
echo -e '\E[32m'"Disk Usages :" $tecreset 
cat /tmp/diskusage

# top
loadaverage=$(top -n 1 -b | grep "load average:" | awk '{print $10 $11 $12}')
echo -e '\E[32m'"Load Average :" $tecreset $loadaverage

tecuptime=$(uptime | awk '{print $3,$4}' | cut -f1 -d,)
echo -e '\E[32m'"System Uptime Days/(HH:MM) :" $tecreset $tecuptime

# unset used variables after use
unset tecreset os architecture kernelrelease internalip externalip nameserver loadaverage

# remove temporary file
rm /tmp/who /tmp/ramcache /tmp/diskusage


shift $(($OPTIND -1))