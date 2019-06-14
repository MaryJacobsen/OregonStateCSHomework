<?php
	//Turn on error reporting
	ini_set('display_errors', 'On');
	//Connects to the database
	$mysqli = new mysqli("oniddb.cws.oregonstate.edu","jacomary-db","lmR5VpwfeDNwA834","jacomary-db");
	if($mysqli->connect_errno){
		echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;    	 
	}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<div>
	<table>
		<tr>
			<td>Book Club Members</td>
		</tr>
		<tr>
			<td>First Name</td>
			<td>Last Name</td>
			<td>School</td>
			<td>Favorite Author</td>
		</tr>
	<?php
	if(!($stmt = $mysqli->prepare("SELECT members.fname, members.lname, members.school, authors.fname, authors.lname FROM members INNER JOIN authors ON authors.id = members.fav_author_id"))){
		echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
	}

	if(!$stmt->execute()){
		echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

	if(!$stmt->bind_result($mfname, $mlname, $school, $afname, $alname)){
		echo "Bind failed: " . $mysql->connect_errno . " " . $mysqli->connect_error;
	}

	While($stmt->fetch()){
  		echo "<tr>\n<td>\n" . $mfname . "\n</td>\n<td>\n" . $mlname . "\n</td>\n<td>\n" . $school . "\n</td>\n<td>" . $afname . " " . $alname . "\n</td>\n</tr>";
	}
	$stmt->close();
	?>
	</table>
</div>

<div>
	<form method="post" action="addmember.php">

		<fieldset>
			<legend>Add a Member</legend>
			<p>First Name: <input type="text" name="FirstName" /></p>
			<p>Last Name: <input type="text" name="LastName" /></p>	
			<p>School Name: <input tyoe="text" name="School" /></p>
			<p>Author: <select name="AuthorId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, fname, lname FROM authors"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
	   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($id, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" ' . $id . ' "> ' . $fname . " " . $lname . '</option>\n';			
				}
				$stmt->close();
				?>
			</select>
			</p>	
	
		</fieldset>
		<p><input type="submit" /></p>

	</form>
</div>

<div>
	<form method="post" action="update.php">

		<fieldset>
			<legend>Update a Member</legend>
			<p>Select a member to update:<select name="MemberId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, fname, lname FROM members"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($id, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $id . ' "> ' . $fname . " " . $lname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>
			<p>First Name: <input type="text" name="FirstName" /></p>
			<p>Last Name: <input type="text" name="LastName" /></p>	
			<p>School Name: <input tyoe="text" name="School" /></p>
			<p>Author: <select name="AuthorId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, fname, lname FROM authors"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
	   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($id, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" ' . $id . ' "> ' . $fname . " " . $lname . '</option>\n';			
				}
				$stmt->close();
				?>
			</select>
			</p>	
	
		</fieldset>
		<p><input type="submit" /></p>

	</form>
</div>

<div>
	<form method="post" action="filterfav.php">
		<fieldset>
			<legend>Filter By Favorite Author</legend>
			<select name="FavAuthor">

				<?php
				if(!($stmt = $mysqli->prepare("SELECT MIN(authors.id) AS id, authors.fname, authors.lname FROM authors INNER JOIN members ON members.fav_author_id = authors.id GROUP BY authors.lname"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($id, $fname, $lname)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
					echo '<option value=" '. $id . ' "> ' . $fname . " " . $lname . '</option>\n';
				}
				$stmt->close();
				?>

			</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>

<div>
	<table>
		<tr>
			<td>Authors</td>
		</tr>
		<tr>
			<td>First Name</td>
			<td>Last Name</td>
			<td>Birth</td>
			<td>Death</td>
		</tr>
	<?php
	if(!($stmt = $mysqli->prepare("SELECT fname, lname, birth_year, death_year FROM authors"))){
		echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
	}

	if(!$stmt->execute()){
		echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

	if(!$stmt->bind_result($fname, $lname, $birth_year, $death_year)){
		echo "Bind failed: " . $mysql->connect_errno . " " . $mysqli->connect_error;
	}

	While($stmt->fetch()){
  		echo "<tr>\n<td>\n" . $fname . "\n</td>\n<td>\n" . $lname . "\n</td>\n<td>\n" . $birth_year . "\n</td>\n<td>\n" . $death_year . "\n</td>\n</tr>";
	}
	$stmt->close();
	?>
	</table>
</div>

<div>
	<form method="post" action="addauthor.php">

		<fieldset>
			<legend>Add an Author</legend>
			<p>First Name: <input type="text" name="FirstName" /></p>
			<p>Last Name: <input type="text" name="LastName" /></p>
			<p>Year of Birth: <input type="text" name="Birth" /></p>
			<p>Year of Death: <input type="text" name="Death" /></p>
		</fieldset>
		<p><input type="submit" /><p>
	</form>
</div>

<div>
	<form method="post" action="filterbirth.php">
		<fieldset>
			<legend>Filter By Birth Year</legend>
			<select name="BirthYear">
				<?php
				if(!($stmt = $mysqli->prepare("SELECT birth_year, MIN(id) AS id FROM authors GROUP BY birth_year"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($birth_year, $id)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
					echo '<option value=" '. $id . ' "> ' . $birth_year . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>


<div>
	<table>
		<tr>
			<td>Books</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Author</td>
			<td>Genre</td>			
			<td>Publication Year</td>
		</tr>
<?php
	if(!($stmt = $mysqli->prepare("SELECT books.name, authors.fname, authors.lname, books.genre, books.publication_year FROM books INNER JOIN authors ON books.author_id = authors.id"))){
	   	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;	
	}

	if(!$stmt->execute()){
	   	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	if(!$stmt->bind_result($name, $fname, $lname, $genre, $publication_year)){	   	
		echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

	while($stmt->fetch()){
		echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $fname . " " . $lname . "\n</td>\n<td>\n" . $genre . "\n</td>\n<td>\n" . $publication_year . "\n</td>\n</tr>";
	}
	$stmt->close();
?>
	</table>
</div>

<div>
	<form method="post" action="addbook.php"> 

		<fieldset>
			<legend>Add a Book</legend>
			<p>Name: <input type="text" name="Name" /></p>
			<p>Author: <select name="AuthorId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, fname, lname FROM authors"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
	   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($id, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" ' . $id . ' "> ' . $fname . " " . $lname . '</option>\n';			
				}
				$stmt->close();
				?>
			</select>
			</p>	
			<p>Genre: <input type="text" name="Genre" /></p>
			<p>Publication Year: <input type="text" name="PublicationYear" /></p>
		</fieldset>
		<p><input type="submit" /></p>
	</form>
</div>

<div>
	<form method="post" action="filtergenre.php">
		<fieldset>
			<legend>Filter By Genre</legend>
			<select name="Genre">
				<?php
				if(!($stmt = $mysqli->prepare("SELECT genre, MIN(id) AS id FROM books GROUP BY genre"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($genre, $id)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
					echo '<option value=" '. $id . ' "> ' . $genre . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>

<div>
	<table>
		<tr>
			<td>Libraries</td>
		</tr>
		<tr>
			<td>Owner</td>
		</tr>
		<?php
		if(!($stmt = $mysqli->prepare("SELECT members.fname, members.lname FROM libraries INNER JOIN members ON libraries.owner_id = members.id"))){
	   		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}

		if(!$stmt->execute()){
	   		echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
				
		if(!$stmt->bind_result($fname, $lname)){	   	
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}

		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $fname . " " . $lname . "\n</td>\n</tr>";
		}
		$stmt->close();
		?>
	</table>
</div>

<div>
	<form method="post" action="addlibrary.php"> 

		<fieldset>
			<legend>Add a Library</legend>
			<p>Owner: <select name="OwnerId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, fname, lname FROM members"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($id, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $id . ' "> ' . $fname . " " . $lname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>	
		</fieldset>
		<p><input type="submit" /></p>
	</form>
</div>

<div>
	<form method="post" action="filtername.php">
		<fieldset>
			<legend>Filter By Last Name of Library Owner</legend>
			<select name="LastName">
				<?php
				if(!($stmt = $mysqli->prepare("SELECT members.lname, MIN(members.id) AS id FROM members INNER JOIN libraries ON libraries.owner_id = members.id GROUP BY lname"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($lname, $id)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
					echo '<option value=" '. $id . ' "> ' . $lname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>

<div>
	<table>
		<tr>
			<td>Library Books</td>
		</tr>
		<tr>
			<td>Library Owner</td>
			<td>Book</td>
		</tr>
		<?php
		if(!($stmt = $mysqli->prepare("SELECT members.fname, members.lname, books.name FROM members INNER JOIN libraries 
				   	       ON libraries.owner_id = members.id INNER JOIN library_book 
					       ON library_book.lid = libraries.id INNER JOIN books 
					       ON books.id = library_book.bid ORDER BY members.id"))){
	   	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}

		if(!$stmt->execute()){
	   		echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
				
		if(!$stmt->bind_result($fname, $lname, $name)){	   	
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}

		while($stmt->fetch()){
			echo "<tr>\n<td>\n" . $fname . " " . $lname . "\n</td>\n<td>" . $name . "\n</td>\n</tr>";
		}
		$stmt->close();
		?>
	</table>
</div>

<div>
	<form method="post" action="addlibrarybook.php"> 

		<fieldset>
			<legend>Add a Book to a Library</legend>
			<p>Library Owner: <select name="LibraryId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT libraries.id, members.fname, members.lname FROM libraries INNER JOIN members ON libraries.owner_id = members.id"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($lid, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $lid . ' "> ' . $fname . " " . $lname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>	
			
			<p>Book: <select name="BookId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, name FROM books"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($bid, $name)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $bid . ' "> ' . $name . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>	
		</fieldset>
		<p><input type="submit" /></p>
	</form>
</div>

<div>
	<form method="post" action="filter.php">
		<fieldset>
			<legend>Filter By Book</legend>
			<select name="Book">
				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, name FROM books"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($id, $bname)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
					echo '<option value=" '. $id . ' "> ' . $bname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
		</fieldset>
		<input type="submit" value="Run Filter" />
	</form>
</div>

<div>
	<form method="post" action="delete.php"> 

		<fieldset>
			<legend>Delete a Library Book</legend>
			<p>Library Owner: <select name="LibraryId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT libraries.id, members.fname, members.lname FROM libraries INNER JOIN members ON libraries.owner_id = members.id"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($lid, $fname, $lname)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $lid . ' "> ' . $fname . " " . $lname . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>	
			
			<p>Book: <select name="BookId"> 

				<?php
				if(!($stmt = $mysqli->prepare("SELECT id, name FROM books"))){
	   				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}

				if(!$stmt->execute()){
		   				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}

				if(!$stmt->bind_result($bid, $name)){
	   				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				
				while($stmt->fetch()){
	   				echo '<option value=" '. $bid . ' "> ' . $name . '</option>\n';
				}
				$stmt->close();
				?>
			</select>
			</p>	
		</fieldset>
		<p><input type="submit" /></p>
	</form>
</div>

	
</body>
</html>



