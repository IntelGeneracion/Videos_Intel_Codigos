<?php
/* ///////////////////////////////////////////////////////////
// Esta preconfiguracion es para  crear y controlar el pin 13 
// de la targeta Intel galileo.
////////////////////////////////////////////////////////////*/
$blink=0;
echo "verificar permisos en archivo export de gpio".'<br>';
$permisos=substr(sprintf('%o', fileperms('/sys/class/gpio/export')), -4);
echo 'Permisos archivo export: '.$permisos.'<br>';

if($permisos=='0775') {
	echo 'OK permisos'.'<br>';
	crear_pin13();
}
else {
	 echo 'No tiene los adecuados'.'<br>';
	 if(chmod("/sys/class/gpio/export", 0755))
	{	
		echo 'realisado'.'<br>';
		crear_pin13();
	}
	else{
		$blink=1;
		echo 'NO se pudo'.'<br>';
	}	
}				 

echo "verificar permisos en archivo direction de gpio3".'<br>';
$permisos=substr(sprintf('%o', fileperms('/sys/class/gpio/gpio3/direction')), -4);
echo 'Permisos archivo direction: '.$permisos.'<br>';

if($permisos=='0775') {
	echo 'OK permisos'.'<br>';
	output_pin13();
}
else {
	 echo 'No tiene los adecuados'.'<br>';
	 if(chmod("/sys/class/gpio/gpio3/direction", 0755))
	{	
		echo 'realisado'.'<br>';
		output_pin13();
	}
	else{
		$blink=1;
		echo 'NO se pudo'.'<br>';
	}	
}

echo "verificar permisos en archivo value de gpio3".'<br>';
$permisos=substr(sprintf('%o', fileperms('/sys/class/gpio/gpio3/value')), -4);
echo 'Permisos archivo direction: '.$permisos.'<br>';

if($permisos=='0775') {
	echo 'OK permisos'.'<br>';
	prendido_pin13();
}
else {
	 echo 'No tiene los adecuados'.'<br>';
	 if(chmod("/sys/class/gpio/gpio3/value", 0755))
	{	
		echo 'realisado'.'<br>';
		prendido_pin13();
	}
	else{
		$blink=1;
		echo 'NO se pudo'.'<br>';
	}	
}

if($blink==0){
		for ($x=0;$x<2;$x++){	
		prendido_pin13();
		Sleep(1);
		apagado_pin13();
		Sleep(1);
	}
}
else{
	header("location:Preconfi.php");
}

// funciones de control para el pin 13
function crear_pin13()
{
	//crear carperas del pin
	$p=fopen("../../sys/class/gpio/export","w");
	echo "export:".$p."<br>";
	fputs($p,"3");
	fclose($p);
}
function eliminar_pin13()
{
	//crear carperas del pin
	$p=fopen("../../sys/class/gpio/unexport","w");
	echo "unexport:".$p."<br>";
	fputs($p,"3");
	fclose($p);
}
function output_pin13()
{
	//colocar el pin de salida o entrada
	$p=fopen("../../sys/class/gpio/gpio3/direction","w");
	echo "direction:".$p."<br>";
	fputs($p,"out");
	fclose($p);
}
function prendido_pin13()
{
	//colocar el pin sendido o apagado
	$p=fopen("../../sys/class/gpio/gpio3/value","w");
	echo "value:".$p."<br>";
	fputs($p,"1");
	fclose($p);
}
function apagado_pin13()
{
	//colocar el pin sendido o apagado
	$p=fopen("../../sys/class/gpio/gpio3/value","w");
	echo "value:".$p."<br>";
	fputs($p,"0");
	fclose($p);
}
?>