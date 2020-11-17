<?php	
	$ini = parse_ini_file('../../db-config.ini'); // relativer Pfad zur Konfigurations-Datei, diese darf NICHT in einem öffentlichen Ordner liegen
	$db_host = $ini['db_host'];
	$db_name = $ini['db_name'];
	$db_table = $ini['db_table'];
	$db_user = $ini['db_user'];
	$db_password = $ini['db_password'];
	$connection = new mysqli($db_host, $db_user, $db_password, $db_name);
?>

<html>
<head>
<style type="text/css"> <!-- Stylesheet nach eigenen Wünschen anpassen -->

form {
 font-family: Verdana, Arial, Helvetica, sans-serif;
 font-size: 200%;
}
select {
 font-family: Verdana, Arial, Helvetica, sans-serif;
 font-size: 100%;
}
button {
 font-size: 200%;
 width: 150px;
 height: 150px;
}
label {
 font-family: Verdana, Arial, Helvetica, sans-serif;
 font-size: 200%;
}


</style>
	<meta http-equiv="refresh" content="60">
	<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
	<!-- This loads the 'corechart' package. -->	
    <script type="text/javascript">
	   	google.charts.load('current', {packages: ['corechart', 'line']});
		google.charts.setOnLoadCallback(drawCurveTypes);

		function drawCurveTypes() {
			var button15 = document.getElementById('button15');
			button15.onclick = draw15;
			var button30 = document.getElementById('button30');
			button30.onclick = draw30;
			var button60 = document.getElementById('button60');
			button60.onclick = draw60;
			var button120 = document.getElementById('button120');
			button120.onclick = draw120;
			var button360 = document.getElementById('button360');
			button360.onclick = draw360;
			var button720 = document.getElementById('button720');
			button720.onclick = draw720;
			var button1440 = document.getElementById('button1440');
			button1440.onclick = draw1440;
			
			var data = new google.visualization.DataTable();
			data.addColumn('datetime', 'Time');
			data.addColumn('number', 'CO2');
			data.addColumn('number', 'Temperatur');
			data.addColumn('number', 'Feuchtigkeit');
			data.addRows([
			
			<?php
				if (array_key_exists('sensor', $_GET)) {
					$sensorNr = ($_GET['sensor']);
				} else {
					$sensorNr = '01';
				}
				if (array_key_exists('zeitraum', $_GET)) {
					$interval = ($_GET['zeitraum']);
				} else {
					$interval = '30';
				}
				date_default_timezone_set("Europe/Berlin");
				
				$sql = "SELECT sensor, valueco2, valuetemp, valuehumid, reading_time FROM $db_table WHERE sensor = $sensorNr AND DATE_SUB(CURTIME(),INTERVAL $interval MINUTE) <= reading_time ORDER BY reading_time DESC";
				$result = $connection->query($sql);  
							
				
					while ($row = $result->fetch_assoc()) {
						echo "[new Date('".$row["reading_time"]."'),";
						echo $row['valueco2'].",";
						echo $row['valuetemp'].",";
						echo $row['valuehumid']."],";
					}
			?> 

			]);

			var options = {
				chartArea: {
					right: 100,
					left: 100				
				},
				
				title: 'Messwerte für Sensor <?php echo $sensorNr ?>',
				
				curveType : 'function',
				lineWidth : 1,
				pointSize : 0,
				series: {
					0: {targetAxisIndex: 0, color: 'green'},
					1: {targetAxisIndex: 1, color: 'red'},
					2: {targetAxisIndex: 2, color: 'blue'},
				},
				vAxes: {
					0: {title: 'CO2 (ppm)', textPosition: 'out'},
					1: {title: 'Temp (°C)', textPosition: 'in', minValue: 0, maxValue: 50 },
					2: {title: 'Humid (%)', textPosition: 'out', minValue: 0, maxValue: 100 },
				},
				hAxis: {
					gridlines: {
						count: 6,
						units: {
							days: {format: ['dd.MM']},
							hours: {format: ['HH:mm']},
							minutes: {format: ['HH:mm']}
						}
					},
					minorGridlines: {
						count: 10,
						units: {
							hours: {format: ['kk']},
							minutes: {format: [':mm']}
						}
					}					
				}
			};
			var chart = new google.visualization.LineChart(document.getElementById('chart_div'));
			chart.draw(data, options);
		}
		
		function draw15(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=15");			
		}
		function draw30(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=30");		
		}
		function draw60(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=60");		
		}
		function draw120(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=120");		
		}
		function draw360(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=360");		
		}
		function draw720(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=720");		
		}
		function draw1440(){
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum=1440");		
		}
	</script>
	<script>	
	document.addEventListener('DOMContentLoaded', function () {
		document.SensorForm.sensor.addEventListener('change', ChangeSensor);
 		function ChangeSensor () {
			var sensorSelected = document.SensorForm.sensor;
			window.location.replace(window.location.pathname+"?sensor="+sensorSelected.value+"&zeitraum="+<?php if (array_key_exists('zeitraum', $_GET)) {
					echo $_GET['zeitraum'];
				} else {
					echo '30';
				} ?>);		
		}
	});
	
	</script>
	
</head>
<form name="SensorForm">
<label for="sensor">Sensor: 
<select id="sensor" name="sensor">	
  <option value="01"<?= ($_GET['sensor'] == "01")? "selected":"";?>>01</option>
  <option value="02"<?= ($_GET['sensor'] == "02")? "selected":"";?>>02</option>
  <option value="03"<?= ($_GET['sensor'] == "03")? "selected":"";?>>03</option>
  <option value="04"<?= ($_GET['sensor'] == "04")? "selected":"";?>>04</option>	
  <option value="05"<?= ($_GET['sensor'] == "05")? "selected":"";?>>05</option>
  <option value="06"<?= ($_GET['sensor'] == "06")? "selected":"";?>>06</option>
  <option value="07"<?= ($_GET['sensor'] == "07")? "selected":"";?>>07</option>
  <option value="08"<?= ($_GET['sensor'] == "08")? "selected":"";?>>08</option>
  <option value="09"<?= ($_GET['sensor'] == "09")? "selected":"";?>>09</option>	
  <option value="10"<?= ($_GET['sensor'] == "10")? "selected":"";?>>10</option>	
</select>
</label>
</form>
<div id="chart_div" style="width: 100%; height: 50%; halign: center "></div>
<button id="button15" type="button" >15 Min</button>
<button id="button30" type="button">30 Min</button> 
<button id="button60" type="button" >60 Min</button> 
<button id="button120" type="button" >2 Std</button> 
<button id="button360" type="button" >6 Std</button> 
<button id="button720" type="button">12 Std</button> 
<button id="button1440" type="button">24 Std</button> 


