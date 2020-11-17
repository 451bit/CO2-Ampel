<?php
# Einlesen der Konfigurationsdatei
	$ini = parse_ini_file('../../db-config.ini'); // relativer Pfad zur Konfigurations-Datei, diese darf NICHT in einem öffentlichen Ordner liegen

$db_host = $ini['db_host'];	
$db_name = $ini['db_name'];	
$db_user = $ini['db_user'];	
$db_password = $ini['db_password'];
$db_table = $ini['db_table'];	
$api_key_value = $ini['api_key_value']; 

$api_key = $sensor = $location = $valueco2 = $valuetemp = $valuehumid = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $sensor = test_input($_POST["sensor"]);
        $location = test_input($_POST["location"]);
        $valueco2 = test_input($_POST["valueco2"]);
        $valuetemp = test_input($_POST["valuetemp"]);
        $valuehumid = test_input($_POST["valuehumid"]);
        
        // Verbindung aufbauen
        $conn = new mysqli($db_host, $db_user, $db_password, $db_name);
        // Überprüfen
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        // DB-Abfrage
        $sql = "INSERT INTO $db_table (sensor, location, valueco2, valuetemp, valuehumid)
        VALUES ('" . $sensor . "', '" . $location . "', '" . $valueco2 . "', '" . $valuetemp . "', '" . $valuehumid . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}