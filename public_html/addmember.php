<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","jacomary-db","lmR5VpwfeDNwA834","jacomary-db");
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
			
if(!($stmt = $mysqli->prepare("INSERT INTO members(fname, lname, school, fav_author_id) VALUES (?,?,?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
	if(!($stmt->bind_param("sssi",$_POST['FirstName'],$_POST['LastName'],$_POST['School'],$_POST['AuthorId']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " row[s] to members.";
}
?>

