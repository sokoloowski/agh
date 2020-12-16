#!/usr/bin/php
<?php
header('Content-Type: text/plain');

function input(): string
{
    return trim(fgets(STDIN));
}

if (!isset($argv[1])) $user = input();
else $user = $argv[1];

if (trim(shell_exec('grep -E ^' . $user . ' /etc/passwd')) == '') die('Użytkownik nie istnieje!');

$ps = explode('\n', trim(shell_exec('ps aux')));
foreach ($ps as $line) {
    global $user;
    $line = preg_replace('/ +/', ' ', $line);
    $col= explode(' ', $line);
    if ($col[0] == $user) shell_exec('kill -SIGUSR1 ' . $col[1]);
}