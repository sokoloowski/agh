#!/usr/bin/awk -f

# do użycia z plikiem dane.xml

BEGIN {
    RS="\n";
    FS=""
}

{
    if (match($0, / *<osoba>/))
    {
        print "---------------------------"
    }
    else if (match($0, / *<([a-z]+)>.+/))
    {
        print gensub(/ *<([a-z]+)>(.+)<\/.+/, "\\1: \\2", "g", $0)
    }
}

END {
    print "---------------------------"
}
