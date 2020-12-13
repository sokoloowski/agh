#!/usr/bin/php
<?php
$reminder_path = trim(shell_exec('echo $HOME')) . '/reminder';
if (!file_exists($reminder_path)) die('Plik ' . $reminder_path . ' nie istnieje!');
$reminder = file($reminder_path);

foreach ($reminder as $line) {
    $line = trim($line);
    $date = preg_replace('/(\d{4}-\d{2}-\d{2}).+/', '$1', $line);
    $to_remind = preg_replace('/\d{4}-\d{2}-\d{2} (.+)/', '$1', $line);
    if ($date == date('Y-m-d')) {
        echo $to_remind . PHP_EOL;
    }
}
