<?php
	prendido_pin13();
function prendido_pin13()
{
	//colocar el pin sendido o apagado
	$p=fopen("../../sys/class/gpio/gpio3/value","w");
	echo "value:".$p."<br>";
	fputs($p,"1");
	fclose($p);
}
?>