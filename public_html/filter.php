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
			<td>Owner[s] of 
			<?php
			if(!($stmt = $mysqli->prepare("SELECT name FROM books WHERE books.id = ?"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}

			if(!($stmt->bind_param("i",$_POST['Book']))){
				echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
			}

			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			
			if(!$stmt->bind_result($name)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
	
			while($stmt->fetch()){
				echo " " . $name;
			}
			$stmt->close();
			?>
			</td>
		</tr>
		<tr>
			<td>First Name</td>
			<td>Last Name</td>
			<td>School</td>
		</tr>
		<?php
	
		if(!($stmt = $mysqli->prepare("SELECT members.fname, members.lname, members.school FROM members INNER JOIN libraries 
				   	       ON libraries.owner_id = members.id INNER JOIN library_book 
					       ON library_book.lid = libraries.id INNER JOIN books 
					       ON books.id = library_book.bid WHERE books.id = ?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}

		if(!($stmt->bind_param("i",$_POST['Book']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}

		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($fname, $lname, $school)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
	
		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $fname . "\n</td>\n<td>\n" . $lname . "\n</td>\n<td>\n" . $school . "\n</td>\n</tr>";
		}
		$stmt->close();
		?>
	</table>
</div>

</body>
</html>
