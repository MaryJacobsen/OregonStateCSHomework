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
		<td>Books that are part of the  
			<?php
			if(!($stmt = $mysqli->prepare("SELECT genre FROM books WHERE id = ?"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!($stmt->bind_param("i",$_POST['Genre']))){
				echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
			}
		
			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			if(!$stmt->bind_result($genre)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
		
			while($stmt->fetch()){
				echo " " . $genre . " genre";
			}
			$stmt->close();
			?>
		</td>
		</tr>
		
		<?php
		if(!($stmt = $mysqli->prepare("SELECT name FROM books WHERE genre = (SELECT genre FROM books WHERE id = ?)"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!($stmt->bind_param("i",$_POST['Genre']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		
		if(!$stmt->bind_result($name)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
			
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $name . "\n</td>\n</tr>";
		}
		
		$stmt->close();
		
		?>
	</table>
</div>

</body>
</html>	
