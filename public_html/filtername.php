<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","jacomary-db","lmR5VpwfeDNwA834","jacomary-db");
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<div>
	<table>
		<tr>
			<td>Library Owner[s] with the Last Name 
			<?php
			if(!($stmt = $mysqli->prepare("SELECT lname FROM members WHERE id = ?"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!($stmt->bind_param("i",$_POST['LastName']))){
				echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			if(!$stmt->bind_result($lname)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			while($stmt->fetch()){
				echo " " . $lname;
			}
			$stmt->close();
			?>
			</td>
		</tr>
		<tr>
			<td>First Name</td>
		</tr>
		<?php
	
		if(!($stmt = $mysqli->prepare("SELECT members.fname FROM members INNER JOIN libraries ON libraries.owner_id = members.id WHERE members.lname = (SELECT lname FROM members WHERE id = ?)"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!($stmt->bind_param("i",$_POST['LastName']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		
		if(!$stmt->bind_result($firstname)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
			
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $firstname . "\n</td>\n</tr>";
		}
		
		$stmt->close();
		
		?>
	</table>
</div>

</body>
</html>				  
