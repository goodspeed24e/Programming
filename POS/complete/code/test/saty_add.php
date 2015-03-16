<?php
    include("swmcntdb.php");	
	$sql="INSERT INTO saty (satyno, satyname) VALUES ('$satyno', '$satyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   