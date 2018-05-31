#!/bin/bash

#this is a game
#filename : game.sh

function dis_welcome()
{
    declare -r str='0000000010000000000000000000000000000010000100000000000000100000
0000000010000000001000001000000000100001000100000000000000101000
1111110010000000000100110011110000010001000100000000000000100100
0000010011111100000100100010010000010111101111100111111000100100
0000010100000100000000100010010010000010001000000000001000100000
0100100100001000000000100010010001000010010000000000001000111110
0010101001000000111100100010010001000011101111000010010111100000
0001010001000000000100100010010000010010100001000001010000100100
0001000001000000000100100010010000010010100010000000100000100100
0010100010100000000100101011010000100010100010000000100000101000
0010010010100000000100110010100011100010101111100001010000101000
0100010100010000000100100010000000100010100010000001001000010000
1000000100010000000100000010000000100100100010000010001000110010
0000001000001000001010000010000000100100100010000100000001001010
0000010000000100010001111111111000101001101010000000000010000110
0000100000000010000000000000000000010000000100000000000100000010'
    declare -i j=0
    declare -i row=5                                    
    line_char_count=65                                  

    echo -ne "\033[37;40m\033[5;3H"                     

    for ((i=0; i<${#str}; i++));do
        # 换行
        if [ "$[i%line_char_count]" == "0" ] && [ "$i" != "0" ];then
            row=$row+1
            echo -ne "\033["$row";3H"
        fi
        if [ "${str:$i:1}" == "0" ];then
            echo -ne "\033[37;40m "
        elif [ "${str:$i:1}" == "1" ];then
            echo -ne "\033[31;40m$"
        fi
    done
}

function dismenu()
{
    while [ 1 ]
    do
        draw_border        
        echo -e  "\033[8;30H1) Number"
        echo -e  "\033[9;30H2) Alphabet"
        echo -e  "\033[10;30H3) AlphaNum"
        echo -e  "\033[11;30H4) Word"
        echo -e  "\033[12;30H5) Exit"
        echo -ne "\033[22;2HPlease enter your choice: "
        read choice
        case $choice in
        "1" )    draw_border
            main digit
            echo -e "\033[39;49m"
            ;;
        "2" )    draw_border
            main char    
            echo -e "\033[39;49m"
            ;;
        "3" )    draw_border
            main mix
            echo -e "\033[39;49m"
            ;;
        "4" )    draw_border
            echo -ne "\033[22;2H"
            read -p "enter a file path as the word source: " file
            if [ ! -f "$file" ];then
                dismenu
            else
                exec 4<$file
                main word
                echo -e "\033[39;49m"
            fi
            ;;
        "5"|"q"|"Q" )
            draw_border
            echo -e "\033[10;25Hyou will exit this game, now"
            echo -e "\033[39;49m"
            sleep 1
            clear
            exit 1
            ;;
        * )
            draw_border
            echo -e "\033[22;2Hyour choice is wrong, please try again"    
            sleep 1
            ;;
        esac
    done
}

function draw_border()
{
    declare -i width
    declare -i high
    width=79
    high=23

    clear

    echo -e "\033[37;40m"
    for (( i=1; i<=$width; i=i+1 ))
    do        
        for (( j=1; j<=$high; j=j+1))
        do
            echo -e "\033["$j";"$i"H "
        done
    done
    
    echo -e "\033[1;1H+\033["$high";1H+\033[1;"$width"H+\033["$high";"$width"H+" 
    for (( i=2; i<=$width-1; i=i+1 ))
    do        
        echo -e "\033[1;"$i"H-"
        echo -e "\033["$high";"$i"H-"
    done
    for (( i=2; i<=$high-1; i=i+1 ))
    do        
        echo -e "\033["$i";1H|"
        echo -e "\033["$i";"$width"H|\n"
    done
}

function doexit()
{  
    draw_border
    echo -e "\033[10;30Hthis game will exit....."
    echo -e "\033[0m"
    sleep 2
    clear
    exit 1
}


function clear_all_area()
{
    local i j
    
    for (( i=5; i<=21; i++ ))
    do
        for (( j=3; j<=77; j=j+1))
        do
            echo -e "\033[44m\033["$i";"$j"H "
        done
    done
    echo -e "\033[37;40m"
}


function clear_line()
{
    local i
    #填充打字区域
    for (( i=5; i<=21; i++ ))
    do
        for (( j=$1; j<=$1+9; j=j+1))
        do
            echo -e "\033[44m\033["$i";"$j"H "
        done
    done
    echo -e "\033[37;40m"
}


function move()
{
    
    local locate_row lastloca
    locate_row=$(($1+5))
    
    echo -e "\033[30;44m\033["$locate_row";"$2"H$3\033[37;40m"
    if [ "$1" -gt "0" ];then
        lastloca=$(($locate_row-1))
    
        echo -e "\033[30;44m\033["$lastloca";"$2"H \033[37;40m"    
    fi
}


function putarray()
{
    local chars
    case $1 in
    digit) 
        chars='0123456789'
        for (( i=0; i<10; i++ ))
        do
            array[$i]=${chars:$i:1}
        done
        ;;
    char)     
        chars='ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
        for (( i=0; i<52; i++ ))
        do
                array[$i]=${chars:$i:1}
        done
        ;;
    mix)     
        chars='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
        for (( i=0; i<62; i++ ))
        do
                array[$i]=${chars:$i:1}
        done
        ;;
    *)  
        ;;
    esac    
}


function get_random_char()
{
    local typenum
    declare -i typenum=0
    case $1 in
    digit)     
        typenum=$(($RANDOM%10))
        ;;
    char)     
        typenum=$(($RANDOM%52))
        ;;
    mix)     
        typenum=$(($RANDOM%62))
        ;;
    *)
        ;;
    esac    
    random_char=${array[$typenum]}    
}

function main()
{
    declare -i gamestarttime=0
    declare -i gamedonetime=0

    declare -i starttime
    declare -i deadtime
    declare -i curtime
    declare -i donetime
    
    declare -i numright=0
    declare -i numtotal=0
    declare -i accuracy=0

    putarray $1

    gamestarttime=`date +%s`

    while :
    do                        
        echo -e "\033[2;2Henter the character before they disappear"

        echo -e "\033[3;2HTime:     "
        curtime=`date +%s`
        gamedonetime=$curtime-$gamestarttime    
        echo -e "\033[31;40m\033[3;15H$gamedonetime s\033[37;40m"
        echo -e "\033[3;60HTotal：\033[31;26m$numtotal\033[37;40m"
        echo -e "\033[3;30HAccuracy：\033[31;40m$accuracy %\033[37;40m"
        echo -ne "\033[22;2Hyour input：                         "
        clear_all_area
        
        for (( line=20; line<=60; line=line+10 ))
        do
             
            if [ "${ifchar[$line]}" == "" ] || [ "${donetime[$line]}" -gt "$time" ]
            then
                
                clear_line $line
                
                if [ "$1" == "word" ];then
                    read -u 4 word
                    if [ "$word" == "" ];then 
                        exec 4<$file
                    fi
                    putchar[$line]=$word
                else
                    get_random_char $1
                    putchar[$line]=$random_char
                fi
                numtotal=$numtotal+1
                
                ifchar[$line]=1
                
                starttime[$line]=`date +%s`
                curtime[$line]=${starttime[$line]}
                donetime[$line]=$time
                
                column[$line]=0
                if [ "$1" == "word" ];then
                    move 0 $line ${putchar[$line]}
                fi
            else
                curtime[$line]=`date +%s`
                donetime[$line]=${curtime[$line]}-${starttime[$line]}
                move ${donetime[$line]} $line ${putchar[$line]}
            fi
        done

        if [ "$1" != "word" ];then
            echo -ne "\033[22;14H" 
            
            if read -n 1 -t 0.5 tmp
            then
                for (( line=20; line<=60; line=line+10 ))
                do
                    if [ "$tmp" == "${putchar[$line]}" ];then
                        clear_line $line
                        ifchar[$line]=""
                        echo -e "\007\033[32;40m\033[4;62H         right !\033[37;40m"
                        numright=$numright+1
                        break
                    else
                        echo -e "\033[31;40m\033[4;62Hwrong,try again!\033[37;40m"
                    fi
                done
            fi
        else
            echo -ne "\033[22;14H" 
            
            if read tmp
            then
                for (( line=20; line<=60; line=line+10 ))
                do
                    if [ "$tmp" == "${putchar[$line]}" ];then
                        clear_line $line
                        
                        ifchar[$line]=""
                        echo -e "\007\033[32;40m\033[4;62H         right !\033[37;40m"
                        numright=$numright+1
                        break
                    else
                        echo -e "\033[31;40m\033[4;62Hwrong,try again!\033[37;40m"
                    fi
                done
            fi
        fi
        trap " doexit " 2
        accuracy=$numright*100/$numtotal
    done
}


declare -i time
function modechoose()
{
    echo -e  "\033[8;30H1) easy mode"
    echo -e  "\033[9;30H2) normal mode"
    echo -e  "\033[10;30H3) difficult mode"
    echo -ne "\033[22;2HPlease input your choice: "
    read mode    
    case $mode in
        "1" )
            time=10
            dismenu 
            ;;
        "2" )
            time=5
            dismenu
            ;;
        "3" )
            time=3
            dismenu
            ;;
        * )
            echo -e "\033[22;2Hyour choice is wrong, please try again"    
            sleep 1
    esac
}

# +------- main --------+

draw_border
dis_welcome
echo -ne "\033[3;30Hstart the game. Y/N : "
read yourchoice
if [ "$yourchoice" == "Y" ] || [ "$yourchoice" == "y" ];then
draw_border
modechoose
else 
    clear
    exit 1
fi

exit 1