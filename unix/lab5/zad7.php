#!/usr/bin/php
<?php
pcntl_async_signals(TRUE);
$log_file = trim(shell_exec('echo $HOME')) . '/myps.log';

pcntl_signal(SIGINT, function ($signal) {
    // Ignore ^C
});

pcntl_signal(SIGTERM, function ($signal) {
    // Ignore SIGTERM
});

pcntl_signal(SIGUSR1, function ($signal) {
    global $log_file;
    file_put_contents($log_file, '');
    fwrite(STDERR, 'File ~/myps.log cleaned' . PHP_EOL);
});

if (!file_exists($log_file)) die("Plik $log_file nie istnieje!" . PHP_EOL);
while (true) {
    $log = file_get_contents($log_file);
    $uptime = trim(shell_exec('uptime'));
    $log .= implode(',', [
        date('Y-m-d H:i:s'),
        trim(shell_exec('ps -aux | wc -l')),
        str_replace(' ', '', substr($uptime, strrpos($uptime, ':') + 2))
    ]);
    $log .= PHP_EOL;
    file_put_contents($log_file, $log);
    shell_exec('sleep 3');
}
