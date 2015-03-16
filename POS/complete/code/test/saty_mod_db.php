<?php
    include("swmcntdb.php");	
	$sql="UPDATE saty SET satyname = '$satyname' WHERE   satyno = '$satyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   