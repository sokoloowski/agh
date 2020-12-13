#!/usr/bin/awk -f
BEGIN {
    RS="\n";
    FS=":"
}

{
    if ($3 < 1000)
    {
        print $1 " " $3
    }
}
