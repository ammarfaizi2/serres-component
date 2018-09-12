<?php

// $a = teaEncrypt("asd", "123");
// $b = teaDecrypt($a, "123");
// var_dump($a, $b, base64_encode($a));

for ($i=0; $i < 5000; $i++) { 
	//$str = str_repeat(rand(1,100), rand(1, 100));
	//$key = str_repeat(rand(1,100), rand(1, 100));
	$str = "123";
	$key = "";
	$a = teaEncrypt($str, $key);
	$b = teaDecrypt($a, $key);
	// var_dump($a, $b, base64_encode($a));
	print $i."\n";
	if ($b !== $str) {
		print "Error!\n";
		exit(1);
	}
}
print "Success!\n";
exit(0);