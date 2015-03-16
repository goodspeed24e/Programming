<?php
    include("swmcntdb.php");	
	$sql="UPDATE vety SET vetyname = '$vetyname' WHERE   vetyno = '$vetyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   