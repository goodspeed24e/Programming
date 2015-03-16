<?php
    include("swmcntdb.php");	
	$sql="INSERT INTO prty (prtyno, prtyname) VALUES ('$prtyno', '$prtyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   