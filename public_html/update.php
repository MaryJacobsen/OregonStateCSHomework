<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","jacomary-db","lmR5VpwfeDNwA834","jacomary-db");
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
			
if(!($stmt = $mysqli->prepare("UPDATE members SET fname = ?, lname = ?, school = ?, fav_author_id = ? WHERE id = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
	if(!($stmt->bind_param("sssii",$_POST['FirstName'],$_POST['LastName'],$_POST['School'],$_POST['AuthorId'],$_POST['MemberId']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " row[s] of members.";
}
?>

