<?php

$a = teaEncrypt("asd", "123");
$b = teaDecrypt($a, "123");
var_dump($a, $b);
