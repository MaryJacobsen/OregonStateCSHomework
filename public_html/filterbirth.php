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
			<td>Author[s] born in the year  
			<?php
			if(!($stmt = $mysqli->prepare("SELECT birth_year FROM authors WHERE id = ?"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!($stmt->bind_param("i",$_POST['BirthYear']))){
				echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			if(!$stmt->bind_result($birth_year)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			while($stmt->fetch()){
				echo " " . $birth_year;
			}
			$stmt->close();
			?>
			</td>
		</tr>
		
		<tr>
			<td>First Name</td>
			<td>Last Name</td>
		</tr>
			
		<?php
		if(!($stmt = $mysqli->prepare("SELECT fname, lname FROM authors WHERE birth_year = (SELECT birth_year FROM authors WHERE id = ?)"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!($stmt->bind_param("i",$_POST['BirthYear']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		
		if(!$stmt->bind_result($fname, $lname)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
			
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $fname . "\n</td>\n<td>" . $lname . "\n</td>\n</tr>";
		}
		
		$stmt->close();
		
		?>
	</table>
</div>

</body>
</html>	
	
