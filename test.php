<?php

$time = microtime(true);
$str = "qwertyuiopasdfghjklzzxcvbnmQWERTYUIOPSDFGHJKLZXCVBNM";
$key = "ini kunci";
for ($i=0; $i < 5000; $i++) { 
	$a = teaEncrypt($str, $key);
	$b = teaDecrypt($a, $key);
	print $i."\n";
	if ($b !== $str) {
		print "Error!\n";
		exit(1);
	}
}
print "Success!\n".(microtime(true) - $time). " seconds\n";
exit(0);
